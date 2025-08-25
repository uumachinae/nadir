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
///   File: read_to_arrays.hpp
///
/// Author: $author$
///   Date: 4/17/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_HEX_READ_TO_ARRAYS_HPP
#define XOS_IO_HEX_READ_TO_ARRAYS_HPP

#include "xos/io/hex/reader.hpp"
#include "xos/base/arrays.hpp"
#include "xos/base/array.hpp"
#include <stdarg.h>

namespace xos {
namespace io {
namespace hex {

/// class read_to_arrayst
template 
<class TArrays = xos::byte_arrays, class TArray = xos::byte_array,
 class TReaderEvents = reader_events, class TExtends = extend, class TImplements = TReaderEvents>

class exported read_to_arrayst: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements, implements;
    typedef TExtends Extends, extends;
    typedef read_to_arrayst Derives, derives; 
    
    typedef TArrays arrays_t;
    typedef typename arrays_t::what_t array_pointer_t;
    typedef TArray array_t;
    typedef typename array_t::what_t element_t;
    typedef TReaderEvents reader_events_t;
    typedef typename reader_events_t::what_t what_t;
    typedef typename reader_events_t::sized_t sized_t;

    /// constructors / destructor
    read_to_arrayst(array_pointer_t array_pointer, ...)
    : array_index_(0), array_pointer_(0), byte_(0), nibble_(0), arrays_(this_arrays_) {
        va_list va;
        va_start(va, array_pointer);
        construct(array_pointer, va);
        va_end(va);
    }
    read_to_arrayst(arrays_t& arrays)
    : array_index_(0), array_pointer_(0), byte_(0), nibble_(0), arrays_(arrays) {
        construct(arrays);
    }
    read_to_arrayst(const read_to_arrayst& copy)
    : array_index_(0), array_pointer_(0), byte_(0), nibble_(0), arrays_(this_arrays_) {
        throw xos::exception(exception_unexpected);
        construct(copy);
    }
    read_to_arrayst()
    : array_index_(0), array_pointer_(0), byte_(0), nibble_(0), arrays_(this_arrays_) {
        construct();
    }
    virtual ~read_to_arrayst() {
    }

private:
    void construct(const read_to_arrayst& copy) {
    }
    void construct(array_pointer_t array_pointer, va_list va) {
        for (size_t index = 0, count = 0; array_pointer; ++count) {
            this_arrays_.append(&array_pointer, 1);
            array_pointer = va_arg(va, array_pointer_t);
        }
    }
    void construct(arrays_t& arrays) {
    }
    void construct() {
    }
    void destruct() {
        this_arrays_.clear();
    }
public:

    /// on_...
    virtual ssize_t on_begin(what_t* what, size_t size) {
        size_t index = 0, length = 0;
        if ((((index = array_index_) + 1) <= (length = arrays_.length()))) {
            if ((array_pointer_ = arrays_[array_index_++])) {
                array_pointer_->set_length(0);
            }
        } else {
            if ((&arrays_ != &this_arrays_)) {
                array_pointer_t array_pointer = 0;
                if ((array_pointer = arrays_.new_instance())) {
                    arrays_.append(&array_pointer, 1);
                    if ((array_pointer_ = arrays_[array_index_++])) {
                        array_pointer_->set_length(0);
                    }
                }
            }
        }
        byte_ = nibble_ = 0;
        return size;
    }
    virtual ssize_t on_end(what_t* what, size_t size) {
        return size;
    }
    virtual ssize_t on_hex_digit(unsigned d, what_t* what, size_t size) {
        byte_t n = ((byte_t)(d & 15)); 
        byte_ = ((byte_ << 4) | n);
        if ((nibble_++)) {
            if ((array_pointer_)) {
                element_t e = ((element_t)byte_);
                array_pointer_->append(&e, 1);
            }
            byte_ = nibble_ = 0;
         }
        return size;
    }

    /// arrays
    virtual arrays_t &arrays() const {
        return (arrays_t &)arrays_;
    }

protected:
    size_t array_index_;
    array_pointer_t array_pointer_;
    byte_t byte_, nibble_;
    arrays_t this_arrays_, &arrays_;
}; /// class read_to_arrayst
typedef read_to_arrayst<> read_to_arrays;

typedef read_to_arrayst<xos::byte_arrays, xos::byte_array> read_to_byte_arrays;

} /// namespace hex
} /// namespace io
} /// namespace xos

#endif /// XOS_IO_HEX_READ_TO_ARRAYS_HPP
