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
///   Date: 1/16/2018
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_APP_CONSOLE_NADIR_THREAD_HPP
#define _NADIR_APP_CONSOLE_NADIR_THREAD_HPP

#include "nadir/mt/os/thread.hpp"
#include "nadir/mt/thread.hpp"
#include "nadir/base/ran.hpp"

namespace nadir {
namespace app {
namespace console {
namespace nadir {

typedef ::nadir::mt::os::thread::ran_t thread_ran_implements;
///////////////////////////////////////////////////////////////////////
///  Class: thread_ran
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS thread_ran: virtual public thread_ran_implements {
public:
    typedef thread_ran_implements Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void thread_run() {
        Implements::run();
    }
    virtual void run() {
        thread_run();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef ::nadir::mt::os::thread thread_extends;
///////////////////////////////////////////////////////////////////////
///  Class: thread
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS thread: public thread_extends {
public:
    typedef thread_extends Extends;
    thread(thread_ran& ran, bool created = true): Extends(ran, (attached_t)unattached) {
        if ((created)) {
            if (!(this->create())) {
                create_exception e(create_failed);
                throw (e);
            }
        }
    }
    thread(bool created = true): Extends((attached_t)unattached) {
        if ((created)) {
            if (!(this->create())) {
                create_exception e(create_failed);
                throw (e);
            }
        }
    }
    virtual ~thread() {
        if (!(this->destroyed())) {
            create_exception e(destroy_failed);
            throw (e);
        }
    }
};
typedef implement_base thread_array_extends;
///////////////////////////////////////////////////////////////////////
///  Class: thread_array
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS thread_array: public thread_array_extends {
public:
    typedef thread_array_extends Extends;
    thread_array(size_t n, thread_ran& r): t_(0), n_(0) {
        construct(n, &r);
    }
    thread_array(size_t n): t_(0), n_(0) {
        construct(n);
    }
    virtual ~thread_array() {
        destruct();
    }
    virtual thread_array& construct(size_t n, thread_ran* r = 0) {
        if ((n)) {
            LOG_DEBUG("new thread*[n_ = " << n << "]...");
            if ((t_ = new thread*[n_ = n])) {
                LOG_DEBUG("...new thread*[n_ = " << n << "]");
                for (n = 0; n < n_; ++n) {
                    LOG_DEBUG("try {...");
                    try {
                        LOG_DEBUG("t_[n = " << n << "] = new thread()...");
                        t_[n] = (r)?(new thread(*r)):(new thread());
                        LOG_DEBUG("...t_[n = " << n << "] = new thread()");
                    } catch (...) {
                        LOG_ERROR("...catch (...)");
                        break;
                    }
                }
            }
        }
        return *this;
    }
    virtual thread_array& destruct() {
        if ((t_) && (n_)) {
            for (thread* t = 0; n_; --n_) {
                if ((t = t_[n_-1])) {
                    LOG_DEBUG("try {...");
                    try {
                        LOG_DEBUG("delete t...");
                        delete t;
                        LOG_DEBUG("...delete t");
                    } catch (...) {
                        LOG_ERROR("...catch (...)");
                    }
                }
            }
            LOG_DEBUG("try {...");
            try {
                LOG_DEBUG("delete t_...");
                delete t_;
                LOG_DEBUG("...delete t_");
            } catch (...) {
                LOG_ERROR("...catch (...)");
            }
        }
        return *this;
    }
protected:
    thread** t_;
    size_t n_;
};

} // namespace nadir 
} // namespace console 
} // namespace app 
} // namespace nadir 

#endif // _NADIR_APP_CONSOLE_NADIR_THREAD_HPP 
