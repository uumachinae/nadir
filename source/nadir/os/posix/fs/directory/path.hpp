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
///   File: path.hpp
///
/// Author: $author$
///   Date: 12/30/2016
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_OS_POSIX_FS_DIRECTORY_PATH_HPP
#define _NADIR_OS_POSIX_FS_DIRECTORY_PATH_HPP

#include "nadir/os/posix/fs/directory/entry.hpp"
#include "nadir/fs/directory/path.hpp"
#include "nadir/base/opened.hpp"

namespace nadir {
namespace os {
namespace posix {
namespace fs {
namespace directory {

typedef DIR* path_attached_t;
///////////////////////////////////////////////////////////////////////
///  Class: patht
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char,  typename TEnd = TChar, TEnd VEnd = 0,
 class TString = char_stringt<TChar, TEnd, VEnd>,
 class TEntry = entryt<TChar, TEnd, VEnd>,
 class TImplements = attachert
 <path_attached_t, int, 0, nadir::fs::directory::patht
  <TChar, TEnd, VEnd, TString, TEntry> >,
 class TExtends = openedt
 <path_attached_t, int, 0, TImplements, attachedt
  <path_attached_t, int, 0, TImplements> > >

class _EXPORT_CLASS patht: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef patht Derives;

    typedef path_attached_t attached_t;
    typedef nadir::fs::entry_type entry_type;
    enum {
        entry_type_none          = nadir::fs::entry_type_none,
        entry_type_file          = nadir::fs::entry_type_file,
        entry_type_directory     = nadir::fs::entry_type_directory,
        entry_type_symbolic_link = nadir::fs::entry_type_symbolic_link,
        entry_type_hard_link     = nadir::fs::entry_type_hard_link,
        entry_type_block_device  = nadir::fs::entry_type_block_device,
        entry_type_char_device   = nadir::fs::entry_type_char_device,
        entry_type_pipe          = nadir::fs::entry_type_pipe,
        entry_type_socket        = nadir::fs::entry_type_socket,
    };
    typedef TEntry entry_t;
    typedef TString string_t;
    typedef TChar char_t;
    typedef TEnd end_t;
    enum { end = VEnd };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    patht(): get_first_(0), get_next_(0) {
    }
    virtual ~patht() {
        if (!(this->closed())) {
            open_exception e(close_failed);
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool open(const char_t* name) {
        if ((name)) {
            if ((this->closed())) {
                attached_t d = 0;

                LOG_DEBUG("opendir(name = \"" << name << "\")...");
                if ((d = opendir(name))) {
                    LOG_DEBUG("...opendir(name = \"" << name << "\")");
                    this->set_name(name);
                    this->attach_opened(d);
                    get_first_ = &Derives::get_first;
                    return true;
                } else {
                    LOG_ERROR("failed " << errno << " on opendir(\"" << name << "\")");
                }
            }
        }
        return false;
    }
    virtual bool close() {
        attached_t d = 0;
        get_first_ = 0;
        get_next_ = 0;

        if ((d = this->detach())) {
            int err = 0;

            LOG_DEBUG("closedir(d)...");
            if (!(err = closedir(d))) {
                LOG_DEBUG("...closedir(d)");
                return true;
            } else {
                LOG_ERROR("failed " << err << " on closedir()");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual entry_t* get_first_entry() {
        if ((get_first_)) {
            return (this->*get_first_)();
        }
        return 0;
    }
    virtual entry_t* get_next_entry() {
        if ((get_next_)) {
            return (this->*get_next_)();
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_name(const char_t* chars, size_t length) {
        name_.assign(chars, length);
        return name_.c_str();
    }
    virtual const char_t* set_name(const char_t* chars) {
        name_.assign(chars);
        return name_.c_str();
    }
    virtual const char_t* name(size_t& length) const {
        length = name_.length();
        return name_.c_str();
    }
    virtual const char_t* name() const {
        return name_.c_str();
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual entry_t* get_first_again() {
        return 0;
    }
    virtual entry_t* get_first() {
        get_first_ = &Derives::get_first_again;
        get_next_ = &Derives::get_next;
        return get_next();
    }
    virtual entry_t* get_next() {
        attached_t d = 0;

        if ((d = this->attached_to())) {
            const struct dirent* dirent = 0;

            LOG_DEBUG("readdir(d)...");
            if ((dirent = readdir(d))) {
                LOG_DEBUG("...readdir(d)");
                entry_.assign(name_.chars(), dirent);
                return &entry_;
            } else {
                LOG_DEBUG("failed " << errno << " on readdir()");
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef entry_t* (Derives::*get_t)();

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    get_t get_first_, get_next_;
    entry_t entry_;
    string_t name_;
};
typedef patht<> path;

} // namespace directory
} // namespace fs 
} // namespace posix 
} // namespace os 
} // namespace nadir 

#endif // _NADIR_OS_POSIX_FS_DIRECTORY_PATH_HPP 
