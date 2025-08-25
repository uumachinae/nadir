/*/
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
///   File: platform_unix.h
///
/// Author: $author$
///   Date: 2/25/2017
///////////////////////////////////////////////////////////////////////
/*/
#ifndef _NADIR_PLATFORM_PLATFORM_UNIX_H
#define _NADIR_PLATFORM_PLATFORM_UNIX_H

#include "nadir/platform/platform_types.h"

#if !defined(WINDOWS)
/*/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////*/
typedef struct _SECURITY_ATTRIBUTES {
  DWORD  nLength;
  LPVOID lpSecurityDescriptor;
  BOOL   bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

#endif /*/ !defined(WINDOWS) /*/

#if defined(__cplusplus)
namespace nadir {
#endif /*/ defined(__cplusplus)  /*/

#if defined(__cplusplus)
} /*/ namespace nadir /*/
#endif /*/ defined(__cplusplus)  /*/

#endif // _NADIR_PLATFORM_PLATFORM_UNIX_H 
