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
///   File: semaphore.hpp
///
/// Author: $author$
///   Date: 1/2/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_MT_MICROSOFT_WINDOWS_SEMAPHORE_HPP
#define _NADIR_MT_MICROSOFT_WINDOWS_SEMAPHORE_HPP

#include "nadir/mt/semaphore.hpp"
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

typedef HANDLE semaphore_attached_t;

typedef creatort<mt::semaphore> semaphore_creator;
typedef attachert<semaphore_attached_t, int, 0, semaphore_creator> semaphore_attacher;
typedef attachedt<semaphore_attached_t, int, 0, semaphore_attacher, base> semaphore_attached;
typedef createdt<semaphore_attached_t, int, 0, semaphore_attacher, semaphore_attached> semaphore_created;
typedef semaphore_creator semaphoret_implements;
typedef semaphore_created semaphoret_extends;
///////////////////////////////////////////////////////////////////////
///  Class: semaphoret
///////////////////////////////////////////////////////////////////////
template
<class TImplements = semaphoret_implements, class TExtends = semaphoret_extends>
class _EXPORT_CLASS semaphoret: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef typename Extends::attached_t attached_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    semaphoret
    (attached_t detached, bool is_created = false, bool is_logging = true)
    : Extends(detached, is_created), is_logging_(is_logging) {
    }
    semaphoret(bool is_logging = true): is_logging_(is_logging) {
        if (!(this->create())) {
            create_exception e(create_failed);
            IS_LOGGING_ERROR("...throwing create_exception e(create_failed)...")
            throw (e);
        }
    }
    virtual ~semaphoret() {
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
    virtual bool acquire() {
        return acquire_success == untimed_acquire();
    }
    virtual bool release() {
        return release(1);
    }
    virtual bool release(size_t amount) {
        attached_t detached = 0;
        if ((detached = this->attached_to())) {
            LONG lReleaseCount = ((LONG)amount);
            LONG lPreviousCount = 0;
            IS_LOGGING_DEBUG("ReleaseSemaphore(detached, lReleaseCount, &lPreviousCount)...");
            if ((ReleaseSemaphore(detached, lReleaseCount, &lPreviousCount))) {
                return true;
            } else {
                int error = GetLastError();
                IS_LOGGING_ERROR("...failed error = " << error << " on ReleaseSemaphore(detached, lReleaseCount, &lPreviousCount)");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual acquire_status try_acquire() {
        return timed_acquire(0);
    }
    virtual acquire_status untimed_acquire() {
        return timed_acquire(-1);
    }
    virtual acquire_status timed_acquire(mseconds_t milliseconds) {
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
                return acquire_success;
            } else {
                switch (dwResult) {
                case WAIT_TIMEOUT:
                    if ((0 < milliseconds) && (500 > milliseconds)) {
                        IS_LOGGING_TRACE("...failed WAIT_TIMEOUT on WaitForSingleObject(detached, dwMilliseconds)");
                    } else {
                        IS_LOGGING_DEBUG("...failed WAIT_TIMEOUT on WaitForSingleObject(detached, dwMilliseconds)");
                    }
                    return acquire_busy;
                case WAIT_ABANDONED:
                    IS_LOGGING_ERROR("...failed WAIT_ABANDONED on WaitForSingleObject(detached, dwMilliseconds)");
                    return acquire_interrupted;
                default:
                    IS_LOGGING_ERROR("...failed on WaitForSingleObject(detached, dwMilliseconds)");
                }
            }
        }
        return acquire_failed;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual attached_t create_detached() const {
        return create_detached(0, -1);
    }
    virtual attached_t create_detached
    (size_t initial_count, ssize_t maximum_count) const {
        LONG lInitialCount = ((LONG)initial_count);
        LONG lMaximumCount = ((LONG)(0 > maximum_count)?(((ULONG)(-1))>>1):(maximum_count));
        LPSECURITY_ATTRIBUTES lpSecurityAttributes = 0;
        LPCTSTR lpName = 0;
        attached_t detached = 0;

        IS_LOGGING_DEBUG("CreateSemaphore(lpSecurityAttributes, lInitialCount, lMaximumCount, lpName)...");
        if ((detached = CreateSemaphore
            (lpSecurityAttributes, lInitialCount, lMaximumCount, lpName))) {
            return detached;
        } else {
            int error = GetLastError();
            IS_LOGGING_ERROR("...failed error = " << error << " on CreateSemaphore(lpSecurityAttributes, lInitialCount, lMaximumCount, lpName)");
        }
        return 0;
    }
    virtual bool destroy_detached(HANDLE hSemaphore) const {
        bool success = true;
        IS_LOGGING_DEBUG("CloseHandle(hSemaphore)...");
        if (!(CloseHandle(hSemaphore))) {
            int error = GetLastError();
            IS_LOGGING_ERROR("...failed error = " << error << " on CloseHandle(hSemaphore)");
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
typedef semaphoret<> semaphore;

} // namespace windows 
} // namespace microsoft 
} // namespace mt 
} // namespace nadir 

#endif // _NADIR_MT_MICROSOFT_WINDOWS_SEMAPHORE_HPP 
        

