///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2022 $organization$
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
///   Date: 5/7/2022, 11/15/2024
///////////////////////////////////////////////////////////////////////
#ifndef XOS_CONSOLE_MAIN_HPP
#define XOS_CONSOLE_MAIN_HPP

#include "xos/console/io.hpp"
#include "xos/io/reader.hpp"
#include "xos/io/writer.hpp"
#include "xos/io/string/reader.hpp"
#include "xos/base/logged.hpp"
#include "xos/base/logger.hpp"
#include "xos/base/location.hpp"
#include "xos/base/error.hpp"

namespace xos {
namespace console {

/// class maint
template 
<typename TChar = char, class TIo = iot<TChar>,
 class TExtends = extended::logged, class TImplements = TIo>

class exported maint: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements, implements;
    typedef TExtends Extends, extends;
    typedef maint Derives, derives;

    typedef TIo io_t;
    typedef TChar sequence_char_t;
    typedef xos::io::sequencet<TChar> sequence_t;
    typedef xos::io::seekert<sequence_t> seeker_t;
    typedef xos::io::readert<seeker_t> reader_t;
    typedef xos::io::writert<sequence_t> writer_t;
    typedef xos::io::char_sequencet<TChar> char_sequence_t;
    typedef xos::io::char_seekert<char_sequence_t> char_seeker_t;
    typedef xos::io::char_readert<char_seeker_t> char_reader_t;
    typedef xos::io::char_writert<char_sequence_t> char_writer_t;
    typedef xos::base::stringt<sequence_char_t> reader_string_t;
    typedef xos::io::string::readert<reader_string_t, char_reader_t> string_reader_t;
    typedef string_reader_t  char_string_reader_t;
    //typedef xos::io::string::readert<char_reader_t> string_reader_t;
    //typedef typename string_reader_t::string_t reader_string_t;
    typedef typename reader_string_t::char_t reader_char_t;
    typedef typename implements::file_t file_t;
    typedef typename implements::string_t string_t;
    typedef TChar char_t;
    typedef char_t end_char_t;
    enum { end_char = 0 };
    enum { exception_none, exception_unexpected, 
           exception_exist, exception_not_exist };

    /// constructor / destructor
    maint()
    : run_(0), did_run_(false), did_usage_(false), 
      in_reader_(*this), out_writer_(*this), err_writer_(*this) {
        derives*& the_main = derives::the_main();
        if ((the_main)) {
            throw (exception_exist);
        } else {
            the_main = this;
        }
    }
    virtual ~maint() {
        derives*& the_main = derives::the_main();
        if ((the_main)) {
            if ((the_main != this)) {
                throw (exception_unexpected);
            } else {
                the_main = 0;
            }
        } else {
            throw (exception_not_exist);
        }
    }
private:
    maint(const maint& copy)
    : run_(0), did_run_(false), did_usage_(false), 
      in_reader_(*this), out_writer_(*this), err_writer_(*this) {
        throw exception(exception_unexpected);
    }

public:
    /// the_main
    static int the_main(int argc, char_t** argv, char** env) {
        derives* the_main = 0;
        int err = 0;
        if ((the_main = derives::the_main())) {
            err = (*the_main)(argc, argv, env);
        } else {
            LOGGER_LOG_ERROR("...failed 0 = derives::the_main() err = 1...");
            err = 1;
        }
        return err;
    }
protected:
    static derives*& the_main() {
        static derives* the_main = 0;
        return the_main;
    }

protected:
    typedef xos::extend io_extends_t;

    /// class io_extend_t
    class exported io_extend_t: public io_extends_t {
    public:
        typedef io_extends_t extends;
        typedef io_extend_t derives;
    
        /// constructor / destructor
        io_extend_t(const io_extend_t& copy): extends(copy), io_(copy.io_) {
        }
        io_extend_t(io_t& io): io_(io) {
        }
        virtual ~io_extend_t() {
        }
    protected:
        io_t& io_;
    }; /// class io_extend_t
    
    /// class in_reader_t
    class exported in_reader_t: virtual public reader_t, public io_extend_t {
    public:
        typedef reader_t implements;
        typedef io_extend_t extends;
        typedef in_reader_t derives;
    
        typedef typename implements::what_t what_t;
        typedef typename implements::sized_t sized_t;

        /// constructor / destructor
        in_reader_t(const in_reader_t& copy): extends(copy) {
        }
        in_reader_t(io_t& io): extends(io) {
        }
        virtual ~in_reader_t() {
        }
        virtual ssize_t read(what_t* what, size_t size) {
            ssize_t count = 0;
            count = this->io_.in(what, size);
            return count;
        }    
    }; /// class in_reader_t
    
    /// class out_writer_t
    class exported out_writer_t: virtual public writer_t, public io_extend_t {
    public:
        typedef writer_t implements;
        typedef io_extend_t extends;
        typedef out_writer_t derives;
    
        typedef typename implements::what_t what_t;
        typedef typename implements::sized_t sized_t;

        /// constructor / destructor
        out_writer_t(const out_writer_t& copy): extends(copy) {
        }
        out_writer_t(io_t& io): extends(io) {
        }
        virtual ~out_writer_t() {
        }
        virtual ssize_t write(const what_t* what, size_t size) {
            ssize_t count = 0;
            count = this->io_.out(what, size);
            return count;
        }    
        virtual ssize_t flush() {
            ssize_t count = 0;
            count = this->io_.out_flush();
            return count;
        }    
    }; /// class out_writer_t
    
    /// class err_writer_t
    class exported err_writer_t: virtual public writer_t, public io_extend_t {
    public:
        typedef writer_t implements;
        typedef io_extend_t extends;
        typedef err_writer_t derives;
    
