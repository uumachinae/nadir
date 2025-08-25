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
///   File: platform.hpp
///
/// Author: $author$
///   Date: 7/23/2017
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_PLATFORM_PLATFORM_HPP
#define _XOS_PLATFORM_PLATFORM_HPP

#include "xos/platform/platform.h"

#if defined(WINDOWS)
#include "xos/platform/platform_windows.hpp"
#else // defined(WINDOWS)
#include "xos/platform/platform_unix.hpp"
#endif // defined(WINDOWS)

namespace xos {

} // namespace xos 

#endif // _XOS_PLATFORM_PLATFORM_HPP 
