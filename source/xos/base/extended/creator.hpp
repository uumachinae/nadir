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
///   File: creator.hpp
///
/// Author: $author$
///   Date: 4/22/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_BASE_EXTENDED_CREATOR_HPP
#define XOS_BASE_EXTENDED_CREATOR_HPP

#include "xos/base/created.hpp"

namespace xos {
namespace extended {

/// class creatort
template <class TImplements = xos::creator, class TExtends = xos::extend>
class exported creatort: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef creatort derives; 
    
    /// constructors / destructor
    creatort(const creatort& copy): is_created_(copy.is_created_) {
    }
    creatort(const bool& is_created): is_created_(is_created) {
    }
    creatort(): is_created_(false) {
    }
    virtual ~creatort() {
        if (!(this->destroyed())) {
            throw (create_exception(destroy_failed));
        }
    }

    /// ...is_created / ...is_destroyed
    virtual bool set_is_created(bool to = true) {
        is_created_ = to;
        return is_created_;
    }
    virtual bool is_created() const {
        return is_created_;
    }
    virtual bool set_is_destroyed(bool to = true) {
        is_created_ = !to;
        return !is_created_;
    }
    virtual bool is_destroyed() const {
        return !is_created_;
    }

protected:
    bool is_created_;
}; /// class creatort
typedef creatort<> creator;

} /// namespace extended
} /// namespace xos

#endif /// XOS_BASE_EXTENDED_CREATOR_HPP
