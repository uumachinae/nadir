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
///   File: resumed.hpp
///
/// Author: $author$
///   Date: 1/21/2020
///////////////////////////////////////////////////////////////////////
#ifndef XOS_BASE_RESUMED_HPP
#define XOS_BASE_RESUMED_HPP

#include "xos/base/exception.hpp"

namespace xos {

/// enum resume_status
typedef int resume_status;
enum {
    /// resume...
    resume_success = 0,
    resume_failed,
    resume_busy,
    resume_timeout,
    resume_interrupted,
    next_resume,
    first_resume = resume_success,
    last_resume = resume_interrupted,
}; /// enum resume_status

/// function resume_status_to_chars
inline const char* resume_status_to_chars(resume_status status) {
    switch(status) {
    /// resume...
    case resume_success: return "resume_success";
    case resume_failed: return "resume_failed";
    case resume_busy: return "resume_busy";
    case resume_timeout: return "resume_timeout";
    case resume_interrupted: return "resume_interrupted";
    }
    return "unknown";
} /// function resume_status_to_chars

/// class resume_exceptiont
template <class TExtends = exceptiont<resume_status>, class TImplements = typename TExtends::implements>
class exported resume_exceptiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef resume_exceptiont derives;

    /// constructor / destructor
    resume_exceptiont(const resume_exceptiont& copy): extends(copy) {
    }
    resume_exceptiont(resume_status status): extends(status) {
    }

    /// ...status...
    virtual const char* status_to_chars() const {
        return resume_status_to_chars(this->status());
    }
}; /// class resume_exceptiont
typedef resume_exceptiont<> resume_exception;

/// class resumedt 
template <class TImplements = implement>
class exported resumedt: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef resumedt derives;

    typedef xos::resume_status resume_status;
    enum {
        resume_success = xos::resume_success,
        resume_failed = xos::resume_failed,
        resume_busy = xos::resume_busy,
        resume_timeout = xos::resume_timeout,
        resume_interrupted = xos::resume_interrupted
    };
    
    /// resume...
    virtual bool resume() {
        return (resume_success == untimed_resume());
    }
    virtual resume_status timed_resume(mseconds_t milliseconds) {
        return resume_success;
    }
    virtual resume_status untimed_resume() {
        return resume_success;
    }
    virtual resume_status try_resume() {
        return resume_success;
    }
}; /// class resumedt
typedef resumedt<> resumed;

namespace extended {
/// class resumet
template <class TExtends = extend, class TImplements = implement>
class exported resumet: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef resumet derives;

    /// constructor / destructor
    resumet(resumed& _resumed): is_resumed_(false), resumed_(_resumed) {
    }
    virtual ~resumet() {
    }
private:
    resumet(const resumet& copy): is_resumed_(false), resumed_(this_resumed_) {
        throw exception(exception_unexpected);
    }

    virtual bool set_resumed(bool to = true) {
        is_resumed_ = to;
        return is_resumed_;
    }
    virtual bool set_unresumed(bool to = true) {
        is_resumed_ = !to;
        return !is_resumed_;
    }

protected:
    bool is_resumed_;
    resumed this_resumed_, &resumed_;
}; /// class resumet
typedef resumet<> resume;
} /// namespace extended

/// class resumet
template <class TExtends = extended::resume, class TImplements = typename TExtends::implements>
class exported resumet: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef resumet derives;

    /// constructor / destructor
    resumet(resumed& _resumed, mseconds_t mseconds): extends(_resumed) {
        resume_status status = resume_failed;
        if (!(this->is_resumed_ = (resume_success == (status = this->resumed_.timed_resume(mseconds))))) {
            throw resume_exception(status);
        }
    }
    resumet(resumed& _resumed): extends(_resumed) {
        if (!(this->is_resumed_ = (this->resumed_.resume()))) {
            throw resume_exception(resume_failed);
        }
    }
    virtual ~resumet() {
    }
private:
    resumet(const resumet& copy): extends(copy) {
        throw exception(exception_unexpected);
    }
}; /// class resumet
typedef resumet<> resume;

/// class try_resumet
template <class TExtends = extended::resume, class TImplements = typename TExtends::implements>
class exported try_resumet: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef try_resumet derives;

    /// constructor / destructor
    try_resumet(resumed& _resumed): extends(_resumed) {
        resume_status status = resume_failed;
        if (!(this->is_resumed_ = (resume_success == (status = this->resumed_.try_resume())))) {
            throw resume_exception(status);
        }
    }
    virtual ~try_resumet() {
    }
private:
    try_resumet(const try_resumet& copy): extends(copy) {
        throw exception(exception_unexpected);
    }
}; /// class try_resumet
typedef try_resumet<> try_resume;

} /// namespace xos

#endif /// ndef XOS_BASE_RESUMED_HPP
