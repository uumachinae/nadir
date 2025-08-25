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
///   File: told.hpp
///
/// Author: $author$
///   Date: 4/17/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_TOLD_HPP
#define XOS_IO_TOLD_HPP

#include "xos/io/seeker.hpp"

namespace xos {
namespace io {

/// enum from
enum {
    from_begin = from_begining,
    from_endof = from_end
}; /// enum from

/// class toldt
template <class TSeeker = xos::io::seeker, class TExtends = extend, class TImplements = TSeeker>
class exported toldt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements, implements;
    typedef TExtends Extends, extends;
    typedef toldt Derives, derives; 
    
    /// constructors / destructor
    toldt(const toldt& copy): tell_(copy.tell_) {
    }
    toldt(): tell_(0) {
    }
    virtual ~toldt() {
    }

    /// reset / seek / tell / length
    virtual ssize_t reset() {
        ssize_t told = tell_;
        tell_ = 0;
        return told;
    }
    virtual ssize_t seek(size_t to, int whence) {
        size_t length = this->length();
        if (from_end == (whence)) {
            if (length < (to)) {
                to = 0;
            } else {
                to = length - to;
            }
        } else {
            if (from_current == (whence)) {
                if (length < (to += tell_)) {
                    to = length;
                }
            } else {
                if (length < (to)) {
                    to = length;
                }
            }
        }
        tell_ = to;
        return tell_;
    }
    virtual ssize_t tell() const {
        return tell_;
    }
    virtual size_t length() const {
        return 0;
    }

protected:
    size_t tell_;
}; /// class toldt
typedef toldt<> told;

typedef toldt<byte_seeker> byte_told;
typedef toldt<word_seeker> word_told;

typedef toldt<char_seeker> char_told;
typedef toldt<tchar_seeker> tchar_told;
typedef toldt<wchar_seeker> wchar_told;

} /// namespace io
} /// namespace xos

#endif /// XOS_IO_TOLD_HPP
