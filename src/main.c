#include <stdlib.h>

#include <stdio.h>

#include "shell.h"

static int puts2 (const char *const str) {
	if (puts (str) == EOF) return -1;
	return 0;
}

int main (void) {
   char str0[3];
   char str1[5];
   char str2[6];
   char str3[3];
   char *arg0[2];
   char *arg1[3];
   char *arg2[2];
   char *const *argvs[3];
   size_t nargv = 3;
   str0[0] = 'l'; str0[1] = 's'; str0[2] = '\0';
   str1[0] = 'g'; str1[1] = 'r'; str1[2] = 'e'; str1[3] = 'p'; str1[4] = '\0';
   str2[0] = 's'; str2[1] = 'h'; str2[2] = 'e'; str2[3] = 'l'; str2[4] = 'l'; str2[5] = '\0';
   str3[0] = 'w'; str3[1] = 'c'; str3[2] = '\0';
   arg0[0] = str0;
   arg0[1] = NULL;
   arg1[0] = str1;
   arg1[1] = str2;
   arg1[2] = NULL;
   arg2[0] = str3;
   arg2[0] = NULL;

   argvs[0] = arg0;
   argvs[1] = arg1;
   argvs[2] = arg2;
   /*
   char *const *const *const argvs = (char *const *const []) {
	 (char *const []) {"ls", NULL},
	 (char *const []) {"grep", "shell", NULL},
	 (char *const []) {"wc", NULL}
   };*/

   /*if (fork_and_wait (puts2, "Hello") != 0) return -2;*/
   /*if (fork_and_wait2 (puts2, "Hello", puts2, "World") != 0) return -2;*/
   /*puts ("main ()");*/

   if (exec_pipeline ((char *const *const *) argvs, nargv) != 0) return EXIT_FAILURE;
   return EXIT_SUCCESS;
}
