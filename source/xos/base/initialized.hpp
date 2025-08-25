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
///   File: initialized.hpp
///
/// Author: $author$
///   Date: 12/30/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_BASE_INITIALIZED_HPP
#define XOS_BASE_INITIALIZED_HPP

#include "xos/base/exception.hpp"

namespace xos {

/// enum initialize_status
typedef int initialize_status;
enum {
    /// initialize...
    initialize_success = 0,
    initialize_failed,
    initialize_busy,
    initialize_timeout,
    initialize_interrupted,
    next_initialize,
    first_initialize = initialize_success,
    last_initialize = initialize_interrupted,
}; /// enum initialize_status

/// function initialize_status_to_chars
inline const char* initialize_status_to_chars(initialize_status status) {
    switch(status) {
    /// initialize...
    case initialize_success: return "initialize_success";
    case initialize_failed: return "initialize_failed";
    case initialize_busy: return "initialize_busy";
    case initialize_timeout: return "initialize_timeout";
    case initialize_interrupted: return "initialize_interrupted";
    }
    return "unknown";
} /// function initialize_status_to_chars

/// class initialize_exceptiont
template <class TExtends = exceptiont<initialize_status>, class TImplements = typename TExtends::implements>
class exported initialize_exceptiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef initialize_exceptiont derives;

    /// constructor / destructor
    initialize_exceptiont(const initialize_exceptiont& copy): extends(copy) {
    }
    initialize_exceptiont(initialize_status status): extends(status) {
    }

    /// ...status...
    virtual const char* status_to_chars() const {
        return initialize_status_to_chars(this->status());
    }
}; /// class initialize_exceptiont
typedef initialize_exceptiont<> initialize_exception;

/// class initializedt
template <class TImplements = implement>
class exported initializedt: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef initializedt derives; 
    
    typedef xos::initialize_status initialize_status;
    enum {
        initialize_success = xos::initialize_success,
        initialize_failed = xos::initialize_failed,
        initialize_busy = xos::initialize_busy,
        initialize_timeout = xos::initialize_timeout,
        initialize_interrupted = xos::initialize_interrupted
    };

    /// constructors / destructor
    virtual ~initializedt() {
    }

    /// initialize...
    virtual bool initialize() {
        return (initialize_success == untimed_initialize());
    }
    virtual initialize_status timed_initialize(mseconds_t milliseconds) {
        return initialize_success;
    }
    virtual initialize_status untimed_initialize() {
        return initialize_success;
    }
    virtual initialize_status try_initialize() {
        return initialize_success;
    }

    /// ...initialized
    virtual bool set_is_initialized(bool to = true) {
        return false;
    }
    virtual bool is_initialized() const {
        return false;
    }

}; /// class initializedt
typedef initializedt<> initialized;

namespace extended {
/// class initializedt
template <class TExtends = extend, class TImplements = initialized>
class exported initializedt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef initializedt derives;

    /// constructor / destructor
    initializedt(const initializedt& copy): is_initialized_(copy.is_initialized_) {
    }
    initializedt(bool is_initialized): is_initialized_(is_initialized) {
    }
    initializedt(): is_initialized_(false) {
    }
    virtual ~initializedt() {
    }

    /// ...initialized
    virtual bool set_is_initialized(bool to = true) {
        is_initialized_ = to;
        return is_initialized_;
    }
    virtual bool is_initialized() const {
        return is_initialized_;
    }

protected:
    bool is_initialized_;
}; /// class initializedt
typedef initializedt<> initialized;
} /// namespace extended

} /// namespace xos

#endif /// ndef XOS_BASE_INITIALIZED_HPP
