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
///   File: entry.hpp
///
/// Author: $author$
///   Date: 1/4/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_OS_MICROSOFT_WINDOWS_FS_DIRECTORY_ENTRY_HPP
#define _NADIR_OS_MICROSOFT_WINDOWS_FS_DIRECTORY_ENTRY_HPP

#include "nadir/os/microsoft/windows/fs/entry.hpp"
#include "nadir/fs/directory/entry.hpp"

namespace nadir {
namespace os {
namespace microsoft {
namespace windows {
namespace fs {
namespace directory {

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
    virtual entryt& assign(WIN32_FIND_DATAW find_data) {
        nadir::char_string name(find_data.cFileName);
        this->set_name(name.chars());
        this->find_data_ = find_data;
        this->get_found_attributes();
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
};
typedef entryt<> entry;

} // namespace directory
} // namespace fs 
} // namespace windows 
} // namespace microsoft 
} // namespace os 
} // namespace nadir 

#endif // _NADIR_OS_MICROSOFT_WINDOWS_FS_DIRECTORY_ENTRY_HPP 
