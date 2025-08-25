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
///   File: created.hpp
///
/// Author: $author$
///   Date: 12/25/2019
///////////////////////////////////////////////////////////////////////
#ifndef XOS_BASE_CREATED_HPP
#define XOS_BASE_CREATED_HPP

#include "xos/base/attached.hpp"

namespace xos {

/// enum create_status
typedef int create_status;
enum {
    /// create, ...
    create_success = 0,
    create_failed,
    create_busy,
    create_timeout,
    create_interrupted,
    
    /// destroy, ...
    destroy_failed,
    destroy_busy,
    destroy_timeout,
    destroy_interrupted,
    destroy_success = create_success
}; /// enum create_status

/// function create_status_to_chars
inline const char* create_status_to_chars(create_status status) {
    switch(status) {
    /// create, ...
    case create_success: return "create_success";
    case create_failed: return "create_failed";
    case create_busy: return "create_busy";
    case create_timeout: return "create_timeout";
    case create_interrupted: return "create_interrupted";

    /// destroy, ...
    case destroy_failed: return "destroy_failed";
    case destroy_busy: return "destroy_busy";
    case destroy_timeout: return "destroy_timeout";
    case destroy_interrupted: return "destroy_interrupted";
    }
    return "unknown";
} /// function create_status_to_chars

/// class create_exceptiont
template <class TExtends = exceptiont<create_status>, class TImplements = typename TExtends::implements>
class exported create_exceptiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef create_exceptiont derives;

    /// constructor / destructor
    create_exceptiont(const create_exceptiont& copy): extends(copy) {
    }
    create_exceptiont(create_status status): extends(status) {
    }

    /// ...status...
    virtual const char* status_to_chars() const {
        return create_status_to_chars(this->status());
    }
}; /// class create_exceptiont
typedef create_exceptiont<> create_exception;

/// class creatort
template <class TImplements = implement>
class exported creatort: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef creatort derives;

    /// created / destroyed
    virtual bool created() {
        if (!(this->is_created())) {
            if ((this->create())) {
                return true;
            }
            return false;
        }
        return true;
    }
    virtual bool destroyed() {
        if ((this->is_created())) {
            if ((this->destroy())) {
                return true;
            }
            return false;
        }
        return true;
    }

    /// create / destroy
    virtual bool create() {
        if ((this->destroyed())) {
            if ((this->set_is_created())) {
                return true;
            }
        }
        return false;
    }
    virtual bool destroy() {
        if ((this->is_created())) {
            this->set_is_created(false);
            if ((this->is_destroyed())) {
                return true;
            }
        }
        return false;
    }

    /// ...is_created / ...is_destroyed
    virtual bool set_is_created(bool to = true) {
        return false;
    }
    virtual bool is_created() const {
        return false;
    }
    virtual bool set_is_destroyed(bool to = true) {
        return true;
    }
    virtual bool is_destroyed() const {
        return true;
    }
}; /// class creatort
typedef creatort<> creator;

/// class createdt
template 
<typename TAttached = pointer_t, 
 typename TUnattached = int, TUnattached VUnattached = 0,
 class TImplement = creator, class TExtend = extend,
 class TImplements = attachert<TAttached, TUnattached, VUnattached, TImplement>, 
 class TExtends = attachedt<TAttached, TUnattached, VUnattached, TImplements, TExtend> >
class exported createdt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef createdt derives;

    typedef TAttached attached_t;
    typedef TUnattached unattached_t;
    enum { unattached = VUnattached };

    /// constructor / destructor
    createdt(attached_t detached, bool is_created): extends(detached), is_created_(is_created) {
    }
    createdt(attached_t detached): extends(detached), is_created_(false) {
    }
    createdt(const createdt& copy): extends(copy), is_created_(copy.is_created_) {
    }
    createdt(): is_created_(false) {
    }
    virtual ~createdt() {
        if (!(this->destroyed())) {
            throw (create_exception(destroy_failed));
        }
    }

    /// create... / destroy...
    virtual bool create() {
        attached_t detached = (attached_t)(unattached);
        if (((attached_t)(unattached) != (detached = this->create_attached()))) {
            this->set_is_created();
            return true;
        }
        return false;
    }
    virtual bool destroy() {
        attached_t detached = (attached_t)(unattached);
        this->set_is_created(false);
        if (((attached_t)(unattached) != (detached = this->detach()))) {
            if ((this->destroy_detached(detached))) {
                return true;
            }
        } else {
            return true;
        }
        return false;
    }
    virtual attached_t create_attached() {
        attached_t detached = (attached_t)(unattached);
        if ((this->destroyed())) {
            if (((attached_t)(unattached) != (detached = create_detached()))) {
                this->attach(detached);
            }
        }
        return detached;
    }
    virtual attached_t create_detached() const {
        attached_t detached = (attached_t)(unattached);
        return detached;
    }
    virtual bool destroy_detached(attached_t detached) const {
        if ((attached_t)(unattached) != (detached)) {
            return true;
        }
        return false;
    }

    /// ...is_created / ...is_destroyed
    virtual bool set_is_created(bool to = true) {
        is_created_ = to;
        return is_created_;
    }
    virtual bool is_created() const {
        return is_created_;
    }
    virtual bool set_is_destroyed(bool to = true) {
        is_created_ = !to;
        return !is_created_;
    }
    virtual bool is_destroyed() const {
        return !is_created_;
    }

    /// attach... / detach...
    virtual attached_t attach_created(attached_t detached, bool is_created = true) {
        attached_t attached = this->attach(detached);
        this->set_is_created(is_created);
        return attached;
    }
    virtual attached_t detach_created(bool& is_created) {
        attached_t detached = extends::detach();
        is_created = this->is_created();
        this->set_is_created(false);
        return detached;
    }
    virtual attached_t detach() {
        attached_t detached = extends::detach();
        this->set_is_created(false);
        return detached;
    }

