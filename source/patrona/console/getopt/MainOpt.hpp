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
///   File: MainOpt.hpp
///
/// Author: $author$
///   Date: 12/22/2018
///////////////////////////////////////////////////////////////////////
#ifndef _PATRONA_CONSOLE_GETOPT_MAINOPT_HPP
#define _PATRONA_CONSOLE_GETOPT_MAINOPT_HPP

#include "patrona/console/Main.hpp"
#include <getopt.h>

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define MAIN_HELP_OPT "help"
#define MAIN_HELP_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_NONE
#define MAIN_HELP_OPTARG ""
#define MAIN_HELP_OPTUSE "Usage options"
#define MAIN_HELP_OPTVAL_S "h"
#define MAIN_HELP_OPTVAL_C 'h'

#define MAIN_HELP_OPTIONS_OPTION \
   {MAIN_HELP_OPT, \
    MAIN_HELP_OPTARG_REQUIRED, 0, \
    MAIN_HELP_OPTVAL_C},

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define MAIN_OPTIONS_CHARS \
    MAIN_HELP_OPTVAL_S

#define MAIN_OPTIONS_OPTIONS \
    MAIN_HELP_OPTIONS_OPTION

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum {
    MAIN_OPT_ARGUMENT_NONE     = 0,
    MAIN_OPT_ARGUMENT_REQUIRED = 1,
    MAIN_OPT_ARGUMENT_OPTIONAL = 2
};

namespace patrona {
namespace console {
namespace getopt {

} // namespace getopt 
} // namespace console 
} // namespace patrona 

#endif // _PATRONA_CONSOLE_GETOPT_MAINOPT_HPP 
