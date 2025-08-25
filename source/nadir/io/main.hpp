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
///   File: main.hpp
///
/// Author: $author$
///   Date: 1/15/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_IO_MAIN_HPP
#define _NADIR_IO_MAIN_HPP

#include "nadir/console/main.hpp"
#include "nadir/io/stream.hpp"

namespace nadir {
namespace io {
namespace main {

///////////////////////////////////////////////////////////////////////
///  Class: readert
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0,
 class TChars = charst<TSized, TEnd, VEnd>,
 class TReader = io::readert<TWhat, TSized, TEnd, VEnd>,
 class TMain = console::maint<TSized>,
 class TImplements = TReader, class TExtends = base>

class _EXPORT_CLASS readert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TMain main_t;
    typedef TChars chars_t;
    typedef TWhat what_t;
    typedef TSized sized_t;
    typedef TEnd end_t;
    enum { end = VEnd };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    readert(main_t& main): main_(main) {
    }
    virtual ~readert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t read(what_t* what, size_t size) {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t seek(ssize_t offset, int whence) {
        return -1;
    }
    virtual ssize_t tell() {
        return -1;
    }
    virtual ssize_t eof() {
        return -1;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    main_t& main_;
};
typedef readert<void, char, int, 0> reader;

///////////////////////////////////////////////////////////////////////
///  Class: writert
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0,
 class TChars = charst<TSized, TEnd, VEnd>,
 class TWriter = io::writert<TWhat, TSized, TEnd, VEnd>,
 class TMain = console::maint<TSized>,
 class TImplements = TWriter, class TExtends = base>

class _EXPORT_CLASS writert: virtual public TImplements {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TMain main_t;
    typedef TWhat what_t;
    typedef TSized sized_t;
    typedef TSized char_t;
    typedef TEnd end_t;
    enum { end = VEnd };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    writert(main_t& main): main_(main) {
    }
    virtual ~writert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t write(const what_t* what, ssize_t size = -1) {
        return 0;
    }
    virtual ssize_t flush() {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t writefv(const sized_t* format, va_list va) {
        ssize_t count = 0;
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    main_t& main_;
};
typedef writert<void, char, int, 0> writer;

namespace argv {
///////////////////////////////////////////////////////////////////////
///  Class: writert
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0,
 class TChars = charst<TSized, TEnd, VEnd>,
 class TWriter = io::writert<TWhat, TSized, TEnd, VEnd>,
 class TImplements = implement_base, class TExtends = base>

class _EXPORT_CLASS writert: virtual public TImplements {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TWriter writer_t;
    typedef TWhat what_t;
    typedef TSized sized_t;
    typedef TSized char_t;
    typedef TEnd end_t;
    enum { end = VEnd };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    writert(): cr_((char_t)'\r'), lf_((char_t)'\n') {
    }
    virtual ~writert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t write(writer_t& writer, int argc, char_t** argv) {
        ssize_t count = 0, amount = 0;
        if ((argv)) {
            const char_t* chars = 0;
            size_t length = 0;
            for (int i = 0; i < argc; ++i) {
                if ((chars = argv[i]) && (0 < (length = chars_t::count(chars)))) {
                    if (0 < (amount = writer.write(chars, length))) {
                        count += amount;
                        if (0 < (amount = writer.write(&cr_, 1))) {
                            count += amount;
                            if (0 < (amount = writer.write(&lf_, 1))) {
                                count += amount;
                            }
                        }
                    }
                }
            }
        }
        if (0 < (amount = writer.write(&cr_, 1))) {
            count += amount;
            if (0 < (amount = writer.write(&lf_, 1))) {
                count += amount;
            }
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    const char_t cr_, lf_;
};
typedef writert<void, char, int, 0> writer;
} // namespace argv

namespace in {
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS reader: public main::reader {
public:
    typedef main::reader Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    reader(main_t& main): Extends(main) {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t read(what_t* what, size_t size) {
        sized_t* sized = 0;
        if ((sized = ((sized_t*)what)) && (size)) {
            return main_.in(sized, size);
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
} // namespace in

namespace out {
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS writer: public main::writer {
public:
    typedef main::writer Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    writer(main_t& main): Extends(main) {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t write(const what_t* what, ssize_t size = -1) {
        const sized_t* sized = 0;
        if ((sized = ((const sized_t*)what)) && (size)) {
            return main_.out(sized, size);
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
} // namespace out

namespace err {
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS writer: public main::writer {
public:
    typedef main::writer Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    writer(main_t& main): Extends(main) {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t write(const what_t* what, ssize_t size = -1) {
        const sized_t* sized = 0;
        if ((sized = ((const sized_t*)what)) && (size)) {
            return main_.err(sized, size);
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
} // namespace err

} // namespace main
} // namespace io 
} // namespace nadir 

#endif // _NADIR_IO_MAIN_HPP 
