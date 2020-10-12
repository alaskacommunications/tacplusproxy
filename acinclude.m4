#
#   TACACS+ Proxy and Tools
#   Copyright (c) 2020 Alaska Communications
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
#   acinclude.m4 - custom m4 macros used by configure.ac
#


# AC_TACPROXY_LTLIBTACPROXY_LA
# ______________________________________________________________________________
AC_DEFUN_ONCE([AC_TACPROXY_LTLIBTACPROXY_LA],[dnl

   # prerequists
   AC_REQUIRE([AC_TACPROXY_TACPROXYD])

   enableval=""
   AC_ARG_ENABLE(
      libtacproxy,
      [AS_HELP_STRING([--enable-libtacproxy], [enable building libraries])],
      [ ELIBTACPROXY=$enableval ],
      [ ELIBTACPROXY=$enableval ]
   )

   if test "x${TACPROXY_TACPROXYD}" == "xyes";then
      ELIBTACPROXY=yes
   fi

   TACPROXY_LTLIBTACPROXY_LA_STATUS="install"
   if test "x${ELIBTACPROXY}" != "xyes";then
      ELIBTACPROXY=no
      TACPROXY_LTLIBTACPROXY_LA_STATUS="skip"
   fi
   TACPROXY_LTLIBTACPROXY_LA=${ELIBTACPROXY}

   AM_CONDITIONAL([TACPROXY_LTLIBTACPROXY_LA], [test "x$TACPROXY_LTLIBTACPROXY_LA" = "xyes"])
])dnl


# AC_TACPROXY_LIBTACPROXY_A
# ______________________________________________________________________________
AC_DEFUN_ONCE([AC_TACPROXY_LIBTACPROXY_A],[dnl

   # prerequists
   AC_REQUIRE([AC_TACPROXY_LTLIBTACPROXY_LA])
   AC_REQUIRE([AC_TACPROXY_TACCLI])

   if test "x${TACPROXY_LTLIBTACPROXY_LA}" == "xyes";then
      TACPROXY_LIBTACPROXY_A=yes
      TACPROXY_LIBTACPROXY_A_STATUS=install
   elif test "x${TACPROXY_TACCLI}" == "xyes";then
      TACPROXY_LIBTACPROXY_A=yes
      TACPROXY_LIBTACPROXY_A_STATUS=build
   else
      TACPROXY_LIBTACPROXY_A=no
      TACPROXY_LIBTACPROXY_A_STATUS=skip
   fi

   AM_CONDITIONAL([TACPROXY_LIBTACPROXY_A], [test "x$TACPROXY_LIBTACPROXY_A" = "xyes"])
])dnl


# AC_TACPROXY_MOD_FILES
# ______________________________________________________________________________
AC_DEFUN_ONCE([AC_TACPROXY_MOD_FILES],[dnl

   # prerequists
   AC_REQUIRE([AC_TACPROXY_TACPROXYD])

   enableval=""
   AC_ARG_ENABLE(
      mod-files,
      [AS_HELP_STRING([--enable-mod-files], [disable building mod_files])],
      [ EMODFILES=$enableval ],
      [ EMODFILES=$enableval ]
   )

   if test "x${TACPROXY_TACPROXYD}" == "xno";then
      EMODFILES=no
   fi

   if test "x${EMODFILES}" != "xno";then
      EMODFILES=yes
   fi
   TACPROXY_MOD_FILES=${EMODFILES}

   TACPROXY_MOD_FILES_STATUS="skip"
   if test "x${EMODFILES}" == "xyes";then
      TACPROXY_MOD_FILES_STATUS="install"
   fi

   AM_CONDITIONAL([TACPROXY_MOD_FILES], [test "x$TACPROXY_MOD_FILES" = "xyes"])
])dnl


# AC_TACPROXY_MOD_LDAP
# ______________________________________________________________________________
AC_DEFUN_ONCE([AC_TACPROXY_MOD_LDAP],[dnl

   # prerequists
   AC_REQUIRE([AC_TACPROXY_TACPROXYD])

   enableval=""
   AC_ARG_ENABLE(
      mod-ldap,
      [AS_HELP_STRING([--enable-mod-ldap], [disable building mod_ldap])],
      [ EMODLDAP=$enableval ],
      [ EMODLDAP=$enableval ]
   )

   if test "x${TACPROXY_TACPROXYD}" == "xno";then
      EMODLDAP=no
   fi

   if test "x${EMODLDAP}" != "xno";then
      EMODLDAP=yes
   fi
   TACPROXY_MOD_LDAP=${EMODLDAP}

   TACPROXY_MOD_LDAP_STATUS="skip"
   if test "x${EMODLDAP}" == "xyes";then
      TACPROXY_MOD_LDAP_STATUS="install"
   fi

   AM_CONDITIONAL([TACPROXY_MOD_LDAP], [test "x$TACPROXY_MOD_LDAP" = "xyes"])
])dnl


