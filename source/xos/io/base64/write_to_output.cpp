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
///   File: write_to_output.cpp
///
/// Author: $author$
///   Date: 8/4/2022
///////////////////////////////////////////////////////////////////////
#include "xos/io/base64/write_to_output.hpp"

#if !defined(XOS_IO_BASE64_WRITE_TO_OUTPUT_INSTANCE)
///#define XOS_IO_BASE64_WRITE_TO_OUTPUT_INSTANCE
#endif /// !defined(XOS_IO_BASE64_WRITE_TO_OUTPUT_INSTANCE)

namespace xos {
namespace io {
namespace base64 {

///  Class: write_to_outputt
#if defined(XOS_IO_BASE64_WRITE_TO_OUTPUT_INSTANCE)
static write_to_output the_write_to_output;
#endif /// defined(XOS_IO_BASE64_WRITE_TO_OUTPUT_INSTANCE)


} /// namespace base64
} /// namespace io
} /// namespace xos
