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
///   File: main_opt.cpp
///
/// Author: $author$
///   Date: 6/19/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_APP_CONSOLE_NETWORK_MAIN_HPP
#include "nadir/app/console/network/main_opt.hpp"

namespace nadir {
namespace app {
namespace console {
namespace network {

typedef nadir::console::getopt::maint_implements main_implements;
typedef nadir::console::getopt::main main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main: virtual public main_implements, public main_extends {
public:
    typedef main_implements Implements;
    typedef main_extends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_client_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_server_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_host_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_port_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_family_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_transport_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
#endif // _NADIR_APP_CONSOLE_NETWORK_MAIN_HPP

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        switch(optval) {
        case NADIR_APP_CONSOLE_NETWORK_MAIN_CLIENT_OPTVAL_C:
            err = on_client_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case NADIR_APP_CONSOLE_NETWORK_MAIN_SERVER_OPTVAL_C:
            err = on_server_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case NADIR_APP_CONSOLE_NETWORK_MAIN_HOST_OPTVAL_C:
            err = on_host_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case NADIR_APP_CONSOLE_NETWORK_MAIN_PORT_OPTVAL_C:
            err = on_port_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case NADIR_APP_CONSOLE_NETWORK_MAIN_FAMILY_OPTVAL_C:
            err = on_family_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case NADIR_APP_CONSOLE_NETWORK_MAIN_TRANSPORT_OPTVAL_C:
            err = on_transport_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        default:
            err = Extends::on_option
            (optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* option_usage
    (const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = "";
        switch(longopt->val) {
        case NADIR_APP_CONSOLE_NETWORK_MAIN_CLIENT_OPTVAL_C:
            optarg = NADIR_APP_CONSOLE_NETWORK_MAIN_CLIENT_OPTARG;
            chars = NADIR_APP_CONSOLE_NETWORK_MAIN_CLIENT_OPTUSE;
            break;
        case NADIR_APP_CONSOLE_NETWORK_MAIN_SERVER_OPTVAL_C:
            optarg = NADIR_APP_CONSOLE_NETWORK_MAIN_SERVER_OPTARG;
            chars = NADIR_APP_CONSOLE_NETWORK_MAIN_SERVER_OPTUSE;
            break;
        case NADIR_APP_CONSOLE_NETWORK_MAIN_HOST_OPTVAL_C:
            optarg = NADIR_APP_CONSOLE_NETWORK_MAIN_HOST_OPTARG;
            chars = NADIR_APP_CONSOLE_NETWORK_MAIN_HOST_OPTUSE;
            break;
        case NADIR_APP_CONSOLE_NETWORK_MAIN_PORT_OPTVAL_C:
            optarg = NADIR_APP_CONSOLE_NETWORK_MAIN_PORT_OPTARG;
            chars = NADIR_APP_CONSOLE_NETWORK_MAIN_PORT_OPTUSE;
            break;
        case NADIR_APP_CONSOLE_NETWORK_MAIN_FAMILY_OPTVAL_C:
            optarg = NADIR_APP_CONSOLE_NETWORK_MAIN_FAMILY_OPTARG;
            chars = NADIR_APP_CONSOLE_NETWORK_MAIN_FAMILY_OPTUSE;
            break;
        case NADIR_APP_CONSOLE_NETWORK_MAIN_TRANSPORT_OPTVAL_C:
            optarg = NADIR_APP_CONSOLE_NETWORK_MAIN_TRANSPORT_OPTARG;
            chars = NADIR_APP_CONSOLE_NETWORK_MAIN_TRANSPORT_OPTUSE;
            break;
        default:
            chars = Extends::option_usage(optarg, longopt);
        }
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* options(const struct option*& longopts) {
        int err = 0;
        static const char_t* chars = NADIR_APP_CONSOLE_NETWORK_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            NADIR_APP_CONSOLE_NETWORK_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* arguments(const char_t**& argv) {
        static const char_t* _args = NADIR_APP_CONSOLE_NETWORK_MAIN_ARGS;
        static const char_t* _argv[] = {
            NADIR_APP_CONSOLE_NETWORK_MAIN_ARGV
            0};
        argv = _argv;
        return _args;
    }

#ifndef _NADIR_APP_CONSOLE_NETWORK_MAIN_HPP
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace network
} // namespace console 
} // namespace app 
} // namespace nadir 

#endif // _NADIR_APP_CONSOLE_NETWORK_MAIN_HPP
