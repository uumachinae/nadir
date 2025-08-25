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
///   File: Logger.hpp
///
/// Author: $author$
///   Date: 12/22/2018
///////////////////////////////////////////////////////////////////////
#ifndef _PATRONA_IO_LOGGER_HPP
#define _PATRONA_IO_LOGGER_HPP

#include "patrona/base/Base.hpp"

#if defined(USE_CRONO_LOGGER)
#include "crono/io/Logger.hpp"
#define PATRONA_LOG_ERROR CRONO_LOG_ERROR
#define PATRONA_LOG_DEBUG CRONO_LOG_DEBUG
#define PATRONA_LOG_TRACE CRONO_LOG_TRACE
#define PATRONA_ERR_LOG_ERROR CRONO_ERR_LOG_ERROR
#define PATRONA_ERR_LOG_DEBUG CRONO_ERR_LOG_DEBUG
#define PATRONA_ERR_LOG_TRACE CRONO_ERR_LOG_TRACE
#else // defined(USE_CRONO_LOGGER)
#if defined(USE_NADIR_LOGGER)
#include "nadir/io/logger.hpp"
#define PATRONA_LOG_ERROR NADIR_LOG_ERROR
#define PATRONA_LOG_DEBUG NADIR_LOG_DEBUG
#define PATRONA_LOG_TRACE NADIR_LOG_TRACE
#define PATRONA_ERR_LOG_ERROR NADIR_ERR_LOG_ERROR
#define PATRONA_ERR_LOG_DEBUG NADIR_ERR_LOG_DEBUG
#define PATRONA_ERR_LOG_TRACE NADIR_ERR_LOG_TRACE
#else // defined(USE_NADIR_LOGGER)
#define PATRONA_LOG_ERROR(...)
#define PATRONA_LOG_DEBUG(...)
#define PATRONA_LOG_TRACE(...)
#define PATRONA_ERR_LOG_ERROR(...)
#define PATRONA_ERR_LOG_DEBUG(...)
#define PATRONA_ERR_LOG_TRACE(...)
#endif // defined(USE_NADIR_LOGGER)
#endif // defined(USE_CRONO_LOGGER)

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#if !defined(LOG_ERROR)
#define LOG_ERROR PATRONA_LOG_ERROR
#endif // !defined(LOG_ERROR)

#if !defined(LOG_DEBUG)
#define LOG_DEBUG PATRONA_LOG_DEBUG
#endif // !defined(LOG_DEBUG)

#if !defined(LOG_TRACE)
#define LOG_TRACE PATRONA_LOG_TRACE
#endif // !defined(LOG_TRACE)

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#if !defined(ERR_LOG_ERROR)
#define ERR_LOG_ERROR PATRONA_ERR_LOG_ERROR
#endif // !defined(ERR_LOG_ERROR)

#if !defined(ERR_LOG_DEBUG)
#define ERR_LOG_DEBUG PATRONA_ERR_LOG_DEBUG
#endif // !defined(ERR_LOG_DEBUG)

#if !defined(ERR_LOG_TRACE)
#define ERR_LOG_TRACE PATRONA_ERR_LOG_TRACE
#endif // !defined(ERR_LOG_TRACE)

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

namespace patrona {
namespace io {

} // namespace io 
} // namespace patrona 

#endif // _PATRONA_IO_LOGGER_HPP 
