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
///   File: argv.hpp
///
/// Author: $author$
///   Date: 7/26/2020
///////////////////////////////////////////////////////////////////////
#ifndef XOS_BASE_ARGV_HPP
#define XOS_BASE_ARGV_HPP

#include "xos/base/array.hpp"
#include "xos/base/string.hpp"

namespace xos {

/// class argvt
template 
<typename TChar = char, class TString = based::stringt<TChar>,
 class TExtends = arrayt<TChar*>, class TImplements = implement>
class exported argvt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef argvt derives;

    typedef arrayt<TString> strings_t;
    typedef TString string_t;
    typedef TChar* chars_t;
    typedef TChar char_t;

    /// constructor / destructor
    argvt(const char_t** elements, const size_t& length, bool is_end = true): end_(0) {
        append(elements, length);
        if ((is_end)) {
            append_end();
        }
    }
    argvt(const char_t* element, va_list va, bool is_end = true): end_(0) {
        appendv(element, va);
        if ((is_end)) {
            append_end();
        }
    }
    argvt(const char_t* element, ...): end_(0) {
        if ((element) && (element[0])) {
            va_list va;
            va_start(va, element);
            appendv(element, va);
            va_end(va);
        }
        append_end();
    }
    argvt(bool is_end = false): end_(0) {
        if ((is_end)) {
            append_end();
        }
    }
    virtual ~argvt() {
        clear();
    }
private:
    argvt(const argvt& copy): extends(copy) {
    }
public:

    /// assign...
    virtual derives& assignl(const char_t* element, ...) {
        if ((element) && (element[0])) {
            va_list va;
            va_start(va, element);
            assignv(element, va);
            va_end(va);
        }
        return *this;
    }
    virtual derives& assignv(const char_t* element, va_list va) {
        clear();
        append(element, va);
        return *this;
    }
    virtual derives& assign(const char_t** elements, size_t length, bool is_end = false) {
        size_t count = 0;
        clear();
        append(elements, length, is_end);
        return *this;
    }
    virtual derives& assign(const char_t* element, bool is_end = false) {
        assign(&element, 1, is_end);
        return *this;
    }
    virtual derives& assignl_end(const char_t* element, ...) {
        if ((element) && (element[0])) {
            va_list va;
            va_start(va, element);
            assignv_end(element, va);
            va_end(va);
        }
        return *this;
    }
    virtual derives& assignv_end(const char_t* element, va_list va) {
        assignv(element, va);
        append_end();
        return *this;
    }
    virtual derives& assign_end(const char_t** elements, size_t length) {
        assign(elements, length);
        append_end();
        return *this;
    }
    virtual derives& assign_end(const char_t* element) {
        assign(element);
        append_end();
        return *this;
    }
    virtual derives& assign_end() {
        clear();
        append_end();
        return *this;
    }
    
    /// append...
    virtual derives& appendl(const char_t* element, ...) {
        if ((element) && (element[0])) {
            va_list va;
            va_start(va, element);
            appendv(element, va);
            va_end(va);
        }
        return *this;
    }
    virtual derives& appendv(const char_t* element, va_list va) {
        typedef const char_t *const_chars_t;
        for (size_t index = strings_.length(),  count = 0; ((element) && (element[0])); ++count) {
            string_t string(element);
            chars_t chars = 0;

            strings_.append(&string, 1);
            if ((chars = strings_[index + count].buffer())) {
                extends::append(&chars, 1);
                element = va_arg(va, const_chars_t);
                continue;
            }
            break;
        }
        return *this;
    }
    virtual derives& append(const char_t** elements, size_t length, bool is_end = false) {
        if ((elements) && (length)) {
            for (size_t index = strings_.length(),  count = 0; count < length; ++count) {
                string_t string(elements[count]);
                chars_t chars = 0;

                strings_.append(&string, 1);
                if ((chars = strings_[index + count].buffer())) {
                    extends::append(&chars, 1);
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
    virtual derives& append(const char_t* element, bool is_end = false) {
        append(&element, 1, is_end);
        return *this;
    }
    virtual derives& appendl_end(const char_t* element, ...) {
        if ((element) && (element[0])) {
            va_list va;
            va_start(va, element);
            appendv_end(element, va);
            va_end(va);
        }
        return *this;
    }
    virtual derives& appendv_end(const char_t* element, va_list va) {
        appendv(element, va);
        append_end();
        return *this;
    }
    virtual derives& append_end(const char_t** elements, size_t length) {
        append(elements, length);
        append_end();
        return *this;
    }
    virtual derives& append_end(const char_t* element) {
        append(element);
        append_end();
        return *this;
    }
    virtual derives& append_end() {
        extends::append(&end_, 1);
        return *this;
    }

    /// clear
    virtual size_t clear() {
        size_t count = extends::clear();
        strings_.clear();
        return count;
    }

    /// strings / end
    virtual strings_t& strings() const {
        return (strings_t&)strings_;
    }
    virtual chars_t& end() const {
        return (chars_t&)end_;
    }

protected:
    chars_t end_;
    strings_t strings_;
}; /// class argvt

typedef argvt<char> argv;
typedef argvt<wchar_t> wargv;
typedef argvt<tchar_t> targv;

} /// namespace xos

#endif /// ndef XOS_BASE_ARGV_HPP 
