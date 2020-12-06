/*
 *  TACACS+ Proxy Server and Utilities
 *  Copyright (c) 2020 Alaska Communications
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *     1. Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *
 *     2. Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *
 *     3. Neither the name of the copyright holder nor the names of its
 *        contributors may be used to endorse or promote products derived from
 *        this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 *  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 *  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 *  lib/libtacacs/lversion.c version functions
 */
#define _LIB_LIBTACACS_LCONF_C 1
#include "lconf.h"

///////////////
//           //
//  Headers  //
//           //
///////////////
#pragma mark - Headers

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <regex.h>


#undef  RC_CONF_REGEX
#define RC_CONF_REGEX  "^[[:space:]]*"         /* ignore leading white space */ \
                       "([-_a-z0-9]+)"         /* option name */\
                       "[[:space:]]+"          /* ignore white space delimitor */ \
                       "("                     \
                          "on|off|"            /* boolean value */ \
                          "[0-9]+|"            /* numerical value */ \
                          "\"[^\"]+\"|"        /* double quoted value */ \
                          "'[^']+'|"           /* single quoted value */ \
                          "[^\'\"[:space:]]+"  /* unquoted value */ \
                       ")"                     \
                       "[[:space:]]*"          /* ignore trailing white space */ \
                       "(#.*){0,1}$"           /* ignore trailing comment */

#undef  RC_CONF_MAX_MATCHES
#define RC_CONF_MAX_MATCHES   5


/////////////////
//             //
//  Datatypes  //
//             //
/////////////////
#pragma mark - Datatypes

typedef struct my_conf_parser
{
   regex_t                    reg;
   char *                     line;
   size_t                     linecap;
   regmatch_t *               matches;
} MyConfParser;


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#pragma mark - Prototypes

_TACPP_F int
tacacs_conf_defaults(
       TACACS *                        td );

_TACPP_F int
tacacs_conf_file(
       TACACS *                        td );

_TACPP_F int
tacacs_conf_file_free(
       TACACS *                        td,
       MyConfParser *                  parser );

_TACPP_F int
tacacs_conf_file_parse(
       TACACS *                        td,
       MyConfParser *                  parser,
       const char *                    filename );

_TACPP_F int
tacacs_conf_parse(
       TACACS *                        td,
       int                             field,
       const char *                    value );

_TACPP_F int
tacacs_conf_variables(
       TACACS *                        td );


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#pragma mark - Functions

int tacacs_conf( TACACS * td )
{
   int           rc;
   char *        str;

   assert(td != NULL);

   if ((rc = tacacs_conf_defaults(td)) != TACACS_SUCCESS)
      return(rc);

   if ((str = getenv("TACACSNOINIT")) != NULL)
      return(TACACS_SUCCESS);

   if ((rc = tacacs_conf_file(td)) != TACACS_SUCCESS)
      return(rc);

   if ((rc = tacacs_conf_variables(td)) != TACACS_SUCCESS)
      return(rc);

   return(TACACS_SUCCESS);
}


int tacacs_conf_defaults( TACACS * td)
{
   int rc;
   int ival;

   assert(td != NULL);


   ival = TACACS_DFLT_KEEPALIVE_IDLE;
   if ((rc = tacacs_set_option(td, TACACS_OPT_KEEPALIVE_IDLE, &ival)) != TACACS_SUCCESS)
      return(rc);

   ival = TACACS_DFLT_KEEPALIVE_INTERVAL;
   if ((rc = tacacs_set_option(td, TACACS_OPT_KEEPALIVE_INTERVAL, &ival)) != TACACS_SUCCESS)
      return(rc);

   ival = TACACS_DFLT_KEEPALIVE_PROBES;
   if ((rc = tacacs_set_option(td, TACACS_OPT_KEEPALIVE_PROBES, &ival)) != TACACS_SUCCESS)
      return(rc);

   ival = TACACS_DFLT_NETWORK_TIMEOUT;
   if ((rc = tacacs_set_option(td, TACACS_OPT_NETWORK_TIMEOUT, &ival)) != TACACS_SUCCESS)
      return(rc);

   ival = TACACS_DFLT_RESTART;
   if ((rc = tacacs_set_option(td, TACACS_OPT_RESTART, &ival)) != TACACS_SUCCESS)
      return(rc);

   ival = TACACS_DFLT_TIMEOUT;
   if ((rc = tacacs_set_option(td, TACACS_OPT_TIMEOUT, &ival)) != TACACS_SUCCESS)
      return(rc);

   ival = TACACS_DFLT_UNENCRYPTED;
   if ((rc = tacacs_set_option(td, TACACS_OPT_UNENCRYPTED, &ival)) != TACACS_SUCCESS)
      return(rc);

   if ((rc = tacacs_set_option(td, TACACS_OPT_URL, TACACS_DFLT_URL)) != TACACS_SUCCESS)
      return(rc);


   return(TACACS_SUCCESS);
}


