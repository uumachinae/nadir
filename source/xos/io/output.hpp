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
///   File: output.hpp
///
/// Author: $author$
///   Date: 3/3/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_OUTPUT_HPP
#define XOS_IO_OUTPUT_HPP

#include "xos/base/to_string.hpp"
#include "xos/base/locked.hpp"
#include <stdarg.h>

namespace xos {
namespace io {

/// class outputt
template 
<typename TChar = char, typename TEndChar = TChar, TEndChar VEndChar = 0,
 class TLocked = locked, class TImplements = TLocked>

class exported outputt: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef outputt derives; 
    
    typedef stringt<TChar> string_t;
    typedef TChar char_t;
    typedef TEndChar end_char_t;
    enum { end_char = VEndChar };

    typedef char_t what_t;
    typedef char_t sized_t;

    /// constructors / destructor
    virtual ~outputt() {
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
        ssize_t count = 0, amount = 0;
        if (0 <= (count = errlv(what, va))) {
            if (0 <= (amount = errln())) {
                count += amount;
            } else {
                count = amount;
            }
        }
        return count;
    }
    virtual ssize_t errlv(const what_t *what, va_list va) {
        typedef const char *what_t;
        ssize_t count = 0, amount = 0;
        for (count = 0; what; count += amount) {
            if (0 > (amount = err(what))) {
                return amount;
            }
            what = va_arg(va, what_t);
        }
        return count;
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
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t errln(const what_t *what, size_t length) {
        ssize_t count = 0;
        if (0 <= (count = err(what, length))) {
            ssize_t amount = 0;
            if (0 <= (amount = errln())) {
                count += amount;
            } else {
                count = amount;
            }
        }
        return count;
    }
    virtual ssize_t errln(const what_t *what) {
        ssize_t count = 0;
        if (0 <= (count = err(what))) {
            ssize_t amount = 0;
            if (0 <= (amount = errln())) {
                count += amount;
            } else {
                count = amount;
            }
        }
        return count;
    }
    virtual ssize_t err(const what_t *what, size_t length) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t err(const what_t *what) {
        ssize_t count = 0, amount = 0;
        for (char_t c = *(what); c; c = *(++what), count += amount) {
            if (0 >= (amount = err(&c, 1))) {
                return amount;
            }
        }
        return count;
    }
    virtual ssize_t errln() {
        ssize_t count = 0;
        count = errlf();
        return count;
    }
    virtual ssize_t errcrlf() {
        ssize_t count = 0;
        if (0 < (count = errcr())) {
            ssize_t amount = 0;
            if (0 < (amount = errlf())) {
                count += amount;
            } else {
                return amount;
            }
        }
        return count;
    }
    virtual ssize_t errcr() {
        const char_t& cr = this->cr();
        ssize_t count = 0;
        count = err(&cr, 1);
        return count;
    }
    virtual ssize_t errlf() {
        const char_t& lf = this->lf();
        ssize_t count = 0;
        count = err(&lf, 1);
        return count;
    }
    virtual ssize_t err_flush() {
        ssize_t count = 0;
        return count;
    }

    /// out...
    virtual ssize_t outln(const string_t& chars) {
        ssize_t count = outln(chars.chars(), chars.length());
        return count;
    }
    virtual ssize_t out(const string_t& chars) {
        ssize_t count = out(chars.chars(), chars.length());
        return count;
    }
    virtual ssize_t outlln(const what_t *what, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, what);
        count = this->outllnv(what, va);
        va_end(va);
        return count;
    }
    virtual ssize_t outl(const what_t *what, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, what);
        count = this->outlv(what, va);
        va_end(va);
        return count;
    }
    virtual ssize_t outllnv(const what_t *what, va_list va) {
        ssize_t count = 0, amount = 0;
        if (0 <= (count = outlv(what, va))) {
            if (0 <= (amount = outln())) {
                count += amount;
            } else {
                count = amount;
            }
        }
        return count;
    }
    virtual ssize_t outlv(const what_t *what, va_list va) {
        typedef const char *what_t;
        ssize_t count = 0, amount = 0;
        for (count = 0; what; count += amount) {
            if (0 > (amount = out(what))) {
                return amount;
            }
            what = va_arg(va, what_t);
        }
        return count;
    }
    virtual ssize_t outsf(char_t *string, size_t size, const sized_t *format, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, format);
        count = this->outsfv(string, size, format, va);
        va_end(va);
        return count;
    }
    virtual ssize_t outsfv(char_t *string, size_t size, const sized_t *format, va_list va) {
        return 0;
    }
    virtual ssize_t outf(const sized_t *format, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, format);
        count = this->outfv(format, va);
        va_end(va);
        return count;
    }
    virtual ssize_t outfv(const sized_t *format, va_list va) {
        return 0;
    }
    virtual ssize_t outln(const what_t *what, size_t length) {
        ssize_t count = 0;
        if (0 <= (count = out(what, length))) {
            ssize_t amount = 0;
            if (0 <= (amount = outln())) {
                count += amount;
            } else {
                count = amount;
            }
        }
        return count;
    }
    virtual ssize_t outln(const what_t *what) {
        ssize_t count = 0;
        if (0 <= (count = out(what))) {
            ssize_t amount = 0;
            if (0 <= (amount = outln())) {
                count += amount;
            } else {
                count = amount;
            }
        }
        return count;
    }
    virtual ssize_t out(const what_t *what, size_t length) {
        return 0;
    }
    virtual ssize_t out(const what_t *what) {
        ssize_t count = 0, amount = 0;
        for (char_t c = *(what); c; c = *(++what), count += amount) {
            if (0 >= (amount = out(&c, 1))) {
                return amount;
            }
        }
        return count;
    }
    virtual ssize_t outln() {
        ssize_t count = 0;
        count = outlf();
        return count;
    }
    virtual ssize_t outcrlf() {
        ssize_t count = 0;
        if (0 < (count = outcr())) {
            ssize_t amount = 0;
            if (0 < (amount = outlf())) {
                count += amount;
            } else {
                return amount;
            }
        }
        return count;
    }
    virtual ssize_t outcr() {
        const char_t& cr = this->cr();
        ssize_t count = 0;
        count = out(&cr, 1);
        return count;
    }
    virtual ssize_t outlf() {
        const char_t& lf = this->lf();
        ssize_t count = 0;
        count = out(&lf, 1);
        return count;
    }
    virtual ssize_t out_flush() {
        return 0;
    }

    /// cr / lf
    virtual const char_t& cr() const {
        static const char_t cr = (char_t)'\r';
        return cr;
    }
    virtual const char_t& lf() const {
        static const char_t lf = (char_t)'\n';
        return lf;
    }

    /// outx...
    virtual ssize_t outxln(const void* out, size_t length, bool upper_case = false) {
        ssize_t count = 0, amount = 0;
        if (0 <= (amount = this->outx(out, length, upper_case))) {
            count += amount;
            if (0 <= (amount = this->outln())) {
                count += amount;
            }
        }
        return count;
    }
    virtual ssize_t outx(const void* out, size_t length, bool upper_case = false) {
        ssize_t count = 0; const uint8_t* bytes = 0;

        if ((bytes = (const uint8_t*)(out)) && (length)) {
            ssize_t amount = 0; uint8_t b = 0; char_t x[2];

            for (; 0 < length; --length) {
                b = (*bytes++);
                x[0] = dtox(b >> 4, upper_case);
                x[1] = dtox(b & 15, upper_case);

                if (0 < (amount = this->out(x, 2))) {
                    count += amount;
                } else {
                    return amount;
                }
            }
        }
        return count;
    }
    /// dtox / xtod
    virtual char_t dtox(uint8_t d, bool upper_case = false) const {
        char a = (upper_case)?('A'):('a'); char_t x = (char_t)(0);
        if ((0 <= d) && (9 >= d)) {
            x = (char_t)(('0') +  d);
        } else {
            if ((10 <= d) && (15 >= d)) {
                x = (char_t)((a) + (d - 10));
            } else {
                x = invalid_dtox(d);
            }
        }
        return x;
    }
    virtual char_t invalid_dtox(uint8_t d) const {
        return (char_t)(0);
    }

    /// out64...
    virtual ssize_t out64ln(const void* out, size_t length) {
        ssize_t count = 0, amount = 0;

        if (0 <= (amount = this->out64(out, length))) {
            count += amount;
            if (0 <= (amount = this->outln())) {
                count += amount;
            }
        }
        return count;
    }
    virtual ssize_t out64(const void* out, size_t length) {
        ssize_t count = 0;
        const uint8_t* byte = 0;

        if ((byte = (const uint8_t*)(out)) && (length)) {
            ssize_t amount = 0;
            uint8_t b = 0, carry = 0, shift = 0;
            if (0 <= length) {
                for (carry = 0, shift = 2; 0 < length; --length, ++byte) {
                    b = (*byte);
                    if (0 > (amount = this->put64(b, carry, shift))) {
                        return amount;
                    }
                    count += amount;
                }
            } else {
                for (carry = 0, shift = 2; (b = (*byte)); ++byte) {
                    if (0 > (amount = this->put64(b, carry, shift))) {
                        return amount;
                    }
                    count += amount;
                }
            }
            if ((2 != (shift))) {
                if (0 > (amount = this->put64_end(carry, shift))) {
                    return amount;
                }
                count += amount;
            }
        }
        return count;
    }
    virtual ssize_t put64(uint8_t b, uint8_t& carry, uint8_t& shift) {
        const uint8_t mask = ((uint8_t)-1);
        ssize_t count = 0, amount = 0;
        sized_t x = (sized_t)(0);
        x = (sized_t)(this->dtob64(carry | (b >> shift)));
        if (0 > (amount = this->out((const what_t*)(&x), 1))) {
            return amount;
        }
        count += amount;
        carry = (b & (mask >> (8 - shift))) << (6 - shift);
        if (6 > (shift)) {
            shift += 2;
        } else {
            x = (sized_t)(this->dtob64(carry));
            if (0 > (amount = this->out((const what_t*)(&x), 1))) {
                return amount;
            }
            count += amount;
            carry = 0;
            shift = 2;
        }
        return count;
    }
    virtual ssize_t put64_end(uint8_t& carry, uint8_t& shift) {
        ssize_t count = 0, amount = 0;
        sized_t x = (sized_t)(0);
        x = (sized_t)(this->dtob64(carry));
        if (0 > (amount = this->out((const what_t*)(&x), 1))) {
            return amount;
        }
        count += amount;
        for (x = ((sized_t)'='); shift != 2;) {
            if (0 > (amount = this->out((const what_t*)(&x), 1))) {
                return amount;
            }
            count += amount;
            if (6 > (shift)) {
                shift += 2;
            } else {
                shift = 2;
            }
        }
        return count;
    }
    virtual char_t dtob64(uint8_t d) const {
        char_t x = (char_t)(0);
        if ((0 <= d) && (25 >= d)) {
            x = (char_t)(('A') + d);
        } else {
            if ((26 <= d) && (51 >= d)) {
                x = (char_t)(('a') + (d - 26));
            } else {
                if ((52 <= d) && (61 >= d)) {
                    x = (char_t)(('0') + (d - 52));
                } else {
                    if ((62 == d)) {
                        x = (char_t)(('+'));
                    } else {
                        if ((63 == d)) {
                            x = (char_t)(('/'));
                        } else {
                            x = invalid_dtob64(d);
                        }
                    }
                }
            }
        }
        return x;
    }
    virtual char_t invalid_dtob64(uint8_t d) const {
        return (char_t)(0);
    }

}; /// class outputt
typedef outputt<> output;

