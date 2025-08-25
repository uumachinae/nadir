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
///   File: suspended.hpp
///
/// Author: $author$
///   Date: 5/10/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_BASE_SUSPENDED_HPP
#define _NADIR_BASE_SUSPENDED_HPP

#include "nadir/base/exception.hpp"

namespace nadir {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum suspend_status {
    resume_success,
    suspend_success = resume_success,

    suspend_failed,
    suspend_busy,
    suspend_interrupted,
    suspend_invalid,

    resume_failed,
    resume_busy,
    resume_interrupted,
    resume_invalid
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
inline const char* suspend_status_to_chars(suspend_status status) {
    switch (status) {
    case suspend_success: return "suspend_success";
    case suspend_failed: return "suspend_failed";
    case suspend_busy: return "suspend_busy";
    case suspend_interrupted: return "suspend_interrupted";
    case suspend_invalid: return "suspend_invalid";

    case resume_failed: return "resume_failed";
    case resume_busy: return "resume_busy";
    case resume_interrupted: return "resume_interrupted";
    case resume_invalid: return "resume_invalid";
    }
    return "unknown";
}

typedef exceptiont_implements suspend_exceptiont_implements;
typedef exceptiont<suspend_status> suspend_exceptiont_extends;
///////////////////////////////////////////////////////////////////////
///  Class: suspend_exceptiont
///////////////////////////////////////////////////////////////////////
template
<class TImplements = suspend_exceptiont_implements,
 class TExtends = suspend_exceptiont_extends>

class _EXPORT_CLASS suspend_exceptiont
: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    suspend_exceptiont(suspend_status status): Extends(status) {}
    virtual ~suspend_exceptiont() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* status_to_chars() const {
        return suspend_status_to_chars(this->status());
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef suspend_exceptiont<> suspend_exception;

typedef implement_base suspendedt_implements;
///////////////////////////////////////////////////////////////////////
///  Class: suspendedt
///////////////////////////////////////////////////////////////////////
template <class TImplements = suspendedt_implements>

class _EXPORT_CLASS suspendedt: virtual public TImplements {
public:
    typedef TImplements Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef suspendedt<> suspended;

} // namespace nadir 

#endif // _NADIR_BASE_SUSPENDED_HPP 
