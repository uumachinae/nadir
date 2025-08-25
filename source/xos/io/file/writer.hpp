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
///   File: writer.hpp
///
/// Author: $author$
///   Date: 6/1/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_FILE_WRITER_HPP
#define XOS_IO_FILE_WRITER_HPP

#include "xos/io/crt/file/writer.hpp"

namespace xos {
namespace io {
namespace file {

/// class writert
template <class TExtends = extend, class TImplements = implement>
class exported writert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef writert derives; 
    
    /// constructors / destructor
    writert(const writert& copy): extends(copy) {
    }
    writert() {
    }
    virtual ~writert() {
    }
}; /// class writert
typedef writert<> writer;

} /// namespace file
} /// namespace io
} /// namespace xos

#endif /// ndef XOS_IO_FILE_WRITER_HPP
