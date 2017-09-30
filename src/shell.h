#ifndef _SHELL_H_
#define _SHELL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#include <glitter.h>

/* exec_pipeline, exec_ring */

int exec_pipeline (
	char *const *const argvs[],
	size_t nargv)
__attribute__ ((nonnull (1), nothrow, warn_unused_result)) ;

/* ---------- */

/* ring, command, pipeline */

typedef __attribute__ ((warn_unused_result))
int (*pipelinecb_t) (fd_t, fd_t, fd_t, bool, bool, void *restrict) ;

	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wpadded"
typedef struct {
	pipelinecb_t cb;
	void *arg;
	pid_t cpid;
} pipeline_t;
	#pragma GCC diagnostic pop

int pipeline (pipeline_t cmds[], size_t ncmd)
__attribute__ ((nonnull (1), warn_unused_result)) ;

int ring (void)
__attribute__ ((const, warn_unused_result)) ;

/* ---------- */

/* fork a process
 * child invokes cb (args)
 * parent does nothing, creating a zombie */
int zombify (stdcb_t cb, void *restrict args)
__attribute__ ((nonnull (1), warn_unused_result)) ;

/* fork a process, then fork a process
 * grandchild invokes cb (args)
 * child does nothing, but dies, so grandchild is adopted by the init orphanage
 * parent waits for child to die */
int background (stdcb_t cb, void *restrict args)
__attribute__ ((nonnull (1), warn_unused_result)) ;

/* ---------- */

/* fork a process
 * child invokes cb (args)
 * parent waits for child */
int fork_and_wait (stdcb_t cb, void *restrict cb_args)
__attribute__ ((nonnull (1), warn_unused_result)) ;

/* fork a process
 * child invokes childcb (childargs)
 * parent invokes parencb (parenargs), then waits for child */
int fork_and_wait2 (
	stdcb_t childcb,  void *restrict childcb_args,
	stdcb_t parentcb, void *restrict parentcb_args)
__attribute__ ((nonnull (1, 3), warn_unused_result)) ;

#ifdef __cplusplus
}
#endif

#endif /* _SHELL_H_ */