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
///   File: logger_location.hpp
///
/// Author: $author$
///   Date: 5/20/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_IO_LOGGER_LOCATION_HPP
#define _NADIR_IO_LOGGER_LOCATION_HPP

#include "nadir/io/logger_function.hpp"
#include "nadir/base/string.hpp"

namespace nadir {
namespace io {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS logger_location: public char_string {
public:
    typedef char_string Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    logger_location
    (const char* function_name, const char* file_name, size_t line_number)
    : function_name_(function_name),
      file_name_(file_name),
      line_number_(line_number) {
    }
    logger_location
    (const logger_location& copy)
    : function_name_(copy.function_name_),
      file_name_(copy.file_name_),
      line_number_(copy.line_number_) {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    inline char_string function_name() const { return function_name_; }
    inline char_string file_name() const { return file_name_; }
    inline char_string line_number() const {
        return char_string().assign_unsigned(line_number_);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    char_string function_name_;
    char_string file_name_;
    size_t line_number_;
};

} // namespace io
} // namespace nadir 

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

#if !defined(LOGGER_LOCATION)
#if !defined(__LOGGER_FUNC__)
#if defined(__GNUC__)
#define __LOGGER_FUNC__ __FUNCTION__
#else // defined(__GNUC__)
#if defined(_MSC_VER)
#if (_MSC_VER >= 1300)
#define __LOGGER_FUNC__ __FUNCTION__
#else // (_MSC_VER >= 1300)
#define __LOGGER_FUNC__ ""
#endif // (_MSC_VER >= 1300)
#else // defined(_MSC_VER)
#define __LOGGER_FUNC__ ""
#endif // defined(_MSC_VER)
#endif // defined(__GNUC__)
#endif // !defined(__LOGGER_FUNC__)
#define LOGGER_LOCATION ::nadir::io::logger::location(__LOGGER_FUNC__, __FILE__, __LINE__)
#endif // !defined(LOGGER_LOCATION)

#endif // _NADIR_IO_LOGGER_LOCATION_HPP
