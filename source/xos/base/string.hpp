///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2019 $organization$
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
///   File: string.hpp
///
/// Author: $author$
///   Date: 12/5/2019, 8/7/2022, 5/10/2025
///////////////////////////////////////////////////////////////////////
#ifndef XOS_BASE_STRING_HPP
#define XOS_BASE_STRING_HPP

#include "xos/base/chars.hpp"
#include <stdarg.h>
#include <locale>
#include <string>
#include <sstream>

#define XOS_STRING_DEFAULT_SIZE 128

namespace xos {

/// class stringt
template 
<typename TChar = char, 
 typename TEndChar = TChar, TEndChar VEndChar = 0, 
 class TSStream = ::std::basic_stringstream<TChar>,
 class TString = ::std::basic_string<TChar>, 
 class TChars = implemented::charst<TChar, TEndChar, VEndChar>,
 class TImplements = TChars, class TExtends = TString>

class exported stringt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef stringt derives;

    typedef TSStream sstream_t;
    typedef TString string_t;
    typedef TChar char_t;
    typedef TEndChar end_char_t;
    enum { end_char = VEndChar };

    /// constructor / destructor
    stringt(const char_t* chars, size_t length) {
        if ((chars) && (length)) {
            this->append(chars, length);
        }
    }
    stringt(const char_t* chars) {
        if ((chars)) {
            this->append(chars);
        }
    }
    stringt(const string_t& copy): extends(copy) {
    }
    stringt(const stringt& copy): extends(copy) {
    }
    stringt() {
    }
    virtual ~stringt() {
    }
    
    /// assign...
    virtual stringt& assignX(const void* in, size_t length, bool upper_case = true) {
        this->assignx(in, length, upper_case);
        return *this;
    }
    virtual stringt& assignx(const void* in, size_t length, bool upper_case = true) {
        this->clear();
        this->appendx(in, length, upper_case);
        return *this;
    }
    virtual stringt& assignln(const char_t* chars, size_t length) {
        this->clear();
        this->appendln(chars, length);
        return *this;
    }
    virtual stringt& assignln(const char_t* chars) {
        this->clear();
        this->appendln(chars);
        return *this;
    }
    virtual stringt& assignl(const char_t* chars, ...) {
        va_list va; va_start(va, chars);
        this->assignv(chars, va);
        va_end(va);
        return *this;
    }
    virtual stringt& assignv(const char_t* chars, va_list va) {
        this->clear();
        return appendv(chars, va);
    }
    virtual stringt& assign_char(char_t value) {
        this->clear();
        this->append_char(value);
        return *this;
    }
    virtual stringt& assign_signed(const signed& value) {
        this->clear();
        this->append_signed(value);
        return *this;
    }
    virtual stringt& assign_unsigned(const unsigned& value) {
        this->clear();
        this->append_unsigned(value);
        return *this;
    }

    /// append...
    virtual stringt& appendX(const void* in, size_t length, bool upper_case = true) {
        this->appendx(in, length, upper_case);
        return *this;
    }
    virtual stringt& appendx(const void* in, size_t length, bool upper_case = false) {
        const byte_t* bytes = (const byte_t*)(in);
        if ((bytes) && (length)) {
            char_t x[2];
            byte_t b;
            for (; 0 < length; --length) {
                b = (*bytes++);
                x[0] = this->to_x(b >> 4, upper_case);
                x[1] = this->to_x(b & 15, upper_case);
                this->append(x, 2);
            }
        }
        return *this;
    }
    virtual stringt& appendln(const char_t* chars, size_t length) {
        this->append(chars, length);
        this->appendln();
        return *this;
    }
    virtual stringt& appendln(const char_t* chars) {
        this->append(chars);
        this->appendln();
        return *this;
    }
    virtual stringt& appendln() {
        this->appendcr();
        this->appendlf();
        return *this;
    }
    virtual stringt& appendcr() {
        char_t cr = ((char_t)'\r');
        this->append(&cr, 1);
        return *this;
    }
    virtual stringt& appendlf() {
        char_t lf = ((char_t)'\n');
        this->append(&lf, 1);
        return *this;
    }
    virtual stringt& appendl(const char_t* chars, ...) {
        va_list va; va_start(va, chars);
        appendv(chars, va);
        va_end(va);
        return *this;
    }
    virtual stringt& appendv(const char_t* chars, va_list va) {
        typedef const char_t* const_chars_t;
        if ((chars)) {
            do { this->append(chars);
            } while ((chars = va_arg(va, const_chars_t)));
        }
        return *this;
    }
    virtual stringt& append_char(char_t value) {
        this->append(&value, 1);
        return *this;
    }
    virtual stringt& append_signed(const signed& value) {
        sstream_t sstream; sstream << value;
        this->append(sstream.str().c_str());
        return *this;
    }
    virtual stringt& append_unsigned(const unsigned& value) {
        sstream_t sstream; sstream << value;
        this->append(sstream.str().c_str());
        return *this;
    }

