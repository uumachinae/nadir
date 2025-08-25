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
///   File: error.hpp
///
/// Author: $author$
///   Date: 8/5/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_CONSOLE_ERROR_HPP
#define XOS_CONSOLE_ERROR_HPP

#include "xos/console/out.hpp"

namespace xos {
namespace console {

/// err...
file_t std_err();
ssize_t errlln(const char *what, ...);
ssize_t errl(const char *what, ...);
ssize_t errllnv(const char *what, va_list va);
ssize_t errlv(const char *what, va_list va);
ssize_t errf(const char *format, ...);
ssize_t errfv(const char *format, va_list va);
ssize_t err(const char *what, size_t length);
ssize_t err(const char *what);

/// class errort
template 
<typename TChar = char, typename TFile = FILE*, class TLocked = locked, 
 class TOut = xos::console::outt<TChar, TFile, TLocked>, class TImplements = TOut>

class exported errort: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef errort derives; 
    
    typedef TFile file_t;
    typedef int null_file_t;
    enum { null_file = 0 };

    typedef stringt<TChar> string_t;
    typedef TChar char_t;
    typedef char_t end_char_t;
    enum { end_char = 0 };

    typedef char_t what_t;
    typedef char_t sized_t;
    
    /// constructors / destructor
    virtual ~errort() {
    }

    /// err...
    virtual ssize_t errln(const string_t& chars) {
        ssize_t count = errln(chars.chars(), chars.length());
        return count;
    }
    virtual ssize_t err(const string_t& chars) {
        ssize_t count = err(chars.chars(), chars.length());
        return count;
    }
    virtual ssize_t errlln(const what_t *what, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, what);
        count = this->errllnv(what, va);
        va_end(va);
        return count;
    }
    virtual ssize_t errl(const what_t *what, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, what);
        count = this->errlv(what, va);
        va_end(va);
        return count;
    }
    virtual ssize_t errllnv(const what_t *what, va_list va) {
        file_t f = err_std_err();
        return console::outllnv(f, what, va);
    }
    virtual ssize_t errlv(const what_t *what, va_list va) {
        file_t f = err_std_err();
        return console::outlv(f, what, va);
    }
    virtual ssize_t errf(const sized_t *format, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, format);
        count = this->errfv(format, va);
        va_end(va);
        return count;
    }
    virtual ssize_t errfv(const sized_t *format, va_list va) {
        file_t f = err_std_err();
        return console::outfv(f, format, va);
    }

    virtual ssize_t errXln(const void* out, size_t length, bool upper_case = true) {
        file_t f = err_std_err();
        return this->outxln(f, out, length, upper_case);
    }
    virtual ssize_t errX(const void* out, size_t length, bool upper_case = true) {
        file_t f = err_std_err();
        return this->outx(f, out, length, upper_case);
    }
    virtual ssize_t errxln(const void* out, size_t length, bool upper_case = false) {
        file_t f = err_std_err();
        return this->outxln(f, out, length, upper_case);
    }
    virtual ssize_t errx(const void* out, size_t length, bool upper_case = false) {
        file_t f = err_std_err();
        return this->outx(f, out, length, upper_case);
    }

    virtual ssize_t err0Xln(const void* out, size_t length, bool upper_case = true) {
        file_t f = err_std_err();
        return this->out0xln(f, out, length, upper_case);
    }
    virtual ssize_t err0X(const void* out, size_t length, bool upper_case = true) {
        file_t f = err_std_err();
        return this->out0x(f, out, length, upper_case);
    }
    virtual ssize_t err0xln(const void* out, size_t length, bool upper_case = false) {
        file_t f = err_std_err();
        return this->out0xln(f, out, length, upper_case);
    }
    virtual ssize_t err0x(const void* out, size_t length, bool upper_case = false) {
        file_t f = err_std_err();
        return this->out0x(f, out, length, upper_case);
    }

    virtual ssize_t err64ln(const void* out, size_t length) {
        file_t f = err_std_err();
        return this->out64ln(f, out, length);
    }
    virtual ssize_t err64(const void* out, size_t length) {
        file_t f = err_std_err();
        return this->out64(f, out, length);
    }

    virtual ssize_t errln(const what_t *what, size_t length) {
        file_t f = err_std_err();
        return console::outln(f, what, length);
    }
    virtual ssize_t errln(const what_t *what) {
        file_t f = err_std_err();
        return console::outln(f, what);
    }
    virtual ssize_t err(const what_t *what, size_t length) {
        file_t f = err_std_err();
        return console::out(f, what, length);
    }
    virtual ssize_t err(const what_t *what) {
        file_t f = err_std_err();
        return console::out(f, what);
    }
    virtual ssize_t errln() {
        file_t f = err_std_err();
        return console::outln(f);
    }
    virtual ssize_t err_flush() {
        file_t f = err_std_err();
        return console::out_flush(f);
    }
protected:
    virtual file_t err_std_err() {
        return std_err();
    }
    virtual file_t std_err() const {
        return (file_t)stderr;
    }

}; /// class errort
typedef errort<> error;

} /// namespace console
} /// namespace xos

#endif /// ndef XOS_CONSOLE_ERROR_HPP
