#
#   TACACS+ Proxy Server and Utilities
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


# AC_TACPLUS_DOCS
# ______________________________________________________________________________
AC_DEFUN_ONCE([AC_TACPLUS_DOCS],[dnl

   # prerequists
   AC_REQUIRE([AC_TACPLUS_DAEMON])
   AC_REQUIRE([AC_TACPLUS_CLIENT])
   AC_REQUIRE([AC_TACPLUS_LIBTACACS])

   if test "x${TACPLUS_TACPLUSPROXYD}" == "xyes";then
      TACPLUS_DOCS=yes
   elif test "x${TACPLUS_CLIENT}" == "xyes";then
      TACPLUS_DOCS=yes
   elif test "x${TACPLUS_LIBTACPROXY}" == "xyes";then
      TACPLUS_DOCS=yes
   else
      TACPLUS_DOCS=no
   fi

   if test "x${TACPLUS_DOCS}" == "xyes";then
      TACPLUS_DOCS_STATUS=install
   else
      TACPLUS_DOCS_STATUS=skip
   fi

   AM_CONDITIONAL([TACPLUS_DOCS], [test "x$TACPLUS_DOCS" = "xyes"])
])dnl


# AC_TACPLUS_LIBTACACS
# ______________________________________________________________________________
AC_DEFUN_ONCE([AC_TACPLUS_LIBTACACS],[dnl

   # prerequists
   AC_REQUIRE([AC_TACPLUS_DAEMON])
   AC_REQUIRE([AC_TACPLUS_CLIENT])

   enableval=""
   AC_ARG_ENABLE(
      libtacacs,
      [AS_HELP_STRING([--enable-libtacacs], [enable building TACACS+ protocol library])],
      [ ELIBTACACS=$enableval ],
      [ ELIBTACACS=$enableval ]
   )

   if test "x${TACPLUS_TACPLUSPROXYD}" == "xyes";then
      ELIBTACACS=yes
   elif test "x${TACPLUS_CLIENT}" == "xyes";then
      ELIBTACACS=yes
   fi

   if test "x${ELIBTACACS}" == "xyes";then
      TACPLUS_LIBTACACS=yes
      TACPLUS_LIBTACACS_STATUS=install
   else
      TACPLUS_LIBTACACS=no
      TACPLUS_LIBTACACS_STATUS=skip
   fi

   AM_CONDITIONAL([TACPLUS_LIBTACACS], [test "x$TACPLUS_LIBTACACS" = "xyes"])
])dnl


# AC_TACPLUS_MOD_FILES
# ______________________________________________________________________________
AC_DEFUN_ONCE([AC_TACPLUS_MOD_FILES],[dnl

   # prerequists
   AC_REQUIRE([AC_TACPLUS_DAEMON])

   enableval=""
   AC_ARG_ENABLE(
      mod-files,
      [AS_HELP_STRING([--enable-mod-files], [disable building mod_files])],
      [ EMODFILES=$enableval ],
      [ EMODFILES=$enableval ]
   )

   if test "x${TACPLUS_TACPLUSPROXYD}" == "xno";then
      EMODFILES=no
   fi

   if test "x${EMODFILES}" != "xno";then
      EMODFILES=yes
   fi
   TACPLUS_MOD_FILES=${EMODFILES}

   TACPLUS_MOD_FILES_STATUS="skip"
   if test "x${EMODFILES}" == "xyes";then
      TACPLUS_MOD_FILES_STATUS="install"
   fi

   AM_CONDITIONAL([TACPLUS_MOD_FILES], [test "x$TACPLUS_MOD_FILES" = "xyes"])
])dnl


# AC_TACPLUS_MOD_LDAP
# ______________________________________________________________________________
AC_DEFUN_ONCE([AC_TACPLUS_MOD_LDAP],[dnl

   # prerequists
   AC_REQUIRE([AC_TACPLUS_DAEMON])

   enableval=""
   AC_ARG_ENABLE(
      mod-ldap,
      [AS_HELP_STRING([--enable-mod-ldap], [disable building mod_ldap])],
      [ EMODLDAP=$enableval ],
      [ EMODLDAP=$enableval ]
   )

   if test "x${TACPLUS_TACPLUSPROXYD}" == "xno";then
      EMODLDAP=no
   fi

   if test "x${EMODLDAP}" != "xno";then
      EMODLDAP=yes
   fi
   TACPLUS_MOD_LDAP=${EMODLDAP}

   TACPLUS_MOD_LDAP_STATUS="skip"
   if test "x${EMODLDAP}" == "xyes";then
      TACPLUS_MOD_LDAP_STATUS="install"
   fi

   AM_CONDITIONAL([TACPLUS_MOD_LDAP], [test "x$TACPLUS_MOD_LDAP" = "xyes"])
])dnl


