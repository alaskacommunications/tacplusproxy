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


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#pragma mark - Functions

int tacacs_defaults( TACACS * td)
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


/* end of source*/
