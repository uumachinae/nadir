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
///   File: Main.hpp
///
/// Author: $author$
///   Date: 12/22/2018
///////////////////////////////////////////////////////////////////////
#ifndef _PATRONA_CONSOLE_MAIN_HPP
#define _PATRONA_CONSOLE_MAIN_HPP

#include "patrona/console/IO.hpp"
#include "patrona/base/Locked.hpp"
#include <iostream>

namespace patrona {
namespace console {

typedef Locked MainTImplements;
typedef Base MainTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: MainT
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char, typename TEndChar = TChar, TEndChar VEndChar = 0,
 class TImplements = IOT<TChar, TEndChar, VEndChar, MainTImplements>,
 class TExtends = MainTExtends>

class _EXPORT_CLASS MainT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TChar char_t;
    typedef TEndChar endchar_t;
    static const TEndChar endchar = VEndChar;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Exception: public Base {
    public:
        enum Reason { MainAlreadyExists, MainUnequalExists, MainShouldExist };
        Exception(Reason which): m_which(which) {}
        virtual Reason Which() { return m_which; }
    protected:
        Reason m_which;
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    MainT(): m_didUsage(false) {
        if ((TheMain())) {
            Exception e(Exception::MainAlreadyExists);
            throw (e);
        } else {
            TheMain() = this;
        }
    }
    virtual ~MainT() {
        MainT* theMain = TheMain();
        if ((theMain)) {
            if ((theMain != this)) {
                Exception e(Exception::MainUnequalExists);
                throw (e);
            } else {
                TheMain() = 0;
            }
        } else {
            Exception e(Exception::MainShouldExist);
            throw (e);
        }
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Run(int argc, char_t**argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int BeforeRun(int argc, char_t**argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int AfterRun(int argc, char_t**argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int operator()(int argc, char_t**argv, char_t** env) {
        int err = 0;
        if (!(err = this->BeforeRun(argc, argv, env))) {
            int err2 = 0;
            if (!(DidUsage())) {
                err = this->Run(argc, argv, env);
            }
            if ((err2 = this->AfterRun(argc, argv, env))) {
                if (!err) err = err2;
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Usage(int argc, char_t**argv, char_t** env) {
        int err = 1;
        return err;
    }
    virtual bool SetDidUsage(bool to = true) {
        return m_didUsage = to;
    }
    virtual bool DidUsage() const {
        return m_didUsage;
    }

public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static int TheMain(int argc, char_t**argv, char_t** env) {
        int err = 1;
        MainT* theMain = 0;
        if ((theMain = TheMain())) {
            err = (*theMain)(argc, argv, env);
        }
        return err;
    }
protected:
    static MainT*& TheMain() {
        static MainT* theMain = 0;
        return theMain;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t ErrLn(const char* chars, size_t length) {
        ssize_t count = this->OutLn(this->OutStdErr(), chars, length);
        return count;
    }
    virtual ssize_t ErrLn(const char* chars) {
        ssize_t count = this->OutLn(this->OutStdErr(), chars);
        return count;
    }
    virtual ssize_t ErrLn() {
        ssize_t count = this->OutLn(this->OutStdErr());
        return count;
    }
    virtual ssize_t Err(const char* chars, size_t length) {
        ssize_t count = this->Out(this->OutStdErr(), chars, length);
        return count;
    }
    virtual ssize_t Err(const char* chars) {
        ssize_t count = this->Out(this->OutStdErr(), chars);
        return count;
    }
    virtual ssize_t ErrF(const char* chars, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, chars);
        count = ErrFV(chars, va);
        va_end(va);
        return count;
    }
    virtual ssize_t ErrFV(const char* chars, va_list va) {
        ssize_t count = this->OutFV(this->OutStdErr(), chars, va);
        return count;
    }
    virtual ssize_t ErrLV(const char* chars, va_list va) {
        ssize_t count = this->OutLV(this->OutStdErr(), chars, va);
        return count;
    }
    virtual ssize_t ErrFlush() {
        ssize_t count = this->OutFlush(this->OutStdErr());
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OutLn(const char* chars, size_t length) {
        ssize_t count = this->OutLn(this->OutStdOut(), chars, length);
        return count;
    }
    virtual ssize_t OutLn(const char* chars) {
        ssize_t count = this->OutLn(this->OutStdOut(), chars);
        return count;
    }
    virtual ssize_t OutLn() {
        ssize_t count = this->OutLn(this->OutStdOut());
        return count;
    }
    virtual ssize_t Out(const char* chars, size_t length) {
        ssize_t count = this->Out(this->OutStdOut(), chars, length);
        return count;
    }
    virtual ssize_t Out(const char* chars) {
        ssize_t count = this->Out(this->OutStdOut(), chars);
        return count;
    }
    virtual ssize_t OutF(const char* chars, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, chars);
        count = OutFV(chars, va);
        va_end(va);
        return count;
    }
    virtual ssize_t OutFV(const char* chars, va_list va) {
        ssize_t count = this->OutFV(this->OutStdOut(), chars, va);
        return count;
    }
    virtual ssize_t OutLV(const char* chars, va_list va) {
        ssize_t count = this->OutLV(this->OutStdOut(), chars, va);
        return count;
    }
    virtual ssize_t OutFlush() {
        ssize_t count = this->OutFlush(this->OutStdOut());
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OutLn(FILE* out, const char* chars, size_t length) const {
        ssize_t count = 0, amount = 0;
        if (0 <= (amount = this->Out(out, chars, length))) {
            count += amount;
        } else {
            return amount;
        }
        if (0 < (amount = OutLn(out))) {
            count += amount;
        } else {
            return amount;
        }
        return count;
    }
    virtual ssize_t OutLn(FILE* out, const char* chars) const {
        ssize_t count = 0, amount = 0;
        if (0 <= (amount = this->Out(out, chars))) {
            count += amount;
        } else {
            return amount;
        }
        if (0 < (amount = OutLn(out))) {
            count += amount;
        } else {
            return amount;
        }
        return count;
    }
    virtual ssize_t OutLn(FILE* out) const {
        ssize_t count = this->Out(out, "\n", 1);
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Out(FILE* out, const char* chars, size_t length) const {
        ssize_t count = 0, amount = 0;
        if ((out) && (chars) && (length)) {
            if (0 < (amount = fwrite(chars, 1,length, out))) {
                count += amount;
            } else {
                return amount;
            }
        }
        return count;
    }
    virtual ssize_t Out(FILE* out, const char* chars) const {
        ssize_t count = 0, amount = 0;
        if ((out) && (chars)) {
            for (char c = *chars; c; c = *++chars) {
                if (0 < (amount = fwrite(&c, 1,1, out))) {
                    count += amount;
                } else {
                    return amount;
                }
            }
        }
        return count;
    }
    virtual ssize_t OutFV(FILE* out, const char* chars, va_list va) const {
        ssize_t count = 0, amount = 0;
        if ((out) && (chars)) {
            if (0 <= (amount = vfprintf(out, chars, va))) {
                count += amount;
            } else {
                return amount;
            }
        }
        return count;
    }
    virtual ssize_t OutLV(FILE* out, const char* chars, va_list va) const {
        ssize_t count = 0, amount = 0;
        for (count = 0; chars; count += amount) {
            if (0 > (amount = this->Out(out, chars))) {
                return amount;
            }
            chars = va_arg(va, const char*);
        }
        return count;
    }
    virtual ssize_t OutFlush(FILE* out) const {
        ssize_t count = 0;
        if ((out)) {
            fflush(out);
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual FILE* OutStdErr() {
        return this->StdErr();
    }
    virtual FILE* OutStdOut() {
        return this->StdOut();
    }
    virtual FILE* InStdIn() {
        return this->StdIn();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual FILE* StdErr() const {
        return stderr;
    }
    virtual FILE* StdOut() const {
        return stdout;
    }
    virtual FILE* StdIn() const {
        return stdin;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool m_didUsage;
};
typedef MainT<> Main;

} // namespace console
} // namespace patrona

#endif // _PATRONA_CONSOLE_MAIN_HPP
