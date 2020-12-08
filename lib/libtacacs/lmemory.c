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
 *  lib/libtacacs/lversion.c version functions
 */
#define _LIB_LIBTACACS_LMEMORY_C 1
#include "lmemory.h"

///////////////
//           //
//  Headers  //
//           //
///////////////
#pragma mark - Headers

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include "lconf.h"


//////////////
//          //
//  Macros  //
//          //
//////////////
#pragma mark - Macros


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


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#pragma mark - Prototypes

int
tacacs_get_option_flag(
       TACACS *                        td,
       int *                           outvalue,
       uint64_t                        flag );

int
tacacs_get_option_int(
       TACACS *                        td,
       int *                           outvalue,
       int                             invalue );

int
tacacs_get_option_string(
       TACACS *                        td,
       char **                         outvalue,
       const char *                    invalue );

int
tacacs_set_option_flag(
       TACACS *                        td,
       const int *                     invalue,
       uint64_t                        flag );

int
tacacs_set_option_int(
       TACACS *                        td,
       const int *                     invalue,
       int *                           outvalue );

int
tacacs_set_option_string(
       TACACS *                        td,
       const char *                    invalue,
       char **                         outvalue );

int
tacacs_set_option_socket(
       TACACS *                        td,
       const int *                     invalue );

int
tacacs_set_option_url(
       TACACS *                        td,
       const char *                    invalue );


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#pragma mark - Functions

int tacacs_get_option( TACACS * td, int option, void * outvalue )
{
   assert(td       != NULL);
   assert(outvalue != NULL);

   switch(option)
   {
      case TACACS_OPT_FLAGS:
      *((uint64_t *)outvalue) = td->flags;
      return(TACACS_SUCCESS);

      case TACACS_OPT_KEEPALIVE_IDLE:
      return(tacacs_get_option_int(td, outvalue, td->keepalive_idle));

      case TACACS_OPT_KEEPALIVE_INTERVAL:
      return(tacacs_get_option_int(td, outvalue, td->keepalive_interval));

      case TACACS_OPT_KEEPALIVE_PROBES:
      return(tacacs_get_option_int(td, outvalue, td->keepalive_probes));

      case TACACS_OPT_NETWORK_TIMEOUT:
      return(tacacs_get_option_int(td, outvalue, td->network_timeout));

      case TACACS_OPT_RESTART:
      return(tacacs_get_option_flag(td, outvalue, TACACS_FLG_RESTART));

      case TACACS_OPT_SECRET:
      return(tacacs_get_option_string(td, outvalue, td->secret));

      case TACACS_OPT_SOCKET:
      return(tacacs_get_option_int(td, outvalue, td->s));

      case TACACS_OPT_TIMEOUT:
      return(tacacs_get_option_int(td, outvalue, td->timeout));

      case TACACS_OPT_UNENCRYPTED:
      return(tacacs_get_option_flag(td, outvalue, TACACS_FLG_UNENCRYPTED));

      case TACACS_OPT_URL:
      return(tacacs_get_option_string(td, outvalue, td->url));

      default:
      break;
   };

   return(TACACS_EBADOPT);
}


int tacacs_get_option_flag( TACACS * td, int * outvalue, uint64_t flag )
{
   assert(td       != NULL);
   assert(outvalue != NULL);

   *outvalue = ((td->flags & flag) == 0) ? TACACS_OPT_OFF : TACACS_OPT_ON;

   return(TACACS_SUCCESS);
}


int tacacs_get_option_int( TACACS * td, int * outvalue, int invalue )
{
   assert(td       != NULL);
   assert(outvalue != NULL);

   *outvalue = invalue;

   return(TACACS_SUCCESS);
}


int tacacs_get_option_string( TACACS * td, char ** outvalue, const char * invalue )
{
   char * str;

   assert(td       != NULL);
   assert(outvalue != NULL);

   str = NULL;
   if ((invalue))
      if ((str = strdup(invalue)) == NULL)
         return(TACACS_ENOMEM);
   *outvalue = str;

   return(TACACS_SUCCESS);
}


int tacacs_initialize( TACACS ** tdp, const char * url, uint64_t flags )
{
   int      rc;
   TACACS * td;

   assert(tdp != NULL);

   *tdp = NULL;

   // initialize memory
   if ((td = malloc(sizeof(TACACS))) == NULL)
   {
      return(TACACS_ENOMEM);
   };
   bzero(td, sizeof(TACACS));
   td->s     = -1;
   td->flags = (TACACS_FLG_MASK_USER & flags);


   // parse configurations
   if ((rc = tacacs_conf(td)) != TACACS_SUCCESS)
   {
      tacacs_unbind(td);
      return(rc);
   };


   // verify and saves URI
   if ((url))
   {
      if ((rc = tacacs_set_option(td, TACACS_OPT_URL, url)) != TACACS_SUCCESS)
      {
         tacacs_unbind(td);
         return(rc);
      };
   };


   // saves memory
   *tdp = td;

   return(0);
}