    /// to...
    virtual signed to_signed() const {
        signed to = 0;
        sstream_t ss(*this);
        ss >> to;
        return to;
    }
    virtual unsigned to_unsigned() const {
        unsigned to = 0;
        sstream_t ss(*this);
        ss >> to;
        return to;
    }
    virtual bool to_bool() const {
        bool to = 0;
        sstream_t ss(*this);
        ss >> to;
        return to;
    }

    /// ...chars
    virtual const char_t* has_chars(size_t& length) const {
        const char_t* chars = this->c_str();
        length = this->length();
        return (length)?(chars):(0);
    }
    virtual const char_t* has_chars() const {
        const char_t* chars = this->c_str();
        size_t length = this->length();
        return (length)?(chars):(0);
    }
    virtual const char_t* chars(size_t& length) const {
        length = this->length();
        return this->c_str();
    }
    virtual const char_t* chars() const {
        return this->c_str();
    }

    virtual int cased_compare(const stringt& to) const {
        int unequal = case_compare(*this, to, cased_compare);
        return unequal;
    }
    virtual int uncased_compare(const stringt& to) const {
        int unequal = case_compare(*this, to, uncased_compare);
        return unequal;
    }
protected:
    static int case_compare
    (const stringt& s, const stringt& to,
     int compare(const char_t& c, const char_t& c2)) {
        int unequal = 0, compared = 0;
        const char_t *chars = 0, *to_chars = 0, *end = 0;
        size_t length = 0, to_length = 0;

        if ((chars = s.has_chars(length))) {
            if ((to_chars = to.has_chars(to_length))) {
                if (((end = (chars + length)) - chars) > to_length) {
                    end = (chars + to_length);
                    unequal = 1;
                } else {
                    if (to_length > length) {
                        unequal = -1;
                    }
                }
                for (; chars != end; ++chars, ++to_chars) {
                    if ((compared = compare(*chars, *to_chars))) {
                        return compared;
                    }
                }
            } else {
                unequal = 1;
            }
        } else {
            if ((to_chars = to.has_chars(to_length))) {
                unequal = -1;
            }
        }
        return unequal;
    }
    static int cased_compare(const char_t& c, const char_t& c2) {
        if (c > c2) { return 1; } else {
            if (c < c2) { return -1; }
        }
        return 0;
    }
    static int uncased_compare(const char_t& c, const char_t& c2) {
        ::std::locale locale;
        char_t tolower_c = ::std::tolower(c, locale), 
               tolower_c2 = ::std::tolower(c2, locale);
        return cased_compare(tolower_c, tolower_c2);
    }
}; /// class stringt

typedef stringt<> string;
typedef stringt<char> char_string;
typedef stringt<tchar_t> tchar_string;
typedef stringt<wchar_t> wchar_string;

#if defined(STD_BYTE_STRING_ALLOWED)
typedef stringt<byte_t> byte_string;
#endif /// defined(STD_BYTE_STRING_ALLOWED)

