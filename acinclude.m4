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

   if test "x${TACPLUS_DAEMON}" == "xyes";then
      TACPLUS_DOCS=yes
   elif test "x${TACPLUS_CLIENT}" == "xyes";then
      TACPLUS_DOCS=yes
   elif test "x${TACPLUS_LIBTACACS}" == "xyes";then
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

   # processes argument
   if test "x${ELIBTACACS}" == "xno";then
      if test "x${TACPLUS_DAEMON}" == "xyes";then
         AC_MSG_ERROR([--enable-daemon requires --enable-libtacacs])
      elif test "x${TACPLUS_CLIENT}" == "xyes";then
         AC_MSG_ERROR([--enable-client requires --enable-libtacacs])
      fi
      TACPLUS_LIBTACACS=no
   elif test "x${ELIBTACACS}" == "xyes";then
      TACPLUS_LIBTACACS=yes
   elif test "x${TACPLUS_DAEMON}" == "xyes";then
      TACPLUS_LIBTACACS=yes
   elif test "x${TACPLUS_CLIENT}" == "xyes";then
      TACPLUS_LIBTACACS=yes
   else
      TACPLUS_LIBTACACS=no
   fi

   # determines status message
   if test "x${TACPLUS_LIBTACACS}" == "xyes";then
      TACPLUS_LIBTACACS_STATUS=install
   else
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

   # processes argument
   if test "x${EMODFILES}" == "xno";then
      TACPLUS_MOD_FILES=no
   elif test "x${TACPLUS_DAEMON}" == "xno";then
      if test "x${EMODFILES}" == "xyes";then
         AC_MSG_ERROR([--enable-mod-files requires --enable-daemon])
      fi
      TACPLUS_MOD_FILES=no
   else
      TACPLUS_MOD_FILES=yes
   fi

   # determines status message
   if test "x${TACPLUS_MOD_FILES}" == "xyes";then
      TACPLUS_MOD_FILES_STATUS="install"
   else
      TACPLUS_MOD_FILES_STATUS="skip"
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

   # processes argument
   if test "x${EMODLDAP}" == "xno";then
      TACPLUS_MOD_LDAP=no
   elif test "x${TACPLUS_DAEMON}" == "xno";then
      if test "x${EMODLDAP}" == "xyes";then
         AC_MSG_ERROR([--enable-mod-ldap requires --enable-daemon])
      fi
      TACPLUS_MOD_LDAP=no
   else
      HAVE_LDAP=yes
      AC_CHECK_HEADERS([ldap.h],,            [HAVE_LDAP=no])
      AC_CHECK_TYPES([LDAPURLDesc],,         [HAVE_LDAP=no],[#include <ldap.h>])
      AC_SEARCH_LIBS([ldap_dn2str],          ldap,,[HAVE_LDAP=no], [-llber])
      AC_SEARCH_LIBS([ldap_dnfree],          ldap,,[HAVE_LDAP=no], [-llber])
      AC_SEARCH_LIBS([ldap_explode_dn],      ldap,,[HAVE_LDAP=no], [-llber])
      AC_SEARCH_LIBS([ldap_first_entry],     ldap,,[HAVE_LDAP=no], [-llber])
      AC_SEARCH_LIBS([ldap_free_urldesc],    ldap,,[HAVE_LDAP=no], [-llber])
      AC_SEARCH_LIBS([ldap_get_dn],          ldap,,[HAVE_LDAP=no], [-llber])
      AC_SEARCH_LIBS([ldap_initialize],      ldap,,[HAVE_LDAP=no], [-llber])
      AC_SEARCH_LIBS([ldap_result],          ldap,,[HAVE_LDAP=no], [-llber])
      AC_SEARCH_LIBS([ldap_sasl_bind_s],     ldap,,[HAVE_LDAP=no], [-llber])
      AC_SEARCH_LIBS([ldap_search_ext],      ldap,,[HAVE_LDAP=no], [-llber])
      AC_SEARCH_LIBS([ldap_set_option],      ldap,,[HAVE_LDAP=no], [-llber])
      AC_SEARCH_LIBS([ldap_str2dn],          ldap,,[HAVE_LDAP=no], [-llber])
      AC_SEARCH_LIBS([ldap_unbind_ext_s],    ldap,,[HAVE_LDAP=no], [-llber])
      AC_SEARCH_LIBS([ldap_url_parse],       ldap,,[HAVE_LDAP=no], [-llber])
      AC_SEARCH_LIBS([ldap_value_free],      ldap,,[HAVE_LDAP=no], [-llber])
      if test "x${HAVE_LDAP}" == "xno";then
         if test "x${EMODLDAP}" == "xyes";then
            AC_MSG_ERROR([mod_ldap requires OpenLDAP])
         else
            AC_MSG_NOTICE([OpenLDAP not found or unusable, skipping mod_ldap])
         fi
      fi
      TACPLUS_MOD_LDAP=${HAVE_LDAP}
   fi

   # determines status message
   if test "x${TACPLUS_MOD_LDAP}" == "xyes";then
      TACPLUS_MOD_LDAP_STATUS="install"
   else
      TACPLUS_MOD_LDAP_STATUS="skip"
   fi

   AM_CONDITIONAL([TACPLUS_MOD_LDAP], [test "x$TACPLUS_MOD_LDAP" = "xyes"])
])dnl


