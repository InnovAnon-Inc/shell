#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include <ezfork.h>
#include <restart.h>

#include "shell.h"

typedef struct {
	int (*cb) (void *);
	void *arg;
} closure_t;

__attribute__ ((nothrow, warn_unused_result))
static int ezfork_parentcb_wait (pid_t cpid, void *unused) {
	pid_t wpid;
	int status;

	/*puts ("ezfork_parentcb_wait ()");*/

	do {
		wpid = r_waitpid (cpid, &status, WUNTRACED);
		error_check (wpid == -1) return -1;
	} while_check (! WIFEXITED (status) && ! WIFSIGNALED (status));
	if (status == -1) return -2;
	return 0;
}

__attribute__ ((nonnull (1), warn_unused_result))
int fork_and_wait (int (*cb) (void *), void *cb_args) {
	/*puts ("fork_and_wait ()");*/
	return ezfork (cb, cb_args, ezfork_parentcb_wait, NULL);
}

typedef closure_t parentcb_t;

__attribute__ ((nonnull (2), nothrow, warn_unused_result))
static int ezfork_parentcb_wait2 (pid_t cpid, void *args) {
	pid_t wpid;
	int status;
	parentcb_t *cb = (parentcb_t *) args;

	/*puts ("ezfork_parentcb_wait2 ()");*/

	error_check (cb->cb (cb->arg) != 0) {
		/* TODO cleanup child */
		/*puts ("ezfork_parent_cb_wait2 error");*/
	   return -2;
   }

   /*puts ("ezfork_parentcb_wait2 waiting");*/

	do {
		wpid = r_waitpid (cpid, &status, WUNTRACED);
		error_check (wpid == -1) return -2;
	} while_check (! WIFEXITED (status) && ! WIFSIGNALED (status));
	error_check (status == -1) {
		/*puts ("ezfork_parentcb_wait2 child failed");*/
		return -2;
	}
	/*puts ("ezfork_parentcb_wait2 success");*/
	return 0;
}

__attribute__ ((nonnull (1, 3), warn_unused_result))
int fork_and_wait2 (
	int (*childcb)  (void *), void *childcb_args,
	int (*parentcb) (void *), void *parentcb_args) {
	parentcb_t cb;

	/*puts ("fork_and_wait2 ()");*/

	cb.cb = parentcb;
	cb.arg = parentcb_args;
	error_check (ezfork (
		childcb, childcb_args,
		ezfork_parentcb_wait2, (void *) &cb) != 0) {
			/*puts ("fork_and_wait2 error");*/
			return -1;
		}
	/*puts ("fork_and_wait2 success");*/
	return 0;
}

__attribute__ ((const, nothrow, warn_unused_result))
static int do_nothing (pid_t cpid, void *unused) {
	/*puts ("do_nothing ()");*/
	return 0;
}

__attribute__ ((nonnull (1), warn_unused_result))
int zombify (int (*childcb)  (void *), void *childcb_args) {
	/* insert joke about neglecting children */
	/*puts ("zombify ()");*/
	error_check (ezfork (childcb, childcb_args, do_nothing, NULL) != 0) {
		/*puts ("zombify error");*/
		return -1;
	}
	/*puts ("zombify success");*/
	return 0;
}

__attribute__ ((nonnull (1), warn_unused_result))
static int zombify_wrapper (void *arg) {
	closure_t *closure = (closure_t *) arg;
	/*puts ("zombify_wrapper ()");*/
	error_check (zombify (closure->cb, closure->arg) != 0) {
		/*puts ("zombify_wrapper error");*/
		return -1;
	}
	/*puts ("zombify_wrapper success");*/
	return 0;
}

typedef closure_t background_t;

/* typedef apply_closure_t; ==> closure with a closure in it */

/*
static int backgroundcb (void *args) {
	background_t *tmp = (background_t *) args;
	return zombify (tmp->cb, tmp->args);
}
*/

