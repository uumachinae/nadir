///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2021 $organization$
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
///   File: stream.cpp
///
/// Author: $author$
///   Date: 7/16/2021
///////////////////////////////////////////////////////////////////////
#include "xos/io/crt/file/stream.hpp"

#if !defined(XOS_IO_CRT_FILE_STREAM_INSTANCE)
///#define XOS_IO_CRT_FILE_STREAM_INSTANCE
#endif /// !defined(XOS_IO_CRT_FILE_STREAM_INSTANCE)

namespace xos {
namespace io {
namespace crt {
namespace file {

///  Class: streamt
#if defined(XOS_IO_CRT_FILE_STREAM_INSTANCE)
static stream the_stream;
#endif /// defined(XOS_IO_CRT_FILE_STREAM_INSTANCE)


} /// namespace file
} /// namespace crt
} /// namespace io
} /// namespace xos
