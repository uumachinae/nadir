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
///   File: writer.hpp
///
/// Author: $author$
///   Date: 8/3/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_DELEGATED_WRITER_HPP
#define XOS_IO_DELEGATED_WRITER_HPP

#include "xos/io/delegated/writer_events.hpp"

namespace xos {
namespace io {
namespace delegated {

/// class writert
template 
<class TWriter = io::writer, class TWriterEvents = writer_eventst<TWriter>, 
 class TExtends = extend, class TImplements = TWriter>

class exported writert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef writert derives; 
    
    typedef TWriterEvents writer_events_t;
    typedef TWriter writer_t;
    typedef typename writer_t::what_t what_t;
    typedef typename writer_t::sized_t sized_t;
    
    /// constructors / destructor
    writert(writer_events_t& writer_events, writer_t& writer): writer_(writer), writer_events_(writer_events) {
    }
    writert(const writert& copy): writer_(copy.writer_), writer_events_(copy.writer_events_) {
    }
    writert(writer_t& writer): writer_(writer), writer_events_(*this) {
    }
    virtual ~writert() {
    }

    /// write / flush
    using implements::write;
    virtual ssize_t write(const what_t* what, size_t size) {
        ssize_t count = 0;
        if (0 < (count = writer_.write(what, size))) {
            count = this->on_write(what, (size_t)count);
        }
        return count;
    }
    virtual ssize_t flush() {
        ssize_t count = 0;
        if (0 <= (count = writer_.flush())) {
            count = this->on_flush((size_t)count);
        }
        return count;
    }

protected:
    /// on_write / on_flush
    virtual ssize_t on_write(what_t* what, size_t size) {
        if (&writer_events_ != this) {
            return writer_events_.on_write(what, size);
        }
        return size;
    }
    virtual ssize_t on_flush(size_t size) {
        if (&writer_events_ != this) {
            return writer_events_.on_flush(size);
        }
        return size;
    }

protected:
    writer_t& writer_;
    writer_events_t& writer_events_;
}; /// class writert
typedef writert<> writer;

} /// namespace delegated
} /// namespace io
} /// namespace xos

#endif /// ndef XOS_IO_DELEGATED_WRITER_HPP
