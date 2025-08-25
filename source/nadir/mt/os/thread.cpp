///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2018 $organization$
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
///   File: thread.cpp
///
/// Author: $author$
///   Date: 1/15/2018
///////////////////////////////////////////////////////////////////////
#include "nadir/mt/os/thread.hpp"

#if defined(WINDOWS)
// Windows
#include "nadir/mt/microsoft/windows/thread.cpp"
#elif defined(MACOSX)
// MacOSX
#include "nadir/mt/apple/osx/thread.cpp"
#else // defined(WINDOWS)
// Posix
#include "nadir/mt/posix/thread.cpp"
#endif // defined(WINDOWS)

namespace nadir {
namespace mt {
namespace os {

} // namespace os 
} // namespace mt 
} // namespace nadir 
