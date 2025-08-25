///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2019 $organization$
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
///   Date: 1/20/2020
///////////////////////////////////////////////////////////////////////
#ifndef XOS_BASE_JOINED_HPP
#define XOS_BASE_JOINED_HPP

#include "xos/base/forked.hpp"

namespace xos {

/// enum join_status
typedef int join_status;
enum {
    /// join...
    join_success = fork_success,
    join_failed = next_fork,
    join_busy,
    join_timeout,
    join_interrupted,
    next_join,
    first_join = join_failed,
    last_join = join_interrupted,
}; /// enum join_status

/// function join_status_to_chars
inline const char* join_status_to_chars(join_status status) {
    switch(status) {
    /// join...
    case join_success: return "join_success";
    case join_failed: return "join_failed";
    case join_busy: return "join_busy";
    case join_timeout: return "join_timeout";
    case join_interrupted: return "join_interrupted";
    }
    return "unknown";
} /// function join_status_to_chars

/// class join_exceptiont
template <class TExtends = exceptiont<join_status>, class TImplements = typename TExtends::implements>
class exported join_exceptiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef join_exceptiont derives;

    /// constructor / destructor
    join_exceptiont(const join_exceptiont& copy): extends(copy) {
    }
    join_exceptiont(join_status status): extends(status) {
    }

    /// ...status...
    virtual const char* status_to_chars() const {
        return join_status_to_chars(this->status());
    }
}; /// class join_exceptiont
typedef join_exceptiont<> join_exception;

/// class joinedt 
template <class TImplements = implement>
class exported joinedt: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef joinedt derives;

    typedef xos::join_status join_status;
    enum {
        join_success = xos::join_success,
        join_failed = xos::join_failed,
        join_busy = xos::join_busy,
        join_timeout = xos::join_timeout,
        join_interrupted = xos::join_interrupted
    };
    
    /// join...
    virtual bool joined() {
        if ((is_forked())) {
            return join();
        }
        return true;
    }
    virtual bool join() {
        return (join_success == untimed_join());
    }
    virtual join_status time_join(mseconds_t milliseconds) {
        return join_success;
    }
    virtual join_status timed_join(mseconds_t milliseconds) {
        return join_success;
    }
    virtual join_status untimed_join() {
        return join_success;
    }
    virtual join_status try_join() {
        return join_success;
    }
    
    /// ...is_forked
    virtual bool set_is_forked(bool to = true) {
        return is_forked();
    }
    virtual bool is_forked() const {
        return false;
    }
}; /// class joinedt
typedef joinedt<> joined;

namespace extended {
/// class joint
template <class TExtends = extend, class TImplements = implement>
class exported joint: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef joint derives;

    /// constructor / destructor
    joint(joined& _joined): is_joined_(false), joined_(_joined) {
    }
    virtual ~joint() {
    }
private:
    joint(const joint& copy): is_joined_(false), joined_(this_joined_) {
        throw exception(exception_unexpected);
    }

    virtual bool set_joined(bool to = true) {
        is_joined_ = to;
        return is_joined_;
    }
    virtual bool set_unjoined(bool to = true) {
        is_joined_ = !to;
        return !is_joined_;
    }

protected:
    bool is_joined_;
    joined this_joined_, &joined_;
}; /// class joint
typedef joint<> join;
} /// namespace extended

/// class joint
template <class TExtends = extended::join, class TImplements = typename TExtends::implements>
class exported joint: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef joint derives;

    /// constructor / destructor
    joint(joined& _joined, mseconds_t mseconds): extends(_joined) {
        join_status status = join_failed;
        if (!(this->is_joined_ = (join_success == (status = this->joined_.timed_join(mseconds))))) {
            throw join_exception(status);
        }
    }
    joint(joined& _joined): extends(_joined) {
        if (!(this->is_joined_ = (this->joined_.join()))) {
            throw join_exception(join_failed);
        }
    }
    virtual ~joint() {
    }
private:
    joint(const joint& copy): extends(copy) {
        throw exception(exception_unexpected);
    }
}; /// class joint
typedef joint<> join;

/// class try_joint
template <class TExtends = extended::join, class TImplements = typename TExtends::implements>
class exported try_joint: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef try_joint derives;

    /// constructor / destructor
    try_joint(joined& _joined): extends(_joined) {
        join_status status = join_failed;
        if (!(this->is_joined_ = (join_success == (status = this->joined_.try_join())))) {
            throw join_exception(status);
        }
    }
    virtual ~try_joint() {
    }
private:
    try_joint(const try_joint& copy): extends(copy) {
        throw exception(exception_unexpected);
    }
}; /// class try_joint
typedef try_joint<> try_join;

} /// namespace xos

#endif /// ndef XOS_BASE_JOINED_HPP
