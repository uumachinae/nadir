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
///   File: semaphore.hpp
///
/// Author: $author$
///   Date: 1/2/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_MT_SEMAPHORE_HPP
#define _NADIR_MT_SEMAPHORE_HPP

#include "nadir/base/acquired.hpp"
#include "nadir/base/waited.hpp"

namespace nadir {
namespace mt {

///////////////////////////////////////////////////////////////////////
///  Class: semaphoret_implements
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS semaphoret_implements
: virtual public waited, virtual public acquired {
};

///////////////////////////////////////////////////////////////////////
///  Class: semaphoret
///////////////////////////////////////////////////////////////////////
template <class TImplements = semaphoret_implements>
class _EXPORT_CLASS semaphoret: virtual public TImplements {
public:
    typedef TImplements Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool wait() {
        return this->acquire();
    }
    virtual wait_status try_wait() {
        return wait_status_of(this->try_acquire());
    }
    virtual wait_status untimed_wait() {
        return wait_status_of(this->untimed_acquire());
    }
    virtual wait_status timed_wait(mseconds_t milliseconds) {
        return wait_status_of(this->timed_acquire(milliseconds));
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual wait_status wait_status_of(acquire_status status) const {
        switch (status) {
        case acquire_success: return wait_success;
        case acquire_busy: return wait_busy;
        case acquire_interrupted: return wait_interrupted;
        case acquire_invalid: return wait_invalid;
        }
        return wait_failed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef semaphoret<> semaphore;

} // namespace mt 
} // namespace nadir 

#endif // _NADIR_MT_SEMAPHORE_HPP 
