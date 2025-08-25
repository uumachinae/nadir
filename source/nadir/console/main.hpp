///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2016 $organization$
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
///   Date: 12/31/2016
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_CONSOLE_MAIN_HPP
#define _NADIR_CONSOLE_MAIN_HPP

#include "nadir/console/main_exception.hpp"
#include "nadir/console/io.hpp"

namespace nadir {
namespace console {

typedef base maint_extends;
///////////////////////////////////////////////////////////////////////
///  Class: maint
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char, typename TEndChar = TChar, TEndChar VEndChar = 0,
 class TImplements = iot<TChar, TEndChar, VEndChar>,
 class TExtends = maint_extends>

class _EXPORT_CLASS maint: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TChar char_t;
    typedef TEndChar end_char_t;
    enum { end_char = VEndChar };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    maint(): did_main_(false), did_run_(false), locked_(0) {
        if ((the_main())) {
            main_exception e(main_already_exists);
            throw (e);
        } else {
            the_main() = this;
        }
    }
    virtual ~maint() {
        if ((this != the_main())) {
            main_exception e(main_doesnt_exist);
            throw (e);
        } else {
            the_main() = 0;
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int operator()(int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = before_main(argc, argv, env))) {
            int err2 = 0;
            if (!(did_main())) {
                err = main(argc, argv, env);
            }
            if ((err2 = after_main(argc, argv, env)) && (!err)) {
                err = err2;
            }
        }
        return err;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int main(int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = before_run(argc, argv, env))) {
            int err2 = 0;
            if (!(did_run())) {
                err = run(argc, argv, env);
            }
            if ((err2 = after_run(argc, argv, env)) && (!err)) {
                err = err2;
            }
        }
        return err;
    }
    virtual int before_main(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_main(int argc, char_t** argv, char_t** env) {
        int err = 0;
        set_did_main();
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int before_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        set_did_run();
        return err;
    }

public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Implements::out;
    virtual ssize_t out(FILE* f, const char_t* out, ssize_t length = -1) {
        ssize_t count = 0;
        if ((out) && (f)) {
            ssize_t amount;
            if (0 <= (length)) {
                if (0 < (amount = fwrite(out, sizeof(char_t), length, f)))
                    count += amount;
            } else {
                for (; *out; ++out) {
                    if (0 < (amount = fwrite(out, sizeof(char_t), 1, f)))
                        count += amount;
                }
            }
        }
        return count;
    }
    virtual ssize_t out_flush(FILE* f) {
        ssize_t count = 0;
        if ((f)) {
            fflush(f);
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Implements::in;
    virtual ssize_t in(FILE* f, char_t* in, size_t size) {
        ssize_t count = 0;
        if ((in) && (f) && (0 < (size))) {
            ssize_t amount;
            if (0 < (amount = fread(in, sizeof(char_t), size, f))) {
                count += amount;
            }
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual FILE* std_out() const {
        return stdout;
    }
    virtual FILE* std_err() const {
        return stderr;
    }
    virtual FILE* std_in() const {
        return stdin;
    }

public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static maint* get_the_main() {
        return the_main();
    }
protected:
    static maint*& the_main() {
        static maint* main = 0;
        return main;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_did_main(bool to = true) {
        return did_main_ = to;
    }
    virtual bool did_main() const {
        return did_main_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_did_run(bool to = true) {
        return did_run_ = to;
    }
    virtual bool did_run() const {
        return did_run_;
    }

public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool lock() { 
        locked* l = 0;
        if ((l = get_locked())) {
            return l->lock();
        }
        return false; 
    }
    virtual bool unlock() { 
        locked* l = 0;
        if ((l = get_locked())) {
            return l->unlock();
        }
        return false; 
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual locked* set_locked(locked* to) {
        locked_ = to;
        return locked_;
    }
    virtual locked* get_locked() const {
        return locked_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool did_main_, did_run_;
    locked* locked_;
};

typedef maint<char> main;
typedef main::Implements main_extend_implements;
typedef main main_extend_extends;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main_extend
: virtual public main_extend_implements, public main_extend_extends {
public:
    typedef main_extend_implements Implements;
    typedef main_extend_extends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t outfv(FILE* f, const char_t* format, va_list va) {
        ssize_t count = 0;
        count = vfprintf(f, format, va);
        return count;
    }
    virtual ssize_t infv(FILE* f, const char_t* format, va_list va) {
        ssize_t count = 0;
        count = vfscanf(f, format, va);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace console 
} // namespace nadir 

#endif // _NADIR_CONSOLE_MAIN_HPP 
