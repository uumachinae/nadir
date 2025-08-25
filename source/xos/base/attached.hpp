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
///   File: attached.hpp
///
/// Author: $author$
///   Date: 12/25/2019
///////////////////////////////////////////////////////////////////////
#ifndef XOS_BASE_ATTACHED_HPP
#define XOS_BASE_ATTACHED_HPP

#include "xos/base/exception.hpp"

namespace xos {

/// enum attach_status
typedef int attach_status;
enum {
    /// attach, ...
    attach_success = 0,
    attach_failed,
    attach_busy,
    attach_timeout,
    attach_interrupted,
    
    /// detach, ...
    detach_failed,
    detach_busy,
    detach_timeout,
    detach_interrupted,
    detach_success = attach_success
}; /// enum attach_status

/// function attach_status_to_chars
inline const char* attach_status_to_chars(attach_status status) {
    switch(status) {
    /// attach, ...
    case attach_success: return "attach_success";
    case attach_failed: return "attach_failed";
    case attach_busy: return "attach_busy";
    case attach_timeout: return "attach_timeout";
    case attach_interrupted: return "attach_interrupted";

    /// detach, ...
    case detach_failed: return "detach_failed";
    case detach_busy: return "detach_busy";
    case detach_timeout: return "detach_timeout";
    case detach_interrupted: return "detach_interrupted";
    }
    return "unknown";
} /// function attach_status_to_chars

/// class attach_exceptiont
template <class TExtends = exceptiont<attach_status>, class TImplements = typename TExtends::implements>
class exported attach_exceptiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef attach_exceptiont derives;

    /// constructor / destructor
    attach_exceptiont(const attach_exceptiont& copy): extends(copy) {
    }
    attach_exceptiont(attach_status status): extends(status) {
    }

    /// ...status...
    virtual const char* status_to_chars() const {
        return attach_status_to_chars(this->status());
    }
}; /// class attach_exceptiont
typedef attach_exceptiont<> attach_exception;

/// class attachert
template 
<typename TAttached = pointer_t, 
 typename TUnattached = int, TUnattached VUnattached = 0,
 class TImplements = implement>
class exported attachert: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef attachert derives;

    typedef TAttached attached_t;
    typedef TUnattached unattached_t;
    enum { unattached = VUnattached };

    /// attached / detached
    virtual bool detached() {
        if (((attached_t)unattached) != (this->attached_to())) {
            if (((attached_t)unattached) != (this->detach())) {
                return true;
            }
            return false;
        }
        return true;
    }
    virtual attached_t attach(attached_t detached) {
        return ((attached_t)unattached);
    }
    virtual attached_t detach() {
        return ((attached_t)unattached);
    }
    virtual attached_t attached_to() const {
        return ((attached_t)unattached);
    }
}; /// class attachert
typedef attachert<> attacher;

/// class attachedt
template 
<typename TAttached = pointer_t, 
 typename TUnattached = int, TUnattached VUnattached = 0,
 class TImplement = implement, class TExtends = extend, 
 class TImplements = attachert<TAttached, TUnattached, VUnattached, TImplement> >
class exported attachedt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef attachedt derives;

    typedef TAttached attached_t;
    typedef TUnattached unattached_t;
    enum { unattached = VUnattached };

    /// constructor / destructor
    attachedt(attached_t detached): attached_to_(detached) {
    }
    attachedt(const attachedt& copy): attached_to_(copy.attached_to_) {
    }
    attachedt(): attached_to_((attached_t)unattached) {
    }
    virtual ~attachedt() {
        if (!(this->detached())) {
            throw (attach_exception(detach_failed));
        }
    }

    /// attach / detach
    virtual attached_t attach(attached_t detached) {
        attached_to_ = detached;
        return attached_to_;
    }
    virtual attached_t detach() {
        attached_t detached = attached_to_;
        attached_to_ = ((attached_t)unattached);
        return detached;
    }
    virtual attached_t attached_to() const {
        return attached_to_;
    }

protected:
    attached_t attached_to_;
}; /// class attachedt
typedef attachedt<> attached;

namespace base {

typedef ::xos::attach_exception attach_exception;
static const attach_exception attach_failed = ::xos::attach_failed;
static const attach_exception detach_failed = ::xos::detach_failed;

typedef ::xos::attach_status attacher_exception;
static const attacher_exception failed_to_attach = ::xos::attach_failed;
static const attacher_exception failed_to_detach = ::xos::detach_failed;

/// class attachert
template 
<typename TAttached = pointer_t, typename TUnattached = int, TUnattached VUnattached = 0,
 class TImplement = implement_base, class TImplements = ::xos::attachert
 <TAttached, TUnattached, VUnattached, TImplement> >
class exported attachert: virtual public TImplements {
public:
    typedef TImplements implements, Implements;
    typedef attachert derives, Derives;

    typedef TAttached attached_t;
    typedef TUnattached unattached_t;
    enum { unattached = VUnattached };

}; /// class attachert
typedef attachert<> attacher;

/// class attachedt
template 
<typename TAttached = pointer_t, typename TUnattached = int, TUnattached VUnattached = 0,
 class TImplements = attachert<TAttached, TUnattached, VUnattached, implement_base>, 
 class TExtends = base>
class exported attachedt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements, Implements;
    typedef TExtends extends, Extends;
    typedef attachedt derives, Derives;

    typedef TAttached attached_t;
    typedef TUnattached unattached_t;
    enum { unattached = VUnattached };

    /// constructor / destructor
    attachedt(attached_t detached): attached_to_(detached) {
    }
    attachedt(const attachedt& copy): attached_to_(copy.attached_to_) {
    }
    attachedt(): attached_to_((attached_t)unattached) {
    }
    virtual ~attachedt() {
        if (!(this->detached())) {
            throw (attach_exception(detach_failed));
        }
    }

    /// attach / detach
    virtual attached_t attach(attached_t detached) {
        attached_to_ = detached;
        return attached_to_;
    }
    virtual attached_t detach() {
        attached_t detached = attached_to_;
        attached_to_ = ((attached_t)unattached);
        return detached;
    }
    virtual attached_t attached_to() const {
        return attached_to_;
    }

protected:
    attached_t attached_to_;
}; /// class attachedt
typedef attachedt<> attached;

} /// namespace base
} /// namespace xos

#endif /// ndef XOS_BASE_ATTACHED_HPP
