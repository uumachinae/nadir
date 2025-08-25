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
///   File: writer_events.hpp
///
/// Author: $author$
///   Date: 8/3/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_DELEGATED_WRITER_EVENTS_HPP
#define XOS_IO_DELEGATED_WRITER_EVENTS_HPP

#include "xos/io/writer.hpp"

namespace xos {
namespace io {
namespace delegated {

/// class writer_eventst
template <class TWriter, class TImplements = implement>
class exported writer_eventst: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef writer_eventst derives; 
    
    typedef TWriter writer_t;
    typedef typename writer_t::what_t what_t;
    typedef typename writer_t::sized_t sized_t;
    
    /// constructors / destructor
    virtual ~writer_eventst() {
    }

    /// on_write / on_flush
    virtual ssize_t on_write(const what_t* what, size_t size) {
        return size;
    }
    virtual ssize_t on_flush(size_t size) {
        return size;
    }

}; /// class writer_eventst

} /// namespace delegated
} /// namespace io
} /// namespace xos

#endif /// ndef XOS_IO_DELEGATED_WRITER_EVENTS_HPP
