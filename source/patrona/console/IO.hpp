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
///   File: IO.hpp
///
/// Author: $author$
///   Date: 12/22/2018
///////////////////////////////////////////////////////////////////////
#ifndef _PATRONA_CONSOLE_IO_HPP
#define _PATRONA_CONSOLE_IO_HPP

#include "patrona/io/Writer.hpp"
#include "patrona/io/Reader.hpp"
#include "patrona/base/Locked.hpp"

namespace patrona {
namespace console {

typedef Locked IOTImplements;
///////////////////////////////////////////////////////////////////////
///  Class: IOT
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char,
 typename TEndChar = TChar, TEndChar VEndChar = 0,
 class TImplements = IOTImplements>

class _EXPORT_CLASS IOT: virtual public TImplements {
public:
    typedef TImplements Implements;

    typedef TChar char_t;
    typedef TEndChar endchar_t;
    static const TEndChar endchar = VEndChar;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OutLn(const char_t* chars, size_t length) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t OutLn(const char_t* chars) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t OutLn() {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t Out(const char_t* chars, size_t length) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t Out(const char_t* chars) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t OutF(const char_t* chars, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, chars);
        count = OutFV(chars, va);
        va_end(va);
        return count;
    }
    virtual ssize_t OutFV(const char_t* chars, va_list va) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t OutL(const char_t* chars, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, chars);
        count = OutLV(chars, va);
        va_end(va);
        return count;
    }
    virtual ssize_t OutLV(const char_t* chars, va_list va) {
        ssize_t count = 0, amount = 0;
        for (count = 0; chars; count += amount) {
            if (0 > (amount = this->Out(chars))) {
                return amount;
            }
            chars = va_arg(va, const char_t*);
        }
        return count;
    }
    virtual ssize_t OutFlush() {
        ssize_t count = 0;
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t ErrLn(const char_t* chars, size_t length) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t ErrLn(const char_t* chars) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t ErrLn() {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t Err(const char_t* chars, size_t length) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t Err(const char_t* chars) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t ErrF(const char_t* chars, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, chars);
        count = ErrFV(chars, va);
        va_end(va);
        return count;
    }
    virtual ssize_t ErrFV(const char_t* chars, va_list va) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t ErrL(const char_t* chars, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, chars);
        count = ErrLV(chars, va);
        va_end(va);
        return count;
    }
    virtual ssize_t ErrLV(const char_t* chars, va_list va) {
        ssize_t count = 0, amount = 0;
        for (count = 0; chars; count += amount) {
            if (0 > (amount = this->Err(chars))) {
                return amount;
            }
            chars = va_arg(va, const char_t*);
        }
        return count;
    }
    virtual ssize_t ErrFlush() {
        ssize_t count = 0;
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t InLn(char_t* chars, size_t length) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t InLn(char_t* chars) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t InLn() {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t In(char_t* chars, size_t length) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t In(char_t* chars) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t InF(char_t* chars, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, chars);
        count = InFV(chars, va);
        va_end(va);
        return count;
    }
    virtual ssize_t InFV(char_t* chars, va_list va) {
        ssize_t count = 0;
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef IOT<char> IO;
typedef IOT<tchar_t> TIO;
typedef IOT<wchar_t> WIO;

typedef Base OutIOWriterTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: OutIOWriterT
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char,
 typename TEndChar = TChar, TEndChar VEndChar = 0,
 class TIO = IOT<TChar, TEndChar, VEndChar>,
 class TImplements = io::CharWriterT<TChar, void>,
 class TExtends = OutIOWriterTExtends>

class _EXPORT_CLASS OutIOWriterT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef TIO IO;
    typedef typename Implements::sized_t sized_t;
    typedef typename Implements::what_t what_t;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    OutIOWriterT(IO& io): m_io(io) {
    }
    virtual ~OutIOWriterT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write(const what_t* what, size_t size) {
        ssize_t count = 0;
        count = m_io.Out((const sized_t*)what, size);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    IO& m_io;
};
typedef OutIOWriterT<char> OutIOWriter;
typedef OutIOWriterT<tchar_t> TOutIOWriter;
typedef OutIOWriterT<wchar_t> WOutIOWriter;

typedef Base InIOReaderTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: InIOReaderT
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char,
 typename TEndChar = TChar, TEndChar VEndChar = 0,
 class TIO = IOT<TChar, TEndChar, VEndChar>,
 class TImplements = io::ReaderT<TChar, void>,
 class TExtends = InIOReaderTExtends>

class _EXPORT_CLASS InIOReaderT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef TIO IO;
    typedef typename Implements::sized_t sized_t;
    typedef typename Implements::what_t what_t;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    InIOReaderT(IO& io): m_io(io) {
    }
    virtual ~InIOReaderT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(what_t* what, size_t size) {
        ssize_t count = 0;
        count = m_io.In((sized_t*)what, size);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    IO& m_io;
};
typedef InIOReaderT<char> InIOReader;
typedef InIOReaderT<tchar_t> TInIOReader;
typedef InIOReaderT<wchar_t> WInIOReader;

} // namespace console
} // namespace patrona 

#endif // _PATRONA_CONSOLE_IO_HPP 