# AC_TACPROXY_MOD_PGSQL
# ______________________________________________________________________________
AC_DEFUN_ONCE([AC_TACPROXY_MOD_PGSQL],[dnl

   # prerequists
   AC_REQUIRE([AC_TACPROXY_TACPROXYD])

   enableval=""
   AC_ARG_ENABLE(
      mod-pgsql,
      [AS_HELP_STRING([--enable-mod-pgsql], [disable building mod_pgsql])],
      [ EMODPGSQL=$enableval ],
      [ EMODPGSQL=$enableval ]
   )
   EMODPGSQL=no # force disable of module until it is written

   if test "x${TACPROXY_TACPROXYD}" == "xno";then
      EMODPGSQL=no
   fi

   if test "x${EMODPGSQL}" != "xno";then
      EMODPGSQL=yes
   fi
   TACPROXY_MOD_PGSQL=${EMODPGSQL}

   TACPROXY_MOD_PGSQL_STATUS="skip"
   if test "x${EMODPGSQL}" == "xyes";then
      TACPROXY_MOD_PGSQL_STATUS="install"
   fi

   AM_CONDITIONAL([TACPROXY_MOD_PGSQL], [test "x$TACPROXY_MOD_PGSQL" = "xyes"])
])dnl


# AC_TACPROXY_MOD_RADIUS
# ______________________________________________________________________________
AC_DEFUN_ONCE([AC_TACPROXY_MOD_RADIUS],[dnl

   # prerequists
   AC_REQUIRE([AC_TACPROXY_TACPROXYD])

   enableval=""
   AC_ARG_ENABLE(
      mod-radius,
      [AS_HELP_STRING([--enable-mod-radius], [disable building mod_radius])],
      [ EMODRADIUS=$enableval ],
      [ EMODRADIUS=$enableval ]
   )

   if test "x${TACPROXY_TACPROXYD}" == "xno";then
      EMODRADIUS=no
   fi

   if test "x${EMODRADIUS}" != "xno";then
      EMODRADIUS=yes
   fi
   TACPROXY_MOD_RADIUS=${EMODRADIUS}

   TACPROXY_MOD_RADIUS_STATUS="skip"
   if test "x${EMODRADIUS}" == "xyes";then
      TACPROXY_MOD_RADIUS_STATUS="install"
   fi

   AM_CONDITIONAL([TACPROXY_MOD_RADIUS], [test "x$TACPROXY_MOD_RADIUS" = "xyes"])
])dnl


# AC_TACPROXY_MOD_SYSLOG
# ______________________________________________________________________________
AC_DEFUN_ONCE([AC_TACPROXY_MOD_SYSLOG],[dnl

   # prerequists
   AC_REQUIRE([AC_TACPROXY_TACPROXYD])

   enableval=""
   AC_ARG_ENABLE(
      mod-syslog,
      [AS_HELP_STRING([--enable-mod-syslog], [disable building mod_syslog])],
      [ EMODSYSLOG=$enableval ],
      [ EMODSYSLOG=$enableval ]
   )

   if test "x${TACPROXY_TACPROXYD}" == "xno";then
      EMODSYSLOG=no
   fi

   if test "x${EMODSYSLOG}" != "xno";then
      EMODSYSLOG=yes
   fi
   TACPROXY_MOD_SYSLOG=${EMODSYSLOG}

   TACPROXY_MOD_SYSLOG_STATUS="skip"
   if test "x${EMODSYSLOG}" == "xyes";then
      TACPROXY_MOD_SYSLOG_STATUS="install"
   fi

   AM_CONDITIONAL([TACPROXY_MOD_SYSLOG], [test "x$TACPROXY_MOD_SYSLOG" = "xyes"])
])dnl


# AC_TACPROXY_TACCLI
# ______________________________________________________________________________
AC_DEFUN_ONCE([AC_TACPROXY_TACCLI],[dnl

   enableval=""
   AC_ARG_ENABLE(
      tac-cli,
      [AS_HELP_STRING([--enable-tac-cli], [enable building TACACS+ client utility])],
      [ ETACCLI=$enableval ],
      [ ETACCLI=$enableval ]
   )

   if test "x${ETACCLI}" != "xyes";then
      ETACCLI=no
   fi
   TACPROXY_TACCLI=${ETACPROXYD}

   TACPROXY_TACCLI_STATUS="skip"
   if test "x${ETACCLI}" == "xyes";then
      TACPROXY_TACCLI_STATUS="install"
      TACPROXY_TACCLI="yes"
   fi

   AM_CONDITIONAL([TACPROXY_TACCLI], [test "x$TACPROXY_TACCLI" = "xyes"])
])dnl


# AC_TACPROXY_TACPROXYD
# ______________________________________________________________________________
AC_DEFUN_ONCE([AC_TACPROXY_TACPROXYD],[dnl

   enableval=""
   AC_ARG_ENABLE(
      tacproxyd,
      [AS_HELP_STRING([--disable-tacproxyd], [disable building TACACS+ proxy daemon])],
      [ ETACPROXYD=$enableval ],
      [ ETACPROXYD=$enableval ]
   )

   if test "x${ETACPROXYD}" != "xno";then
      ETACPROXYD=yes
   fi
   TACPROXY_TACPROXYD=${ETACPROXYD}

   TACPROXY_TACPROXYD_STATUS="skip"
   if test "x${ETACPROXYD}" == "xyes";then
      TACPROXY_TACPROXYD_STATUS="install"
      TACPROXY_LIBTACPROXY="yes"
   fi

   AM_CONDITIONAL([TACPROXY_TACPROXYD], [test "x$TACPROXY_TACPROXYD" = "xyes"])
])dnl


# end of M4 file
