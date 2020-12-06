
TACACS+ Proxy Server and Utilities
==================================

Copyright (c) 2020 David M. Syzdek <david@syzdek.net>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

   1. Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

   3. Neither the name of the copyright holder nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


Contents
--------

   * Overview
   * Source Code
   * Package Maintence Notes


Overview
==========

This package contains a TACACS+ proxy, library, and CLI client.  The TACACS+
proxy could be used as a standalone system without proxying the requests to
another AAA system, however the proxy will not provide any branching logic for
determining advanced user access and permissions.


Source Code
===========

The source code for this project is maintained using git
(http://git-scm.com).  The following contains information to checkout the
source code from the git repository.

Browse Source:

   * https://github.com/syzdek/tacplusproxy
   * https://github.com/alaskacommunications/tacplusproxy
   * https://scm.prv.acsalaska.net/pub/scm/ipeng/tacplusproxy.git/

Git URLs:

   * https://github.com/syzdek/tacplusproxy
   * https://github.com/alaskacommunications/tacplusproxy
   * https://scm.prv.acsalaska.net/pub/scm/ipeng/tacplusproxy.git

Downloading Source:

      $ git clone https://github.com/syzdek/tacplusproxy

Preparing Source:

      $ cd tacplusproxy
      $ ./autogen.sh

Compiling Source:

      $ cd build
      $ ./configure
      $ make && make install

For more information on building and installing using configure, please
read the INSTALL file.

Git Branches:

   * master - Current release of packages.
   * next   - changes staged for next release
   * pu     - proposed updates for next release
   * xx/yy+ - branch for testing new changes before merging to 'pu' branch


Package Maintence Notes
=======================

This is a collection of notes for developers to use when maintaining this
package.

New Release Checklist:

   - Switch to 'master' branch in Git repository.
   - Update version in configure.ac.
   - Update date and version in ChangeLog.
   - Commit configure.ac and ChangeLog changes to repository.
   - Create tag in git repository:

           $ git tag -s v${MAJOR}.${MINOR}

   - Push repository to publishing server:

           $ git push --tags origin master:master next:next pu:pu

Creating Source Distribution Archives:

      $ ./configure
      $ make update
      $ make distcheck
      $ make dist-bzip2
      $ make dist-xz


