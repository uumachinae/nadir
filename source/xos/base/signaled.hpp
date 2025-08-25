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
///   File: signaled.hpp
///
/// Author: $author$
///   Date: 1/15/2020
///////////////////////////////////////////////////////////////////////
#ifndef XOS_BASE_SIGNALED_HPP
#define XOS_BASE_SIGNALED_HPP

#include "xos/base/waited.hpp"

namespace xos {

/// enum signal_status
typedef int signal_status;
enum {
    /// signal...
    signal_success = wait_success,
    signal_failed = last_wait + 1,
    signal_busy,
    signal_timeout,
    signal_interrupted,
    first_signal = signal_failed,
    last_signal = signal_interrupted,
}; /// enum signal_status

/// function signal_status_to_chars
inline const char* signal_status_to_chars(signal_status status) {
    switch(status) {
    /// signal...
    case signal_failed: return "signal_failed";
    case signal_busy: return "signal_busy";
    case signal_timeout: return "signal_timeout";
    case signal_interrupted: return "signal_interrupted";
    }
    return wait_status_to_chars(status);
} /// function signal_status_to_chars

/// class signal_exceptiont
template <class TExtends = wait_exception, class TImplements = typename TExtends::implements>
class exported signal_exceptiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef signal_exceptiont derives;

    /// constructor / destructor
    signal_exceptiont(const signal_exceptiont& copy): extends(copy) {
    }
    signal_exceptiont(signal_status status): extends(status) {
    }

    /// ...status...
    virtual const char* status_to_chars() const {
        return signal_status_to_chars(this->status());
    }
}; /// class signal_exceptiont
typedef signal_exceptiont<> signal_exception;

/// class signaledt 
template <class TImplements = waited>
class exported signaledt: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef signaledt derives;

    typedef xos::wait_status wait_status;
    enum {
        wait_success = xos::wait_success,
        wait_failed = xos::wait_failed,
        wait_busy = xos::wait_busy,
        wait_timeout = xos::wait_timeout,
        wait_interrupted = xos::wait_interrupted
    };
    typedef xos::signal_status signal_status;
    enum {
        signal_success = xos::signal_success,
        signal_failed = xos::signal_failed,
        signal_busy = xos::signal_busy,
        signal_timeout = xos::signal_timeout,
        signal_interrupted = xos::signal_interrupted
    };
    
    /// signal...
    virtual bool signal() {
        return (signal_success == untimed_signal());
    }
    virtual signal_status timed_signal(mseconds_t milliseconds) {
        return signal_success;
    }
    virtual signal_status untimed_signal() {
        return signal_success;
    }
    virtual signal_status try_signal() {
        return signal_success;
    }
}; /// class signaledt
typedef signaledt<> signaled;

namespace extended {
/// class signalt
template <class TExtends = extend, class TImplements = implement>
class exported signalt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef signalt derives;

    /// constructor / destructor
    signalt(signaled& _signaled): signaled_(_signaled) {
    }
    virtual ~signalt() {
    }
private:
    signalt(const signalt& copy): signaled_(this_signaled_) {
        throw exception(exception_unexpected);
    }

protected:
    signaled this_signaled_, &signaled_;
}; /// class signalt
typedef signalt<> signal;
} /// namespace extended

/// class signalt
template <class TExtends = extended::signal, class TImplements = implement>
class exported signalt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef signalt derives;

    /// constructor / destructor
    signalt(signaled& _signaled): extends(_signaled) {
        if (!(this->signaled_.signal())) {
            throw signal_exception(signal_failed);
        }
    }
private:
    signalt(const signalt& copy) {
        throw exception(exception_unexpected);
    }
}; /// class signalt
typedef signalt<> signal;

} /// namespace xos

#endif /// ndef XOS_BASE_SIGNALED_HPP
