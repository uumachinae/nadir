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
///   File: waited.hpp
///
/// Author: $author$
///   Date: 1/15/2020
///////////////////////////////////////////////////////////////////////
#ifndef XOS_BASE_WAITED_HPP
#define XOS_BASE_WAITED_HPP

#include "xos/base/exception.hpp"

namespace xos {

/// enum wait_status
typedef int wait_status;
enum {
    /// wait...
    wait_success = 0,
    wait_failed,
    wait_busy,
    wait_timeout,
    wait_interrupted,
    first_wait = wait_success,
    last_wait = wait_interrupted,
}; /// enum wait_status

/// function wait_status_to_chars
inline const char* wait_status_to_chars(wait_status status) {
    switch(status) {
    /// wait...
    case wait_success: return "wait_success";
    case wait_failed: return "wait_failed";
    case wait_busy: return "wait_busy";
    case wait_timeout: return "wait_timeout";
    case wait_interrupted: return "wait_interrupted";
    }
    return "unknown";
} /// function wait_status_to_chars

/// class wait_exceptiont
template <class TExtends = exceptiont<wait_status>, class TImplements = typename TExtends::implements>
class exported wait_exceptiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef wait_exceptiont derives;

    /// constructor / destructor
    wait_exceptiont(const wait_exceptiont& copy): extends(copy) {
    }
    wait_exceptiont(wait_status status): extends(status) {
    }

    /// ...status...
    virtual const char* status_to_chars() const {
        return wait_status_to_chars(this->status());
    }
}; /// class wait_exceptiont
typedef wait_exceptiont<> wait_exception;

/// class waitedt 
template <class TImplements = implement>
class exported waitedt: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef waitedt derives;

    typedef xos::wait_status wait_status;
    enum {
        wait_success = xos::wait_success,
        wait_failed = xos::wait_failed,
        wait_busy = xos::wait_busy,
        wait_timeout = xos::wait_timeout,
        wait_interrupted = xos::wait_interrupted
    };
    
    /// wait...
    virtual bool wait() {
        return (wait_success == untimed_wait());
    }
    virtual wait_status time_wait(mseconds_t milliseconds) {
        return wait_success;
    }
    virtual wait_status timed_wait(mseconds_t milliseconds) {
        return wait_success;
    }
    virtual wait_status untimed_wait() {
        return wait_success;
    }
    virtual wait_status try_wait() {
        return wait_success;
    }
}; /// class waitedt
typedef waitedt<> waited;

namespace extended {
/// class waitt
template <class TExtends = extend, class TImplements = implement>
class exported waitt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef waitt derives;

    typedef xos::wait_status wait_status;
    enum {
        wait_success = xos::wait_success,
        wait_failed = xos::wait_failed,
        wait_busy = xos::wait_busy,
        wait_timeout = xos::wait_timeout,
        wait_interrupted = xos::wait_interrupted
    };
    
    /// constructor / destructor
    waitt(waited& _waited): waited_(_waited) {
    }
private:
    waitt(const waitt& copy): waited_(this_waited_) {
        throw exception(exception_unexpected);
    }

protected:
    waited this_waited_, &waited_;
}; /// class waitt
typedef waitt<> wait;
} /// namespace extended

/// class waitt
template 
<class TExtends = extended::wait, 
 class TImplements = typename TExtends::implements>
class exported waitt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef waitt derives;

    typedef typename extends::wait_status wait_status;
    enum {
        wait_success = extends::wait_success,
        wait_failed = extends::wait_failed,
        wait_busy = extends::wait_busy,
        wait_timeout = extends::wait_timeout,
        wait_interrupted = extends::wait_interrupted
    };
    
    /// constructor / destructor
    waitt(waited& _waited, mseconds_t mseconds): extends(_waited) {
        wait_status status = wait_failed;
        if (wait_success != (status = this->waited_.timed_wait(mseconds))) {
            throw wait_exception(status);
        }
    }
    waitt(waited& _waited): extends(_waited) {
        if (!(this->waited_.wait())) {
            throw wait_exception(wait_failed);
        }
    }
private:
    waitt(const waitt& copy) {
        throw exception(exception_unexpected);
    }
}; /// class waitt
typedef waitt<> wait;

/// class time_waitt
template 
<class TExtends = extended::wait, 
 class TImplements = typename TExtends::implements>
class exported time_waitt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef time_waitt derives;

    typedef typename extends::wait_status wait_status;
    enum {
        wait_success = extends::wait_success,
        wait_failed = extends::wait_failed,
        wait_busy = extends::wait_busy,
        wait_timeout = extends::wait_timeout,
        wait_interrupted = extends::wait_interrupted
    };
    
    /// constructor / destructor
    time_waitt(waited& _waited, mseconds_t mseconds): extends(_waited) {
        wait_status status = wait_failed;
        if (wait_success != (status = this->waited_.time_wait(mseconds))) {
            throw wait_exception(status);
        }
    }
private:
    time_waitt(const time_waitt& copy) {
        throw exception(exception_unexpected);
    }
}; /// class time_waitt
typedef time_waitt<> time_wait;

/// class try_waitt
template 
<class TExtends = extended::wait, 
 class TImplements = typename TExtends::implements>
class exported try_waitt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef try_waitt derives;

    typedef typename extends::wait_status wait_status;
    enum {
        wait_success = extends::wait_success,
        wait_failed = extends::wait_failed,
        wait_busy = extends::wait_busy,
        wait_timeout = extends::wait_timeout,
        wait_interrupted = extends::wait_interrupted
    };
    
    /// constructor / destructor
    try_waitt(waited& _waited): extends(_waited) {
        wait_status status = wait_failed;
        if (wait_success != (status = this->waited_.try_wait())) {
            throw wait_exception(status);
        }
    }
private:
    try_waitt(const try_waitt& copy) {
        throw exception(exception_unexpected);
    }
}; /// class try_waitt
typedef try_waitt<> try_wait;

} /// namespace xos

#endif /// ndef XOS_BASE_WAITED_HPP
