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
///   File: Attached.hpp
///
/// Author: $author$
///   Date: 12/22/2018
///////////////////////////////////////////////////////////////////////
#ifndef _PATRONA_IO_MICROSOFT_WINDOWS_CRT_FILE_ATTACHED_HPP
#define _PATRONA_IO_MICROSOFT_WINDOWS_CRT_FILE_ATTACHED_HPP

#include "patrona/io/crt/file/Attached.hpp"

namespace patrona {
namespace io {
namespace microsoft {
namespace windows {
namespace crt {
namespace file {

typedef io::crt::file::Attached::Implements AttachedTImplements;
typedef io::crt::file::Attached AttachedTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: AttachedT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = AttachedTImplements, class TExtends = AttachedTExtends>

class _EXPORT_CLASS AttachedT: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef typename Extends::Attached Attached;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    AttachedT(const AttachedT& copy): Extends(copy), m_mode(0) {
    }
    AttachedT(Attached detached = 0): Extends(detached), m_mode(0) {
    }
    virtual ~AttachedT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetModeIsBinary(bool to = true) {
        Attached detached = 0;
        if ((detached = this->AttachedTo())) {
            int fd = -1;
            if (0 <= (fd = _fileno(detached))) {
                int err = 0, mode = (to)?(_O_BINARY):(_O_TEXT);
                if (0 <= (err = _setmode(fd, mode))) {
                    m_mode = mode;
                    return true;
                } else {
                    LOG_ERROR("...failed " << err << " = _setmode(fd = " << fd << ", mode = " << mode << ")");
                }
            } else {
                LOG_ERROR("...failed " << fd << " = _fileno(detached)");
            }
        }
        return false;
    }
    virtual bool ModeIsBinary() const {
        if (_O_BINARY == (m_mode)) {
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    int m_mode;
}; /// class _EXPORT_CLASS AttachedT
typedef AttachedT<> Attached;

} // namespace file 
} // namespace crt 
} // namespace windows 
} // namespace microsoft 
} // namespace io 
} // namespace patrona 

#endif // _PATRONA_IO_MICROSOFT_WINDOWS_CRT_FILE_ATTACHED_HPP 
