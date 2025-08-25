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
///   File: main.hpp
///
/// Author: $author$
///   Date: 5/14/2018
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_APP_CONSOLE_NADIR_MAIN_HPP
#define _NADIR_APP_CONSOLE_NADIR_MAIN_HPP

#include "nadir/app/console/nadir/main_opt.hpp"
#include "nadir/app/console/nadir/thread.hpp"
#include "nadir/lib/nadir/version.hpp"

namespace nadir {
namespace app {
namespace console {
namespace nadir {

typedef thread_ran maint_ran_implements;
typedef main_opt::Implements maint_implements;
typedef main_opt maint_extends;
///////////////////////////////////////////////////////////////////////
///  Class: maint
///////////////////////////////////////////////////////////////////////
template 
<class TRanImplements = maint_ran_implements, 
 class TImplements = maint_implements, class TExtends = maint_extends>
class _EXPORT_CLASS maint
: virtual public TRanImplements, virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef maint Derives;

    typedef thread thread_t;
    typedef thread_ran thread_ran_t;
    typedef thread_array thread_array_t;

    typedef typename Implements::char_t char_t;
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    maint(): run_(0), thread_run_(0), threads_(0) {
    }
    virtual ~maint() {
    }
private:
    maint(const maint &copy) {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        if ((this->run_)) {
            err = (this->*run_)(argc, argv, env);
        } else {
            err = default_run(argc, argv, env);
        }
        return err;
    }
    virtual int default_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        const lib::version& version = lib::nadir::version::which();
        this->outl(version.name(), " version = ", version.to_string().chars(), NULL);
        this->outln();
        this->usage(argc, argv, env);
        return err;
    }
    virtual int thread_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        size_t n = 0;
        if (0 < (n = threads())) {
            LOG_DEBUG("try {...");
            try {
                thread_array_t t(n, *this);
                LOG_DEBUG("...} try");
            } catch(...) {
                LOG_ERROR("...catch(...)");
                err = 1;
            }
        } else {
            thread_run();
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void thread_run() {
        if ((thread_run_)) {
            (this->*thread_run_)();
        } else {
            default_thread_run();
        }
    }
    virtual void default_thread_run() {
        LOG_DEBUG("in...");
        try {
            locker lock(*this);
            size_t i = 0, n = threads();
            do {
                this->outf("Hello");
                if (i < n) {
                    this->outf(" %u", i);
                }
                this->outln();
            } while ((++i) < n);
            if (1 < (n)) {
                this->outln();
            }
        } catch(...) {
            LOG_ERROR("...catch(...)");
        }
        LOG_DEBUG("...out");
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_threads_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            unsigned threads = 0;
            if (0 <= (threads = char_string(optarg).to_unsigned())) {
                set_threads(threads);
                run_ = &Derives::thread_run;
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set_threads(size_t to) {
        threads_ = to;
        return threads_;
    }
    virtual size_t threads() const {
        return threads_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    int (Derives::*run_)(int argc, char_t** argv, char_t** env);
    void (Derives::*thread_run_)();
    size_t threads_;
};
typedef maint<> main;

} // namespace nadir
} // namespace console
} // namespace app
} // namespace nadir

#endif // _NADIR_APP_CONSOLE_NADIR_MAIN_HPP 
