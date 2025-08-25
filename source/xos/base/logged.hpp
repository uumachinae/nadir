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
///   File: logged.hpp
///
/// Author: $author$
///   Date: 12/5/2019
///////////////////////////////////////////////////////////////////////
#ifndef XOS_BASE_LOGGED_HPP
#define XOS_BASE_LOGGED_HPP

#include "xos/base/base.hpp"

#define XOS_BASE_LOGGED_DEBUG_THREASHOLD_DEFAULT_MSECONDS 500

namespace xos {

/// class loggedt
template <class TImplements = implement>
class exported loggedt: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef loggedt derives;

    /// ...is_logged
    virtual bool set_is_logged(bool to = true) {
        return is_logged();
    }
    virtual bool is_logged() const {
        return true;
    }

    /// ...is_logged_debug...
    virtual bool is_logged_debug(mseconds_t milliseconds) const {
        mseconds_t threashold = is_logged_debug_threashold();
        return (milliseconds >= threashold);
    }
    virtual mseconds_t set_is_logged_debug_threashold(mseconds_t to) {
        return is_logged_debug_threashold();
    }
    virtual mseconds_t is_logged_debug_threashold() const {
        return is_logged_debug_threashold_default();
    }
    virtual mseconds_t is_logged_debug_threashold_default() const {
        return XOS_BASE_LOGGED_DEBUG_THREASHOLD_DEFAULT_MSECONDS;
    }
}; /// class loggedt
typedef loggedt<> logged;

namespace extended {
/// class loggedt
template <class TImplements = xos::logged, class TExtends = extend>
class exported loggedt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef loggedt derives;

    /// constructors / destructor
    loggedt(bool is_logged, mseconds_t is_logged_debug_threashold)
    : is_logged_(is_logged), 
      is_logged_debug_threashold_(is_logged_debug_threashold) {
    }
    loggedt(bool is_logged)
    : is_logged_(is_logged), 
      is_logged_debug_threashold_(this->is_logged_debug_threashold_default()) {
    }
    loggedt(const loggedt& copy)
    : is_logged_(copy.is_logged_),
      is_logged_debug_threashold_(copy.is_logged_debug_threashold_) {
    }
    loggedt()
    : is_logged_(true), 
      is_logged_debug_threashold_(this->is_logged_debug_threashold_default()) {
    }
    virtual ~loggedt() {
    }

    /// ...is_logged
    virtual bool set_is_logged(bool to = true) {
        is_logged_ = to;
        return is_logged_;
    }
    virtual bool is_logged() const {
        return is_logged_;
    }

    /// ...is_logged_debug...
    virtual mseconds_t set_is_logged_debug_threashold(mseconds_t to) {
        is_logged_debug_threashold_ = to;
        return is_logged_debug_threashold_;
    }
    virtual mseconds_t is_logged_debug_threashold() const {
        return is_logged_debug_threashold_;
    }

protected:
    bool is_logged_;
    mseconds_t is_logged_debug_threashold_;
}; /// class loggedt
typedef loggedt<> logged;
} /// namespace extended

namespace base {

typedef xos::logged logged;

} /// namespace base
} /// namespace xos

#endif /// ndef XOS_BASE_LOGGED_HPP