/// class string_to_string
template <typename TString, class TExtends, class TImplements = typename TExtends::implements>
class exported string_to_string: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef string_to_string derives;

    typedef TString tchar_string;
    typedef typename tchar_string::char_t tchar_t;
    typedef extends char_string;
    typedef typename char_string::extends string_t;
    typedef typename char_string::char_t char_t;
    
    /// constructor / destructor
    string_to_string(const tchar_string& copy) {
        append(copy);
    }
    string_to_string(const tchar_t* copy, size_t length) {
        append(copy, length);
    }
    string_to_string(const tchar_t* copy) {
        append(copy);
    }
    string_to_string(const char_string& copy): extends(copy) {
    }
    string_to_string(const char_t* copy, size_t length): extends(copy, length) {
    }
    string_to_string(const char_t* copy): extends(copy) {
    }
    string_to_string(const string_to_string& copy): extends(copy) {
    }
    string_to_string() {
    }
    virtual ~string_to_string() {
    }
    
    /// assign
    using extends::assign;
    virtual derives& assign(const tchar_string& copy) {
        this->clear();
        append(copy);
        return *this;
    }
    virtual derives& assign(const tchar_t* copy, size_t length) {
        this->clear();
        append(copy, length);
        return *this;
    }
    virtual derives& assign(const tchar_t* copy) {
        this->clear();
        append(copy);
        return *this;
    }

    /// append
    using extends::append;
    virtual derives& append(const tchar_string& copy) {
        const tchar_t* chars = 0;
        size_t length = 0;
        if ((chars = copy.has_chars(length))) {
            append(chars, length);
        }
        return *this;
    }
    virtual derives& append(const tchar_t* copy, size_t length) {
        if (copy) {
            for (; 0 < length; --length, ++copy) {
                char_t c = (char_t)(*copy);
                this->append(&c, 1);
            }
        }
        return *this;
    }
    virtual derives& append(const tchar_t* copy) {
        if (copy) {
            for (char_t c = (char_t)(*copy); 0 != c; c = (char_t)(*(++copy))) {
                this->append(&c, 1);
            }
        }
        return *this;
    }
}; /// class string_to_string

typedef string_to_string<wchar_string, char_string> to_char_string;
typedef string_to_string<char_string, wchar_string> to_wchar_string;

namespace based {
/// class stringt
template 
<typename TChar = char, size_t VDefaultSize = XOS_STRING_DEFAULT_SIZE,
 typename TEndChar = TChar, TEndChar VEndChar = 0,
 class TExtends = extend, class TImplements = implement>
class exported stringt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef stringt derives;

    typedef TChar char_t;
    typedef TEndChar end_char_t;
    enum { default_size = VDefaultSize };
    enum { end_char = VEndChar };

    /// constructor / destructor
    stringt(const char_t* chars, size_t length) {
        construct();
        append(chars, length);
    }
    stringt(const char_t* chars) {
        construct();
        append(chars);
    }
    stringt(const stringt& copy): extends(copy) {
        construct();
        append(copy.c_str(), copy.length());
    }
    stringt() {
        construct();
    }
    virtual ~stringt() {
        destruct();
    }

    /// assign / append / clear
    virtual derives& assign(const char_t* chars, size_t length) {
        clear();
        return append(chars, length);
    }
    virtual derives& assign(const char_t* chars) {
        clear();
        return append(chars);
    }
    virtual derives& assign(const derives& copy) {
        clear();
        return append(copy.c_str(), copy.length());
    }
    virtual derives& append(const char_t* chars, size_t length) {
        if ((chars) && (0 < length)) {
            size_t newSize = (tell_+length);
            if (size_ <= newSize) {
                if (fixed_size_)
                    length = size_-tell_;
                else
                if (!(_adjust_to_size(_new_size_of(newSize))))
                    length = 0;
            }
            if (length) {
                _copy_to(write_buffer_+tell_, chars, length);
                if ((tell_ += length) > length_)
                if ((length_ = tell_) < size_)
                    write_buffer_[tell_] = ((char_t)end_char);
            }
        }
        return *this;
    }
    virtual derives& append(const char_t* chars) {
        return append(chars, _length_of(chars));
    }
    virtual derives& append(const derives& copy) {
        return append(copy.c_str(), copy.length());
    }
    virtual derives& clear() {
        if ((write_buffer_)) {
            if (size_ > (length_ = (tell_ = 0))) {
                write_buffer_[tell_] = ((char_t)end_char);
            }
        }
        return *this;
    }