void tacacs_memfree( void * p )
{
   if (!(p))
      return;
   free(p);
   return;
}


int tacacs_set_option( TACACS * td, int option, const void * invalue )
{
   assert(invalue  != NULL);
   assert(td       != NULL);

   switch(option)
   {
      case TACACS_OPT_KEEPALIVE_IDLE:
      return(tacacs_set_option_int(td, invalue, &td->keepalive_idle));

      case TACACS_OPT_KEEPALIVE_INTERVAL:
      return(tacacs_set_option_int(td, invalue, &td->keepalive_interval));

      case TACACS_OPT_KEEPALIVE_PROBES:
      return(tacacs_set_option_int(td, invalue, &td->keepalive_probes));

      case TACACS_OPT_NETWORK_TIMEOUT:
      return(tacacs_set_option_int(td, invalue, &td->network_timeout));

      case TACACS_OPT_RESTART:
      return(tacacs_set_option_flag(td, invalue, TACACS_FLG_RESTART));

      case TACACS_OPT_SECRET:
      return(tacacs_set_option_string(td, invalue, &td->secret));

      case TACACS_OPT_SOCKET:
      return(tacacs_set_option_socket(td, invalue));

      case TACACS_OPT_TIMEOUT:
      return(tacacs_set_option_int(td, invalue, &td->timeout));

      case TACACS_OPT_UNENCRYPTED:
      return(tacacs_set_option_flag(td, invalue, TACACS_FLG_UNENCRYPTED));

      case TACACS_OPT_URL:
      return(tacacs_set_option_url(td, invalue));

      default:
      break;
   };

   return(TACACS_EBADOPT);
}


int tacacs_set_option_flag( TACACS * td, const int * invalue, uint64_t flag )
{
   assert(td       != NULL);
   assert(invalue  != NULL);

   switch(*invalue)
   {
      case TACACS_OPT_ON:
      td->flags |= flag;
      break;

      case TACACS_OPT_OFF:
      td->flags &= ~flag;
      break;

      default:
      return(TACACS_EUNKNOWN);
   };

   return(TACACS_SUCCESS);
}


int tacacs_set_option_int( TACACS * td, const int * invalue, int * outvalue )
{
   assert(td       != NULL);
   assert(outvalue != NULL);

   *outvalue  = *invalue;

   return(TACACS_SUCCESS);
}


int tacacs_set_option_string( TACACS * td, const char * invalue, char ** outvalue )
{
   char *      str;

   assert(td       != NULL);
   assert(outvalue != NULL);

   // copies secret
   if ((str = strdup(invalue)) == NULL)
      return(TACACS_ENOMEM);

   // free old secret
   if ((td->secret))
      free(td->secret);

   // saves new secret
   td->secret =  str;
   td->flags  &= ~((uint64_t)TACACS_FLG_UNENCRYPTED);

   return(TACACS_SUCCESS);
}


int tacacs_set_option_socket( TACACS * td, const int * invalue)
{
   assert(td       != NULL);

   // closes existing socket
   if ((td->flags & TACACS_FLG_LIBSOCKET) == TACACS_FLG_LIBSOCKET)
      if (td->s != -1)
         close(td->s);

   // stores external socket
   td->flags  &= ~((uint64_t)TACACS_FLG_LIBSOCKET);
   td->s       = *invalue;

   return(TACACS_SUCCESS);
}


int tacacs_set_option_url( TACACS * td, const char * invalue )
{
   int                  rc;
   char *               str;
   TACACSURLDesc *      tudp;

   assert(td       != NULL);


   // parses URL
   if ((rc = tacacs_url_parse(invalue, &tudp)) != TACACS_SUCCESS)
      return(rc);
   if ((str = strdup(invalue)) == NULL)
   {
      tacacs_free_urldesc(tudp);
      return(TACACS_ENOMEM);
   };


   // saves value
   if ((td->url))
      free(td->url);
   td->url = str;
   if ((td->tudp))
      tacacs_free_urldesc(td->tudp);
   td->tudp = tudp;


   return(TACACS_SUCCESS);
}


int tacacs_unbind( TACACS * td )
{
   assert(td != NULL);

   // free URI
   if ((td->secret))   free(td->secret);
   if ((td->tudp))     tacacs_free_urldesc(td->tudp);
   if ((td->url))      free(td->url);

   // closes socket
   if ((td->flags & TACACS_FLG_LIBSOCKET) == TACACS_FLG_LIBSOCKET)
      if (td->s != -1)
         close(td->s);

   // free TACACS struct
   bzero(td, sizeof(TACACS));
   free(td);

   return(0);
}


/* end of source*/
