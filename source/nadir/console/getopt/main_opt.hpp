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
///   File: main_opt.hpp
///
/// Author: $author$
///   Date: 1/13/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_CONSOLE_GETOPT_MAIN_OPT_HPP
#define _NADIR_CONSOLE_GETOPT_MAIN_OPT_HPP

#include "nadir/console/getopt/main_base.hpp"
#include "nadir/io/logger.hpp"

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPT "logging-level"
#define NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_REQUIRED NADIR_CONSOLE_GETOPT_MAIN_OPT_ARGUMENT_REQUIRED
#define NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG "{(a)all | (n)none | (f)fatal | (e)error | (w)waring | (i)info | (d)debug | (t)trace}"
#define NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_ALL 'a'
#define NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_NONE 'n'
#define NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_FATAL 'f'
#define NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_ERROR 'e'
#define NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_WARN 'w'
#define NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_INFO 'i'
#define NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_DEBUG 'd'
#define NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_TRACE 't'
#define NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_MESSAGE_FATAL 'F'
#define NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_MESSAGE_ERROR 'E'
#define NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_MESSAGE_WARN 'W'
#define NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_MESSAGE_INFO 'I'
#define NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_MESSAGE_DEBUG 'D'
#define NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_MESSAGE_TRACE 'T'
#define NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTUSE ""
#define NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTVAL_S "l:"
#define NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTVAL_C 'l'

#define NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTIONS_OPTION \
   {NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPT, \
    NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_REQUIRED, 0, \
    NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTVAL_C},

#define NADIR_CONSOLE_GETOPT_MAIN_HELP_OPT "help"
#define NADIR_CONSOLE_GETOPT_MAIN_HELP_OPTARG_REQUIRED NADIR_CONSOLE_GETOPT_MAIN_OPT_ARGUMENT_NONE
#define NADIR_CONSOLE_GETOPT_MAIN_HELP_OPTARG ""
#define NADIR_CONSOLE_GETOPT_MAIN_HELP_OPTUSE "Usage options"
#define NADIR_CONSOLE_GETOPT_MAIN_HELP_OPTVAL_S "h"
#define NADIR_CONSOLE_GETOPT_MAIN_HELP_OPTVAL_C 'h'

#define NADIR_CONSOLE_GETOPT_MAIN_HELP_OPTIONS_OPTION \
   {NADIR_CONSOLE_GETOPT_MAIN_HELP_OPT, \
    NADIR_CONSOLE_GETOPT_MAIN_HELP_OPTARG_REQUIRED, 0, \
    NADIR_CONSOLE_GETOPT_MAIN_HELP_OPTVAL_C},

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define NADIR_CONSOLE_GETOPT_MAIN_OPTIONS_CHARS \
    NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTVAL_S \
    NADIR_CONSOLE_GETOPT_MAIN_HELP_OPTVAL_S

#define NADIR_CONSOLE_GETOPT_MAIN_OPTIONS_OPTIONS \
    NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTIONS_OPTION \
    NADIR_CONSOLE_GETOPT_MAIN_HELP_OPTIONS_OPTION

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

namespace nadir {
namespace console {
namespace getopt {

typedef main_base::Implements main_optt_implements;
typedef main_base main_optt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main_optt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = main_optt_implements, class TExtends = main_optt_extends>

class _EXPORT_CLASS main_optt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef typename Extends::char_t char_t;
    typedef typename Extends::end_char_t end_char_t;
    enum { end_char = Extends::end_char };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main_optt() {
    }
    virtual ~main_optt() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_logging_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        char c = 0;
        if ((optarg) && (c = optarg[0]) && (!optarg[1])) {
            switch(c) {

            case '7':
            case NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_ALL:
                SET_LOGGING_LEVEL(LOGGING_LEVELS_ALL | LOGGING_MESSAGE_LEVELS_ALL);
                break;
            case '0':
            case NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_NONE:
                SET_LOGGING_LEVEL(LOGGING_LEVELS_NONE | LOGGING_MESSAGE_LEVELS_NONE);
                break;
            case '1':
            case NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_FATAL:
                SET_LOGGING_LEVEL(LOGGING_LEVELS_FATAL | LOGGING_MESSAGE_LEVELS_FATAL);
                break;
            case '2':
            case NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_ERROR:
                SET_LOGGING_LEVEL(LOGGING_LEVELS_ERROR | LOGGING_MESSAGE_LEVELS_ERROR);
                break;
            case '3':
            case NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_WARN:
                SET_LOGGING_LEVEL(LOGGING_LEVELS_WARN | LOGGING_MESSAGE_LEVELS_WARN);
                break;
            case '4':
            case NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_INFO:
                SET_LOGGING_LEVEL(LOGGING_LEVELS_INFO | LOGGING_MESSAGE_LEVELS_INFO);
                break;
            case '5':
            case NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_DEBUG:
                SET_LOGGING_LEVEL(LOGGING_LEVELS_DEBUG | LOGGING_MESSAGE_LEVELS_DEBUG);
                break;
            case '6':
            case NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_TRACE:
                SET_LOGGING_LEVEL(LOGGING_LEVELS_TRACE | LOGGING_MESSAGE_LEVELS_TRACE);
                break;

            case NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_MESSAGE_FATAL:
                SET_LOGGING_LEVEL(LOGGING_LEVELS_FATAL | LOGGING_MESSAGE_LEVELS_FATAL);
                break;
            case NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_MESSAGE_ERROR:
                SET_LOGGING_LEVEL(LOGGING_LEVELS_ERROR | LOGGING_MESSAGE_LEVELS_ERROR);
                break;
            case NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_MESSAGE_WARN:
                SET_LOGGING_LEVEL(LOGGING_MESSAGE_LEVELS_WARN);
                break;
            case NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_MESSAGE_INFO:
                SET_LOGGING_LEVEL(LOGGING_MESSAGE_LEVELS_INFO);
                break;
            case NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_MESSAGE_DEBUG:
                SET_LOGGING_LEVEL(LOGGING_MESSAGE_LEVELS_DEBUG);
                break;
            case NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG_C_MESSAGE_TRACE:
                SET_LOGGING_LEVEL(LOGGING_MESSAGE_LEVELS_TRACE);
                break;

            default:
                err = this->on_invalid_option_arg
                (optval, optarg, optname, optind, argc, argv, env);
                break;
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        switch(optval) {
        case NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTVAL_C:
            err = on_logging_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case NADIR_CONSOLE_GETOPT_MAIN_HELP_OPTVAL_C:
            err = this->on_usage_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        default:
            err = this->on_invalid_option
            (optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* option_usage
    (const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = "";
        switch(longopt->val) {
        case NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTVAL_C:
            optarg = NADIR_CONSOLE_GETOPT_MAIN_LOGGING_OPTARG;
            break;
        case NADIR_CONSOLE_GETOPT_MAIN_HELP_OPTVAL_C:
            chars = NADIR_CONSOLE_GETOPT_MAIN_HELP_OPTUSE;
            break;
        default:
            break;
        }
        return chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* options(const struct option*& longopts) {
        static const char_t* chars = NADIR_CONSOLE_GETOPT_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            NADIR_CONSOLE_GETOPT_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef main_optt<> main_opt;

} // namespace getopt
} // namespace console
} // namespace nadir

#endif // _NADIR_CONSOLE_GETOPT_MAIN_OPT_HPP 
