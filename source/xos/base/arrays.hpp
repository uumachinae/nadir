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
///   File: arrays.hpp
///
/// Author: $author$
///   Date: 4/17/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_BASE_ARRAYS_HPP
#define XOS_BASE_ARRAYS_HPP

#include "xos/base/array.hpp"

namespace xos {

/// class arrayst
template 
<typename TElement = xos::array, typename TWhat = TElement*, size_t VDefaultSize = XOS_ARRAY_DEFAULT_SIZE,
 class TExtends = xos::arrayt<TWhat, VDefaultSize>, class TImplements = typename TExtends::implements>

class exported arrayst: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef arrayst derives;

    typedef TElement element_t;
    typedef TWhat what_t;
    enum { default_size = VDefaultSize };

    /// constructor / destructor
    arrayst(const what_t* what, size_t length): extends(what, length) {
    }
    arrayst(ssize_t length): extends(length) {
    }
    arrayst(const arrayst& copy): extends(copy) {
    }
    arrayst() {
    }
    virtual ~arrayst() {
    }

    /// new_instance
    virtual element_t* new_instance() {
        element_t* instance = 0;
        instance = new element_t;
        return instance;
    }

}; /// class arrayst
typedef xos::arrayst<> arrays;

typedef xos::arrayst<char_array> char_arrays;
typedef xos::arrayst<tchar_array> tchar_arrays;
typedef xos::arrayst<wchar_array> wchar_arrays;

typedef xos::arrayst<byte_array> byte_arrays;
typedef xos::arrayst<word_array> word_arrays;

namespace base {
} /// namespace base
} /// namespace xos

#endif /// XOS_BASE_ARRAYS_HPP
