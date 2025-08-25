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
///   File: logger_level.hpp
///
/// Author: $author$
///   Date: 5/20/2017, 2/27/2024
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_IO_LOGGER_LEVEL_HPP
#define _NADIR_IO_LOGGER_LEVEL_HPP

#include "nadir/base/base.hpp"

namespace nadir {
namespace io {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef unsigned logger_level;
enum {
    logger_level_fatal_shift = 0,
    logger_level_error_shift,
    logger_level_warn_shift,
    logger_level_info_shift,
    logger_level_debug_shift,
    logger_level_trace_shift,

    next_logger_level_shift
};
enum {
    logger_level_none  = 0,

    logger_level_fatal = (1 << logger_level_fatal_shift),
    logger_level_error = (1 << logger_level_error_shift),
    logger_level_warn  = (1 << logger_level_warn_shift),
    logger_level_info  = (1 << logger_level_info_shift),
    logger_level_debug = (1 << logger_level_debug_shift),
    logger_level_trace = (1 << logger_level_trace_shift),

    next_logger_level  = (1 << next_logger_level_shift),
    all_logger_level   = (next_logger_level - 1),
    logger_level_all = all_logger_level,

    logger_message_level_none  = 0,

    logger_message_level_fatal = (logger_level_fatal << next_logger_level_shift),
    logger_message_level_error = (logger_level_error << next_logger_level_shift),
    logger_message_level_warn  = (logger_level_warn << next_logger_level_shift),
    logger_message_level_info  = (logger_level_info << next_logger_level_shift),
    logger_message_level_debug = (logger_level_debug << next_logger_level_shift),
    logger_message_level_trace = (logger_level_trace << next_logger_level_shift),

    next_logger_message_level  = (next_logger_level << next_logger_level),
    all_logger_message_level   = (all_logger_level << next_logger_level),
    logger_message_level_all = all_logger_message_level
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef logger_level logger_levels;
enum {
    logger_levels_fatal_shift = 1,
    logger_levels_error_shift,
    logger_levels_warn_shift,
    logger_levels_info_shift,
    logger_levels_debug_shift,
    logger_levels_trace_shift,

    next_logger_levels_shift
};
enum {
    logger_levels_none  = 0,

    logger_levels_fatal = ((1 << (logger_levels_fatal_shift)) - 1),
    logger_levels_error = ((1 << (logger_levels_error_shift)) - 1),
    logger_levels_warn  = ((1 << (logger_levels_warn_shift)) - 1),
    logger_levels_info  = ((1 << (logger_levels_info_shift)) - 1),
    logger_levels_debug = ((1 << (logger_levels_debug_shift)) - 1),
    logger_levels_trace = ((1 << (logger_levels_trace_shift)) - 1),

    next_logger_levels  = ((1 << (next_logger_levels_shift)) - 1),
    all_logger_levels   = (next_logger_levels >> 1),
    logger_levels_all = all_logger_levels,

    logger_message_levels_none  = 0,

    logger_message_levels_fatal = (logger_levels_fatal << (next_logger_levels_shift - 1)),
    logger_message_levels_error = (logger_levels_error << (next_logger_levels_shift - 1)),
    logger_message_levels_warn  = (logger_levels_warn << (next_logger_levels_shift - 1)),
    logger_message_levels_info  = (logger_levels_info << (next_logger_levels_shift - 1)),
    logger_message_levels_debug = (logger_levels_debug << (next_logger_levels_shift - 1)),
    logger_message_levels_trace = (logger_levels_trace << (next_logger_levels_shift - 1)),

