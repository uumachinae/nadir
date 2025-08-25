///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2016 $organization$
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
///   File: main_main.cpp
///
/// Author: $author$
///   Date: 12/31/2016
///////////////////////////////////////////////////////////////////////
#include "nadir/console/main_main.hpp"
#include "nadir/console/main_logger.hpp"

namespace nadir {
namespace console {

} // namespace console
} // namespace nadir 

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
int main(int argc, char **argv, char **env) {
    int err = 1;
    nadir::console::main* main = 0;
    STDERR_LOG_DEBUG("nadir::console::main::get_the_main()...");
    if ((main = nadir::console::main::get_the_main())) {
        try {
            nadir::mt::os::mutex mutex(false);
            nadir::console::main_logger logger(mutex, *main);
            err = (*main)(argc, argv, env);
        } catch (nadir::create_exception& e) {
            STDERR_LOG_ERROR("...caught nadir::create_exception& e status = " << e.status() << "");
        }
    } else {
        STDERR_LOG_ERROR("...failed 0 = nadir::console::main::get_the_main()");
    }
    return err;
}
