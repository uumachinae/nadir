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
///   File: winsock.cpp
///
/// Author: $author$
///   Date: 6/18/2017
///////////////////////////////////////////////////////////////////////
#include "nadir/network/microsoft/windows/winsock.hpp"

#if !defined(WINDOWS)
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
int closesocket(
  _In_ SOCKET s
) {
    return close(s);
}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
int WSAStartup(
  _In_  WORD      wVersionRequested,
  _Out_ LPWSADATA lpWSAData
) {
    memset(lpWSAData, 0, sizeof(WSADATA));
    return 0;
}
int WSACleanup(void) {
    return 0;
}
int WSAGetLastError(void) {
    return errno;
}
#else // !defined(WINDOWS)
#endif // !defined(WINDOWS)

namespace nadir {
namespace network {
namespace microsoft {
namespace windows {

} // namespace windows 
} // namespace microsoft 
} // namespace network 
} // namespace nadir 
