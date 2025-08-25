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
///   File: Waited.hpp
///
/// Author: $author$
///   Date: 12/22/2018
///////////////////////////////////////////////////////////////////////
#ifndef _PATRONA_BASE_WAITED_HPP
#define _PATRONA_BASE_WAITED_HPP

#include "patrona/base/Base.hpp"

namespace patrona {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum WaitStatus {
    ContinueSuccess,
    WaitSuccess = ContinueSuccess,

    WaitFailed,
    WaitBusy,
    WaitInterrupted,
    WaitInvalid,

    ContinueFailed,
    ContinueBusy,
    ContinueInterrupted,
    ContinueInvalid
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
inline const char* WaitStatusToChars(WaitStatus status) {
    switch (status) {
    case WaitSuccess: return "WaitSuccess";
    case WaitFailed: return "WaitFailed";
    case WaitBusy: return "WaitBusy";
    case WaitInterrupted: return "WaitInterrupted";
    case WaitInvalid: return "WaitInvalid";

    case ContinueFailed: return "ContinueFailed";
    case ContinueBusy: return "ContinueBusy";
    case ContinueInterrupted: return "ContinueInterrupted";
    case ContinueInvalid: return "ContinueInvalid";
    }
    return "Unknown";
}

typedef ImplementBase WaitExceptionImplements;
typedef Base WaitExceptionExtends;
///////////////////////////////////////////////////////////////////////
///  Class: WaitExceptionT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = WaitExceptionImplements,
 class TExtends = WaitExceptionExtends>

class _EXPORT_CLASS WaitExceptionT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    WaitExceptionT(WaitStatus status): m_status(status) {}
    virtual ~WaitExceptionT() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual WaitStatus Status() const {
        return m_status;
    }
    virtual String StatusToString() const {
        String to(StatusToChars());
        return to;
    }
    virtual const char* StatusToChars() const {
        return WaitStatusToChars(Status());
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    WaitStatus m_status;
};
typedef WaitExceptionT<> WaitException;

typedef ImplementBase WaitedTImplements;
///////////////////////////////////////////////////////////////////////
///  Class: WaitedT
///////////////////////////////////////////////////////////////////////
template
<class TWaitException = WaitException,
 class TImplements = WaitedTImplements>

class _EXPORT_CLASS WaitedT: virtual public TImplements {
public:
    typedef TImplements Implements;
    typedef TWaitException WaitException;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Wait() { return false; }
    virtual WaitStatus TryWait() { return WaitFailed; }
    virtual WaitStatus TimedWait(mseconds_t milliseconds) { return WaitFailed; }
    virtual WaitStatus UntimedWait() { return WaitFailed; }
    virtual bool Continue() { return false; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef WaitedT<> Waited;

typedef ImplementBase WaiterTImplements;
typedef Base WaiterTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: WaiterT
///////////////////////////////////////////////////////////////////////
template
<class TWaited = Waited,
 class TWaitException = WaitException,
 class TImplements = WaiterTImplements,
 class TExtends = WaiterTExtends>

class _EXPORT_CLASS WaiterT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef TWaited Waited;
    typedef TWaitException WaitException;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    WaiterT(Waited& waited): m_waited(waited) {
        if (!(m_waited.Wait())) {
            WaitException e(WaitFailed);
            throw (e);
        }
    }
    virtual ~WaiterT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Waited& m_waited;
};
typedef WaiterT<> Waiter;

typedef ImplementBase ContinuerTImplements;
typedef Base ContinuerTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: ContinuerT
///////////////////////////////////////////////////////////////////////
template
<class TWaited = Waited,
 class TWaitException = WaitException,
 class TImplements = ContinuerTImplements,
 class TExtends = ContinuerTExtends>

class _EXPORT_CLASS ContinuerT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef TWaited Waited;
    typedef TWaitException WaitException;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ContinuerT(Waited& waited): m_waited(waited) {
        if (!(m_waited.Continue())) {
            WaitException e(ContinueFailed);
            throw (e);
        }
    }
    virtual ~ContinuerT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Waited& m_waited;
};
typedef ContinuerT<> Continuer;

} // namespace patrona

#endif // _PATRONA_BASE_WAITED_HPP
