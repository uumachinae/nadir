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
///   File: main_opt.hpp
///
/// Author: $author$
///   Date: 5/3/2022, 11/10/2024
///////////////////////////////////////////////////////////////////////
#ifndef XOS_CONSOLE_GETOPT_MAIN_OPT_HPP
#define XOS_CONSOLE_GETOPT_MAIN_OPT_HPP

#include "xos/console/main.hpp"
#include <getopt.h>

#define XOS_CONSOLE_MAIN_OPT_ARGUMENT_NONE     0
#define XOS_CONSOLE_MAIN_OPT_ARGUMENT_REQUIRED 1
#define XOS_CONSOLE_MAIN_OPT_ARGUMENT_OPTIONAL 2

#define XOS_CONSOLE_MAIN_INVALID_OPTVAL_C '?'

#define XOS_CONSOLE_MAIN_LOGGING_OPT "logging-level"
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_RESULT 0
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG "{ (a)all | (n)none | (f)fatal | (e)error | (w)waring | (i)info | (d)debug | (t)trace }"
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_ALL 'a'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_NONE 'n'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_FATAL 'f'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_ERROR 'e'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_WARN 'w'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_INFO 'i'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_DEBUG 'd'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_TRACE 't'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_MESSAGE_FATAL 'F'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_MESSAGE_ERROR 'E'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_MESSAGE_WARN 'W'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_MESSAGE_INFO 'I'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_MESSAGE_DEBUG 'D'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_MESSAGE_TRACE 'T'
#define XOS_CONSOLE_MAIN_LOGGING_OPTUSE ""
#define XOS_CONSOLE_MAIN_LOGGING_OPTVAL_S "l:"
#define XOS_CONSOLE_MAIN_LOGGING_OPTVAL_C 'l'
#define XOS_CONSOLE_MAIN_LOGGING_OPTION \
   {XOS_CONSOLE_MAIN_LOGGING_OPT, \
    XOS_CONSOLE_MAIN_LOGGING_OPTARG_REQUIRED, \
    XOS_CONSOLE_MAIN_LOGGING_OPTARG_RESULT, \
    XOS_CONSOLE_MAIN_LOGGING_OPTVAL_C}, \

#define XOS_CONSOLE_MAIN_DEBUG_OPT "debug"
#define XOS_CONSOLE_MAIN_DEBUG_OPTARG_REQUIRED XOS_CONSOLE_MAIN_LOGGING_OPTARG_REQUIRED
#define XOS_CONSOLE_MAIN_DEBUG_OPTARG_RESULT XOS_CONSOLE_MAIN_LOGGING_OPTARG_RESULT
#define XOS_CONSOLE_MAIN_DEBUG_OPTARG XOS_CONSOLE_MAIN_LOGGING_OPTARG
#define XOS_CONSOLE_MAIN_DEBUG_OPTUSE XOS_CONSOLE_MAIN_LOGGING_OPTUSE
#define XOS_CONSOLE_MAIN_DEBUG_OPTVAL_S "d:"
#define XOS_CONSOLE_MAIN_DEBUG_OPTVAL_C 'd'
#define XOS_CONSOLE_MAIN_DEBUG_OPTION \
   {XOS_CONSOLE_MAIN_DEBUG_OPT, \
    XOS_CONSOLE_MAIN_DEBUG_OPTARG_REQUIRED, \
    XOS_CONSOLE_MAIN_DEBUG_OPTARG_RESULT, \
    XOS_CONSOLE_MAIN_DEBUG_OPTVAL_C}, \

#define XOS_CONSOLE_MAIN_HELP_OPT "help"
#define XOS_CONSOLE_MAIN_HELP_OPTARG_REQUIRED XOS_CONSOLE_MAIN_OPT_ARGUMENT_NONE
#define XOS_CONSOLE_MAIN_HELP_OPTARG_RESULT 0
#define XOS_CONSOLE_MAIN_HELP_OPTARG ""
#define XOS_CONSOLE_MAIN_HELP_OPTUSE "Usage options"
#define XOS_CONSOLE_MAIN_HELP_OPTVAL_S "h"
#define XOS_CONSOLE_MAIN_HELP_OPTVAL_C 'h'
#define XOS_CONSOLE_MAIN_HELP_OPTION \
   {XOS_CONSOLE_MAIN_HELP_OPT, \
    XOS_CONSOLE_MAIN_HELP_OPTARG_REQUIRED, \
    XOS_CONSOLE_MAIN_HELP_OPTARG_RESULT, \
    XOS_CONSOLE_MAIN_HELP_OPTVAL_C}, \

