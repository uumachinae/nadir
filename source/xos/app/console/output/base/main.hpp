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
///   Date: 11/13/2024, 11/26/2024
//////////////////////////////////////////////////////////////////////////
#ifndef XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_HPP
#define XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_HPP

#include "xos/app/console/output/base/main_opt.hpp"

namespace xos {
namespace app {
namespace console {
namespace output {
namespace base {

/// class maint
template 
<class TExtends = xos::app::console::output::base::main_optt<>,  class TImplements = typename TExtends::implements>

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
      verbose_output_(false), 
      output_lf_(true),
      crlf2_("\r\n\r\n"),
      crlf_("\r\n"),
      cr_("\r"), 
      lf_("\n") {
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
    /// ...output_text_run
    virtual int default_output_text_run(const char_t* chars, size_t length, int argc, char_t** argv, char_t** env) {
        int err = 0;
        const bool& output_lf = this->output_lf();
        LOGGER_IS_LOGGED_INFO("((output_lf))...");
        if ((output_lf)) {
            LOGGER_IS_LOGGED_INFO("...((output_lf))");
            LOGGER_IS_LOGGED_INFO("this->outln(\"" << chars << "\", " << length << ")...");
            this->outln(chars, length);
        } else {
            LOGGER_IS_LOGGED_INFO("...failed on ((output_lf))");
            LOGGER_IS_LOGGED_INFO("this->out(\"" << chars << "\", " << length << ")...");
            this->out(chars, length);
        }
        return err;
    }
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    /// ...output_text
    ssize_t (derives::*output_text_)(const char_t* chars, size_t length, bool lf);
    virtual ssize_t output_text(const char_t* chars, size_t length, bool lf = false) {
        ssize_t amount = 0;
        if (output_text_) {
            if (0 <= (amount = (this->*output_text_)(chars, length, lf))) {
            } else {
            }
        } else {
            if (0 <= (amount = default_output_text(chars, length, lf))) {
            } else {
            }
        }
        return amount;
    }
    virtual ssize_t default_output_text(const char_t* chars, size_t length, bool lf = false) {
        ssize_t amount = 0;
        if ((chars) && (length)) {
            if ((lf)) {
                amount = this->outln(chars, length);
            } else {
                amount = this->out(chars, length);
            }
        }
        return amount;
    }
    virtual ssize_t before_output_text(const char_t* chars, size_t length, bool lf = false) {
        ssize_t amount = 0;
        return amount;
    }
    virtual ssize_t after_output_text(const char_t* chars, size_t length, bool lf = false) {
        ssize_t amount = 0;
        return amount;
    }
    virtual ssize_t all_output_text(const char_t* chars, size_t length, bool lf = false) {
        ssize_t amount = 0;
        if (0 <= (amount = before_output_text(chars, length, lf))) {
            ssize_t amount2 = 0;
            if (0 <= (amount2 = output_text(chars, length, lf))) {
                amount += amount2;
                if (0 <= (amount2 = after_output_text(chars, length, lf))) {
                    amount += amount2;
                }
            }
        }
        return amount;
    }
    //////////////////////////////////////////////////////////////////////////
    /// ...base64_output_text
    virtual ssize_t base64_output_text(const char_t* chars, size_t length, bool lf = false) {
        ssize_t amount = 0;
        if (0 > (amount = output_base64(chars, length, lf))) {} else {}
        return amount;
    }
    virtual int set_base64_output_text(int argc, char_t** argv, char_t** env) {
        int err = 0;
        output_text_ = &derives::base64_output_text;
        return err;
    }
    virtual int base64_output_text_set(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int unset_base64_output_text(int argc, char_t** argv, char_t** env) {
        int err = 0;
        output_text_ = 0;
        return err;
    }
    virtual int base64_output_text_unset(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    //////////////////////////////////////////////////////////////////////////
    /// ...lower_hex_output_text
    virtual ssize_t lower_hex_output_text(const char_t* chars, size_t length, bool lf = false) {
        ssize_t amount = 0;
        if (0 > (amount = output_lower_hex(chars, length, lf))) {} else {}
        return amount;
    }
    virtual int set_lower_hex_output_text(int argc, char_t** argv, char_t** env) {
        int err = 0;
        output_text_ = &derives::lower_hex_output_text;
        return err;
    }
    virtual int lower_hex_output_text_set(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int unset_lower_hex_output_text(int argc, char_t** argv, char_t** env) {
        int err = 0;
        output_text_ = 0;
        return err;
    }
    virtual int lower_hex_output_text_unset(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    //////////////////////////////////////////////////////////////////////////
    /// ...upper_hex_output_text
    virtual ssize_t upper_hex_output_text(const char_t* chars, size_t length, bool lf = false) {
        ssize_t amount = 0;
        if (0 > (amount = output_upper_hex(chars, length, lf))) {} else {}
        return amount;
    }
    virtual int set_upper_hex_output_text(int argc, char_t** argv, char_t** env) {
        int err = 0;
        output_text_ = &derives::upper_hex_output_text;
        return err;
    }
    virtual int upper_hex_output_text_set(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int unset_upper_hex_output_text(int argc, char_t** argv, char_t** env) {
        int err = 0;
        output_text_ = 0;
        return err;
    }
    virtual int upper_hex_output_text_unset(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    //////////////////////////////////////////////////////////////////////////
    /// ...output_base64
    ssize_t (derives::*output_base64_)(const void* bytes, size_t length, bool lf);
    virtual ssize_t output_base64(const void* bytes, size_t length, bool lf = false) {
        ssize_t amount = 0;
        if (output_base64_) {
            if (0 <= (amount = (this->*output_base64_)(bytes, length, lf))) {
            } else {
            }
        } else {
            if (0 <= (amount = default_output_base64(bytes, length, lf))) {
            } else {
            }
        }
        return amount;
    }
    virtual ssize_t default_output_base64(const void* bytes, size_t length, bool lf = false) {
        ssize_t amount = 0;
        if ((bytes) && (length)) {
            if ((lf)) {
                amount = this->out64ln(bytes, length);
            } else {
                amount = this->out64(bytes, length);
            }
        }
        return amount;
    }
    virtual ssize_t before_output_base64(const void* bytes, size_t length, bool lf = false) {
        ssize_t amount = 0;
        return amount;
    }
    virtual ssize_t after_output_base64(const void* bytes, size_t length, bool lf = false) {
        ssize_t amount = 0;
        return amount;
    }
    virtual ssize_t all_output_base64(const void* bytes, size_t length, bool lf = false) {
        ssize_t amount = 0;
        if (0 <= (amount = before_output_base64(bytes, length, lf))) {
            ssize_t amount2 = 0;
            if (0 <= (amount2 = output_base64(bytes, length, lf))) {
                amount += amount2;
                if (0 <= (amount2 = after_output_base64(bytes, length, lf))) {
                    amount += amount2;
                }
            }
        }
        return amount;
    }
    //////////////////////////////////////////////////////////////////////////
    /// ...output_lower_hex
    ssize_t (derives::*output_lower_hex_)(const void* bytes, size_t length, bool lf);
    virtual ssize_t output_lower_hex(const void* bytes, size_t length, bool lf = false) {
        ssize_t amount = 0;
        if (output_lower_hex_) {
            if (0 <= (amount = (this->*output_lower_hex_)(bytes, length, lf))) {
            } else {
            }
        } else {
            if (0 <= (amount = default_output_lower_hex(bytes, length, lf))) {
            } else {
            }
        }
        return amount;
    }
    virtual ssize_t default_output_lower_hex(const void* bytes, size_t length, bool lf = false) {
        ssize_t amount = 0;
        if ((bytes) && (length)) {
            if ((lf)) {
                amount = this->outxln(bytes, length);
            } else {
                amount = this->outx(bytes, length);
            }
        }
        return amount;
    }
    virtual ssize_t before_output_lower_hex(const void* bytes, size_t length, bool lf = false) {
        ssize_t amount = 0;
        return amount;
    }
    virtual ssize_t after_output_lower_hex(const void* bytes, size_t length, bool lf = false) {
        ssize_t amount = 0;
        return amount;
    }
    virtual ssize_t all_output_lower_hex(const void* bytes, size_t length, bool lf = false) {
        ssize_t amount = 0;
        if (0 <= (amount = before_output_lower_hex(bytes, length, lf))) {
            ssize_t amount2 = 0;
            if (0 <= (amount2 = output_lower_hex(bytes, length, lf))) {
                amount += amount2;
                if (0 <= (amount2 = after_output_lower_hex(bytes, length, lf))) {
                    amount += amount2;
                }
            }
        }
        return amount;
    }
    //////////////////////////////////////////////////////////////////////////
    /// ...output_upper_hex
    ssize_t (derives::*output_upper_hex_)(const void* bytes, size_t length, bool lf);
    virtual ssize_t output_upper_hex(const void* bytes, size_t length, bool lf = false) {
        ssize_t amount = 0;
        if (output_upper_hex_) {
            if (0 <= (amount = (this->*output_upper_hex_)(bytes, length, lf))) {
            } else {
            }
        } else {
            if (0 <= (amount = default_output_upper_hex(bytes, length, lf))) {
            } else {
            }
        }
        return amount;
    }
    virtual ssize_t default_output_upper_hex(const void* bytes, size_t length, bool lf = false) {
        ssize_t amount = 0;
        if ((bytes) && (length)) {
            if ((lf)) {
                amount = this->outXln(bytes, length);
            } else {
                amount = this->outX(bytes, length);
            }
        }
        return amount;
    }
    virtual ssize_t before_output_upper_hex(const void* bytes, size_t length, bool lf = false) {
        ssize_t amount = 0;
        return amount;
    }
    virtual ssize_t after_output_upper_hex(const void* bytes, size_t length, bool lf = false) {
        ssize_t amount = 0;
        return amount;
    }
    virtual ssize_t all_output_upper_hex(const void* bytes, size_t length, bool lf = false) {
        ssize_t amount = 0;
        if (0 <= (amount = before_output_upper_hex(bytes, length, lf))) {
            ssize_t amount2 = 0;
            if (0 <= (amount2 = output_upper_hex(bytes, length, lf))) {
                amount += amount2;
                if (0 <= (amount2 = after_output_upper_hex(bytes, length, lf))) {
                    amount += amount2;
                }
            }
        }
        return amount;
    }
    //////////////////////////////////////////////////////////////////////////
    /// ...output_hex
    ssize_t (derives::*output_hex_)(const void* bytes, size_t length, bool lf);
    virtual ssize_t output_hex(const void* bytes, size_t length, bool lf = false) {
        ssize_t amount = 0;
        if (output_hex_) {
            if (0 <= (amount = (this->*output_hex_)(bytes, length, lf))) {
            } else {
            }
        } else {
            if (0 <= (amount = default_output_hex(bytes, length, lf))) {
            } else {
            }
        }
        return amount;
    }
    virtual ssize_t default_output_hex(const void* bytes, size_t length, bool lf = false) {
        ssize_t amount = 0;
        if (0 <= (amount = all_output_lower_hex(bytes, length, lf))) {
        } else {
        }
        return amount;
    }
    virtual ssize_t before_output_hex(const void* bytes, size_t length, bool lf = false) {
        ssize_t amount = 0;
        return amount;
    }
    virtual ssize_t after_output_hex(const void* bytes, size_t length, bool lf = false) {
        ssize_t amount = 0;
        return amount;
    }
    virtual ssize_t all_output_hex(const void* bytes, size_t length, bool lf = false) {
        ssize_t amount = 0;
        if (0 <= (amount = before_output_hex(bytes, length, lf))) {
            ssize_t amount2 = 0;
            if (0 <= (amount2 = output_hex(bytes, length, lf))) {
                amount += amount2;
                if (0 <= (amount2 = after_output_hex(bytes, length, lf))) {
                    amount += amount2;
                }
            }
        }
        return amount;
    }
    //////////////////////////////////////////////////////////////////////////
    virtual int set_output_lower_hex(int argc, char_t** argv, char_t** env) {
        int err = 0;
        output_hex_ = &derives::all_output_lower_hex;
        return err;
    }
    virtual int output_lower_hex_set(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int unset_output_lower_hex(int argc, char_t** argv, char_t** env) {
        int err = 0;
        output_hex_ = 0;
        return err;
    }
    virtual int output_lower_hex_unset(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    //////////////////////////////////////////////////////////////////////////
    virtual int set_output_upper_hex(int argc, char_t** argv, char_t** env) {
        int err = 0;
        output_hex_ = &derives::all_output_upper_hex;
        return err;
    }
    virtual int output_upper_hex_set(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int unset_output_upper_hex(int argc, char_t** argv, char_t** env) {
        int err = 0;
        output_hex_ = 0;
        return err;
    }
    virtual int output_upper_hex_unset(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    /// ...on_set_onoff_option_on
    virtual bool on_set_onoff_option_on
    (bool& on, const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        if ((optarg) && (optarg[0])) {
            string_t arg(optarg);
            int unequal = 0;
            LOGGER_IS_LOGGED_INFO("(!(unequal = arg.compare(\"" << XOS_APP_CONSOLE_MAIN_OPTARG_ON << "\")))...");
            if (!(unequal = arg.compare(XOS_APP_CONSOLE_MAIN_OPTARG_ON))) {
                LOGGER_IS_LOGGED_INFO("...(!(unequal = arg.compare(\"" << XOS_APP_CONSOLE_MAIN_OPTARG_ON << "\")))");
                LOGGER_IS_LOGGED_INFO("on = true...");
                on = true;
            } else {
                LOGGER_IS_LOGGED_INFO("...failed on (!(unequal = arg.compare(\"" << XOS_APP_CONSOLE_MAIN_OPTARG_ON << "\")))");
                LOGGER_IS_LOGGED_INFO("(!(unequal = arg.compare(\"" << XOS_APP_CONSOLE_MAIN_OPTARG_OFF << "\")))...");
                if (!(unequal = arg.compare(XOS_APP_CONSOLE_MAIN_OPTARG_OFF))) {
                    LOGGER_IS_LOGGED_INFO("...(!(unequal = arg.compare(\"" << XOS_APP_CONSOLE_MAIN_OPTARG_OFF << "\")))");
                    LOGGER_IS_LOGGED_INFO("on = false...");
                    on = false;
                } else {
                    LOGGER_IS_LOGGED_INFO("...failed on (!(unequal = arg.compare(\"" << XOS_APP_CONSOLE_MAIN_OPTARG_OFF << "\")))");
                    LOGGER_IS_LOGGED_INFO("return false...");
                    return false;
                }
            }
        } else {
            LOGGER_IS_LOGGED_INFO("return false...");
            return false;
        }
        LOGGER_IS_LOGGED_INFO("return true...");
        return true;
    }
    //////////////////////////////////////////////////////////////////////////
    /// on...noline_output_option...
    virtual int on_get_noline_output_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        LOGGER_IS_LOGGED_INFO("set_output_lf(false)...");
        set_output_lf(false);
        return err;
    }
    virtual int on_set_noline_output_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            bool noline_output = false;
            if ((on_set_onoff_option_on(noline_output, optarg, optind, argc, argv, env))) {
                LOGGER_IS_LOGGED_INFO("set_output_lf(" << !noline_output << ")...");
                set_output_lf(!noline_output);
            } else {
            }
        } else {
        }
        return err;
    }
    //////////////////////////////////////////////////////////////////////////
    /// on...quiet_output...option...
    virtual int on_quiet_output_on_option_set
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_quiet_output_off_option_set
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_get_quiet_output_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        LOGGER_IS_LOGGED_INFO("set_quiet_output()...");
        set_quiet_output();
        if (!(err = on_quiet_output_on_option_set(optarg, optind, argc, argv, env))) {
        } else {
        }
        return err;
    }
    virtual int on_set_quiet_output_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            bool quiet_output = false;
            if ((on_set_onoff_option_on(quiet_output, optarg, optind, argc, argv, env))) {
                LOGGER_IS_LOGGED_INFO("set_quiet_output(" << quiet_output << ")...");
                set_quiet_output(quiet_output);
                if ((quiet_output)) {
                    if (!(err = on_quiet_output_on_option_set(optarg, optind, argc, argv, env))) {
                    } else {
                    }
                } else {
                    if (!(err = on_quiet_output_off_option_set(optarg, optind, argc, argv, env))) {
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
    /// on...verbose_output...option...
    virtual int on_verbose_output_on_option_set
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_verbose_output_off_option_set
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_get_verbose_output_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        LOGGER_IS_LOGGED_INFO("set_verbose_output()...");
        set_verbose_output();
        if (!(err = on_verbose_output_on_option_set(optarg, optind, argc, argv, env))) {
        } else {
        }
        return err;
    }
    virtual int on_set_verbose_output_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            bool verbose_output = false;
            if ((on_set_onoff_option_on(verbose_output, optarg, optind, argc, argv, env))) {
                LOGGER_IS_LOGGED_INFO("set_verbose_output(" << verbose_output << ")...");
                set_verbose_output(verbose_output);
                if ((verbose_output)) {
                    if (!(err = on_verbose_output_on_option_set(optarg, optind, argc, argv, env))) {
                    } else {
                    }
                } else {
                    if (!(err = on_verbose_output_off_option_set(optarg, optind, argc, argv, env))) {
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
    /// ...verbose_output
    virtual bool& set_quiet_output(const bool& to = true) {
        bool& verbose_output = this->verbose_output();
        verbose_output = !to;
        return verbose_output;
    }
    virtual bool& set_verbose_output(const bool& to = true) {
        bool& verbose_output = this->verbose_output();
        verbose_output = to;
        return verbose_output;
    }
    virtual bool& verbose_output() const {
        return (bool&)verbose_output_;
    }
    //////////////////////////////////////////////////////////////////////////
    /// ...output_lf
    virtual bool& set_output_lf(const bool& to = true) {
        bool& output_lf = this->output_lf();
        output_lf = to;
        return output_lf;
    }
    virtual bool& output_lf() const {
        return (bool&)output_lf_;
    }
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    /// ...crlf2
    virtual string_t& set_crlf2(const string_t& to) {
        string_t& crlf2 = this->crlf2();
        crlf2 = to;
        return crlf2;
    }
    virtual string_t& crlf2() const {
        return (string_t&)crlf2_;
    }
    //////////////////////////////////////////////////////////////////////////
    /// ...crlf
    virtual string_t& set_crlf(const string_t& to) {
        string_t& crlf = this->crlf();
        crlf = to;
        return crlf;
    }
    virtual string_t& crlf() const {
        return (string_t&)crlf_;
    }
    //////////////////////////////////////////////////////////////////////////
    /// ...cr
    virtual string_t& set_cr(const string_t& to) {
        string_t& cr = this->cr();
        cr = to;
        return cr;
    }
    virtual string_t& cr() const {
        return (string_t&)cr_;
    }
    //////////////////////////////////////////////////////////////////////////
    /// ...lf
    virtual string_t& set_lf(const string_t& to) {
        string_t& lf = this->lf();
        lf = to;
        return lf;
    }
    virtual string_t& lf() const {
        return (string_t&)lf_;
    }
    //////////////////////////////////////////////////////////////////////////
    /// ...lf
    virtual string_t& set_null_lf(const string_t& to) {
        string_t& lf = this->null_lf();
        lf = to;
        return lf;
    }
    virtual string_t& null_lf() const {
        return (string_t&)null_lf_;
    }
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
protected:
    bool verbose_output_, output_lf_;
    string_t crlf2_, crlf_, cr_, lf_, null_lf_;
}; /// class maint 
typedef maint<> main;

} /// namespace base 
} /// namespace output 
} /// namespace console 
} /// namespace app 
} /// namespace xos 

#endif /// ndef XOS_APP_CONSOLE_OUTPUT_BASE_MAIN_HPP

