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
#ifndef _NADIR_OS_TIME_HPP
#define _NADIR_OS_TIME_HPP

#include "nadir/base/time.hpp"
#include "nadir/os/os.hpp"

#if defined(WINDOWS)
#include "nadir/os/microsoft/windows/time.hpp"
#elif defined(MACOSX)
#include "nadir/os/apple/osx/time.hpp"
#else // defined(WINDOWS)
#include "nadir/os/posix/time.hpp"
#endif // defined(WINDOWS)

namespace nadir {
namespace os {

typedef os::time time;

namespace current {

typedef os::current::time time;

namespace gmt {
typedef os::current::gmt::time time;
} // namespace gmt

namespace local {
typedef os::current::local::time time;
} // namespace local

} // namespace current
} // namespace os
} // namespace nadir 

#endif // _NADIR_OS_TIME_HPP 
        