namespace extended {
/// class outputt
template 
<class TOutput = output, class TExtends = extend, class TImplements = TOutput>

class exported outputt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef outputt derives; 
    
    typedef TOutput output_t;
    typedef typename implements::string_t string_t;
    typedef typename implements::char_t char_t;
    typedef typename implements::end_char_t end_char_t;
    enum { end_char = implements::end_char };

    typedef char_t what_t;
    typedef char_t sized_t;

    /// constructors / destructor
    outputt(const outputt& copy): verbose_output_(copy.verbose_output_) {
    }
    outputt(): verbose_output_(false) {
    }
    virtual ~outputt() {
    }

    /// out...
    virtual ssize_t outsfv(char_t *string, size_t size, const sized_t *format, va_list va) {
        return 0;
    }
    virtual ssize_t outfv(const sized_t *format, va_list va) {
        return 0;
    }
    using implements::out;
    virtual ssize_t out(const what_t *what, size_t length) {
        return 0;
    }

    /// ...verbose_output
    virtual bool& set_verbose_output(const bool& to) {
        verbose_output_ = to;
        return (bool&)verbose_output_;
    }
    virtual bool& verbose_output() const {
        return (bool&)verbose_output_;
    }

protected:
    bool verbose_output_;
}; /// class outputt
typedef outputt<> output;
} /// namespace extended

