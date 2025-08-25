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
///   File: Mode.hpp
///
/// Author: $author$
///   Date: 12/22/2018
///////////////////////////////////////////////////////////////////////
#ifndef _PATRONA_IO_CRT_FILE_MODE_HPP
#define _PATRONA_IO_CRT_FILE_MODE_HPP

#include "patrona/base/Base.hpp"

#define PATRONA_IO_CRT_FILE_MODE_READ "r"
#define PATRONA_IO_CRT_FILE_MODE_WRITE "w"

#define PATRONA_IO_CRT_FILE_MODE_BINARY "b"
#define PATRONA_IO_CRT_FILE_MODE_APPEND "+"

///////////////////////////////////////////////////////////////////////
#define PATRONA_IO_CRT_FILE_MODE_READ_APPEND \
    PATRONA_IO_CRT_FILE_MODE_READ \
    PATRONA_IO_CRT_FILE_MODE_APPEND

#define PATRONA_IO_CRT_FILE_MODE_WRITE_APPEND \
    PATRONA_IO_CRT_FILE_MODE_WRITE \
    PATRONA_IO_CRT_FILE_MODE_APPEND

///////////////////////////////////////////////////////////////////////
#define PATRONA_IO_CRT_FILE_MODE_READ_BINARY \
    PATRONA_IO_CRT_FILE_MODE_READ \
    PATRONA_IO_CRT_FILE_MODE_BINARY

#define PATRONA_IO_CRT_FILE_MODE_WRITE_BINARY \
    PATRONA_IO_CRT_FILE_MODE_WRITE \
    PATRONA_IO_CRT_FILE_MODE_BINARY

#define PATRONA_IO_CRT_FILE_MODE_READ_BINARY_APPEND \
    PATRONA_IO_CRT_FILE_MODE_READ \
    PATRONA_IO_CRT_FILE_MODE_BINARY \
    PATRONA_IO_CRT_FILE_MODE_APPEND

#define PATRONA_IO_CRT_FILE_MODE_WRITE_BINARY_APPEND \
    PATRONA_IO_CRT_FILE_MODE_WRITE \
    PATRONA_IO_CRT_FILE_MODE_BINARY \
    PATRONA_IO_CRT_FILE_MODE_APPEND

namespace patrona {
namespace io {
namespace crt {
namespace file {

enum Mode {
    ModeRead   = 0,
    ModeWrite  = 1,
    ModeAppend = 3,
    ModeBinary = 4,
    ModeReadBinary = (ModeRead | ModeBinary),
    ModeWriteBinary = (ModeWrite | ModeBinary),
    ModeAppendBinary = (ModeAppend | ModeBinary)
};

} // namespace file 
} // namespace crt 
} // namespace io 
} // namespace patrona 

#endif // _PATRONA_IO_CRT_FILE_MODE_HPP 
