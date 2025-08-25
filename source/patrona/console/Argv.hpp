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
///   File: Argv.hpp
///
/// Author: $author$
///   Date: 12/22/2018
///////////////////////////////////////////////////////////////////////
#ifndef _PATRONA_CONSOLE_ARGV_HPP
#define _PATRONA_CONSOLE_ARGV_HPP

#include "patrona/io/Writer.hpp"
#include "patrona/base/Array.hpp"

namespace patrona {
namespace console {

///////////////////////////////////////////////////////////////////////
///  Class: ArgvT
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char,
 class TExtends = ArrayT<TChar*>,
 class TImplements = ArrayTImplements>

class _EXPORT_CLASS ArgvT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef TChar* arg_t;
    typedef TChar char_t;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ArgvT(size_t argc, arg_t* argv): m_end((arg_t)0) {
        Assign(argc, argv);
    }
    ArgvT(): m_end((arg_t)0) {
        Extends::Assign(&m_end, 1);
    }
    virtual ~ArgvT() {
        Free();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::Assign;
    virtual ArgvT& Assign(size_t argc, arg_t* argv) {
        Free();
        Extends::Assign(&m_end, 1);
        if (0 < (argc)) {
            Extends::Assign(argv, argc);
            Extends::Append(&m_end, 1);
            Allocate();
        }
        return *this;
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t Allocate() {
        size_t count = 0;
        arg_t* arg = 0;
        if ((arg = this->Elements())) {
            char_t *chars = 0, *chars2 = 0;
            size_t length = 0, size = 0;
            for (chars = (*arg); chars; chars = *(++arg)) {
                size = this->NewSize((length = Count(chars))+1);
                if ((chars2 = new char_t[size])) {
                    Copy(chars2, chars, length);
                }
                *arg = chars2;
            }
        }
        return count;
    }
    virtual size_t Free() {
        size_t count = 0;
        arg_t* arg = 0;
        if ((arg = this->Elements())) {
            char_t *chars = 0;
            size_t length = 0;
            for (length = this->Length(); length; --length, ++arg) {
                if ((chars = (*arg))) {
                    delete[] chars;
                    chars = 0;
                }
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t Count(char_t* arg) const {
        size_t count = 0;
        if (arg) {
            while (*(arg++)) {
                ++count;
            }
        }
        return count;
    }
    virtual size_t Copy
    (char_t* to, const char_t* from, size_t length) const {
        size_t count = 0;
        if ((to) && (from)) {
            for (count = 0; length > 0; --length, count++) {
                (*to++) = (*from++);
            }
            to[length] = 0;
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    arg_t m_end;
};
typedef ArgvT<char> Argv;
typedef ArgvT<tchar_t> TArgv;
typedef ArgvT<wchar_t> WArgv;

typedef ImplementBase ArgvWriterTImplements;
typedef Base ArgvWriterTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: ArgvWriterT
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char,
 class TArgv = ArgvT<TChar>, class TWriter = io::WriterT<TChar, void>,
 class TImplements = ArgvWriterTImplements, class TExtends = ArgvWriterTExtends>

class _EXPORT_CLASS ArgvWriterT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef TArgv Argv;
    typedef TWriter Writer;
    typedef TChar* arg_t;
    typedef TChar char_t;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ArgvWriterT(Writer& writer): cr_((char_t)'\r'), lf_((char_t)'\n'), m_writer(writer) {
    }
    virtual ~ArgvWriterT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t Write(const Argv& argv) {
        return Write(argv.Elements());
    }
    virtual size_t Write(char_t** argv) {
        size_t count = 0, amount = 0;
        if ((argv) && (*argv)) {
            for (char_t* arg = (*argv); arg; arg = *(++argv)) {
                if (0 <= (amount = m_writer.Write(arg))) {
                    count += amount;
                    if (0 < (amount = m_writer.Write(&cr_, 1))) {
                        count += amount;
                        if (0 < (amount = m_writer.Write(&lf_, 1))) {
                            count += amount;
                        } else {
                            return amount;
                        }
                    } else {
                        return amount;
                    }
                } else {
                    return amount;
                }
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    /*static*/ const char_t cr_/* = ((char_t)'\r')*/;
    /*static*/ const char_t lf_/* = ((char_t)'\n')*/;
    Writer& m_writer;
};
typedef ArgvWriterT<char> ArgvWriter;
typedef ArgvWriterT<tchar_t> TArgvWriter;
typedef ArgvWriterT<wchar_t> WArgvWriter;

} // namespace console 
} // namespace patrona 

#endif // _PATRONA_CONSOLE_ARGV_HPP 
