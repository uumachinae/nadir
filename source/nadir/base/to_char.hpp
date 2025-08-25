///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2016 $organization$
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
///   File: to_char.hpp
///
/// Author: $author$
///   Date: 9/18/2016
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_BASE_TO_CHAR_HPP
#define _NADIR_BASE_TO_CHAR_HPP

#include "nadir/base/base.hpp"
#include <string>

namespace nadir {

typedef implement_base to_chart_implements;
///////////////////////////////////////////////////////////////////////
///  Class: to_chart
///////////////////////////////////////////////////////////////////////
template
<typename TToChar, typename TChar,
 class TExtends = ::std::basic_string<TToChar>,
 class TImplements = to_chart_implements>

class _EXPORT_CLASS to_chart: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TToChar to_char_t;
    typedef TChar char_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    to_chart(const char_t& c) {
        transcode(c);
    }
    to_chart(size_t& count, const char_t* chars) {
        transcode(count, chars);
    }
    to_chart(const to_chart& copy): Extends(copy) {
    }
    to_chart() {
    }
    virtual ~to_chart() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual to_chart& transcode(const char_t& c) {
        to_char_t to = (to_char_t)c;
        this->assign(&to, 1);
        return *this;
    }
    virtual to_chart& transcode(size_t& count, const char_t* chars) {
        if ((chars)) {
            to_char_t to = (to_char_t)(*chars);
            this->assign(&to, 1);
            count = 1;
        }
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace nadir 

#endif // _NADIR_BASE_TO_CHAR_HPP 
