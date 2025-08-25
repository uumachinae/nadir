///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2016 $organization$
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
///   Date: 12/26/2016
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_BASE_CREATED_HPP
#define _NADIR_BASE_CREATED_HPP

#include "nadir/base/attached.hpp"
#include "nadir/base/exception.hpp"

namespace nadir {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum create_status {
    destroy_success,
    create_success = destroy_success,
    create_failed,
    destroy_failed
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
inline const char* create_status_to_chars(create_status status) {
    switch (status) {
    case create_success: return "create_success";
    case create_failed: return "create_failed";
    case destroy_failed: return "destroy_failed";
    }
    return "unknown";
}

typedef exceptiont_implements create_exceptiont_implements;
typedef exceptiont<create_status> create_exceptiont_extends;
///////////////////////////////////////////////////////////////////////
///  Class: create_exceptiont
///////////////////////////////////////////////////////////////////////
template
<class TImplements = create_exceptiont_implements,
 class TExtends = create_exceptiont_extends>

class _EXPORT_CLASS create_exceptiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    create_exceptiont(create_status status): Extends(status) {}
    virtual ~create_exceptiont() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* status_to_chars() const {
        return create_status_to_chars(this->status());
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef create_exceptiont<> create_exception;

typedef implement_base creatort_implements;
///////////////////////////////////////////////////////////////////////
///  Class: creatort
///////////////////////////////////////////////////////////////////////
template
<class TImplements = creatort_implements>

class _EXPORT_CLASS creatort: virtual public TImplements {
public:
    typedef TImplements Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
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
    virtual bool destroyed() {
        if ((this->is_created())) {
            if ((this->destroy())) {
                return true;
            }
        }
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_is_created(bool to = true) {
        return false;
    }
    virtual bool is_created() const {
        return false;
    }
    virtual bool is_destroyed() const {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef creatort<> creator;

typedef creator createdt_implements;
typedef base createdt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: createdt
///////////////////////////////////////////////////////////////////////
template
<typename TAttached = void*,
 typename TUnattached = int,
 TUnattached VUnattached = 0,
 class TImplements = attachert
 <TAttached, TUnattached, VUnattached, createdt_implements>,
 class TExtends = attachedt
 <TAttached, TUnattached, VUnattached, TImplements, createdt_extends> >

class _EXPORT_CLASS createdt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TAttached attached_t;
    typedef TUnattached unattached_t;
    enum { unattached = VUnattached };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    createdt
    (attached_t detached = (attached_t)(unattached), bool is_created = false)
    : Extends(detached), is_created_(is_created) {
    }
    virtual ~createdt() {
        if (!(this->destroyed())) {
            create_exception e(destroy_failed);
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
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

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
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

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
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

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual attached_t attach_created(attached_t detached, bool is_created = true) {
        attached_t attached = this->attach(detached);
        this->set_is_created(is_created);
        return attached;
    }
    virtual attached_t detach_created(bool& is_created) {
        attached_t detached = Extends::detach();
        is_created = this->is_created();
        this->set_is_created(false);
        return detached;
    }
    virtual attached_t detach() {
        attached_t detached = Extends::detach();
        this->set_is_created(false);
        return detached;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool is_created_;
};

} // namespace nadir

#endif // _NADIR_BASE_CREATED_HPP 