namespace forwarded {
/// class outputt
template 
<class TExtendsOutput = io::extended::output, class TOutputTo = io::output, 
 class TExtends = TExtendsOutput, class TImplements = typename TExtends::implements>

class exported outputt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef outputt derives; 
    
    typedef TOutputTo output_to_t;
    typedef typename implements::string_t string_t;
    typedef typename implements::char_t char_t;
    typedef typename implements::end_char_t end_char_t;
    enum { end_char = implements::end_char };

    typedef char_t what_t;
    typedef char_t sized_t;

    /// constructors / destructor
    outputt(const outputt& copy): output_to_(0) {
    }
    outputt(output_to_t* output_to): output_to_(output_to) {
    }
    outputt(): output_to_(0) {
    }
    virtual ~outputt() {
    }

    /// out...
    virtual ssize_t outsfv(char_t *string, size_t size, const sized_t *format, va_list va) {
        ssize_t count = 0;
        output_to_t* output_to = 0;
        if ((output_to = this->output_to())) {
            count = output_to->outsfv(string, size, format, va);
        } else {
            count = extends::outsfv(string, size, format, va);
        }
        return count;
    }
    virtual ssize_t outfv(const sized_t *format, va_list va) {
        ssize_t count = 0;
        output_to_t* output_to = 0;
        if ((output_to = this->output_to())) {
            count = output_to->outfv(format, va);
        } else {
            count = extends::outfv(format, va);
        }
        return count;
    }
    using implements::out;
    virtual ssize_t out(const what_t *what, size_t length) {
        ssize_t count = 0;
        output_to_t* output_to = 0;
        if ((output_to = this->output_to())) {
            count = output_to->out(what, length);
        } else {
            count = extends::out(what, length);
        }
        return count;
    }
    virtual ssize_t out_flush() {
        ssize_t count = 0;
        output_to_t* output_to = 0;
        if ((output_to = this->output_to())) {
            count = output_to->out_flush();
        } else {
            count = extends::out_flush();
        }
        return count;
    }

    /// ...output_to
    virtual output_to_t* set_output_to(output_to_t* to) {
        output_to_t *&output_to = this->output_to(), *old_output_to = output_to;
        output_to = to;
        return old_output_to;
    }
    virtual output_to_t* unset_output_to() {
        output_to_t *&output_to = this->output_to(), *old_output_to = output_to;
        output_to = 0;
        return old_output_to;
    }
protected:
    virtual output_to_t*& output_to() const {
        return (output_to_t*&)output_to_;
    }

protected:
    output_to_t* output_to_;
}; /// class outputt
typedef outputt<> output;
} /// namespace forwarded

} /// namespace io
} /// namespace xos

#endif /// XOS_IO_OUTPUT_HPP
