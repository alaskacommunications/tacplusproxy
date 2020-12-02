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
#define _LIB_LIBTACACS_LURL_C 1
#include "lurl.h"

///////////////
//           //
//  Headers  //
//           //
///////////////
#pragma mark - Headers

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <regex.h>
#include <arpa/inet.h>


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#pragma mark - Functions

void tacacs_free_urldesc( TACACSURLDesc * tudp)
{
   if (!(tudp))
      return;

   if (!(tudp->tud_scheme))     free(tudp->tud_scheme);
   if (!(tudp->tud_host))       free(tudp->tud_host);

   bzero(tudp, sizeof(TACACSURLDesc));
   free(tudp);

   return;
}


int tacacs_is_ldap_url( const char * url )
{
   size_t       p;

   assert(url != NULL);


   // test URL scheme
   if (!(strncasecmp(url, "tacacs://", strlen("tacacs://"))))
      url += strlen("tacacs://");
   else if (!(strncasecmp(url, "tacplus://", strlen("tacplus://"))))
      url += strlen("tacplus://");
   else
      return(TACACS_EBADURL);


   // test host
   if (url[0] == '[')
   {
      for(p = 1; (url[p] != ']'); p++)
      {
         if ((url[p] >= 'a') && (url[p] <= 'f')) continue;
         if ((url[p] >= 'A') && (url[p] <= 'F')) continue;
         if ((url[p] >= '0') && (url[p] <= '9')) continue;
         if  (url[p] == ':')                     continue;
         return(TACACS_EBADURL);
      };
      url += p + 1;
   } else {
      for(p = 0; ((url[p] != ':')&&(url[p] != '\0')&&(url[p] != '/')); p++)
      {
         if ((url[p] >= 'a') && (url[p] <= 'z')) continue;
         if ((url[p] >= 'A') && (url[p] <= 'Z')) continue;
         if ((url[p] >= '0') && (url[p] <= '9')) continue;
         if ((url[p] == '.') || (url[p] == '-')) continue;
         return(TACACS_EBADURL);
      };
      url += p;
   };


   // test port
   if (url[0] == ':')
   {
      for(p = 1; ((url[p] != '\0') && (url[p] != '/')); p++)
      {
         if ((url[p] >= '0') && (url[p] <= '9'))
            continue;
         return(TACACS_EBADURL);
      };
      url += p + 1;
   };


   return(TACACS_SUCCESS);
}