#define XOS_CONSOLE_MAIN_USAGE_OPT "usage"
#define XOS_CONSOLE_MAIN_USAGE_OPTARG_REQUIRED XOS_CONSOLE_MAIN_HELP_OPTARG_REQUIRED
#define XOS_CONSOLE_MAIN_USAGE_OPTARG_RESULT XOS_CONSOLE_MAIN_HELP_OPTARG_RESULT
#define XOS_CONSOLE_MAIN_USAGE_OPTARG XOS_CONSOLE_MAIN_HELP_OPTARG
#define XOS_CONSOLE_MAIN_USAGE_OPTUSE XOS_CONSOLE_MAIN_HELP_OPTUSE
#define XOS_CONSOLE_MAIN_USAGE_OPTVAL_S "u"
#define XOS_CONSOLE_MAIN_USAGE_OPTVAL_C 'u'
#define XOS_CONSOLE_MAIN_USAGE_OPTION \
   {XOS_CONSOLE_MAIN_USAGE_OPT, \
    XOS_CONSOLE_MAIN_USAGE_OPTARG_REQUIRED, \
    XOS_CONSOLE_MAIN_USAGE_OPTARG_RESULT, \
    XOS_CONSOLE_MAIN_USAGE_OPTVAL_C}, \

///////////////////////////////////////////////////////////////////////
#define XOS_CONSOLE_MAIN_OPTIONS_CHARS \
    XOS_CONSOLE_MAIN_LOGGING_OPTVAL_S \
    XOS_CONSOLE_MAIN_HELP_OPTVAL_S \

#define XOS_CONSOLE_MAIN_OPTIONS_OPTIONS \
    XOS_CONSOLE_MAIN_LOGGING_OPTION \
    XOS_CONSOLE_MAIN_HELP_OPTION \

///////////////////////////////////////////////////////////////////////
#define XOS_CONSOLE_HELP_MAIN_OPTIONS_CHARS \
    XOS_CONSOLE_MAIN_LOGGING_OPTVAL_S \
    XOS_CONSOLE_MAIN_HELP_OPTVAL_S \

#define XOS_CONSOLE_HELP_MAIN_OPTIONS_OPTIONS \
    XOS_CONSOLE_MAIN_LOGGING_OPTION \
    XOS_CONSOLE_MAIN_HELP_OPTION \

///////////////////////////////////////////////////////////////////////
#define XOS_CONSOLE_USAGE_MAIN_OPTIONS_CHARS \
    XOS_CONSOLE_MAIN_LOGGING_OPTVAL_S \
    XOS_CONSOLE_MAIN_USAGE_OPTVAL_S \

#define XOS_CONSOLE_USAGE_MAIN_OPTIONS_OPTIONS \
    XOS_CONSOLE_MAIN_LOGGING_OPTION \
    XOS_CONSOLE_MAIN_USAGE_OPTION \

///////////////////////////////////////////////////////////////////////
#define XOS_CONSOLE_LOGGING_MAIN_OPTIONS_CHARS \
    XOS_CONSOLE_MAIN_LOGGING_OPTVAL_S \

#define XOS_CONSOLE_LOGGING_MAIN_OPTIONS_OPTIONS \
    XOS_CONSOLE_MAIN_LOGGING_OPTION \

///////////////////////////////////////////////////////////////////////
#define XOS_CONSOLE_MAIN_DEBUG_OPTIONS_CHARS \
    XOS_CONSOLE_MAIN_DEBUG_OPTVAL_S \
    XOS_CONSOLE_MAIN_HELP_OPTVAL_S \

#define XOS_CONSOLE_MAIN_DEBUG_OPTIONS_OPTIONS \
    XOS_CONSOLE_MAIN_DEBUG_OPTION \
    XOS_CONSOLE_MAIN_HELP_OPTION \

///////////////////////////////////////////////////////////////////////
#define XOS_CONSOLE_MAIN_HELP_OPTIONS_CHARS \
    XOS_CONSOLE_MAIN_LOGGING_OPTVAL_S \
    XOS_CONSOLE_MAIN_HELP_OPTVAL_S \

