#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdlib.h>
#include <unistd.h>
/*#include <sys/wait.h>*/

#include <ezfork.h>

#define CHILD_CASE case 0
#define PARENT_CASE default
#define ERROR_CASE case -1

__attribute__ ((nonnull (1, 3), warn_unused_result))
int ezfork (
   childcb_t childcb,    void *restrict childcb_args,
   parentcb_t parentcb, void *restrict parentcb_args) {
	pid_t pid;

	pid = fork ();
	/*switch (pid) {
    ERROR_CASE: return -1;
	CHILD_CASE:
	   if (childcb (childcb_args) != 0)
	      return EXIT_FAILURE;
	   return EXIT_SUCCESS;
	PARENT_CASE:
	   if (parentcb (pid, parentcb_args) != 0)
		   return -3;
	   return 0;
   }
   __builtin_unreachable ();*/
   error_check (pid == -1) return -1;
   if (pid == 0) {
      error_check (childcb (childcb_args) != 0)
         return EXIT_FAILURE;
      return EXIT_SUCCESS;
   }
   error_check (parentcb (pid, parentcb_args) != 0)
      return -3;
   return 0;
}

#undef CHILD_CASE
#undef PARENT_CASE
#undef ERROR_CASE