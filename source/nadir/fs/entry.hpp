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
#ifndef _NADIR_FS_ENTRY_HPP
#define _NADIR_FS_ENTRY_HPP

#include "nadir/fs/time.hpp"
#include "nadir/base/string.hpp"

#define NADIR_FS_ENTRY_TYPE_WHICH_NAME_NONE "none"
#define NADIR_FS_ENTRY_TYPE_WHICH_NAME_FILE "file"
#define NADIR_FS_ENTRY_TYPE_WHICH_NAME_DIRECTORY "directory"
#define NADIR_FS_ENTRY_TYPE_WHICH_NAME_SYMBOLIC_LINK "symbolic-link"
#define NADIR_FS_ENTRY_TYPE_WHICH_NAME_HARD_LINK "hard-link"
#define NADIR_FS_ENTRY_TYPE_WHICH_NAME_BLOCK_DEVICE "block-device"
#define NADIR_FS_ENTRY_TYPE_WHICH_NAME_CHAR_DEVICE "char-device"
#define NADIR_FS_ENTRY_TYPE_WHICH_NAME_PIPE "pipe"
#define NADIR_FS_ENTRY_TYPE_WHICH_NAME_SOCKET "socket"

namespace nadir {
namespace fs {

typedef int64_t entry_ssize_t;
typedef uint64_t entry_size_t;

///////////////////////////////////////////////////////////////////////
///   Enum: entry_type_which
///////////////////////////////////////////////////////////////////////
typedef int entry_type_which;
enum {
    entry_type_none = 0,

    entry_type_file          = 1,
    entry_type_directory     = (1 << 1),
    entry_type_symbolic_link = (1 << 2),
    entry_type_hard_link     = (1 << 3),
    entry_type_block_device  = (1 << 4),
    entry_type_char_device   = (1 << 5),
    entry_type_pipe          = (1 << 6),
    entry_type_socket        = (1 << 7),

    next_entry_type,
    first_entry_type = 1,
    last_entry_type = (next_entry_type-1),

