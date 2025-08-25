///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2022 $organization$
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
///   File: io.cpp
///
/// Author: $author$
///   Date: 8/5/2022
///////////////////////////////////////////////////////////////////////
#include "xos/console/io.hpp"
#include "xos/console/sequence.cpp"
#include "xos/console/input.cpp"
#include "xos/console/output.cpp"
#include "xos/console/error.cpp"
#include "xos/console/out.cpp"

#if !defined(XOS_CONSOLE_IO_INSTANCE)
///#define XOS_CONSOLE_IO_INSTANCE
#endif /// !defined(XOS_CONSOLE_IO_INSTANCE)

namespace xos {
namespace console {

///  Class: iot
#if defined(XOS_CONSOLE_IO_INSTANCE)
static io the_io;
#endif /// defined(XOS_CONSOLE_IO_INSTANCE)


} /// namespace console
} /// namespace xos
