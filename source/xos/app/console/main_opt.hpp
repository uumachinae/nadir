//////////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2024 $organization$
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
///   File: main_opt.hpp
///
/// Author: $author$
///   Date: 11/3/2024
//////////////////////////////////////////////////////////////////////////
#ifndef XOS_APP_CONSOLE_MAIN_OPT_HPP
#define XOS_APP_CONSOLE_MAIN_OPT_HPP

#include "xos/console/getopt/main.hpp"

#define XOS_APP_CONSOLE_MAIN_OPTIONS_CHARS_EXTEND \

#define XOS_APP_CONSOLE_MAIN_OPTIONS_OPTIONS_EXTEND \

///////////////////////////////////////////////////////////////////////
#define XOS_APP_CONSOLE_MAIN_HELP_OPTIONS_CHARS \
   XOS_APP_CONSOLE_MAIN_OPTIONS_CHARS_EXTEND \
   XOS_CONSOLE_MAIN_HELP_OPTIONS_CHARS

#define XOS_APP_CONSOLE_MAIN_HELP_OPTIONS_OPTIONS \
   XOS_APP_CONSOLE_MAIN_OPTIONS_OPTIONS_EXTEND \
   XOS_CONSOLE_MAIN_HELP_OPTIONS_OPTIONS

///////////////////////////////////////////////////////////////////////
#define XOS_APP_CONSOLE_MAIN_USAGE_OPTIONS_CHARS \
   XOS_APP_CONSOLE_MAIN_OPTIONS_CHARS_EXTEND \
   XOS_CONSOLE_MAIN_USAGE_OPTIONS_CHARS

#define XOS_APP_CONSOLE_MAIN_USAGE_OPTIONS_OPTIONS \
   XOS_APP_CONSOLE_MAIN_OPTIONS_OPTIONS_EXTEND \
   XOS_CONSOLE_MAIN_USAGE_OPTIONS_OPTIONS

///////////////////////////////////////////////////////////////////////
#define XOS_APP_CONSOLE_MAIN_LOGGING_OPTIONS_CHARS \
   XOS_APP_CONSOLE_MAIN_OPTIONS_CHARS_EXTEND \
   XOS_CONSOLE_MAIN_LOGGING_OPTIONS_CHARS

#define XOS_APP_CONSOLE_MAIN_LOGGING_OPTIONS_OPTIONS \
   XOS_APP_CONSOLE_MAIN_OPTIONS_OPTIONS_EXTEND \
   XOS_CONSOLE_MAIN_LOGGING_OPTIONS_OPTIONS

///////////////////////////////////////////////////////////////////////
#define XOS_APP_CONSOLE_MAIN_OPTIONS_CHARS \
   XOS_APP_CONSOLE_MAIN_OPTIONS_CHARS_EXTEND \
   XOS_CONSOLE_MAIN_OPTIONS_CHARS

#define XOS_APP_CONSOLE_MAIN_OPTIONS_OPTIONS \
   XOS_APP_CONSOLE_MAIN_OPTIONS_OPTIONS_EXTEND \
   XOS_CONSOLE_MAIN_OPTIONS_OPTIONS

///////////////////////////////////////////////////////////////////////
#define XOS_APP_CONSOLE_MAIN_ARGS 0
#define XOS_APP_CONSOLE_MAIN_ARGV 0,

namespace xos {
namespace app {
namespace console {

/// class main_optt
template 
<class TExtends = xos::console::getopt::maint<>,  class TImplements = typename TExtends::implements>

class main_optt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef main_optt derives;

    typedef typename extends::char_t char_t;
    typedef typename extends::end_char_t end_char_t;
    enum { end_char = extends::end_char };
    typedef typename extends::string_t string_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;
    typedef typename extends::file_t file_t;

    typedef typename extends::sequence_char_t sequence_char_t;
    typedef typename extends::char_sequence_t char_sequence_t;
    typedef typename extends::char_seeker_t char_seeker_t;
    typedef typename extends::char_reader_t char_reader_t;
    typedef typename extends::char_writer_t char_writer_t;
    typedef typename extends::reader_string_t reader_string_t;
    typedef typename extends::string_reader_t string_reader_t;

    /// constructor / destructor
    main_optt(): run_(0) {
    }
    virtual ~main_optt() {
    }
private:
    main_optt(const main_optt &copy) {
        throw exception(exception_unexpected);
    }

protected:
    typedef typename extends::in_reader_t in_reader_t;
    typedef typename extends::out_writer_t out_writer_t;
    typedef typename extends::err_writer_t err_writer_t;

    //////////////////////////////////////////////////////////////////////////
    /// run
    int (derives::*run_)(int argc, char_t** argv, char_t** env);
    virtual int run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        if ((run_)) {
            if (!(err = (this->*run_)(argc, argv, env))) {
            } else {
            }
        } else {
            if (!(err = all_default_run(argc, argv, env))) {
            } else {
            }
        }
        return err;
    }

    //////////////////////////////////////////////////////////////////////////
    /// ...default_run
    virtual int default_run(int argc, char_t** argv, char** env) {
        int err = 0;
        if (!(err = this->all_usage(argc, argv, env))) {
        } else {
        }
        return err;
    }
    virtual int before_default_run(int argc, char_t** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int after_default_run(int argc, char_t** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int all_default_run(int argc, char_t** argv, char** env) {
        int err = 0;
        if (!(err = before_default_run(argc, argv, env))) {
            int err2 = 0;
            err = default_run(argc, argv, env);
            if ((err2 = after_default_run(argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }
    virtual int set_default_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        run_ = &derives::all_default_run;
        return err;
    }
    virtual int default_run_set(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int unset_default_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        run_ = 0;
        return err;
    }
    virtual int default_run_unset(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    /// on_option
    virtual int on_option
    (int optval, const char_t* optarg, const char_t* optname,
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        switch(optval) {
        default:
            err = extends::on_option(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    
    /// option_usage
    virtual const char_t* option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = "";
        switch(longopt->val) {
        default:
            chars = extends::option_usage(optarg, longopt);
            break;
        }
        return chars;
    }

    /// options
    virtual const char_t* options(const struct option*& longopts) {
        static const char_t* chars = XOS_APP_CONSOLE_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            XOS_APP_CONSOLE_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

    /// arguments
    virtual const char_t* arguments(const char_t**& argv) {
        static const char_t* _args = XOS_APP_CONSOLE_MAIN_ARGS;
        static const char_t* _argv[] = {
            XOS_APP_CONSOLE_MAIN_ARGV
            0};
        argv = _argv;
        return _args;
    }
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
protected:
}; /// class main_optt 
typedef main_optt<> main_opt;

} /// namespace console 
} /// namespace app 
} /// namespace xos 

#endif /// ndef XOS_APP_CONSOLE_MAIN_OPT_HPP

