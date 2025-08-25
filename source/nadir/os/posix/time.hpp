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
///   File: time.hpp
///
/// Author: $author$
///   Date: 1/16/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_OS_POSIX_TIME_HPP
#define _NADIR_OS_POSIX_TIME_HPP

#include "nadir/base/date.hpp"
#include "nadir/io/logger.hpp"

namespace nadir {
namespace os {
namespace posix {

typedef nadir::date_implements time_implements;
typedef nadir::date time_extends;
///////////////////////////////////////////////////////////////////////
///  Class: time
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS time
: virtual public time_implements, public time_extends {
public:
    typedef time_implements Implements;
    typedef time_extends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    time(bool is_current, bool is_gmt, bool is_12 = false) {
        if ((is_current)) {
            if (!(get_current(is_gmt, is_12))) {
                time_exception e(time_failed);
                LOG_ERROR("...failed on get_current(is_gmt = " << ((is_gmt)?("true"):("false")) << ")");
                LOG_ERROR("...throwing time_exception e(time_failed)...");
                throw (e);
            }
        }
    }
    time() {
    }
    virtual ~time() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool get_current(bool is_gmt, bool is_12 = false) {
        bool success = true;
        struct tm tm;
        time_t t;
        ::time(&t);
        if (!(is_local_ = !(is_gmt))) {
            LOG_DEBUG("gmtime_r(&t, &tm)...");
            if (!(gmtime_r(&t, &tm))) {
                LOG_ERROR("...failed errno = " << errno << " on gmtime_r(&t, &tm)");
                return false;
            }
        } else {
            LOG_DEBUG("localtime_r(&t, &tm)...");
            if (!(localtime_r(&t, &tm))) {
                LOG_ERROR("...failed errno = " << errno << " on localtime_r(&t, &tm)");
                return false;
            }
        }
        year_ = tm.tm_year+1900;
        month_ = tm.tm_mon+1;
        day_ = tm.tm_mday;
        hour_ = tm.tm_hour;
        minute_ = tm.tm_min;
        second_ = tm.tm_sec;
        if (is_12) {
            set_24_hour_to_12_hour();
        }
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

namespace current {
typedef posix::time time_extends;
///////////////////////////////////////////////////////////////////////
///  Class: time
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS time: public time_extends {
public:
    typedef time_extends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    time(bool is_gmt, bool is_12 = false): Extends(true, is_gmt, is_12) {
    }
    time(): Extends(true, false) {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

namespace gmt {
typedef current::time time_extends;
///////////////////////////////////////////////////////////////////////
///  Class: time
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS time: public time_extends {
public:
    typedef time_extends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    time(bool is_12 = false): Extends(true, is_12) {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
} // namespace gmt

namespace local {
typedef current::time time_extends;
///////////////////////////////////////////////////////////////////////
///  Class: time
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS time: public time_extends {
public:
    typedef time_extends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    time(bool is_12 = false): Extends(false, is_12) {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
} // namespace local
} // namespace current

} // namespace posix
} // namespace os 
} // namespace nadir 

#endif // _NADIR_OS_POSIX_TIME_HPP 
