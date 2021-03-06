#
#   TACACS+ Proxy Server and Utilities
#   Copyright (c) 2020 David M. Syzdek <david@syzdek.net>
#   All rights reserved.
#
#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted provided that the following conditions are
#   met:
#
#      1. Redistributions of source code must retain the above copyright
#         notice, this list of conditions and the following disclaimer.
#
#      2. Redistributions in binary form must reproduce the above copyright
#         notice, this list of conditions and the following disclaimer in the
#         documentation and/or other materials provided with the distribution.
#
#      3. Neither the name of the copyright holder nor the names of its
#         contributors may be used to endorse or promote products derived from
#         this software without specific prior written permission.
#
#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
#   IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#   PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
#   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
#   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
#   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
#   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
#   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#   configure.ac - automate compiling on a unix platform
#

# +-=-=-=-=-=-=-=-=-+
# |                 |
# |  Autoconf Init  |
# |                 |
# +-=-=-=-=-=-=-=-=-+

AC_PREREQ(2.65)

AC_COPYRIGHT([Copyright (C) 2020 David M. Syzdek <david@syzdek.net>.])
AC_REVISION(0.1)
AC_INIT([TACACS+ Proxy Server and Utilities],[0.0],[david@syzdek.net],[tacplusproxy])

AC_SUBST([RELEASE_MONTH],["August 2020"])

PACKAGE_COPYRIGHT="Copyright (C) 2020 David M. Syzdek <david@syzdek.net>."
AC_DEFINE_UNQUOTED(PACKAGE_COPYRIGHT, ["${PACKAGE_COPYRIGHT}"], [Copyright notice.])
AC_SUBST([PACKAGE_COPYRIGHT], [${PACKAGE_COPYRIGHT}])


# directory locations
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_SRCDIR([build-aux/git-tar-name.txt])
#AC_CONFIG_LIBOBJ_DIR(compat)
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# determines host type
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

# configures for automake
AM_INIT_AUTOMAKE(gnu std-options subdir-objects foreign)

# Compilers
AC_PROG_CC
#AC_PROG_OBJC
AC_PROG_CXX
AM_PROG_CC_C_O
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_USE_SYSTEM_EXTENSIONS # replaces AC_AIX AC_GNU_SOURCE AC_MINIX
AC_C_BIGENDIAN
AC_C_INLINE

# Version Info:
#    Current    -- the current version number of this API
#    Revision   -- the revision of the implementation of the API version
#    Age        -- How many seqential past API versions is supported by
#                  this implementation
# Format => Current:Revision:Age
# Convenience macro:
#    AC_BINDLE_LIBTOOL_VERSION_INFO(current, revision, age)
AC_BINDLE_LIBTOOL_VERSION_INFO(0, 0, 0)

# binary locations
AC_PATH_PROG([SHELL],   sh bash,        [AC_MSG_ERROR([missing "sh"])], [$PATH])
AC_CHECK_TOOLS(AR,      ar gar,         [AC_MSG_ERROR([missing binutil "ar"])])
AC_CHECK_TOOLS(LD,      ld gld,         [AC_MSG_ERROR([missing binutil "ld"])])
AC_CHECK_TOOLS(NM,      nm gnm,         [AC_MSG_ERROR([missing binutil "nm"])])
AC_CHECK_TOOLS(RANLIB,  ranlib granlib, [AC_MSG_ERROR([missing binutil "ranlib"])])
AC_CHECK_TOOLS(STRIP,   strip gstrip,   [AC_MSG_ERROR([missing binutil "strip"])])

# shell programs
AC_PROG_AWK
AC_PROG_EGREP
AC_PROG_FGREP
AM_PROG_LEX
AC_PROG_YACC
AC_PROG_LN_S
AC_PROG_MKDIR_P
AC_PROG_SED

# GNU Libtool Support
LT_INIT(dlopen disable-fast-install win32-dll)

# check for common functions
AC_FUNC_ALLOCA
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_STRERROR_R

# Type checks
AC_TYPE_INT8_T
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UID_T
AC_TYPE_UINT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T

# check for required functions
AC_CHECK_FUNCS([bzero],          [], [AC_MSG_ERROR([missing required functions])])
AC_CHECK_FUNCS([getpass],        [], [AC_MSG_ERROR([missing required functions])])
AC_CHECK_FUNCS([gettimeofday],   [], [AC_MSG_ERROR([missing required functions])])
AC_CHECK_FUNCS([memset],         [], [AC_MSG_ERROR([missing required functions])])
AC_CHECK_FUNCS([regcomp],        [], [AC_MSG_ERROR([missing required functions])])
AC_CHECK_FUNCS([setlocale],      [], [AC_MSG_ERROR([missing required functions])])
AC_CHECK_FUNCS([socket],         [], [AC_MSG_ERROR([missing required functions])])
AC_CHECK_FUNCS([strcasecmp],     [], [AC_MSG_ERROR([missing required functions])])
AC_CHECK_FUNCS([strchr],         [], [AC_MSG_ERROR([missing required functions])])
AC_CHECK_FUNCS([strdup],         [], [AC_MSG_ERROR([missing required functions])])
AC_CHECK_FUNCS([strerror],       [], [AC_MSG_ERROR([missing required functions])])
AC_CHECK_FUNCS([strncasecmp],    [], [AC_MSG_ERROR([missing required functions])])
AC_CHECK_FUNCS([strtol],         [], [AC_MSG_ERROR([missing required functions])])
AC_CHECK_FUNCS([strtoul],        [], [AC_MSG_ERROR([missing required functions])])
AC_CHECK_FUNCS([strtoull],       [], [AC_MSG_ERROR([missing required functions])])

