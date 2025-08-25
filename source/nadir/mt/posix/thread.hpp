///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2018 $organization$
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
///   File: thread.hpp
///
/// Author: $author$
///   Date: 1/15/2018
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_MT_POSIX_THREAD_HPP
#define _NADIR_MT_POSIX_THREAD_HPP

#include "nadir/mt/posix/timed.hpp"
#include "nadir/mt/thread.hpp"
#include "nadir/io/logger.hpp"

#include <pthread.h>
#include <time.h>
#include <errno.h>

#if defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )
#if !defined(PTHREAD_HAS_TRYJOIN)
#define PTHREAD_HAS_TRYJOIN
#endif // !defined(PTHREAD_HAS_TRYJOIN)
#if !defined(PTHREAD_HAS_TIMEDJOIN)
#define PTHREAD_HAS_TIMEDJOIN
#endif // !defined(PTHREAD_HAS_TIMEDJOIN)
#else // defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )
//
// pthread_tryjoin_np
//
#if !defined(PTHREAD_HAS_TRYJOIN)
#define PTHREAD_HAS_TRYJOIN
#if !defined(pthread_tryjoin_np)
#define pthread_tryjoin_np(t, v) EINVAL
#endif // !defined(pthread_tryjoin_np)
#endif // !defined(PTHREAD_HAS_TRYJOIN)
//
// pthread_timedjoin_np
//
#if !defined(PTHREAD_HAS_TIMEDJOIN)
#define PTHREAD_HAS_TIMEDJOIN
#if !defined(pthread_timedjoin_np)
#define pthread_timedjoin_np(t, v, u) EINVAL
#endif // !defined(pthread_timedjoin_np)
#endif // !defined(PTHREAD_HAS_TIMEDJOIN)
#endif // defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )

