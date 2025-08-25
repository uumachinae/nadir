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
///   File: reader.hpp
///
/// Author: $author$
///   Date: 4/10/2020, 8/24/2021, 5/10/2025
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_STRING_READER_HPP
#define XOS_IO_STRING_READER_HPP

#include "xos/io/reader.hpp"
#include "xos/base/string.hpp"

namespace xos {
namespace io {
namespace string {

/// class readert
template 
<typename TString = base::string,
 class TImplements = io::char_readert<io::char_seekert<io::char_sequencet
 <typename TString::char_t> > >, class TExtends = extend>
class exported readert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef readert derives;

    typedef TString string_t;
    typedef typename implements::what_t what_t;
    typedef typename implements::sized_t sized_t;
    enum { from_begining = io::from_begining,
           from_end = io::from_end,
           from_current = io::from_current };

    /// constructor / destructor
    readert(const readert& copy): string_(copy.string_), tell_(0) {
    }
    readert(const string_t& string): string_(string), tell_(0) {
    }
    readert(): string_(this_string_), tell_(0) {
    }
    virtual ~readert() {
    }

    /// read
    virtual ssize_t read(what_t* what, size_t size) {
        size_t length = this->length();
        sized_t* sized = 0;

        if ((sized = ((sized_t*)what)) && (size) && (length > (this->tell_))) {
            const char_t* chars = 0;

            if (length < (this->tell_ + size)) {
                if (1 > (size = length - this->tell_)) {
                    return 0;
                }
            }
            if ((chars = string_.chars())) {
                ssize_t count = 0;

                if ((sizeof(sized_t) == sizeof(char_t))) {
                    for (chars += this->tell_; size; --size, ++chars, ++sized, ++count) {
                        *sized = *(((const sized_t*)chars));
                    }
                }
                this->tell_ += count;
                return count;
            }
        }
        return 0;
    }

    /// reset / seek / tell
    virtual ssize_t reset() {
        tell_ = 0;
        return tell_;
    }
    virtual ssize_t seek(size_t to) {
        return seek(to, from_begining);
    }
    virtual ssize_t seek(size_t to, int whence) {
        size_t length = this->length();
        if (from_end == (whence)) {
            if (length < (to)) {
                to = 0;
            } else {
                to = length - to;
            }
        } else {
            if (from_current == (whence)) {
                if (length < (to += tell_)) {
                    to = length;
                }
            } else {
                if (length < (to)) {
                    to = length;
                }
            }
        }
        tell_ = to;
        return tell_;
    }
    virtual ssize_t tell() const {
        return tell_;
    }
    virtual ssize_t length() const {
        return string_.length();
    }

protected:
    string_t this_string_;
    const string_t& string_;
    size_t tell_;
}; /// class readert
typedef readert<> reader;

typedef readert<base::cstring> char_reader;
typedef readert<base::tstring> tchar_reader;
typedef readert<base::wstring> wchar_reader;

#if defined(STD_BYTE_STRING_ALLOWED)
typedef stringt<base::bstring> byte_string;
#endif /// defined(STD_BYTE_STRING_ALLOWED)

} /// namespace string
} /// namespace io
} /// namespace xos

#endif /// ndef XOS_IO_STRING_READER_HPP 
