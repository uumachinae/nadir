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
///   File: Main.hpp
///
/// Author: $author$
///   Date: 12/22/2018
///////////////////////////////////////////////////////////////////////
#ifndef _PATRONA_CONSOLE_GETOPT_MAIN_HPP
#define _PATRONA_CONSOLE_GETOPT_MAIN_HPP

#include "patrona/console/getopt/MainOpt.hpp"

namespace patrona {
namespace console {
namespace getopt {

typedef console::MainTImplements MainTImplements;
typedef console::Main MainTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: MainT
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char, typename TEndChar = TChar, TEndChar VEndChar = 0,
 class TImplements = MainTImplements, class TExtends = MainTExtends>

class _EXPORT_CLASS MainT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TChar char_t;
    typedef TEndChar endchar_t;
    static const TEndChar endchar = VEndChar;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    MainT() {
    }
    virtual ~MainT() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int BeforeRun(int argc, char_t**argv, char_t** env) {
        int err = 0;
        if (!(err = BeforeGetOptions(argc, argv, env))) {
            int err2 = 0;
            err = GetOptions(argc, argv, env);
            if ((err2 = AfterGetOptions(argc, argv, env))) {
                if (!err) err = err2;
            } else {
                if ((err2 = BeforeGetArguments(argc, argv, env))) {
                    if (!(err)) err = err2;
                } else {
                    if ((err2 = GetArguments(argc, argv, env))) {
                        if (!(err)) err = err2;
                    }
                    if ((err2 = AfterGetArguments(argc, argv, env))) {
                        if (!(err)) err = err2;
                    }
                }
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int GetOptions(int argc, char_t**argv, char_t** env) {
        int err = 1;
        return err;
    }
    virtual int BeforeGetOptions(int argc, char_t**argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int AfterGetOptions(int argc, char_t**argv, char_t** env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int GetArguments(int argc, char_t**argv, char_t** env) {
        int err = 1;
        return err;
    }
    virtual int BeforeGetArguments(int argc, char_t**argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int AfterGetArguments(int argc, char_t**argv, char_t** env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef MainTImplements MainImplements;
typedef MainT<> MainExtends;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main: virtual public MainImplements, public MainExtends {
public:
    typedef MainImplements Implements;
    typedef MainExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Main() {
    }
    virtual ~Main() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Usage(int argc, char** argv, char** env) {
        int err = 0;

        if (!(DidUsage())) {
            const char* arg = 0;
            const char** args = 0;
            const char* argstring = Arguments(args);
            const struct option* longopts = 0;
            const char* optstring = Options(longopts);
            const char* name = UsageName(argc, argv, env);

            OutF
            ("Usage: %s%s%s%s\n", (name)?(name):(""),
             (optstring)?(" [options]"):(""),
             (argstring)?(" "):(""), (argstring)?(argstring):(""));

            if ((optstring) && (longopts)) {
                OutF("\nOptions:\n");

                while ((longopts->name)) {
                    const char* optarg =
                    (MAIN_OPT_ARGUMENT_REQUIRED == longopts->has_arg)?(" arg"):
                    ((MAIN_OPT_ARGUMENT_OPTIONAL == longopts->has_arg)?(" [arg]"):(""));
                    const char* optusage = OptionUsage(optarg, longopts);
                    const char* optargSeparator = (optarg[0])?(" "):("");
                    const char* optusageSeparator = "  ";

                    OutF
                    (" -%c --%s%s%s%s%s\n",
                     longopts->val, longopts->name,
                     optargSeparator, optarg, optusageSeparator, optusage);
                    longopts++;
                }
            }

            if ((argstring) && (args)) {
                OutF("\nArguments:\n");

                while ((arg = (*args))) {
                    OutF(" %s\n", arg);
                    args++;
                }
            }
            SetDidUsage();
        }
        return err;
    }
    virtual const char* UsageName
    (int argc, char** argv, char** env) const {
        const char* arg0 = (0 < argc)?((argv)?(argv[0]):(0)):(0);
        if ((arg0)) {
            for (const char* i = arg0; *i; ++i) {
                char c = (*i);
                if (('/' == c) || ('\\' == c) || (':' == c)) {
                    arg0 = i + 1;
                }
            }
        }
        return arg0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int GetOptions(int argc, char**argv, char** env) {
        int err = 0;
        int longindex = 0;
        const struct option* longopts = 0;
        char optvaluename[2] = {0,0};
        const char* optname = optvaluename;
        const char* optstring = 0;
        int optvalue = 0;

        if ((optstring = Options(longopts)) && (longopts)) {
            while (0 <= (optvalue = getopt_long(argc, argv, optstring, longopts, &longindex))) {
                optvaluename[0] = optvalue;
                optname = (longindex)?(longopts[longindex].name):(optvaluename);

                if ((err = OnOption(optvalue, optarg, optname, longindex, argc, argv, env))) {
                    break;
                }
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnUsageOption
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char** argv, char** env) {
        int err = Usage(argc, argv, env);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnInvalidOption
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 1;
        ErrF("invalid option \"%s\"\n", optname);
        return err;
    }
    virtual int OnInvalidOptionArg
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 1;
        ErrF("invalid argument \"%s\" for option \"%s\"\n", optarg, optname);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnOption
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char** argv, char** env) {
        int err = 0;
        switch(optval) {
        case MAIN_HELP_OPTVAL_C:
            err = OnUsageOption
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        default:
            err = OnInvalidOption
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        }
        return err;
    }
    virtual const char* OptionUsage
    (const char*& optarg, const struct option* longopt) {
        const char* chars = "";
        switch(longopt->val) {
        case MAIN_HELP_OPTVAL_C:
            chars = MAIN_HELP_OPTUSE;
            break;
        default:
            break;
        }
        return chars;
    }
    virtual const char* Options(const struct option*& longopts) {
        static const char* chars = MAIN_OPTIONS_CHARS;
        static struct option optstruct[] = {
            MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int GetArguments(int argc, char** argv, char** env) {
        int err = 0;
        if (argc > (optind)) {
            for (int argind = optind; argind < argc; ++argind) {
                if ((err = OnArgument(argv[argind], argind-optind, argc, argv, env))) {
                    break;
                }
            }
        }
        return err;
    }
    virtual int OnArgument
    (const char* arg, int argind,
     int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int MissingArgument(const char* arg) {
        int err = 1;
        this->ErrF("missing argument \"%s\"\n", arg);
        return err;
    }
    virtual const char* Arguments(const char**& args) {
        args = 0;
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace getopt
} // namespace console 
} // namespace patrona 

#endif // _PATRONA_CONSOLE_GETOPT_MAIN_HPP 