    /// = / == / !=
    derives& operator = (const derives& copy) {
        return assign(copy);
    }
    bool operator == (const derives& to) const {
        return compare(to) == 0;
    }
    int operator != (const derives& to) const {
        return compare(to);
    }

    /// compare
    virtual int compare(const derives& to) const {
        return compare(to.c_str(), to.length());
    }
    virtual int compare(const char_t* toChars, size_t toLength) const {
        int unequal = 2;
        const char_t* thisChars = 0;
        char_t toChar = 0, thisChar = 0;
        size_t thisLength = 0;
        ssize_t lendiff = 0;

        if (!(thisChars = (c_str()))) {
            return (toChars)?(-1):(1);
        }

        if (0 < (lendiff = (toLength - (thisLength = length())))) {
            toLength = thisLength;
            unequal = -1;
        } else {
            if (lendiff) {
                unequal = 1;
            }
        }

        if (toLength > 0) {
            do {
                if ((thisChar = *(thisChars++)) > (toChar = *(toChars++))) {
                    return 1;
                } else {
                    if (thisChar < toChar) {
                        return -1;
                    }
                }
            } while (--toLength > 0);
        }
        return unequal;
    }
    virtual int compare(const char_t* toChars) const {
        return compare(toChars, _length_of(toChars));
    }

    /// buffer / chars / length
    virtual char_t* buffer() const {
        return str();
    }
    virtual const char_t* chars() const {
        return c_str();
    }
    virtual char_t* str() const {
        return write_buffer_;
    }
    virtual const char_t* c_str() const {
        return read_buffer_;
    }
    virtual size_t length() const {
        return length_;
    }

protected:
    /// construct / destruct
    virtual void construct() {
        free_buffer_ = fixed_size_ = false;
        size_ = default_size;
        length_ = tell_ = 0;
        read_buffer_ = write_buffer_ = default_buffer_;
    }
    virtual void destruct() {
        if ((write_buffer_ != default_buffer_)) {
            if ((write_buffer_) && (free_buffer_)) {
                _free_buffer(write_buffer_);
            }
        }
    }

    /// ...size...
    virtual size_t adjust_size(size_t newSize) {
        if (write_buffer_) {
            if (size_ < (newSize)) {
                if (!fixed_size_) {
                    if (0 < (_adjust_to_size(_new_size_of(newSize)))) {
                        return size_;
                    }
                }
            } else {
                return size_;
            }
        }
        return 0;
    }
    virtual size_t _adjust_to_size(size_t size) {
        if (write_buffer_) {
            if (size > size_) {
                bool freeBuffer = false;
                char_t* buffer = 0;

                if (!(freeBuffer = free_buffer_)) {
                    free_buffer_ = true;
                }
                if ((buffer = _alloc_buffer(size))) {
                    if (length_ > 0) {
                        _copy_to(buffer, write_buffer_, length_);
                    }
                    if ((write_buffer_ != default_buffer_) && (freeBuffer)) {
                        _free_buffer(write_buffer_);
                    }
                    read_buffer_ = write_buffer_ = buffer;
                    size_ = size;
                    return size_;
                } else {
                    free_buffer_ = freeBuffer;
                }
            } else {
                return size_;
            }
        }
        return 0;
    }
    virtual size_t _new_size_of(size_t size) const {
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
        return ((size/default_size)+1)*default_size;
    }

    /// ...copy... / ...length...
    virtual size_t _copy_to(char_t* to, const char_t* from, size_t size) const {
        size_t length = 0;

        for (length = size; size; --size) {
            (*to++) = (*from++);
        }
        return length;
    }
    virtual size_t _length_of(const char_t* chars) const {
        const char_t endChar(((char_t)end_char));
        size_t length = 0;

        for (length = 0; ((*chars) != endChar); chars++) {
            length++;
        }
        return length;
    }

