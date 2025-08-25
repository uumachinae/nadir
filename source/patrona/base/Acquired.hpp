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
///   File: Acquired.hpp
///
/// Author: $author$
///   Date: 12/22/2018
///////////////////////////////////////////////////////////////////////
#ifndef _PATRONA_BASE_ACQUIRED_HPP
#define _PATRONA_BASE_ACQUIRED_HPP

#include "patrona/base/Base.hpp"

namespace patrona {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum AcquireStatus {
    ReleaseSuccess,
    AcquireSuccess = ReleaseSuccess,

    AcquireFailed,
    AcquireBusy,
    AcquireInterrupted,
    AcquireInvalid,

    ReleaseFailed,
    ReleaseBusy,
    ReleaseInterrupted,
    ReleaseInvalid
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
inline const char* AcquireStatusToChars(AcquireStatus status) {
    switch (status) {
    case AcquireSuccess: return "AcquireSuccess";
    case AcquireFailed: return "AcquireFailed";
    case AcquireBusy: return "AcquireBusy";
    case AcquireInterrupted: return "AcquireInterrupted";
    case AcquireInvalid: return "AcquireInvalid";

    case ReleaseFailed: return "ReleaseFailed";
    case ReleaseBusy: return "ReleaseBusy";
    case ReleaseInterrupted: return "ReleaseInterrupted";
    case ReleaseInvalid: return "ReleaseInvalid";
    }
    return "Unknown";
}

typedef ImplementBase AcquireExceptionImplements;
typedef Base AcquireExceptionExtends;
///////////////////////////////////////////////////////////////////////
///  Class: AcquireExceptionT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = AcquireExceptionImplements,
 class TExtends = AcquireExceptionExtends>

class _EXPORT_CLASS AcquireExceptionT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    AcquireExceptionT(AcquireStatus status): m_status(status) {}
    virtual ~AcquireExceptionT() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual AcquireStatus Status() const {
        return m_status;
    }
    virtual String StatusToString() const {
        String to(StatusToChars());
        return to;
    }
    virtual const char* StatusToChars() const {
        return AcquireStatusToChars(Status());
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    AcquireStatus m_status;
};
typedef AcquireExceptionT<> AcquireException;

typedef ImplementBase AcquiredTImplements;
///////////////////////////////////////////////////////////////////////
///  Class: AcquiredT
///////////////////////////////////////////////////////////////////////
template
<class TAcquireException = AcquireException,
 class TImplements = AcquiredTImplements>

class _EXPORT_CLASS AcquiredT: virtual public TImplements {
public:
    typedef TImplements Implements;
    typedef TAcquireException AcquireException;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Acquire() { return false; }
    virtual AcquireStatus TryAcquire() { return AcquireFailed; }
    virtual AcquireStatus TimedAcquire(mseconds_t milliseconds) { return AcquireFailed; }
    virtual AcquireStatus UntimedAcquire() { return AcquireFailed; }
    virtual bool Release() { return false; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef AcquiredT<> Acquired;

typedef ImplementBase AcquirerTImplements;
typedef Base AcquirerTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: AcquirerT
///////////////////////////////////////////////////////////////////////
template
<class TAcquired = Acquired,
 class TAcquireException = AcquireException,
 class TImplements = AcquirerTImplements,
 class TExtends = AcquirerTExtends>

class _EXPORT_CLASS AcquirerT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef TAcquired Acquired;
    typedef TAcquireException AcquireException;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    AcquirerT
    (Acquired& acquired, mseconds_t milliseconds): m_acquired(acquired) {
        AcquireStatus status = AcquireSuccess;
        if (AcquireSuccess != (status = m_acquired.TimedAcquire(milliseconds))) {
            AcquireException e(AcquireFailed);
            throw (e);
        }
    }
    AcquirerT(Acquired& acquired): m_acquired(acquired) {
        if (!(m_acquired.Acquire())) {
            AcquireException e(AcquireFailed);
            throw (e);
        }
    }
    virtual ~AcquirerT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Acquired& m_acquired;
};
typedef AcquirerT<> Acquirer;

typedef ImplementBase ReleaserTImplements;
typedef Base ReleaserTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: ReleaserT
///////////////////////////////////////////////////////////////////////
template
<class TAcquired = Acquired,
 class TAcquireException = AcquireException,
 class TImplements = ReleaserTImplements,
 class TExtends = ReleaserTExtends>

class _EXPORT_CLASS ReleaserT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef TAcquired Acquired;
    typedef TAcquireException AcquireException;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ReleaserT(Acquired& acquired): m_acquired(acquired) {
        if (!(m_acquired.Release())) {
            AcquireException e(ReleaseFailed);
            throw (e);
        }
    }
    virtual ~ReleaserT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Acquired& m_acquired;
};
typedef ReleaserT<> Releaser;

} // namespace patrona

#endif // _PATRONA_BASE_ACQUIRED_HPP
