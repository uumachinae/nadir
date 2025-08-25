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
///   File: pipe.hpp
///
/// Author: $author$
///   Date: 12/30/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_MT_OS_PIPE_HPP
#define _NADIR_MT_OS_PIPE_HPP

#include "nadir/mt/os/os.hpp"
#include "nadir/mt/pipe.hpp"

#if defined(WINDOWS)
// Windows
#include "nadir/mt/microsoft/windows/pipe.hpp"
#elif defined(MACOSX)
// MacOSX
#include "nadir/mt/apple/osx/pipe.hpp"
#else // defined(WINDOWS)
// Posix
#include "nadir/mt/posix/pipe.hpp"
#endif // defined(WINDOWS)

namespace nadir {
namespace mt {
namespace os {

typedef os::pipe pipe;

typedef os::char_pipe char_pipe;
typedef os::tchar_pipe tchar_pipe;
typedef os::wchar_pipe wchar_pipe;

typedef os::byte_pipe byte_pipe;
typedef os::word_pipe word_pipe;

} // namespace os 
} // namespace mt 
} // namespace nadir 

#endif // _NADIR_MT_OS_PIPE_HPP 
