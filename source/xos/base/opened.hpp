///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2020 $organization$
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
///   File: opened.hpp
///
/// Author: $author$
///   Date: 3/23/2020
///////////////////////////////////////////////////////////////////////
#ifndef XOS_BASE_OPENED_HPP
#define XOS_BASE_OPENED_HPP

#include "xos/base/attached.hpp"

namespace xos {

/// enum open_status
typedef exception_status open_status;
enum {
    close_success,
    open_success = close_success,
    open_failed,
    close_failed
}; /// enum open_status

/// function open_status_to_chars
inline const char* open_status_to_chars(open_status status) {
    switch (status) {
    case open_success: "open_success";
    case open_failed: "open_failed";
    case close_failed: "close_failed";
    }
    return "unknown";
} /// function open_status_to_chars

/// class open_exceptiont
template <class TExtends = exceptiont<open_status>, class TImplements = typename TExtends::implements>
class exported open_exceptiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef open_exceptiont derives;

    /// constructor / destructor
    open_exceptiont(const open_exceptiont& copy): extends(copy) {
    }
    open_exceptiont(open_status status): extends(status) {
    }

    /// ...status...
    virtual const char* status_to_chars() const {
        return open_status_to_chars(this->status());
    }
}; /// class open_exceptiont
typedef open_exceptiont<> open_exception;

/// class openert
template <class TImplements = implement>
class exported openert: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef openert derives;

    /// open / close
    virtual bool open() {
        if ((this->closed())) {
            if ((this->set_is_open())) {
                return true;
            }
        }
        return false;
    }
    virtual bool close() {
        if ((this->is_open())) {
            this->set_is_open(false);
            if ((this->is_closed())) {
                return true;
            }
        }
        return false;
    }
    virtual bool closed() {
        if ((this->is_open())) {
            if ((this->close())) {
                return true;
            }
            return false;
        }
        return true;
    }

    /// ...open / ...close
    virtual bool set_is_open(bool to = true) {
        return false;
    }
    virtual bool is_open() const {
        return false;
    }
    virtual bool set_is_closed(bool to = true) {
        return !set_is_open(!to);
    }
    virtual bool is_closed() const {
        return !is_open();
    }
}; /// class openert
typedef openert<> opener;

/// class openedt
template 
<typename TAttached = pointer_t, 
 typename TUnattached = int, TUnattached VUnattached = 0,
 class TImplement = opener, class TExtend = extend, 
 class TExtends = attachedt<TAttached, TUnattached, VUnattached, TImplement, TExtend>, 
 class TImplements = typename TExtends::implements>

class exported openedt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef openedt derives;

    typedef TAttached attached_t;
    typedef TUnattached unattached_t;
    enum { unattached = VUnattached };

    /// constructor / destructor
    openedt(attached_t detached, bool is_open): extends(detached), is_open_(is_open) {
    }
    openedt(attached_t detached): extends(detached), is_open_(false) {
    }
    openedt(const openedt& copy): extends(copy), is_open_(false) {
    }
    openedt(): is_open_(false) {
    }
    virtual ~openedt() {
        if (!(this->closed())) {
            throw (open_exception(close_failed));
        }
    }
    
    /// open / close
    virtual bool open() {
        attached_t detached = (attached_t)unattached;
        if ((attached_t)unattached != (detached = this->open_attached())) {
            this->set_is_open();
            return true;
        }
        return false;
    }
    virtual bool close() {
        attached_t detached = (attached_t)unattached;
        this->set_is_open(false);
        if ((attached_t)unattached != (detached = this->detach())) {
            if ((this->close_detached(detached))) {
                return true;
            }
        } else {
            return true;
        }
        return false;
    }

    /// open.../ close...
    virtual attached_t open_attached() {
        attached_t detached = (attached_t)unattached;
        if ((this->closed())) {
            if ((attached_t)unattached != (detached = open_detached())) {
                this->attach(detached);
            }
        }
        return detached;
    }
    virtual attached_t open_detached() const {
        attached_t detached = (attached_t)unattached;
        return detached;
    }
    virtual bool close_detached(attached_t detached) const {
        if ((attached_t)unattached != (detached)) {
            return true;
        }
        return false;
    }

    /// attach... / detach...
    virtual attached_t attach_opened(attached_t detached, bool is_open = true) {
        attached_t attached = this->attach(detached);
        this->set_is_open(is_open);
        return attached;
    }
    virtual attached_t detach_opened(bool& is_open) {
        is_open = this->is_open();
        return this->detach();
    }
    virtual attached_t attach(attached_t detached) {
        this->set_is_open(false);
        return extends::attach(detached);
    }
    virtual attached_t detach() {
        this->set_is_open(false);
        return extends::detach();
    }

    /// ...is_open
    virtual bool set_is_open(bool to = true) {
        is_open_ = to;
        return is_open_;
    }
    virtual bool is_open() const {
        return is_open_;
    }

protected:
    bool is_open_;
}; /// class openedt
typedef openedt<> opened;

namespace base {

typedef ::xos::open_exception open_exception;
static const open_exception open_failed = ::xos::open_failed;
static const open_exception close_failed = ::xos::close_failed;

typedef open_exception opener_exception;
static const opener_exception failed_to_open = open_failed;
static const opener_exception failed_to_close = close_failed;

} /// namespace base
} /// namespace xos

#endif /// ndef XOS_BASE_OPENED_HPP 
