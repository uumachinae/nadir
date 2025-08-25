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
///   File: forked.hpp
///
/// Author: $author$
///   Date: 1/20/2020
///////////////////////////////////////////////////////////////////////
#ifndef XOS_BASE_FORKED_HPP
#define XOS_BASE_FORKED_HPP

#include "xos/base/exception.hpp"

namespace xos {

/// enum fork_status
typedef int fork_status;
enum {
    /// fork...
    fork_success = 0,
    fork_failed,
    fork_busy,
    fork_timeout,
    fork_interrupted,
    next_fork,
    first_fork = fork_success,
    last_fork = fork_interrupted,
}; /// enum fork_status

/// function fork_status_to_chars
inline const char* fork_status_to_chars(fork_status status) {
    switch(status) {
    /// fork...
    case fork_success: return "fork_success";
    case fork_failed: return "fork_failed";
    case fork_busy: return "fork_busy";
    case fork_timeout: return "fork_timeout";
    case fork_interrupted: return "fork_interrupted";
    }
    return "unknown";
} /// function fork_status_to_chars

/// class fork_exceptiont
template <class TExtends = exceptiont<fork_status>, class TImplements = typename TExtends::implements>
class exported fork_exceptiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef fork_exceptiont derives;

    /// constructor / destructor
    fork_exceptiont(const fork_exceptiont& copy): extends(copy) {
    }
    fork_exceptiont(fork_status status): extends(status) {
    }

    /// ...status...
    virtual const char* status_to_chars() const {
        return fork_status_to_chars(this->status());
    }
}; /// class fork_exceptiont
typedef fork_exceptiont<> fork_exception;

/// class forkedt 
template <class TImplements = implement>
class exported forkedt: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef forkedt derives;

    typedef xos::fork_status fork_status;
    enum {
        fork_success = xos::fork_success,
        fork_failed = xos::fork_failed,
        fork_busy = xos::fork_busy,
        fork_timeout = xos::fork_timeout,
        fork_interrupted = xos::fork_interrupted
    };
    
    /// fork...
    virtual bool fork() {
        return (fork_success == untimed_fork());
    }
    virtual fork_status timed_fork(mseconds_t milliseconds) {
        return fork_success;
    }
    virtual fork_status untimed_fork() {
        return fork_success;
    }
    virtual fork_status try_fork() {
        return fork_success;
    }
}; /// class forkedt
typedef forkedt<> forked;

namespace extended {
/// class forkt
template <class TExtends = extend, class TImplements = implement>
class exported forkt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef forkt derives;

    /// constructor / destructor
    forkt(forked& _forked): is_forked_(false), forked_(_forked) {
    }
    virtual ~forkt() {
    }
private:
    forkt(const forkt& copy): is_forked_(false), forked_(this_forked_) {
        throw exception(exception_unexpected);
    }

    virtual bool set_forked(bool to = true) {
        is_forked_ = to;
        return is_forked_;
    }
    virtual bool set_unforked(bool to = true) {
        is_forked_ = !to;
        return !is_forked_;
    }

protected:
    bool is_forked_;
    forked this_forked_, &forked_;
}; /// class forkt
typedef forkt<> fork;
} /// namespace extended

/// class forkt
template <class TExtends = extended::fork, class TImplements = typename TExtends::implements>
class exported forkt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef forkt derives;

    /// constructor / destructor
    forkt(forked& _forked, mseconds_t mseconds): extends(_forked) {
        fork_status status = fork_failed;
        if (!(this->is_forked_ = (fork_success == (status = this->forked_.timed_fork(mseconds))))) {
            throw fork_exception(status);
        }
    }
    forkt(forked& _forked): extends(_forked) {
        if (!(this->is_forked_ = (this->forked_.fork()))) {
            throw fork_exception(fork_failed);
        }
    }
    virtual ~forkt() {
    }
private:
    forkt(const forkt& copy): extends(copy) {
        throw exception(exception_unexpected);
    }
}; /// class forkt
typedef forkt<> fork;

/// class try_forkt
template <class TExtends = extended::fork, class TImplements = typename TExtends::implements>
class exported try_forkt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef try_forkt derives;

    /// constructor / destructor
    try_forkt(forked& _forked): extends(_forked) {
        fork_status status = fork_failed;
        if (!(this->is_forked_ = (fork_success == (status = this->forked_.try_fork())))) {
            throw fork_exception(status);
        }
    }
    virtual ~try_forkt() {
    }
private:
    try_forkt(const try_forkt& copy): extends(copy) {
        throw exception(exception_unexpected);
    }
}; /// class try_forkt
typedef try_forkt<> try_fork;

} /// namespace xos

#endif /// ndef XOS_BASE_FORKED_HPP
