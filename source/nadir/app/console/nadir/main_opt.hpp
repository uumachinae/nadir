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
///   File: main_opt.hpp
///
/// Author: $author$
///   Date: 1/16/2018
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_APP_CONSOLE_NADIR_MAIN_OPT_HPP
#define _NADIR_APP_CONSOLE_NADIR_MAIN_OPT_HPP

#include "nadir/console/getopt/main.hpp"

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define NADIR_APP_CONSOLE_NADIR_MAIN_THREADS_OPT "threads"
#define NADIR_APP_CONSOLE_NADIR_MAIN_THREADS_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define NADIR_APP_CONSOLE_NADIR_MAIN_THREADS_OPTARG_RESULT 0
#define NADIR_APP_CONSOLE_NADIR_MAIN_THREADS_OPTARG ""
#define NADIR_APP_CONSOLE_NADIR_MAIN_THREADS_OPTUSE ""
#define NADIR_APP_CONSOLE_NADIR_MAIN_THREADS_OPTVAL_S "t:"
#define NADIR_APP_CONSOLE_NADIR_MAIN_THREADS_OPTVAL_C 't'
#define NADIR_APP_CONSOLE_NADIR_MAIN_THREADS_OPTION \
   {NADIR_APP_CONSOLE_NADIR_MAIN_THREADS_OPT, \
    NADIR_APP_CONSOLE_NADIR_MAIN_THREADS_OPTARG_REQUIRED, \
    NADIR_APP_CONSOLE_NADIR_MAIN_THREADS_OPTARG_RESULT, \
    NADIR_APP_CONSOLE_NADIR_MAIN_THREADS_OPTVAL_C}, \

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define NADIR_APP_CONSOLE_NADIR_MAIN_OPTIONS_CHARS \
   NADIR_APP_CONSOLE_NADIR_MAIN_THREADS_OPTVAL_S \
   NADIR_CONSOLE_GETOPT_MAIN_OPTIONS_CHARS

#define NADIR_APP_CONSOLE_NADIR_MAIN_OPTIONS_OPTIONS \
   NADIR_APP_CONSOLE_NADIR_MAIN_THREADS_OPTION \
   NADIR_CONSOLE_GETOPT_MAIN_OPTIONS_OPTIONS

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define NADIR_APP_CONSOLE_NADIR_MAIN_ARGS 0
#define NADIR_APP_CONSOLE_NADIR_MAIN_ARGV

namespace nadir {
namespace app {
namespace console {
namespace nadir {

typedef ::nadir::console::getopt::main::Implements main_optt_implements;
typedef ::nadir::console::getopt::main main_optt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main_optt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = main_optt_implements, class TExtends = main_optt_extends>

class _EXPORT_CLASS main_optt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main_optt() {
    }
    virtual ~main_optt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_threads_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
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
        case NADIR_APP_CONSOLE_NADIR_MAIN_THREADS_OPTVAL_C:
            err = on_threads_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        default:
            err = Extends::on_option
            (optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* option_usage
    (const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = "";
        switch(longopt->val) {
        case NADIR_APP_CONSOLE_NADIR_MAIN_THREADS_OPTVAL_C:
            optarg = NADIR_APP_CONSOLE_NADIR_MAIN_THREADS_OPTARG;
            chars = NADIR_APP_CONSOLE_NADIR_MAIN_THREADS_OPTUSE;
            break;
        default:
            chars = Extends::option_usage(optarg, longopt);
        }
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* options(const struct option*& longopts) {
        int err = 0;
        static const char_t* chars = NADIR_APP_CONSOLE_NADIR_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            NADIR_APP_CONSOLE_NADIR_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef main_optt<> main_opt;

} // namespace nadir 
} // namespace console 
} // namespace app 
} // namespace nadir 

#endif // _NADIR_APP_CONSOLE_NADIR_MAIN_OPT_HPP 
