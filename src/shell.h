#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdbool.h>
#include <sys/types.h>

/* exec_pipeline, exec_ring */

int exec_pipeline (char *const *const *argvs, size_t nargv) ;

/* ---------- */

/* ring, command, pipeline */

typedef int fd_t;

typedef struct {
	int (*cb) (fd_t, fd_t, fd_t, bool, bool, void *);
	void *arg;
	pid_t cpid;
} pipeline_t;

int pipeline (pipeline_t cmds[], size_t ncmd) ;

/* ---------- */

/* fork a process
 * child invokes cb (args)
 * parent does nothing, creating a zombie */
int zombify (int (*cb) (void *), void *args) ;

/* fork a process, then fork a process
 * grandchild invokes cb (args)
 * child does nothing, but dies, so grandchild is adopted by the init orphanage
 * parent waits for child to die */
int background (int (*cb) (void *), void *args) ;

/* ---------- */

/* fork a process
 * child invokes cb (args)
 * parent waits for child */
int fork_and_wait (int (*cb) (void *), void *cb_args) ;

/* fork a process
 * child invokes childcb (childargs)
 * parent invokes parencb (parenargs), then waits for child */
int fork_and_wait2 (
	int (*childcb)  (void *), void *childcb_args,
	int (*parentcb) (void *), void *parentcb_args) ;

#endif /* _SHELL_H_ */