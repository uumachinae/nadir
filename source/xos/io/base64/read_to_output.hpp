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
///   File: read_to_output.hpp
///
/// Author: $author$
///   Date: 7/30/2022, 8/19/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_BASE64_READ_TO_OUTPUT_HPP
#define XOS_IO_BASE64_READ_TO_OUTPUT_HPP

#include "xos/io/base64/reader_to.hpp"
#include "xos/console/io.hpp"

namespace xos {
namespace io {
namespace base64 {

/// class read_to_outputt
template 
<class TOutput, 
 class TReader = xos::io::reader,
 class TReaderEvents = xos::io::base64::reader_to_eventst<TReader>, 
 class TExtends = extend, class TImplements = TReaderEvents>
class exported read_to_outputt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef read_to_outputt derives; 
    
    typedef TOutput output_t;
    typedef TReader reader_t;
    typedef TReaderEvents reader_events_t;
    typedef typename reader_events_t::what_t what_t;
    typedef typename reader_events_t::sized_t sized_t;

    /// constructors / destructor
    read_to_outputt(const read_to_outputt& copy): output_(copy.output_) {
    }
    read_to_outputt(output_t &output): output_(output) {
    }
    virtual ~read_to_outputt() {
    }

    /// on...
    virtual ssize_t on_begin(what_t* what, size_t size) {
        output_t &output = this->output();
        output.begin_out_base64_digits();
        return size;
    }
    virtual ssize_t on_end(what_t* what, size_t size) {
        output_t &output = this->output();
        output.end_out_base64_digits();
        return size;
    }
    virtual ssize_t on_end_base64_digit(uint8_t d, what_t* what, size_t size) {
        output_t &output = this->output();
        output.end_out_base64_digit(d);
        return size;
    }
    virtual ssize_t on_base64_digit(uint8_t d, what_t* what, size_t size) {
        output_t &output = this->output();
        output.out_base64_digit(d);
        return size;
    }

protected:
    /// output
    virtual output_t &output() const {
        return (output_t &)output_;
    }

protected:
    output_t &output_;
}; /// class read_to_outputt

} /// namespace base64
} /// namespace io
} /// namespace xos

#endif /// ndef XOS_IO_BASE64_READ_TO_OUTPUT_HPP
