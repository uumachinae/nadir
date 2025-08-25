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
///   File: platform_defines.h
///
/// Author: $author$
///   Date: 9/17/2016
///////////////////////////////////////////////////////////////////////
/*/
#ifndef _NADIR_PLATFORM_PLATFORM_DEFINES_H
#define _NADIR_PLATFORM_PLATFORM_DEFINES_H

#include "nadir/platform/platform_build.h"

#if defined(WINDOWS)
/*/
// Windows
// ...
/*/
#if !defined(__GNUC__)
/*/
// Microsoft C/C++
// ...
/*/
/*/
// ...
// Microsoft C/C++
/*/
#else /*/ !defined(__GNUC__) /*/
/*/
// Gnu C/C++
// ...
/*/
#if defined(CPLATFORM_DEFINED_DEBUG)
#error Compiler other than Microsoft C/C++ (Gnu C/C++) being used
#endif /*/ defined(CPLATFORM_DEFINED_DEBUG) /*/
/*/
// ...
// Gnu C/C++
/*/
#endif /*/ !defined(__GNUC__) /*/

#if defined(UNICODE)
#define TCHAR_NOT_CHAR
#endif /*/ defined(UNICODE) /*/

#define PLATFORM_EXPORT __declspec(dllexport)
#define PLATFORM_IMPORT __declspec(dllimport)

#define FOREIGN_DIRECTORY_SEPARATOR_CHAR '/'
#define PLATFORM_DIRECTORY_SEPARATOR_CHAR '\\'
#define PLATFORM_VOLUME_SEPARATOR_CHAR ':'
/*/
// ...
// Windows
/*/
#else /*/ defined(WINDOWS) /*/
/*/
// Unix
// ...
/*/
#if defined(__GNUC__)
/*/
// Gnu C/C++
// ...
/*/
/*/
// ...
// Gnu C/C++
/*/
#else /*/ defined(__GNUC__) /*/
#error Compiler other than Gnu C/C++ not supported
#endif /*/ defined(__GNUC__) /*/

#define PLATFORM_EXPORT
#define PLATFORM_IMPORT

#if defined(unix)
#define PLATFORM_unix unix
#undef unix
#endif /*/ defined(unix) /*/

#if defined(MACOSX)
/*/
// MacOSX
// ...
/*/
#if !defined(PLATFORM_HAS_NO_EXECVPE)
#define PLATFORM_HAS_NO_EXECVPE
#endif /*/ !defined(PLATFORM_HAS_NO_EXECVPE) /*/
/*/
// ...
// MacOSX
/*/
#endif /*/ defined(MACOSX) /*/

#define FOREIGN_DIRECTORY_SEPARATOR_CHAR '\\'
#define PLATFORM_DIRECTORY_SEPARATOR_CHAR '/'
#define PLATFORM_VOLUME_SEPARATOR_CHAR 0

#define TRUE 1
#define FALSE 0

#define INFINITE -1

#define WINAPI
#define FAR
#define _In_
#define _Out_
#define _Inout_
#define _In_opt_
#define _Out_opt_
#define _Inout_opt_
/*/
// ...
// Unix
/*/
#endif /*/ defined(WINDOWS) /*/

#if defined(__MSC__)
/*/
// Microsoft C/C++
// ...
/*/
#define PACKED_STRUCT
/*/
// ...
// Microsoft C/C++
/*/
#else /*/ defined(__MSC__) /*/
#if defined(__GNUC__)
/*/
// Gnu C/C++
// ...
/*/
#define PACKED_STRUCT __attribute__ ((packed))
/*/
// ...
// Gnu C/C++
/*/
#else /*/ defined(__GNUC__) /*/
#error Compiler not supported
#endif /*/ defined(__GNUC__) /*/
#endif /*/ defined(__MSC__) /*/

/*/
// Generic
// ...
/*/
#define UNDEFINED -1

#define NULL_POINTER_VALUE ((void*)(0))

#define INVALID_HANDLE INVALID_HANDLE_VALUE
#define NULL_HANDLE NULL_HANDLE_VALUE
#define NULL_ATOM NULL_ATOM_VALUE
#define NULL_POINTER NULL_POINTER_VALUE

#define NULL_BYTE 0
#define NULL_CHAR 0
#define NULL_TCHAR 0
#define NULL_WCHAR 0

#if defined(NO_TEMPLATE_PARAMETER_CAST)
/*/
// Can't cast template parameters
/*/
#define V_INVALID_HANDLE 0
#define V_NULL_HANDLE 0
#define V_NULL_ATOM 0
#else /*/ defined(NO_TEMPLATE_PARAMETER_CAST) /*/
#define V_INVALID_HANDLE INVALID_HANDLE
#define V_NULL_HANDLE NULL_HANDLE
#define V_NULL_ATOM NULL_ATOM
#endif /*/ defined(NO_TEMPLATE_PARAMETER_CAST) /*/

#define PLATFORM_EXTENSION_SEPARATOR "."
#define FOREIGN_EXTENSION_SEPARATOR PLATFORM_EXTENSION_SEPARATOR

#define PLATFORM_EXTENSION_SEPARATOR_CHAR '.'
#define FOREIGN_EXTENSION_SEPARATOR_CHAR PLATFORM_EXTENSION_SEPARATOR_CHAR

#define _PLATFORM_IMPORT PLATFORM_IMPORT
#define _PLATFORM_EXPORT PLATFORM_EXPORT

#define c_EXPORT PLATFORM_EXPORT
#define c_IMPORT PLATFORM_IMPORT

#if defined(DELETE)
#define PLATFORM_DELETE DELETE
#undef DELETE
#endif /*/ defined(DELETE) /*/
/*/
// ...
// Generic
/*/

#if defined(__cplusplus)
/*/
/// C++
/// ...
/*/
#define EXPORT_CLASS PLATFORM_EXPORT
#define INTERFACE_CLASS PLATFORM_EXPORT

#if !defined(NO_IMPLEMENT_CLASS)
#define IMPLEMENT_CLASS PLATFORM_EXPORT
#endif /*/ !defined(NO_IMPLEMENT_CLASS) /*/

#define INSTANCE_CLASS PLATFORM_EXPORT

#define _EXPORT_CLASS PLATFORM_EXPORT
#define _INTERFACE_CLASS PLATFORM_EXPORT
#define _IMPLEMENT_CLASS PLATFORM_EXPORT
#define _INSTANCE_CLASS PLATFORM_EXPORT

#define c_EXPORT_CLASS PLATFORM_EXPORT
#define c_INTERFACE_CLASS PLATFORM_EXPORT
#define c_IMPLEMENT_CLASS PLATFORM_EXPORT
#define c_INSTANCE_CLASS PLATFORM_EXPORT
/*/
/// ...
/// C++
/*/
#endif /*/ defined(__cplusplus)  /*/

#if defined(__cplusplus)
namespace nadir {
#endif /*/ defined(__cplusplus)  /*/

#if defined(__cplusplus)
#else /*/ defined(__cplusplus)  /*/
#endif /*/ defined(__cplusplus)  /*/

#if defined(__cplusplus)
} /*/ namespace nadir /*/
#endif /*/ defined(__cplusplus)  /*/

#endif /*/ _NADIR_PLATFORM_PLATFORM_DEFINES_H /*/
