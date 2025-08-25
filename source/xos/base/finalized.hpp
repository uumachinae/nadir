///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2022 $organization$
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
///   File: finalized.hpp
///
/// Author: $author$
///   Date: 12/30/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_BASE_FINALIZED_HPP
#define XOS_BASE_FINALIZED_HPP

#include "xos/base/initialized.hpp"

namespace xos {

/// enum finalize_status
typedef int finalize_status;
enum {
    /// finalize...
    finalize_success = initialize_success,
    finalize_failed = next_initialize,
    finalize_busy,
    finalize_timeout,
    finalize_interrupted,
    next_finalize,
    first_finalize = finalize_failed,
    last_finalize = finalize_interrupted,
}; /// enum finalize_status

/// function finalize_status_to_chars
inline const char* finalize_status_to_chars(finalize_status status) {
    switch(status) {
    /// finalize...
    case finalize_success: return "finalize_success";
    case finalize_failed: return "finalize_failed";
    case finalize_busy: return "finalize_busy";
    case finalize_timeout: return "finalize_timeout";
    case finalize_interrupted: return "finalize_interrupted";
    }
    return "unknown";
} /// function finalize_status_to_chars

/// class finalize_exceptiont
template <class TExtends = exceptiont<finalize_status>, class TImplements = typename TExtends::implements>
class exported finalize_exceptiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef finalize_exceptiont derives;

    /// constructor / destructor
    finalize_exceptiont(const finalize_exceptiont& copy): extends(copy) {
    }
    finalize_exceptiont(finalize_status status): extends(status) {
    }

    /// ...status...
    virtual const char* status_to_chars() const {
        return finalize_status_to_chars(this->status());
    }
}; /// class finalize_exceptiont
typedef finalize_exceptiont<> finalize_exception;

/// class finalizedt
template <class TImplements = xos::initialized>
class exported finalizedt: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef finalizedt derives; 
    
    typedef xos::finalize_status finalize_status;
    enum {
        finalize_success = xos::finalize_success,
        finalize_failed = xos::finalize_failed,
        finalize_busy = xos::finalize_busy,
        finalize_timeout = xos::finalize_timeout,
        finalize_interrupted = xos::finalize_interrupted
    };

    /// constructors / destructor
    virtual ~finalizedt() {
    }

    /// finalize...
    virtual bool finalized() {
        if ((this->is_initialized())) {
            return finalize();
        }
        return true;
    }
    virtual bool finalize() {
        return (finalize_success == untimed_finalize());
    }
    virtual finalize_status time_finalize(mseconds_t milliseconds) {
        return finalize_success;
    }
    virtual finalize_status timed_finalize(mseconds_t milliseconds) {
        return finalize_success;
    }
    virtual finalize_status untimed_finalize() {
        return finalize_success;
    }
    virtual finalize_status try_finalize() {
        return finalize_success;
    }
    
}; /// class finalizedt
typedef finalizedt<> finalized;

namespace extended {
/// class finalizedt
template <class TExtends = extend, class TImplements = implement>
class exported finalizedt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef finalizedt derives;

    /// constructor / destructor
    finalizedt(const finalizedt& copy): is_finalized_(copy.is_finalized_) {
    }
    finalizedt(bool is_finalized): is_finalized_(is_finalized) {
    }
    finalizedt(): is_finalized_(false) {
    }
    virtual ~finalizedt() {
    }

    /// ...finalized
    virtual bool set_finalized(bool to = true) {
        is_finalized_ = to;
        return is_finalized_;
    }
    virtual bool is_finalized() const {
        return is_finalized_;
    }

protected:
    bool is_finalized_;
}; /// class finalizedt
typedef finalizedt<> finalized;
} /// namespace extended

} /// namespace xos

#endif /// ndef XOS_BASE_FINALIZED_HPP
