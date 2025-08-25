///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2018 $organization$
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
///   File: Attached.hpp
///
/// Author: $author$
///   Date: 12/22/2018
///////////////////////////////////////////////////////////////////////
#ifndef _PATRONA_BASE_ATTACHED_HPP
#define _PATRONA_BASE_ATTACHED_HPP

#include "patrona/base/Base.hpp"

namespace patrona {

///////////////////////////////////////////////////////////////////////
///  Enum: AttachStatus
///////////////////////////////////////////////////////////////////////
enum AttachStatus {
    DetachSuccess,
    AttachSuccess = DetachSuccess,
    AttachFailed,
    DetachFailed
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
inline const char* AttachStatusToChars(AttachStatus status) {
    switch (status) {
    case AttachSuccess: return "AttachSuccess";
    case AttachFailed: return "AttachFailed";
    case DetachFailed: return "DetachFailed";
    }
    return "Unknown";
}

typedef ImplementBase AttachExceptionTImplements;
typedef Base AttachExceptionTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: AttachExceptionT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = AttachExceptionTImplements,
 class TExtends = AttachExceptionTExtends>

class _EXPORT_CLASS AttachExceptionT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    AttachExceptionT(AttachStatus status): m_status(status) {}
    virtual ~AttachExceptionT() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual AttachStatus Status() const {
        return m_status;
    }
    virtual String StatusToString() const {
        String to(StatusToChars());
        return to;
    }
    virtual const char* StatusToChars() const {
        return AttachStatusToChars(Status());
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    AttachStatus m_status;
};
typedef AttachExceptionT<> AttachException;

typedef ImplementBase AttacherTImplements;
///////////////////////////////////////////////////////////////////////
///  Class: AttacherT
///////////////////////////////////////////////////////////////////////
template
<class TAttached, class TUnattached = TAttached,
 TUnattached VUnattached = 0, class TImplements = AttacherTImplements>

class _EXPORT_CLASS AttacherT: virtual public TImplements {
public:
    typedef TImplements Implements;
    typedef TAttached Attached;
    static const TUnattached Unattached = VUnattached;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Attached Attach(Attached attachedTo) {
        return ((Attached)Unattached);
    }
    virtual Attached Detach() {
        return ((Attached)Unattached);
    }
    virtual bool Detached() {
        if (((Attached)Unattached) != (this->AttachedTo())) {
            if (((Attached)Unattached) == (this->Detach())) {
                return false;
            }
        }
        return true;
    }
    virtual Attached AttachedTo() const {
        return ((Attached)Unattached);
    }
    virtual operator Attached() const {
        return AttachedTo();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef Base AttachedTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: AttachedT
///////////////////////////////////////////////////////////////////////
template
<class TAttached,
 class TUnattached = TAttached, TUnattached VUnattached = 0,
 class TImplements = AttacherT
 <TAttached, TUnattached, VUnattached, AttacherTImplements>,
 class TExtends = AttachedTExtends>

class _EXPORT_CLASS AttachedT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef TAttached Attached;
    static const TUnattached Unattached = VUnattached;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    AttachedT(Attached attachedTo): m_attachedTo(attachedTo) {
    }
    AttachedT(const AttachedT& copy): m_attachedTo(copy.m_attachedTo) {
    }
    AttachedT(): m_attachedTo(((Attached)Unattached)) {
    }
    virtual ~AttachedT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Attached Attach(Attached attachedTo) {
        return m_attachedTo = attachedTo;
    }
    virtual Attached Detach() {
        Attached detached = m_attachedTo;
        m_attachedTo = ((Attached)Unattached);
        return detached;
    }
    virtual Attached AttachedTo() const {
        return m_attachedTo;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Attached m_attachedTo;
};

} // namespace patrona

#endif // _PATRONA_BASE_ATTACHED_HPP
        

