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
#ifndef _NADIR_MT_APPLE_MACH_SEMAPHORE_HPP
#define _NADIR_MT_APPLE_MACH_SEMAPHORE_HPP

#include "nadir/mt/semaphore.hpp"
#include "nadir/base/created.hpp"
#include "nadir/io/logger.hpp"

#include <mach/task.h>
#include <mach/mach.h>
#include <mach/semaphore.h>

namespace nadir {
namespace mt {
namespace apple {
namespace mach {

typedef semaphore_t* semaphore_attached_t;

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
            IS_LOGGING_DEBUG("semaphore_signal(*detached)...");
            if (KERN_SUCCESS == (err = semaphore_signal(*detached))) {
                return true;
            } else {
                IS_LOGGING_ERROR("...failed err = " << err << " on semaphore_signal(*detached)");
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
        attached_t detached = 0;
        if ((detached = this->attached_to())) {
            int err = 0;
            IS_LOGGING_DEBUG("semaphore_wait(*detached)...");
            if (KERN_SUCCESS == (err = semaphore_wait(*detached))) {
                IS_LOGGING_DEBUG("...semaphore_wait(*detached)");
                return acquire_success;
            } else {
                if (KERN_ABORTED == (err)) {
                    IS_LOGGING_ERROR("...failed KERN_ABORTED err = " << err << " on semaphore_wait(*detached)");
                    return acquire_interrupted;
                } else {
                    IS_LOGGING_ERROR("...failed err = " << err << " on semaphore_wait(*detached)");
                }
            }
        }
        return acquire_failed;
    }
    virtual acquire_status timed_acquire(mseconds_t milliseconds) {
        if (0 > milliseconds) {
            return untimed_acquire();
        } else {
            attached_t detached = 0;
            if ((detached = this->attached_to())) {
                int err = 0;
                mach_timespec_t wait_time;

                wait_time.tv_sec = milliseconds/1000;
                wait_time.tv_nsec = (milliseconds%1000)*1000;

                if (500 > milliseconds) {
                    IS_LOGGING_TRACE("semaphore_timedwait(*detached, wait_time)...");
                } else {
                    IS_LOGGING_DEBUG("semaphore_timedwait(*detached, wait_time)...");
                }
                if (KERN_SUCCESS == (err = semaphore_timedwait(*detached, wait_time))) {
                    if (500 > milliseconds) {
                        IS_LOGGING_TRACE("...semaphore_timedwait(*detached, wait_time)");
                    } else {
                        IS_LOGGING_DEBUG("...semaphore_timedwait(*detached, wait_time)");
                    }
                    return acquire_success;
                } else {
                    if (KERN_OPERATION_TIMED_OUT == (err)) {
                        if (500 > milliseconds) {
                            IS_LOGGING_TRACE("...failed KERN_OPERATION_TIMED_OUT err = " << err << " on semaphore_timedwait(*detached, wait_time)");
                        } else {
                            IS_LOGGING_DEBUG("...failed KERN_OPERATION_TIMED_OUT err = " << err << " on semaphore_timedwait(*detached, wait_time)");
                        }
                        return acquire_busy;
                    } else {
                        if (KERN_ABORTED == (err)) {
                            IS_LOGGING_ERROR("...failed KERN_ABORTED err = " << err << " on semaphore_timedwait(*detached, wait_time)");
                            return acquire_interrupted;
                        } else {
                            IS_LOGGING_ERROR("...failed err = " << err << " on semaphore_timedwait(*detached, wait_time)");
                        }
                    }
                }
            }
        }
        return acquire_failed;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual attached_t create_detached(semaphore_t& sem) const {
        return create_detached(sem, 0);
    }
    virtual attached_t create_detached
    (semaphore_t& sem, size_t initial_count) const {
        task_t task = mach_task_self();
        sync_policy_t sync_policy = SYNC_POLICY_FIFO;
        int err = 0;
        IS_LOGGING_DEBUG("semaphore_create(task, &sem, sync_policy, initial_count)...");
        if ((KERN_SUCCESS == (err = semaphore_create(task, &sem, sync_policy, initial_count)))) {
            return &sem;
        } else {
            IS_LOGGING_ERROR("...failed err = " << err << " on semaphore_create(task, &sem, sync_policy, initial_count)");
        }
        return 0;
    }
    virtual bool destroy_detached(semaphore_t& sem) const {
        bool success = true;
        task_t task = mach_task_self();
        int err = 0;
        IS_LOGGING_DEBUG("semaphore_destroy(task, sem)...");
        if (KERN_SUCCESS != (err = semaphore_destroy(task, sem))) {
            IS_LOGGING_ERROR("...failed err = " << err << " on semaphore_destroy(task, sem)");
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
    semaphore_t sem_;
};
typedef semaphoret<> semaphore;

} // namespace mach 
} // namespace apple 
} // namespace mt 
} // namespace nadir 

#endif // _NADIR_MT_APPLE_MACH_SEMAPHORE_HPP 
