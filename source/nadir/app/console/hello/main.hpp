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
///   File: main.hpp
///
/// Author: $author$
///   Date: 9/18/2016
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_APP_CONSOLE_HELLO_MAIN_HPP
#define _NADIR_APP_CONSOLE_HELLO_MAIN_HPP

#include "nadir/console/getopt/main.hpp"
#include "nadir/os/fs/directory/path.hpp"
#include "nadir/os/fs/directory/entry.hpp"
#include "nadir/os/fs/entry.hpp"
#include "nadir/mt/os/process.hpp"
#include "nadir/mt/os/semaphore.hpp"
#include "nadir/base/argv.hpp"

namespace nadir {
namespace app {
namespace console {
namespace hello {

typedef nadir::console::getopt::main main_extends;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main: public main_extends {
public:
    typedef main_extends Extends;
    typedef main Derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main() {
    }
    virtual ~main() {
    }
    
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    int run(int argc, char_t **argv, char_t **env) {
        int err = 0;
        if ((optind < argc)) {
            err = run_fs(argc, argv, env);
        } else {
            err = run_process(argc, argv, env);
        }
        return err;
    }
    int run_process(int argc, char_t **argv, char_t **env) {
        int err = 0;
        const char_t* arg0 = 0;
        char_t **ev = 0;

        if ((0 < argc) && (arg0 = argv[0]) && (arg0[0]) && (ev = env)) {
            const char_t *arg1 = "--help";
            char_t **argv = 0;
            argv_t arg(&arg0, 1);

            arg.append(&arg1, 1, true);
            if ((argv = arg.elements())) {
                const char_t* env0 = ev[0];
                char_t **env = 0;
                argv_t en(&env0, 1);
                
                if ((env0)) {
                    for (int e = 1; (env0 = ev[e]); ++e) {
                        LOG_DEBUG("env[" << e << "] = \"" << env0 << "\"");
                        en.append(&env0, 1);
                    }
                    en.append_end();
                }
                if ((env = en.elements())) {
                    mt::os::process p;
                    
                    LOG_DEBUG("$ " << arg0 << " " << arg1 << "...");
                    p.create(arg0, argv, env, 0, 0);
                }
            }
        }
        return err;
    }
    int run_semaphore(int argc, char_t **argv, char_t **env) {
        int err = 0;
        try {
            nadir::mt::os::semaphore s;
            s.release();
            s.timed_wait(2000);
        } catch (const create_exception& e) {
            LOG_ERROR("...caught const create_exception& e.status() = " << e.status());
            return 1;
        }
        return err;
    }
    int run_fs(int argc, char_t **argv, char_t **env) {
        int err = 0;
        const char* arg = 0;
        
        nadir::os::fs::entry e;
        if ((optind < argc) && (e.exists((arg = argv[optind])))) {
            std::cout << e.name() << " exists\n";
        }

        nadir::os::fs::directory::path p;
        if ((p.open(arg))) {
            nadir::os::fs::directory::entry *e = 0;

            if ((e = p.get_first_entry())) {
                do {
                    std::cout << e->name() << "\n";
                } while ((e = p.get_next_entry()));
            }
            p.close();
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace hello 
} // namespace console 
} // namespace app 
} // namespace nadir 

#endif // _NADIR_APP_CONSOLE_HELLO_MAIN_HPP 
