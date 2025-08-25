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
///   Date: 1/1/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_MT_POSIX_MUTEX_HPP
#define _NADIR_MT_POSIX_MUTEX_HPP

#include "nadir/mt/posix/timed.hpp"
#include "nadir/mt/mutex.hpp"
#include "nadir/base/created.hpp"
#include "nadir/io/logger.hpp"

#include <pthread.h>
#include <time.h>
#include <errno.h>

#if defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )
#define PTHREAD_MUTEX_HAS_TIMEDLOCK
#else // defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )
#define PTHREAD_MUTEX_HAS_TIMEDLOCK
#if !defined(pthread_mutex_timedlock)
#define pthread_mutex_timedlock(m, t) EINVAL
#endif // 
#endif // defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )

namespace nadir {
namespace mt {
namespace posix {

typedef pthread_mutexattr_t mutexattr_t;
typedef pthread_mutex_t mutex_t;
typedef mutex_t* mutex_attached_t;

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
    (attached_t detached, bool is_created = false,
     bool is_logging = true, bool is_stderr_logging = true)
    : Extends(detached, is_created),
      is_logging_(is_logging), is_stderr_logging_(is_stderr_logging) {
    }
    mutext
    (bool is_logging = true, bool is_stderr_logging = true)
    : is_logging_(is_logging), is_stderr_logging_(is_stderr_logging) {
        if (!(this->create())) {
            create_exception e(create_failed);
            throw (e);
        }
    }
    virtual ~mutext() {
        if (!(this->destroyed())) {
            create_exception e(destroy_failed);
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create() {
        if ((this->destroyed())) {
            attached_t detached = 0;
            if ((detached = this->create_detached(mutex_))) {
                this->attach_created(detached);
                return true;
            }
        }
        return false;
    }
    virtual bool destroy() {
        attached_t detached = 0;
        if ((detached = this->detach())) {
            if ((this->destroy_detached(*detached))) {
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
            int err = 0;
            IS_LOGGING_DEBUG("pthread_mutex_unlock(detached)...");
            if (!(err = pthread_mutex_unlock(detached))) {
                return true;
            } else {
                IS_LOGGING_ERROR("...failed err =" << err << " on pthread_mutex_unlock(detached)");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual lock_status try_lock() {
        attached_t detached = 0;
        if ((detached = this->attached_to())) {
            int err = 0;
            IS_LOGGING_TRACE("pthread_mutex_trylock(detached)...");
            if (!(err = pthread_mutex_trylock(detached))) {
                IS_LOGGING_TRACE("...pthread_mutex_trylock(detached)");
                return lock_success;
            } else {
                if (ETIMEDOUT != (err)) {
                    if (EINTR != (err)) {
                        IS_LOGGING_ERROR("...failed err = " << err << " on pthread_mutex_trylock(detached)");
                    } else {
                        IS_LOGGING_ERROR("...failed EINTR err = " << err << " on pthread_mutex_trylock(detached)");
                        return lock_interrupted;
                    }
                } else {
                    IS_LOGGING_TRACE("...failed ETIMEDOUT err = " << err << " on pthread_mutex_trylock(detached)");
                    return lock_busy;
                }
            }
        }
        return lock_failed;
    }
    virtual lock_status untimed_lock() {
        attached_t detached = 0;
        if ((detached = this->attached_to())) {
            int err = 0;
            IS_LOGGING_DEBUG("pthread_mutex_lock(detached)...");
            if (!(err = pthread_mutex_lock(detached))) {
                IS_LOGGING_DEBUG("...pthread_mutex_lock(detached)");
                return lock_success;
            } else {
                if (EINTR != (err)) {
                    IS_LOGGING_ERROR("...failed err = " << err << " on pthread_mutex_lock(detached)");
                } else {
                    IS_LOGGING_ERROR("...failed EINTR err = " << err << " on pthread_mutex_lock(detached)");
                    return lock_interrupted;
                }
            }
        }
        return lock_failed;
    }
    virtual lock_status timed_lock(mseconds_t milliseconds) {
        lock_status status = lock_failed;
        if (0 > milliseconds) {
            status = untimed_lock();
        } else {
#if defined(PTHREAD_MUTEX_HAS_TIMEDLOCK)
            attached_t detached = 0;
            if ((detached = this->attached_to())) {
                struct timespec until_time = timed_until_time(milliseconds);
                int err = 0;
                /*struct timespec until_time;

                clock_gettime(CLOCK_REALTIME, &until_time);
                until_time.tv_sec +=  milliseconds/1000;
                until_time.tv_nsec +=  (milliseconds%1000)*1000;
                */
                if (500 > milliseconds) {
                    IS_LOGGING_TRACE("pthread_mutex_timedlock(detached, &until_time)...");
                } else {
                    IS_LOGGING_DEBUG("pthread_mutex_timedlock(detached, &until_time)...");
                }
                if (!(err = pthread_mutex_timedlock(detached, &until_time))) {
                    if (500 > milliseconds) {
                        IS_LOGGING_TRACE("...pthread_mutex_timedlock(detached, &until_time)");
                    } else {
                        IS_LOGGING_DEBUG("...pthread_mutex_timedlock(detached, &until_time)");
                    }
                    return lock_success;
                } else {
                    if (ETIMEDOUT != (err)) {
                        if (EINTR != (err)) {
                            IS_LOGGING_ERROR("...failed err = " << err << " on pthread_mutex_timedlock(detached, &until_time)");
                        } else {
                            IS_LOGGING_ERROR("...failed EINTR err = " << err << " on pthread_mutex_timedlock(detached, &until_time)");
                            return lock_interrupted;
                        }
                    } else {
                        if (500 > milliseconds) {
                            IS_LOGGING_TRACE("...failed ETIMEDOUT err = " << err << " on pthread_mutex_timedlock(detached, &until_time)");
                        } else {
                            IS_LOGGING_DEBUG("...failed ETIMEDOUT err = " << err << " on pthread_mutex_timedlock(detached, &until_time)");
                        }
                        return lock_busy;
                    }
                }
            }
#else // defined(PTHREAD_MUTEX_HAS_TIMEDLOCK)
            if (milliseconds) {
                IS_LOGGING_ERROR("...invalid pthread_mutex_timedlock(detached, ...)");
                status = lock_invalid;
            } else {
                status = try_lock();
            }
#endif // defined(PTHREAD_MUTEX_HAS_TIMEDLOCK)
        }
        return status;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual attached_t create_detached(mutex_t& mutex) const {
        int err = 0;
        mutexattr_t mutexattr;
        IS_STDERR_LOGGING_DEBUG("pthread_mutexattr_init(&mutexattr)...");
        if (!(err = pthread_mutexattr_init(&mutexattr))) {
            IS_STDERR_LOGGING_DEBUG("pthread_mutex_init(&mutex, &mutexattr)...");
            if (!(err = pthread_mutex_init(&mutex, &mutexattr))) {
                IS_STDERR_LOGGING_DEBUG("pthread_mutexattr_destroy(&mutexattr)...");
                if (!(err = pthread_mutexattr_destroy(&mutexattr))) {
                    return &mutex;
                } else {
                    IS_STDERR_LOGGING_ERROR("...failed err =" << err << " on pthread_mutexattr_destroy(&mutexattr)");
                    IS_STDERR_LOGGING_DEBUG("pthread_mutex_destroy(&mutex)...");
                    if ((err = pthread_mutex_destroy(&mutex))) {
                        IS_STDERR_LOGGING_ERROR("...failed err = " << err << " on pthread_mutex_destroy(&mutex)");
                    }
                }
            } else {
                IS_STDERR_LOGGING_ERROR("...failed err = " << err << " on pthread_mutex_init(&mutex, &mutexattr)");
                IS_STDERR_LOGGING_DEBUG("pthread_mutexattr_destroy(&mutexattr)...");
                if ((err = pthread_mutexattr_destroy(&mutexattr))) {
                    IS_STDERR_LOGGING_ERROR("...failed err =" << err << " on pthread_mutexattr_destroy(&mutexattr)");
                }
            }
        } else {
            IS_STDERR_LOGGING_ERROR("...failed err =" << err << " on pthread_mutexattr_init(&mutexattr)");
        }
        return 0;
    }
    virtual bool destroy_detached(mutex_t& mutex) const {
        bool success = true;
        int err = 0;
        IS_STDERR_LOGGING_DEBUG("pthread_mutex_destroy(&mutex)...");
        if ((err = pthread_mutex_destroy(&mutex))) {
            IS_STDERR_LOGGING_ERROR("...failed err = " << err << " on pthread_mutex_destroy(&mutex)");
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
    inline bool is_stderr_logging() const {
        return is_stderr_logging_;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool is_logging_, is_stderr_logging_;
    mutex_t mutex_;
};
typedef mutext<> mutex;

} // namespace posix
} // namespace mt 
} // namespace nadir 

#endif // _NADIR_MT_POSIX_MUTEX_HPP 
