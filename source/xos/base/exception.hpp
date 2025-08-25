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
///   File: exception.hpp
///
/// Author: $author$
///   Date: 12/5/2019, 7/14/2021
///////////////////////////////////////////////////////////////////////
#ifndef XOS_BASE_EXCEPTION_HPP
#define XOS_BASE_EXCEPTION_HPP

#include "xos/base/string.hpp"

namespace xos {

/// enum exception_status
typedef int exception_status;
enum {
    exception_success,
    exception_failed,
    exception_unexpected,
    exception_exist,
    exception_exists
}; /// enum exception_status

/// function exception_status_to_chars
inline const char* exception_status_to_chars(exception_status status) {
    switch(status) {
    case exception_success: return "exception_success";
    case exception_failed: return "exception_failed";
    case exception_unexpected: return "exception_unexpected";
    case exception_exist: return "exception_exist";
    case exception_exists: return "exception_exists";
    }
    return "unknown";
}

/// class exceptiont
template 
<typename TStatus = exception_status,
 class TExtends = extend, class TImplements = implement>
class exported exceptiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef exceptiont derives;

    typedef TStatus status_t;

    /// constructor / destructor
    exceptiont(const exceptiont& copy): extends(copy), status_(copy.status()) {
    }
    exceptiont(status_t status): status_(status) {
    }

    /// ...status...
    virtual status_t set_status(status_t to) {
        status_ = to;
        return status_;
    }
    virtual status_t status() const {
        return status_;
    }
    virtual const char* status_to_chars() const {
        return exception_status_to_chars(status());
    }

protected:
    status_t status_;
}; /// class exceptiont
typedef exceptiont<> exception;

namespace base {

/// enum exception_status
typedef int exception_status;
enum {
    exception_success    = xos::exception_success,
    exception_failed     = xos::exception_failed,
    exception_unexpected = xos::exception_unexpected,
    exception_exist      = xos::exception_exist,
    exception_exists     = xos::exception_exists
}; /// enum exception_status

/// class exceptiont
template 
<typename TStatus = exception_status, typename TChar = char, class TString = stringt<TChar>,
 class TExtends = xos::exceptiont<TStatus>, class TImplements = typename TExtends::implements>
class exported exceptiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements, Implements;
    typedef TExtends extends, Extends;
    typedef exceptiont derives, Derives; 
    
    typedef typename extends::status_t status_t;

    /// constructors / destructor
    exceptiont(const exceptiont& copy): extends(copy) {
    }
    exceptiont(status_t status): extends(status) {
    }
    virtual ~exceptiont() {
    }
}; /// class exceptiont
typedef exceptiont<> exception;

} /// namespace base
} /// namespace xos

#endif /// ndef XOS_BASE_EXCEPTION_HPP
