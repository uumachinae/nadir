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
///   File: writer.hpp
///
/// Author: $author$
///   Date: 3/10/2020, 9/1/2021
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_WRITER_HPP
#define XOS_IO_WRITER_HPP

#include "xos/io/sequence.hpp"

namespace xos {
namespace io {

///  Class: writert
template <class TImplements = sequence>
class exported writert: virtual public TImplements {
public:
    typedef TImplements Implements, implements;

    typedef typename implements::what_t what_t;
    typedef typename implements::sized_t sized_t;
    typedef typename implements::endof_t endof_t;
    static const endof_t endof = implements::endof;

    /// write... / flush
    virtual ssize_t write(const what_t* what, size_t size) {
        ssize_t count = 0;
        return count;
    }    
    virtual ssize_t write(const what_t* what) {
        const sized_t* sized = 0;
        ssize_t count = 0;
        if ((sized = ((const sized_t*)what))) {
            ssize_t amount = 0;
            do {
                const sized_t& c = *sized;
                if (c != endof) {
                    if (0 < (amount = write(sized, 1))) {
                        count += amount;
                        ++sized;
                        continue;
                    } else {
                        if (0 > (amount)) {
                            count = amount;
                        }
                    }
                }
                break;
            } while (sized);
        }
        return count;
    }    
    virtual ssize_t writel(const what_t* what, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, what);
        count = writev(what, va);
        va_end(va);
        return count;
    }    
    virtual ssize_t writev(const what_t* what, va_list va) {
        typedef const sized_t* const_sized_pointer;
        ssize_t count = 0, amount = 0;
        for (count = 0; what; count += amount) {
            if (0 > (amount = write(what))) {
                return count;
            }
            what = va_arg(va, const_sized_pointer);
        }
        return count;
    }    
    virtual ssize_t flush() {
        ssize_t count = 0;
        return count;
    }    
}; /// class exported writert
typedef writert<sequence> writer;

typedef writert<byte_sequence> byte_writer;
typedef writert<word_sequence> word_writer;

///  Class: char_writert
template <class TSequence = char_sequence, class TImplements = writert<TSequence> >
class exported char_writert: virtual public TImplements {
public:
    typedef TImplements Implements, implements;

    typedef typename implements::what_t what_t;
    typedef typename implements::sized_t sized_t;
    typedef typename implements::endof_t endof_t;
    static const endof_t endof = implements::endof;

    /// writeln
    virtual ssize_t writeln(const what_t* out, size_t length) {
        ssize_t count = 0, amount = 0;
        if (0 <= (amount = this->write(out, length))) {
            count += amount;
            if (0 <= (amount = this->writeln())) {
                count += amount;
            }
        }
        return count;
    }
    virtual ssize_t writeln(const what_t* out) {
        ssize_t count = 0, amount = 0;
        if (0 <= (amount = this->write(out))) {
            count += amount;
            if (0 <= (amount = this->writeln())) {
                count += amount;
            }
        }
        return count;
    }
    virtual ssize_t writeln() {
        const char_t ln = ((char_t)'\n');
        ssize_t count = this->write(&ln, 1);
        return count;
    }

    /// writex...
    virtual ssize_t writexln(const void* out, size_t length, bool upper_case = false) {
        ssize_t count = 0, amount = 0;
        if (0 <= (amount = this->writex(out, length, upper_case))) {
            count += amount;
            if (0 <= (amount = this->writeln())) {
                count += amount;
            }
        }
        return count;
    }
    virtual ssize_t writex(const void* out, size_t length, bool upper_case = false) {
        ssize_t count = 0;
        const byte_t* bytes = 0;

        if ((bytes = (const byte_t*)(out)) && (length)) {
            ssize_t amount = 0;
            uint8_t b = 0;
            char_t x[2];

            for (; 0 < length; --length) {
                b = (*bytes++);
                x[0] = this->dtox(b >> 4, upper_case);
                x[1] = this->dtox(b & 15, upper_case);

                if (0 < (amount = this->write(x, 2))) {
                    count += amount;
                } else {
                    return amount;
                }
            }
        }
        return count;
    }

    /// write64...
    virtual ssize_t write64ln(const void* out, size_t length) {
        ssize_t count = 0, amount = 0;

        if (0 <= (amount = this->write64(out, length))) {
            count += amount;
            if (0 <= (amount = this->writeln())) {
                count += amount;
            }
        }
        return count;
    }
    virtual ssize_t write64(const void* out, size_t length) {
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
        if (0 > (amount = this->write((const what_t*)(&x), 1))) {
            return amount;
        }
        count += amount;
        carry = (b & (mask >> (8 - shift))) << (6 - shift);
        if (6 > (shift)) {
            shift += 2;
        } else {
            x = (sized_t)(this->dtob64(carry));
            if (0 > (amount = this->write((const what_t*)(&x), 1))) {
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
        if (0 > (amount = this->write((const what_t*)(&x), 1))) {
            return amount;
        }
        count += amount;
        for (x = ((sized_t)'='); shift != 2;) {
            if (0 > (amount = this->write((const what_t*)(&x), 1))) {
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
}; /// class exported char_writert

typedef char_writert<char_sequence> char_writer;
typedef char_writert<tchar_sequence> tchar_writer;
typedef char_writert<wchar_sequence> wchar_writer;

} /// namespace io
} /// namespace xos

#endif /// ndef XOS_IO_WRITER_HPP 
