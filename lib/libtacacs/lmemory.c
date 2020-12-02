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


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#pragma mark - Functions

int tacacs_initialize( TACACS ** tdp, const char * url )
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


   // verify and saves URI
   if ((url))
   {
      if ((td->url = strdup(url)) == NULL)
      {
         tacacs_unbind(td);
         return(TACACS_ENOMEM);
      };
      if ((rc = tacacs_url_parse(url, &td->tudp)) != TACACS_SUCCESS)
      {
         tacacs_unbind(td);
         return(rc);
      };
   };


   // saves memory
   *tdp = td;

   return(0);
}


int tacacs_unbind( TACACS * td )
{
   assert(td != NULL);

   // free URI
   if ((td->url))      free(td->url);
   if ((td->tudp))     tacacs_free_urldesc(td->tudp);

   // free TACACS struct
   bzero(td, sizeof(TACACS));
   free(td);

   return(0);
}


/* end of source*/
