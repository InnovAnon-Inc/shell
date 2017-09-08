lib_LTLIBRARIES = libshell.la
libshell_la_SOURCES = shell.c
include_HEADERS	= shell.h

libshell_la_CFLAGS = -Wextra -pedantic -ansi
libshell_la_LDFLAGS = -lezfork -lrestart

bin_PROGRAMS = shell-test
shell_test_SOURCES = main.c
shell_test_LDFLAGS = -lezfork -lrestart
shell_test_LDADD = libshell.la

shell_test_CFLAGS = -Wextra -pedantic -ansi -Wconversion -Winit-self -Wuninitialized -Wmissing-declarations -Winit-self -Wcast-qual -Wcast-align -Wstrict-overflow