__attribute__ ((nonnull (1), warn_unused_result))
int background (int (*cb) (void *), void *args) {
	closure_t tmp;
	tmp.cb = cb;
	tmp.arg = args;
	/*puts ("background ()");*/
	error_check (fork_and_wait (zombify_wrapper, &tmp) != 0) {
		/*puts ("background error");*/
		return -1;
	}
	/*puts ("background success");*/
	return 0;
}

/* ------------------------------------------ */



typedef struct {
	fd_t input;
	fd_t wr;
	fd_t rd;
	pid_t cpid;
	bool last;
} parentcb2_t;

__attribute__ ((nonnull (2), nothrow, warn_unused_result))
static int parentcb (pid_t cpid, void *cbargs) {
	parentcb2_t *args = (parentcb2_t *) cbargs;
	fd_t input = args->input;
	fd_t wr = args->wr;
	fd_t rd = args->rd;
	bool last = args->last;
	args->cpid = cpid;

	/*puts ("parentcb ()");
	printf ("input:%d\nrd:%d\nwr:%d\n", input, rd, wr);*/

	error_check (r_close (input) != 0) {
		r_close (wr);
		if (last) r_close (rd);
		return -1;
	}
	error_check (r_close (wr) != 0) {
		if (last) r_close (rd);
		return -2;
	}
	if (last) {
		error_check (r_close (rd) != 0)
			return -3;
	}
	/*return rd;*/
	return 0;
}


/* client code */
/*
typedef struct {
	bool first, last;
	fd_t input, rd, wr;
	void *args;
} command_t;
*/



typedef struct {
	fd_t input, rd, wr;
	pipeline_t *cmd;
	bool first, last;
} childcommon_t;

__attribute__ ((nonnull (1), warn_unused_result))
static int childcommon (void *tmp) {
	childcommon_t *arg = (childcommon_t *) tmp;
	fd_t input = arg->input;
	fd_t rd = arg->rd;
	fd_t wr = arg->wr;
	pipeline_t *cmd = arg->cmd;
	bool first = arg->first;
	bool last = arg->last;
	/*puts ("childcommon ()");
	printf ("input:%d\nrd:%d\nwr:%d\n", input, rd, wr);*/
	error_check (cmd->cb (input, rd, wr, first, last, cmd->arg) != 0) {
		/*puts ("childcommon failed");*/
		return -1;
	}
	/*puts ("childcommon success");*/
	return 0;
}
/*
typedef struct {
	int rd; / * ret val * /
	fd_t input;
	bool first;
	bool last;
	closure_t args;
} command_t;*/

#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("TODO - " #x))

#define swallow(E,D) do { \
	_Pragma ("GCC diagnostic push") \
	DO_PRAGMA (GCC diagnostic ignored #D) \
	(void) (E); \
	_Pragma ("GCC diagnostic pop") \
} while (false) ;

__attribute__ ((nonnull (1), warn_unused_result))
static int command (pipeline_t *cmd, fd_t *input, bool first, bool last) {
	childcommon_t cargs;
	parentcb2_t pargs;

	fd_t pipettes[2];

	/* TODO */
	error_check (pipe (pipettes) != 0)
		return -1;

	cargs.first = first;
	cargs.last = last;
	cargs.input = *input;
	cargs.rd = pipettes[0];
	/* */ cargs.wr = pipettes[1];
	cargs.cmd = cmd;

	pargs.input = *input;
	pargs.wr = pipettes[1];
	pargs.rd = pipettes[0];
	pargs.last = last;

	*input = pipettes[0];
	/*puts ("command ()");*/

	error_check (ezfork (childcommon, &cargs, parentcb, &pargs) != 0) {
		/*puts ("command failed");*/
		swallow (r_close (pipettes[0]), -Wunused-result);
		swallow (r_close (pipettes[1]), -Wunused-result);
		return -2;
	}
	cmd->cpid = pargs.cpid;
	/*
	if (fork_and_wait2 (
		childcommon, &cargs,
		parentcb, &pargs) != 0) {
			puts ("command failed");
			return -1;
	}
	puts ("command success");
	*/

	return 0;
}

