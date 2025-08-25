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
///   File: Locked.hpp
///
/// Author: $author$
///   Date: 12/22/2018, 8/16/2025
///////////////////////////////////////////////////////////////////////
#ifndef _PATRONA_BASE_LOCKED_HPP
#define _PATRONA_BASE_LOCKED_HPP

#include "patrona/base/Base.hpp"

namespace patrona {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum LockStatus {
    UnlockSuccess,
    LockSuccess = UnlockSuccess,

    LockFailed,
    LockBusy,
    LockInterrupted,
    LockInvalid,

    UnlockFailed,
    UnlockBusy,
    UnlockInterrupted,
    UnlockInvalid
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
inline const char* LockStatusToChars(LockStatus status) {
    switch (status) {
    case LockSuccess: return "LockSuccess";
    case LockFailed: return "LockFailed";
    case LockBusy: return "LockBusy";
    case LockInterrupted: return "LockInterrupted";
    case LockInvalid: return "LockInvalid";

    case UnlockFailed: return "UnlockFailed";
    case UnlockBusy: return "UnlockBusy";
    case UnlockInterrupted: return "UnlockInterrupted";
    case UnlockInvalid: return "UnlockInvalid";
    }
    return "Unknown";
}

typedef ImplementBase LockExceptionTImplements;
typedef Base LockExceptionTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: LockExceptionT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = LockExceptionTImplements,
 class TExtends = LockExceptionTExtends>

class _EXPORT_CLASS LockExceptionT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    LockExceptionT(LockStatus status): m_status(status) {}
    virtual ~LockExceptionT() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual LockStatus Status() const {
        return m_status;
    }
    virtual String StatusToString() const {
        String to(StatusToChars());
        return to;
    }
    virtual const char* StatusToChars() const {
        return LockStatusToChars(Status());
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    LockStatus m_status;
};
typedef LockExceptionT<> LockException;

typedef ImplementBase LockedTImplements;
///////////////////////////////////////////////////////////////////////
///  Class: LockedT
///////////////////////////////////////////////////////////////////////
template
<class TLockException = LockException,
 class TImplements = LockedTImplements>

class _EXPORT_CLASS LockedT: virtual public TImplements {
public:
    typedef TImplements Implements;
    typedef TLockException LockException;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Lock() { return false; }
    virtual LockStatus TryLock() { return LockFailed; }
    virtual LockStatus TimedLock(mseconds_t milliseconds) { return LockFailed; }
    virtual LockStatus UntimedLock() { return LockFailed; }
    virtual bool Unlock() { return false; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef LockedT<> Locked;

typedef ImplementBase LockerTImplements;
typedef Base LockerTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: LockerT
///////////////////////////////////////////////////////////////////////
template
<class TLocked = Locked,
 class TLockException = LockException,
 class TImplements = LockerTImplements,
 class TExtends = LockerTExtends>

class _EXPORT_CLASS LockerT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef TLocked Locked;
    typedef TLockException LockException;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    LockerT(Locked& locked, mseconds_t milliseconds): m_locked(locked) {
        if ((0 > (milliseconds))) {
            if (!(m_locked.Lock())) {
                LockException e(LockFailed);
                throw (e);
            }
        } else {
            LockStatus status = LockFailed;
            if ((0 < (milliseconds))) {
                if (LockSuccess != (status = m_locked.TimedLock(milliseconds))) {
                    LockException e((LockBusy != status)?(LockFailed):(LockBusy));
                    throw (e);
                }
            } else {
                if (LockSuccess != (m_locked.TryLock())) {
                    LockException e((LockBusy != status)?(LockFailed):(LockBusy));
                    throw (e);
                }
            }
        }
    }
    LockerT(Locked& locked): m_locked(locked) {
        if (!(m_locked.Lock())) {
            LockException e(LockFailed);
            throw (e);
        }
    }
    virtual ~LockerT() {
        if (!(m_locked.Unlock())) {
            LockException e(UnlockFailed);
            throw (e);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Locked& m_locked;
};
typedef LockerT<> Locker;

} // namespace patrona

#endif // _PATRONA_BASE_LOCKED_HPP
