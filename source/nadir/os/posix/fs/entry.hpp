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
#ifndef _NADIR_OS_POSIX_FS_ENTRY_HPP
#define _NADIR_OS_POSIX_FS_ENTRY_HPP

#include "nadir/fs/directory/entry.hpp"
#include "nadir/io/logger.hpp"

#include <sys/stat.h>
#include <utime.h>

#define S_IRWX (S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)
#define S_IRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define S_IR (S_IRUSR | S_IRGRP | S_IROTH)

namespace nadir {
namespace os {
namespace posix {
namespace fs {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS stat_t {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    stat_t() { memset(&stat_, 0, sizeof(stat_)); }
    virtual ~stat_t() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual struct stat* operator & () const { return (struct stat*)(&stat_); }
    virtual operator struct stat&() const { return (struct stat&)(stat_); }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    struct stat stat_;
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS utimbuf_t {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    utimbuf_t() { memset(&utimbuf_, 0, sizeof(utimbuf_)); }
    virtual ~utimbuf_t() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual struct utimbuf* operator & () const { return (struct utimbuf*)(&utimbuf_); }
    virtual operator struct utimbuf&() const { return (struct utimbuf&)(utimbuf_); }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    struct utimbuf utimbuf_;
};

typedef nadir::fs::entry_implements entry_implements;
typedef nadir::fs::entry entry_extends;
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

    typedef nadir::fs::time_when time_when;
    enum {
        time_when_none     = nadir::fs::time_when_none,
        time_when_modified = nadir::fs::time_when_modified,
        time_when_accessed = nadir::fs::time_when_accessed,
        time_when_changed  = nadir::fs::time_when_changed,
        time_when_created  = nadir::fs::time_when_created
    };
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
    typedef nadir::fs::entry_ssize_t entry_ssize_t;

