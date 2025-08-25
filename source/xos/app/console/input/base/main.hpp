//////////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2024 $organization$
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
///   Date: 12/13/2024, 12/30/2024
//////////////////////////////////////////////////////////////////////////
#ifndef XOS_APP_CONSOLE_INPUT_BASE_MAIN_HPP
#define XOS_APP_CONSOLE_INPUT_BASE_MAIN_HPP

#include "xos/app/console/input/base/main_opt.hpp"
#include "xos/io/string/reader.hpp"
#include "xos/io/crt/file/reader.hpp"
#include "xos/io/hex/read_to_string.hpp"

namespace xos {
namespace app {
namespace console {
namespace input {
namespace base {

/// class maint
template 
<class TExtends = xos::app::console::input::base::main_optt<>,  class TImplements = typename TExtends::implements>

class maint: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef maint derives;

    typedef typename extends::char_t char_t;
    typedef typename extends::end_char_t end_char_t;
    enum { end_char = extends::end_char };
    typedef typename extends::string_t string_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;
    typedef typename extends::file_t file_t;

    typedef typename extends::sequence_char_t sequence_char_t;
    typedef typename extends::char_sequence_t char_sequence_t;
    typedef typename extends::char_seeker_t char_seeker_t;
    typedef typename extends::char_reader_t char_reader_t;
    typedef typename extends::char_writer_t char_writer_t;
    typedef typename extends::reader_string_t reader_string_t;
    typedef typename extends::string_reader_t string_reader_t;

    /// constructor / destructor
    maint()
    : run_(0), 
      input_input_(false), 
      file_input_(false), 
      string_input_(true) {
    }
    virtual ~maint() {
    }
private:
    maint(const maint &copy) {
        throw exception(exception_unexpected);
    }

protected:
    typedef typename extends::in_reader_t in_reader_t;
    typedef typename extends::out_writer_t out_writer_t;
    typedef typename extends::err_writer_t err_writer_t;

