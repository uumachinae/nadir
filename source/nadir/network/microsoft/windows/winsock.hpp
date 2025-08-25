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
///   File: winsock.hpp
///
/// Author: $author$
///   Date: 6/18/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_NETWORK_MICROSOFT_WINDOWS_WINSOCK_HPP
#define _NADIR_NETWORK_MICROSOFT_WINDOWS_WINSOCK_HPP

#include "nadir/base/base.hpp"

#if !defined(WINDOWS)
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef int SOCKET;
enum { SOCKET_ERROR = -1 };
enum { INVALID_SOCKET = -1 };
enum {
    SD_RECEIVE = 0,
    SD_SEND    = 1,
    SD_BOTH    = 2
};
enum {
    WSADESCRIPTION_LEN = 128,
    WSASYS_STATUS_LEN  = WSADESCRIPTION_LEN
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef struct WSAData {
  WORD           wVersion;
  WORD           wHighVersion;
  char           szDescription[WSADESCRIPTION_LEN+1];
  char           szSystemStatus[WSASYS_STATUS_LEN+1];
  unsigned short iMaxSockets;
  unsigned short iMaxUdpDg;
  char FAR       *lpVendorInfo;
} WSADATA, *LPWSADATA;

extern "C" {
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
int closesocket(
  _In_ SOCKET s
);
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
int WSAStartup(
  _In_  WORD      wVersionRequested,
  _Out_ LPWSADATA lpWSAData
);
int WSACleanup(void);
int WSAGetLastError(void);
} // extern "C"
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

#endif // _NADIR_NETWORK_MICROSOFT_WINDOWS_WINSOCK_HPP 