/* TODO add void * param to cmds' siggy, and void * arg... closure-style */

/* nargv is non-zero */
__attribute__ ((nonnull (1), warn_unused_result))
int pipeline (pipeline_t cmds[], size_t ncmd) {
	fd_t input = STDIN_FILENO;
	bool first = true;
	size_t i;

	/*printf ("ncmd:%d\n", (int) ncmd);*/

	for (i = 0; i != ncmd - 1; i++) {
		/*printf ("1cmd:%d\n", (int) i);*/
		error_check (command (cmds + i, &input, first, false) != 0)
			return -1;
		first = false;
	}
	/*printf ("2cmd:%d\n", (int) i);*/
	error_check (command (cmds + i, &input, first, true) != 0)
		return -2;
	for (i = 0; i != ncmd; i++) {
		pid_t cpid = cmds[i].cpid;
		pid_t wpid;
		int status;
		do {
			wpid = r_waitpid (cpid, &status, WUNTRACED);
			error_check (wpid == -1) return -3;
		} while_check (! WIFEXITED (status) && ! WIFSIGNALED (status));
		error_check (status == -1) {
			/*puts ("ezfork_parentcb_wait2 child failed");*/
			return -4;
		}
	}
	return 0;
}

__attribute__ ((const, warn_unused_result))
int ring (void) {
	return -2;
}

/* zombify (): fork and don't wait */
/* bg (): fork_and_wait (zombify (cb)) */
/* pipeline (): fork_and_wait (fork_and_wait (fork_and_wait (..., pcb), pcb), pcb) */
/* ring (): */
/* web (): */



typedef struct {
	char *const *argv;
} exec_pipelinecb_t;

__attribute__ ((nonnull (6), nothrow, warn_unused_result))
static int exec_pipelinecb (fd_t input, fd_t rd, fd_t wr,
	bool first, bool last, void *cbargs) {
	exec_pipelinecb_t *args = (exec_pipelinecb_t *) cbargs;
	char *const *argv = args->argv;
	/*puts ("exec_pipelinecb");*/
	/*if (argv == NULL) puts ("a");
	puts ("aa");
	if (argv[0] == NULL) puts ("b");
	puts ("bb");*/
	/*printf ("exec_piplinecb: %s\n", argv[0]);*/
	/*fflush (stdout);*/

	/*cb ();*/
	if (first && ! last && input == STDIN_FILENO) { /* first command */
		error_check (r_dup2 (wr, STDOUT_FILENO) != 0)    return -1;
	} else if (! first && ! last && input != STDIN_FILENO) { /* middle command */
		error_check (r_dup2 (input, STDIN_FILENO) != 0)  return -2;
		error_check (r_dup2 (wr,    STDOUT_FILENO) != 0) return -3;
	} else {/* last command */
		error_check (r_dup2 (input, STDIN_FILENO) != 0)  return -4;
	}

	execvp (argv[0], argv); /* returns -1 */
	return -5;
	/*return closure->cb (closure->arg);*/
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
int exec_pipeline (char *const *const *argvs, size_t nargv) {
	pipeline_t *cmds = malloc (nargv * sizeof (pipeline_t)
	+ nargv * sizeof (exec_pipelinecb_t));
	exec_pipelinecb_t *tmps;
	size_t i;
	error_check (cmds == NULL) return -1;
	tmps = (exec_pipelinecb_t *) (cmds + nargv);
	for (i = 0; i != nargv; i++) {
		cmds[i].cb = exec_pipelinecb;
		cmds[i].arg = tmps + i;
		tmps[i].argv = argvs[i];
	}
	/*puts ("exec_pipeline ()");*/
	error_check (pipeline (cmds, nargv) != 0) {
		/*puts ("exec_pipeline failed");*/
		free (cmds);
		return -2;
	}
	/*puts ("exec_pipeline success");*/
	free (cmds);
	return 0;
}