# AC_TACPLUS_MOD_PGSQL
# ______________________________________________________________________________
AC_DEFUN_ONCE([AC_TACPLUS_MOD_PGSQL],[dnl

   # prerequists
   AC_REQUIRE([AC_TACPLUS_DAEMON])

   enableval=""
   AC_ARG_ENABLE(
      mod-pgsql,
      [AS_HELP_STRING([--enable-mod-pgsql], [disable building mod_pgsql])],
      [ EMODPGSQL=$enableval ],
      [ EMODPGSQL=$enableval ]
   )
   EMODPGSQL=no # force disable of module until it is written

   if test "x${TACPLUS_TACPLUSPROXYD}" == "xno";then
      EMODPGSQL=no
   fi

   if test "x${EMODPGSQL}" != "xno";then
      EMODPGSQL=yes
   fi
   TACPLUS_MOD_PGSQL=${EMODPGSQL}

   TACPLUS_MOD_PGSQL_STATUS="skip"
   if test "x${EMODPGSQL}" == "xyes";then
      TACPLUS_MOD_PGSQL_STATUS="install"
   fi

   AM_CONDITIONAL([TACPLUS_MOD_PGSQL], [test "x$TACPLUS_MOD_PGSQL" = "xyes"])
])dnl


# AC_TACPLUS_MOD_RADIUS
# ______________________________________________________________________________
AC_DEFUN_ONCE([AC_TACPLUS_MOD_RADIUS],[dnl

   # prerequists
   AC_REQUIRE([AC_TACPLUS_DAEMON])

   enableval=""
   AC_ARG_ENABLE(
      mod-radius,
      [AS_HELP_STRING([--enable-mod-radius], [disable building mod_radius])],
      [ EMODRADIUS=$enableval ],
      [ EMODRADIUS=$enableval ]
   )

   if test "x${TACPLUS_TACPLUSPROXYD}" == "xno";then
      EMODRADIUS=no
   fi

   if test "x${EMODRADIUS}" != "xno";then
      EMODRADIUS=yes
   fi
   TACPLUS_MOD_RADIUS=${EMODRADIUS}

   TACPLUS_MOD_RADIUS_STATUS="skip"
   if test "x${EMODRADIUS}" == "xyes";then
      TACPLUS_MOD_RADIUS_STATUS="install"
   fi

   AM_CONDITIONAL([TACPLUS_MOD_RADIUS], [test "x$TACPLUS_MOD_RADIUS" = "xyes"])
])dnl


# AC_TACPLUS_MOD_SYSLOG
# ______________________________________________________________________________
AC_DEFUN_ONCE([AC_TACPLUS_MOD_SYSLOG],[dnl

   # prerequists
   AC_REQUIRE([AC_TACPLUS_DAEMON])

   enableval=""
   AC_ARG_ENABLE(
      mod-syslog,
      [AS_HELP_STRING([--enable-mod-syslog], [disable building mod_syslog])],
      [ EMODSYSLOG=$enableval ],
      [ EMODSYSLOG=$enableval ]
   )

   if test "x${TACPLUS_TACPLUSPROXYD}" == "xno";then
      EMODSYSLOG=no
   fi

   if test "x${EMODSYSLOG}" != "xno";then
      EMODSYSLOG=yes
   fi
   TACPLUS_MOD_SYSLOG=${EMODSYSLOG}

   TACPLUS_MOD_SYSLOG_STATUS="skip"
   if test "x${EMODSYSLOG}" == "xyes";then
      TACPLUS_MOD_SYSLOG_STATUS="install"
   fi

   AM_CONDITIONAL([TACPLUS_MOD_SYSLOG], [test "x$TACPLUS_MOD_SYSLOG" = "xyes"])
])dnl


# AC_TACPLUS_CLIENT
# ______________________________________________________________________________
AC_DEFUN_ONCE([AC_TACPLUS_CLIENT],[dnl

   enableval=""
   AC_ARG_ENABLE(
      client,
      [AS_HELP_STRING([--enable-client], [enable building TACACS+ client utilities])],
      [ ECLIENT=$enableval ],
      [ ECLIENT=$enableval ]
   )

   if test "x${ECLIENT}" != "xyes";then
      ECLIENT=no
   fi
   TACPLUS_CLIENT=${ETACPROXYD}

   TACPLUS_CLIENT_STATUS="skip"
   if test "x${ECLIENT}" == "xyes";then
      TACPLUS_CLIENT_STATUS="install"
      TACPLUS_CLIENT="yes"
   fi

   AM_CONDITIONAL([TACPLUS_CLIENT], [test "x$TACPLUS_CLIENT" = "xyes"])
])dnl


# AC_TACPLUS_DAEMON
# ______________________________________________________________________________
AC_DEFUN_ONCE([AC_TACPLUS_DAEMON],[dnl

   enableval=""
   AC_ARG_ENABLE(
      daemon,
      [AS_HELP_STRING([--disable-daemon], [disable building TACACS+ proxy daemon and utlities])],
      [ EDAEMON=$enableval ],
      [ EDAEMON=$enableval ]
   )

   if test "x${EDAEMON}" != "xno";then
      EDAEMON=yes
   fi
   TACPLUS_DAEMON=${EDAEMON}

   TACPLUS_DAEMON_STATUS="skip"
   if test "x${EDAEMON}" == "xyes";then
      TACPLUS_DAEMON_STATUS="install"
   fi

   AM_CONDITIONAL([TACPLUS_DAEMON], [test "x$TACPLUS_DAEMON" = "xyes"])
])dnl


# end of M4 file
