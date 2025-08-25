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
///   File: raised.hpp
///
/// Author: $author$
///   Date: 6/14/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_BASE_RAISED_HPP
#define _NADIR_BASE_RAISED_HPP

#include "nadir/base/exception.hpp"

namespace nadir {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum raise_status {
    lower_success,
    raise_success = lower_success,

    raise_failed,
    raise_busy,
    raise_interrupted,
    raise_invalid,

    lower_failed,
    lower_busy,
    lower_interrupted,
    lower_invalid
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
inline const char* raise_status_to_chars(raise_status status) {
    switch (status) {
    case raise_success: return "raise_success";
    case raise_failed: return "raise_failed";
    case raise_busy: return "raise_busy";
    case raise_interrupted: return "raise_interrupted";
    case raise_invalid: return "raise_invalid";

    case lower_failed: return "lower_failed";
    case lower_busy: return "lower_busy";
    case lower_interrupted: return "lower_interrupted";
    case lower_invalid: return "lower_invalid";
    }
    return "unknown";
}

typedef exceptiont_implements raise_exception_implements;
typedef exceptiont<raise_status> raise_exception_extends;
///////////////////////////////////////////////////////////////////////
///  Class: raise_exceptiont
///////////////////////////////////////////////////////////////////////
template
<class TImplements = raise_exception_implements,
 class TExtends = raise_exception_extends>

class _EXPORT_CLASS raise_exceptiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    raise_exceptiont(raise_status status): Extends(status) {}
    virtual ~raise_exceptiont() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* status_to_chars() const {
        return raise_status_to_chars(this->status());
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef raise_exceptiont<> raise_exception;

typedef implement_base raiseedt_implements;
///////////////////////////////////////////////////////////////////////
///  Class: raiseedt
///////////////////////////////////////////////////////////////////////
template
<class TLockException = raise_exception,
 class TImplements = raiseedt_implements>

class _EXPORT_CLASS raiseedt: virtual public TImplements {
public:
    typedef TImplements Implements;
    typedef TLockException raise_exception;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool raise() { return false; }
    virtual raise_status try_raise() { return raise_failed; }
    virtual raise_status untimed_raise() { return raise_failed; }
    virtual raise_status timed_raise(mseconds_t milliseconds) { return raise_failed; }
    virtual bool lower() { return false; }
    virtual raise_status try_lower() { return lower_failed; }
    virtual raise_status untimed_lower() { return lower_failed; }
    virtual raise_status timed_lower(mseconds_t milliseconds) { return lower_failed; }
    virtual bool is_raised() const { return false; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef raiseedt<> raiseed;

} // namespace nadir

#endif // _NADIR_BASE_RAISED_HPP 
