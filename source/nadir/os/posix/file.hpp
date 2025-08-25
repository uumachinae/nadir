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
///   File: file.hpp
///
/// Author: $author$
///   Date: 12/30/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_OS_POSIX_FILE_HPP
#define _NADIR_OS_POSIX_FILE_HPP

#include "nadir/base/opened.hpp"
#include "nadir/io/stream.hpp"
#include "nadir/io/logger.hpp"

#include <fcntl.h>

namespace nadir {
namespace os {
namespace posix {

typedef int fd_t;
typedef int invalid_fd_t;
enum { invalid_fd = -1 };

typedef fd_t file_attached_t;
typedef invalid_fd_t file_unattached_t;
enum { file_unattached = invalid_fd };

///////////////////////////////////////////////////////////////////////
///  Class: filet
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0,
 class TImplement = implement_base, class TExtend = base,
 class TReader = io::readert<TWhat, TSized, TEnd, VEnd, TImplement>,
 class TWriter = io::writert<TWhat, TSized, TEnd, VEnd, TImplement>,
 class TStream = io::streamt<TWhat, TSized, TEnd, VEnd, TReader, TWriter>,
 class TOpener = openert<TStream>,
 class TAttacher = attachert
 <file_attached_t, file_unattached_t, file_unattached, TOpener>,
 class TAttached = attachedt
 <file_attached_t, file_unattached_t, file_unattached, TAttacher, TExtend>,
 class TOpened = openedt
 <file_attached_t, file_unattached_t, file_unattached, TAttacher, TAttached>,
 class TImplements = TAttacher, class TExtends = TOpened>

class _EXPORT_CLASS filet: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef posix::fd_t fd_t;
    typedef posix::invalid_fd_t invalid_fd_t;
    enum { invalid_fd = posix::invalid_fd };

    typedef typename TImplements::attached_t attached_t;
    typedef typename TImplements::unattached_t unattached_t;
    enum { unattached = TImplements::unattached };

    typedef typename TImplements::what_t what_t;
    typedef typename TImplements::sized_t sized_t;
    typedef typename TImplements::end_t endof_t;
    enum { endof = TImplements::end };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    filet(attached_t attached, bool is_created)
    : Extends(attached, is_created) {
    }
    filet(attached_t attached): Extends(attached) {
    }
    filet() {
    }
    virtual ~filet() {
        if (!(this->closed())) {
            const open_exception e(close_failed);
            LOG_ERROR("...throwing open_exception e(close_failed)...");
            throw (e);
        }
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool open(const char* path) {
        int oflag = O_RDONLY | O_EXCL;
        return open(path, oflag);
    }
    virtual bool open(const char* path, int oflag) {
        mode_t mode = S_IRWXU | S_IRGRP | S_IROTH;
        return open(path, oflag, mode);
    }
    virtual bool open(const char* path, int oflag, mode_t mode) {
        if ((this->closed())) {
            attached_t fd = invalid_fd;
            
            LOG_DEBUG("::open(path = \"" << path << "\", oflag = " << oflag << ", mode = " << mode << ")...");
            if (invalid_fd = (fd = ::open(path, oflag, mode))) {
                this->attach_opened(fd);
                return true;
            } else {
                LOG_ERROR("...failed errno = " << errno << " on ::open(path = \"" << path << "\", oflag = " << oflag << ", mode = " << mode << ")...");
            }
        }
        return false;
    }
    virtual bool close() {
        attached_t fd = invalid_fd;
        
        if (invalid_fd != (fd = this->detach())) {
            int err = 0;
            
            LOG_DEBUG("::close(fd = " << fd << ")...");
            if ((err = ::close(fd))) {
                LOG_ERROR("...failed errno = " << errno << " on close(fd = " << fd << ")");
            } else {
                return true;
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t read(what_t* what, size_t size) {
        sized_t* sized = 0;

        if ((sized = ((sized_t*)what)) && (size)) {
            attached_t fd = invalid_fd;

            if (invalid_fd != (fd = this->attached_to())) {
                ssize_t count = 0, amount = 0;

                for (count = 0, amount = 0; count < size; ++sized, ++count) {
                    if (0 > (amount = ::read(fd, sized, sizeof(sized_t)))) {
                        LOG_ERROR("...failed on ::read(fd = " << fd << ", sized, sizeof(sized_t) = " << sizeof(sized_t) << ")");
                        return amount;
                    } else {
                        if (1 > amount) {
                            break;
                        }
                    }
                }
                return count;
            }
        }
        return 0;
    }
    virtual ssize_t write(const what_t* what, ssize_t size = -1) {
        const sized_t* sized = 0;

        if ((sized = ((const sized_t*)what)) && (size)) {
            attached_t fd = invalid_fd;

            if (invalid_fd != (fd = this->attached_to())) {
                ssize_t amount = 0;

                if (0 > (size)) {
                    const sized_t sized_endof = ((sized_t)endof);
                    ssize_t count = 0;

                    for (count = 0; sized_endof != (*sized); ++sized, ++count) {
                        if (0 > (amount = ::write(fd, sized, sizeof(sized_t)))) {
                            LOG_ERROR("...failed on ::write(fd = " << fd << ", sized, sizeof(sized_t) = " << sizeof(sized_t) << ")");
                            return amount;
                        }
                    }
                    return count;
                } else {
                    if (0 > (amount = ::write(fd, what, size*sizeof(sized_t)))) {
                        LOG_ERROR("...failed on ::write(fd = " << fd << ", what, size*sizeof(sized_t) = " << size*sizeof(sized_t) << ")");
                        return amount;
                    }
                    return size;
                }
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual operator fd_t() const {
        return this->attached_to();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef filet<void, char> file;

typedef filet<char, char> char_file;
typedef filet<tchar_t, tchar_t> tchar_file;
typedef filet<wchar_t, wchar_t> wchar_file;

typedef filet<byte_t, byte_t> byte_file;
typedef filet<word_t, word_t> word_file;
} // namespace posix 
} // namespace os 
} // namespace nadir 

#endif // _NADIR_OS_POSIX_FILE_HPP 
