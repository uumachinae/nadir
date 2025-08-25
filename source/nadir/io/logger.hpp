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
///   File: logger.hpp
///
/// Author: $author$
///   Date: 12/30/2016
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_IO_LOGGER_HPP
#define _NADIR_IO_LOGGER_HPP

#include "nadir/io/logger_level.hpp"
#include "nadir/io/logger_function.hpp"
#include "nadir/io/logger_location.hpp"
#include "nadir/io/logger_message.hpp"
#include "nadir/io/logger_stdio.hpp"
#include "nadir/base/locked.hpp"

namespace nadir {
namespace io {

typedef locked logger_implements;
///////////////////////////////////////////////////////////////////////
///  Class: logger
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS logger: virtual public logger_implements {
public:
    typedef logger_implements Implements;

    typedef logger_function function;
    typedef logger_location location;
    typedef logger_message message;
    typedef logger_level level;
    typedef logger_levels levels;
    enum {
        level_none  = logger_level_none,
        level_fatal = logger_level_fatal,
        level_error = logger_level_error,
        level_warn  = logger_level_warn,
        level_info  = logger_level_info,
        level_debug = logger_level_debug,
        level_trace = logger_level_trace,
        all_level   = all_logger_level,
        level_all   = all_level,

        message_level_none  = logger_message_level_none,
        message_level_fatal = logger_message_level_fatal,
        message_level_error = logger_message_level_error,
        message_level_warn  = logger_message_level_warn,
        message_level_info  = logger_message_level_info,
        message_level_debug = logger_message_level_debug,
        message_level_trace = logger_message_level_trace,
        all_message_level   = all_logger_message_level,
        message_level_all   = all_message_level
    };
    enum {
        levels_none  = logger_levels_none,
        levels_fatal = logger_levels_fatal,
        levels_error = logger_levels_error,
        levels_warn  = logger_levels_warn,
        levels_info  = logger_levels_info,
        levels_debug = logger_levels_debug,
        levels_trace = logger_levels_trace,
        all_levels   = all_logger_levels,
        levels_all   = all_levels,

        message_levels_none  = logger_message_levels_none,
        message_levels_fatal = logger_message_levels_fatal,
        message_levels_error = logger_message_levels_error,
        message_levels_warn  = logger_message_levels_warn,
        message_levels_info  = logger_message_levels_info,
        message_levels_debug = logger_message_levels_debug,
        message_levels_trace = logger_message_levels_trace,
        all_message_levels   = all_logger_message_levels,
        message_levels_all   = all_message_levels
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool lock() { return true; }
    virtual bool unlock() { return true; }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool init() { return true; }
    virtual bool fini() { return true; }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void log
    (const level& _level, const location& _location, const message& _message) {
        locker lock(*this);
        if ((this->is_enabled_for(_level))) {
            this->logln(_location, _message);
        }
    }
    virtual void logf
    (const level& _level, const location& _location, const char* format, ...) {
        locker lock(*this);
        if ((this->is_enabled_for(_level))) {
            if ((format)) {
                va_list va;
                va_start(va, format);
                this->logfvln(_location, format, va);
                va_end(va);
            }
        }
    }
    virtual void logf
    (const level& _level,
     const location& _location, const message& _message, const char* format, ...) {
        locker lock(*this);
        if ((this->is_enabled_for(_level))) {
            if ((format)) {
                va_list va;
                va_start(va, format);
                this->logfvln(_location, _message, format, va);
                va_end(va);
            } else {
                this->logln(_location, _message);
            }
        }
    }
    virtual void logfv
    (const level& _level, const location& _location, const char* format, va_list va) {
        locker lock(*this);
        if ((this->is_enabled_for(_level))) {
            if ((format)) {
                this->logfvln(_location, format, va);
            }
        }
    }
    virtual void logfv
    (const level& _level, const location& _location,
     const message& _message, const char* format, va_list va) {
        locker lock(*this);
        if ((this->is_enabled_for(_level))) {
            if ((format)) {
                this->logfvln(_location, _message, format, va);
            } else {
                this->logln(_location, _message);
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void log
    (const level& _level, const message& _message) {
        locker lock(*this);
        if ((this->is_enabled_for(_level))) {
            this->log(_message);
            this->logln();
        }
    }
    virtual void logf
    (const level& _level, const char* format, ...) {
        locker lock(*this);
        if ((this->is_enabled_for(_level))) {
            if ((format)) {
                va_list va;
                va_start(va, format);
                this->logfv(format, va);
                va_end(va);
            }
            this->logln();
        }
    }
    virtual void logfv
    (const level& _level, const char* format, va_list va) {
        locker lock(*this);
        if ((this->is_enabled_for(_level))) {
            if ((format)) {
                this->logfv(format, va);
            }
            this->logln();
        }
    }
    virtual void logfv
    (const level& _level, const message& _message, const char* format, va_list va) {
        locker lock(*this);
        if ((this->is_enabled_for(_level))) {
            this->log(_message);
            if ((format)) {
                this->logfv(format, va);
            }
            this->logln();
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void enable_for(const level& _level) {}
    virtual level enabled_for() const { return enabled_for_default(); }
    virtual level enabled_for_default() const {
#if defined(DEBUG_BUILD)
        return (levels_debug | message_levels_debug);
#else // defined(DEBUG_BUILD)
        return (levels_error | message_levels_error);
#endif // defined(DEBUG_BUILD)
    }
    virtual bool is_enabled_for(const level& _level) const {
        level _enabled_for = enabled_for();
		level anded = _enabled_for & _level;
        if ((_level) && (_level == (_enabled_for & _level))) {
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static logger* set_the_logger(logger* to) {
        logger *old_logger = the_logger();
        the_logger() = to;
        return old_logger;
    }
    static logger* get_the_logger() {
        return the_logger();
    }
protected:
    static logger*& the_logger() {
        static logger *the_logger = 0;
        return the_logger;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void logln(const location& _location, const message& _message) {
        this->log(_location);
        this->log(_message);
        this->logln();
    }
    virtual void logln(const function& _function, const message& _message) {
        this->log(_function);
        this->log(_message);
        this->logln();
    }
    virtual void logln(const message& _message) {
        this->log(_message);
        this->logln();
    }
    virtual void logfvln
    (const location& _location,
     const message& _message, const char* format, va_list va) {
        this->log(_location);
        this->log(_message);
        if ((format)) {
            this->logfv(format, va);
        }
        this->logln();
    }
    virtual void logfvln
    (const location& _location, const char* format, va_list va) {
        this->log(_location);
        if ((format)) {
            this->logfv(format, va);
        }
        this->logln();
    }
    virtual void logfvln
    (const function& _function,
     const message& _message, const char* format, va_list va) {
        this->log(_function);
        this->log(_message);
        if ((format)) {
            this->logfv(format, va);
        }
        this->logln();
    }
    virtual void logfvln
    (const function& _function, const char* format, va_list va) {
        this->log(_function);
        if ((format)) {
            this->logfv(format, va);
        }
        this->logln();
    }
    virtual void logfvln
    (const message& _message, const char* format, va_list va) {
        this->log(_message);
        if ((format)) {
            this->logfv(format, va);
        }
        this->logln();
    }
    virtual void logfvln(const char* format, va_list va) {
        if ((format)) {
            this->logfv(format, va);
        }
        this->logln();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void log(const location& _location) {
        log(_location.file_name().chars());
        log("[");
        log(_location.line_number().chars());
        log("]");
        log(" ");
        log(_location.function_name().chars());
        log(" ");
    }
    virtual void log(const function& _function) {
        log(_function.chars());
    }
    virtual void log(const message& _message) {
        log(_message.chars());
    }
    virtual void logf(const char* format, ...) {
        va_list va;
        va_start(va, format);
        logfv(format, va);
        va_end(va);
    }
    virtual void logfv(const char* format, va_list va) {
    }
    virtual void log(const char* chars, size_t length) {
    }
    virtual void log(const char* chars) {
    }
    virtual void logln() {
        log("\n");
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef logger logger_instance_implements;
typedef base logger_instance_extends;
///////////////////////////////////////////////////////////////////////
///  Class: logger_instance
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS logger_instance
: virtual public logger_instance_implements, public logger_instance_extends {
public:
    typedef logger_instance_implements Implements;
    typedef logger_instance_extends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    logger_instance(): old_logger_(the_logger()), enabled_for_(levels_none) {
        the_logger() = this;
        enabled_for_ = enabled_for_default();
    }
    virtual ~logger_instance() {
        if (this == the_logger()) {
            the_logger() = old_logger_;
        }
    }    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void enable_for(const level& _level) {
        enabled_for_ = _level;
    }
    virtual level enabled_for() const {
        return enabled_for_;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    logger* old_logger_;
    level enabled_for_;
};

} // namespace io
} // namespace nadir 

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

#define INIT_LOGGER(logger_) { \
::nadir::io::logger* logger = logger_; \
if ((logger)) { logger->init(); } }

#define FINI_LOGGER(logger_) { \
::nadir::io::logger* logger = logger_; \
if ((logger)) { logger->fini(); } }

#define SET_LOGGER_LEVEL(logger_, level_) { \
::nadir::io::logger* logger = logger_; \
if ((logger)) { logger->enable_for(level_); } }

#define GET_LOGGER_LEVEL(logger_) \
((logger_)?(logger_->enabled_for()):(::nadir::io::logger::level\
(::nadir::io::logger::levels_none)))

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define LOGGER_LOG(logger_, level_, message_) { \
::nadir::io::logger* logger = logger_; \
if ((logger)?(logger->is_enabled_for(level_)):(false)) {\
   ::nadir::io::logger::message message; \
   logger->log(level_, LOGGER_LOCATION, message << message_); } }

#define LOGGER_LOGF(logger_, level_, format_, ...) { \
::nadir::io::logger* logger = logger_; \
if ((logger)?(logger->is_enabled_for(level_)):(false)) {\
   logger->logf(level_, LOGGER_LOCATION, format_, ##__VA_ARGS__); } }

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define LOGGER_LOG_MESSAGE(logger_, level_, message_) { \
::nadir::io::logger* logger = logger_; \
if ((logger)?(logger->is_enabled_for(level_)):(false)) {\
   ::nadir::io::logger::message message; \
   logger->log(level_, message << message_); } }

#define LOGGER_LOG_MESSAGEF(logger_, level_, format_, ...) { \
::nadir::io::logger* logger = logger_; \
if ((logger)?(logger->is_enabled_for(level_)):(false)) {\
   logger->logf(level_, format_, ##__VA_ARGS__); } }

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define SET_THE_LOGGER(_logger) ::nadir::io::logger::set_the_logger(_logger)
#define THE_LOGGER ::nadir::io::logger::get_the_logger()

#define LOGGER_INIT() INIT_LOGGER(THE_LOGGER)
#define LOGGER_FINI() FINI_LOGGER(THE_LOGGER)

#define SET_LOGGING_LEVEL(level)  SET_LOGGER_LEVEL(THE_LOGGER, level)
#define GET_LOGGING_LEVEL(level)  (level = GET_LOGGER_LEVEL(THE_LOGGER))

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define LOG_FATAL(message) LOGGER_LOG(THE_LOGGER, ::nadir::io::logger::level_fatal, message)
#define LOG_ERROR(message) LOGGER_LOG(THE_LOGGER, ::nadir::io::logger::level_error, message)
#define LOG_WARN(message) LOGGER_LOG(THE_LOGGER, ::nadir::io::logger::level_warn, message)
#define LOG_INFO(message) LOGGER_LOG(THE_LOGGER, ::nadir::io::logger::level_info, message)
#define LOG_DEBUG(message) LOGGER_LOG(THE_LOGGER, ::nadir::io::logger::level_debug, message)
#define LOG_TRACE(message) LOGGER_LOG(THE_LOGGER, ::nadir::io::logger::level_trace, message)

#define LOG_FATALF(message, ...) LOGGER_LOGF(THE_LOGGER, ::nadir::io::logger::level_fatal, message, ##__VA_ARGS__)
#define LOG_ERRORF(message, ...) LOGGER_LOGF(THE_LOGGER, ::nadir::io::logger::level_error, message, ##__VA_ARGS__)
#define LOG_WARNF(message, ...) LOGGER_LOGF(THE_LOGGER, ::nadir::io::logger::level_warn, message, ##__VA_ARGS__)
#define LOG_INFOF(message, ...) LOGGER_LOGF(THE_LOGGER, ::nadir::io::logger::level_info, message, ##__VA_ARGS__)
#define LOG_DEBUGF(message, ...) LOGGER_LOGF(THE_LOGGER, ::nadir::io::logger::level_debug, message, ##__VA_ARGS__)
#define LOG_TRACEF(message, ...) LOGGER_LOGF(THE_LOGGER, ::nadir::io::logger::level_trace, message, ##__VA_ARGS__)

#define IS_LOGGING_FATAL(message) if (this->is_logging()) LOG_FATAL(message)
#define IS_LOGGING_ERROR(message) if (this->is_logging()) LOG_ERROR(message)
#define IS_LOGGING_WARN(message)  if (this->is_logging()) LOG_WARN(message)
#define IS_LOGGING_INFO(message)  if (this->is_logging()) LOG_INFO(message)
#define IS_LOGGING_DEBUG(message) if (this->is_logging()) LOG_DEBUG(message)
#define IS_LOGGING_TRACE(message) if (this->is_logging()) LOG_TRACE(message)

#define IS_LOGGING_FATALF(message, ...) if (this->is_logging()) LOG_FATAL(message, ##__VA_ARGS__)
#define IS_LOGGING_ERRORF(message, ...) if (this->is_logging()) LOG_ERROR(message, ##__VA_ARGS__)
#define IS_LOGGING_WARNF(message, ...)  if (this->is_logging()) LOG_WARN(message, ##__VA_ARGS__)
#define IS_LOGGING_INFOF(message, ...)  if (this->is_logging()) LOG_INFO(message, ##__VA_ARGS__)
#define IS_LOGGING_DEBUGF(message, ...) if (this->is_logging()) LOG_DEBUG(message, ##__VA_ARGS__)
#define IS_LOGGING_TRACEF(message, ...) if (this->is_logging()) LOG_TRACE(message, ##__VA_ARGS__)

#define IS_STDERR_LOGGING_FATAL(message) if (this->is_logging()) LOG_FATAL(message) else if (this->is_stderr_logging()) STDERR_LOG_ERROR(message)
#define IS_STDERR_LOGGING_ERROR(message) if (this->is_logging()) LOG_ERROR(message) else if (this->is_stderr_logging()) STDERR_LOG_ERROR(message)
#define IS_STDERR_LOGGING_WARN(message)  if (this->is_logging()) LOG_WARN(message) else if (this->is_stderr_logging()) STDERR_LOG_DEBUG(message)
#define IS_STDERR_LOGGING_INFO(message)  if (this->is_logging()) LOG_INFO(message) else if (this->is_stderr_logging()) STDERR_LOG_DEBUG(message)
#define IS_STDERR_LOGGING_DEBUG(message) if (this->is_logging()) LOG_DEBUG(message) else if (this->is_stderr_logging()) STDERR_LOG_DEBUG(message)
#define IS_STDERR_LOGGING_TRACE(message) if (this->is_logging()) LOG_TRACE(message) else if (this->is_stderr_logging()) STDERR_LOG_TRACE(message)

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define LOG_MESSAGE_FATAL(message) LOGGER_LOG_MESSAGE(THE_LOGGER, ::nadir::io::logger::message_level_fatal, message)
#define LOG_MESSAGE_ERROR(message) LOGGER_LOG_MESSAGE(THE_LOGGER, ::nadir::io::logger::message_level_error, message)
#define LOG_MESSAGE_WARN(message) LOGGER_LOG_MESSAGE(THE_LOGGER, ::nadir::io::logger::message_level_warn, message)
#define LOG_MESSAGE_INFO(message) LOGGER_LOG_MESSAGE(THE_LOGGER, ::nadir::io::logger::message_level_info, message)
#define LOG_MESSAGE_DEBUG(message) LOGGER_LOG_MESSAGE(THE_LOGGER, ::nadir::io::logger::message_level_debug, message)
#define LOG_MESSAGE_TRACE(message) LOGGER_LOG_MESSAGE(THE_LOGGER, ::nadir::io::logger::message_level_trace, message)

#define LOG_MESSAGE_FATALF(message, ...) LOGGER_LOG_MESSAGEF(THE_LOGGER, ::nadir::io::logger::message_level_fatal, message, ##__VA_ARGS__)
#define LOG_MESSAGE_ERRORF(message, ...) LOGGER_LOG_MESSAGEF(THE_LOGGER, ::nadir::io::logger::message_level_error, message, ##__VA_ARGS__)
#define LOG_MESSAGE_WARNF(message, ...) LOGGER_LOG_MESSAGEF(THE_LOGGER, ::nadir::io::logger::message_level_warn, message, ##__VA_ARGS__)
#define LOG_MESSAGE_INFOF(message, ...) LOGGER_LOG_MESSAGEF(THE_LOGGER, ::nadir::io::logger::message_level_info, message, ##__VA_ARGS__)
#define LOG_MESSAGE_DEBUGF(message, ...) LOGGER_LOG_MESSAGEF(THE_LOGGER, ::nadir::io::logger::message_level_debug, message, ##__VA_ARGS__)
#define LOG_MESSAGE_TRACEF(message, ...) LOGGER_LOG_MESSAGEF(THE_LOGGER, ::nadir::io::logger::message_level_trace, message, ##__VA_ARGS__)

#define IS_LOGGING_MESSAGE_FATAL(message) if (this->is_logging()) LOG_MESSAGE_FATAL(message)
#define IS_LOGGING_MESSAGE_ERROR(message) if (this->is_logging()) LOG_MESSAGE_ERROR(message)
#define IS_LOGGING_MESSAGE_WARN(message)  if (this->is_logging()) LOG_MESSAGE_WARN(message)
#define IS_LOGGING_MESSAGE_INFO(message)  if (this->is_logging()) LOG_MESSAGE_INFO(message)
#define IS_LOGGING_MESSAGE_DEBUG(message) if (this->is_logging()) LOG_MESSAGE_DEBUG(message)
#define IS_LOGGING_MESSAGE_TRACE(message) if (this->is_logging()) LOG_MESSAGE_TRACE(message)

#define IS_LOGGING_MESSAGE_FATALF(message, ...) if (this->is_logging()) LOG_MESSAGE_FATAL(message, ##__VA_ARGS__)
#define IS_LOGGING_MESSAGE_ERRORF(message, ...) if (this->is_logging()) LOG_MESSAGE_ERROR(message, ##__VA_ARGS__)
#define IS_LOGGING_MESSAGE_WARNF(message, ...)  if (this->is_logging()) LOG_MESSAGE_WARN(message, ##__VA_ARGS__)
#define IS_LOGGING_MESSAGE_INFOF(message, ...)  if (this->is_logging()) LOG_MESSAGE_INFO(message, ##__VA_ARGS__)
#define IS_LOGGING_MESSAGE_DEBUGF(message, ...) if (this->is_logging()) LOG_MESSAGE_DEBUG(message, ##__VA_ARGS__)
#define IS_LOGGING_MESSAGE_TRACEF(message, ...) if (this->is_logging()) LOG_MESSAGE_TRACE(message, ##__VA_ARGS__)

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

#endif // _NADIR_IO_LOGGER_HPP