#define XOS_CONSOLE_MAIN_HELP_OPTIONS_OPTIONS \
    XOS_CONSOLE_MAIN_LOGGING_OPTION \
    XOS_CONSOLE_MAIN_HELP_OPTION \

///////////////////////////////////////////////////////////////////////
#define XOS_CONSOLE_MAIN_LOGGING_OPTIONS_CHARS \
    XOS_CONSOLE_MAIN_LOGGING_OPTVAL_S \

#define XOS_CONSOLE_MAIN_LOGGING_OPTIONS_OPTIONS \
    XOS_CONSOLE_MAIN_LOGGING_OPTION \

///////////////////////////////////////////////////////////////////////
#define XOS_CONSOLE_MAIN_USAGE_OPTIONS_CHARS \
    XOS_CONSOLE_MAIN_LOGGING_OPTVAL_S \
    XOS_CONSOLE_MAIN_USAGE_OPTVAL_S \

#define XOS_CONSOLE_MAIN_USAGE_OPTIONS_OPTIONS \
    XOS_CONSOLE_MAIN_LOGGING_OPTION \
    XOS_CONSOLE_MAIN_USAGE_OPTION \

///////////////////////////////////////////////////////////////////////
#define XOS_CONSOLE_MAIN_DEBUG_USAGE_OPTIONS_CHARS \
    XOS_CONSOLE_MAIN_DEBUG_OPTVAL_S \
    XOS_CONSOLE_MAIN_USAGE_OPTVAL_S \

#define XOS_CONSOLE_MAIN_DEBUG_USAGE_OPTIONS_OPTIONS \
    XOS_CONSOLE_MAIN_DEBUG_OPTION \
    XOS_CONSOLE_MAIN_USAGE_OPTION \

///////////////////////////////////////////////////////////////////////