    /// ...alloc... / ...free...
    virtual char_t* _alloc_buffer(size_t size) const {
        char_t* chars = new char_t[size];
        return chars;
    }
    virtual void _free_buffer(char_t* buffer) const {
        delete[] buffer;
    }

protected:
    bool free_buffer_, fixed_size_;
    size_t size_, length_, tell_;
    const char_t* read_buffer_;
    char_t* write_buffer_;
    char_t default_buffer_[default_size];
}; /// class stringt
typedef stringt<> string;

typedef stringt<char> char_string;
typedef stringt<tchar_t> tchar_string;
typedef stringt<wchar_t> wchar_string;

typedef stringt<byte_t> byte_string;
typedef stringt<word_t> word_string;
} /// namespace based

namespace base {

typedef xos::char_string::implements string_implements;
typedef xos::char_string::extends string_extends;

typedef xos::tchar_string::implements tstring_implements;
typedef xos::tchar_string::extends tstring_extends;

typedef xos::wchar_string::implements wstring_implements;
typedef xos::wchar_string::extends wstring_extends;

#if defined(STD_BYTE_STRING_ALLOWED)
typedef xos::byte_string::implements bstring_implements;
typedef xos::byte_string::extends bstring_extends;
#endif /// defined(STD_BYTE_STRING_ALLOWED)

/// class stringt
template 
<typename TChar = char, typename TEndChar = TChar, TEndChar VEndChar = 0, 
 class TExtends = xos::stringt<TChar, TEndChar, VEndChar>, 
 class TImplements = typename TExtends::implements>

class exported stringt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements, Implements;
    typedef TExtends extends, Extends;
    typedef stringt derives, Derives;

    typedef typename extends::char_t sized_t;
    typedef typename extends::char_t what_t;
    typedef typename extends::char_t char_t;
    typedef typename extends::end_char_t end_char_t, end_t;
    enum { end_char = extends::end_char, end = extends::end_char };
    typedef typename extends::string_t string_t;

    /// constructor / destructor
    stringt(const char* chars, size_t length) {
        this->append(chars, length);
    }
    stringt(const wchar_t* chars, size_t length) {
        this->append(chars, length);
    }
    stringt(const char* chars) {
        this->append(chars);
    }
    stringt(const wchar_t* chars) {
        this->append(chars);
    }
    stringt(const string_t& copy): extends(copy) {
    }
    stringt(const stringt& copy): extends(copy) {
    }
    stringt() {
    }
    virtual ~stringt() {
    }
    
    // wchar_t
    /// assign...
    using extends::assign;
    virtual stringt& assign(const wchar_t* chars) {
        this->clear();
        this->append(chars);
        return *this;
    }
    virtual stringt& assign(const wchar_t* chars, size_t length) {
        this->clear();
        this->append(chars);
        return *this;
    }
    virtual stringt& assignl(const wchar_t* chars, ...) {
        this->clear();
        if ((chars)) {
            va_list va;
            va_start(va, chars);
            this->appendv(chars, va);
            va_end(va);
        }
        return *this;
    }
    virtual stringt& assignv(const wchar_t* chars, va_list va) {
        this->clear();
        if ((chars)) {
            this->appendv(chars, va);
        }
        return *this;
    }
    /// append...
    using extends::append;
    virtual stringt& append(const wchar_t* chars) {
        if ((chars)) {
            for (wchar_t c = *chars; c != 0; c = *(++chars)) {
                char_t tc = ((char_t)c);
                extends::append(&tc, 1);
            }
        }
        return *this;
    }
    virtual stringt& append(const wchar_t* chars, size_t length) {
        if ((chars) && (length)) {
            for (; length > 0; --length, ++chars) {
                char_t tc = ((char_t)(*chars));
                extends::append(&tc, 1);
            }
        }
        return *this;
    }
    virtual stringt& appendl(const wchar_t* chars, ...) {
        if ((chars)) {
            va_list va;
            va_start(va, chars);
            this->appendv(chars, va);
            va_end(va);
        }
        return *this;
    }
    virtual stringt& appendv(const wchar_t* chars, va_list va) {
        if ((chars)) {
            do {
                this->append(chars);
            } while ((chars = va_arg(va, const wchar_t*)));
        }
        return *this;
    }

}; /// class stringt
typedef stringt<> string;

