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
///   File: joined.hpp
///
/// Author: $author$
///   Date: 5/10/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_BASE_JOINED_HPP
#define _NADIR_BASE_JOINED_HPP

#include "nadir/base/exception.hpp"

namespace nadir {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum join_status {
    fork_success,
    join_success = fork_success,

    join_failed,
    join_busy,
    join_interrupted,
    join_invalid,

    fork_failed,
    fork_busy,
    fork_interrupted,
    fork_invalid
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
inline const char* join_status_to_chars(join_status status) {
    switch (status) {
    case join_success: return "join_success";
    case join_failed: return "join_failed";
    case join_busy: return "join_busy";
    case join_interrupted: return "join_interrupted";
    case join_invalid: return "join_invalid";

    case fork_failed: return "fork_failed";
    case fork_busy: return "fork_busy";
    case fork_interrupted: return "fork_interrupted";
    case fork_invalid: return "fork_invalid";
    }
    return "unknown";
}

typedef exceptiont_implements join_exceptiont_implements;
typedef exceptiont<join_status> join_exceptiont_extends;
///////////////////////////////////////////////////////////////////////
///  Class: join_exceptiont
///////////////////////////////////////////////////////////////////////
template
<class TImplements = join_exceptiont_implements,
 class TExtends = join_exceptiont_extends>

class _EXPORT_CLASS join_exceptiont
: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    join_exceptiont(join_status status): Extends(status) {}
    virtual ~join_exceptiont() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* status_to_chars() const {
        return join_status_to_chars(this->status());
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef join_exceptiont<> join_exception;

typedef implement_base joinedt_implements;
///////////////////////////////////////////////////////////////////////
///  Class: joinedt
///////////////////////////////////////////////////////////////////////
template <class TImplements = joinedt_implements>
class _EXPORT_CLASS joinedt: virtual public TImplements {
public:
    typedef TImplements Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool joined() {
        if ((this->is_forked())) {
            return this->join();
        }
        return true;
    }
    virtual bool join() {
        return false;
    }
    virtual join_status untimed_join() {
        return join_failed;
    }
    virtual join_status timed_join(mseconds_t milliseconds) {
        return join_failed;
    }
    virtual join_status try_join() {
        return join_failed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_is_forked(bool to = true) {
        return false;
    }
    virtual bool is_forked() const {
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef joinedt<> joined;

} // namespace nadir 

#endif // _NADIR_BASE_JOINED_HPP 
