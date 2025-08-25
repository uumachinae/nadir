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
///   Date: 3/10/2020, 8/12/2024
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_READER_HPP
#define XOS_IO_READER_HPP

#include "xos/io/seeker.hpp"
#include "xos/base/logger.hpp"

namespace xos {
namespace io {

///  Class: readert
template <class TImplements = sequence>
class exported readert: virtual public TImplements {
public:
    typedef TImplements Implements, implements;

    typedef typename implements::what_t what_t;
    typedef typename implements::sized_t sized_t;
    typedef typename implements::endof_t endof_t;
    static const endof_t endof = implements::endof;

    /// read / fill
    virtual ssize_t read(what_t* what, size_t size) {
        ssize_t count = 0;
        return count;
    }    
    virtual ssize_t fill() {
        ssize_t count = 0;
        return count;
    }    
    virtual ssize_t sized_read(sized_t& sized) {
        ssize_t count = 0;
        return count;
    }    
}; /// class exported readert
typedef readert<seeker> reader;

typedef readert<byte_seeker> byte_reader;
typedef readert<word_seeker> word_reader;

///  Class: char_readert
template <class TSeeker = char_seeker, class TImplements = readert<TSeeker> >
class exported char_readert: virtual public TImplements {
public:
    typedef TImplements Implements, implements;

    typedef typename implements::what_t what_t;
    typedef typename implements::sized_t sized_t;
    typedef typename implements::endof_t endof_t;
    static const endof_t endof = implements::endof;

    /// 
    /// readx / getx
    /// ...
    virtual ssize_t readx(void* in, size_t size) {
        ssize_t count = 0;
        uint8_t* byte = 0;

        if ((byte = (uint8_t*)(in)) && (0 < size)) {
            ssize_t amount = 0;
            
            for (; 0 < size; --size, ++byte) {
                if (0 < (amount = getx(*byte))) {
                    ++count;
                } else {
                    if (0 > amount) {
                        count = amount;
                        break;
                    }
                }
            }
        }
        return count;
    }
    virtual ssize_t getx(uint8_t& byte) {
        ssize_t count = 0, amount = 0;
        sized_t x = (sized_t)(0);
        uint8_t n = 0;
        int8_t d = 0;

        for (byte = 0, n = 0; n < 2; ++n) {
            if (0 < (amount = this->read(&x, 1))) {
                if (0 <= (d = this->xtod(x))) {
                    byte = ((byte << 4) | (((uint8_t)d) & 15));
                    count += n;
                } else {
                    count = d;
                    break;
                }
            } else {
                count = amount;
                break;
            }
        }
        return count;
    }
    /// ...
    /// readx / getx
    /// 

