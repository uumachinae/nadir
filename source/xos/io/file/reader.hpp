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
///   File: reader.hpp
///
/// Author: $author$
///   Date: 6/1/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_FILE_READER_HPP
#define XOS_IO_FILE_READER_HPP

#include "xos/io/crt/file/reader.hpp"

namespace xos {
namespace io {
namespace file {

/// class readert
template 
<class TReader = crt::file::char_reader, 
 class TExtends = TReader, class TImplements = typename TExtends::implements>

class exported readert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef readert derives; 
    
    /// constructors / destructor
    readert(const readert& copy): extends(copy) {
    }
    readert() {
    }
    virtual ~readert() {
    }

}; /// class readert
typedef readert<> reader;

typedef readert<crt::file::char_reader> char_reader;

} /// namespace file
} /// namespace io
} /// namespace xos

#endif /// ndef XOS_IO_FILE_READER_HPP
