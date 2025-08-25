///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2020 $organization$
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
///   File: acquired.hpp
///
/// Author: $author$
///   Date: 1/4/2020
///////////////////////////////////////////////////////////////////////
#ifndef XOS_BASE_ACQUIRED_HPP
#define XOS_BASE_ACQUIRED_HPP

#include "xos/base/exception.hpp"

namespace xos {

/// enum acquire_status
typedef int acquire_status;
enum {
    /// acquire, ...
    acquire_success = 0,
    acquire_failed,
    acquire_busy,
    acquire_timeout,
    acquire_interrupted,
    
    /// release, ...
    release_failed,
    release_busy,
    release_timeout,
    release_interrupted,
    release_success = acquire_success
}; /// enum acquire_status

/// function acquire_status_to_chars
inline const char* acquire_status_to_chars(acquire_status status) {
    switch(status) {
    /// acquire, ...
    case acquire_success: return "acquire_success";
    case acquire_failed: return "acquire_failed";
    case acquire_busy: return "acquire_busy";
    case acquire_timeout: return "acquire_timeout";
    case acquire_interrupted: return "acquire_interrupted";

    /// release, ...
    case release_failed: return "release_failed";
    case release_busy: return "release_busy";
    case release_timeout: return "release_timeout";
    case release_interrupted: return "release_interrupted";
    }
    return "unknown";
} /// function acquire_status_to_chars

/// class acquire_exceptiont
template <class TExtends = exceptiont<acquire_status>, class TImplements = typename TExtends::implements>
class exported acquire_exceptiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef acquire_exceptiont derives;

    /// constructor / destructor
    acquire_exceptiont(const acquire_exceptiont& copy): extends(copy) {
    }
    acquire_exceptiont(acquire_status status): extends(status) {
    }

    /// ...status...
    virtual const char* status_to_chars() const {
        return acquire_status_to_chars(this->status());
    }
}; /// class acquire_exceptiont
typedef acquire_exceptiont<> acquire_exception;

/// class acquiredt 
template <class TImplements = implement>
class exported acquiredt: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef acquiredt derives;

    typedef xos::acquire_status acquire_status;
    enum {
        acquire_success = xos::acquire_success,
        acquire_failed = xos::acquire_failed,
        release_success = xos::release_success,
        release_failed = xos::release_failed
    };
    
    /// acquire...
    virtual bool acquire() {
        return (acquire_success == untimed_acquire());
    }
    virtual acquire_status timed_acquire(mseconds_t milliseconds) {
        return acquire_success;
    }
    virtual acquire_status untimed_acquire() {
        return acquire_success;
    }
    virtual acquire_status try_acquire() {
        return acquire_success;
    }

    /// release...
    virtual bool release() {
        return (release_success == untimed_release());
    }
    virtual acquire_status timed_release(mseconds_t milliseconds) {
        return acquire_success;
    }
    virtual acquire_status untimed_release() {
        return acquire_success;
    }
    virtual acquire_status try_release() {
        return acquire_success;
    }
}; /// class acquiredt
typedef acquiredt<> acquired;

/// class acquiret
template <class TExtends = extend, class TImplements = implement>
class exported acquiret: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef acquiret derives;

    /// constructor
    acquiret(acquired& _acquired, mseconds_t mseconds): acquired_(_acquired) {
        acquire_status status = acquire_failed;
        if (acquire_success != (status = acquired_.timed_acquire(mseconds))) {
            throw acquire_exception(status);
        }
    }
    acquiret(acquired& _acquired): acquired_(_acquired) {
        if (!(acquired_.acquire())) {
            throw acquire_exception(acquire_failed);
        }
    }
private:
    acquiret(const acquiret& copy): acquired_(this_acquired_) {
        throw exception(exception_unexpected);
    }

protected:
    acquired this_acquired_, &acquired_;
}; /// class acquiret
typedef acquiret<> acquire;

/// class try_acquiret
template <class TExtends = extend, class TImplements = implement>
class exported try_acquiret: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef try_acquiret derives;

    /// constructor
    try_acquiret(acquired& _acquired): acquired_(_acquired) {
        acquire_status status = acquire_failed;
        if (acquire_success != (status = acquired_.try_acquire())) {
            throw acquire_exception(status);
        }
    }
private:
    try_acquiret(const try_acquiret& copy): acquired_(this_acquired_) {
        throw exception(exception_unexpected);
    }

protected:
    acquired this_acquired_, &acquired_;
}; /// class try_acquiret
typedef try_acquiret<> try_acquire;

/// class timed_acquiret
template <class TExtends = extend, class TImplements = implement>
class exported timed_acquiret: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef timed_acquiret derives;

    /// constructor
    timed_acquiret(acquired& _acquired, mseconds_t timeout): acquired_(_acquired) {
        acquire_status status = acquire_failed;
        if (acquire_success != (status = acquired_.timed_acquire(timeout))) {
            throw acquire_exception(status);
        }
    }
private:
    timed_acquiret(const timed_acquiret& copy): acquired_(this_acquired_) {
        throw exception(exception_unexpected);
    }

protected:
    acquired this_acquired_, &acquired_;
}; /// class timed_acquiret
typedef timed_acquiret<> timed_acquire;

/// class releaset
template <class TExtends = extend, class TImplements = implement>
class exported releaset: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef releaset derives;

    /// constructor
    releaset(acquired& _acquired): acquired_(_acquired) {
        if (!(acquired_.release())) {
            throw acquire_exception(release_failed);
        }
    }
private:
    releaset(const releaset& copy): acquired_(this_acquired_) {
        throw exception(exception_unexpected);
    }

protected:
    acquired this_acquired_, &acquired_;
}; /// class releaset
typedef releaset<> release;

} /// namespace xos

#endif /// ndef XOS_BASE_ACQUIRED_HPP 
