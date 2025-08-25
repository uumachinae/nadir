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
///   File: Reader.hpp
///
/// Author: $author$
///   Date: 12/22/2018
///////////////////////////////////////////////////////////////////////
#ifndef _PATRONA_IO_CRT_FILE_READER_HPP
#define _PATRONA_IO_CRT_FILE_READER_HPP

#include "patrona/io/crt/file/Stream.hpp"

namespace patrona {
namespace io {
namespace crt {
namespace file {

typedef StreamTImplements ReaderTImplements;
typedef Stream ReaderTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: ReaderT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = ReaderTImplements, class TExtends = ReaderTExtends>

class _EXPORT_CLASS ReaderT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef typename Extends::attached_t attached_t;
    typedef typename Extends::sized_t sized_t;
    typedef typename Extends::what_t what_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ReaderT(attached_t attachedTo = 0, bool isOpen = false)
    : Extends(attachedTo, isOpen) {
    }
    ReaderT(const ReaderT& copy): Extends(copy) {
    }
    virtual ~ReaderT() {
        if (!(this->Closed())) {
            OpenException e(CloseFailed);
            PATRONA_LOG_ERROR("...throw (OpenException e(CloseFailed))...");
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::Open;
    virtual bool Open(const char* name) {
        return this->Open(name, file::ModeReadBinary);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* Mode(const file::Mode& mode) const {
        switch (mode) {
        case file::ModeBinary: return this->ModeReadBinary();
        }
        return Extends::Mode(mode);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* ModeWrite() const {
        return 0;
    }
    virtual const char* ModeAppend() const {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char* ModeWriteBinary() const {
        return 0;
    }
    virtual const char* ModeAppendBinary() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write(const what_t* what, size_t size) {
        return 0;
    }
};
typedef ReaderT<> Reader;

} // namespace file 
} // namespace crt 
} // namespace io 
} // namespace patrona 

#endif // _PATRONA_IO_CRT_FILE_READER_HPP 
