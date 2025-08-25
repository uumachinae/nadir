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
///   File: pipe.hpp
///
/// Author: $author$
///   Date: 12/29/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_MT_POSIX_PIPE_HPP
#define _NADIR_MT_POSIX_PIPE_HPP

#include "nadir/mt/pipe.hpp"
#include "nadir/base/created.hpp"
#include "nadir/io/logger.hpp"

namespace nadir {
namespace mt {
namespace posix {

typedef int pipe_fd_t;
typedef int invalid_pipe_fd_t;
enum { invalid_pipe_fd = -1 };

typedef pipe_fd_t* pipe_attached_t;
typedef int pipe_unattached_t;
enum { pipe_unattached = 0 };

///////////////////////////////////////////////////////////////////////
///  Class: pipet
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0,
 class TImplement = implement_base, class TExtend = base,
 class TReader = io::readert<TWhat, TSized, TEnd, VEnd, TImplement>,
 class TWriter = io::writert<TWhat, TSized, TEnd, VEnd, TImplement>,
 class TStream = io::streamt<TWhat, TSized, TEnd, VEnd, TReader, TWriter>,
 class TCreator = creatort<TStream>,
 class TAttacher = attachert
 <pipe_attached_t, pipe_unattached_t, pipe_unattached, TCreator>,
 class TAttached = attachedt
 <pipe_attached_t, pipe_unattached_t, pipe_unattached, TAttacher, TExtend>,
 class TCreated = createdt
 <pipe_attached_t, pipe_unattached_t, pipe_unattached, TAttacher, TAttached>,
 class TImplements = TAttacher, class TExtends = TCreated>

class _EXPORT_CLASS pipet: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef pipe_fd_t fd_t;
    typedef invalid_pipe_fd_t invalid_fd_t;
    enum { invalid_fd = invalid_pipe_fd };

    typedef typename TImplements::attached_t attached_t;
    typedef typename TImplements::unattached_t unattached_t;
    enum { unattached = TImplements::unattached };

    typedef typename TImplements::what_t what_t;
    typedef typename TImplements::sized_t sized_t;
    typedef typename TImplements::end_t endof_t;
    enum { endof = TImplements::end };
    
    typedef int end_t;
    enum { in = 0, out = 1, ends = 2 };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    pipet(attached_t attached, bool is_created)
    : Extends(attached, is_created), invalid_fd_(invalid_fd) {
    }
    pipet(attached_t attached)
    : Extends(attached), invalid_fd_(invalid_fd) {
    }
    pipet(): invalid_fd_(invalid_fd) {
    }
    virtual ~pipet() {
        if (!(this->destroyed())) {
            const create_exception e(destroy_failed);
            LOG_ERROR("...throwing create_exception e(destroy_failed)...");
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create_inherited(end_t end) {
        if ((end >= in) && (end <= out)) {
            if ((create())) {
                return true;
            }
        }
        return false;
    }
    virtual bool create() {
        if ((this->destroyed())) {
            int err = 0;
            
            LOG_DEBUG("::pipe(ends_)...");
            if (!(err = ::pipe(ends_))) {
                this->attach_created(ends_);
                return true;
            } else {
                LOG_ERROR("failed errno = " << errno << " on ::pipe(ends_)");
            }
        }
        return false;
    }
    virtual bool destroy() {
        pipe_attached_t detached = 0;

        if ((detached = this->detach())) {
            bool success = true;
            fd_t fd = invalid_fd;
            int err = 0;

            for (end_t end = in; end < ends; ++end) {
                if (invalid_fd != (fd = detached[end])) {
                    LOG_DEBUG("::close(fd = " << fd << ")...");
                    if ((err = ::close(fd))) {
                        LOG_ERROR("...failed errno = " << errno << " on ::close(fd = " << fd << ")");
                        success = false;
                    }
                }
            }
            return success;
        }
        return false;
    }
    virtual bool close(end_t end) {
        if ((end >= in) && (end <= out)) {
            pipe_attached_t detached = 0;

            if ((detached = this->attached_to())) {
                fd_t fd = invalid_fd;

                if (invalid_fd != (fd = detached[end])) {
                    int err = 0;

                    detached[end] = invalid_fd;
                    LOG_DEBUG("::close(fd = " << fd << ")...");
                    if ((err = ::close(fd))) {
                        LOG_ERROR("...failed errno = " << errno << " on close(fd = " << fd << ")");
                    } else {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    virtual bool close_in() {
        return close(in);
    }
    virtual bool close_out() {
        return close(out);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t read(what_t* what, size_t size) {
        sized_t* sized = 0;

        if ((sized = ((sized_t*)what)) && (size)) {
            pipe_attached_t detached = 0;

            if ((detached = this->attached_to())) {
                fd_t fd = invalid_fd;

                if (invalid_fd != (fd = detached[in])) {
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
        }
        return 0;
    }
    virtual ssize_t write(const what_t* what, ssize_t size = -1) {
        const sized_t* sized = 0;

        if ((sized = ((const sized_t*)what)) && (size)) {
            pipe_attached_t detached = 0;

            if ((detached = this->attached_to())) {
                fd_t fd = invalid_fd;

                if (invalid_fd != (fd = detached[out])) {
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
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual fd_t& in_end() const {
        return ((fd_t&)ends_[in]);
    }
    virtual fd_t& out_end() const {
        return ((fd_t&)ends_[out]);
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual fd_t& operator[](end_t end) const {
        if ((end >= in) && (end <= out)) {
            return ((fd_t&)ends_[end]);
        }
        return ((fd_t&)invalid_fd_);
    }
    virtual operator pipe_attached_t() const {
        return this->attached_to();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    fd_t invalid_fd_;
    fd_t ends_[ends];
};
typedef pipet<void, char> pipe;

typedef pipet<char, char> char_pipe;
typedef pipet<tchar_t, tchar_t> tchar_pipe;
typedef pipet<wchar_t, wchar_t> wchar_pipe;

typedef pipet<byte_t, byte_t> byte_pipe;
typedef pipet<word_t, word_t> word_pipe;
} // namespace posix 
} // namespace mt 
} // namespace nadir 

#endif // _NADIR_MT_POSIX_PIPE_HPP 

        

