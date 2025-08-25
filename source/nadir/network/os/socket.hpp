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
///   File: socket.hpp
///
/// Author: $author$
///   Date: 6/17/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_NETWORK_OS_SOCKET_HPP
#define _NADIR_NETWORK_OS_SOCKET_HPP

#include "nadir/network/os/os.hpp"
#include "nadir/network/socket.hpp"

#if defined(WINDOWS)
// Windows
#include "nadir/network/microsoft/windows/socket.hpp"
#elif defined(MACOSX)
// MacOSX
#include "nadir/network/apple/osx/socket.hpp"
#else // defined(WINDOWS)
// Posix
#include "nadir/network/posix/socket.hpp"
#endif // defined(WINDOWS)

namespace nadir {
namespace network {
namespace os {

typedef os::socket socket;

} // namespace os
} // namespace network 
} // namespace nadir 

#endif // _NADIR_NETWORK_OS_SOCKET_HPP 
