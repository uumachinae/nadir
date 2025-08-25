///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2022 $organization$
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
///   Date: 5/7/2022, 11/3/2024
///////////////////////////////////////////////////////////////////////
#ifndef XOS_CONSOLE_GETOPT_MAIN_HPP
#define XOS_CONSOLE_GETOPT_MAIN_HPP

#include "xos/console/getopt/main_opt.hpp"

namespace xos {
namespace console {
namespace getopt {

/// class maint
template 
<class TExtends = xos::console::getopt::main_opt, class TImplements = typename TExtends::implements>

class exported maint: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements, implements;
    typedef TExtends Extends, extends;
    typedef maint Derives, derives;

    typedef typename extends::char_t char_t;
    typedef typename extends::end_char_t end_char_t;
    enum { end_char = extends::end_char };
    typedef typename extends::string_t string_t;
    typedef typename extends::sequence_char_t sequence_char_t;
    typedef typename extends::sequence_t sequence_t;
    typedef typename extends::seeker_t seeker_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;
    typedef typename extends::char_reader_t char_reader_t;
    typedef typename extends::string_reader_t string_reader_t;
    typedef typename extends::file_t file_t;

    /// constructor / destructor
    maint(): run_(0) {
    }
    virtual ~maint() {
    }
private:
    maint(const maint& copy) {
        throw exception(exception_unexpected);
    }

protected:
    typedef typename extends::in_reader_t in_reader_t;
    typedef typename extends::out_writer_t out_writer_t;
    typedef typename extends::err_writer_t err_writer_t;

    /// ...run
    int (derives::*run_)(int argc, char_t** argv, char_t** env);
    virtual int run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        if ((run_)) {
            err = (this->*run_)(argc, argv, env);
        } else {
            err = extends::run(argc, argv, env);
        }
        return err;
    }

    /// ...option...
    virtual int on_logging_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        char c = 0;
        if ((optarg) && (c = (char)(optarg[0])) && (!optarg[1])) {
            switch(c) {

            case '7':
            case XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_ALL:
                SET_LOGGING_LEVEL(LOGGING_LEVELS_ALL);
                break;
            case '0':
            case XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_NONE:
                SET_LOGGING_LEVEL(LOGGING_LEVELS_NONE);
                break;

            case '1':
            case XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_FATAL:
                SET_LOGGING_LEVEL(LOGGING_LEVELS_FATAL);
                break;
            case '2':
            case XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_ERROR:
                SET_LOGGING_LEVEL(LOGGING_LEVELS_ERROR);
                break;
            case '3':
            case XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_WARN:
                SET_LOGGING_LEVEL(LOGGING_LEVELS_WARN);
                break;
            case '4':
            case XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_INFO:
                SET_LOGGING_LEVEL(LOGGING_LEVELS_INFO);
                break;
            case '5':
            case XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_DEBUG:
                SET_LOGGING_LEVEL(LOGGING_LEVELS_DEBUG);
                break;
            case '6':
            case XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_TRACE:
                SET_LOGGING_LEVEL(LOGGING_LEVELS_TRACE);
                break;

            default:
                err = this->on_invalid_option_arg
                (optval, optarg, optname, optind, argc, argv, env);
                break;
            }
        }
        return err;
    }
    virtual const char_t* logging_option_usage
    (const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = "";
        optarg = XOS_CONSOLE_MAIN_LOGGING_OPTARG;
        chars = XOS_CONSOLE_MAIN_LOGGING_OPTUSE;
        return chars;
    }
    virtual int on_usage_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        err = this->all_usage(argc, argv, env);
        return err;
    }
    virtual const char_t* usage_option_usage
    (const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = "";
        chars = XOS_CONSOLE_MAIN_HELP_OPTUSE;
        return chars;
    }

    /// ...option...
    virtual int on_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        switch(optval) {

        case XOS_CONSOLE_MAIN_LOGGING_OPTVAL_C:
            err = this->on_logging_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_CONSOLE_MAIN_HELP_OPTVAL_C:
            err = this->on_usage_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_CONSOLE_MAIN_USAGE_OPTVAL_C:
            err = this->on_usage_option(optval, optarg, optname, optind, argc, argv, env);
            break;

        default:
            err = extends::on_option(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char_t* option_usage
    (const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = "";
        switch(longopt->val) {

        case XOS_CONSOLE_MAIN_LOGGING_OPTVAL_C:
            chars = this->logging_option_usage(optarg, longopt);
            break;
        case XOS_CONSOLE_MAIN_HELP_OPTVAL_C:
            chars = this->usage_option_usage(optarg, longopt);
            break;
        case XOS_CONSOLE_MAIN_USAGE_OPTVAL_C:
            chars = this->usage_option_usage(optarg, longopt);
            break;

        default:
            chars = extends::option_usage(optarg, longopt);
            break;
        }
        return chars;
    }
    virtual const char_t* options(const struct option*& longopts) {
        static const char_t* chars = XOS_CONSOLE_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            XOS_CONSOLE_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

    /// ...arguments...
    virtual const char_t* arguments(const char_t**& args) {
        args = 0;
        return 0;
    }

protected:
}; /// class maint
typedef maint<> main;

} /// namespace getopt
} /// namespace console
} /// namespace xos

#endif /// ndef XOS_CONSOLE_GETOPT_MAIN_HPP
