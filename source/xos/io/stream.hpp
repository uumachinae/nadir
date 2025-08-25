///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2021 $organization$
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
///   File: stream.hpp
///
/// Author: $author$
///   Date: 7/16/2021, 9/1/2021
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_STREAM_HPP
#define XOS_IO_STREAM_HPP

#include "xos/io/reader.hpp"
#include "xos/io/writer.hpp"

namespace xos {
namespace io {

/// class streamt
template <class TImplements = writert<readert<seekert<sequencet<> > > > >
class exported streamt: virtual public TImplements {
public:
    typedef TImplements Implements, implements;
    typedef streamt Derives, derives; 
    
    /// constructors / destructor
    virtual ~streamt() {
    }
}; /// class streamt
typedef streamt<> stream;

typedef streamt<char_writert<char_readert<seekert<char_sequence> > > > char_stream;
typedef streamt<char_writert<char_readert<seekert<tchar_sequence> > > > tchar_stream;
typedef streamt<char_writert<char_readert<seekert<wchar_sequence> > > > wchar_stream;

typedef streamt<writert<readert<seekert<byte_sequence> > > > byte_stream;
typedef streamt<writert<readert<seekert<word_sequence> > > > word_stream;

} /// namespace io
} /// namespace xos

#endif /// XOS_IO_STREAM_HPP
