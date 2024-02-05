# configure.ac - Last modified: 05-Feb-2024 (kobayasy)
#
# Copyright (C) 2024 by Yuichi Kobayashi <kobayasy@kobayasy.com>
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation files
# (the "Software"), to deal in the Software without restriction,
# including without limitation the rights to use, copy, modify, merge,
# publish, distribute, sublicense, and/or sell copies of the Software,
# and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

AC_PREREQ(2.69)
AC_INIT([printBar], [0.1], [kobayasy@kobayasy.com], [printbar])
AC_COPYRIGHT([Copyright @{:@C@:}@ 2024 by Yuichi Kobayashi <kobayasy@kobayasy.com>])
AC_CONFIG_SRCDIR([printbar.c])
AC_CONFIG_AUX_DIR([conf])

AC_SUBST([CONFFILE], ['~/.psync.conf'])
AC_SUBST([BACKUP], ['3'])
AC_SUBST([EXPIRE], ['400'])
AC_SUBST([SSH], ['ssh'])
AC_SUBST([SSHPORT], ['22'])

AC_DEFUN([MY_ARG_ENABLE],
   [AC_ARG_ENABLE([$1], [AS_HELP_STRING([--$2-$1], [$3])],
       [AS_CASE([$enableval],
         [yes|no],
           [],
           [AC_MSG_WARN([invalid option: --enable-$1=$enableval])
            AS_UNSET([enableval]) ] )],
       [AS_UNSET([enableval])] )] )
AC_DEFUN([MY_ARG_WITH],
   [AC_ARG_WITH([$1], [AS_HELP_STRING([--with-$1=$2], [$3])],
       [AS_CASE([$withval],
         [yes|no],
           [AC_MSG_WARN([invalid option: --with-$1=$withval])
            AS_UNSET([withval]) ] )],
       [AS_UNSET([withval])] )] )

AC_PROG_MAKE_SET
AC_PROG_CC
AC_PROG_INSTALL

MY_ARG_ENABLE([warnall], [enable], [enable most reasonable warnings for compiler options])
AS_VAR_IF([enableval], [yes],
   [AX_CFLAGS_WARN_ALL] )
AX_PTHREAD([LIBS="$PTHREAD_LIBS $LIBS" CFLAGS="$CFLAGS $PTHREAD_CFLAGS" CC="$PTHREAD_CC"])
AC_CHECK_HEADERS([termcap.h],
   [AC_CHECK_FUNC([tgetent],
       [AC_DEFINE([HAVE_TGETENT], [1], [Define to 1 if you have the `tgetent' function.])],
       [AC_SEARCH_LIBS([tgetent], [tinfo ncurses],
           [AC_DEFINE([HAVE_TGETENT], [1])] )] )] )


AC_CONFIG_FILES([Makefile])
AC_CONFIG_HEADERS([config.h])
AH_TOP([#ifndef _INCLUDE_config_h
#define _INCLUDE_config_h])
AH_BOTTOM([#endif  /* #ifndef _INCLUDE_config_h */])
AX_APPEND_FLAG([-I.])
AC_OUTPUT
