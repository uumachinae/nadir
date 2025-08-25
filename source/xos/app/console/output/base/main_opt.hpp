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
///   Date: 11/13/2024, 11/26/2024
//////////////////////////////////////////////////////////////////////////
#ifndef XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_OPT_HPP
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_OPT_HPP

#include "xos/app/console/framework/version/main.hpp"

#define XOS_APP_CONSOLE_MAIN_OPTARG_ON "on"
#define XOS_APP_CONSOLE_MAIN_OPTARG_OFF "off"

#define XOS_APP_CONSOLE_MAIN_OPTARG_ONOFF \
    "{ " XOS_APP_CONSOLE_MAIN_OPTARG_ON \
    " | " XOS_APP_CONSOLE_MAIN_OPTARG_OFF " }"

#define XOS_APP_CONSOLE_MAIN_OPTARG_ONOFF_OPTIONAL \
    "[" XOS_APP_CONSOLE_MAIN_OPTARG_ONOFF "]"

#define XOS_APP_CONSOLE_MAIN_OPTARG_STRING "string"
#define XOS_APP_CONSOLE_MAIN_OPTARG_STRING_OPTIONAL \
    "[" XOS_APP_CONSOLE_MAIN_OPTARG_STRING "]"

#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_NOLINE_OUTPUT_OPT "noline"
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_NOLINE_OUTPUT_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_NOLINE_OUTPUT_OPTARG_RESULT 0
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_NOLINE_OUTPUT_OPTARG XOS_APP_CONSOLE_MAIN_OPTARG_ONOFF_OPTIONAL
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_NOLINE_OUTPUT_OPTUSE "no line feed on output"
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_NOLINE_OUTPUT_OPTVAL_S "n::"
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_NOLINE_OUTPUT_OPTVAL_C 'n'
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_NOLINE_OUTPUT_OPTION \
   {XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_NOLINE_OUTPUT_OPT, \
    XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_NOLINE_OUTPUT_OPTARG_REQUIRED, \
    XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_NOLINE_OUTPUT_OPTARG_RESULT, \
    XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_NOLINE_OUTPUT_OPTVAL_C}, \

#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_QUIET_OUTPUT_OPT "quiet"
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_QUIET_OUTPUT_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_QUIET_OUTPUT_OPTARG_RESULT 0
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_QUIET_OUTPUT_OPTARG XOS_APP_CONSOLE_MAIN_OPTARG_ONOFF_OPTIONAL
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_QUIET_OUTPUT_OPTUSE "quiet output"
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_QUIET_OUTPUT_OPTVAL_S "q::"
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_QUIET_OUTPUT_OPTVAL_C 'q'
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_QUIET_OUTPUT_OPTION \
   {XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_QUIET_OUTPUT_OPT, \
    XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_QUIET_OUTPUT_OPTARG_REQUIRED, \
    XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_QUIET_OUTPUT_OPTARG_RESULT, \
    XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_QUIET_OUTPUT_OPTVAL_C}, \

#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OUTPUT_OPT "verbose"
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OUTPUT_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OUTPUT_OPTARG_RESULT 0
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OUTPUT_OPTARG XOS_APP_CONSOLE_MAIN_OPTARG_ONOFF_OPTIONAL
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OUTPUT_OPTUSE "verbose output"
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OUTPUT_OPTVAL_S "v::"
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OUTPUT_OPTVAL_C 'v'
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OUTPUT_OPTION \
   {XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OUTPUT_OPT, \
    XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OUTPUT_OPTARG_REQUIRED, \
    XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OUTPUT_OPTARG_RESULT, \
    XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OUTPUT_OPTVAL_C}, \

