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
#ifndef _NADIR_OS_APPLE_OSX_TIME_HPP
#define _NADIR_OS_APPLE_OSX_TIME_HPP

#include "nadir/os/posix/time.hpp"

namespace nadir {
namespace os {
namespace apple {
namespace osx {

typedef posix::time time;

namespace current {
typedef posix::current::time time;

namespace gmt {
typedef posix::current::gmt::time time;
} // namespace gmt

namespace local {
typedef posix::current::local::time time;
} // namespace local
} // namespace current

} // namespace osx
} // namespace apple 
} // namespace os 
} // namespace nadir 

#endif // _NADIR_OS_APPLE_OSX_TIME_HPP 
        

