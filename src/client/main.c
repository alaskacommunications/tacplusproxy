/*
 *  TACACS+ Proxy Server and Utilities
 *  Copyright (c) 2020 David M. Syzdek <david@syzdek.net>
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
 *  include/tacproxy.h common includes and prototypes
 */
#define _SRC_CLI_MAIN_C 1

///////////////
//           //
//  Headers  //
//           //
///////////////
#pragma mark - Headers

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <tacplusproxy/tacacs.h>
#include <pwd.h>
#include <unistd.h>
#include <getopt.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


///////////////////
//               //
//  Definitions  //
//               //
///////////////////
#pragma mark - Definitions


/////////////////
//             //
//  Datatypes  //
//             //
/////////////////
#pragma mark - Datatypes

struct tacplus_cfg
{
   int                      silent;
   int                      verbose;
   int                      debug;
   int                      prompt;
   const char *             prog_name;
   TACACS *                 td;
};
typedef struct tacplus_cfg TACPLUSCFG;


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#pragma mark - Prototypes

int
main(
       int                             argc,
       char *                          argv[] );

int
my_debug(
       TACPLUSCFG *                    td );

void
my_debug_bool(
       const char *                    fld,
       int                             i );

void
my_debug_int(
       const char *                    fld,
       int                             i );

void
my_debug_str(
       const char *                    fld,
       char *                          str );

void
my_free_cfg(
       TACPLUSCFG *                    cfg );

void
my_usage(
       const char *                    prog_name );

void
my_version(
       void );


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#pragma mark - Functions

int main(int argc, char * argv[])
{
   int              rc;
   int              c;
   int              opt_index;
   char *           str;
   char *           prog_name;
   TACPLUSCFG *     cfg;

   static char          short_options[]   = "dH:hqvVWw:";
   static struct option long_options[]    =
   {
      { "debug",         no_argument,       0, 'd' },
      { "help",          no_argument,       0, 'h' },
      { "quiet",         no_argument,       0, 'q' },
      { "silent",        no_argument,       0, 'q' },
      { "verbose",       no_argument,       0, 'v' },
      { "version",       no_argument,       0, 'V' },
      { NULL,            0,                 0, 0   }
   };


   // determine program name
   if ((prog_name = rindex(argv[0], '/')) == NULL)
      prog_name = argv[0];
   else
      prog_name = &prog_name[1];


   // initialize TACACS handle
   if ((cfg = malloc(sizeof(TACPLUSCFG))) == NULL)
   {
      fprintf(stderr, "%s: out of virtual memory\n", prog_name);
      return(1);
   };
   bzero(cfg, sizeof(TACPLUSCFG));
   if ((rc = tacacs_initialize(&cfg->td, NULL)) != TACACS_SUCCESS)
   {
      fprintf(stderr, "%s: %s\n", prog_name, tacacs_err2string(rc));
      my_free_cfg(cfg);
      return(1);
   };


   // loops through args
   while((c = getopt_long(argc, argv, short_options, long_options, &opt_index)) != -1)
   {
      switch(c)
      {
         case -1:       /* no more arguments */
         case 0:        /* long options toggles */
         break;

         case 'd':
         cfg->debug++;
         break;

         case 'H':
         if ((rc = tacacs_set_option(cfg->td, TACACS_OPT_URL, optarg)) != TACACS_SUCCESS)
         {
            fprintf(stderr, "%s: %s\n", prog_name, tacacs_err2string(rc));
            my_free_cfg(cfg);
            return(1);
         };
         break;

         case 'h':
         my_usage(prog_name);
         return(0);

         case 'q':
         cfg->silent  = 1;
         cfg->verbose = 0;
         break;

         case 'V':
         my_version();
         return(0);

         case 'v':
         cfg->verbose++;
         cfg->silent = 0;
         break;

         case 'W':
         cfg->prompt = 1;
         break;

         case 'w':
         if ((rc = tacacs_set_option(cfg->td, TACACS_OPT_SECRET, optarg)) != TACACS_SUCCESS)
         {
            fprintf(stderr, "%s: %s\n", prog_name, tacacs_err2string(rc));
            my_free_cfg(cfg);
            return(1);
         };
         break;

         // argument error
         case '?':
         fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
         return(1);

         // unknown argument error
         default:
         fprintf(stderr, "%s: unrecognized option `--%c'\n", PROGRAM_NAME, c);
         fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
         return(1);
      };
   };


   // prompt for secret
   if ((cfg->prompt))
   {
      if ((str = getpass("Enter TACACS Secret: ")) == NULL)
      {
         fprintf(stderr, "%s: %s\n", prog_name, tacacs_err2string(TACACS_ENOMEM));
         my_free_cfg(cfg);
         return(1);
      };
      if ((rc = tacacs_set_option(cfg->td, TACACS_OPT_SECRET, str)) != TACACS_SUCCESS)
      {
         fprintf(stderr, "%s: %s\n", prog_name, tacacs_err2string(rc));
         my_free_cfg(cfg);
         return(1);
      };
   };


   // print debug information
   if ((cfg->debug))
   {
      my_debug(cfg);
      my_free_cfg(cfg);
      return(0);
   };


   my_free_cfg(cfg);


   return(0);
}