    typedef TString string_t;
    typedef TChar char_t;
    typedef TEnd end_t;
    enum { end = VEnd };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    entryt() {
    }
    entryt(const entryt& copy): Extends(copy) {
    }
    virtual ~entryt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual entry_type exists(const char_t* path) {
        char_string path_name(path);
        const char* chars = 0;
        if ((chars = path_name.has_chars())) {
            if ((is_found(chars))) {
                entry_type type = entry_type_none;
                if (entry_type_none != (type = get_found_attributes())) {
                    return type;
                }
            }
        }
        return entry_type_none;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool is_found(const char* path) {
        if ((path)) {
            int err = 0;
            if (!(err = stat(path, &st_))) {
                if (!(err = lstat(path, &lst_))) {
                    const char* name = path;
                    for (char c = *(path); c; c = *(++path)) {
                        if ((is_directory_separator(c))) {
                            name = path+1;
                        }
                    }
                    if ((name[0])) {
                        this->set_name(name);
                    }
                    return true;
                } else {
                    LOG_DEBUG("failed " << errno << " on lstat(\"" << path << "\",...)");
                }
            } else {
                LOG_DEBUG("failed " << errno << " on stat(\"" << path << "\",...)");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual entry_type get_found(const char_t* path) {
        char_string path_name(path);
        if ((path = this->name())) {
            const char* chars = 0;
            if ((path_name.has_chars())) {
                path_name.append(NADIR_FS_DIRECTORY_SEPARATOR_CHARS);
            }
            path_name.append(path);
            if ((chars = path_name.has_chars())) {
                if ((is_found(chars))) {
                    return get_found_attributes(this->type());
                }
            }
        }
        return entry_type_none;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual entry_type get_found_attributes(entry_type type = entry_type_none) {
        entry_ssize_t size = -1;
        if (0 <= (size = get_found_size())) {
            if (entry_type_none != (type = get_found_type(type))) {
                time_when times = time_when_none;
                if (time_when_none != (times = get_found_times())) {
                    return type;
                }
            }
        }
        return entry_type_none;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual time_when get_found_times() {
        time_when time = time_when_none;
        const struct stat& st = st_;
        bool is_local = false;

        if ((to_time(this->time_modified_, st.st_mtime, is_local))) {
            LOG_DEBUG("time modified  = " << this->time_modified_.month() << "/" << this->time_modified_.day() << "/" << this->time_modified_.year());
            time |= time_when_modified;
        }
        if ((to_time(this->time_accessed_, st.st_atime, is_local))) {
            LOG_DEBUG("time accessed  = " << this->time_accessed_.month() << "/" << this->time_accessed_.day() << "/" << this->time_accessed_.year());
            time |= time_when_accessed;
        }
        if ((to_time(this->time_changed_, st.st_ctime, is_local))) {
            LOG_DEBUG("time changed  = " << this->time_changed_.month() << "/" << this->time_changed_.day() << "/" << this->time_changed_.year());
            time |= time_when_changed;
        }
        this->set_times(time);
        return time;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual entry_type get_found_type(entry_type type = entry_type_none) {
        const struct stat& st = st_;
        const struct stat& lst = lst_;
        mode_t fmt;

        if (S_IFDIR == (S_IFDIR & st.st_mode)) {
            LOG_DEBUG("S_IFDIR");
            type &= ~entry_type_file;
            type |= entry_type_directory;
        } else {
            type &= ~entry_type_directory;
            type |= entry_type_file;
        }

        if (S_IFLNK == (fmt = (S_IFMT & (lst.st_mode)))) {
            LOG_DEBUG("S_IFLNK");
            type &= ~entry_type_hard_link;
            type |= entry_type_symbolic_link;
        }
        this->set_type(type);
        return type;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual entry_ssize_t get_found_size() {
        const struct stat& st = st_;
        off_t size = -1;

        if (0 <= (size = st.st_size)) {
            this->set_size(size);
        }
        return size;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual nadir::fs::time* to_time
    (nadir::fs::time& to, const time_t& from, bool is_local = false) {
        struct tm tm;
        if ((to_system_time(tm, from, is_local))) {
            return to_time(to, tm, is_local);
        }
        return 0;
    }
    virtual time_t* from_time
    (time_t& to, const nadir::fs::time& from, bool is_local = false) {
        struct tm tm;
        if ((from_time(tm, from, is_local))) {
            return from_system_time(to, tm, is_local);
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual nadir::fs::time* to_time
    (nadir::fs::time& to, const struct tm& from, bool is_local = false) {
        to.clear();
        to.set_year(from.tm_year+1900);
        to.set_month(from.tm_mon+1);
        to.set_day(from.tm_mday);
        to.set_hour(from.tm_hour);
        to.set_minute(from.tm_min);
        to.set_second(from.tm_sec);
        return &to;
    }
    virtual struct tm* from_time
    (struct tm& to, const nadir::fs::time& from, bool is_local = false) {
        memset(&to, 0, sizeof(struct tm));
        to.tm_year = from.year()-1900;
        to.tm_mon = from.month()-1;
        to.tm_mday = from.day();
        to.tm_hour = from.hour();
        to.tm_min = from.minute();
        to.tm_sec = from.second();
        return &to;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual struct tm* to_system_time
    (struct tm& to, const time_t& from, bool is_local = false) const {
        struct tm* t = 0;
        if (is_local) {
            if (!(t = localtime_r(&from, &to))) {
                LOG_ERROR("failed " << errno << " on localtime_r()");
            }
        } else {
            if (!(t = gmtime_r(&from, &to))) {
                LOG_ERROR("failed " << errno << " on gmtime_r()");
            }
        }
        return t;
    }
    virtual time_t* from_system_time
    (time_t& to, const struct tm& from, bool is_local = false) const {
        struct tm tm = from;
        if ((is_local)) {
            if (0 > (to = mktime(&tm))) {
                LOG_ERROR("failed " << errno << " on mktime()");
                return 0;
            }
        } else {
            if (0 > (to = timegm(&tm))) {
                LOG_ERROR("failed " << errno << " on timegm()");
                return 0;
            }
        }
        return &to;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool is_directory_separator(char c) const {
        if (('/' == c) || ('\\' == c)) {
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    stat_t st_, lst_, to_st_;
    utimbuf_t ut_;
};
typedef entryt<> entry;

} // namespace fs
} // namespace posix 
} // namespace os 
} // namespace nadir 

#endif // _NADIR_OS_POSIX_FS_ENTRY_HPP 
