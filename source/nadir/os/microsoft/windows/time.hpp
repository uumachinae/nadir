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
///   Date: 1/17/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_OS_MICROSOFT_WINDOWS_TIME_HPP
#define _NADIR_OS_MICROSOFT_WINDOWS_TIME_HPP

#include "nadir/base/date.hpp"
#include "nadir/io/logger.hpp"

#if !defined(WINDOWS)
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef struct _SYSTEMTIME {
  WORD wYear;         // 1601 .. 30827
  WORD wMonth;        // 1 .. 12
  WORD wDayOfWeek;    // 0 .. 6
  WORD wDay;          // 1 .. 31
  WORD wHour;         // 0 .. 23
  WORD wMinute;       // 0 .. 59
  WORD wSecond;       // 0 .. 59
  WORD wMilliseconds; // 0 .. 999
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;
extern "C" {
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void WINAPI GetSystemTime(
  _Out_ LPSYSTEMTIME lpSystemTime
);
void WINAPI GetLocalTime(
  _Out_ LPSYSTEMTIME lpSystemTime
);
}
#else // !defined(WINDOWS)
#endif // !defined(WINDOWS)

namespace nadir {
namespace os {
namespace microsoft {
namespace windows {

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
        SYSTEMTIME st;
        if (!(is_local_ = !(is_gmt))) {
            LOG_DEBUG("GetSystemTime(&st)...");
            GetSystemTime(&st);
        } else {
            LOG_DEBUG("GetLocalTime(&st)...");
            GetLocalTime(&st);
        }
        if ((st.wYear)) {
            year_ = st.wYear;
            month_ = st.wMonth;
            day_ = st.wDay;
            hour_ = st.wHour;
            minute_ = st.wMinute;
            second_ = st.wSecond;
            if ((is_12)) {
                set_24_hour_to_12_hour();
            }
            return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

namespace current {
typedef windows::time time_extends;
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

} // namespace windows
} // namespace microsoft 
} // namespace os 
} // namespace nadir 

#endif // _NADIR_OS_MICROSOFT_WINDOWS_TIME_HPP 
        

