///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2020 $organization$
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
///   File: ran.hpp
///
/// Author: $author$
///   Date: 1/21/2020
///////////////////////////////////////////////////////////////////////
#ifndef XOS_BASE_RAN_HPP
#define XOS_BASE_RAN_HPP

#include "xos/base/exception.hpp"

namespace xos {

/// enum run_status
typedef int run_status;
enum {
    /// run...
    run_success = 0,
    run_failed,
    run_busy,
    run_timeout,
    run_interrupted,
    next_run,
    first_run = run_success,
    last_run = run_interrupted,
}; /// enum run_status

/// function run_status_to_chars
inline const char* run_status_to_chars(run_status status) {
    switch(status) {
    /// run...
    case run_success: return "run_success";
    case run_failed: return "run_failed";
    case run_busy: return "run_busy";
    case run_timeout: return "run_timeout";
    case run_interrupted: return "run_interrupted";
    }
    return "unknown";
} /// function run_status_to_chars

/// class run_exceptiont
template <class TExtends = exceptiont<run_status>, class TImplements = typename TExtends::implements>
class exported run_exceptiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef run_exceptiont derives;

    /// constructor / destructor
    run_exceptiont(const run_exceptiont& copy): extends(copy) {
    }
    run_exceptiont(run_status status): extends(status) {
    }

    /// ...status...
    virtual const char* status_to_chars() const {
        return run_status_to_chars(this->status());
    }
}; /// class run_exceptiont
typedef run_exceptiont<> run_exception;

/// class rant
template <class TImplements = implement>
class exported rant: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef rant derives;

    /// run
    virtual pointer_t run(pointer_t parameter_ = 0) {
        return 0;
    }
}; /// class rant
typedef rant<> ran;

namespace extended {
/// class runt
template <class TExtends = extend, class TImplements = implement>
class exported runt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef runt derives;

    /// constructor / destructor
    runt(ran& _ran): result_(0), ran_(_ran) {
    }
    virtual ~runt() {
    }
private:
    runt(const runt& copy): result_(0), ran_(this_ran_) {
        throw exception(exception_unexpected);
    }

    virtual pointer_t result() const {
        return result_;
    }

protected:
    pointer_t result_;
    ran this_ran_, &ran_;
}; /// class runt
typedef runt<> run;
} /// namespace extended

/// class runt
template <class TExtends = extended::run, class TImplements = typename TExtends::implements>
class exported runt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef runt derives;

    /// constructor / destructor
    runt(ran& _ran, pointer_t parameter): extends(_ran) {
        this->result_ = this->ran_.run(parameter);
    }
    runt(ran& _ran): extends(_ran) {
        this->result_ = this->ran_.run();
    }
    virtual ~runt() {
    }
private:
    runt(const runt& copy): extends(copy) {
        throw exception(exception_unexpected);
    }
}; /// class runt
typedef runt<> run;

} /// namespace xos

#endif /// ndef XOS_BASE_RAN_HPP 
