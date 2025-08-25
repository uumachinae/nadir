///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2019 $organization$
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
///   File: suspended.hpp
///
/// Author: $author$
///   Date: 1/21/2020
///////////////////////////////////////////////////////////////////////
#ifndef XOS_BASE_SUSPENDED_HPP
#define XOS_BASE_SUSPENDED_HPP

#include "xos/base/resumed.hpp"

namespace xos {

/// enum suspend_status
typedef int suspend_status;
enum {
    /// suspend...
    suspend_success = resume_success,
    suspend_failed = next_resume,
    suspend_busy,
    suspend_timeout,
    suspend_interrupted,
    next_suspend,
    first_suspend = suspend_failed,
    last_suspend = suspend_interrupted,
}; /// enum suspend_status

/// function suspend_status_to_chars
inline const char* suspend_status_to_chars(suspend_status status) {
    switch(status) {
    /// suspend...
    case suspend_success: return "suspend_success";
    case suspend_failed: return "suspend_failed";
    case suspend_busy: return "suspend_busy";
    case suspend_timeout: return "suspend_timeout";
    case suspend_interrupted: return "suspend_interrupted";
    }
    return "unknown";
} /// function suspend_status_to_chars

/// class suspend_exceptiont
template <class TExtends = exceptiont<suspend_status>, class TImplements = typename TExtends::implements>
class exported suspend_exceptiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef suspend_exceptiont derives;

    /// constructor / destructor
    suspend_exceptiont(const suspend_exceptiont& copy): extends(copy) {
    }
    suspend_exceptiont(suspend_status status): extends(status) {
    }

    /// ...status...
    virtual const char* status_to_chars() const {
        return suspend_status_to_chars(this->status());
    }
}; /// class suspend_exceptiont
typedef suspend_exceptiont<> suspend_exception;

/// class suspendedt 
template <class TImplements = implement>
class exported suspendedt: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef suspendedt derives;

    typedef xos::suspend_status suspend_status;
    enum {
        suspend_success = xos::suspend_success,
        suspend_failed = xos::suspend_failed,
        suspend_busy = xos::suspend_busy,
        suspend_timeout = xos::suspend_timeout,
        suspend_interrupted = xos::suspend_interrupted
    };
    
    /// suspend...
    virtual bool suspend() {
        return (suspend_success == untimed_suspend());
    }
    virtual suspend_status timed_suspend(mseconds_t milliseconds) {
        return suspend_success;
    }
    virtual suspend_status untimed_suspend() {
        return suspend_success;
    }
    virtual suspend_status try_suspend() {
        return suspend_success;
    }
}; /// class suspendedt
typedef suspendedt<> suspended;

namespace extended {
/// class suspendt
template <class TExtends = extend, class TImplements = implement>
class exported suspendt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef suspendt derives;

    /// constructor / destructor
    suspendt(suspended& _suspended): is_suspended_(false), suspended_(_suspended) {
    }
    virtual ~suspendt() {
    }
private:
    suspendt(const suspendt& copy): is_suspended_(false), suspended_(this_suspended_) {
        throw exception(exception_unexpected);
    }

    virtual bool set_suspended(bool to = true) {
        is_suspended_ = to;
        return is_suspended_;
    }
    virtual bool set_unsuspended(bool to = true) {
        is_suspended_ = !to;
        return !is_suspended_;
    }

protected:
    bool is_suspended_;
    suspended this_suspended_, &suspended_;
}; /// class suspendt
typedef suspendt<> suspend;
} /// namespace extended

/// class suspendt
template <class TExtends = extended::suspend, class TImplements = typename TExtends::implements>
class exported suspendt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef suspendt derives;

    /// constructor / destructor
    suspendt(suspended& _suspended, mseconds_t mseconds): extends(_suspended) {
        suspend_status status = suspend_failed;
        if (!(this->is_suspended_ = (suspend_success == (status = this->suspended_.timed_suspend(mseconds))))) {
            throw suspend_exception(status);
        }
    }
    suspendt(suspended& _suspended): extends(_suspended) {
        if (!(this->is_suspended_ = (this->suspended_.suspend()))) {
            throw suspend_exception(suspend_failed);
        }
    }
    virtual ~suspendt() {
    }
private:
    suspendt(const suspendt& copy): extends(copy) {
        throw exception(exception_unexpected);
    }
}; /// class suspendt
typedef suspendt<> suspend;

/// class try_suspendt
template <class TExtends = extended::suspend, class TImplements = typename TExtends::implements>
class exported try_suspendt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef try_suspendt derives;

    /// constructor / destructor
    try_suspendt(suspended& _suspended): extends(_suspended) {
        suspend_status status = suspend_failed;
        if (!(this->is_suspended_ = (suspend_success == (status = this->suspended_.try_suspend())))) {
            throw suspend_exception(status);
        }
    }
    virtual ~try_suspendt() {
    }
private:
    try_suspendt(const try_suspendt& copy): extends(copy) {
        throw exception(exception_unexpected);
    }
}; /// class try_suspendt
typedef try_suspendt<> try_suspend;

} /// namespace xos

#endif /// ndef XOS_BASE_SUSPENDED_HPP
