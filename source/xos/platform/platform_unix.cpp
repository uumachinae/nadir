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
///   File: platform_unix.cpp
///
/// Author: $author$
///   Date: 9/11/2017, 6/13/2021
///////////////////////////////////////////////////////////////////////
#include "xos/platform/platform_unix.hpp"
#include "xos/platform/platform_unix.c"

namespace xos {
namespace platform {

} // namespace platform 
} // namespace xos 

#if !defined(WINDOWS)
#if defined(MACOSX)
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
int clock_gettime(clockid_t clk_id, struct timespec *res) {
    if ((res)) {
        memset(res, 0, sizeof(struct timespec));
        return 0;
    }
    return EINVAL;
}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
int pthread_tryjoin_np(pthread_t thread, void **retval) {
    return EINVAL;
}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
int pthread_timedjoin_np
(pthread_t thread, void **retval, const struct timespec *abstime) {
    return EINVAL;
}
#else // defined(MACOSX)
#endif // defined(MACOSX)
#else // !defined(WINDOWS)
#endif // !defined(WINDOWS)

#if !defined(WINDOWS)
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
BOOL WINAPI CloseHandle(
  _In_ HANDLE hObject
) {
    ::xos::platform::microsoft::windows::Handle* handle = 0;
    if ((handle = ((::xos::platform::microsoft::windows::Handle*)hObject))) {
        BOOL success = handle->CloseHandle();
        delete handle;
        return success;
    }
    return FALSE;
}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
BOOL WINAPI ReleaseMutex(
  _In_ HANDLE hMutex
) {
    ::xos::platform::microsoft::windows::Handle* handle = 0;
    if ((handle = ((::xos::platform::microsoft::windows::Handle*)hMutex))) {
        BOOL success = handle->ReleaseMutex();
        return success;
    }
    return FALSE;
}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
BOOL WINAPI ReleaseSemaphore(
  _In_      HANDLE hSemaphore,
  _In_      LONG   lReleaseCount,
  _Out_opt_ LPLONG lpPreviousCount
) {
    ::xos::platform::microsoft::windows::Handle* handle = 0;
    if ((handle = ((::xos::platform::microsoft::windows::Handle*)hSemaphore))) {
        BOOL success = handle->ReleaseSemaphore(lReleaseCount, lpPreviousCount);
        return success;
    }
    return FALSE;
}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
DWORD WINAPI WaitForSingleObject(
  _In_ HANDLE hHandle,
  _In_ DWORD  dwMilliseconds
) {
    ::xos::platform::microsoft::windows::Handle* handle = 0;
    if ((handle = ((::xos::platform::microsoft::windows::Handle*)hHandle))) {
        DWORD dwStatus = handle->WaitForSingleObject(dwMilliseconds);
        return dwStatus;
    }
    return WAIT_FAILED;
}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
DWORD WINAPI GetLastError(void) {
    DWORD dwLastError = 1;
    return dwLastError;
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
int _fileno(
   FILE *stream
) {
    return ::fileno(stream);
}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
int _setmode (
   int fd,
   int mode
) {
    if (0 <= (fd)) {
        return 0;
    }
    return -1;
}

#else // !defined(WINDOWS)
#endif // !defined(WINDOWS)
