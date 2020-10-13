/*
 *  TACACS+ Proxy and Tools
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
 *  include/tacproxy.h common includes and prototypes
 */
#define _LIB_LIBTACPROXY_LVERSION_C 1
#include "lversion.h"

///////////////
//           //
//  Headers  //
//           //
///////////////
#pragma mark - Headers


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

const char * tacproxy_lib_info( uint32_t * agep, uint32_t * currentp,
   uint32_t * revisionp )
{
   if ((currentp))  *currentp  = LIB_VERSION_CURRENT;
   if ((agep))      *agep      = LIB_VERSION_AGE;
   if ((revisionp)) *revisionp = LIB_VERSION_REVISION;
   return(LIB_VERSION_INFO);
}


const char * tacproxy_version( uint32_t * majorp, uint32_t * minorp,
   uint32_t * patchp, const char ** buildp )
{
   if ((majorp)) *majorp = GIT_PACKAGE_MAJOR;
   if ((minorp)) *minorp = GIT_PACKAGE_MINOR;
   if ((patchp)) *patchp = GIT_PACKAGE_PATCH;
   if ((buildp)) *buildp = GIT_PACKAGE_BUILD;
   return(GIT_PACKAGE_VERSION_BUILD);
}


/* end of source*/
