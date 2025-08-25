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
///   File: entry.hpp
///
/// Author: $author$
///   Date: 12/30/2016
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_FS_DIRECTORY_ENTRY_HPP
#define _NADIR_FS_DIRECTORY_ENTRY_HPP

#include "nadir/fs/entry.hpp"

#define NADIR_FS_DIRECTORY_PARENT_CHARS ".."
#define NADIR_FS_DIRECTORY_CURRENT_CHARS "."
#define NADIR_FS_DIRECTORY_SEPARATOR_CHARS "/"

namespace nadir {
namespace fs {
namespace directory {

typedef fs::entry_implements entry_implements;
///////////////////////////////////////////////////////////////////////
///  Class: entryt
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char, typename TEnd = TChar, TEnd VEnd = 0,
 class TString = char_stringt<TChar, TEnd, VEnd>,
 class TExtends = fs::entryt<TChar, TEnd, VEnd>,
 class TImplements = entry_implements>

class _EXPORT_CLASS entryt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TString string_t;
    typedef TChar char_t;
    typedef TEnd end_t;
    enum { end = VEnd };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    entryt(const entryt& copy)
    : Extends(copy),
      current_chars_(NADIR_FS_DIRECTORY_CURRENT_CHARS),
      parent_chars_(NADIR_FS_DIRECTORY_PARENT_CHARS),
      is_current_(copy.is_current()),
      is_parent_(copy.is_parent()) {
    }
    entryt()
    : current_chars_(NADIR_FS_DIRECTORY_CURRENT_CHARS),
      parent_chars_(NADIR_FS_DIRECTORY_PARENT_CHARS),
      is_current_(false),
      is_parent_(false) {
    }
    virtual ~entryt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool is_circular() const {
        return (is_current_ || is_parent_);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_is_parent(bool is_true = true) {
        is_current_ = (false);
        return is_parent_ = is_true;
    }
    virtual bool is_parent() const {
        return is_parent_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_is_current(bool is_true = true) {
        is_parent_ = (false);
        return is_current_ = is_true;
    }
    virtual bool is_current() const {
        return is_current_;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void on_set_name() {
        set_is_current(false);
        set_is_parent(false);
        if (!(this->name_.compare(current_chars_))) {
            set_is_current();
        } else {
            if (!(this->name_.compare(parent_chars_))) {
                set_is_parent();
            } else {
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    const char*const current_chars_, *const parent_chars_;
    bool is_current_, is_parent_;
};
typedef entryt<> entry;

} // namespace directory
} // namespace fs 
} // namespace nadir 

#endif // _NADIR_FS_DIRECTORY_ENTRY_HPP 