int tacacs_conf_file(TACACS * td)
{
   int                 rc;
   size_t              size;
   char *              home;
   char *              tacacsconf;
   char *              tacacsrc;
   char                path[256];
   MyConfParser        parser;

   assert(td != NULL);


   bzero(&parser, sizeof(MyConfParser));


   // compile regex
   if ((rc = regcomp(&parser.reg, RC_CONF_REGEX, REG_EXTENDED|REG_ICASE)) != 0)
      return(TACACS_EUNKNOWN);


   // allocate buffer for matches
   size = sizeof(regmatch_t) * (parser.reg.re_nsub + 1);
   if ((parser.matches = malloc(size)) == NULL)
   {
      tacacs_conf_file_free(td, &parser);
      return(TACACS_ENOMEM);
   };
   bzero(parser.matches, size);


   home       = getenv("HOME");
   tacacsconf = getenv("TACACSCONF");
   tacacsrc   = getenv("TACACSRC");


   snprintf(path, sizeof(path), "%s/tacacs.conf", SYSCONFDIR);
   tacacs_conf_file_parse(td, &parser, path);


   if ((home))
   {
      snprintf(path, sizeof(path), "%s/tacacsrc", home);
      tacacs_conf_file_parse(td, &parser, path);

      snprintf(path, sizeof(path), "%s/.tacacsrc", home);
      tacacs_conf_file_parse(td, &parser, path);
   };


   if ((tacacsconf))
      tacacs_conf_file_parse(td, &parser, tacacsconf);


   if ( ((home)) && ((tacacsrc)) )
   {
      snprintf(path, sizeof(path), "%s/%s", home, tacacsrc);
      tacacs_conf_file_parse(td, &parser, path);

      snprintf(path, sizeof(path), "%s/.%s", home, tacacsrc);
      tacacs_conf_file_parse(td, &parser, path);
   };


   // free regex
   tacacs_conf_file_free(td, &parser);

   return(TACACS_SUCCESS);
}


int tacacs_conf_file_free( TACACS * td, MyConfParser * parser )
{
   assert(td     != NULL);
   assert(parser != NULL);

   if ((parser->line))
      free(parser->line);

   if ((parser->matches))
      free(parser->matches);

   regfree(&parser->reg);

   bzero(parser, sizeof(MyConfParser));

   return(TACACS_SUCCESS);
}


