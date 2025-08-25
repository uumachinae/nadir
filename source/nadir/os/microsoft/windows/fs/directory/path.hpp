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
///   File: path.hpp
///
/// Author: $author$
///   Date: 1/4/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_OS_MICROSOFT_WINDOWS_FS_DIRECTORY_PATH_HPP
#define _NADIR_OS_MICROSOFT_WINDOWS_FS_DIRECTORY_PATH_HPP

#include "nadir/os/microsoft/windows/fs/directory/entry.hpp"
#include "nadir/fs/directory/path.hpp"
#include "nadir/base/opened.hpp"

#if !defined(WINDOWS)
extern "C" {
}
#endif // !defined(WINDOWS)

namespace nadir {
namespace os {
namespace microsoft {
namespace windows {
namespace fs {
namespace directory {

typedef HANDLE path_attached_t;
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
            LOG_ERROR("...throwing open_exception e(close_failed)...")
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool open(const char_t* name) {
        if ((name) && (name[0])) {
            if ((this->closed())) {
                entry_type type = entry_type_none;
                if (entry_type_none != (type = this->entry_.exists(name))) {
                    if ((entry_type_directory == (entry_type_directory & type))) {
                        wchar_string wmatch(name, "/*", NULL);
                        const wchar_t* wchars = 0;
                        if ((wchars = wmatch.has_chars())) {
                            match_.assign(wchars);
                            if ((name = match_.has_chars())) {
                                HANDLE detached = 0;
                                LOG_DEBUG("FindFirstFileW(\"" << name << "\", &find_data_)...");
                                if ((INVALID_HANDLE_VALUE != (detached = FindFirstFileW(wchars, &find_data_)))) {
                                    this->attach_opened(detached);
                                    name_.assign(name);
                                    entry_.assign(find_data_);
                                    get_first_ = &Derives::get_first;
                                    get_next_ = &Derives::get_next;
                                    return true;
                                }
                            } else {
                                LOG_DEBUG("...failed " << GetLastError() << " on FindFirstFileW(\"" << name << "\", &find_data_)");
                            }
                        }
                    }
                }
            }
        }
        return false;
    }
    virtual bool close() {
        HANDLE detached = 0;
        get_first_ = 0;
        get_next_ = 0;
        name_.clear();
        if ((detached = this->detach())) {
            LOG_DEBUG("FindClose(detached)...");
            if ((FindClose(detached))) {
                return true;
            } else {
                LOG_ERROR("...failed " << GetLastError() << " on FindClose(detached)");
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

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual entry_t* get_first_again() {
        return 0;
    }
    virtual entry_t* get_first() {
        get_first_ = &Derives::get_first_again;
        return &entry_;
    }
    virtual entry_t* get_next() {
        HANDLE detached = 0;
        const char_t* name = 0;
        if ((detached = (this->attached_to())) && (name = match_.has_chars())) {
            LOG_DEBUG("FindNextFileW(detached, &find_data_)(\"" << name << "\")...");
            if (((FindNextFileW(detached, &find_data_)))) {
                entry_.assign(find_data_);
                return &entry_;
            } else {
                LOG_DEBUG("...failed " << GetLastError() << " on FindNextFileW(detached, &find_data_)(\"" << name << "\")...");
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
    string_t name_, match_;
    WIN32_FIND_DATAW find_data_;
};
typedef patht<> path;

} // namespace directory
} // namespace fs 
} // namespace windows 
} // namespace microsoft 
} // namespace os 
} // namespace nadir 

#endif // _NADIR_OS_MICROSOFT_WINDOWS_FS_DIRECTORY_PATH_HPP 
