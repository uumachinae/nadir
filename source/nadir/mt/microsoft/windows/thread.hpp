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
///   File: thread.hpp
///
/// Author: $author$
///   Date: 9/30/2018
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_MT_MICROSOFT_WINDOWS_THREAD_HPP
#define _NADIR_MT_MICROSOFT_WINDOWS_THREAD_HPP

#include "nadir/mt/thread.hpp"

namespace nadir {
namespace mt {
namespace microsoft {
namespace windows {

typedef HANDLE thread_attached_t;
typedef creatort<mt::thread> thread_creator;
typedef attachert<thread_attached_t, int, 0, thread_creator> thread_attacher;
typedef attachedt<thread_attached_t, int, 0, thread_attacher, base> thread_attached;
typedef createdt<thread_attached_t, int, 0, thread_attacher, thread_attached> thread_created;
typedef thread_attacher threadt_implements;
typedef thread_created threadt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: threadt
///////////////////////////////////////////////////////////////////////
template 
<class TImplements = threadt_implements, class TExtends = threadt_extends>
class _EXPORT_CLASS threadt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef typename Implements::ran_t ran_t;
    typedef typename Implements::attached_t attached_t;
    typedef typename Implements::unattached_t unattached_t;
    enum { unattached = Implements::unattached };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    threadt(ran_t& ran, attached_t attached, bool forked = false)
    : Extends(attached, forked), ran_(ran), forked_(forked) {
    }
    threadt(attached_t attached, bool forked = false)
    : Extends(attached, forked), ran_(*this), forked_(forked) {
    }
    threadt(ran_t& ran): ran_(ran), forked_(false) {
        if (!(this->create())) {
            create_exception e(create_failed);
            throw (e);
        }
    }
    threadt(): ran_(*this), forked_(false) {
        if (!(this->create())) {
            create_exception e(create_failed);
            throw (e);
        }
    }
    virtual ~threadt() {
        if (!(this->destroyed())) {
            create_exception e(destroy_failed);
            throw (e);
        }
    }
private:
	threadt(const threadt &copy) {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    ran_t& ran_;
    bool forked_;
};
typedef threadt<> thread;

} /// namespace windows
} /// namespace microsoft
} /// namespace mt
} /// namespace nadir

#endif /// _NADIR_MT_MICROSOFT_WINDOWS_THREAD_HPP 
