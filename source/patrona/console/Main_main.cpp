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
///   File: Main_main.cpp
///
/// Author: $author$
///   Date: 12/22/2018
///////////////////////////////////////////////////////////////////////
#include "patrona/console/Main_main.hpp"
#include "patrona/io/Logger.hpp"

namespace patrona {
namespace cpp {
namespace xos {
namespace console {

} // namespace console 
} // namespace xos 
} // namespace cpp 
} // namespace patrona 

///////////////////////////////////////////////////////////////////////
/// Function main
///////////////////////////////////////////////////////////////////////
int main(int argc, char** argv, char** env) {
    int err = 0;
    ERR_LOG_DEBUG("try {...");
    try {
        ERR_LOG_DEBUG("patrona::console::Main::TheMain(argc, argv, env)...");
        err = patrona::console::Main::TheMain(argc, argv, env);
        ERR_LOG_DEBUG("..." << err << " = patrona::console::Main::TheMain(argc, argv, env)");
    } catch (...) {
        ERR_LOG_ERROR("...} catch (...)");
    }
    ERR_LOG_DEBUG("...} try");
    return err;
}