namespace xos {

enum {
    MAIN_OPT_ARGUMENT_NONE     = XOS_CONSOLE_MAIN_OPT_ARGUMENT_NONE,
    MAIN_OPT_ARGUMENT_REQUIRED = XOS_CONSOLE_MAIN_OPT_ARGUMENT_REQUIRED,
    MAIN_OPT_ARGUMENT_OPTIONAL = XOS_CONSOLE_MAIN_OPT_ARGUMENT_OPTIONAL
};

namespace console {
namespace getopt {

/// class main_optt
template <class TExtends = xos::console::main, class TImplements = typename TExtends::implements>
class exported main_optt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements, Implements;
    typedef TExtends extends, Extends;
    typedef main_optt derives, Derives;

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
    main_optt(): run_(0) {
    }
    virtual ~main_optt() {
    }
private:
    main_optt(const main_optt& copy) {
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

    /// ...get_options...
    virtual int get_options(int argc, char_t** argv, char** env) {
        int err = 0;
        int longindex = 0;
        const struct option* longopts = 0;
        char_t optvaluename[2] = {0,0};
        const char_t* optname = optvaluename;
        const char_t* optstring = 0;
        int optvalue = 0;

        if ((optstring = options(longopts)) && (longopts)) {
            opterr = 0; optopt = 0;
            while (0 <= (optvalue = getopt_long(argc, argv, optstring, longopts, &longindex))) {
                optvaluename[0] = optvalue;
                optname = (longindex)?(longopts[longindex].name):(optvaluename);

                if ((err = all_on_option
                     (optvalue, optarg, optname, longindex, argc, argv, env))) {
                    break;
                }
            }
        }
        return err;
    }
    virtual int before_get_options(int argc, char_t** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int after_get_options(int argc, char_t** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int all_get_options(int argc, char_t** argv, char** env) {
        int err = 0;
        if (!(err = before_get_options(argc, argv, env))) {
            int err2 = 0;
            err = get_options(argc, argv, env);
            if ((err2 = after_get_options(argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }

    /// on...option...
    virtual int on_invalid_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 1;
        char_t optval_chars[2] = {((char_t)optval), 0};
        this->errl("Invalid option -", optval_chars, " --", optname, "\n", NULL);
        return err;
    }
    virtual int on_invalid_option_arg
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 1;
        this->errl("Invalid argument \"", optarg, "\" for option \"", optname, "\"\n", NULL);
        return err;
    }
    virtual int on_invalid_option_arg_value
    (const char_t* optarg, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 1;
        const char_t* optind_chars = 0;
        int_to_string optind_string(optind);
        if (!(optind_chars = optind_string.chars())) {
            optind_chars = "";
        }
        this->errl("Invalid argument value \"", optarg, "\" on option ", optind_chars, "\n", NULL);
        return err;
    }
    virtual int on_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        switch(optval) {
        default:
            err = on_invalid_option
            (optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual int before_on_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t** argv, char** env) {
        int err = 0;
        switch(optval) {
        case XOS_CONSOLE_MAIN_INVALID_OPTVAL_C:
            if (!opterr) {
                int argind = (0 < optind)?(optind):((0 < ::optind)?(::optind):((0 < argc)?(1):(0)));
                const char_t* arg = argv[(argc > argind)?(argind):(argc - 1)];
                int optchar = (arg[1]!='-')?(arg[1]):(arg[2]);
                const char_t* optchars = (arg[1]!='-')?(arg+1):(arg+2);
                err = on_invalid_option
                (optchar, optarg, optchars, optind, argc, argv, env);
            }
        break;
        }
        return err;
    }
    virtual int after_on_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int all_on_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t** argv, char** env) {
        int err = 0;
        if (!(err = before_on_option(optval, optarg, optname, optind, argc, argv, env))) {
            int err2 = 0;
            err = on_option(optval, optarg, optname, optind, argc, argv, env);
            if ((err2 = after_on_option(optval, optarg, optname, optind, argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }
    
    /// ...option...
    virtual const char_t* option_usage
    (const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = "";
        switch(longopt->val) {
        default:
            break;
        }
        return chars;
    }
    virtual const char_t* options(const struct option*& longopts) {
        static const char_t* chars = 0;
        static struct option optstruct[]= {
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

    /// ...arguments...
    virtual int before_get_arguments(int argc, char_t** argv, char** env) {
        int err = 0;
        err = all_get_options(argc, argv, env);
        return err;
    }
    virtual int arguments_index() const {
        return optind;
    }

    /// ...usage...
    virtual int usage(int argc, char_t** argv, char_t** env) {
        int err = 0;
        const char_t* arg = 0;
        const char_t** args = 0;
        const char_t* argstring = this->arguments(args);
        const struct option* longopts = 0;
        const char_t* optstring = options(longopts);
        const char_t* name = usage_name(argc, argv, env);

        this->outl
        ("Usage: ", (name)?(name):(""),(optstring)?(" [options]"):(""),
         (argstring)?(" "):(""), (argstring)?(argstring):(""), "\n", NULL);

        if ((optstring) && (longopts)) {
            this->out("\nOptions:\n");

            while ((longopts->name)) {
                const char_t* optarg =
                (MAIN_OPT_ARGUMENT_REQUIRED == longopts->has_arg)?(" arg"):
                ((MAIN_OPT_ARGUMENT_OPTIONAL == longopts->has_arg)?(" [arg]"):(""));
                const char_t* optusage = option_usage(optarg, longopts);
                const char_t* optarg_separator = (optarg[0])?(" "):("");
                const char_t* optusage_separator = "  ";
                const char_t* optarg_name = longopts->name;
                const char optarg_value[2] = {((char)(longopts->val)), 0};

                this->outl
                (" -", optarg_value, " --", optarg_name,
                 optarg_separator, optarg, optusage_separator, optusage, "\n", NULL);
                longopts++;
            }
        }
        if ((argstring) && (args)) {
            this->out("\nArguments:\n");

            while ((arg = (*args))) {
                this->outl(" ", arg, "\n", NULL);
                args++;
            }
        }
        this->set_did_usage();
        return err;
    }
    virtual const char_t* usage_name(int argc, char_t** argv, char_t** env) const {
        const char_t* arg0 = (0 < argc)?((argv)?(argv[0]):(0)):(0);
        if ((arg0)) {
            for (const char_t* i = arg0; *i; ++i) {
                char c = (char)(*i);
                if (('/' == c) || ('\\' == c) || (':' == c)) {
                    arg0 = i + 1;
                }
            }
        }
        return arg0;
    }
}; /// class main_optt
typedef main_optt<> main_opt;

} /// namespace getopt
} /// namespace console
} /// namespace xos

#endif /// ndef XOS_CONSOLE_GETOPT_MAIN_OPT_HPP
