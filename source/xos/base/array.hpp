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
///   File: array.hpp
///
/// Author: $author$
///   Date: 3/11/2022, 6/20/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_BASE_ARRAY_HPP
#define XOS_BASE_ARRAY_HPP

#include "xos/base/base.hpp"

#define XOS_ARRAY_DEFAULT_SIZE 128

namespace xos {

/// class arrayt
template 
<typename TWhat = char, size_t VDefaultSize = XOS_ARRAY_DEFAULT_SIZE,
 class TExtends = extend, class TImplements = typename TExtends::implements>

class exported arrayt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef arrayt derives;

    typedef TWhat what_t;
    enum { default_size = VDefaultSize };

    /// constructor / destructor
    arrayt(const what_t* elements, size_t length): elements_(sized_elements_), size_(default_size), length_(0) {
        append(elements, length);
    }
    arrayt(ssize_t length): elements_(sized_elements_), size_(default_size), length_(0) {
        set_length(length);
    }
    arrayt(const arrayt& copy): elements_(sized_elements_), size_(default_size), length_(0) {
        append(copy.elements(), copy.length());
    }
    arrayt(): elements_(sized_elements_), size_(default_size), length_(0) {
    }
    virtual ~arrayt() {
        clear();
    }

    /// assign / append
    virtual arrayt& assign(const what_t* elements, size_t elements_length){
        size_t count = 0;
        size_t new_elements_length = 0;

        if ((!elements) || (!elements_) || (elements_length < 1)) {
            return *this;
        }
        if (size_ < (new_elements_length = (elements_length))) {
            if (0 >= (count = adjust_to_size(new_size(new_elements_length)))) {
                return *this;
            }
        }
        copy_elements(elements_, elements, elements_length);
        length_ = (count = elements_length);
        return *this;
    }
    virtual arrayt& append(const what_t* elements, size_t elements_length){
        size_t count = 0;
        size_t new_elements_length = 0;

        if ((!elements) || (!elements_) || (elements_length < 1)) {
            return *this;
        }
        if (size_ < (new_elements_length = (length_ + elements_length))) {
            if (0 >= (count = adjust_to_size(new_size(new_elements_length)))) {
                return *this;
            }
        }
        copy_elements(elements_+length_, elements, elements_length);
        length_ += (count = elements_length);
        return *this;
    }

    /// set / clear
    virtual size_t set(const what_t& element){
        return set(element, length_);
    }
    virtual size_t set(const what_t& element, size_t elements_length) {
        size_t count = 0;
        size_t new_elements_length = 0;

        if ((!elements_) || (elements_length < 1)) {
            return 0;
        }
        if (size_ < (new_elements_length = (elements_length))) {
            if (0 >= (count = adjust_to_size(new_size(new_elements_length)))) {
                return count;
            }
        }
        set_elements(elements_, element, elements_length);
        length_ = (count = elements_length);
        return count;
    }
    virtual size_t clear(){
        size_t count = length_;
        if (elements_) {
            if (elements_ != sized_elements_) {
                delete[] elements_;
            }
        }
        elements_ = sized_elements_;
        size_ = default_size;
        length_ = 0;
        return count;
    }

    /// ...length / ...size
    virtual size_t set_length(ssize_t to_length){
        size_t to_size = 0;
        if (!elements_) {
            return 0;
        }
        if (0 > to_length) {
            to_length = default_size;
        }
        if ((to_size = (size_t)(to_length)) > size_) {
            if (to_length > ((ssize_t)(set_size(to_size)))) {
                return 0;
            }
        }
        length_ = to_length;
        return length_;
    }
    virtual size_t length() const {
        return length_;
    }

    virtual size_t set_size(size_t to) {
        if (to != size_){
            adjust_to_size(new_size(to));
        }
        return size_;
    }
    virtual size_t size() const {
        return size_;
    }

    /// ...elements...
    virtual what_t* has_elements(size_t& size, size_t& length) const {
        size = size_;
        if (0 < (length = length_)) {
            return elements_;
        }
        return 0;
    }
    virtual what_t* has_elements(size_t& length) const {
        if (0 < (length = length_)) {
            return elements_;
        }
        return 0;
    }
    virtual what_t* has_elements() const {
        if (0 < (length_)) {
            return elements_;
        }
        return 0;
    }
    virtual what_t* elements(size_t& size, size_t& length) const {
        size = size_;
        length = length_;
        return elements_;
    }
    virtual what_t* elements(size_t& length) const {
        length = length_;
        return elements_;
    }
    virtual what_t* elements() const {
        return elements_;
    }
    
