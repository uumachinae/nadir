///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2016 $organization$
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
///   Date: 11/17/2016
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_BASE_ARRAY_HPP
#define _NADIR_BASE_ARRAY_HPP

#include "nadir/base/to_char.hpp"

#define NADIR_ARRAY_DEFAULT_SIZE 128

namespace nadir {

typedef implement_base arrayt_implements;
typedef base arrayt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: arrayt
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = char,
 typename TSize = size_t, TSize VDefaultSize = NADIR_ARRAY_DEFAULT_SIZE,
 class TImplements = arrayt_implements, class TExtends = arrayt_extends>

class _EXPORT_CLASS arrayt: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TWhat what_t;
    typedef TSize size_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    arrayt(const TWhat* elements, size_t length)
    : elements_(sized_elements_), size_(VDefaultSize), length_(0) {
        append(elements, length);
    }
    arrayt(ssize_t length)
    : elements_(sized_elements_), size_(VDefaultSize), length_(0) {
        set_length(length);
    }
    arrayt(const arrayt& copy)
    : elements_(sized_elements_), size_(VDefaultSize), length_(0) {
        append(copy.elements(), copy.length());
    }
    arrayt()
    : elements_(sized_elements_), size_(VDefaultSize), length_(0) {
    }
    virtual ~arrayt() {
        clear();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual arrayt& assign(const TWhat* elements, size_t elements_length){
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
    virtual arrayt& append(const TWhat* elements, size_t elements_length){
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

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set(const TWhat& element){
        return set(element, length_);
    }
    virtual size_t set(const TWhat& element, size_t elements_length) {
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
        size_ = VDefaultSize;
        length_ = 0;
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set_length(ssize_t to_length){
        size_t to_size = 0;
        if (!elements_) {
            return 0;
        }
        if (0 > to_length) {
            to_length = VDefaultSize;
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

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set_size(size_t to) {
        if (to != size_){
            adjust_to_size(new_size(to));
        }
        return size_;
    }
    virtual size_t size() const {
        return size_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual TWhat* has_elements(size_t& length) const {
        if (0 < (length = length_)) {
            return elements_;
        }
        return 0;
    }
    virtual TWhat* has_elements() const {
        if (0 < (length_)) {
            return elements_;
        }
        return 0;
    }
    virtual TWhat* elements() const {
        return elements_;
    }
    virtual TWhat& operator[](size_t index) const {
        return (TWhat&)(elements_[index]);
    }
#if !defined(__MSC__)
    virtual operator TWhat*() const {
        return (TWhat*)(elements_);
    }
#endif // !defined(__MSC__)

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t adjust_to_size(size_t size) {
        size_t count = 0;
        TWhat* elements = 0;

        if (!elements_) {
            return 0;
        }
        if (size <= size_) {
            // elements is already big enough
            //
            return size_;
        }
        if (!(elements = new TWhat[size])) {
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
        count = size_;
        return count;
    }
    virtual size_t new_size(size_t size) const {
        size_t count = 0;
        // Lets increase the buffer size by default buffer
        // sized chunks. Note the desired new size is always
        // needed size + 1. The size in chunks is calculated
        // as (new size + (chunk size - 1)) / chunk size.
        // since new size = needed size + 1 then we have
        // chunks = (needed size + chunk size) / chunk size.
        // Finally we need bytes which is chunks * chunk size
        // which can be reduced to
        // ((needed size / chunk size) + 1) * chunk size
        //
        count = (size = ((size/VDefaultSize)+1)*VDefaultSize);
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set_elements
    (TWhat* to, const TWhat& from, size_t size) const {
        size_t count = 0;
        if ((to)) {
            for (count = 0; size > 0; --size, count++) {
                (*to++) = from;
            }
        }
        return count;
    }
    virtual size_t copy_elements
    (TWhat* to, const TWhat* from, size_t size) const {
        size_t count = 0;
        if ((to) && (from)) {
            for (count = 0; size > 0; --size, count++) {
                (*to++) = (*from++);
            }
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    TWhat sized_elements_[VDefaultSize], *elements_;
    size_t size_, length_;
};
typedef arrayt<byte_t> byte_array;
typedef arrayt<word_t> word_array;

typedef arrayt_implements char_arrayt_implements;
///////////////////////////////////////////////////////////////////////
///  Class: char_arrayt
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char,
 typename TEnd = TChar, TEnd VEnd = 0,
 typename TSize = size_t, TSize VDefaultSize = NADIR_ARRAY_DEFAULT_SIZE,
 class TCharTo = to_chart<TChar, char>, class TWCharTo = to_chart<TChar, wchar_t>,
 class TExtends = arrayt<char, TSize, VDefaultSize>,
 class TImplements = char_arrayt_implements>

class _EXPORT_CLASS char_arrayt: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TCharTo char_to;
    typedef TWCharTo wchar_to;
    typedef TChar char_t;
    typedef TEnd end_t;
    static const end_t end = VEnd;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    char_arrayt(const char* chars, size_t length) {
    }
    char_arrayt(const char* chars) {
    }
    char_arrayt(const char& c) {
    }
    ///////////////////////////////////////////////////////////////////////
    char_arrayt(const wchar_t* chars, size_t length) {
    }
    char_arrayt(const wchar_t* chars) {
    }
    char_arrayt(const wchar_t& c) {
    }
    ///////////////////////////////////////////////////////////////////////
    char_arrayt(const char_arrayt& copy): Extends(copy) {
    }
    char_arrayt() {
    }
    virtual ~char_arrayt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual char_arrayt& assign(const char& c) {
        this->clear();
        return append(c);
    }
    virtual char_arrayt& assign(const char* chars) {
        this->clear();
        return append(chars);
    }
    virtual char_arrayt& assign(const char* chars, size_t length) {
        this->clear();
        return append(chars, length);
    }
    ///////////////////////////////////////////////////////////////////////
    virtual char_arrayt& assign(const wchar_t& c) {
        this->clear();
        return append(c);
    }
    virtual char_arrayt& assign(const wchar_t* chars) {
        this->clear();
        return append(chars);
    }
    virtual char_arrayt& assign(const wchar_t* chars, size_t length) {
        this->clear();
        return append(chars, length);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual char_arrayt& append(const char& c) {
        return append(&c, 1);
    }
    virtual char_arrayt& append(const char* chars) {
        if ((chars) && (*chars)) {
            const char_t* to_chars = 0;
            size_t to_length = 0;
            char_to to;
            for (; *chars; ++chars) {
                to_chars = to.transcode(*chars).c_str();
                to_length = to.length();
                Extends::append(to_chars, to_length);
            }
        }
        return *this;
    }
    virtual char_arrayt& append(const char* chars, size_t length) {
        if ((chars) && (length)) {
            const char_t* to_chars = 0;
            size_t to_length = 0;
            char_to to;
            for (; length; --length, ++chars) {
                to_chars = to.transcode(*chars).c_str();
                to_length = to.length();
                Extends::append(to_chars, to_length);
            }
        }
        return *this;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual char_arrayt& append(const wchar_t& c) {
        return append(&c, 1);
    }
    virtual char_arrayt& append(const wchar_t* chars) {
        if ((chars) && (*chars)) {
            const char_t* to_chars = 0;
            size_t to_length = 0;
            wchar_to to;
            for (; *chars; ++chars) {
                to_chars = to.transcode(*chars).c_str();
                to_length = to.length();
                Extends::append(to_chars, to_length);
            }
        }
        return *this;
    }
    virtual char_arrayt& append(const wchar_t* chars, size_t length) {
        if ((chars) && (length)) {
            const char_t* to_chars = 0;
            size_t to_length = 0;
            wchar_to to;
            for (; length; --length, ++chars) {
                to_chars = to.transcode(*chars).c_str();
                to_length = to.length();
                Extends::append(to_chars, to_length);
            }
        }
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef char_arrayt<char> char_array;
typedef char_arrayt<tchar_t> tchar_array;
typedef char_arrayt<wchar_t> wchar_array;
} // namespace nadir

#endif // _NADIR_BASE_ARRAY_HPP 
