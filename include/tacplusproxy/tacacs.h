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
#ifndef _TACPLUSPROXY_TACACS_H
#define _TACPLUSPROXY_TACACS_H 1

///////////////
//           //
//  Headers  //
//           //
///////////////
#pragma mark - Headers


#include <inttypes.h>
#include <tacplusproxy/tac_plus.h>
#include <tacplusproxy/cdefs.h>


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

#define TACACS_PORT                    49


#define TACACS_SUCCESS                 0x00     ///< Success
#define TACACS_ENOMEM                  0x01     ///< Cannot allocate memory
#define TACACS_EBADURL                 0x02     ///< Bad URL
#define TACACS_EBADOPT                 0x03     ///< Bad TACACS option
#define TACACS_EUNKNOWN                -1       ///< Unknown error


#define TACACS_URL_SUCCESS             0x00              ///< Success
#define TACACS_URL_ERR_BADSCHEME       0x40000001        ///< unsupported or unknown URI scheme
#define TACACS_URL_ERR_BADHOST         0x40000002        ///< invalid host
#define TACACS_URL_ERR_BADPORT         0x40000003        ///< invalid port
#define TACACS_URL_ERR_BADURL          TACACS_EBADURL    ///< bad URL port
#define TACACS_URL_ERR_MEM             TACACS_ENOMEM     ///< can't allocate memory space


#define TACACS_OPT_URL                 1  ///< URL of TACACS+ Server
#define TACACS_OPT_NETWORK_TIMEOUT     2  ///< Timeout in seconds for connect and poll() operations
#define TACACS_OPT_RESTART             3  ///< should should  implicitly  restart connections
#define TACACS_OPT_KEEPALIVE_IDLE      4  ///< seconds a connection is idle before sending keepalive probes
#define TACACS_OPT_KEEPALIVE_PROBES    5  ///< maximum number of keepalive probes TCP to send before dropping the connection
#define TACACS_OPT_KEEPALIVE_INTERVAL  6  ///< the interval in seconds between keepalive probes
#define TACACS_OPT_SOCKET              7
#define TACACS_OPT_TIMEOUT             8
#define TACACS_OPT_UNENCRYPTED         9
#define TACACS_OPT_SECRET             10
#define TACACS_OPT_FLAGS              11


#define TACACS_OPT_OFF                 0
#define TACACS_OPT_ON                  1


#define TACACS_DFLT_KEEPALIVE_IDLE     300
#define TACACS_DFLT_KEEPALIVE_INTERVAL 75
#define TACACS_DFLT_KEEPALIVE_PROBES   9
#define TACACS_DFLT_NETWORK_TIMEOUT    10
#define TACACS_DFLT_RESTART            TACACS_OPT_OFF
#define TACACS_DFLT_TIMEOUT            120
#define TACACS_DFLT_UNENCRYPTED        TACACS_OPT_ON
#define TACACS_DFLT_URL                "tacacs://localhost/"


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

/// internal libtacacs.la state data
typedef struct tacacs TACACS;

/// TACACS URL description
typedef struct tacacs_url_desc TACACSURLDesc;


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#pragma mark - Prototypes
TACPP_BEGIN_C_DECLS

//-----------------//
// error functions //
//-----------------//
#pragma mark - error functions

_TACPP_F const char *
tacacs_err2string(
       int                             err );


//------------------//
// memory functions //
//------------------//
#pragma mark - memory functions

_TACPP_F int
tacacs_get_option(
       TACACS *                        td,
       int                             option,
       void *                          outvalue );

_TACPP_F int
tacacs_initialize(
       TACACS **                       tdp,
       const char *                    url );

_TACPP_F void
tacacs_memfree(
       void *                          p );

_TACPP_F int
tacacs_set_option(
       TACACS *                        td,
       int                             option,
       const void *                    invalue );

_TACPP_F int
tacacs_unbind(
       TACACS *                        td );


//---------------//
// URL functions //
//---------------//
#pragma mark - URL functions

_TACPP_F void
tacacs_free_urldesc(
       TACACSURLDesc *                 tudp );

_TACPP_F int
tacacs_is_tacacs_url(
       const char *                    url );

_TACPP_F int
tacacs_url_parse(
       const char *                    url,
       TACACSURLDesc **                tudpp );


//-------------------//
// version functions //
//-------------------//
#pragma mark - version functions

_TACPP_F const char *
tacacs_api_version(
       void );

_TACPP_F const char *
tacacs_version(
       void );


TACPP_END_C_DECLS
#endif /* end of header */
