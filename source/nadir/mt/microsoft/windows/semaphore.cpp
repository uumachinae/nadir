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
///   File: semaphore.cpp
///
/// Author: $author$
///   Date: 1/2/2017
///////////////////////////////////////////////////////////////////////
#include "nadir/mt/microsoft/windows/semaphore.hpp"

#if !defined(WINDOWS)
#include "nadir/mt/os/semaphore.hpp"
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Handle {
public:
    Handle() {}
    virtual ~Handle() {}
    virtual BOOL CloseHandle() {
        BOOL success = FALSE;
        return success;
    }
    virtual DWORD WaitForSingleObject(DWORD dwMilliseconds) {
        DWORD dwStatus = WAIT_FAILED;
        return dwStatus;
    }
    virtual BOOL ReleaseSemaphore() {
        BOOL success = FALSE;
        return success;
    }
};
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Semaphore: public Handle {
public:
    Semaphore() {}
    virtual BOOL CloseHandle() {
        BOOL success = FALSE;
        if ((semaphore_.destroyed())) {
            success = TRUE;
        }
        return success;
    }
    virtual DWORD WaitForSingleObject(DWORD dwMilliseconds) {
        DWORD dwStatus = WAIT_FAILED;
        nadir::acquire_status status = nadir::acquire_failed;
        if (INFINITE != dwMilliseconds) {
            status = semaphore_.timed_acquire(dwMilliseconds);
        } else {
            status = semaphore_.untimed_acquire();
        }
        switch (status) {
        case nadir::acquire_success:
            dwStatus = WAIT_OBJECT_0;
            break;
        case nadir::acquire_busy:
            dwStatus = WAIT_TIMEOUT;
            break;
        case nadir::acquire_interrupted:
            dwStatus = WAIT_ABANDONED;
            break;
        }
        return dwStatus;
    }
    virtual BOOL ReleaseSemaphore() {
        BOOL success = FALSE;
        if ((semaphore_.release())) {
            success = TRUE;
        }
        return success;
    }
    nadir::mt::os::semaphore semaphore_;
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
HANDLE WINAPI CreateSemaphore(
  _In_opt_ LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
  _In_     LONG                  lInitialCount,
  _In_     LONG                  lMaximumCount,
  _In_opt_ LPCTSTR               lpName
) {
    try {
        Semaphore* sem = 0;
        if ((sem = new Semaphore)) {
            return sem;
        }
    } catch (const nadir::create_exception e) {
    }
    return 0;
}
BOOL WINAPI ReleaseSemaphore(
  _In_      HANDLE hSemaphore,
  _In_      LONG   lReleaseCount,
  _Out_opt_ LPLONG lpPreviousCount
) {
    Handle* handle = 0;
    if ((handle = ((Handle*)hSemaphore))) {
        BOOL success = handle->ReleaseSemaphore();
        return success;
    }
    return FALSE;
}
DWORD WINAPI WaitForSingleObject(
  _In_ HANDLE hHandle,
  _In_ DWORD  dwMilliseconds
) {
    Handle* handle = 0;
    if ((handle = ((Handle*)hHandle))) {
        DWORD dwStatus = handle->WaitForSingleObject(dwMilliseconds);
        return dwStatus;
    }
    return WAIT_FAILED;
}
BOOL WINAPI CloseHandle(
  _In_ HANDLE hObject
) {
    Handle* handle = 0;
    if ((handle = ((Handle*)hObject))) {
        BOOL success = handle->CloseHandle();
        delete handle;
        return success;
    }
    return FALSE;
}
DWORD WINAPI GetLastError(void) {
    return 1;
}
#endif // !defined(WINDOWS)

namespace nadir {
namespace mt {
namespace microsoft {
namespace windows {

///////////////////////////////////////////////////////////////////////
///  Class: semaphoret
///////////////////////////////////////////////////////////////////////

} // namespace windows 
} // namespace microsoft 
} // namespace mt 
} // namespace nadir 
