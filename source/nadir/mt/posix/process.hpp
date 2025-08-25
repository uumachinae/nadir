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
///   File: process.hpp
///
/// Author: $author$
///   Date: 12/30/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_MT_POSIX_PROCESS_HPP
#define _NADIR_MT_POSIX_PROCESS_HPP

#include "nadir/mt/process.hpp"
#include "nadir/mt/posix/pipe.hpp"
#include "nadir/os/posix/file.hpp"
#include "nadir/base/created.hpp"
#include "nadir/base/waited.hpp"
#include "nadir/io/logger.hpp"

#include "thirdparty/gnu/glibc/posix/execvpe.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

namespace nadir {
namespace mt {
namespace posix {

typedef int invalid_pid_t;
enum { invalid_pid = -1};

typedef pid_t process_attached_t;
typedef int process_unattached_t;
enum { process_unattached = -1};

///////////////////////////////////////////////////////////////////////
///  Class: processt
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0,
 class TImplement = implement_base, class TExtend = base,
 class TReader = io::readert<TWhat, TSized, TEnd, VEnd, TImplement>,
 class TWriter = io::writert<TWhat, TSized, TEnd, VEnd, TImplement>,
 class TStream = io::streamt<TWhat, TSized, TEnd, VEnd, TReader, TWriter>,
 class TFile = nadir::os::posix::filet
 <TWhat, TSized, TEnd, VEnd, TImplement, TExtend, TReader, TWriter>,
 class TPipe = pipet
 <TWhat, TSized, TEnd, VEnd, TImplement, TExtend, TReader, TWriter>,
 class TWaited = waitedt<wait_exception, TImplement>,
 class TCreator = creatort<TWaited>,
 class TAttacher = attachert
 <process_attached_t, process_unattached_t, process_unattached, TCreator>,
 class TAttached = attachedt
 <process_attached_t, process_unattached_t, process_unattached, TAttacher, TExtend>,
 class TCreated = createdt
 <process_attached_t, process_unattached_t, process_unattached, TAttacher, TAttached>,
 class TImplements = TAttacher, class TExtends = TCreated>

class _EXPORT_CLASS processt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef typename TFile::fd_t fd_t;
    typedef typename TFile::invalid_fd_t invalid_fd_t;
    enum { invalid_fd = TFile::invalid_fd };

    typedef typename TPipe::fd_t pipe_fd_t;
    typedef typename TPipe::invalid_fd_t invalid_pipe_fd_t;
    enum { invalid_pipe_fd = TPipe::invalid_fd };

    typedef typename TImplements::attached_t attached_t;
    typedef typename TImplements::unattached_t unattached_t;
    enum { unattached = TImplements::unattached };

