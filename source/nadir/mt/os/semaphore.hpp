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
///   File: semaphore.hpp
///
/// Author: $author$
///   Date: 1/2/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_MT_OS_SEMAPHORE_HPP
#define _NADIR_MT_OS_SEMAPHORE_HPP

#include "nadir/mt/semaphore.hpp"
#include "nadir/mt/os/os.hpp"

#if defined(WINDOWS)
// Windows
#include "nadir/mt/microsoft/windows/semaphore.hpp"
#elif defined(MACOSX)
// MacOSX
#include "nadir/mt/apple/osx/semaphore.hpp"
#else // defined(WINDOWS)
// Posix
#include "nadir/mt/posix/semaphore.hpp"
#endif // defined(WINDOWS)

namespace nadir {
namespace mt {
namespace os {

typedef os::semaphore semaphore;

} // namespace os
} // namespace mt
} // namespace nadir 

#endif // _NADIR_MT_OS_SEMAPHORE_HPP
