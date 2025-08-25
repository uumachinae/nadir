///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2018 $organization$
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
///   File: Stream.hpp
///
/// Author: $author$
///   Date: 12/22/2018
///////////////////////////////////////////////////////////////////////
#ifndef _PATRONA_IO_CRT_FILE_STREAM_HPP
#define _PATRONA_IO_CRT_FILE_STREAM_HPP

#include "patrona/io/crt/file/Mode.hpp"
#include "patrona/io/Stream.hpp"
#include "patrona/io/Writer.hpp"
#include "patrona/io/Reader.hpp"
#include "patrona/base/Opened.hpp"
#include "patrona/base/Attached.hpp"
#include "patrona/io/Logger.hpp"

namespace patrona {
namespace io {
namespace crt {
namespace file {

typedef FILE* StreamAttachedTo;
typedef patrona::OpenerT<patrona::io::Stream> StreamOpener;
typedef patrona::AttacherT<StreamAttachedTo, int, 0, StreamOpener> StreamAttacher;
typedef patrona::AttachedT<StreamAttachedTo, int, 0, StreamAttacher, Base> StreamAttached;
typedef patrona::OpenedT<StreamAttachedTo, int, 0, StreamAttacher, StreamAttached> StreamOpened;

typedef StreamAttacher StreamTImplements;
typedef StreamOpened StreamTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: StreamT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = StreamTImplements, class TExtends = StreamTExtends>

class _EXPORT_CLASS StreamT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef typename Extends::Attached attached_t;
    typedef typename Implements::Implements::what_t what_t;
    typedef typename Implements::Implements::sized_t sized_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    StreamT(attached_t attachedTo = 0, bool isOpen = false)
    : Extends(attachedTo, isOpen) {
    }
    StreamT(const StreamT& copy)
    : Extends(copy.AttachedTo()) {
    }
    virtual ~StreamT() {
        if (!(this->Closed())) {
            OpenException e(CloseFailed);
            PATRONA_LOG_ERROR("...throw (OpenException e(CloseFailed))...");
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Open(const char* name, const file::Mode& mode) {
        return Open(name, Mode(mode));
    }
    virtual bool Open(const char* name, const char* mode) {
        FILE* detached = 0;
        if ((detached = OpenAttached(name, mode))) {
            this->SetIsOpen();
            return true;
        }
        return false;
    }
    virtual bool Close() {
        FILE* detached = 0;
        if ((detached = this->Detach())) {
            if ((CloseDetached(detached))) {
                return true;
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual FILE* OpenAttached(const char* name, const file::Mode& mode) {
        return OpenAttached(name, Mode(mode));
    }
    virtual FILE* OpenAttached(const char* name, const char* mode) {
        if ((this->Closed())) {
            FILE* detached = 0;
            if ((detached = OpenDetached(name, mode))) {
                this->Attach(detached);
            }
            return detached;
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual FILE* OpenDetached(const char* name, const file::Mode& mode) const {
        return OpenDetached(name, Mode(mode));
    }
    virtual FILE* OpenDetached(const char* name, const char* mode) const {
        if ((name) && (name[0]) && (mode) && (mode[0])) {
            FILE* detached = 0;
            PATRONA_LOG_DEBUG("fopen(name = " << name << ", mode = " << mode << ")...");
            if ((detached = fopen(name, mode))) {
                return detached;
            } else {
                PATRONA_LOG_DEBUG("...failed errno = " << errno << " on fopen(name = " << name << ", mode = " << mode << ")");
            }
        }
        return 0;
    }
    virtual bool CloseDetached(FILE* detached) const {
        if ((detached)) {
            int err = 0;
            PATRONA_LOG_DEBUG("fclose(detached)...");
            if (!(err = fclose(detached))) {
                return true;
            } else {
                PATRONA_LOG_ERROR("...failed errno = " << errno << " on fclose(detached)");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(what_t* what, size_t size) {
        FILE* f = 0;
        if ((f = this->AttachedTo()) && (what) && (0 < (size))) {
            ssize_t count = 0;
            PATRONA_LOG_TRACE("fread(what, " << sizeof(sized_t) << ", " << size << ", f)...")
            if (size > (count = fread(what, sizeof(sized_t), size, f))) {
                PATRONA_LOG_ERROR("...failed " << count << " on fread(what, " << sizeof(sized_t) << ", " << size << ", f)")
            }
            return count;
        }
        return 0;
    }
    virtual ssize_t Write(const what_t* what, size_t size) {
        FILE* f = 0;
        if ((f = this->AttachedTo()) && (what) && (0 < (size))) {
            ssize_t count = 0;
            PATRONA_LOG_TRACE("fwrite(what, " << sizeof(sized_t) << ", " << size << ", f)...")
            if (size > (count = fwrite(what, sizeof(sized_t), size, f))) {
                PATRONA_LOG_ERROR("...failed " << count << " on fwrite(what, " << sizeof(sized_t) << ", " << size << ", f)")
            }
            return count;
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* Mode(const file::Mode& mode) const {
        switch (mode) {
        case file::ModeRead: return this->ModeRead();
        case file::ModeWrite: return this->ModeWrite();
        case file::ModeAppend: return this->ModeAppend();
        case file::ModeReadBinary: return this->ModeReadBinary();
        case file::ModeWriteBinary: return this->ModeWriteBinary();
        case file::ModeAppendBinary: return this->ModeAppendBinary();
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* ModeRead() const {
        const char* mode = PATRONA_IO_CRT_FILE_MODE_READ;
        return mode;
    }
    virtual const char* ModeWrite() const {
        const char* mode = PATRONA_IO_CRT_FILE_MODE_WRITE;
        return mode;
    }
    virtual const char* ModeAppend() const {
        const char* mode = PATRONA_IO_CRT_FILE_MODE_WRITE_APPEND;
        return mode;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char* ModeReadBinary() const {
        const char* mode = PATRONA_IO_CRT_FILE_MODE_READ_BINARY;
        return mode;
    }
    virtual const char* ModeWriteBinary() const {
        const char* mode = PATRONA_IO_CRT_FILE_MODE_WRITE_BINARY;
        return mode;
    }
    virtual const char* ModeAppendBinary() const {
        const char* mode = PATRONA_IO_CRT_FILE_MODE_WRITE_BINARY_APPEND;
        return mode;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef StreamT<> Stream;

typedef patrona::OpenerT<patrona::io::CharStream> CharStreamOpener;
typedef patrona::AttacherT<StreamAttachedTo, int, 0, CharStreamOpener> CharStreamAttacher;
typedef patrona::AttachedT<StreamAttachedTo, int, 0, CharStreamAttacher, Base> CharStreamAttached;
typedef patrona::OpenedT<StreamAttachedTo, int, 0, CharStreamAttacher, CharStreamAttached> CharStreamOpened;
typedef CharStreamAttacher CharStreamImplements;
typedef StreamT<CharStreamImplements, CharStreamOpened> CharStream;

} // namespace file
} // namespace crt 
} // namespace io 
} // namespace patrona 

#endif // _PATRONA_IO_CRT_FILE_STREAM_HPP 