    /// operator...
    virtual derives& operator = (const arrayt& copy) {
        assign(copy.elements(), copy.length());
        return *this;
    }
    virtual what_t& operator[](size_t index) const {
        return (what_t&)(elements_[index]);
    }
#if !defined(__MSC__)
    virtual operator what_t*() const {
        return (what_t*)(elements_);
    }
#endif /// !defined(__MSC__)

protected:
    /// ...size...
    virtual size_t adjust_to_size(size_t size) {
        what_t* elements = 0;

        if (!elements_) {
            return 0;
        }
        if (size <= size_) {
            /// elements is already big enough
            return size_;
        }
        if (!(elements = new what_t[size])) {
            return 0;
        }
        if (elements_) {
            if (length_ > 0) {
                copy_elements(elements, elements_, length_);
            }
            if (elements_ != sized_elements_) {
                delete elements_;
            }
        }
        elements_ = elements;
        size_ = size;
        return size_;
    }
    virtual size_t new_size(size_t size) const {
        ///
        /// Increase the buffer size by default buffer
        /// sized chunks. Note the desired new size is always
        /// needed size + 1. The size in chunks is calculated
        /// as (new size + (chunk size - 1)) / chunk size.
        /// since new size = needed size + 1 then we have
        /// chunks = (needed size + chunk size) / chunk size.
        /// Finally we need bytes which is chunks * chunk size
        /// which can be reduced to
        /// ((needed size / chunk size) + 1) * chunk size
        ///
        size = ((size / default_size) + 1) * default_size;
        return size;
    }

    /// set / copy elements
    virtual size_t set_elements(what_t* to, const what_t& from, size_t size) const {
        size_t count = 0;
        if ((to)) {
            for (count = 0; size > 0; --size, count++) {
                (*to++) = from;
            }
        }
        return count;
    }
    virtual size_t copy_elements(what_t* to, const what_t* from, size_t size) const {
        size_t count = 0;
        if ((to) && (from)) {
            for (count = 0; size > 0; --size, count++) {
                (*to++) = (*from++);
            }
        }
        return count;
    }

protected:
    what_t sized_elements_[default_size], *elements_;
    size_t size_, length_;
}; /// class arrayt

/// class byte_arrayt
template 
<size_t VDefaultSize = 128, typename TWhat = byte_t, 
 class TExtends = arrayt<TWhat, VDefaultSize>, class TImplements = typename TExtends::implements>
class exported byte_arrayt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef byte_arrayt derives; 
    
    typedef typename extends::what_t what_t;
    enum { default_size = extends::default_size };

    /// constructors / destructor
    byte_arrayt(const byte_arrayt& copy): extends(copy) {
    }
    byte_arrayt() {
    }
    virtual ~byte_arrayt() {
    }
}; /// class byte_arrayt

typedef arrayt<char_t> array;

typedef arrayt<char_t> char_array;
typedef arrayt<tchar_t> tchar_array;
typedef arrayt<wchar_t> wchar_array;

typedef arrayt<byte_t> byte_array;
typedef arrayt<word_t> word_array;

namespace base {

typedef xos::arrayt<> array;
typedef xos::arrayt<char_t> char_array;
typedef xos::arrayt<tchar_t> tchar_array;
typedef xos::arrayt<wchar_t> wchar_array;
typedef xos::arrayt<byte_t> byte_array;
typedef xos::arrayt<word_t> word_array;

/// class arrayt
template 
<typename TWhat = char, 
 typename TSize = size_t, TSize VDefaultSize = XOS_ARRAY_DEFAULT_SIZE,
 class TExtends = xos::arrayt<TWhat, VDefaultSize>, 
 class TImplements = typename TExtends::implements>

class exported arrayt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef arrayt derives;

    typedef TWhat what_t;
    enum { default_size = VDefaultSize };

    /// constructor / destructor
    arrayt(const what_t* elements, size_t length): extends(elements, length) {
    }
    arrayt(ssize_t length): extends(length) {
    }
    arrayt(const arrayt& copy): extends(copy) {
    }
    arrayt() {
    }
    virtual ~arrayt() {
        this->clear();
    }
}; /// class arrayt

typedef xos::array::implements array_implements;
typedef xos::array::extends array_extends;

} /// namespace base
} /// namespace xos

#endif /// ndef XOS_BASE_ARRAY_HPP