# check for required libraries
AC_SEARCH_LIBS([getopt_long],          c gnugetopt,,AC_MSG_ERROR([missing required function]))
AC_SEARCH_LIBS([socket],               socket,,AC_MSG_ERROR([missing required function]), [-lresolv])

# check for headers
AC_CHECK_HEADER_STDBOOL
AC_CHECK_HEADERS([arpa/inet.h],,       [AC_MSG_ERROR([missing required header])])
AC_CHECK_HEADERS([fcntl.h],,           [AC_MSG_ERROR([missing required header])])
AC_CHECK_HEADERS([limits.h],,          [AC_MSG_ERROR([missing required header])])
AC_CHECK_HEADERS([termios.h],,         [AC_MSG_ERROR([missing required header])])
AC_CHECK_HEADERS([getopt.h],,          [AC_MSG_ERROR([missing required header])])
AC_CHECK_HEADERS([signal.h],,          [AC_MSG_ERROR([missing required header])])
AC_CHECK_HEADERS([sys/socket.h],,      [AC_MSG_ERROR([missing required header])])
AC_CHECK_HEADERS([libintl.h])
AC_CHECK_HEADERS([malloc.h])
AC_CHECK_HEADERS([sgtty.h])
AC_CHECK_HEADERS([stddef.h])

# initiates bindle tools macros
AC_BINDLE(contrib/bindletools)

# determine PACKAGE_VERSION via Git
AC_BINDLE_GIT_PACKAGE_VERSION([contrib/bindletools/build-aux/git-package-version.sh])

# custom configure options
AC_BINDLE_ENABLE_WARNINGS([-Wno-padded -Wno-unknown-pragmas], [-Wpadded])
AC_TACPLUS_CLIENT
AC_TACPLUS_DAEMON
AC_TACPLUS_MOD_FILES
AC_TACPLUS_MOD_LDAP
AC_TACPLUS_MOD_PGSQL
AC_TACPLUS_MOD_RADIUS
AC_TACPLUS_MOD_SYSLOG
AC_TACPLUS_LIBTACACS
AC_TACPLUS_DOCS

# Creates outputs
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

# Show local config
AC_MSG_NOTICE([ ])
AC_MSG_NOTICE([   TACACS+ Proxy Server and Utilities ($PACKAGE_VERSION)])
AC_MSG_NOTICE([ ])
AC_MSG_NOTICE([   Use Warnings                  $USE_WARNINGS])
AC_MSG_NOTICE([   Use Strict Warnings           $USE_STRICTWARNINGS])
AC_MSG_NOTICE([ ])
AC_MSG_NOTICE([   Libraries:])
AC_MSG_NOTICE([      libtacacs.a                $TACPLUS_LIBTACACS_STATUS])
AC_MSG_NOTICE([      libtacacs.la               $TACPLUS_LIBTACACS_STATUS])
AC_MSG_NOTICE([ ])
AC_MSG_NOTICE([   Daemon and Utilities:])
AC_MSG_NOTICE([      tacplusd                   $TACPLUS_DAEMON_STATUS])
AC_MSG_NOTICE([      tacplus                    $TACPLUS_CLIENT_STATUS])
AC_MSG_NOTICE([ ])
AC_MSG_NOTICE([   Daemon Modules:])
AC_MSG_NOTICE([      mod_files                  $TACPLUS_MOD_FILES_STATUS])
AC_MSG_NOTICE([      mod_ldap                   $TACPLUS_MOD_LDAP_STATUS])
AC_MSG_NOTICE([      mod_pgsql                  $TACPLUS_MOD_PGSQL_STATUS])
AC_MSG_NOTICE([      mod_radius                 $TACPLUS_MOD_RADIUS_STATUS])
AC_MSG_NOTICE([      mod_syslog                 $TACPLUS_MOD_SYSLOG_STATUS])
AC_MSG_NOTICE([ ])
AC_MSG_NOTICE([   Documentation:])
AC_MSG_NOTICE([      RFC 8907                   $TACPLUS_DOCS_STATUS])
AC_MSG_NOTICE([ ])
AC_MSG_NOTICE([   Please send suggestions to:   $PACKAGE_BUGREPORT])
AC_MSG_NOTICE([ ])
AC_MSG_NOTICE([   run 'make all'])
AC_MSG_NOTICE([ ])

# end of configure.ac
