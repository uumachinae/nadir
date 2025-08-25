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
#ifndef _NADIR_OS_POSIX_FS_DIRECTORY_ENTRY_HPP
#define _NADIR_OS_POSIX_FS_DIRECTORY_ENTRY_HPP

#include "nadir/os/posix/fs/entry.hpp"
#include "nadir/fs/directory/entry.hpp"

#include <dirent.h>

namespace nadir {
namespace os {
namespace posix {
namespace fs {
namespace directory {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS dirent_t {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    dirent_t(const struct dirent* dirent = 0): dirent_(dirent) {}
    virtual ~dirent_t() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual dirent_t& operator = (const struct dirent* dirent) {
        dirent_ = dirent;
        return *this;
    }
    virtual const struct dirent& operator -> () const { return *dirent_; }
    virtual const struct dirent& operator * () const { return *dirent_; }
    virtual const struct dirent* operator & () const { return dirent_; }
    virtual operator const struct dirent*() const { return dirent_; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    const struct dirent* dirent_;
};

typedef nadir::fs::directory::entry_implements entry_implements;
///////////////////////////////////////////////////////////////////////
///  Class: entry_extendst
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char, typename TEnd = TChar, TEnd VEnd = 0,
 class TString = char_stringt<TChar, TEnd, VEnd>,
 class TExtends = nadir::fs::directory::entryt
 <TChar, TEnd, VEnd, TString, fs::entryt<TChar, TEnd, VEnd> >,
 class TImplements = fs::entry_implements>

class _EXPORT_CLASS entry_extendst: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
};

typedef entry_extendst<> entry_extends;
///////////////////////////////////////////////////////////////////////
///  Class: entryt
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char, typename TEnd = TChar, TEnd VEnd = 0,
 class TString = char_stringt<TChar, TEnd, VEnd>,
 class TExtends = entry_extendst<TChar, TEnd, VEnd>,
 class TImplements = entry_implements>

class _EXPORT_CLASS entryt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

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
    typedef TString string_t;
    typedef TChar char_t;
    typedef TEnd end_t;
    enum { end = VEnd };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    entryt(const entryt& copy): Extends(copy) {
    }
    entryt() {
    }
    virtual ~entryt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual entryt& assign(const char_t* path, const struct dirent* dirent) {
        if ((path) && (dirent)) {
            this->set_dirent(dirent);
            this->set_found(path, *dirent);
        }
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual entry_type set_found(const char_t* path, const struct dirent& dirent) {
        entry_type type = set_found_type(dirent);
#if defined(MACOSX)
        this->set_name(dirent.d_name, dirent.d_namlen);
#else // defined(MACOSX)
        this->set_name(dirent.d_name);
#endif // defined(MACOSX)
        return this->get_found(path);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual entry_type set_found_type(const struct dirent& dirent) {
        this->set_type(entry_type_none);
        switch (dirent.d_type) {
        case DT_REG:
            this->set_type(entry_type_file);
            break;
        case DT_DIR:
            this->set_type(entry_type_directory);
            break;
        case DT_LNK:
            this->set_type(entry_type_symbolic_link);
            break;
        case DT_BLK:
            this->set_type(entry_type_block_device);
            break;
        case DT_CHR:
            this->set_type(entry_type_char_device);
            break;
        case DT_FIFO:
            this->set_type(entry_type_pipe);
            break;
        case DT_SOCK:
            this->set_type(entry_type_socket);
            break;
        }
        return this->type();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const struct dirent* set_dirent(const struct dirent* dirent) {
        dirent_ = dirent;
        return dirent_;
    }
    virtual const struct dirent* dirent() const {
        return dirent_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    dirent_t dirent_;
};
typedef entryt<> entry;

} // namespace directory
} // namespace fs 
} // namespace posix 
} // namespace os 
} // namespace nadir 

#endif // _NADIR_OS_POSIX_FS_DIRECTORY_ENTRY_HPP 
