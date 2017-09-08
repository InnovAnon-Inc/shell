#include <stdlib.h>

#include <stdio.h>

#include "shell.h"

static int puts2 (const char *const str) {
	if (puts (str) == EOF) return -1;
	return 0;
}

int main (void) {
	/*
   char str0[] = "ls";
   char str1[] = "grep";
   char str2[] = "shell";
   char str3[] = "wc";
   char *arg0[] = {str0};
   char *arg1[] = {str1, str2};
   char *arg2[] = {str3};
   char **argvs[3] = {arg0, arg1, arg2};
   */
   /*const*/ char /*const*/ * const * const * const argvs = (char *const *const []) {
	 (char *const []) {"ls", NULL},
	 (char *const []) {"grep", "shell", NULL},
	 (char *const []) {"wc", NULL}
   };
   size_t nargv = 3;

   /*if (fork_and_wait (puts2, "Hello") != 0) return -2;*/
   /*if (fork_and_wait2 (puts2, "Hello", puts2, "World") != 0) return -2;*/
   /*puts ("main ()");*/

   if (exec_pipeline (argvs, nargv) != 0) return EXIT_FAILURE;
   return EXIT_SUCCESS;
}
