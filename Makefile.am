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
#   @configure_input@
#
#   Makefile.am - automate compiling on a unix platform
#

# Sub directories
SUBDIRS					= $(subdirs)
DIST_SUBDIRS				= $(subdirs)


# directory locations
doxygendir				= $(docdir)/doxygen


# GNU make options
V					= 0


# Global flags
AM_LIBS					=
AM_LDFLAGS				=
AM_CFLAGS				= -O2 $(CFLAGS_WARNINGS)
AM_CXXFLAGS				= -O2 @AM_CXXFLAGS@
AM_OBJCFLAGS				= -O2 @AM_OBJCFLAGS@
AM_CPPFLAGS				= -O2 \
					  -UPMARK \
					  -DHAVE_CONFIG_H=1 \
					  -I$(top_builddir)/include \
					  -I$(top_srcdir)/include \
					  -DSYSCONFDIR=\"$(sysconfdir)\"
ACLOCAL_AMFLAGS				= -I m4 -W all -W error
AM_MAKEINFOFLAGS                        = --no-split
AM_DISTCHECK_CONFIGURE_FLAGS		= --enable-strictwarnings \
					  --enable-tac-cli \
					  CFLAGS="$(CFLAGS)" \
					  CPPFLAGS="$(CPPFLAGS)" \
					  LDFLAGS="$(LDFLAGS)"
AM_YFLAGS				= -d
DEFS					=
LDADD					=


# automake targets
bin_PROGRAMS				=
check_PROGRAMS				=
doc_DATA				=
doxygen_DATA				=
noinst_DATA				=
EXTRA_PROGRAMS				=
include_HEADERS				=
info_TEXINFOS				=
lib_LIBRARIES				=
lib_LTLIBRARIES				=
pkglib_LTLIBRARIES			=
noinst_LTLIBRARIES			=
EXTRA_LIBRARIES				=
EXTRA_LTLIBRARIES			=
man_MANS				=
noinst_HEADERS				= include/tacproxy.h
noinst_PROGRAMS				=
noinst_LIBRARIES			=
if TACPROXY_LIBTACPROXY
   lib_LTLIBRARIES			+= lib/libtacproxy.la
   include_HEADERS			+= include/tacproxy.h
endif
if TACPROXY_MOD_FILES
   pkglib_LTLIBRARIES			+= lib/mod_files.la
endif
if TACPROXY_MOD_LDAP
   pkglib_LTLIBRARIES			+= lib/mod_ldap.la
endif
if TACPROXY_MOD_RADIUS
   pkglib_LTLIBRARIES			+= lib/mod_radius.la
endif
if TACPROXY_MOD_SYSLOG
   pkglib_LTLIBRARIES			+= lib/mod_syslog.la
endif
if TACPROXY_TACCLI
   bin_PROGRAMS				+= src/tac-cli
#   man_MANS				+= doc/tac-cli.1
endif
if TACPROXY_TACPROXYD
   bin_PROGRAMS				+= src/tac-proxyd
#   man_MANS				+= doc/tac-proxyd.1
endif


# lists
AM_INSTALLCHECK_STD_OPTIONS_EXEMPT	=
BUILT_SOURCES				=
TESTS					=
XFAIL_TESTS				=
EXTRA_MANS				=
EXTRA_DIST				= $(noinst_HEADERS) \
					  ChangeLog.md \
					  COPYING.md \
					  NEWS.md \
					  README.md \
					  TODO.md \
					  lib/libtacproxy/libtacproxy.sym
CLEANFILES				= \
					  $(builddir)/a.out   $(srcdir)/a.out \
					  $(builddir)/*/a.out $(srcdir)/*/a.out \
					  config.h.in~ $(srcdir)/config.h.in~ \
					  $(man_MANS) \
					  $(pkgdata_DATA) \
					  $(bin_SCRIPTS) \
					  $(sbin_SCRIPTS) \
					  @PACKAGE_TARNAME@-*.tar.* \
					  @PACKAGE_TARNAME@-*.txz \
					  @PACKAGE_TARNAME@-*.zip


### macros for lib/libtacproxy.la
lib_libtacproxy_la_DEPENDENCIES		= Makefile lib/libtacproxy/libtacproxy.sym
lib_libtacproxy_la_CPPFLAGS		= $(AM_CPPFLAGS) -I$(srcdir)/lib/libtacproxy
lib_libtacproxy_la_CFLAGS		= $(AM_CFLAGS)
lib_libtacproxy_la_LDFLAGS		= -rpath'$(libdir)' \
					  -version-info $(LIB_VERSION_INFO) \
					  $(AM_LDFLAGS) \
					  -export-symbols $(srcdir)/lib/libtacproxy/libtacproxy.sym
lib_libtacproxy_la_LIBADD		= $(AM_LIBS)
lib_libtacproxy_la_SOURCES		= $(noinst_HEADERS) \
					  lib/libtacproxy/test.c


