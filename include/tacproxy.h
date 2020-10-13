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
#ifndef _TACPROXY_H
#define _TACPROXY_H 1

///////////////
//           //
//  Headers  //
//           //
///////////////
#pragma mark - Headers


#include <inttypes.h>


//////////////
//          //
//  Macros  //
//          //
//////////////
#pragma mark - Macros

// Exports function type
#undef TACPROXY_C_DECLS
#undef TACPROXY_BEGIN_C_DECLS
#undef TACPROXY_END_C_DECLS
#undef _TACPROXY_I
#undef _TACPROXY_F
#undef _TACPROXY_V
#if defined(__cplusplus) || defined(c_plusplus)
#   define _TACPROXY_I             extern "C" inline
#   define TACPROXY_C_DECLS        "C"             ///< exports as C functions
#   define TACPROXY_BEGIN_C_DECLS  extern "C" {    ///< exports as C functions
#   define TACPROXY_END_C_DECLS    }               ///< exports as C functions
#else
#   define _TACPROXY_I             inline
#   define TACPROXY_C_DECLS        /* empty */     ///< exports as C functions
#   define TACPROXY_BEGIN_C_DECLS  /* empty */     ///< exports as C functions
#   define TACPROXY_END_C_DECLS    /* empty */     ///< exports as C functions
#endif
#ifdef WIN32
#   ifdef _LIB_LIBTACPROXY_H
#      define _TACPROXY_F   extern TACPROXY_C_DECLS __declspec(dllexport)   ///< used for library calls
#      define _TACPROXY_V   extern TACPROXY_C_DECLS __declspec(dllexport)   ///< used for library calls
#   else
#      define _TACPROXY_F   extern TACPROXY_C_DECLS __declspec(dllimport)   ///< used for library calls
#      define _TACPROXY_V   extern TACPROXY_C_DECLS __declspec(dllimport)   ///< used for library calls
#   endif
#else
#   ifdef _LIB_LIBTACPROXY_H
#      define _TACPROXY_F   /* empty */                                      ///< used for library calls
#      define _TACPROXY_V   extern TACPROXY_C_DECLS                         ///< used for library calls
#   else
#      define _TACPROXY_F   extern TACPROXY_C_DECLS                         ///< used for library calls
#      define _TACPROXY_V   extern TACPROXY_C_DECLS                         ///< used for library calls
#   endif
#endif


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
TACPROXY_BEGIN_C_DECLS


TACPROXY_END_C_DECLS
#endif /* end of header */
