///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2020 $organization$
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
///   Date: 5/4/2020
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_STRING_WRITER_HPP
#define XOS_IO_STRING_WRITER_HPP

#include "xos/io/writer.hpp"
#include "xos/base/string.hpp"

namespace xos {
namespace io {
namespace string {

/// class writert
template <class TImplements = io::char_writer, class TExtends = extend>
class exported writert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef writert derives;

    typedef typename implements::what_t what_t;
    typedef typename implements::sized_t sized_t;
    typedef stringt<sized_t> string_t;

    /// constructor / destructor
    writert(const writert& copy): string_(copy.string_) {
    }
    writert(string_t& string): string_(string) {
    }
    virtual ~writert() {
    }

    /// write
    virtual ssize_t write(const what_t* what, size_t size) {
        sized_t* sized = 0;
        if ((sized = ((sized_t*)what)) && (size)) {
            string_.append(sized, size);
            return size;
        }
        return 0;
    }    

protected:
    string_t& string_;
}; /// class writert
typedef writert<> writer;

} /// namespace string
} /// namespace io
} /// namespace xos

#endif /// ndef XOS_IO_STRING_WRITER_HPP 
