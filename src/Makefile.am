lib_LTLIBRARIES = libshell.la
libshell_la_SOURCES = shell.c
include_HEADERS	= shell.h

libshell_la_CFLAGS = -g -O0 -Wextra -pedantic -ansi
libshell_la_LDFLAGS = -lezfork -lrestart

bin_PROGRAMS = shell-test
shell_test_SOURCES = main.c
shell_test_LDFLAGS = -lezfork -lrestart
shell_test_LDADD = libshell.la

shell_test_CFLAGS = -g -O0 -Wextra -pedantic -ansi -Wconversion -Winit-self -Wold-style-cast -Woverloaded-virtual -Wuninitialized -Wmissing-declarations -Winit-self -Wcast-qual  -Wsign-promo -Wcast-align -Wstrict-null-sentinel -Wstrict-overflow
