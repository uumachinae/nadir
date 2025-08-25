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
#ifndef _NADIR_NETWORK_APPLE_OSX_SOCKET_HPP
#define _NADIR_NETWORK_APPLE_OSX_SOCKET_HPP

#include "nadir/network/posix/socket.hpp"

namespace nadir {
namespace network {
namespace apple {
namespace osx {

typedef posix::socket_implements sockett_implements;
typedef posix::socket sockett_extends;
///////////////////////////////////////////////////////////////////////
///  Class: sockett
///////////////////////////////////////////////////////////////////////
template
<class TImplements = sockett_implements, class TExtends = sockett_extends>
class _EXPORT_CLASS sockett: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    sockett(const sockett& copy): Extends(copy) {
    }
    sockett() {
    }
    virtual ~sockett() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef sockett<> socket;

} // namespace osx
} // namespace apple 
} // namespace network 
} // namespace nadir 

#endif // _NADIR_NETWORK_APPLE_OSX_SOCKET_HPP 