typedef stringt<char> cstring;
typedef stringt<tchar_t> tstring;
typedef stringt<wchar_t> wstring;

#if defined(STD_BYTE_STRING_ALLOWED)
typedef stringt<byte_t> bstring;
#endif /// defined(STD_BYTE_STRING_ALLOWED)

/// class string_baset
template 
<typename TChar = char, size_t VDefaultSize = XOS_STRING_DEFAULT_SIZE,
 typename TEndChar = TChar, TEndChar VEndChar = 0,
 class TExtends = xos::based::stringt<TChar, VDefaultSize, TEndChar, VEndChar>, 
 class TImplements = implement>
class exported string_baset: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements,implements;
    typedef TExtends Extends, extends;
    typedef string_baset Derives, derives;

    typedef typename extends::char_t sized_t;
    typedef typename extends::char_t what_t;
    typedef typename extends::char_t char_t;
    typedef typename extends::end_char_t end_char_t, end_t;
    enum { end_char = extends::end_char, end = extends::end_char };

    /// constructor / destructor
    string_baset(const char* chars, size_t length) {
        this->append(chars, length);
    }
    string_baset(const wchar_t* chars, size_t length) {
        this->append(chars, length);
    }
    string_baset(const char* chars) {
        this->append(chars);
    }
    string_baset(const wchar_t* chars) {
        this->append(chars);
    }
    string_baset(const extends& copy): extends(copy) {
    }
    string_baset(const string_baset& copy): extends(copy) {
    }
    string_baset() {
    }
    virtual ~string_baset() {
    }

    // wchar_t
    /// assign...
    using extends::assign;
    virtual string_baset& assign(const wchar_t* chars) {
        this->clear();
        this->append(chars);
        return *this;
    }
    virtual string_baset& assign(const wchar_t* chars, size_t length) {
        this->clear();
        this->append(chars);
        return *this;
    }
    virtual string_baset& assignl(const wchar_t* chars, ...) {
        this->clear();
        if ((chars)) {
            va_list va;
            va_start(va, chars);
            this->appendv(chars, va);
            va_end(va);
        }
        return *this;
    }
    virtual string_baset& assignv(const wchar_t* chars, va_list va) {
        this->clear();
        if ((chars)) {
            this->appendv(chars, va);
        }
        return *this;
    }
    /// append...
    using extends::append;
    virtual string_baset& append(const wchar_t* chars) {
        if ((chars)) {
            for (wchar_t c = *chars; c != 0; c = *(++chars)) {
                char_t tc = ((char_t)c);
                extends::append(&tc, 1);
            }
        }
        return *this;
    }
    virtual string_baset& append(const wchar_t* chars, size_t length) {
        if ((chars) && (length)) {
            for (; length > 0; --length, ++chars) {
                char_t tc = ((char_t)(*chars));
                extends::append(&tc, 1);
            }
        }
        return *this;
    }
    virtual string_baset& appendl(const wchar_t* chars, ...) {
        if ((chars)) {
            va_list va;
            va_start(va, chars);
            this->appendv(chars, va);
            va_end(va);
        }
        return *this;
    }
    virtual string_baset& appendv(const wchar_t* chars, va_list va) {
        if ((chars)) {
            do {
                this->append(chars);
            } while ((chars = va_arg(va, const wchar_t*)));
        }
        return *this;
    }
}; /// class string_baset
typedef string_baset<> string_base;

typedef string_baset<tchar_t> tstring_base;
typedef string_baset<wchar_t> wstring_base;
typedef string_baset<byte_t> bstring_base;

} /// namespace base

} /// namespace xos

#endif /// ndef XOS_BASE_STRING_HPP