### macros for lib/mod_files.la
lib_mod_files_la_DEPENDENCIES		= Makefile lib/libtacproxy.la
lib_mod_files_la_CPPFLAGS		= $(AM_CPPFLAGS) -I$(srcdir)/lib/mod_files
lib_mod_files_la_CFLAGS			= $(AM_CFLAGS)
lib_mod_files_la_LDFLAGS		= -module \
					  -avoid-version \
					  -export-dynamic \
					  -shared \
					  $(AM_LDFLAGS)
lib_mod_files_la_LIBADD			= $(AM_LIBS)
lib_mod_files_la_SOURCES		= $(noinst_HEADERS) \
					  lib/libtacproxy/test.c


### macros for lib/mod_ldap.la
lib_mod_ldap_la_DEPENDENCIES		= Makefile lib/libtacproxy.la
lib_mod_ldap_la_CPPFLAGS		= $(AM_CPPFLAGS) -I$(srcdir)/lib/mod_ldap
lib_mod_ldap_la_CFLAGS			= $(AM_CFLAGS)
lib_mod_ldap_la_LDFLAGS			= -module \
					  -avoid-version \
					  -export-dynamic \
					  -shared \
					  $(AM_LDFLAGS)
lib_mod_ldap_la_LIBADD			= $(AM_LIBS)
lib_mod_ldap_la_SOURCES			= $(noinst_HEADERS) \
					  lib/libtacproxy/test.c


### macros for lib/mod_radius.la
lib_mod_radius_la_DEPENDENCIES		= Makefile lib/libtacproxy.la
lib_mod_radius_la_CPPFLAGS		= $(AM_CPPFLAGS) -I$(srcdir)/lib/mod_radius
lib_mod_radius_la_CFLAGS		= $(AM_CFLAGS)
lib_mod_radius_la_LDFLAGS		= -module \
					  -avoid-version \
					  -export-dynamic \
					  -shared \
					  $(AM_LDFLAGS)
lib_mod_radius_la_LIBADD		= $(AM_LIBS)
lib_mod_radius_la_SOURCES		= $(noinst_HEADERS) \
					  lib/libtacproxy/test.c


### macros for lib/mod_syslog.la
lib_mod_syslog_la_DEPENDENCIES		= Makefile lib/libtacproxy.la
lib_mod_syslog_la_CPPFLAGS		= $(AM_CPPFLAGS) -I$(srcdir)/lib/mod_syslog
lib_mod_syslog_la_CFLAGS		= $(AM_CFLAGS)
lib_mod_syslog_la_LDFLAGS		= -module \
					  -avoid-version \
					  -export-dynamic \
					  -shared \
					  $(AM_LDFLAGS)
lib_mod_syslog_la_LIBADD		= $(AM_LIBS)
lib_mod_syslog_la_SOURCES		= $(noinst_HEADERS) \
					  lib/libtacproxy/test.c


### macros for src/tac-cli
src_tac_cli_DEPENDENCIES		= Makefile lib/libtacproxy.la
src_tac_cli_CPPFLAGS			= -DPROGRAM_NAME="\"tac-cli\"" $(AM_CPPFLAGS)
src_tac_cli_CFLAGS			= $(AM_CFLAGS)
src_tac_cli_LDFLAGS			= $(AM_LDFLAGS)
src_tac_cli_LDADD			= $(AM_LDADD) lib/libtacproxy.la
src_tac_cli_SOURCES			= src/test.c


### macros for src/tac-proxyd
src_tac_proxyd_DEPENDENCIES		= Makefile lib/libtacproxy.la
src_tac_proxyd_CPPFLAGS			= -DPROGRAM_NAME="\"tac-cli\"" $(AM_CPPFLAGS)
src_tac_proxyd_CFLAGS			= $(AM_CFLAGS)
src_tac_proxyd_LDFLAGS			= $(AM_LDFLAGS)
src_tac_proxyd_LDADD			= $(AM_LDADD) lib/libtacproxy.la
src_tac_proxyd_SOURCES			= src/test.c


# Makefile includes
GIT_PACKAGE_VERSION_DIR=include
SUBST_EXPRESSIONS =
include $(srcdir)/contrib/bindletools/build-aux/makefile-bindle.am
include $(srcdir)/contrib/bindletools/build-aux/makefile-autotools.am
include $(srcdir)/contrib/bindletools/build-aux/makefile-subst.am
include $(srcdir)/contrib/bindletools/build-aux/makefile-version.am


# custom targets
.PHONY:


# local targets
install-exec-local:

install-data-local:

install-exec-hook:

install-data-hook:

uninstall-local:

clean-local:

distclean-local:
	rm -fR $(srcdir)/autom4te.cache

maintainer-clean-local:

# end of automake file