int tacacs_conf_file_parse( TACACS * td, MyConfParser * parser,
   const char * filename )
{
   int         rc;
   FILE *      fs;
   ssize_t     len;
   size_t      lineno;
   size_t      nmatch;
   char *      field;
   char *      val;

   assert(td       != NULL);
   assert(filename != NULL);


   // open file for reading
   if ((fs = fopen(filename, "r")) == NULL)
   {
      fprintf(stderr, "%s: %s\n", filename, strerror(errno));
      return(TACACS_EUNKNOWN);
   };


   // resets file stats
   lineno = 0;
   nmatch = parser->reg.re_nsub+1;


   // loops through file, one line at a time
   while((len = getline(&parser->line, &parser->linecap, fs)) > 0)
   {
      // increment line number and truncate newline
      lineno++;
      parser->line[len-1] = '\0';

      // checks line against regular expression
      if ((rc = regexec(&parser->reg, parser->line, nmatch, parser->matches, 0)) != 0)
         continue;

      // isoloate field
      parser->line[parser->matches[1].rm_eo] = '\0';
      field = &parser->line[parser->matches[1].rm_so];

      // isoloate value
      parser->line[parser->matches[2].rm_eo] = '\0';
      val = &parser->line[parser->matches[2].rm_so];
      if (val[0] == '"')
      {
         parser->line[parser->matches[2].rm_eo-1] = '\0';
         val = &parser->line[parser->matches[2].rm_so+1];
      };

      // store values
      if (!(strcmp(field,      "keepalive_idle")))
         tacacs_conf_parse(td, TACACS_OPT_KEEPALIVE_IDLE,     val);
      else if (!(strcmp(field, "keepalive_interval")))
         tacacs_conf_parse(td, TACACS_OPT_KEEPALIVE_INTERVAL, val);
      else if (!(strcmp(field, "keepalive_probes")))
         tacacs_conf_parse(td, TACACS_OPT_KEEPALIVE_PROBES,   val);
      else if (!(strcmp(field, "network_timeout")))
         tacacs_conf_parse(td, TACACS_OPT_NETWORK_TIMEOUT,    val);
      else if (!(strcmp(field, "timeout")))
         tacacs_conf_parse(td, TACACS_OPT_TIMEOUT,            val);
      else if (!(strcmp(field, "secret")))
         tacacs_conf_parse(td, TACACS_OPT_SECRET,             val);
      else if (!(strcmp(field, "restart")))
         tacacs_conf_parse(td, TACACS_OPT_RESTART,            val);
      else if (!(strcmp(field, "unencrypted")))
         tacacs_conf_parse(td, TACACS_OPT_UNENCRYPTED,        val);
      else if (!(strcmp(field, "url")))
         tacacs_conf_parse(td, TACACS_OPT_URL,                val);
   };


   // close file
   fclose(fs);

   return(TACACS_SUCCESS);
}


int tacacs_conf_parse( TACACS * td, int field, const char * value )
{
   int i;

   assert(td  != NULL);

   if (!(value))
      return(TACACS_SUCCESS);
   if (!(value[0]))
      return(TACACS_SUCCESS);

   switch(field)
   {
      case TACACS_OPT_KEEPALIVE_IDLE:
      case TACACS_OPT_KEEPALIVE_INTERVAL:
      case TACACS_OPT_KEEPALIVE_PROBES:
      case TACACS_OPT_NETWORK_TIMEOUT:
      case TACACS_OPT_TIMEOUT:
      i = atoi(value);
      return(tacacs_set_option(td, field, &i));


      case TACACS_OPT_SECRET:
      case TACACS_OPT_URL:
      return(tacacs_set_option(td, field, value));


      case TACACS_OPT_RESTART:
      case TACACS_OPT_UNENCRYPTED:
      if (!(strcasecmp(value, "on")))
         i = TACACS_OPT_ON;
      else if  (!(strcasecmp(value, "off")))
         i = TACACS_OPT_OFF;
      else
         return(TACACS_EUNKNOWN);
      return(tacacs_set_option(td, field, &i));


      default:
      break;
   };


   return(TACACS_EUNKNOWN);
}


int tacacs_conf_variables( TACACS * td )
{
   assert(td != NULL);

   tacacs_conf_parse(td, TACACS_OPT_KEEPALIVE_IDLE,     getenv("TACACSKEEPALIVE_IDLE"));
   tacacs_conf_parse(td, TACACS_OPT_KEEPALIVE_INTERVAL, getenv("TACACSKEEPALIVE_INTERVAL"));
   tacacs_conf_parse(td, TACACS_OPT_KEEPALIVE_PROBES,   getenv("TACACSKEEPALIVE_PROBES"));
   tacacs_conf_parse(td, TACACS_OPT_NETWORK_TIMEOUT,    getenv("TACACSNETWORK_TIMEOUT"));
   tacacs_conf_parse(td, TACACS_OPT_TIMEOUT,            getenv("TACACSTIMEOUT"));
   tacacs_conf_parse(td, TACACS_OPT_SECRET,             getenv("TACACSSECRET"));
   tacacs_conf_parse(td, TACACS_OPT_RESTART,            getenv("TACACSRESTART"));
   tacacs_conf_parse(td, TACACS_OPT_UNENCRYPTED,        getenv("TACACSUNENCRYPTED"));
   tacacs_conf_parse(td, TACACS_OPT_URL,                getenv("TACACSURL"));

   return(TACACS_SUCCESS);
}


/* end of source*/
