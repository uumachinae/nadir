///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2017 $organization$
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
///   File: signaler.hpp
///
/// Author: $author$
///   Date: 6/14/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_MT_SIGNALER_HPP
#define _NADIR_MT_SIGNALER_HPP

#include "nadir/mt/os/mutex.hpp"
#include "nadir/base/locked.hpp"

namespace nadir {
namespace mt {

typedef implement_base signalert_implements;
typedef base signalert_extends;
///////////////////////////////////////////////////////////////////////
///  Class: signalert
///////////////////////////////////////////////////////////////////////
template
<typename TRaised = bool, TRaised VRaised = true, TRaised VLowered = false,
 class TImplements = signalert_implements, class TExtends = signalert_extends>

class _EXPORT_CLASS signalert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    signalert(TRaised& raised): raise_(VLowered), raised_(raised) {
    }
    signalert(): raise_(VLowered), raised_(raise_) {
    }
    virtual ~signalert() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void operator()(TRaised raised = VRaised) {
        locker lock(lock_);
        raised_ = raised;
    }
    virtual operator TRaised() {
        locker lock(lock_);
        TRaised raised = raised_;
        return raised;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    TRaised raise_;
    TRaised& raised_;
    mt::os::mutex lock_;
};
typedef signalert<> signaler;

} // namespace mt 
} // namespace nadir 

#endif // _NADIR_MT_SIGNAL_HPP 