    ///
    ///  read64 / get64
    /// ...
    virtual ssize_t read64(void* in, size_t size) {
        ssize_t count = 0;
        uint8_t* bytes = 0;

        if ((bytes = (uint8_t*)(in)) && (0 < size)) {
            ssize_t amount = 0;
            sized_t sized = 0;            
            uint8_t carry = 0, shift = 0;

            for (carry = 0, shift = 2; 0 < size; ) {
                if (0 < (amount = this->get64(bytes, carry, shift, sized))) {
                    LOGGER_LOG_DEBUG("...(0 < (amount(" << signed_to_string(amount) << ") = this->get64(bytes, carry(" << signed_to_string(carry) << "), shift(" << signed_to_string(shift) << "), sized(" << char_to_string(sized) << "))))");
                }
                if (0 > (amount)) {
                    LOGGER_LOG_DEBUG("...(0 > (amount(" << signed_to_string(amount) << ")))");
                    return amount;
                } else {
                    if (0 < (amount)) {
                        LOGGER_LOG_DEBUG("...(0 < (amount(" << signed_to_string(amount) << ")))");
                        size -= amount;
                        bytes += amount;
                        count += amount;
                        LOGGER_LOG_DEBUG("...count(" << signed_to_string(count) << ") += amount(" << signed_to_string(amount) << ")");
                    } else {
                        LOGGER_LOG_DEBUG("...(0 == (amount(" << signed_to_string(amount) << ")))");
                        if (!(this->is_end_b64tod(sized))) {
                            break;
                        } else {
                            LOGGER_LOG_DEBUG("...is_end_b64tod(" << char_to_string(sized) << ")");
                        }
                    }
                }
            }
        }
        return count;
    }
    virtual ssize_t get64(uint8_t b[], uint8_t& carry, uint8_t& shift, sized_t& sized) {
        ssize_t count = 0, amount = 0, ncount = 0;
        int8_t d = 0;
        uint8_t n = 0;

        if (!(this->is_end_b64tod(sized))) {
            if (2 == (shift)) {
                LOGGER_LOG_DEBUG("...(2 == (shift(" << signed_to_string(shift) << ")))");
                for (n = 0; n < 2;) {
                    if (0 < (amount = this->read(&sized, 1))) {
                        LOGGER_LOG_DEBUG("...(0 < (amount(" << signed_to_string(amount) << ")) = this->read(&sized(" << char_to_string(sized) << "), 1)))");
                    }
                    if (0 >= (amount)) {
                        if (0 > (amount)) {
                            return amount;
                        } else {
                            shift = 2;
                            if (n < 1) {
                                carry = 0;
                                return 0;
                            } else {
                                b[0] = carry;
                                LOGGER_LOG_DEBUG("...b[0](" << char_to_string(b[0]) << ") = carry(" << signed_to_string(carry) << ")");
                                carry = 0;
                                return 1;
                            }
                        }
                    } else {
                        if (0 <= (d = this->b64tod(sized))) {
                            if (n < 1) {
                                carry = (((uint8_t)d) << 2);
                            } else {
                                b[0] = (carry | (((uint8_t)d) >> 4));
                                LOGGER_LOG_DEBUG("...b[0](" << char_to_string(b[0]) << ") = (carry(" << signed_to_string(carry) << ") | (((uint8_t)d(" << char_to_string(d) << ")) >> 4))");
                                carry = ((((uint8_t)d) & 0xF) << 4);
                                shift += 2;
                                count = 1;
                            }
                            ++n;
                            ++ncount;
                        }
                    }
                }
            } else {
                if (4 == (shift)) {
                    LOGGER_LOG_DEBUG("...(4 == (shift(" << signed_to_string(shift) << ")))");
                    for (n = 0; n < 2;) {
                        if (0 < (amount = this->read(&sized, 1))) {
                            LOGGER_LOG_DEBUG("...(0 < (amount(" << signed_to_string(amount) << ")) = this->read(&sized(" << char_to_string(sized) << "), 1)))");
                        }
                        if (0 >= (amount)) {
                            if (0 > amount) {
                                return amount;
                            } else {
                                b[n] = carry;
                                LOGGER_LOG_DEBUG("...b[n](" << char_to_string(b[n]) << ") = carry(" << signed_to_string(carry) << ")");
                                carry = 0;
                                shift = 2;
                                return 1;
                            }
                        } else {
                            if (0 <= (d = this->b64tod(sized))) {
                                b[n] = (carry | (((uint8_t)d) >> (6 - shift)));
                                LOGGER_LOG_DEBUG("...b[n](" << char_to_string(b[n]) << ") = (carry(" << signed_to_string(carry) << ") | (((uint8_t)d(" << char_to_string(d) << ")) >> (6 - shift(" << signed_to_string(shift) << ")))");
                                if (n < 1) {
                                    carry = ((((uint8_t)d) & 0x3) << 6);
                                    shift += 2;
                                } else {
                                    carry = 0;
                                    shift = 2;
                                    count = 2;
                                }
                                ++n;
                                ++ncount;
                            } else {
                                LOGGER_LOG_DEBUG("...(0 > (d(" << signed_to_string(d) << ") = this->b64tod(sized(" << char_to_string(sized) << "))))");
                                return ncount;
                            }
                        }
                    }
                } else {
                    LOGGER_LOG_ERROR("...unecpected invalid_shift(" << unsigned_to_string(shift).chars() << ")");
                }
            }
        } else {
            if (0 < (amount = this->read(&sized, 1))) {
                LOGGER_LOG_DEBUG("...(0 < (amount(" << signed_to_string(amount) << ")) = this->read(&sized(" << char_to_string(sized) << "), 1)))");
            }
            if (0 > (amount)) {
                return amount;
            } else {
                if (0 == amount) {
                    sized = 0;
                }
            }
        }
        return count;
    }
    /// ...
    ///  read64 / get64
    /// 

}; /// class exported char_readert

typedef char_readert<char_seeker> char_reader;
typedef char_readert<tchar_seeker> tchar_reader;
typedef char_readert<wchar_seeker> wchar_reader;

} /// namespace io
} /// namespace xos

#endif /// ndef XOS_IO_READER_HPP 
