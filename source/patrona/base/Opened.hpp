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
///   File: Opened.hpp
///
/// Author: $author$
///   Date: 12/22/2018
///////////////////////////////////////////////////////////////////////
#ifndef _PATRONA_BASE_OPENED_HPP
#define _PATRONA_BASE_OPENED_HPP

#include "patrona/base/Attached.hpp"

namespace patrona {

///////////////////////////////////////////////////////////////////////
///  Enum: OpenStatus
///////////////////////////////////////////////////////////////////////
enum OpenStatus {
    CloseSuccess,
    OpenSuccess = CloseSuccess,
    OpenFailed,
    CloseFailed
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
inline const char* OpenStatusToChars(OpenStatus status) {
    switch (status) {
    case OpenSuccess: return "OpenSuccess";
    case OpenFailed: return "OpenFailed";
    case CloseFailed: return "CloseFailed";
    }
    return "Unknown";
}

typedef ImplementBase OpenExceptionTImplements;
typedef Base OpenExceptionTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: OpenExceptiont
///////////////////////////////////////////////////////////////////////
template
<class TImplements = OpenExceptionTImplements,
 class TExtends = OpenExceptionTExtends>

class _EXPORT_CLASS OpenExceptiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    OpenExceptiont(OpenStatus status): m_status(status) {}
    virtual ~OpenExceptiont() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual OpenStatus Status() const {
        return m_status;
    }
    virtual String StatusToString() const {
        String to(StatusToChars());
        return to;
    }
    virtual const char* StatusToChars() const {
        return OpenStatusToChars(Status());
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    OpenStatus m_status;
};
typedef OpenExceptiont<> OpenException;

typedef ImplementBase OpenerTImplements;
///////////////////////////////////////////////////////////////////////
///  Class: OpenerT
///////////////////////////////////////////////////////////////////////
template <class TImplements = OpenerTImplements>
class _EXPORT_CLASS OpenerT: virtual public TImplements {
public:
    typedef TImplements Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Open() { return false; }
    virtual bool Close() { return false; }
    virtual bool Closed() {
        if ((IsOpen())) {
            return Close();
        }
        return true; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetIsOpen(bool isTrue = true) { return false; }
    virtual bool IsOpen() const { return false; }
    virtual bool IsClosed() const { return !IsOpen(); }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef OpenerT<> Opener;

typedef Opener OpenedTImplements;
typedef Base OpenedTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: OpenedT
///////////////////////////////////////////////////////////////////////
template
<typename TAttached,
 typename TUnattached = TAttached, TUnattached VUnattached = 0,
 class TImplements = AttacherT
  <TAttached, TUnattached, VUnattached, OpenedTImplements>,
 class TExtends = AttachedT
 <TAttached, TUnattached, VUnattached, TImplements, OpenedTExtends> >

class _EXPORT_CLASS OpenedT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TAttached Attached;
    static const TUnattached Unattached = VUnattached;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    OpenedT(Attached attachedTo, bool isOpen)
    : Extends(attachedTo), m_isOpen(isOpen) {
    }
    OpenedT(Attached attachedTo)
    : Extends(attachedTo), m_isOpen(false) {
    }
    OpenedT(const OpenedT& copy)
    : Extends(copy.AttachedTo()), m_isOpen(false) {
    }
    OpenedT()
    : Extends(((Attached)Unattached)), m_isOpen(false) {
    }
    virtual ~OpenedT() {
        if (!(this->Closed())) {
            OpenException e(CloseFailed);
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Attached AttachOpened
    (Attached attachedTo, bool isOpen = true) {
        attachedTo = this->Attach(attachedTo);
        this->SetIsOpen(isOpen);
        return attachedTo;
    }
    virtual Attached DetachOpened(bool& isOpen){
        Attached detached = this->Detach();
        isOpen = this->IsOpen();
        this->SetIsOpen(false);
        return detached;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Attached Attach(Attached attachedTo) {
        attachedTo = Extends::Attach(attachedTo);
        this->SetIsOpen(false);
        return attachedTo;
    }
    virtual Attached Detach(){
        Attached detached = Extends::Detach();
        this->SetIsOpen(false);
        return detached;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetIsOpen(bool isTrue = true) {
        m_isOpen = isTrue;
        return m_isOpen;
    }
    virtual bool IsOpen() const {
        return m_isOpen;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool m_isOpen;
};

} // namespace patrona

#endif // _PATRONA_BASE_OPENED_HPP 