    next_logger_message_levels  = (next_logger_levels << (next_logger_levels_shift - 1)),
    all_logger_message_levels   = (all_logger_levels << (next_logger_levels_shift - 1)),
    logger_message_levels_all = all_logger_message_levels
};

} // namespace io
} // namespace nadir 

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define LOGGING_LEVELS_ALL ::nadir::io::logger::levels_all
#define LOGGING_LEVELS_NONE ::nadir::io::logger::levels_none
#define LOGGING_LEVELS_FATAL ::nadir::io::logger::levels_fatal
#define LOGGING_LEVELS_ERROR ::nadir::io::logger::levels_error
#define LOGGING_LEVELS_WARN ::nadir::io::logger::levels_warn
#define LOGGING_LEVELS_INFO ::nadir::io::logger::levels_info
#define LOGGING_LEVELS_DEBUG ::nadir::io::logger::levels_debug
#define LOGGING_LEVELS_TRACE ::nadir::io::logger::levels_trace

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define LOGGING_MESSAGE_LEVELS_ALL ::nadir::io::logger::message_levels_all
#define LOGGING_MESSAGE_LEVELS_NONE ::nadir::io::logger::message_levels_none
#define LOGGING_MESSAGE_LEVELS_FATAL ::nadir::io::logger::message_levels_fatal
#define LOGGING_MESSAGE_LEVELS_ERROR ::nadir::io::logger::message_levels_error
#define LOGGING_MESSAGE_LEVELS_WARN ::nadir::io::logger::message_levels_warn
#define LOGGING_MESSAGE_LEVELS_INFO ::nadir::io::logger::message_levels_info
#define LOGGING_MESSAGE_LEVELS_DEBUG ::nadir::io::logger::message_levels_debug
#define LOGGING_MESSAGE_LEVELS_TRACE ::nadir::io::logger::message_levels_trace

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#if !defined(LOGGING_LEVELS_DEFAULT)
#if defined(XOS_DEFAULT_LOG_TRACE)
#define LOGGING_LEVELS_DEFAULT LOGGING_LEVELS_TRACE
#elif defined(XOS_DEFAULT_LOG_DEBUG)
#define LOGGING_LEVELS_DEFAULT LOGGING_LEVELS_DEBUG
#elif defined(XOS_DEFAULT_LOG_ERROR)
#define LOGGING_LEVELS_DEFAULT LOGGING_LEVELS_ERROR
#else // defined(XOS_DEFAULT_LOG_TRACE)
#endif // defined(XOS_DEFAULT_LOG_TRACE)
#endif // !defined(LOGGING_LEVELS_DEFAULT)

#if !defined(LOGGING_LEVELS_DEFAULT)
#if defined(DEFAULT_LOG_TRACE)
#define LOGGING_LEVELS_DEFAULT LOGGING_LEVELS_TRACE
#elif defined(DEFAULT_LOG_DEBUG)
#define LOGGING_LEVELS_DEFAULT LOGGING_LEVELS_DEBUG
#elif defined(DEFAULT_LOG_ERROR)
#define LOGGING_LEVELS_DEFAULT LOGGING_LEVELS_ERROR
#else // defined(DEFAULT_LOG_TRACE)
#endif // defined(DEFAULT_LOG_TRACE)
#endif // !defined(LOGGING_LEVELS_DEFAULT)

#if !defined(LOGGING_LEVELS_DEFAULT)
#if defined(DEFAULT_LOGGING_LEVELS_TRACE)
#define LOGGING_LEVELS_DEFAULT LOGGING_LEVELS_TRACE
#elif defined(DEFAULT_LOGGING_LEVELS_DEBUG)
#define LOGGING_LEVELS_DEFAULT LOGGING_LEVELS_DEBUG
#elif defined(DEFAULT_LOGGING_LEVELS_ERROR)
#define LOGGING_LEVELS_DEFAULT LOGGING_LEVELS_ERROR
#else // defined(DEFAULT_LOGGING_LEVELS_TRACE)
#endif // defined(DEFAULT_LOGGING_LEVELS_TRACE)
#endif // !defined(LOGGING_LEVELS_DEFAULT)

#if !defined(LOGGING_LEVELS_DEFAULT)
#if defined(TRACE_BUILD)
#define LOGGING_LEVELS_DEFAULT LOGGING_LEVELS_TRACE
#else // defined(TRACE_BUILD)
#if defined(DEBUG_BUILD)
#define LOGGING_LEVELS_DEFAULT LOGGING_LEVELS_DEBUG
#else // defined(DEBUG_BUILD)
#define LOGGING_LEVELS_DEFAULT LOGGING_LEVELS_ERROR
#endif // defined(DEBUG_BUILD)
#endif // defined(TRACE_BUILD)
#endif // !defined(LOGGING_LEVELS_DEFAULT)

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

#endif // _NADIR_IO_LOGGER_LEVEL_HPP