# AC_TACPLUS_MOD_PGSQL
# ______________________________________________________________________________
AC_DEFUN_ONCE([AC_TACPLUS_MOD_PGSQL],[dnl

   # prerequists
   AC_REQUIRE([AC_TACPLUS_DAEMON])

   enableval=""
   #AC_ARG_ENABLE(
   #   mod-pgsql,
   #   [AS_HELP_STRING([--enable-mod-pgsql], [disable building mod_pgsql])],
   #   [ EMODPGSQL=$enableval ],
   #   [ EMODPGSQL=$enableval ]
   #)

   # processes argument
   if test "x${EMODPGSQL}" == "xno";then
      TACPLUS_MOD_PGSQL=no
   elif test "x${TACPLUS_DAEMON}" == "xno";then
      if test "x${EMODPGSQL}" == "xyes";then
         AC_MSG_ERROR([--enable-mod-pgsql requires --enable-daemon])
      fi
   else
      TACPLUS_MOD_PGSQL=yes
   fi

   # determines status message
   if test "x${TACPLUS_MOD_PGSQL}" == "xyes";then
      TACPLUS_MOD_PGSQL_STATUS="install"
   else
      TACPLUS_MOD_PGSQL_STATUS="skip"
   fi

   # force disable of module until it is written
   TACPLUS_MOD_PGSQL=no
   TACPLUS_MOD_PGSQL_STATUS=n/a

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

   # processes argument
   if test "x${EMODRADIUS}" == "xno";then
      TACPLUS_MOD_RADIUS=no
   elif test "x${TACPLUS_DAEMON}" == "xno";then
      if test "x${EMODRADIUS}" == "xyes";then
         AC_MSG_ERROR([--enable-mod-radius requires --enable-daemon])
      fi
      TACPLUS_MOD_RADIUS=no
   else
      TACPLUS_MOD_RADIUS=yes
   fi

   # determines status message
   if test "x${TACPLUS_MOD_RADIUS}" == "xyes";then
      TACPLUS_MOD_RADIUS_STATUS="install"
   else
      TACPLUS_MOD_RADIUS_STATUS="skip"
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

   # processes argument
   if test "x${EMODSYSLOG}" == "xno";then
      TACPLUS_MOD_SYSLOG=no
   elif test "x${TACPLUS_DAEMON}" == "xno";then
      if test "x${EMODSYSLOG}" == "xyes";then
         AC_MSG_ERROR([--enable-mod-syslog requires --enable-daemon])
      fi
      TACPLUS_MOD_SYSLOG=no
   else
      TACPLUS_MOD_SYSLOG=yes
   fi

   # determines status message
   if test "x${TACPLUS_MOD_SYSLOG}" == "xyes";then
      TACPLUS_MOD_SYSLOG_STATUS="install"
   else
      TACPLUS_MOD_SYSLOG_STATUS="skip"
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
      TACPLUS_CLIENT_STATUS="skip"
      TACPLUS_CLIENT="no"
   else
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
      TACPLUS_DAEMON_STATUS="install"
      TACPLUS_DAEMON=yes
   else
      TACPLUS_DAEMON_STATUS="skip"
      TACPLUS_DAEMON=no
   fi

   AM_CONDITIONAL([TACPLUS_DAEMON], [test "x$TACPLUS_DAEMON" = "xyes"])
])dnl


# end of M4 file