protected:
    bool is_created_;
}; /// class createdt
typedef createdt<> created;

namespace base {

typedef ::xos::create_exception create_exception;
static const create_exception create_failed = ::xos::create_failed;
static const create_exception destroy_failed = ::xos::destroy_failed;

typedef ::xos::create_status creator_exception;
static const creator_exception failed_to_create = ::xos::create_failed;
static const creator_exception failed_to_destroy = ::xos::destroy_failed;

/// class creatort
template <class TImplement = implement_base, class TImplements = ::xos::creatort<TImplement> >
class exported creatort: virtual public TImplements {
public:
    typedef TImplements implements, Implements;
    typedef creatort derives, Derives;

}; /// class creatort
typedef creatort<> creator;

/// class creator_extendt
template
<class TImplements = creator, class TExtends = base>
class exported creator_extendt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements, Implements;
    typedef TExtends extends, Extends;
    typedef creator_extendt derives, Derives;

    /// constructor / destructor
    creator_extendt(bool is_created = false): is_created_(is_created) {
    }
    virtual ~creator_extendt() {
    }

    /// ...is_created / ...is_destroyed
    virtual bool set_is_created(bool to = true) {
        is_created_ = to;
        return is_created_;
    }
    virtual bool is_created() const {
        return is_created_;
    }
    virtual bool is_destroyed() const {
        return !is_created_;
    }

protected:
    bool is_created_;
}; /// class creator_extendt
typedef creator_extendt<> creator_extend;

/// class createdt
template 
<typename TAttached = pointer_t, typename TUnattached = int, TUnattached VUnattached = 0,
 class TImplements = attachert<TAttached, TUnattached, VUnattached, creator>, 
 class TExtends = attachedt<TAttached, TUnattached, VUnattached, TImplements, base> >
class exported createdt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements, Implements;
    typedef TExtends extends, Extends;
    typedef createdt derives, Derives;

    typedef TAttached attached_t;
    typedef TUnattached unattached_t;
    enum { unattached = VUnattached };

    /// constructor / destructor
    createdt(attached_t detached, bool is_created): extends(detached), is_created_(is_created) {
    }
    createdt(attached_t detached): extends(detached), is_created_(false) {
    }
    createdt(const createdt& copy): extends(copy), is_created_(copy.is_created_) {
    }
    createdt(): is_created_(false) {
    }
    virtual ~createdt() {
        if (!(this->destroyed())) {
            throw (create_exception(destroy_failed));
        }
    }

    /// create... / destroy...
    virtual bool create() {
        attached_t detached = (attached_t)(unattached);
        if (((attached_t)(unattached) != (detached = this->create_attached()))) {
            this->set_is_created();
            return true;
        }
        return false;
    }
    virtual bool destroy() {
        attached_t detached = (attached_t)(unattached);
        this->set_is_created(false);
        if (((attached_t)(unattached) != (detached = this->detach()))) {
            if ((this->destroy_detached(detached))) {
                return true;
            }
        } else {
            return true;
        }
        return false;
    }
    virtual attached_t create_attached() {
        attached_t detached = (attached_t)(unattached);
        if ((this->destroyed())) {
            if (((attached_t)(unattached) != (detached = create_detached()))) {
                this->attach(detached);
            }
        }
        return detached;
    }
    virtual attached_t create_detached() const {
        attached_t detached = (attached_t)(unattached);
        return detached;
    }
    virtual bool destroy_detached(attached_t detached) const {
        if ((attached_t)(unattached) != (detached)) {
            return true;
        }
        return false;
    }

    /// ...is_created / ...is_destroyed
    virtual bool set_is_created(bool to = true) {
        is_created_ = to;
        return is_created_;
    }
    virtual bool is_created() const {
        return is_created_;
    }
    virtual bool set_is_destroyed(bool to = true) {
        is_created_ = !to;
        return !is_created_;
    }
    virtual bool is_destroyed() const {
        return !is_created_;
    }

    /// attach... / detach...
    virtual attached_t attach_created(attached_t detached, bool is_created = true) {
        attached_t attached = this->attach(detached);
        this->set_is_created(is_created);
        return attached;
    }
    virtual attached_t detach_created(bool& is_created) {
        attached_t detached = extends::detach();
        is_created = this->is_created();
        this->set_is_created(false);
        return detached;
    }
    virtual attached_t detach() {
        attached_t detached = extends::detach();
        this->set_is_created(false);
        return detached;
    }

protected:
    bool is_created_;
}; /// class createdt
typedef createdt<> created;

} /// namespace base
} /// namespace xos

#endif /// ndef XOS_BASE_CREATED_HPP
