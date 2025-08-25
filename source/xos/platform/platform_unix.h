/*/
///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2017 $organization$
///
/// This software is provided by the author and contributors ``as is'' 
/// and any express or implied warranties, including, but not limited to, 
/// the implied warranties of merchantability and fitness for a particular 
/// purpose are disclaimed. In no event shall the author or contributors 
/// be liable for any direct, indirect, incidental, special, exemplary, 
/// or consequential damages (including, but not limited to, procurement 
/// of substitute goods or services; loss of use, data, or profits; or 
/// business interruption) however caused and on any theory of liability, 
/// whether in contract, strict liability, or tort (including negligence 
/// or otherwise) arising in any way out of the use of this software, 
/// even if advised of the possibility of such damage.
///
///   File: platform_unix.h
///
/// Author: $author$
///   Date: 7/23/2017
///////////////////////////////////////////////////////////////////////
/*/
#ifndef _XOS_PLATFORM_PLATFORM_UNIX_H
#define _XOS_PLATFORM_PLATFORM_UNIX_H

#include "xos/platform/platform_build.h"
#include "xos/platform/platform_compiler.h"
#include "xos/platform/platform_includes.h"
#include "xos/platform/platform_defines.h"
#include "xos/platform/platform_types.h"
#include "xos/platform/platform_api.h"

#if defined(MACOSX)
#if !defined(__MAC_OS_X_VERSION_MAX_ALLOWED_NO_POSIX_SEM)
#define __MAC_OS_X_VERSION_MAX_ALLOWED_NO_POSIX_SEM __MAC_10_9
#endif /*/ !defined(__MAC_OS_X_VERSION_MAX_ALLOWED_NO_POSIX_SEM) /*/
#else /*/ defined(MACOSX) /*/
#endif /*/ defined(MACOSX) /*/

#if defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )
#if !defined(HAS_POSIX_TIMEOUTS)
#define HAS_POSIX_TIMEOUTS
#else /*/ !defined(HAS_POSIX_TIMEOUTS) /*/
#endif /*/ !defined(HAS_POSIX_TIMEOUTS) /*/
#else /*/ defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 ) /*/
#endif /*/ defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 ) /*/

#if !defined(HAS_POSIX_TIMEOUTS)
#if !defined(CLOCK_REALTIME)
/*/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////*/
#define HAS_CLOCK_GETTIME
#define CLOCK_REALTIME 0
#define clockid_t int
/*/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////*/
#if defined(__cplusplus)
extern "C" {
#endif /*/ defined(__cplusplus)  /*/

#if !defined(clock_gettime)
int clock_gettime(clockid_t clk_id, struct timespec *res);
#endif /*/ !defined(clock_gettime) /*/

#if defined(__cplusplus)
} /*/ extern "C" /*/
#endif /*/ defined(__cplusplus)  /*/
/*/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////*/
#else /*/ !defined(CLOCK_REALTIME) /*/
#endif /*/ !defined(CLOCK_REALTIME) /*/
#else /*/ !defined(HAS_POSIX_TIMEOUTS) /*/
#endif /*/ !defined(HAS_POSIX_TIMEOUTS) /*/

#if defined(MACOSX)
#if (__MAC_OS_X_VERSION_MAX_ALLOWED <= __MAC_OS_X_VERSION_MAX_ALLOWED_NO_POSIX_SEM)
#include <semaphore.h>
/*/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////*/
#define sem_t posix_sem_t
#define sem_close posix_sem_close
#define sem_destroy posix_sem_destroy
#define sem_getvalue posix_sem_getvalue
#define sem_init posix_sem_init
#define sem_open posix_sem_open
#define sem_post posix_sem_post
#define sem_unlink posix_sem_unlink
#define sem_wait posix_sem_wait
#define sem_trywait posix_sem_trywait
#define sem_timedwait posix_sem_timedwait
#define semctl posix_semctl
#define semget posix_semget
#define semop posix_semop
typedef void* sem_t;
/*/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////*/
#if defined(__cplusplus)
extern "C" {
#endif /*/ defined(__cplusplus)  /*/

int sem_close(sem_t *sem);
int sem_destroy(sem_t *sem);
int sem_getvalue(sem_t *sem, int *sval);
int sem_init(sem_t *sem, int pshared, unsigned int value);
sem_t *sem_open(const char *name, int oflag, ...);
int sem_post(sem_t *sem);
int sem_trywait(sem_t *sem);
int sem_unlink(const char *name);
int sem_wait(sem_t *sem);

int semctl(int semid, int semnum, int cmd, ...);
int semget(key_t key, int nsems, int semflg);
int semop(int semid, struct sembuf *sops, size_t nsops);

#if defined(__cplusplus)
} /*/ extern "C" /*/
#endif /*/ defined(__cplusplus)  /*/
/*/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////*/
#else /*/ (__MAC_OS_X_VERSION_MAX_ALLOWED <= __MAC_OS_X_VERSION_MAX_ALLOWED_NO_POSIX_SEM) /*/
#include <semaphore.h>
#include <errno.h>
#endif /*/ (__MAC_OS_X_VERSION_MAX_ALLOWED <= __MAC_OS_X_VERSION_MAX_ALLOWED_NO_POSIX_SEM) /*/
#else /*/ defined(MACOSX) /*/
#endif /*/ defined(MACOSX) /*/

#if !defined(HAS_POSIX_TIMEOUTS)
#if !defined(SEM_HAS_TIMEDWAIT)
/*/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////*/
#if defined(__cplusplus)
extern "C" {
#endif /*/ defined(__cplusplus)  /*/

int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);

