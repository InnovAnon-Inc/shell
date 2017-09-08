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
   char const *const arg0[2];
   arg0[0] = str0;
   arg0[1] = NULL;
   char const *const arg1[3];
   arg1[0] = str1;
   arg1[1] = str2;
   arg1[2] = NULL;
   char const *const arg2[2];
   arg2[0] = str3;
   arg2[0] = NULL;
   char const *const *const argvs[3];
   argvs[0] = arg0;
   argvs[1] = arg1;
   argvs[2] = arg2;
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