    entry_type_any = (((last_entry_type) << 1) - 1)
};

typedef implement_base entry_type_implements;
typedef base entry_type_extends;
///////////////////////////////////////////////////////////////////////
///  Class: entry_typet
///////////////////////////////////////////////////////////////////////
template
<class TImplements = entry_type_implements, class TExtends = entry_type_extends>

class _EXPORT_CLASS entry_typet: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    entry_typet(entry_type_which which = entry_type_none): which_(which) {
    }
    entry_typet(const entry_typet& copy): which_(copy.which()) {
    }
    virtual ~entry_typet() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual entry_typet& operator |= (entry_type_which which) {
        which_ |= which;
        return *this;
    }
    virtual entry_typet& operator &= (entry_type_which which) {
        which_ &= which;
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual entry_type_which which() const {
        return which_;
    }
    virtual operator entry_type_which() const {
        return which_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static const char* name(entry_type_which of) {
        switch (of) {
        case entry_type_file          : return NADIR_FS_ENTRY_TYPE_WHICH_NAME_FILE;
        case entry_type_directory     : return NADIR_FS_ENTRY_TYPE_WHICH_NAME_DIRECTORY;
        case entry_type_symbolic_link : return NADIR_FS_ENTRY_TYPE_WHICH_NAME_SYMBOLIC_LINK;
        case entry_type_hard_link     : return NADIR_FS_ENTRY_TYPE_WHICH_NAME_HARD_LINK;
        case entry_type_block_device  : return NADIR_FS_ENTRY_TYPE_WHICH_NAME_BLOCK_DEVICE;
        case entry_type_char_device   : return NADIR_FS_ENTRY_TYPE_WHICH_NAME_CHAR_DEVICE;
        case entry_type_pipe          : return NADIR_FS_ENTRY_TYPE_WHICH_NAME_PIPE;
        case entry_type_socket        : return NADIR_FS_ENTRY_TYPE_WHICH_NAME_SOCKET;
        }
        return NADIR_FS_ENTRY_TYPE_WHICH_NAME_NONE;
    }
    static entry_type_which of(const char* name) {
        return entry_type_none;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    entry_type_which which_;
};
typedef entry_typet<> entry_type;

typedef implement_base entry_implements;
typedef base entry_extends;
///////////////////////////////////////////////////////////////////////
///  Class: entryt
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char, typename TEnd = TChar, TEnd VEnd = 0,
 class TString = char_stringt<TChar, TEnd, VEnd>,
 class TExtends = entry_extends, class TImplements = entry_implements>

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
    entryt()
    : is_hidden_(false), size_(0), type_(entry_type_none), times_(time_when_none),
      time_modified_(time_when_modified), time_accessed_(time_when_accessed),
      time_changed_(time_when_changed), time_created_(time_when_created) {
    }
    entryt(const entryt& copy)
    : name_(copy.name()), is_hidden_(copy.is_hidden()),
      size_(copy.size()), type_(copy.type()), times_(copy.times()),
      time_modified_(copy.time_modified()), time_accessed_(copy.time_accessed()),
      time_changed_(copy.time_changed()), time_created_(copy.time_created()) {
    }
    virtual ~entryt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual entry_type exists(const char_t* path) {
        return entry_type_none;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual time_when set_times_to_set(const entryt& e, bool is_local = false) {
        time_when times = time_when_none;
        const time& time_modified = e.time_modified();
        const time& time_accessed = e.time_accessed();
        const time& time_changed = e.time_changed();
        const time& time_created = e.time_created();
        times = set_times_to_set
        (time_modified, time_accessed,
         time_changed, time_created, is_local);
        return times;
    }
    virtual time_when set_times_to_set
    (const time& time_modified, const time& time_accessed,
     const time& time_changed, const time& time_created,
     bool is_local = false) {
        time_when times = time_when_none;
        return times;
    }
    virtual time_when set_times_set() {
        time_when times = time_when_none;
        return times;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void clear() {
        is_hidden_ = false;
        size_ = 0;
        type_ = entry_type_none;
        times_ = time_when_none;
        time_modified_.clear();
        time_accessed_.clear();
        time_changed_.clear();
        time_created_.clear();
        name_.clear();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_name(const char_t* chars, size_t length) {
        name_.assign(chars, length);
        on_set_name();
        return name_.c_str();
    }
    virtual const char_t* set_name(const char_t* chars) {
        name_.assign(chars);
        on_set_name();
        return name_.c_str();
    }
    virtual const char_t* name(size_t& length) const {
        length = name_.length();
        return name_.c_str();
    }
    virtual const char_t* name() const {
        return name_.c_str();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_is_hidden(bool is_hidden = true) {
        is_hidden_ = is_hidden;
        on_set_is_hidden();
        return is_hidden_;
    }
    virtual bool is_hidden() const {
        return is_hidden_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual entry_size_t set_size(entry_size_t size) {
        size_ = size;
        on_set_size();
        return size_;
    }
    virtual entry_size_t size() const {
        return size_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual entry_type set_type(entry_type type) {
        type_ = type;
        on_set_type();
        return type_;
    }
    virtual entry_type type() const {
        return type_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual time_when set_times(time_when times) {
        times_ = times;
        return times_;
    }
    virtual time_when times() const {
        return times_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const time& set_time_modified(const time& to) {
        times_ |= time_when_modified;
        time_modified_ = to;
        return time_modified_;
    }
    virtual const time& time_modified() const {
        return time_modified_;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const time& set_time_accessed(const time& to) {
        times_ |= time_when_accessed;
        time_accessed_ = to;
        return time_accessed_;
    }
    virtual const time& time_accessed() const {
        return time_accessed_;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const time& set_time_changed(const time& to) {
        times_ |= time_when_changed;
        time_changed_ = to;
        return time_changed_;
    }
    virtual const time& time_changed() const {
        return time_changed_;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const time& set_time_created(const time& to) {
        times_ |= time_when_created;
        time_created_ = to;
        return time_created_;
    }
    virtual const time& time_created() const {
        return time_created_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const time* time_which(time_when_which t) const {
        switch (t) {
        case fs::time_when_modified:
            return &time_modified_;
            break;
        case fs::time_when_accessed:
            return &time_accessed_;
            break;
        case fs::time_when_changed:
            return &time_changed_;
            break;
        case fs::time_when_created:
            return &time_created_;
            break;
        }
        return 0;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void on_set_is_hidden() {
    }
    virtual void on_set_name() {
    }
    virtual void on_set_size() {
    }
    virtual void on_set_type() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    string_t name_;
    bool is_hidden_;
    entry_size_t size_;
    entry_type type_;
    time_when times_;
    time time_modified_, time_accessed_, time_changed_, time_created_;
};
typedef entryt<> entry;

} // namespace fs
} // namespace nadir 

#endif // _NADIR_FS_ENTRY_HPP 
