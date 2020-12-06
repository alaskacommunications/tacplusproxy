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
 *  include/tacproxy.h common includes and prototypes
 */
#ifndef _LIB_LIBTACACS_LIBTACACS_H
#define _LIB_LIBTACACS_LIBTACACS_H 1

///////////////
//           //
//  Headers  //
//           //
///////////////
#pragma mark - Headers


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <assert.h>
#include <tacplusproxy/tacacs.h>


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

#define TACACS_FLG_LIBSOCKET       0x01  ///< socket opened by library
#define TACACS_FLG_SERVER          0x02  ///< library processing as server
#define TACACS_FLG_RESTART         0x04
#define TACACS_FLG_UNENCRYPTED     0x08


/////////////////
//             //
//  Datatypes  //
//             //
/////////////////
#pragma mark - Datatypes

/// TACACS URL
struct tacacs_url_desc
{
   char *                          tud_scheme;
   char *                          tud_host;
   int                             tud_port;
   int                             pad_int;
};


struct tacacs
{
   int                             s;
   int                             timeout;
   int                             network_timeout;
   int                             keepalive_idle;
   int                             keepalive_probes;
   int                             keepalive_interval;
   uint64_t                        flags;
   char *                          url;
   char *                          secret;
   TACACSURLDesc *                 tudp;
};


struct tacproxy_header
{
   uint8_t   version;
   uint8_t   type;
   uint8_t   seq_no;
   uint8_t   flags;
   uint32_t  session_id;
   uint32_t  length;
};


struct tacproxy_packet
{
   struct tacproxy_header hdr;
   uint8_t                bdy[];
};


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#pragma mark - Prototypes
TACPP_BEGIN_C_DECLS


TACPP_END_C_DECLS
#endif /* end of header */
