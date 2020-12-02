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
#ifndef _TACPLUSPROXY_TACACS_H
#define _TACPLUSPROXY_TACACS_H 1

///////////////
//           //
//  Headers  //
//           //
///////////////
#pragma mark - Headers


#include <inttypes.h>
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

// TACACS+ packet version
#define TAC_PLUS_MAJOR_VER                 0x0c  ///< major TACACS+ version number
#define TAC_PLUS_MINOR_VER_DEFAULT         0x00  ///< minor TACACS+ version number
#define TAC_PLUS_MINOR_VER_ONE             0x01  ///< minor TACACS+ version number

// TACACS+ packet type
#define TAC_PLUS_AUTHEN                    0x01  ///< authentication packet
#define TAC_PLUS_AUTHOR                    0x02  ///< authorization packet
#define TAC_PLUS_ACCT                      0x03  ///< accounting packet

// TACACS+ packet flags
#define TAC_PLUS_UNENCRYPTED_FLAG          0x01  ///< body of packet is not obfuscated
#define TAC_PLUS_SINGLE_CONNECT_FLAG       0x04  ///< single connection mode

// TACACS+ authentication START packet action
#define TAC_PLUS_AUTHEN_LOGIN              0x01
#define TAC_PLUS_AUTHEN_CHPASS             0x02
#define TAC_PLUS_AUTHEN_SENDAUTH           0x04

// TACACCS+ authentication START packet type
#define TAC_PLUS_AUTHEN_TYPE_ASCII         0x01
#define TAC_PLUS_AUTHEN_TYPE_PAP           0x02
#define TAC_PLUS_AUTHEN_TYPE_CHAP          0x03
#define TAC_PLUS_AUTHEN_TYPE_MSCHAP        0x05
#define TAC_PLUS_AUTHEN_TYPE_MSCHAPV2      0x06

// TACACS+ authentication START packet service
#define TAC_PLUS_AUTHEN_SVC_NONE           0x00
#define TAC_PLUS_AUTHEN_SVC_LOGIN          0x01
#define TAC_PLUS_AUTHEN_SVC_ENABLE         0x02
#define TAC_PLUS_AUTHEN_SVC_PPP            0x03
#define TAC_PLUS_AUTHEN_SVC_PT             0x05
#define TAC_PLUS_AUTHEN_SVC_RCMD           0x06
#define TAC_PLUS_AUTHEN_SVC_X25            0x07
#define TAC_PLUS_AUTHEN_SVC_NASI           0x08
#define TAC_PLUS_AUTHEN_SVC_FWPROXY        0x09

// TACACS+ authentication REPLY packet status
#define TAC_PLUS_AUTHEN_STATUS_PASS        0x01
#define TAC_PLUS_AUTHEN_STATUS_FAIL        0x02
#define TAC_PLUS_AUTHEN_STATUS_GETDATA     0x03
#define TAC_PLUS_AUTHEN_STATUS_GETUSER     0x04
#define TAC_PLUS_AUTHEN_STATUS_GETPASS     0x05
#define TAC_PLUS_AUTHEN_STATUS_RESTART     0x06
#define TAC_PLUS_AUTHEN_STATUS_ERROR       0x07
#define TAC_PLUS_AUTHEN_STATUS_FOLLOW      0x21

// TACACS+ authentication REPLY packet flags
#define TAC_PLUS_REPLY_FLAG_NOECHO         0x01

// TACACS+ authentication CONTINUE packet flags
#define TAC_PLUS_CONTINUE_FLAG_ABORT       0x01

// TACACS+ authorization REQUEST packet methods
#define TAC_PLUS_AUTHEN_METH_NOT_SET       0x00
#define TAC_PLUS_AUTHEN_METH_NONE          0x01
#define TAC_PLUS_AUTHEN_METH_KRB5          0x02
#define TAC_PLUS_AUTHEN_METH_LINE          0x03
#define TAC_PLUS_AUTHEN_METH_ENABLE        0x04
#define TAC_PLUS_AUTHEN_METH_LOCAL         0x05
#define TAC_PLUS_AUTHEN_METH_TACACSPLUS    0x06
#define TAC_PLUS_AUTHEN_METH_GUEST         0x08
#define TAC_PLUS_AUTHEN_METH_RADIUS        0x10
#define TAC_PLUS_AUTHEN_METH_KRB4          0x11
#define TAC_PLUS_AUTHEN_METH_RCMD          0x20

// TACACS+ authorization REPLY packet stastus
#define TAC_PLUS_AUTHOR_STATUS_PASS_ADD    0x01
#define TAC_PLUS_AUTHOR_STATUS_PASS_REPL   0x02
#define TAC_PLUS_AUTHOR_STATUS_FAIL        0x10
#define TAC_PLUS_AUTHOR_STATUS_ERROR       0x11
#define TAC_PLUS_AUTHOR_STATUS_FOLLOW      0x21

#define TAC_PLUS_ACCT_FLAG_START           0x02
#define TAC_PLUS_ACCT_FLAG_STOP            0x04
#define TAC_PLUS_ACCT_FLAG_WATCHDOG        0x08

#define TAC_PLUS_ACCT_STATUS_SUCCESS       0x01
#define TAC_PLUS_ACCT_STATUS_ERROR         0x02
#define TAC_PLUS_ACCT_STATUS_FOLLOW        0x21

// TACACS+ Privilege Levels
#define TAC_PLUS_PRIV_LVL_MIN              0x00
#define TAC_PLUS_PRIV_LVL_USER             0x01
#define TAC_PLUS_PRIV_LVL_ROOT             0x0f
#define TAC_PLUS_PRIV_LVL_MAX              0x0f


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
TACPP_BEGIN_C_DECLS


TACPP_END_C_DECLS
#endif /* end of header */
