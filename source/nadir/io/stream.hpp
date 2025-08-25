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
///   File: stream.hpp
///
/// Author: $author$
///   Date: 1/13/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_IO_STREAM_HPP
#define _NADIR_IO_STREAM_HPP

#include "nadir/io/reader.hpp"
#include "nadir/io/writer.hpp"

namespace nadir {
namespace io {

///////////////////////////////////////////////////////////////////////
///  Class: streamt
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0,
 class TReader = readert<TWhat, TSized, TEnd, VEnd>,
 class TWriter = writert<TWhat, TSized, TEnd, VEnd>,
 class TReaderImplements = TReader, class TWriterImplements = TWriter>

class _EXPORT_CLASS streamt
: virtual public TReaderImplements, virtual public TWriterImplements {
public:
    typedef TReaderImplements ReaderImplements;
    typedef TWriterImplements WriterImplements;

    typedef typename ReaderImplements::what_t what_t;
    typedef typename ReaderImplements::sized_t sized_t;
    typedef typename ReaderImplements::end_t end_t;
    enum { end = ReaderImplements::end };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef streamt<void, char, int, 0> stream;

typedef streamt<char, char, int, 0> char_stream;
typedef streamt<tchar_t, tchar_t, int, 0> tchar_stream;
typedef streamt<wchar_t, wchar_t, int, 0> wchar_stream;

typedef streamt<byte_t, byte_t, int, 0> byte_stream;
typedef streamt<word_t, word_t, int, 0> word_stream;
} // namespace io
} // namespace nadir 

#endif // _NADIR_IO_STREAM_HPP 
