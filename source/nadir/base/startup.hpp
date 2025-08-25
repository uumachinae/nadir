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
///   File: startup.hpp
///
/// Author: $author$
///   Date: 6/18/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_BASE_STARTUP_HPP
#define _NADIR_BASE_STARTUP_HPP

#include "nadir/base/exception.hpp"

namespace nadir {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum startup_status {
    cleanup_success,
    startup_success = cleanup_success,

    startup_failed,
    startup_busy,
    startup_interrupted,
    startup_invalid,

    cleanup_failed,
    cleanup_busy,
    cleanup_interrupted,
    cleanup_invalid
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
inline const char* startup_status_to_chars(startup_status status) {
    switch (status) {
    case startup_success: return "startup_success";
    case startup_failed: return "startup_failed";
    case startup_busy: return "startup_busy";
    case startup_interrupted: return "startup_interrupted";
    case startup_invalid: return "startup_invalid";

    case cleanup_failed: return "cleanup_failed";
    case cleanup_busy: return "cleanup_busy";
    case cleanup_interrupted: return "cleanup_interrupted";
    case cleanup_invalid: return "cleanup_invalid";
    }
    return "unknown";
}

typedef exceptiont_implements startup_exception_implements;
typedef exceptiont<startup_status> startup_exception_extends;
///////////////////////////////////////////////////////////////////////
///  Class: startup_exceptiont
///////////////////////////////////////////////////////////////////////
template
<class TImplements = startup_exception_implements,
 class TExtends = startup_exception_extends>

class _EXPORT_CLASS startup_exceptiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    startup_exceptiont(startup_status status): Extends(status) {}
    virtual ~startup_exceptiont() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* status_to_chars() const {
        return startup_status_to_chars(this->status());
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef startup_exceptiont<> startup_exception;

typedef implement_base startedupt_implements;
///////////////////////////////////////////////////////////////////////
///  Class: startedupt
///////////////////////////////////////////////////////////////////////
template
<class TLockException = startup_exception,
 class TImplements = startedupt_implements>

class _EXPORT_CLASS startedupt: virtual public TImplements {
public:
    typedef TImplements Implements;
    typedef TLockException startup_exception;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool startup() { return false; }
    virtual startup_status try_startup() { return startup_failed; }
    virtual startup_status untimed_startup() { return startup_failed; }
    virtual startup_status timed_startup(mseconds_t milliseconds) { return startup_failed; }
    virtual bool cleanup() { return false; }
    virtual startup_status try_cleanup() { return cleanup_failed; }
    virtual startup_status untimed_cleanup() { return cleanup_failed; }
    virtual startup_status timed_cleanup(mseconds_t milliseconds) { return cleanup_failed; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef startedupt<> startedup;

} // namespace nadir

#endif // _NADIR_BASE_STARTUP_HPP
