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
#define _SRC_CLI_MAIN_C 1

///////////////
//           //
//  Headers  //
//           //
///////////////
#pragma mark - Headers

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <tacplusproxy.h>
#include <getopt.h>
#include <assert.h>
#include <stdio.h>


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

int main(int argc, char *argv[]);
void my_usage(void);
void my_version(void);


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#pragma mark - Functions

int main(int argc, char * argv[])
{
   int            c;
   int            opt_index;

   static char          short_options[]   = "hvV";
   static struct option long_options[]    =
   {
      { "help",          no_argument,       0, 'h' },
      { "verbose",       no_argument,       0, 'v' },
      { "version",       no_argument,       0, 'V' },
      { NULL,            0,                 0, 0   }
   };

   // loops through args
   while((c = getopt_long(argc, argv, short_options, long_options, &opt_index)) != -1)
   {
      switch(c)
      {
         case -1:       /* no more arguments */
         case 0:        /* long options toggles */
         break;

         case 'h':
         my_usage();
         return(0);

         case 'V':
         my_version();
         return(0);

         case 'v':
         break;

         // argument error
         case '?':
         fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
         return(1);

         // unknown argument error
         default:
         fprintf(stderr, "%s: unrecognized option `--%c'\n", PROGRAM_NAME, c);
         fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
         return(1);
      };
   };

   return(0);
}


/// prints program usage and exits
void my_usage(void)
{
   printf("Usage: %s [OPTIONS]\n", PROGRAM_NAME);
   printf("OPTIONS:\n");
   printf("  -h, --help                print this help and exit\n");
   printf("  -v, --verbose             run in verbose mode\n");
   printf("  -V, --version             print version number and exit\n");
   printf("\n");
   return;
}


/// displays version information
void my_version(void)
{
   printf("%s (%s) %s\n", PROGRAM_NAME, PACKAGE_NAME, PACKAGE_VERSION);
   return;
}


/* end of source */