#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_RAW_OUTPUT_OPT "raw"
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_RAW_OUTPUT_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_RAW_OUTPUT_OPTARG_RESULT 0
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_RAW_OUTPUT_OPTARG XOS_APP_CONSOLE_MAIN_OPTARG_ONOFF_OPTIONAL
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_RAW_OUTPUT_OPTUSE "raw output"
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_RAW_OUTPUT_OPTVAL_S "w::"
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_RAW_OUTPUT_OPTVAL_C 'w'
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_RAW_OUTPUT_OPTION \
   {XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_RAW_OUTPUT_OPT, \
    XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_RAW_OUTPUT_OPTARG_REQUIRED, \
    XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_RAW_OUTPUT_OPTARG_RESULT, \
    XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_RAW_OUTPUT_OPTVAL_C}, \

///////////////////////////////////////////////////////////////////////
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_OPTIONS_CHARS_EXTEND \
   XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_NOLINE_OUTPUT_OPTVAL_S \
   XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_QUIET_OUTPUT_OPTVAL_S \
   XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OUTPUT_OPTVAL_S \
   XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_RAW_OUTPUT_OPTVAL_S \

#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_OPTIONS_OPTIONS_EXTEND \
   XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_NOLINE_OUTPUT_OPTION \
   XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_QUIET_OUTPUT_OPTION \
   XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OUTPUT_OPTION \
   XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_RAW_OUTPUT_OPTION \

///////////////////////////////////////////////////////////////////////
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OPTIONS_CHARS_EXTEND \
   XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_QUIET_OUTPUT_OPTVAL_S \
   XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OUTPUT_OPTVAL_S \

#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OPTIONS_OPTIONS_EXTEND \
   XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_QUIET_OUTPUT_OPTION \
   XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OUTPUT_OPTION \

///////////////////////////////////////////////////////////////////////
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OPTIONS_CHARS \
   XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OPTIONS_CHARS_EXTEND \
   XOS_APP_CONSOLE_FRAMEWORK_VERSION_MAIN_LOGGING_OPTIONS_CHARS \

#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OPTIONS_OPTIONS \
   XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OPTIONS_OPTIONS_EXTEND \
   XOS_APP_CONSOLE_FRAMEWORK_VERSION_MAIN_LOGGING_OPTIONS_OPTIONS \

///////////////////////////////////////////////////////////////////////
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_LOGGING_OPTIONS_CHARS \
   XOS_APP_CONSOLE_FRAMEWORK_VERSION_MAIN_LOGGING_OPTIONS_CHARS \

#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_LOGGING_OPTIONS_OPTIONS \
   XOS_APP_CONSOLE_FRAMEWORK_VERSION_MAIN_LOGGING_OPTIONS_OPTIONS \

///////////////////////////////////////////////////////////////////////
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_OPTIONS_CHARS \
   XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_OPTIONS_CHARS_EXTEND \
   XOS_APP_CONSOLE_FRAMEWORK_VERSION_MAIN_LOGGING_OPTIONS_CHARS \

#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_OPTIONS_OPTIONS \
   XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_OPTIONS_OPTIONS_EXTEND \
   XOS_APP_CONSOLE_FRAMEWORK_VERSION_MAIN_LOGGING_OPTIONS_OPTIONS \

///////////////////////////////////////////////////////////////////////
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_ARGS 0
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_ARGV 0,

namespace xos {
namespace app {
namespace console {
namespace output {
namespace base {

/// class main_optt
template 
<class TExtends = xos::app::console::framework::version::maint<>,  class TImplements = typename TExtends::implements>

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
            if (!(err = extends::run(argc, argv, env))) {
            } else {
            }
        }
        return err;
    }

