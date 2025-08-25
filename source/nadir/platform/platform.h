/*/
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
///   File: platform.h
///
/// Author: $author$
///   Date: 9/17/2016
///////////////////////////////////////////////////////////////////////
/*/
#ifndef _NADIR_PLATFORM_PLATFORM_H
#define _NADIR_PLATFORM_PLATFORM_H

#include "nadir/platform/platform_build.h"
#include "nadir/platform/platform_compiler.h"
#include "nadir/platform/platform_includes.h"
#include "nadir/platform/platform_defines.h"
#include "nadir/platform/platform_types.h"
#include "nadir/platform/platform_api.h"

#if defined(WINDOWS)  
#include "nadir/platform/platform_windows.h"
#else /*/ defined(WINDOWS)  /*/
#include "nadir/platform/platform_unix.h"
#endif /*/ defined(WINDOWS)  /*/

#if defined(__cplusplus)  
#else /*/ defined(__cplusplus)  /*/
#endif /*/ defined(__cplusplus)  /*/

#if defined(__cplusplus)
namespace nadir {
#endif /*/ defined(__cplusplus)  /*/

#if defined(__cplusplus)
} /*/ namespace nadir /*/
#endif /*/ defined(__cplusplus)  /*/

#endif /*/ _NADIR_PLATFORM_PLATFORM_H /*/
