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
///   File: Joined.hpp
///
/// Author: $author$
///   Date: 12/22/2018
///////////////////////////////////////////////////////////////////////
#ifndef _PATRONA_BASE_JOINED_HPP
#define _PATRONA_BASE_JOINED_HPP

#include "patrona/base/Base.hpp"

namespace patrona {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum JoinStatus {
    ForkSuccess,
    JoinSuccess = ForkSuccess,

    JoinFailed,
    JoinBusy,
    JoinInterrupted,
    JoinInvalid,

    ForkFailed,
    ForkBusy,
    ForkInterrupted,
    ForkInvalid
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
inline const char* JoinStatusToChars(JoinStatus status) {
    switch (status) {
    case JoinSuccess: return "JoinSuccess";
    case JoinFailed: return "JoinFailed";
    case JoinBusy: return "JoinBusy";
    case JoinInterrupted: return "JoinInterrupted";
    case JoinInvalid: return "JoinInvalid";

    case ForkFailed: return "ForkFailed";
    case ForkBusy: return "ForkBusy";
    case ForkInterrupted: return "ForkInterrupted";
    case ForkInvalid: return "ForkInvalid";
    }
    return "Unknown";
}

typedef ImplementBase JoinExceptionImplements;
typedef Base JoinExceptionExtends;
///////////////////////////////////////////////////////////////////////
///  Class: JoinExceptionT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = JoinExceptionImplements,
 class TExtends = JoinExceptionExtends>

class _EXPORT_CLASS JoinExceptionT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    JoinExceptionT(JoinStatus status): m_status(status) {}
    virtual ~JoinExceptionT() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual JoinStatus Status() const {
        return m_status;
    }
    virtual String StatusToString() const {
        String to(StatusToChars());
        return to;
    }
    virtual const char* StatusToChars() const {
        return JoinStatusToChars(Status());
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    JoinStatus m_status;
};
typedef JoinExceptionT<> JoinException;

typedef ImplementBase JoinedTImplements;
///////////////////////////////////////////////////////////////////////
///  Class: JoinedT
///////////////////////////////////////////////////////////////////////
template
<class TJoinException = JoinException,
 class TImplements = JoinedTImplements>

class _EXPORT_CLASS JoinedT: virtual public TImplements {
public:
    typedef TImplements Implements;
    typedef TJoinException JoinException;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Join() { return false; }
    virtual JoinStatus TryJoin() { return JoinFailed; }
    virtual JoinStatus TimedJoin(mseconds_t milliseconds) { return JoinFailed; }
    virtual JoinStatus UntimedJoin() { return JoinFailed; }
    virtual bool Fork() { return false; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef JoinedT<> Joined;

typedef ImplementBase JoinerTImplements;
typedef Base JoinerTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: JoinerT
///////////////////////////////////////////////////////////////////////
template
<class TJoined = Joined,
 class TJoinException = JoinException,
 class TImplements = JoinerTImplements,
 class TExtends = JoinerTExtends>

class _EXPORT_CLASS JoinerT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef TJoined Joined;
    typedef TJoinException JoinException;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    JoinerT(Joined& joined): m_joined(joined) {
        if (!(m_joined.Join())) {
            JoinException e(JoinFailed);
            throw (e);
        }
    }
    virtual ~JoinerT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Joined& m_joined;
};
typedef JoinerT<> Joiner;

typedef ImplementBase ForkerTImplements;
typedef Base ForkerTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: ForkerT
///////////////////////////////////////////////////////////////////////
template
<class TJoined = Joined,
 class TJoinException = JoinException,
 class TImplements = ForkerTImplements,
 class TExtends = ForkerTExtends>

class _EXPORT_CLASS ForkerT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef TJoined Joined;
    typedef TJoinException JoinException;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ForkerT(Joined& joined): m_joined(joined) {
        if (!(m_joined.Fork())) {
            JoinException e(ForkFailed);
            throw (e);
        }
    }
    virtual ~ForkerT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Joined& m_joined;
};
typedef ForkerT<> Forker;

typedef Joined ForkedTImplements;
typedef Base ForkedTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: ForkedT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = ForkedTImplements, class TExtends = ForkedTExtends>

class _EXPORT_CLASS ForkedT: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ForkedT(): m_isForked(false) {
    }
    virtual ~ForkedT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Joined() {
        if ((this->IsForked())) {
            return this->Join();
        }
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetIsForked(bool to = true) {
        m_isForked = to;
        return m_isForked;
    }
    virtual bool IsForked() const {
        return m_isForked;
    }
    virtual bool SetIsJoined(bool to = true) {
        m_isForked = !to;
        return !m_isForked;
    }
    virtual bool IsJoined() const {
        return !m_isForked;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool m_isForked;
};

} // namespace patrona

#endif // _PATRONA_BASE_JOINED_HPP
