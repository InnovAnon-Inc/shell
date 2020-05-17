AM_CPPFLAGS = -D__STDC_INT64__

#include Makefile-LIBADD.inc
dist_bin_SCRIPTS = libshell_config shell_test_config

lib_LTLIBRARIES =
bin_PROGRAMS    =

lib_LTLIBRARIES += libshell.la
include_HEADERS = shell.h
#libshell_la_LIBADD = $(LIBSHELL_LIBADD)
libshell_la_LIBADD = @LIBSHELL_LIBADD@

bin_PROGRAMS += shell-test
#shell_test_LDADD = libshell.la $(LIBSHELL_LIBADD)
#shell_test_LDADD = $(SHELL_TEST_LIBADD)
shell_test_LDADD = @SHELL_TEST_LIBADD@
EXTRA_shell_test_DEPENDENCIES = libshell.la