int my_debug( TACPLUSCFG * cfg )
{
   int        i;
   char *     str;
   uint64_t   u64;

   printf("%-20s %s\n", "Library Version:", tacacs_version() );
   printf("%-20s %s\n", "Library API:",     tacacs_api_version() );

   tacacs_get_option(cfg->td, TACACS_OPT_KEEPALIVE_IDLE, &i);
   my_debug_int( "Keepalive Idle:", i );

   tacacs_get_option(cfg->td, TACACS_OPT_KEEPALIVE_INTERVAL, &i);
   my_debug_int( "Keepalive Interval:", i );

   tacacs_get_option(cfg->td, TACACS_OPT_KEEPALIVE_PROBES, &i);
   my_debug_int( "Keepalive Probes:", i );

   tacacs_get_option(cfg->td, TACACS_OPT_NETWORK_TIMEOUT, &i);
   my_debug_int( "Network Timeout:", i );

   tacacs_get_option(cfg->td, TACACS_OPT_TIMEOUT, &i);
   my_debug_int( "Request Timeout:", i );

   tacacs_get_option(cfg->td, TACACS_OPT_RESTART, &i);
   my_debug_bool( "Restart:", i );

   tacacs_get_option(cfg->td, TACACS_OPT_SECRET, &str);
   my_debug_str( "Secret:", str );

   tacacs_get_option(cfg->td, TACACS_OPT_UNENCRYPTED, &i);
   my_debug_bool( "Unencrypted:", i );

   tacacs_get_option(cfg->td, TACACS_OPT_URL, &str);
   my_debug_str( "URL:", str );

   tacacs_get_option(cfg->td, TACACS_OPT_FLAGS, &u64);
   printf("%-20s 0x%08" PRIx64 "\n", "Internal Flags:", u64);

   return(0);
}


void my_debug_bool( const char * fld, int i)
{
   printf("%-20s %s\n", fld, ((i == TACACS_OPT_ON) ? "on" : "off"));
   return;
}


void my_debug_int( const char * fld, int i)
{
   printf("%-20s %i\n", fld, i);
   return;
}


void my_debug_str( const char * fld, char * str)
{
   if (!(str))
   {
      printf("%-20s \"\"\n", fld);
      return;
   };
   printf("%-20s \"%s\"\n", fld, str);
   free(str);
   return;
}


/// frees configuration struct
void my_free_cfg(TACPLUSCFG * cfg)
{
   assert(cfg != NULL);

   if ((cfg->td)) tacacs_unbind(cfg->td);
   bzero(cfg, sizeof(TACPLUSCFG));
   free(cfg);

   return;
}


/// prints program usage and exits
void my_usage(const char * prog_name)
{
   printf("Usage: %s [OPTIONS]\n", prog_name);
   printf("OPTIONS:\n");
   printf("  -H url                    TACACS server URL\n");
   printf("  -h, --help                print this help and exit\n");
   printf("  -q, --quiet, --silent     do not print messages\n");
   printf("  -v, --verbose             print verbose messages\n");
   printf("  -V, --version             print version number and exit\n");
   printf("  -W                        prompt for TACACS server secret\n");
   printf("  -w secret                 TACACS server secret\n");
   printf("\n");
   return;
}


/// displays version information
void my_version(void)
{
   printf("%s (%s) %s\n", PROGRAM_NAME, PACKAGE_NAME, PACKAGE_VERSION);
   return;
}


/* end of source */
