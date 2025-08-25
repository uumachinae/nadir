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
///   File: time.cpp
///
/// Author: $author$
///   Date: 1/17/2017
///////////////////////////////////////////////////////////////////////
#include "nadir/os/microsoft/windows/time.hpp"

#if !defined(WINDOWS)
void WINAPI GetCurrentTime(
  _Out_ LPSYSTEMTIME lpSystemTime,
  _In_ BOOL bIsUTC
) {
    if ((lpSystemTime)) {
        bool success = false;
        struct tm tm; time_t t;
        memset(lpSystemTime, 0, sizeof(SYSTEMTIME));
        ::time(&t);
        if ((bIsUTC)) {
            if (!(success = (0 != (gmtime_r(&t, &tm))))) {
                LOG_ERROR("...failed errno = " << errno << " on gmtime_r(&t, &tm)");
            }
        } else {
            if (!(success = (0 != (localtime_r(&t, &tm))))) {
                LOG_ERROR("...failed errno = " << errno << " on localtime_r(&t, &tm)");
            }
        }
        if ((success)) {
            SYSTEMTIME& st = *lpSystemTime;
            st.wYear = tm.tm_year+1900;
            st.wMonth = tm.tm_mon+1;
            st.wDay = tm.tm_mday;
            st.wDayOfWeek = tm.tm_wday;
            st.wHour = tm.tm_hour;
            st.wMinute = tm.tm_min;
            st.wSecond = tm.tm_sec;
        }
    }
}
void WINAPI GetSystemTime(
  _Out_ LPSYSTEMTIME lpSystemTime
) {
    GetCurrentTime(lpSystemTime, TRUE);
}
void WINAPI GetLocalTime(
  _Out_ LPSYSTEMTIME lpSystemTime
) {
    GetCurrentTime(lpSystemTime, FALSE);
}
#else // !defined(WINDOWS)
#endif // !defined(WINDOWS)

namespace nadir {
namespace os {
namespace microsoft {
namespace windows {

} // namespace windows
} // namespace microsoft 
} // namespace os 
} // namespace nadir 
