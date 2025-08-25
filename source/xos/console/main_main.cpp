///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2019 $organization$
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
///   Date: 12/3/2019
///////////////////////////////////////////////////////////////////////
#include "xos/mt/os/mutex.hpp"
#include "xos/console/main_main.hpp"
#include "xos/console/logger.cpp"
#include "xos/console/io.cpp"

namespace xos {
namespace console {

} /// namespace console
} /// namespace xos

/// function main
int main(int argc, char** argv, char** env) {
    int err = 0;

    try {
        LOGGING_LEVELS levels = DEFAULT_LOGGING_LEVELS;
        ::xos::console::logger logger(levels);

        try {
            bool mutex_is_logged = true;
            ::xos::mt::os::mutex mutex(mutex_is_logged);

            mutex.set_is_logged(false);
            GET_LOGGING_LEVEL(levels);
            try {
                ::xos::console::logger logger(mutex, levels);
    
                LOGGER_LOG_DEBUG("try {...");
                try {
                    LOGGER_LOG_DEBUG("::xos::console::main::the_main(argc, argv, env)...");
                    err = ::xos::console::main::the_main(argc, argv, env);
                    SET_LOGGING_LEVEL(levels);
                    LOGGER_LOG_DEBUG("..." << err << " = ::xos::console::main::the_main(argc, argv, env)");
                } catch (const ::xos::exception& e) {
                    SET_LOGGING_LEVEL(levels);
                    LOGGER_LOG_ERROR("...catch (const ::xos::exception& e = \"" << e.status_to_chars() << "\")");
                    err = 1;
                } catch (...) {
                    SET_LOGGING_LEVEL(levels);
                    LOGGER_LOG_ERROR("...catch (...)");
                    err = 1;
                }
                LOGGER_LOG_DEBUG("...} try");
            } catch (const ::xos::exception& e) {
                err = 1;
            } catch (...) {
                err = 1;
            }
            mutex.set_is_logged(mutex_is_logged);
        } catch (const ::xos::exception& e) {
            ::xos::console::logger logger;
            LOGGER_LOG_ERROR("...catch (const ::xos::exception& e = \"" << e.status_to_chars() << "\")");
            err = 1;
        } catch (...) {
            ::xos::console::logger logger;
            LOGGER_LOG_ERROR("...catch (...)");
            err = 1;
        }
    } catch (const ::xos::exception& e) {
        err = 1;
    } catch (...) {
        err = 1;
    }
    return err;
} /// function main