int tacacs_url_parse( const char * curl, TACACSURLDesc ** tudpp )
{
   int                rc;
   size_t             pos;
   char *             str;
   char *             url;
   char *             port;
   char *             p;
   TACACSURLDesc *    tudp;
   struct in6_addr    addr;

   assert(curl  != NULL);
   assert(tudpp != NULL);

   *tudpp = NULL;


   // allocate initial memory
   if ((tudp = malloc(sizeof(TACACSURLDesc))) == NULL)
      return(TACACS_URL_ERR_MEM);
   bzero(tudp, sizeof(TACACSURLDesc));


   // allocates temp string
   if ((str = strdup(curl)) == NULL)
   {
      tacacs_free_urldesc(tudp);
      return(TACACS_ENOMEM);
   };
   url = str;


   // determines URL scheme
   if (!(strncasecmp(url, "tacacs://", strlen("tacacs://"))))
   {
      url += strlen("tacacs://");
      if ((tudp->tud_scheme = strdup("tacacs")) == NULL)
      {
         tacacs_free_urldesc(tudp);
         free(str);
         return(TACACS_ENOMEM);
      };
   }
   else if (!(strncasecmp(url, "tacplus://", strlen("tacplus://"))))
   {
      url += strlen("tacplus://");
      if ((tudp->tud_scheme = strdup("tacacs")) == NULL)
      {
         tacacs_free_urldesc(tudp);
         free(str);
         return(TACACS_ENOMEM);
      };
   }
   else
   {
      tacacs_free_urldesc(tudp);
      free(str);
      return(TACACS_URL_ERR_BADSCHEME);
   };


   // set default values
   tudp->tud_port = TACACS_DEFAULT_PORT;


   // tests for end of URL
   if ((p = strchr(url, '/')) != NULL)
   {
      p[0] = '\0';
      if (p[1] != '\0')
      {
         tacacs_free_urldesc(tudp);
         free(str);
         return(TACACS_EBADURL);
      };
   };


   // test host
   port = NULL;
   if (url[0] == '[')
   {
      url++;
      if ((p = strchr(url, ']')) == NULL)
      {
         tacacs_free_urldesc(tudp);
         free(str);
         return(TACACS_URL_ERR_BADHOST);
      };
      p[0] = '\0';
      if ((tudp->tud_host = strdup(url)) == NULL)
      {
         tacacs_free_urldesc(tudp);
         free(str);
         return(TACACS_ENOMEM);
      };
      url = p;
      url++;
      if ((port = strchr(url, ':')) != NULL)
      {
         port++;
      } else if (url[0] != '\0')
      {
         tacacs_free_urldesc(tudp);
         free(str);
         return(TACACS_EBADURL);
      };
   } else
   {
      if ((port = strchr(url, ':')) != NULL)
      {
         port[0] = '\0';
         port++;
      };
      if ((tudp->tud_host = strdup(url)) == NULL)
      {
         tacacs_free_urldesc(tudp);
         free(str);
         return(TACACS_ENOMEM);
      };
   };


   // look for port
   if ((port))
   {
      p = NULL;
      tudp->tud_port = (int)strtol(port, &p, 10);
      if (p == port)
      {
         tacacs_free_urldesc(tudp);
         free(str);
         return(TACACS_URL_ERR_BADPORT);
      };
      if (p[0] != '\0')
      {
         tacacs_free_urldesc(tudp);
         free(str);
         return(TACACS_URL_ERR_BADPORT);
      };
   };


   // verifies hostname syntax
   if ((rc = inet_pton(AF_INET6, tudp->tud_host, &addr)) == 1)
   {
      free(str);
      *tudpp = tudp;
      return(TACACS_URL_SUCCESS);
   };
   for(pos = 0; (tudp->tud_host[pos] != '\0'); pos++)
   {
      if ((tudp->tud_host[pos] >= 'a') && (tudp->tud_host[pos] <= 'z'))
         continue;
      if ((tudp->tud_host[pos] >= 'A') && (tudp->tud_host[pos] <= 'Z'))
         continue;
      if ((tudp->tud_host[pos] >= '0') && (tudp->tud_host[pos] <= '9'))
         continue;
      if ((tudp->tud_host[pos] == '.') || (tudp->tud_host[pos] == '-'))
      {
         if (pos == 0)
         {
            tacacs_free_urldesc(tudp);
            free(str);
            return(TACACS_URL_ERR_BADHOST);
         };
         if ((tudp->tud_host[pos-1] == '.') || (tudp->tud_host[pos-1] == '-'))
         {
            tacacs_free_urldesc(tudp);
            free(str);
            return(TACACS_URL_ERR_BADHOST);
         };
         if ((tudp->tud_host[pos] == '-') && (tudp->tud_host[pos+1] == '\0'))
         {
            tacacs_free_urldesc(tudp);
            free(str);
            return(TACACS_URL_ERR_BADHOST);
         };
         continue;
      };
      tacacs_free_urldesc(tudp);
      free(str);
      return(TACACS_URL_ERR_BADHOST);
   };
   if (pos == 0)
   {
      tacacs_free_urldesc(tudp);
      free(str);
      return(TACACS_URL_ERR_BADHOST);
   };


   // frees resources and stores URL description
   free(str);
   *tudpp = tudp;


   return(TACACS_URL_SUCCESS);
}


/* end of source*/
