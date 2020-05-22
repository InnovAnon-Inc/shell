AC_INIT([libshell], [1.0], [InnovAnon-Inc@protonmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AM_PROG_AR
LT_INIT([])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
 src/libshell.pc
 src/shell-test.pc
])

PKG_PROG_PKG_CONFIG

AC_ARG_ENABLE([use-submodules],
    AS_HELP_STRING([--enable-use-submodules], [Enable use submodules]))
AM_CONDITIONAL([USE_SUBMODULES], [test x"$enable_use_submodules" = "xyes"])

AC_CONFIG_MACRO_DIR([m4])

AC_CHECK_HEADERS([stdlib.h unistd.h sys/types.h sys/wait.h])
#AC_CHECK_HEADERS([ezfork.h glitter.h restart.h mmalloc.h])

#AC_CHECK_LIB([ezfork],[ezfork])
#AC_CHECK_LIB([restart],[r_waitpid,r_close,r_dup2])
#AC_CHECK_LIB([mmalloc],[mmalloc])

PKG_CHECK_MODULES([GLITTER],[glitter],,)
PKG_CHECK_MODULES([MMALLOC],[libmmalloc],,)
PKG_CHECK_MODULES([RESTART],[librestart],,)
PKG_CHECK_MODULES([EZFORK],[libezfork],,)

INNOVANON_WARNINGS([])

AC_OUTPUT

