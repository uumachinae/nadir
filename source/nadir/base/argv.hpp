///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2017 $organization$
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
///   File: argv.hpp
///
/// Author: $author$
///   Date: 1/13/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_BASE_ARGV_HPP
#define _NADIR_BASE_ARGV_HPP

#include "nadir/base/array.hpp"
#include "nadir/base/string_base.hpp"

#define NADIR_BASE_ARGV_DEFAULT_SIZE NADIR_ARRAY_DEFAULT_SIZE

namespace nadir {

typedef arrayt_implements argv_implements;
///////////////////////////////////////////////////////////////////////
///  Class: argvt
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char, typename TSize = size_t,
 TSize VDefaultSize = NADIR_BASE_ARGV_DEFAULT_SIZE,
 class TString = string_baset<TChar>,
 class TExtends = arrayt<TChar*, TSize, VDefaultSize>,
 class TImplements = argv_implements>

class _EXPORT_CLASS argvt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef argvt Derives;

    typedef TString string_t;
    typedef TChar* chars_t;
    typedef TChar char_t;
    typedef TSize size_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    argvt(const char_t** elements, size_t length, bool is_end = false): end_(0) {
        append(elements, length);
        if ((is_end)) {
            append_end();
        }
    }
    argvt(bool is_end = false): end_(0) {
        if ((is_end)) {
            append_end();
        }
    }
    virtual ~argvt() {
        clear();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Derives& assign
    (const char_t** elements, size_t length, bool is_end = false) {
        size_t count = 0;
        clear();
        append(elements, length);
        return *this;
    }
    virtual Derives& append
    (const char_t** elements, size_t length, bool is_end = false) {
        size_t count = 0;
        if ((elements) && (length)) {
            for (size_t index = strings_.length(); count < length; ++count) {
                string_t s(elements[count]);
                chars_t chars = 0;
                strings_.append(&s, 1);
                if ((chars = strings_[index + count].buffer())) {
                    Extends::append(&chars, 1);
                    continue;
                }
                break;
            }
            if ((is_end)) {
                append_end();
            }
        }
        return *this;
    }
    virtual Derives& append_end() {
        Extends::append(&end_, 1);
        return *this;
    }
    virtual size_t clear() {
        size_t count = Extends::clear();
        strings_.clear();
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef arrayt<string_t, size_t, VDefaultSize> strings_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    chars_t end_;
    strings_t strings_;
};

typedef argvt<char_t> argv_t;
typedef argvt<wchar_t> wargv_t;
typedef argvt<tchar_t> targv_t;

} // namespace nadir

#endif // _NADIR_BASE_ARGV_HPP 