    //////////////////////////////////////////////////////////////////////////
    /// ...output_text_run
    int (derives::*output_text_run_)(const char_t* chars, size_t length, int argc, char_t** argv, char_t** env);
    virtual int output_text_run(const char_t* chars, size_t length, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (output_text_run_) {
            LOGGER_IS_LOGGED_INFO("(!(err = (this->*output_text_run_)(chars, length, argc, argv, env)))...");
            if (!(err = (this->*output_text_run_)(chars, length, argc, argv, env))) {
                LOGGER_IS_LOGGED_INFO("...(!(" << err << " = (this->*output_text_run_)(chars, length, argc, argv, env)))");
            } else {
                LOGGER_IS_LOGGED_INFO("...failed on (!(" << err << " = (this->*output_text_run_)(chars, length, argc, argv, env)))");
            }
        } else {
            LOGGER_IS_LOGGED_INFO("(!(err = default_output_text_run(chars, length, argc, argv, env)))...");
            if (!(err = default_output_text_run(chars, length, argc, argv, env))) {
                LOGGER_IS_LOGGED_INFO("...(!(" << err << " = default_output_text_run(chars, length, argc, argv, env)))");
            } else {
                LOGGER_IS_LOGGED_INFO("...failed on(!(" << err << " = default_output_text_run(chars, length, argc, argv, env)))");
            }
        }
        return err;
    }
    virtual int default_output_text_run(const char_t* chars, size_t length, int argc, char_t** argv, char_t** env) {
        int err = 0;
        /*LOGGER_IS_LOGGED_INFO("(!(err = extends::run(argc, argv, env)))...");
        if (!(err = extends::run(argc, argv, env))) {
            LOGGER_IS_LOGGED_INFO("...(!(" << err << " = extends::run(argc, argv, env)))");
        } else {
            LOGGER_IS_LOGGED_INFO("...failed on (!(" << err << " = extends::run(argc, argv, env)))");
        }*/
        return err;
    }
    virtual int before_output_text_run(const char_t* chars, size_t length, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_output_text_run(const char_t* chars, size_t length, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int all_output_text_run(const char_t* chars, size_t length, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = before_output_text_run(chars, length, argc, argv, env))) {
            int err2 = 0;
            err = output_text_run(chars, length, argc, argv, env);
            if ((err2 = after_output_text_run(chars, length, argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    /// on...noline_output_option...
    virtual int on_get_noline_output_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_noline_output_option_get
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_set_noline_output_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        } else {
        }
        return err;
    }
    virtual int on_noline_output_option_set
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        } else {
        }
        return err;
    }
    virtual int on_noline_output_option
    (int optval, const char_t* optarg, const char_t* optname,
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            if (!(err = on_set_noline_output_option(optarg, optind, argc, argv, env))) {
                if (!(err = on_noline_output_option_set(optarg, optind, argc, argv, env))) {
                } else {
                }
            } else {
            }
        } else {
            if (!(err = on_get_noline_output_option(optarg, optind, argc, argv, env))) {
                if (!(err = on_noline_output_option_get(optarg, optind, argc, argv, env))) {
                } else {
                }
            } else {
            }
        }
        return err;
    }
    virtual const char_t* noline_output_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_NOLINE_OUTPUT_OPTUSE;
        optarg = XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_NOLINE_OUTPUT_OPTARG;
        return chars;
    }
    //////////////////////////////////////////////////////////////////////////
    /// on...quiet_output_option...
    virtual int on_get_quiet_output_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_quiet_output_option_get
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_set_quiet_output_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        } else {
        }
        return err;
    }
    virtual int on_quiet_output_option_set
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        } else {
        }
        return err;
    }
    virtual int on_quiet_output_option
    (int optval, const char_t* optarg, const char_t* optname,
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            if (!(err = on_set_quiet_output_option(optarg, optind, argc, argv, env))) {
                if (!(err = on_quiet_output_option_set(optarg, optind, argc, argv, env))) {
                } else {
                }
            } else {
            }
        } else {
            if (!(err = on_get_quiet_output_option(optarg, optind, argc, argv, env))) {
                if (!(err = on_quiet_output_option_get(optarg, optind, argc, argv, env))) {
                } else {
                }
            } else {
            }
        }
        return err;
    }
    virtual const char_t* quiet_output_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_QUIET_OUTPUT_OPTUSE;
        optarg = XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_QUIET_OUTPUT_OPTARG;
        return chars;
    }
    //////////////////////////////////////////////////////////////////////////
    /// on...verbose_output_option...
    virtual int on_get_verbose_output_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_verbose_output_option_get
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_set_verbose_output_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        } else {
        }
        return err;
    }
    virtual int on_verbose_output_option_set
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        } else {
        }
        return err;
    }
    virtual int on_verbose_output_option
    (int optval, const char_t* optarg, const char_t* optname,
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            if (!(err = on_set_verbose_output_option(optarg, optind, argc, argv, env))) {
                if (!(err = on_verbose_output_option_set(optarg, optind, argc, argv, env))) {
                } else {
                }
            } else {
            }
        } else {
            if (!(err = on_get_verbose_output_option(optarg, optind, argc, argv, env))) {
                if (!(err = on_verbose_output_option_get(optarg, optind, argc, argv, env))) {
                } else {
                }
            } else {
            }
        }
        return err;
    }
    virtual const char_t* verbose_output_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OUTPUT_OPTUSE;
        optarg = XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OUTPUT_OPTARG;
        return chars;
    }
    //////////////////////////////////////////////////////////////////////////
    /// on...raw_output_option...
    virtual int on_get_raw_output_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_raw_output_option_get
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_set_raw_output_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        } else {
        }
        return err;
    }
    virtual int on_raw_output_option_set
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        } else {
        }
        return err;
    }
    virtual int on_raw_output_option
    (int optval, const char_t* optarg, const char_t* optname,
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            if (!(err = on_set_raw_output_option(optarg, optind, argc, argv, env))) {
                if (!(err = on_raw_output_option_set(optarg, optind, argc, argv, env))) {
                } else {
                }
            } else {
            }
        } else {
            if (!(err = on_get_raw_output_option(optarg, optind, argc, argv, env))) {
                if (!(err = on_raw_output_option_get(optarg, optind, argc, argv, env))) {
                } else {
                }
            } else {
            }
        }
        return err;
    }
    virtual const char_t* raw_output_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_RAW_OUTPUT_OPTUSE;
        optarg = XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_RAW_OUTPUT_OPTARG;
        return chars;
    }
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    /// on_option
    virtual int on_option
    (int optval, const char_t* optarg, const char_t* optname,
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        switch(optval) {

        case XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_NOLINE_OUTPUT_OPTVAL_C:
            err = this->on_noline_output_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_QUIET_OUTPUT_OPTVAL_C:
            err = this->on_quiet_output_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OUTPUT_OPTVAL_C:
            err = this->on_verbose_output_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_RAW_OUTPUT_OPTVAL_C:
            err = this->on_raw_output_option(optval, optarg, optname, optind, argc, argv, env);
            break;

        default:
            err = extends::on_option(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    
    /// option_usage
    virtual const char_t* option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = "";
        switch(longopt->val) {

        case XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_NOLINE_OUTPUT_OPTVAL_C:
            chars = this->noline_output_option_usage(optarg, longopt);
            break;
        case XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_QUIET_OUTPUT_OPTVAL_C:
            chars = this->quiet_output_option_usage(optarg, longopt);
            break;
        case XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_VERBOSE_OUTPUT_OPTVAL_C:
            chars = this->verbose_output_option_usage(optarg, longopt);
            break;
        case XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_RAW_OUTPUT_OPTVAL_C:
            chars = this->raw_output_option_usage(optarg, longopt);
            break;

        default:
            chars = extends::option_usage(optarg, longopt);
            break;
        }
        return chars;
    }

    /// options
    virtual const char_t* options(const struct option*& longopts) {
        static const char_t* chars = XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

    /// arguments
    virtual const char_t* arguments(const char_t**& argv) {
        static const char_t* _args = XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_ARGS;
        static const char_t* _argv[] = {
            XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_ARGV
            0};
        argv = _argv;
        return _args;
    }
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
protected:
}; /// class main_optt 
typedef main_optt<> main_opt;

} /// namespace base 
} /// namespace output 
} /// namespace console 
} /// namespace app 
} /// namespace xos 

#endif /// ndef XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_OPT_HPP