    //////////////////////////////////////////////////////////////////////////
    /// run
    int (derives::*run_)(int argc, char_t** argv, char_t** env);
    virtual int run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        if ((run_)) {
            if (!(err = (this->*run_)(argc, argv, env))) {
            } else {
            }
        } else {
            if (!(err = extends::run(argc, argv, env))) {
            } else {
            }
        }
        return err;
    }

    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    /// on...input_input_option...
    virtual int on_get_input_input_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        LOGGER_IS_LOGGED_INFO("set_input_input()...");
        set_input_input();
        LOGGER_IS_LOGGED_INFO("this->on_set_input_input_option_on(optarg, optind, argc, argv, env)...");
        if (!(err = this->on_set_input_input_option_on(optarg, optind, argc, argv, env))) {
            LOGGER_IS_LOGGED_INFO("his->on_input_input_option_on_set(optarg, optind, argc, argv, env)...");
            if (!(err = this->on_input_input_option_on_set(optarg, optind, argc, argv, env))) {
            } else {
            }
        } else {
        }
        return err;
    }
    virtual int on_set_input_input_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            bool input_input = false;
            LOGGER_IS_LOGGED_INFO("this->on_set_onoff_option_on(input_input, optarg, optind, argc, argv, env)...");
            if ((this->on_set_onoff_option_on(input_input, optarg, optind, argc, argv, env))) {
                LOGGER_IS_LOGGED_INFO("set_input_input(" << input_input << ")...");
                if ((set_input_input(input_input))) {
                    LOGGER_IS_LOGGED_INFO("this->on_set_input_input_option_on(optarg, optind, argc, argv, env)...");
                    if (!(err = this->on_set_input_input_option_on(optarg, optind, argc, argv, env))) {
                        LOGGER_IS_LOGGED_INFO("sthis->on_input_input_option_on_set(optarg, optind, argc, argv, env)...");
                        if (!(err = this->on_input_input_option_on_set(optarg, optind, argc, argv, env))) {
                        } else {
                        }
                    } else {
                    }
                } else {
                    LOGGER_IS_LOGGED_INFO("this->on_set_input_input_option_off(optarg, optind, argc, argv, env)...");
                    if (!(err = this->on_set_input_input_option_off(optarg, optind, argc, argv, env))) {
                        LOGGER_IS_LOGGED_INFO("this->on_input_input_option_off_set(optarg, optind, argc, argv, env)...");
                        if (!(err = this->on_input_input_option_off_set(optarg, optind, argc, argv, env))) {
                        } else {
                        }
                    } else {
                    }
                }
            } else {
            }
        } else {
        }
        return err;
    }
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    /// on...file_input_option...
    virtual int on_get_file_input_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        LOGGER_IS_LOGGED_INFO("set_file_input()...");
        set_file_input();
        LOGGER_IS_LOGGED_INFO("this->on_set_file_input_option_on(optarg, optind, argc, argv, env)...");
        if (!(err = this->on_set_file_input_option_on(optarg, optind, argc, argv, env))) {
            LOGGER_IS_LOGGED_INFO("his->on_file_input_option_on_set(optarg, optind, argc, argv, env)...");
            if (!(err = this->on_file_input_option_on_set(optarg, optind, argc, argv, env))) {
            } else {
            }
        } else {
        }
        return err;
    }
    virtual int on_set_file_input_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            bool file_input = false;
            LOGGER_IS_LOGGED_INFO("this->on_set_onoff_option_on(file_input, optarg, optind, argc, argv, env)...");
            if ((this->on_set_onoff_option_on(file_input, optarg, optind, argc, argv, env))) {
                LOGGER_IS_LOGGED_INFO("set_file_input(" << file_input << ")...");
                if ((set_file_input(file_input))) {
                    LOGGER_IS_LOGGED_INFO("this->on_set_file_input_option_on(optarg, optind, argc, argv, env)...");
                    if (!(err = this->on_set_file_input_option_on(optarg, optind, argc, argv, env))) {
                        LOGGER_IS_LOGGED_INFO("sthis->on_file_input_option_on_set(optarg, optind, argc, argv, env)...");
                        if (!(err = this->on_file_input_option_on_set(optarg, optind, argc, argv, env))) {
                        } else {
                        }
                    } else {
                    }
                } else {
                    LOGGER_IS_LOGGED_INFO("this->on_set_file_input_option_off(optarg, optind, argc, argv, env)...");
                    if (!(err = this->on_set_file_input_option_off(optarg, optind, argc, argv, env))) {
                        LOGGER_IS_LOGGED_INFO("this->on_file_input_option_off_set(optarg, optind, argc, argv, env)...");
                        if (!(err = this->on_file_input_option_off_set(optarg, optind, argc, argv, env))) {
                        } else {
                        }
                    } else {
                    }
                }
            } else {
            }
        } else {
        }
        return err;
    }
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    /// on...string_input_option...
    virtual int on_get_string_input_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        LOGGER_IS_LOGGED_INFO("set_string_input()...");
        set_string_input();
        LOGGER_IS_LOGGED_INFO("this->on_set_string_input_option_on(optarg, optind, argc, argv, env)...");
        if (!(err = this->on_set_string_input_option_on(optarg, optind, argc, argv, env))) {
            LOGGER_IS_LOGGED_INFO("this->on_string_input_option_on_set(optarg, optind, argc, argv, env)...");
            if (!(err = this->on_string_input_option_on_set(optarg, optind, argc, argv, env))) {
            } else {
            }
        } else {
        }
        return err;
    }
    virtual int on_set_string_input_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            bool string_input = false;
            LOGGER_IS_LOGGED_INFO("this->on_set_onoff_option_on(string_input, optarg, optind, argc, argv, env)...");
            if ((this->on_set_onoff_option_on(string_input, optarg, optind, argc, argv, env))) {
                LOGGER_IS_LOGGED_INFO("set_string_input(" << string_input << ")...");
                if ((set_string_input(string_input))) {
                    LOGGER_IS_LOGGED_INFO("this->on_set_string_input_option_on(optarg, optind, argc, argv, env)...");
                    if (!(err = this->on_set_string_input_option_on(optarg, optind, argc, argv, env))) {
                        LOGGER_IS_LOGGED_INFO("this->on_string_input_option_on_set(optarg, optind, argc, argv, env)...");
                        if (!(err = this->on_string_input_option_on_set(optarg, optind, argc, argv, env))) {
                        } else {
                        }
                    } else {
                    }
                } else {
                    LOGGER_IS_LOGGED_INFO("this->on_set_string_input_option_off(optarg, optind, argc, argv, env)...");
                    if (!(err = this->on_set_string_input_option_off(optarg, optind, argc, argv, env))) {
                        LOGGER_IS_LOGGED_INFO("this->on_string_input_option_off_set(optarg, optind, argc, argv, env)...");
                        if (!(err = this->on_string_input_option_off_set(optarg, optind, argc, argv, env))) {
                        } else {
                        }
                    } else {
                    }
                }
            } else {
            }
        } else {
        }
        return err;
    }
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    /// ...input_input
    virtual bool& set_input_input(const bool& to = true) {
        bool& input_input = this->input_input();
        bool& file_input = this->file_input();
        bool& string_input = this->string_input();
        string_input = !to;
        file_input = !to;
        input_input = to;
        return input_input;
    }
    virtual bool& input_input() const {
        return (bool&)input_input_;
    }
    //////////////////////////////////////////////////////////////////////////
    /// ...file_input
    virtual bool& set_file_input(const bool& to = true) {
        bool& input_input = this->input_input();
        bool& file_input = this->file_input();
        bool& string_input = this->string_input();
        string_input = !to;
        file_input = to;
        input_input = !to;
        return file_input;
    }
    virtual bool& file_input() const {
        return (bool&)file_input_;
    }
    //////////////////////////////////////////////////////////////////////////
    /// ...string_input
    virtual bool& set_string_input(const bool& to = true) {
        bool& input_input = this->input_input();
        bool& file_input = this->file_input();
        bool& string_input = this->string_input();
        string_input = to;
        file_input = !to;
        input_input = !to;
        return string_input;
    }
    virtual bool& string_input() const {
        return (bool&)string_input_;
    }
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
protected:
    bool input_input_, file_input_, string_input_;
}; /// class maint 
typedef maint<> main;

} /// namespace base 
} /// namespace input 
} /// namespace console 
} /// namespace app 
} /// namespace xos 

#endif /// ndef XOS_APP_CONSOLE_INPUT_BASE_MAIN_HPP

