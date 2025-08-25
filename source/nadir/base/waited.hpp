///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2016 $organization$
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
///   Date: 9/20/2016
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_BASE_WAITED_HPP
#define _NADIR_BASE_WAITED_HPP

#include "nadir/base/exception.hpp"

namespace nadir {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum wait_length {
    wait_forever = -1,
    wait_none = 0
};
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum wait_status {
    continue_success,
    wait_success = continue_success,

    wait_failed,
    wait_busy,
    wait_interrupted,
    wait_invalid,

    continue_failed,
    continue_busy,
    continue_interrupted,
    continue_invalid
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
inline const char* wait_status_to_chars(wait_status status) {
    switch (status) {
    case wait_success: return "wait_success";
    case wait_failed: return "wait_failed";
    case wait_busy: return "wait_busy";
    case wait_interrupted: return "wait_interrupted";
    case wait_invalid: return "wait_invalid";

    case continue_failed: return "continue_failed";
    case continue_busy: return "continue_busy";
    case continue_interrupted: return "continue_interrupted";
    case continue_invalid: return "continue_invalid";
    }
    return "unknown";
}

typedef exceptiont_implements wait_exception_implements;
typedef exceptiont<wait_status> wait_exception_extends;
///////////////////////////////////////////////////////////////////////
///  Class: wait_exceptiont
///////////////////////////////////////////////////////////////////////
template
<class TImplements = wait_exception_implements,
 class TExtends = wait_exception_extends>

class _EXPORT_CLASS wait_exceptiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    wait_exceptiont(wait_status status): Extends(status) {}
    virtual ~wait_exceptiont() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* status_to_chars() const {
        return wait_status_to_chars(this->status());
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef wait_exceptiont<> wait_exception;

typedef implement_base waitedt_implements;
///////////////////////////////////////////////////////////////////////
///  Class: waitedt
///////////////////////////////////////////////////////////////////////
template
<class TWaitException = wait_exception,
 class TImplements = waitedt_implements>

class _EXPORT_CLASS waitedt: virtual public TImplements {
public:
    typedef TImplements Implements;
    typedef TWaitException wait_exception;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool wait() { return false; }
    virtual wait_status try_wait() { return wait_failed; }
    virtual wait_status untimed_wait() { return wait_failed; }
    virtual wait_status timed_wait(mseconds_t milliseconds) { return wait_failed; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef waitedt<> waited;

typedef implement_base waitert_implements;
typedef base waitert_extends;
///////////////////////////////////////////////////////////////////////
///  Class: waitert
///////////////////////////////////////////////////////////////////////
template
<class TWaited = waited,
 class TWaitException = wait_exception,
 class TImplements = waitert_implements,
 class TExtends = waitert_extends>

class _EXPORT_CLASS waitert: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef TWaited waited;
    typedef TWaitException wait_exception;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    waitert(waited& _waited, mseconds_t milliseconds): waited_(_waited) {
        wait_status status = wait_failed;
        if (wait_success != (status = waited_.timed_wait(milliseconds))) {
            wait_exception e(status);
            throw (e);
        }
    }
    waitert(waited& _waited): waited_(_waited) {
        if (!(waited_.wait())) {
            wait_exception e(wait_failed);
            throw (e);
        }
    }
    virtual ~waitert() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    waited& waited_;
};
typedef waitert<> waiter;

} // namespace nadir

#endif // _NADIR_BASE_WAITED_HPP 