    typedef char char_t;
    typedef TWhat what_t;
    typedef TSized sized_t;
    typedef TEnd end_t;
    enum { end = VEnd };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    processt(attached_t attached, bool is_created)
    : Extends(attached, is_created), is_forked_(false) {
    }
    processt(attached_t attached)
    : Extends(attached), is_forked_(false) {
    }
    processt(): is_forked_(false) {
    }
    virtual ~processt() {
        if (!(this->destroyed())) {
            const create_exception e(destroy_failed);
            LOG_ERROR("...throwing create_exception e(destroy_failed)...");
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create
    (const char_t* path, char_t** argv, char_t** env,
     int* fdup, int** pdup, bool is_detached = false) {
        if ((this->destroyed())) {
            pid_t pid = ((pid_t)invalid_pid);

            if (0 < (pid = this->fork(path, argv, env, fdup, pdup, is_detached))) {
                this->attach_created(pid);
                return true;
            }
        }
        return false;
    }
    virtual bool destroy() {
        if ((this->joined())) {
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual pid_t fork
    (const char_t* path, char_t** argv, char_t** env,
     int* fdup, int** pdup, bool is_detached = false) {
        pid_t pid = ((pid_t)invalid_pid);

        LOG_DEBUG("::fork()...");
        if (0 < (pid = ::fork())) {
            LOG_DEBUG("...pid = " << pid << " on ::fork()");
        } else {
            if (0 > (pid)) {
                LOG_ERROR("...failed errno = " << errno << " on ::fork()");
            } else {
                int err = 1;
                LOG_DEBUG("...pid = " << pid << " on ::fork() chlid process...");
                this->exec(path, argv, env, fdup, pdup, is_detached);
                LOG_DEBUG("...chlid process");
                exit(err);
            }
        }
        return pid;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool exec
    (const char_t* path, char_t** argv, char_t** env,
     int* fdup, int** pdup, bool is_detached = false) {
        if ((path) && (argv)) {
            int err = 0;

            if ((fdup)) {
                int fd = 0;
                for (int i = 0; (i < 3) && (fd = fdup[i]); ++i) {
                    LOG_DEBUG("::dup2(" << fd << ", " << i << ")...");
                    if (0 > (err = dup2(fd, i))) {
                        LOG_ERROR("...failed errno = " << errno << " on ::dup2(" << fd << ", " << i << ")");
                        return false;
                    } else {
                        ::close(fd);
                    }
                }
            }

            if ((pdup)) {
                int* p = 0;
                for (int i = 0; (i < 3) && (p = pdup[i]); ++i) {
                    int fd = p[(i)?(1):(0)];
                    LOG_DEBUG("::dup2(" << fd << ", " << i << ")...");
                    if (0 > (err = dup2(fd, i))) {
                        LOG_ERROR("...failed errno = " << errno << " on ::dup2(" << fd << ", " << i << ")");
                        return false;
                    } else {
                        ::close(p[0]);
                        ::close(p[1]);
                    }
                }
            }

            if ((env)) {
                LOG_TRACE("::execvpe(\"" << path << "\", ...)...");
                if ((err = ::execvpe(path, argv, env))) {
                    LOG_ERROR("...failed errno = " << errno << " on ::execvpe(\"" << path << "\",...)");
                }
            } else {
                LOG_TRACE("::execvp(\"" << path << "\", ...)...");
                if ((err = ::execvp(path, argv))) {
                    LOG_ERROR("...failed errno = " << errno << " on ::execvp(\"" << path << "\",...)");
                }
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool joined() {
        if ((this->is_forked())) {
            return this->join();
        }
        return true;
    }
    virtual bool join() {
        return this->wait();
    }
    virtual wait_status try_join() {
        return this->try_wait();
    }
    virtual wait_status timed_join(mseconds_t milliseconds) {
        return this->timed_wait(milliseconds);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool wait() {
        pid_t pid = ((pid_t)invalid_pid);

        this->set_is_forked(false);
        if (((pid_t)invalid_pid) != (pid = this->attached_to())) {
            int options = 0, status = 0;

            LOG_DEBUG("::waitpid(" << pid << ",...)...");
            if (!(pid != ::waitpid(pid, &status, options))) {
                LOG_DEBUG("...::waitpid(" << pid << ",...)");
                return true;
            } else {
                LOG_ERROR("...failed errno = " << errno << " on ::waitpid(" << pid << ",...)");
            }
        }
        return false;
    }
    virtual wait_status untimed_wait() {
        pid_t pid = ((pid_t)invalid_pid);

        if (((pid_t)invalid_pid) != (pid = this->attached_to())) {
            int options = 0, status = 0;

            LOG_DEBUG("::waitpid(" << pid << ",...)...");
            if (!(pid != waitpid(pid, &status, options))) {
                LOG_DEBUG("...::waitpid(" << pid << ",...)");
                this->set_is_forked(false);
                return wait_success;
            } else {
                if (EBUSY != (errno)) {
                    LOG_ERROR("...failed errno = " << errno << " on ::waitpid(" << pid << ",...)");
                    this->set_is_forked(false);
                } else {
                    LOG_ERROR("...unexpected busy errno = " << errno << " on ::waitpid(" << pid << ",...)");
                    return wait_busy;
                }
            }
        }
        return wait_failed;
    }
    virtual wait_status try_wait() {
        pid_t pid = ((pid_t)invalid_pid);

        if (((pid_t)invalid_pid) != (pid = this->attached_to())) {
            int options = WNOHANG, status = 0;

            LOG_TRACE("::waitpid(" << pid << ",...)...");
            if (!(pid != waitpid(pid, &status, options))) {
                LOG_TRACE("...::waitpid(" << pid << ",...)");
                this->set_is_forked(false);
                return wait_success;
            } else {
                if (EBUSY != (errno)) {
                    LOG_ERROR("...failed errno = " << errno << " on ::waitpid(" << pid << ",...)");
                    this->set_is_forked(false);
                } else {
                    LOG_TRACE("...busy errno = " << errno << " on ::waitpid(" << pid << ",...)");
                    return wait_busy;
                }
            }
        }
        return wait_failed;
    }
    virtual wait_status timed_wait(mseconds_t milliseconds) {
        LOG_ERROR("...failed ::timed_waitpid(..., " << milliseconds << ") unavailable");
        return wait_invalid;
    }


    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual pid_t attach_created(pid_t detached, bool is_created = true) {
        pid_t attached = Extends::attach_created(detached);
        this->set_is_forked(is_created);
        return attached;
    }
    virtual pid_t detach_created(bool& is_created) {
        pid_t detached = Extends::detach_created(is_created);
        this->set_is_forked(false);
        return detached;
    }
    virtual pid_t detach() {
        pid_t detached = Extends::detach();
        this->set_is_forked(false);
        return detached;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_is_forked(bool to = true) {
        is_forked_ = to;
        return is_forked_;
    }
    virtual bool is_forked() const {
        return is_forked_;
    }
    virtual bool is_joined() const {
        return !is_forked_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool is_forked_;
};
typedef processt<void, char> process;

typedef processt<char, char> char_process;
typedef processt<tchar_t, tchar_t> tchar_process;
typedef processt<wchar_t, wchar_t> wchar_process;

typedef processt<byte_t, byte_t> byte_process;
typedef processt<word_t, word_t> word_process;

} // namespace posix 
} // namespace mt 
} // namespace nadir 

#endif // _NADIR_MT_POSIX_PROCESS_HPP 
