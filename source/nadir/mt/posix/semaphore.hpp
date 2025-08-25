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
#ifndef _NADIR_MT_POSIX_SEMAPHORE_HPP
#define _NADIR_MT_POSIX_SEMAPHORE_HPP

#include "nadir/mt/posix/timed.hpp"
#include "nadir/mt/semaphore.hpp"
#include "nadir/base/created.hpp"
#include "nadir/io/logger.hpp"

#include <semaphore.h>
#include <errno.h>

#if defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )
#define SEM_HAS_TIMEDWAIT
#endif // defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )

#define SEMAPHORE_PROCESS_PRIVATE 0
#define SEMAPHORE_PROCESS_SHARED  1

namespace nadir {
namespace mt {
namespace posix {

typedef sem_t* semaphore_attached_t;

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
            throw (e);
        }
    }
    virtual ~semaphoret() {
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
            if ((detached = this->create_detached(sem_))) {
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
    virtual bool acquire() {
        return acquire_success == untimed_acquire();
    }
    virtual bool release() {
        attached_t detached = 0;
        if ((detached = this->attached_to())) {
            int err = 0;
            IS_LOGGING_DEBUG("sem_post(detached)...");
            if (!(err = sem_post(detached))) {
                return true;
            } else {
                IS_LOGGING_ERROR("...failed errno = " << errno << " on sem_post(detached)");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual acquire_status try_acquire() {
        attached_t detached = 0;
        if ((detached = this->attached_to())) {
            int err = 0;
            IS_LOGGING_TRACE("sem_trywait(detached)...");
            if (!(err = sem_trywait(detached))) {
                IS_LOGGING_TRACE("...sem_trywait(detached)");
                return acquire_success;
            } else {
                if (EAGAIN == (errno)) {
                    IS_LOGGING_TRACE("...failed EAGAIN errno = " << errno << " on sem_trywait(detached)");
                    return acquire_busy;
                } else {
                    if (EINTR == (errno)) {
                        IS_LOGGING_ERROR("...failed EINTR errno = " << errno << " on sem_trywait(detached)");
                        return acquire_interrupted;
                    } else {
                        IS_LOGGING_ERROR("...failed errno = " << errno << " on sem_trywait(detached)");
                    }
                }
            }
        }
        return acquire_failed;
    }
    virtual acquire_status untimed_acquire() {
        attached_t detached = 0;
        if ((detached = this->attached_to())) {
            int err = 0;
            IS_LOGGING_DEBUG("sem_wait(detached)...");
            if (!(err = sem_wait(detached))) {
                IS_LOGGING_DEBUG("...sem_wait(detached)");
                return acquire_success;
            } else {
                if (EINTR == (errno)) {
                    IS_LOGGING_ERROR("...failed EINTR errno = " << errno << " on sem_wait(detached)");
                    return acquire_interrupted;
                } else {
                    IS_LOGGING_ERROR("...failed errno = " << errno << " on sem_wait(detached)");
                }
            }
        }
        return acquire_failed;
    }
    virtual acquire_status timed_acquire(mseconds_t milliseconds) {
        acquire_status status = acquire_failed;
        if (0 > milliseconds) {
            status = untimed_acquire();
        } else {
#if defined(SEM_HAS_TIMEDWAIT)
            attached_t detached = 0;
            if ((detached = this->attached_to())) {
                struct timespec until_time = timed_until_time(milliseconds);
                int err = 0;
                /*struct timespec until_time;

                clock_gettime(CLOCK_REALTIME, &until_time);
                until_time.tv_sec += milliseconds/1000;
                until_time.tv_nsec += (milliseconds%1000)*1000;
                */
                if (500 > milliseconds) {
                    IS_LOGGING_TRACE("sem_timedwait(detached, &until_time)...");
                } else {
                    IS_LOGGING_DEBUG("sem_timedwait(detached, &until_time)...");
                }
                if (!(err = sem_timedwait(detached, &until_time))) {
                    if (500 > milliseconds) {
                        IS_LOGGING_TRACE("...sem_timedwait(detached, &until_time)");
                    } else {
                        IS_LOGGING_DEBUG("...sem_timedwait(detached, &until_time)");
                    }
                    return acquire_success;
                } else {
                    if (ETIMEDOUT != (errno)) {
                        if (EINTR != (errno)) {
                            IS_LOGGING_ERROR("...failed errno = " << errno << " on sem_timedwait(detached, &until_time)");
                        } else {
                            IS_LOGGING_ERROR("...failed EINTR errno = " << errno << " on sem_timedwait(detached, &until_time)");
                            return acquire_interrupted;
                        }
                    } else {
                        if (500 > milliseconds) {
                            IS_LOGGING_TRACE("...failed ETIMEDOUT errno = " << errno << " on sem_timedwait(detached, &until_time)");
                        } else {
                            IS_LOGGING_DEBUG("...failed ETIMEDOUT errno = " << errno << " on sem_timedwait(detached, &until_time)");
                        }
                        return acquire_busy;
                    }
                }
            }
#else // defined(SEM_HAS_TIMEDWAIT)
            if (milliseconds) {
                IS_LOGGING_ERROR("...invalid sem_timedwait(detached, ...)");
                status = acquire_invalid;
            } else {
                status = try_acquire();
            }
#endif // defined(SEM_HAS_TIMEDWAIT)
        }
        return status;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual attached_t create_detached(sem_t& sem) const {
        return create_detached(sem, 0);
    }
    virtual attached_t create_detached(sem_t& sem, size_t initial_count) const {
        int pshared = SEMAPHORE_PROCESS_PRIVATE;
        int err = 0;
        IS_LOGGING_DEBUG("sem_init(&sem_, pshared, initial_count)...");
        if (!(err = sem_init(&sem, pshared, initial_count))) {
            return &sem;
        } else {
            IS_LOGGING_ERROR("...failed errno = " << errno << " on sem_init(&sem_, pshared, initial_count)");
        }
        return 0;
    }
    virtual bool destroy_detached(sem_t& sem) const {
        bool success = true;
        int err = 0;
        IS_LOGGING_DEBUG("sem_destroy(sem)...");
        if ((err = sem_destroy(&sem))) {
            IS_LOGGING_ERROR("...failed errno = " << errno << " on sem_destroy(sem)");
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
    sem_t sem_;
};
typedef semaphoret<> semaphore;

} // namespace posix 
} // namespace mt 
} // namespace nadir 

#endif // _NADIR_MT_POSIX_SEMAPHORE_HPP 
