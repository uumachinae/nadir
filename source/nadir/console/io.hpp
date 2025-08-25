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
///   File: io.hpp
///
/// Author: $author$
///   Date: 3/8/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_CONSOLE_IO_HPP
#define _NADIR_CONSOLE_IO_HPP

#include "nadir/base/string.hpp"
#include "nadir/base/locked.hpp"

namespace nadir {
namespace console {

typedef locked iot_implements;
///////////////////////////////////////////////////////////////////////
///  Class: iot
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char, typename TEndChar = TChar, TEndChar VEndChar = 0,
 typename TFile = FILE*, typename TNullFile = int, TNullFile VNullFile = 0,
 class TString = char_stringt<TChar, TEndChar, VEndChar>,
 class TImplements = iot_implements>

class _EXPORT_CLASS iot: virtual public TImplements {
public:
    typedef TImplements Implements;

    typedef TString string_t;

    typedef TFile file_t;
    typedef TNullFile null_file_t;
    enum { null_file = VNullFile };

    typedef TChar char_t;
    typedef TEndChar end_char_t;
    enum { end_char = VEndChar };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t outf(const char_t* format, ...) {
        ssize_t count = 0;
        va_list va;
        if ((format)) {
            va_start(va, format);
            count = this->outfv(format, va);
            va_end(va);
        }
        return count;
    }
    virtual ssize_t outl(const char_t* out, ...) {
        ssize_t count = 0;
        va_list va;
        if ((out)) {
            va_start(va, out);
            count = outlv(out, va);
            va_end(va);
        }
        return count;
    }
    virtual ssize_t outlnl(const char_t* out, ...) {
        ssize_t count = 0, amount = 0;
        va_list va;
        if ((out)) {
            va_start(va, out);
            count = this->outlv(out, va);
            va_end(va);
        }
        if (0 <= (count)) {
            if (0 <= (amount = this->outln())) {
                count += amount;
            } else {
                count = amount;
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t errf(const char_t* format, ...) {
        ssize_t count = 0;
        va_list va;
        if ((format)) {
            va_start(va, format);
            count = this->errfv(format, va);
            va_end(va);
        }
        return count;
    }
    virtual ssize_t errl(const char_t* out, ...) {
        ssize_t count = 0;
        va_list va;
        if ((out)) {
            va_start(va, out);
            count = this->errlv(out, va);
            va_end(va);
        }
        return count;
    }
    virtual ssize_t errlnl(const char_t* out, ...) {
        ssize_t count = 0, amount = 0;
        va_list va;
        if ((out)) {
            va_start(va, out);
            count = this->errlv(out, va);
            va_end(va);
        }
        if (0 <= (count)) {
            if (0 <= (amount = this->errln())) {
                count += amount;
            } else {
                count = amount;
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t inf(const char_t* format, ...) {
        ssize_t count = 0;
        va_list va;
        if ((format)) {
            va_start(va, format);
            count = infv(format, va);
            va_end(va);
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t outfv(const char_t* format, va_list va) {
        ssize_t count = outfv(this->out_std_out(), format, va);
        return count;
    }
    virtual ssize_t outlv(const char_t* out, va_list va) {
        ssize_t count = this->outlv(this->out_std_out(), out, va);
        return count;
    }
    virtual ssize_t outln(const char_t* out, ssize_t length = -1) {
        ssize_t count = this->outln(this->out_std_out(), out, length);
        return count;
    }
    virtual ssize_t outln() {
        ssize_t count = this->outln(this->out_std_out());
        return count;
    }
    virtual ssize_t out(const char_t* out, ssize_t length = -1) {
        ssize_t count = this->out(this->out_std_out(), out, length);
        return count;
    }
    virtual ssize_t out_flush() {
        ssize_t count = this->out_flush(this->out_std_out());
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t errfv(const char_t* format, va_list va) {
        ssize_t count = outfv(this->out_std_err(), format, va);
        return count;
    }
    virtual ssize_t errlv(const char_t* out, va_list va) {
        ssize_t count = this->outlv(this->out_std_err(), out, va);
        return count;
    }
    virtual ssize_t errln(const char_t* out, ssize_t length = -1) {
        ssize_t count = this->outln(this->out_std_err(), out, length);
        return count;
    }
    virtual ssize_t errln() {
        ssize_t count = this->outln(this->out_std_err());
        return count;
    }
    virtual ssize_t err(const char_t* out, ssize_t length = -1) {
        ssize_t count = this->out(this->out_std_err(), out, length);
        return count;
    }
    virtual ssize_t err_flush() {
        ssize_t count = this->out_flush(this->out_std_err());
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t infv(const char_t* format, va_list va) {
        ssize_t count = this->infv(this->in_std_in(), format, va);
        return count;
    }
    virtual ssize_t inln(char_t* in, size_t size) {
        ssize_t count = this->inln(this->in_std_in(), in, size);
        return count;
    }
    virtual ssize_t in(char_t* in, size_t size) {
        ssize_t count = this->in(this->in_std_in(), in, size);
        return count;
    }
    virtual ssize_t in_fill() {
        ssize_t count = this->in_fill(this->in_std_in());
        return count;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t outfv(file_t f, const char_t* format, va_list va) {
        ssize_t count = 0;
        if ((f != ((file_t)null_file)) && (format)) {
            /*count = vfprint(f, format, va);*/
        }
        return count;
    }
    virtual ssize_t outlv(file_t f, const char_t* out, va_list va) {
        ssize_t count = 0;
        ssize_t amount = 0;
        for (count = 0; out; count += amount) {
            if (0 > (amount = this->out(f, out))) {
                return amount;
            }
            out = va_arg(va, const char_t*);
        }
        return count;
    }
    virtual ssize_t outln(file_t f, const char_t* out, ssize_t length = -1) {
        ssize_t count = 0;
        ssize_t amount;
        if (0 <= (amount = this->out(f, out, length))) {
            count += amount;
            if (0 <= (amount = this->outln(f))) {
                count += amount;
            }
        }
        return count;
    }
    virtual ssize_t outln(file_t f) {
        const char_t ln = ((char_t)'\n');
        ssize_t count = out(f, &ln, 1);
        return count;
    }
    virtual ssize_t out(file_t f, const char_t* out, ssize_t length = -1) {
        ssize_t count = 0;
        if ((out) && (f != ((file_t)null_file))) {
            ssize_t amount = 0;
            if (0 <= (length)) {
                if (0 < (amount /*= fwrite(out, sizeof(char_t), length, f)*/))
                    count += amount;
            } else {
                for (; *out; ++out) {
                    if (0 < (amount /*= fwrite(out, sizeof(char_t), 1, f)*/)) {
                        count += amount;
                        continue;
                    }
                    break;
                }
            }
        }
        return count;
    }
    virtual ssize_t out_flush(file_t f) {
        ssize_t count = 0;
        if ((f != ((file_t)null_file))) {
            int err = 0;
            if ((err /*= fflush(f)*/)) {
                count = -1;
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t infv(file_t f, const char_t* format, va_list va) {
        ssize_t count = 0;
        if ((f != ((file_t)null_file)) && (format)) {
            /*count = vfscanf(f, format, va);*/
        }
        return count;
    }
    virtual ssize_t inln(file_t f, char_t* in, size_t size) {
        ssize_t count = 0;
        if ((in) && (f != ((file_t)null_file)) && (0 < (size))) {
            const char_t ln = ((char_t)'\n');
            char_t c;
            ssize_t amount;
            while (0 < (size)) {
                if (0 > (amount = this->in(f, &c, 1))) {
                    count = amount;
                } else {
                    --size;
                    if (ln != c) {
                        *in = c;
                        ++in;
                        continue;
                    }
                }
                break;
            }
        }
        return count;
    }
    virtual ssize_t in(file_t f, char_t* in, size_t size) {
        ssize_t count = 0;
        if ((in) && (f != ((file_t)null_file)) && (0 < (size))) {
            ssize_t amount = 0;
            if (0 < (amount /*= fread(in, sizeof(char_t), size, f)*/)) {
                count += amount;
            }
        }
        return count;
    }
    virtual ssize_t in_fill(file_t f) {
        ssize_t count = 0;
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual file_t out_std_out() {
        return this->std_out();
    }
    virtual file_t out_std_err() {
        return this->std_err();
    }
    virtual file_t in_std_in() {
        return this->std_in();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual file_t std_out() const {
        return ((file_t)null_file)/*stdout*/;
    }
    virtual file_t std_err() const {
        return ((file_t)null_file)/*stderr*/;
    }
    virtual file_t std_in() const {
        return ((file_t)null_file)/*stdin*/;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace console 
} // namespace nadir 

#endif // _NADIR_CONSOLE_IO_HPP 