namespace nadir {
namespace mt {
namespace posix {

typedef pthread_t* thread_attached_t;

typedef creatort<mt::thread> thread_creator;
typedef attachert<thread_attached_t, int, 0, thread_creator> thread_attacher;
typedef attachedt<thread_attached_t, int, 0, thread_attacher, base> thread_attached;
typedef createdt<thread_attached_t, int, 0, thread_attacher, thread_attached> thread_created;
typedef thread_attacher threadt_implements;
typedef thread_created threadt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: threadt
///////////////////////////////////////////////////////////////////////
template 
<class TImplements = threadt_implements, class TExtends = threadt_extends>

class _EXPORT_CLASS threadt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef typename Implements::ran_t ran_t;
    typedef typename Implements::attached_t attached_t;
    typedef typename Implements::unattached_t unattached_t;
    enum { unattached = Implements::unattached };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    threadt(ran_t& ran, attached_t attached, bool forked = false)
    : Extends(attached, forked), ran_(ran), forked_(forked) {
    }
    threadt(attached_t attached, bool forked = false)
    : Extends(attached, forked), ran_(*this), forked_(forked) {
    }
    threadt(ran_t& ran): ran_(ran), forked_(false) {
        if (!(this->create())) {
            create_exception e(create_failed);
            throw (e);
        }
    }
    threadt(): ran_(*this), forked_(false) {
        if (!(this->create())) {
            create_exception e(create_failed);
            throw (e);
        }
    }
    virtual ~threadt() {
        if (!(this->destroyed())) {
            create_exception e(destroy_failed);
            throw (e);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create(bool initially_suspended) {
        if (!(initially_suspended)) {
            return this->create();
        }
        return false;
    }
    virtual bool create() {
        pthread_t* detached = 0;
        if ((detached = create_attached())) {
            this->set_is_created();
            return forked_ = true;
        }
        return false;
    }
    virtual bool destroy() {
        if ((this->joined())) {
            this->detach();
            return true;
        }
        return false;
    }
    virtual pthread_t* create_attached() {
        pthread_t* detached = 0;
        if ((this->destroyed())) {
            if ((detached = create_detached(threadattr_, thread_))) {
                this->attach(detached);
                return detached;
            }
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool join() {
        pthread_t* thread = 0;
        if ((thread = this->attached_to())) {
            return join_detached(forked_, thread);
        }
        return false;
    }
    virtual join_status untimed_join() {
        pthread_t* thread = 0;
        if ((thread = this->attached_to())) {
            return untimed_join_detached(forked_, thread);
        }
        return join_failed;
    }
    virtual join_status timed_join(mseconds_t milliseconds) {
        pthread_t* thread = 0;
        if ((thread = this->attached_to())) {
            return timed_join_detached(forked_, thread, milliseconds);
        }
        return join_failed;
    }
    virtual join_status try_join() {
        pthread_t* thread = 0;
        if ((thread = this->attached_to())) {
            return try_join_detached(forked_, thread);
        }
        return join_failed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual pthread_t* create_detached
    (pthread_attr_t& threadattr, pthread_t& thread) const {
        int err = 0;

        LOG_DEBUG("pthread_attr_init(&threadattr)...");
        if (!(err = pthread_attr_init(&threadattr))) {

            LOG_DEBUG("pthread_create(&thread, &threadattr, start_routine, ((void*)this))...");
            if (!(err = pthread_create(&thread, &threadattr, start_routine, ((void*)this)))) {

                LOG_DEBUG("pthread_attr_destroy(&threadattr)...");
                if ((err = pthread_attr_destroy(&threadattr))) {
                    bool forked = true;
                    join_detached(forked, &thread);
                    return 0;
                }
                return &thread;
            }
            if ((err = pthread_attr_destroy(&threadattr))) {
            }
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool join_detached(bool& forked, pthread_t* thread) const {
        if (join_success == (untimed_join_detached(forked, thread))) {
            return true;
        }
        return false;
    }
    virtual join_status untimed_join_detached(bool& forked, pthread_t* thread) const {
        if ((thread)) {
            void* value = 0;
            int err = 0;
            LOG_DEBUG("pthread_join(*thread, &value)...");
            if (!(err = pthread_join(*thread, &value))) {
                LOG_DEBUG("...pthread_join(*thread, &value)");
                forked = false;
                return join_success;
            } else {
                switch(err) {
                case ETIMEDOUT:
                    LOG_ERROR("...ETIMEDOUT err = " << err << " on pthread_join(*thread, &value)");
                    return join_busy;
                case EINTR:
                    LOG_ERROR("...EINTR err = " << err << " on pthread_join(*thread, &value)");
                    return join_interrupted;
                default:
                    LOG_ERROR("...failed err = " << err << " on pthread_join(*thread, &value)");
                    forked = false;
                }
            }
        }
        return join_failed;
    }
    virtual join_status timed_join_detached
    (bool& forked, pthread_t* thread, mseconds_t milliseconds) const {
        if (0 < (milliseconds)) {
#if defined(PTHREAD_HAS_TIMEDJOIN)
            struct timespec until_time = timed_until_time(milliseconds);
            void* value = 0;
            int err = 0;
            LOG_TRACE("pthread_timedjoin_np(*thread, &value, &until_time)...");
            if (!(err =  pthread_timedjoin_np(*thread, &value, &until_time))) {
                forked = false;
                return join_success;
            } else {
                switch(err) {
                case ETIMEDOUT:
                    LOG_TRACE("...ETIMEDOUT err = "<< err << " on pthread_timedjoin_np(*thread, &value, &untilTime)");
                    return join_busy;
                case EINTR:
                    LOG_ERROR("...EINTR err = "<< err << " on pthread_timedjoin_np(*thread, &value, &untilTime)");
                    return join_interrupted;
                default:
                    LOG_ERROR("...failed err = "<< err << " on pthread_timedjoin_np(*thread, &value, &untilTime)");
                    forked = false;
                    return join_failed;
                }
            }
#else // defined(PTHREAD_HAS_TIMEDJOIN)
            LOG_ERROR("...return join_invalid");
            return join_invalid;
#endif // defined(PTHREAD_HAS_TIMEDJOIN)
        } else {
            if (0 > (milliseconds)) {
                return untimed_join_detached(forked, thread);
            } else {
                return try_join_detached(forked, thread);
            }
        }
        return join_failed;
    }
    virtual join_status try_join_detached(bool& forked, pthread_t* thread) const {
#if defined(PTHREAD_HAS_TRYJOIN)
        void* value = 0;
        int err = 0;
        LOG_TRACE("pthread_tryjoin_np(*thread, &value)...");
        if (!(err =  pthread_tryjoin_np(*thread, &value))) {
            forked = false;
            return join_success;
        } else {
            switch(err) {
            case ETIMEDOUT:
                LOG_TRACE("...ETIMEDOUT err = "<< err << " on pthread_tryjoin_np(*thread, &value)");
                return join_busy;
            case EINTR:
                LOG_ERROR("...EINTR err = "<< err << " on pthread_tryjoin_np(*thread, &value)");
                return join_interrupted;
            default:
                LOG_ERROR("...failed err = "<< err << " on pthread_tryjoin_np(*thread, &value)");
                forked = false;
                return join_failed;
            }
        }
        return join_failed;
#else // defined(PTHREAD_HAS_TRYJOIN)
        LOG_ERROR("...return join_invalid");
        return join_invalid;
#endif // defined(PTHREAD_HAS_TRYJOIN)
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_is_forked(bool to = true) {
        forked_ = to;
        return forked_;
    }
    virtual bool is_forked() const {
        return forked_;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual pthread_t* detach() {
        forked_ = false;
        return Extends::detach();
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void run() {
        LOG_DEBUG("...");
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static void* start_routine(void* param) {
        void* result = 0;
        threadt* t = 0;
        LOG_DEBUG("in...");
        if ((t = ((threadt*)param))) {
            LOG_DEBUG("t->ran_.run()...");
            t->ran_.run();
            LOG_DEBUG("...t->ran_.run()");
        } else {
            LOG_ERROR("...unexpected 0 = ((threadt*)param)");
        }
        LOG_DEBUG("...out");
        return result;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    ran_t& ran_;
    bool forked_;
    pthread_t thread_;
    pthread_attr_t threadattr_;
};
typedef threadt<> thread;

} // namespace posix 
} // namespace mt 
} // namespace nadir 

#endif // _NADIR_MT_POSIX_THREAD_HPP 
