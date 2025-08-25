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
///   File: to_array.hpp
///
/// Author: $author$
///   Date: 8/1/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_BASE64_TO_ARRAY_HPP
#define XOS_IO_BASE64_TO_ARRAY_HPP

#include "xos/base/array.hpp"

namespace xos {
namespace io {
namespace base64 {

/// class to_arrayt
template 
<class TArray = xos::byte_array, 
 class TExtends = extend, class TImplements = typename TExtends::implements>
class exported to_arrayt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef to_arrayt derives; 
    
    typedef TArray to_t;
    typedef char char_t;
    
    /// constructors / destructor
    to_arrayt(const to_arrayt& copy): to_(copy.to_), filled_(false) {
    }
    to_arrayt(to_t& to): to_(to), filled_(false) {
    }
    virtual ~to_arrayt() {
    }

    /// flush / put
    virtual ssize_t flush() {
        bool &filled = filled_;
        if (!(filled)) {
            to_t &to = to_;
            if ((0 < (to.length()))) {
                filled = true;
            }
        }
        return 0;
    }
    virtual ssize_t put(const byte_t& byte) {
        bool &filled = filled_;
        if (!(filled)) {
            to_t &to = to_;
            to.append(&byte, 1);
            return 1;
        }
        return 0;
    }
    virtual ssize_t put(const char_t& c) {
        bool &filled = filled_;
        if (!(filled)) {
            to_t &to = to_;
            to.append((const byte_t*)(&c), 1);
            return 1;
        }
        return 0;
    }

protected:
    to_t& to_;
    bool filled_;
}; /// class to_arrayt
typedef to_arrayt<> to_array;

} /// namespace base64
} /// namespace io
} /// namespace xos

#endif /// ndef XOS_IO_BASE64_TO_ARRAY_HPP
