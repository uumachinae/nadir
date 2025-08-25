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
///   File: logger.hpp
///
/// Author: $author$
///   Date: 2/21/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_CONSOLE_LOGGER_HPP
#define _NADIR_CONSOLE_LOGGER_HPP

#include "nadir/io/logger.hpp"
#include "nadir/mt/os/mutex.hpp"

namespace nadir {
namespace console {

typedef nadir::io::logger_instance_implements logger_implements;
typedef nadir::io::logger_instance logger_extends;
///////////////////////////////////////////////////////////////////////
///  Class: logger
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS logger
: virtual public logger_implements, public logger_extends {
public:
    typedef logger_implements Implements;
    typedef logger_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    logger(mt::mutex& mutex): mutex_(mutex) {
    }
    virtual ~logger() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool lock() { return mutex_.lock(); }
    virtual bool unlock() { return mutex_.unlock(); }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void logfv(const char* format, va_list va) {
        vfprintf(stderr, format, va);
    }
    virtual void log(const char* chars) {
        logf("%s", chars);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    mt::mutex& mutex_;
};

} // namespace console 
} // namespace nadir 

#endif // _NADIR_CONSOLE_LOGGER_HPP 
