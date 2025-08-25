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
///   File: acquired.hpp
///
/// Author: $author$
///   Date: 1/2/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_BASE_ACQUIRED_HPP
#define _NADIR_BASE_ACQUIRED_HPP

#include "nadir/base/exception.hpp"

namespace nadir {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum acquire_status {
    release_success,
    acquire_success = release_success,

    acquire_failed,
    acquire_busy,
    acquire_interrupted,
    acquire_invalid,

    release_failed,
    release_busy,
    release_interrupted,
    release_invalid
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
inline const char* acquire_status_to_chars(acquire_status status) {
    switch (status) {
    case acquire_success: return "acquire_success";
    case acquire_failed: return "acquire_failed";
    case acquire_busy: return "acquire_busy";
    case acquire_interrupted: return "acquire_interrupted";
    case acquire_invalid: return "acquire_invalid";

    case release_failed: return "release_failed";
    case release_busy: return "release_busy";
    case release_interrupted: return "release_interrupted";
    case release_invalid: return "release_invalid";
    }
    return "unknown";
}

typedef exceptiont_implements acquire_exceptiont_implements;
typedef exceptiont<acquire_status> acquire_exceptiont_extends;
///////////////////////////////////////////////////////////////////////
///  Class: acquire_exceptiont
///////////////////////////////////////////////////////////////////////
template
<class TImplements = acquire_exceptiont_implements,
 class TExtends = acquire_exceptiont_extends>

class _EXPORT_CLASS acquire_exceptiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    acquire_exceptiont(acquire_status status): Extends(status) {}
    virtual ~acquire_exceptiont() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* status_to_chars() const {
        return acquire_status_to_chars(this->status());
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef acquire_exceptiont<> acquire_exception;

typedef implement_base acquiredt_implements;
///////////////////////////////////////////////////////////////////////
///  Class: acquiredt
///////////////////////////////////////////////////////////////////////
template
<class TLockException = acquire_exception,
 class TImplements = acquiredt_implements>

class _EXPORT_CLASS acquiredt: virtual public TImplements {
public:
    typedef TImplements Implements;
    typedef TLockException acquire_exception;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool acquire() { return false; }
    virtual acquire_status try_acquire() { return acquire_failed; }
    virtual acquire_status untimed_acquire() { return acquire_failed; }
    virtual acquire_status timed_acquire(mseconds_t milliseconds) { return acquire_failed; }
    virtual bool release() { return false; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef acquiredt<> acquired;

} // namespace nadir

#endif // _NADIR_BASE_ACQUIRED_HPP 