        typedef typename implements::what_t what_t;
        typedef typename implements::sized_t sized_t;

        /// constructor / destructor
        err_writer_t(const err_writer_t& copy): extends(copy) {
        }
        err_writer_t(io_t& io): extends(io) {
        }
        virtual ~err_writer_t() {
        }
        virtual ssize_t write(const what_t* what, size_t size) {
            ssize_t count = 0;
            count = this->io_.err(what, size);
            return count;
        }    
        virtual ssize_t flush() {
            ssize_t count = 0;
            count = this->io_.err_flush();
            return count;
        }    
    }; /// class err_writer_t
    
protected:
    /// ...run
    int (derives::*run_)(int argc, char_t** argv, char_t** env);
    virtual int run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        if ((run_)) {
            err = (this->*run_)(argc, argv, env);
        } else {
        }
        return err;
    }
    virtual int before_run(int argc, char_t** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int after_run(int argc, char_t** argv, char** env) {
        int err = 0;
        set_did_run();
        return err;
    }
    virtual int all_run(int argc, char_t** argv, char** env) {
        int err = 0;
        if (!(did_run())) {
            if (!(err = before_run(argc, argv, env))) {
                int err2 = 0;
                err = run(argc, argv, env);
                if ((err2 = after_run(argc, argv, env))) {
                    if (!(err)) err = err2;
                }
            }
        }
        return err;
    }

    /// ...usage...
    virtual int usage(int argc, char_t** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int before_usage(int argc, char_t** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int after_usage(int argc, char_t** argv, char** env) {
        int err = 0;
        set_did_usage();
        return err;
    }
    virtual int all_usage(int argc, char_t** argv, char** env) {
        int err = 0;
        if (!(did_usage())) {
            if (!(err = before_usage(argc, argv, env))) {
                int err2 = 0;
                err = usage(argc, argv, env);
                if ((err2 = after_usage(argc, argv, env))) {
                    if (!(err)) err = err2;
                }
            }
        }
        return err;
    }

    /// ...main...
    virtual int main(int argc, char_t** argv, char** env) {
        int err = 0;
        err = all_run(argc, argv, env);
        return err;
    }
    virtual int before_main(int argc, char_t** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int after_main(int argc, char_t** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int all_main(int argc, char_t** argv, char** env) {
        int err = 0;
        if (!(err = before_main(argc, argv, env))) {
            int err2 = 0;
            err = main(argc, argv, env);
            if ((err2 = after_main(argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }

    /// before / after / operator()
    virtual int before(int argc, char_t** argv, char** env) {
        int err = 0;
        err = all_get_arguments(argc, argv, env);
        return err;
    }
    virtual int after(int argc, char_t** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int operator()(int argc, char_t** argv, char** env) {
        int err = 0;
        if (!(err = before(argc, argv, env))) {
            int err2 = 0;
            err = all_main(argc, argv, env);
            if ((err2 = after(argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }

    /// ...arguments...
    virtual int get_arguments(int argc, char_t** argv, char** env) {
        int err = 0, optind = this->arguments_index();
        if (argc > (optind)) {
            for (int argind = optind; argind < argc; ++argind) {
                if ((err = this->all_on_argument(argv[argind], argind-optind, argc, argv, env))) {
                    break;
                }
            }
        }
        return err;
    }
    virtual int before_get_arguments(int argc, char_t** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int after_get_arguments(int argc, char_t** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int all_get_arguments(int argc, char_t** argv, char** env) {
        int err = 0;
        if (!(err = before_get_arguments(argc, argv, env))) {
            int err2 = 0;
            err = get_arguments(argc, argv, env);
            if ((err2 = after_get_arguments(argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }
    virtual int arguments_index() const {
        return 1;
    }
    virtual const char_t* arguments(const char_t**& args) {
        args = 0;
        return 0;
    }

    /// ...on...argument...
    virtual int on_argument
    (const char_t* arg, int argind, int argc, char_t** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int before_on_argument
    (const char_t* arg, int argind, int argc, char_t** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int after_on_argument
    (const char_t* arg, int argind, int argc, char_t** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int all_on_argument
    (const char_t* arg, int argind, int argc, char_t** argv, char** env) {
        int err = 0;
        if (!(err = before_on_argument(arg, argind, argc, argv, env))) {
            int err2 = 0;
            err = on_argument(arg, argind, argc, argv, env);
            if ((err2 = after_on_argument(arg, argind, argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }
    virtual int on_missing_argument(const char_t* arg) {
        int err = 1;
        return err;
    }

    /// ...did_run
    virtual bool set_did_run(bool to = true) {
        did_usage_ = did_run_ = to;
        return did_run_;
    }
    virtual bool did_run() const {
        return did_run_;
    }

    /// ...did_usage
    virtual bool set_did_usage(bool to = true) {
        did_run_ = did_usage_ = to;
        return did_usage_;
    }
    virtual bool did_usage() const {
        return did_usage_;
    }

    /// ...reader / ...writer
    virtual in_reader_t& in_reader() const {
        return (in_reader_t&)in_reader_;
    }
    virtual out_writer_t& out_writer() const {
        return (out_writer_t&)out_writer_;
    }
    virtual err_writer_t& err_writer() const {
        return (err_writer_t&)err_writer_;
    }

protected:
    bool did_run_, did_usage_;
    in_reader_t in_reader_;
    out_writer_t out_writer_;
    err_writer_t err_writer_;
}; /// class maint
typedef maint<> main;

} /// namespace console
} /// namespace xos

#endif /// ndef XOS_CONSOLE_MAIN_HPP
