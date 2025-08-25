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
///   File: mutex.cpp
///
/// Author: $author$
///   Date: 1/2/2017
///////////////////////////////////////////////////////////////////////
#include "nadir/mt/microsoft/windows/mutex.hpp"

#if !defined(WINDOWS)
#include "nadir/mt/os/mutex.hpp"
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
    virtual BOOL ReleaseMutex() {
        BOOL success = FALSE;
        return success;
    }
    virtual DWORD WaitForSingleObject(DWORD dwMilliseconds) {
        DWORD dwStatus = WAIT_FAILED;
        return dwStatus;
    }
};
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Mutex: public Handle {
public:
    Mutex() {}
    virtual BOOL CloseHandle() {
        BOOL success = FALSE;
        if ((mutex_.destroyed())) {
            success = TRUE;
        }
        return success;
    }
    virtual BOOL ReleaseMutex() {
        BOOL success = FALSE;
        if ((mutex_.unlock())) {
            success = TRUE;
        }
        return success;
    }
    virtual DWORD WaitForSingleObject(DWORD dwMilliseconds) {
        DWORD dwStatus = WAIT_FAILED;
        nadir::lock_status status = nadir::lock_failed;
        if (INFINITE != dwMilliseconds) {
            status = mutex_.timed_lock(dwMilliseconds);
        } else {
            status = mutex_.untimed_lock();
        }
        switch (status) {
        case nadir::lock_success:
            dwStatus = WAIT_OBJECT_0;
            break;
        case nadir::lock_busy:
            dwStatus = WAIT_TIMEOUT;
            break;
        case nadir::lock_interrupted:
            dwStatus = WAIT_ABANDONED;
            break;
        }
        return dwStatus;
    }
    nadir::mt::os::mutex mutex_;
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
HANDLE WINAPI CreateMutex(
  _In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,
  _In_     BOOL                  bInitialOwner,
  _In_opt_ LPCTSTR               lpName
) {
    try {
        Mutex* mutex = 0;
        if ((mutex = new Mutex)) {
            return mutex;
        }
    } catch (const nadir::create_exception e) {
    }
    return 0;
}
BOOL WINAPI ReleaseMutex(
  _In_ HANDLE hMutex
) {
    Handle* handle = 0;
    if ((handle = ((Handle*)hMutex))) {
        BOOL success = handle->ReleaseMutex();
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
///  Class: mutext
///////////////////////////////////////////////////////////////////////

} // namespace windows 
} // namespace microsoft 
} // namespace mt 
} // namespace nadir 
