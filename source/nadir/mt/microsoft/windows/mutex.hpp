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
///   File: mutex.hpp
///
/// Author: $author$
///   Date: 1/2/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_MT_MICROSOFT_WINDOWS_MUTEX_HPP
#define _NADIR_MT_MICROSOFT_WINDOWS_MUTEX_HPP

#include "nadir/mt/mutex.hpp"
#include "nadir/base/created.hpp"
#include "nadir/io/logger.hpp"

#if !defined(WINDOWS)
enum {
    WAIT_FAILED    = -1,
    WAIT_OBJECT_0  = 0,
    WAIT_ABANDONED = 0x80,
    WAIT_TIMEOUT   = 0x102
};
extern "C" {
HANDLE WINAPI CreateMutex(
  _In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,
  _In_     BOOL                  bInitialOwner,
  _In_opt_ LPCTSTR               lpName
);
BOOL WINAPI ReleaseMutex(
  _In_ HANDLE hMutex
);
DWORD WINAPI WaitForSingleObject(
  _In_ HANDLE hHandle,
  _In_ DWORD  dwMilliseconds
);
BOOL WINAPI CloseHandle(
  _In_ HANDLE hObject
);
DWORD WINAPI GetLastError(void);
}
#endif // !defined(WINDOWS)

namespace nadir {
namespace mt {
namespace microsoft {
namespace windows {

typedef HANDLE mutex_attached_t;

typedef creatort<mt::mutex> mutex_creator;
typedef attachert<mutex_attached_t, int, 0, mutex_creator> mutex_attacher;
typedef attachedt<mutex_attached_t, int, 0, mutex_attacher, base> mutex_attached;
typedef createdt<mutex_attached_t, int, 0, mutex_attacher, mutex_attached> mutex_created;
typedef mutex_attacher mutext_implements;
typedef mutex_created mutext_extends;
///////////////////////////////////////////////////////////////////////
///  Class: mutext
///////////////////////////////////////////////////////////////////////
template
<class TImplements = mutext_implements, class TExtends = mutext_extends>
class _EXPORT_CLASS mutext: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef typename Extends::attached_t attached_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    mutext
    (attached_t detached, bool is_created = false, bool is_logging = true)
    : Extends(detached, is_created), is_logging_(is_logging) {
    }
    mutext(bool is_logging = true): is_logging_(is_logging) {
        if (!(this->create())) {
            create_exception e(create_failed);
            IS_LOGGING_ERROR("...throwing create_exception e(create_failed)...")
            throw (e);
        }
    }
    virtual ~mutext() {
        if (!(this->destroyed())) {
            create_exception e(destroy_failed);
            IS_LOGGING_ERROR("...throwing create_exception e(destroy_failed)...")
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create() {
        if ((this->destroyed())) {
            attached_t detached = 0;
            if ((detached = this->create_detached())) {
                this->attach_created(detached);
                return true;
            }
        }
        return false;
    }
    virtual bool destroy() {
        attached_t detached = 0;
        if ((detached = this->detach())) {
            if ((this->destroy_detached(detached))) {
                return true;
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool lock() {
        return lock_success == untimed_lock();
    }
    virtual bool unlock() {
        attached_t detached = 0;
        if ((detached = this->attached_to())) {
            IS_LOGGING_DEBUG("ReleaseMutex(detached)...")
            if ((ReleaseMutex(detached))) {
                return true;
            } else {
                int error = GetLastError();
                IS_LOGGING_ERROR("...failed error = " << error << " on ReleaseMutex(detached)");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual lock_status try_lock() {
        return timed_lock(0);
    }
    virtual lock_status untimed_lock() {
        return timed_lock(-1);
    }
    virtual lock_status timed_lock(mseconds_t milliseconds) {
        attached_t detached = 0;
        if ((detached = this->attached_to())) {
            DWORD dwMilliseconds = (0 > milliseconds)?(INFINITE):((DWORD)milliseconds);
            DWORD dwResult = 0;
            if ((0 < milliseconds) && (500 > milliseconds)) {
                IS_LOGGING_TRACE("WaitForSingleObject(detached, dwMilliseconds)...");
            } else {
                IS_LOGGING_DEBUG("WaitForSingleObject(detached, dwMilliseconds)...");
            }
            if ((WAIT_OBJECT_0 == (dwResult = WaitForSingleObject(detached, dwMilliseconds)))) {
                if ((0 < milliseconds) && (500 > milliseconds)) {
                    IS_LOGGING_TRACE("...WaitForSingleObject(detached, dwMilliseconds)");
                } else {
                    IS_LOGGING_DEBUG("...WaitForSingleObject(detached, dwMilliseconds)");
                }
                return lock_success;
            } else {
                switch (dwResult) {
                case WAIT_TIMEOUT:
                    if ((0 < milliseconds) && (500 > milliseconds)) {
                        IS_LOGGING_TRACE("...failed WAIT_TIMEOUT on WaitForSingleObject(detached, dwMilliseconds)");
                    } else {
                        IS_LOGGING_DEBUG("...failed WAIT_TIMEOUT on WaitForSingleObject(detached, dwMilliseconds)");
                    }
                    return lock_busy;
                case WAIT_ABANDONED:
                    IS_LOGGING_ERROR("...failed WAIT_ABANDONED on WaitForSingleObject(detached, dwMilliseconds)");
                    return lock_interrupted;
                default:
                    IS_LOGGING_ERROR("...failed on WaitForSingleObject(detached, dwMilliseconds)");
                }
            }
        }
        return lock_failed;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual attached_t create_detached() const {
        LPSECURITY_ATTRIBUTES lpMutexAttributes = NULL;
        BOOL bInitialOwner = FALSE;
        LPCTSTR lpName = NULL;
        attached_t detached = 0;
        IS_LOGGING_DEBUG("CreateMutex(lpMutexAttributes, bInitialOwner, lpName)...");
        if ((detached = CreateMutex(lpMutexAttributes, bInitialOwner, lpName))) {
            return detached;
        } else {
            int error = GetLastError();
            IS_LOGGING_ERROR("...failed error = " << error << " on CreateMutex(lpMutexAttributes, bInitialOwner, lpName)");
        }
        return 0;
    }
    virtual bool destroy_detached(HANDLE hMutex) const {
        bool success = true;
        IS_LOGGING_DEBUG("CloseHandle(hMutex)...");
        if (!(CloseHandle(hMutex))) {
            int error = GetLastError();
            IS_LOGGING_ERROR("...failed error = " << error << " on CloseHandle(hMutex)");
            success = false;
        }
        return success;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    inline bool is_logging() const {
        return is_logging_;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool is_logging_;
};
typedef mutext<> mutex;

} // namespace windows 
} // namespace microsoft 
} // namespace mt 
} // namespace nadir 

#endif // _NADIR_MT_MICROSOFT_WINDOWS_MUTEX_HPP 