#if defined(__cplusplus)
} /*/ extern "C" /*/
#endif /*/ defined(__cplusplus)  /*/
#define SEM_HAS_TIMEDWAIT
#else /*/ !defined(SEM_HAS_TIMEDWAIT) /*/
#endif /*/ !defined(SEM_HAS_TIMEDWAIT) /*/
#else /*/ !defined(HAS_POSIX_TIMEOUTS) /*/
#endif /*/ !defined(HAS_POSIX_TIMEOUTS) /*/

#if !defined(HAS_POSIX_TIMEOUTS)
#if !defined(PTHREAD_HAS_TRYJOIN)
/*/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////*/
#if defined(__cplusplus)
extern "C" {
#endif /*/ defined(__cplusplus)  /*/

int pthread_tryjoin_np(pthread_t thread, void **retval);

#if defined(__cplusplus)
} /*/ extern "C" /*/
#endif /*/ defined(__cplusplus)  /*/
#define PTHREAD_HAS_TRYJOIN
#define DEFINED_PTHREAD_HAS_TRYJOIN
#else /*/ !defined(PTHREAD_HAS_TRYJOIN) /*/
#endif /*/ !defined(PTHREAD_HAS_TRYJOIN) /*/

#if !defined(PTHREAD_HAS_TIMEDJOIN)
/*/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////*/
#if defined(__cplusplus)
extern "C" {
#endif /*/ defined(__cplusplus)  /*/

int pthread_timedjoin_np
(pthread_t thread, void **retval, const struct timespec *abstime);

#if defined(__cplusplus)
} /*/ extern "C" /*/
#endif /*/ defined(__cplusplus)  /*/
#define PTHREAD_HAS_TIMEDJOIN
#define DEFINED_PTHREAD_HAS_TIMEDJOIN
#else /*/ !defined(PTHREAD_HAS_TIMEDJOIN) /*/
#endif /*/ !defined(PTHREAD_HAS_TIMEDJOIN) /*/
#else /*/ !defined(HAS_POSIX_TIMEOUTS) /*/
#endif /*/ !defined(HAS_POSIX_TIMEOUTS) /*/

#if !defined(WINDOWS)
/*/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////*/
enum {
_O_RDONLY     = 0,
_O_WRONLY     = 1,
_O_RDWR       = 2,
_O_APPEND     = 0x0008,
_O_RANDOM     = 0x0010,
_O_SEQUENTIAL = 0x0020,
_O_TEMPORARY  = 0x0040,
_O_NOINHERIT  = 0x0080,
_O_CREAT      = 0x0100,
_O_TRUNC      = 0x0200,
_O_EXCL       = 0x0400,
_O_TEXT       = 0x4000,
_O_BINARY     = 0x8000,
_O_RAW        = _O_BINARY,
};
enum {
    WAIT_FAILED    = -1,
    WAIT_OBJECT_0  = 0,
    WAIT_ABANDONED = 0x80,
    WAIT_TIMEOUT   = 0x102
};
enum {
    CREATE_SUSPENDED = 0x00000004,
    STACK_SIZE_PARAM_IS_A_RESERVATION = 0x00010000
};
typedef struct _SECURITY_ATTRIBUTES {
  DWORD  nLength;
  LPVOID lpSecurityDescriptor;
  BOOL   bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

typedef DWORD WINAPI ThreadProc(
  _In_ LPVOID lpParameter
);
typedef ThreadProc *PTHREAD_START_ROUTINE, *LPTHREAD_START_ROUTINE;

/*/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////*/
#if defined(__cplusplus)
extern "C" {
#endif /*/ defined(__cplusplus)  /*/

HANDLE WINAPI CreateMutex(
  _In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,
  _In_     BOOL                  bInitialOwner,
  _In_opt_ LPCTSTR               lpName
);
BOOL WINAPI ReleaseMutex(
  _In_ HANDLE hMutex
);
HANDLE WINAPI CreateSemaphore(
  _In_opt_ LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
  _In_     LONG                  lInitialCount,
  _In_     LONG                  lMaximumCount,
  _In_opt_ LPCTSTR               lpName
);
BOOL WINAPI ReleaseSemaphore(
  _In_      HANDLE hSemaphore,
  _In_      LONG   lReleaseCount,
  _Out_opt_ LPLONG lpPreviousCount
);
HANDLE WINAPI CreateThread(
  _In_opt_  LPSECURITY_ATTRIBUTES  lpThreadAttributes,
  _In_      SIZE_T                 dwStackSize,
  _In_      LPTHREAD_START_ROUTINE lpStartAddress,
  _In_opt_  LPVOID                 lpParameter,
  _In_      DWORD                  dwCreationFlags,
  _Out_opt_ LPDWORD                lpThreadId
);
uintptr_t _beginthreadex(
   void *security,
   unsigned stack_size,
   unsigned ( __stdcall *start_address )( void * ),
   void *arglist,
   unsigned initflag,
   unsigned *thrdaddr
);
DWORD WINAPI WaitForSingleObject(
  _In_ HANDLE hHandle,
  _In_ DWORD  dwMilliseconds
);
BOOL WINAPI CloseHandle(
  _In_ HANDLE hObject
);
DWORD WINAPI GetLastError(void);

int _fileno(
   FILE *stream
);
int _setmode (
   int fd,
   int mode
);

#if defined(__cplusplus)
} /*/ extern "C" /*/
#endif /*/ defined(__cplusplus)  /*/
/*/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////*/
#endif /*/ !defined(WINDOWS) /*/

#if defined(__cplusplus)
namespace xos {
#endif /*/ defined(__cplusplus)  /*/

#if defined(__cplusplus)
} /*/ namespace xos /*/
#endif /*/ defined(__cplusplus)  /*/

#endif /*/ _XOS_PLATFORM_PLATFORM_UNIX_H /*/
