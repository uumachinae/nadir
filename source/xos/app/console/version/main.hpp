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
///   Date: 11/3/2024
//////////////////////////////////////////////////////////////////////////
#ifndef XOS_APP_CONSOLE_VERSION_MAIN_HPP
#define XOS_APP_CONSOLE_VERSION_MAIN_HPP

#include "xos/app/console/version/main_opt.hpp"
#include "xos/lib/nadir/version.hpp"

namespace xos {
namespace app {
namespace console {
namespace version {

/// class maint
template 
<class TVersion = xos::lib::nadir::version, 
 class TExtends = xos::app::console::version::main_optt<>,  class TImplements = typename TExtends::implements>

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

    typedef TVersion version_t;

    /// constructor / destructor
    maint(): run_(0) {
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
    /// ...version_usage_run
    virtual int version_usage_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = this->all_version_run(argc, argv, env))) {
            this->outln();
            if (!(err = this->all_usage(argc, argv, env))) {
            } else {
            }
        } else {
        }
        return err;
    }
    //////////////////////////////////////////////////////////////////////////
    /// version_run
    virtual int version_run(int argc, char_t** argv, char_t** env) {
        const ::xos::lib::version& version = version_t::which();
        const ::xos::lib::version::char_t *version_chars = 0, *name_chars = 0;
        ::xos::lib::version::string_t version_string;
        int err = 0;
        if ((version_chars = version.to_chars(version_string)) && (name_chars = version.name())) {
            ::xos::lib::version::string_t version_name(name_chars);
            version_name.append(" version = ");
            version_name.append(version_string);
            this->outln(version_name);
        } else {
        }
        return err;
    }
    //////////////////////////////////////////////////////////////////////////
    /// default_run
    virtual int default_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = this->all_version_usage_run(argc, argv, env))) {
        } else {
        }
        return err;
    }
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
protected:
}; /// class maint 
typedef maint<> main;

} /// namespace version 
} /// namespace console 
} /// namespace app 
} /// namespace xos 

#endif /// ndef XOS_APP_CONSOLE_VERSION_MAIN_HPP

