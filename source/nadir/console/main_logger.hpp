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
///   File: main_logger.hpp
///
/// Author: $author$
///   Date: 1/7/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_CONSOLE_MAIN_LOGGER_HPP
#define _NADIR_CONSOLE_MAIN_LOGGER_HPP

#include "nadir/console/main.hpp"
#include "nadir/mt/os/mutex.hpp"
#include "nadir/io/logger.hpp"

namespace nadir {
namespace console {

typedef nadir::io::logger_instance main_logger_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main_logger
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main_logger: public main_logger_extends {
public:
    typedef main_logger_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main_logger(mt::mutex& mutex, console::main& main)
    : mutex_(mutex), main_(main), locked_(main.get_locked()) {
        main_.set_locked(this);
    }
    virtual ~main_logger() {
        main_.set_locked(locked_);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool lock() { return mutex_.lock(); }
    virtual bool unlock() { return mutex_.unlock(); }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void logfv(const char* format, va_list va) {
        main_.errfv(format, va);
    }
    virtual void log(const char* chars) {
        main_.err(chars);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    mt::mutex& mutex_;
    console::main& main_;
    locked* locked_;
};

} // namespace console 
} // namespace nadir 

#endif // _NADIR_CONSOLE_MAIN_LOGGER_HPP 
