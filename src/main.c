#include <stdlib.h>

#include <stdio.h>

#include "shell.h"

static int puts2 (const char *const str) {
	if (puts (str) == EOF) return -1;
	return 0;
}

int main (void) {
   const char str0[] = "ls";
   const char str1[] = "grep";
   const char str2[] = "shell";
   const char str3[] = "wc";
   char *const arg0[] = (char *const []) {str0, NULL};
   char *const arg1[] = (char *const []) {str1, str2, NULL};
   char *const arg2[] = (char *const []) {str3, NULL};
   char *const *const argvs[3] = {arg0, arg1, arg2};
   /*
   char *const *const *const argvs = (char *const *const []) {
	 (char *const []) {"ls", NULL},
	 (char *const []) {"grep", "shell", NULL},
	 (char *const []) {"wc", NULL}
   };*/
   size_t nargv = 3;

   /*if (fork_and_wait (puts2, "Hello") != 0) return -2;*/
   /*if (fork_and_wait2 (puts2, "Hello", puts2, "World") != 0) return -2;*/
   /*puts ("main ()");*/

   if (exec_pipeline (argvs, nargv) != 0) return EXIT_FAILURE;
   return EXIT_SUCCESS;
}
