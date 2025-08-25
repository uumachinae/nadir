///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2019 $organization$
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
///   File: time.hpp
///
/// Author: $author$
///   Date: 12/25/2019
///////////////////////////////////////////////////////////////////////
#ifndef XOS_TIME_HPP
#define XOS_TIME_HPP

#include "xos/base/base.hpp"

namespace xos {

/// mseconds_ seconds / mseconds / useconds / nseconds
/// ...
inline seconds_t mseconds_seconds
(mseconds_t mseconds) { return mseconds / 1000; }

inline mseconds_t mseconds_mseconds
(mseconds_t mseconds) { return mseconds % 1000; }

inline mseconds_t useconds_mseconds
(useconds_t useconds) { return useconds / 1000; }

inline useconds_t mseconds_useconds
(mseconds_t mseconds) { return mseconds * 1000; }

inline nseconds_t mseconds_nseconds
(mseconds_t mseconds) { return mseconds_useconds(mseconds) * 1000; }

inline nseconds_t useconds_nseconds
(useconds_t useconds) { return useconds * 1000; }

inline mseconds_t seconds_mseconds
(seconds_t seconds) { return seconds * 1000; }

inline useconds_t seconds_useconds
(seconds_t seconds) { return seconds_mseconds(seconds) * 1000; }

inline nseconds_t seconds_nseconds
(seconds_t seconds) { return seconds_useconds(seconds) * 1000; }

inline useconds_t nseconds_useconds
(nseconds_t nseconds) { return nseconds / 1000; }

inline mseconds_t nseconds_mseconds
(nseconds_t nseconds) { return nseconds_useconds(nseconds) / 1000; }

inline seconds_t nseconds_seconds
(nseconds_t nseconds) { return nseconds_mseconds(nseconds) / 1000; }

inline nseconds_t nseconds_nseconds
(mseconds_t nseconds) { return nseconds % (1000 * 1000 * 1000); }

/// ...
/// mseconds_ seconds / mseconds / useconds / nseconds

} /// namespace xos

#endif /// ndef XOS_TIME_HPP
