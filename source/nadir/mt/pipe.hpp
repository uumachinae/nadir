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
///   File: pipe.hpp
///
/// Author: $author$
///   Date: 12/29/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_MT_PIPE_HPP
#define _NADIR_MT_PIPE_HPP

#include "nadir/io/stream.hpp"

namespace nadir {
namespace mt {

///////////////////////////////////////////////////////////////////////
///  Class: pipet
///////////////////////////////////////////////////////////////////////
template 
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0,
 class TReader = io::readert<TWhat, TSized, TEnd, VEnd>,
 class TWriter = io::writert<TWhat, TSized, TEnd, VEnd>,
 class TStream = io::streamt<TWhat, TSized, TEnd, VEnd, TReader, TWriter>,
 class TImplements = TStream>

class _EXPORT_CLASS pipet: virtual public TImplements {
public:
    typedef TImplements Implements;

    typedef typename Implements::what_t what_t;
    typedef typename Implements::sized_t sized_t;
    enum { end = Implements::end };
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef pipet<void, char> pipe;

typedef pipet<char, char> char_pipe;
typedef pipet<tchar_t, tchar_t> tchar_pipe;
typedef pipet<wchar_t, wchar_t> wchar_pipe;

typedef pipet<byte_t, byte_t> byte_pipe;
typedef pipet<word_t, word_t> word_pipe;
} // namespace mt 
} // namespace nadir 

#endif // _NADIR_MT_PIPE_HPP 

        

