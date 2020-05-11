#ifndef _EZFORK_H_
#define _EZFORK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#include <glitter.h>

typedef __attribute__ ((warn_unused_result))
int (*childcb_t) (void *restrict) ;

typedef __attribute__ ((warn_unused_result))
int (*parentcb_t) (pid_t, void *restrict) ;

int ezfork (
	childcb_t childcb,   void *restrict childcb_args,
	parentcb_t parentcb, void *restrict parentcb_args)
__attribute__ ((nonnull (1, 3), warn_unused_result)) ;

#ifdef __cplusplus
}
#endif

#endif /* _EZFORK_H_ */