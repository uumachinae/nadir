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
///   File: exists.hpp
///
/// Author: $author$
///   Date: 6/18/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_BASE_EXISTS_HPP
#define _NADIR_BASE_EXISTS_HPP

#include "nadir/base/exception.hpp"

namespace nadir {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum exist_status {
    doesnt_exist_success,
    already_exist_success = doesnt_exist_success,

    already_exist_failed,
    already_exist_busy,
    already_exist_interrupted,
    already_exist_invalid,

    doesnt_exist_failed,
    doesnt_exist_busy,
    doesnt_exist_interrupted,
    doesnt_exist_invalid
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
inline const char* exist_status_to_chars(exist_status status) {
    switch (status) {
    case already_exist_success: return "already_exist_success";
    case already_exist_failed: return "already_exist_failed";
    case already_exist_busy: return "already_exist_busy";
    case already_exist_interrupted: return "already_exist_interrupted";
    case already_exist_invalid: return "already_exist_invalid";

    case doesnt_exist_failed: return "doesnt_exist_failed";
    case doesnt_exist_busy: return "doesnt_exist_busy";
    case doesnt_exist_interrupted: return "doesnt_exist_interrupted";
    case doesnt_exist_invalid: return "doesnt_exist_invalid";
    }
    return "unknown";
}

typedef exceptiont_implements exist_exception_implements;
typedef exceptiont<exist_status> exist_exception_extends;
///////////////////////////////////////////////////////////////////////
///  Class: exist_exceptiont
///////////////////////////////////////////////////////////////////////
template
<class TImplements = exist_exception_implements,
 class TExtends = exist_exception_extends>

class _EXPORT_CLASS exist_exceptiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    exist_exceptiont(exist_status status): Extends(status) {}
    virtual ~exist_exceptiont() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* status_to_chars() const {
        return exist_status_to_chars(this->status());
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef exist_exceptiont<> exist_exception;

typedef implement_base existst_implements;
///////////////////////////////////////////////////////////////////////
///  Class: existst
///////////////////////////////////////////////////////////////////////
template
<class TException = exist_exception,
 class TImplements = existst_implements>

class _EXPORT_CLASS existst: virtual public TImplements {
public:
    typedef TImplements Implements;
    typedef TException exist_exception;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool already_exist() { return false; }
    virtual exist_status try_already_exist() { return already_exist_failed; }
    virtual exist_status untimed_already_exist() { return already_exist_failed; }
    virtual exist_status timed_already_exist(mseconds_t milliseconds) { return already_exist_failed; }
    virtual bool doesnt_exist() { return false; }
    virtual exist_status try_doesnt_exist() { return doesnt_exist_failed; }
    virtual exist_status untimed_doesnt_exist() { return doesnt_exist_failed; }
    virtual exist_status timed_doesnt_exist(mseconds_t milliseconds) { return doesnt_exist_failed; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef existst<> exists;

} // namespace nadir

#endif // _NADIR_BASE_EXISTS_HPP 
