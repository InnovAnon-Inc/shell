AC_INIT([libshell], [0.0], [laurence.a.maddox@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AM_PROG_AR
LT_INIT([])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
])
AC_CONFIG_MACRO_DIR([m4])

AC_CHECK_HEADERS([stdlib.h unistd.h sys/types.h sys/wait.h])
AC_CHECK_HEADERS([ezfork.h glitter.h restart.h])

AC_CHECK_LIB([ezfork],[ezfork])
AC_CHECK_LIB([restart],[r_waitpid,r_close,r_dup2])

INNOVANON_WARNINGS([])

AC_OUTPUT
