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
///   File: attached.hpp
///
/// Author: $author$
///   Date: 12/26/2016
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_BASE_ATTACHED_HPP
#define _NADIR_BASE_ATTACHED_HPP

#include "nadir/base/exception.hpp"

namespace nadir {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum attach_status {
    detach_success,
    attach_success = detach_success,

    attach_failed,
    detach_failed
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
inline const char* attach_status_to_chars(attach_status status) {
    switch (status) {
    case attach_success: return "attach_success";
    case attach_failed: return "attach_failed";
    case detach_failed: return "detach_failed";
    }
    return "unknown";
}

typedef exceptiont_implements attach_exception_implements;
typedef exceptiont<attach_status> attach_exception_extends;
///////////////////////////////////////////////////////////////////////
///  Class: attach_exceptiont
///////////////////////////////////////////////////////////////////////
template
<class TImplements = attach_exception_implements,
 class TExtends = attach_exception_extends>

class _EXPORT_CLASS attach_exceptiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    attach_exceptiont(attach_status status): Extends(status) {}
    virtual ~attach_exceptiont() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* status_to_chars() const {
        return attach_status_to_chars(this->status());
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef attach_exceptiont<> attach_exception;

typedef implement_base attachert_implements;
///////////////////////////////////////////////////////////////////////
///  Class: attachert
///////////////////////////////////////////////////////////////////////
template
<typename TAttached = void*,
 typename TUnattached = int,
 TUnattached VUnattached = 0,
 class TImplements = attachert_implements>

class _EXPORT_CLASS attachert: virtual public TImplements {
public:
    typedef TImplements Implements;

    typedef TAttached attached_t;
    typedef TUnattached unattached_t;
    enum { unattached = VUnattached };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool detached() {
        if (((attached_t)unattached) != (this->attached_to())) {
            if (((attached_t)unattached) != (this->detach())) {
                return true;
            }
            return false;
        }
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual attached_t attach(attached_t detached) {
        return ((attached_t)unattached);
    }
    virtual attached_t detach() {
        return ((attached_t)unattached);
    }
    virtual attached_t attached_to() const {
        return ((attached_t)unattached);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef attachert<> attacher;

typedef base attachedt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: attachedt
///////////////////////////////////////////////////////////////////////
template
<typename TAttached = void*,
 typename TUnattached = int,
 TUnattached VUnattached = 0,
 class TImplements = attachert
 <TAttached, TUnattached, VUnattached, attachert_implements>,
 class TExtends = attachedt_extends>

class _EXPORT_CLASS attachedt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TAttached attached_t;
    typedef TUnattached unattached_t;
    enum { unattached = VUnattached };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    attachedt(attached_t detached = ((attached_t)unattached))
    : attached_to_(detached) {
    }
    virtual ~attachedt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
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

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    attached_t attached_to_;
};
typedef attachedt<> attached;

} // namespace nadir

#endif // _NADIR_BASE_ATTACHED_HPP 
