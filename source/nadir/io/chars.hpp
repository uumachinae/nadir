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
///   File: chars.hpp
///
/// Author: $author$
///   Date: 1/15/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_IO_CHARS_HPP
#define _NADIR_IO_CHARS_HPP

#include "nadir/io/reader.hpp"
#include "nadir/base/attached.hpp"
#include "nadir/base/chars.hpp"

namespace nadir {
namespace io {
namespace chars {

///////////////////////////////////////////////////////////////////////
///  Class: readert
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0,
 class TChars = charst<TSized, TEnd, VEnd>,
 class TReader = io::readert<TWhat, TSized, TEnd, VEnd>,
 class TAttacher = attachert<const TSized*, int, 0, TReader>,
 class TAttached = attachedt<const TSized*, int, 0, TAttacher>,
 class TImplements = TAttacher, class TExtends = TAttached>

class _EXPORT_CLASS readert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TChars chars_t;
    typedef TWhat what_t;
    typedef TSized sized_t;
    typedef TEnd end_t;
    enum { end = VEnd };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    readert(const sized_t* detached, size_t length)
    : Extends(detached), length_(length), tell_(0) {
    }
    virtual ~readert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t read(what_t* what, size_t size) {
        sized_t* to = 0;
        const sized_t* from = 0;

        if ((to = ((sized_t*)what)) && (size) && (from = this->attached_to())) {
            if (length_ < (tell_ + size)) {
                size = length_ - tell_;
            }
            if (size) {
                chars_t::copy(to, from + tell_, size);
                tell_ += size;
                return size;
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t seek(ssize_t offset, int whence) {
        return -1;
    }
    virtual ssize_t tell() {
        return tell_;
    }
    virtual ssize_t eof() {
        return -1;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    size_t length_, tell_;
};
typedef readert<void, char> reader;

} // namespace chars
} // namespace io 
} // namespace nadir 

#endif // _NADIR_IO_CHARS_HPP 
