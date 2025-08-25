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
///   File: entry.cpp
///
/// Author: $author$
///   Date: 1/4/2017
///////////////////////////////////////////////////////////////////////
#include "nadir/os/microsoft/windows/fs/entry.hpp"

#if !defined(WINDOWS)
#include "nadir/os/fs/directory/path.hpp"
class _EXPORT_CLASS FindFile {
public:
    FindFile() {}
    virtual ~FindFile() {}
    virtual BOOL FindFileW(
      _In_  LPCWSTR           lpFileName,
      _Out_ LPWIN32_FIND_DATAW lpFindFileData
    ) {
        nadir::char_string name(lpFileName);
        const char* chars = 0;
        size_t length = 0;
        if ((chars = name.has_chars(length)) && (lpFindFileData)) {
            WIN32_FIND_DATAW& ff = *lpFindFileData;
            memset(&ff, 0, sizeof(WIN32_FIND_DATAW));
            if ((path_.open(chars))) {
                if (length >= MAX_PATH) {
                    length = (MAX_PATH - 1);
                }
                nadir::wchars_t::copy(ff.cFileName, lpFileName, length);
                ff.dwFileAttributes |= FILE_ATTRIBUTE_DIRECTORY;
                return TRUE;
            }
        }
        return FALSE;
    }
    virtual BOOL FindFirstFileW(
      _In_  LPCWSTR           lpFileName,
      _Out_ LPWIN32_FIND_DATAW lpFindFileData
    ) {
        if ((lpFileName) && (lpFileName[0])) {
            nadir::char_string name(lpFileName);
            const char* chars = 0;
            size_t length = 0;
            if ((chars = name.has_chars(length))) {
                if (('*' == chars[length-1])) {
                    if ((2 < length)) {
                        nadir::wchar_string wpath(chars, length-2);
                        const wchar_t* wchars = 0;
                        if ((wchars = wpath.has_chars()) && (lpFindFileData)) {
                            if (FindFileW(wchars, lpFindFileData)) {
                                WIN32_FIND_DATAW& ff = *lpFindFileData;
                                nadir::fs::entry* e = 0;
                                memset(&ff, 0, sizeof(WIN32_FIND_DATAW));
                                if ((e = path_.get_first_entry())) {
                                    if ((chars = e->name(length))) {
                                        wpath.assign(chars, length);
                                        if ((wchars = wpath.has_chars(length))) {
                                            if (length >= MAX_PATH) {
                                                length = (MAX_PATH - 1);
                                            }
                                            nadir::wchars_t::copy(ff.cFileName, wchars, length);
                                            return TRUE;
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    return FindFileW(lpFileName, lpFindFileData);
                }
            }
        }
        return FALSE;
    }
    virtual BOOL FindNextFileW(
      _Out_ LPWIN32_FIND_DATAW lpFindFileData
    ) {
        if ((lpFindFileData)) {
            WIN32_FIND_DATAW& ff = *lpFindFileData;
            nadir::fs::entry* e = 0;
            memset(&ff, 0, sizeof(WIN32_FIND_DATAW));
            if ((e = path_.get_next_entry())) {
                const char* chars = 0;
                size_t length = 0;
                if ((chars = e->name(length))) {
                    nadir::wchar_string wpath(chars, length);
                    const wchar_t* wchars = 0;
                    if ((wchars = wpath.has_chars(length))) {
                        if (length >= MAX_PATH) {
                            length = (MAX_PATH - 1);
                        }
                        nadir::wchars_t::copy(ff.cFileName, wchars, length);
                        return TRUE;
                    }
                }
            }
        }
        return FALSE;
    }
    virtual BOOL FindClose() {
        return path_.close();
    }
protected:
    nadir::os::fs::directory::path path_;
};
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
BOOL WINAPI FileTimeToLocalFileTime(
  _In_  const FILETIME   *lpFileTime,
  _Out_       LPFILETIME lpLocalFileTime
) {
    return FALSE;
}
BOOL WINAPI FileTimeToSystemTime(
  _In_  const FILETIME     *lpFileTime,
  _Out_       LPSYSTEMTIME lpSystemTime
) {
    return FALSE;
}
BOOL WINAPI SystemTimeToFileTime(
  _In_  const SYSTEMTIME *lpSystemTime,
  _Out_       LPFILETIME lpFileTime
) {
    return FALSE;
}
HANDLE WINAPI FindFirstFileW(
  _In_  LPCWSTR           lpFileName,
  _Out_ LPWIN32_FIND_DATAW lpFindFileData
) {
    FindFile* ff = 0;
    if ((ff = new FindFile)) {
        if ((ff->FindFirstFileW(lpFileName, lpFindFileData))) {
            return ff;
        }
        delete ff;
    }
    return INVALID_HANDLE_VALUE;
}
BOOL WINAPI FindNextFileW(
  _In_  HANDLE            hFindFile,
  _Out_ LPWIN32_FIND_DATAW lpFindFileData
) {
    FindFile* ff = 0;
    if ((ff = ((FindFile*)hFindFile))) {
        return ff->FindNextFileW(lpFindFileData);
    }
    return FALSE;
}
BOOL WINAPI FindClose(
  _Inout_ HANDLE hFindFile
) {
    FindFile* ff = 0;
    if ((ff = ((FindFile*)hFindFile))) {
        return ff->FindClose();
    }
    return FALSE;
}
DWORD WINAPI GetLastError(void) {
    return 1;
}
#endif // !defined(WINDOWS)

namespace nadir {
namespace os {
namespace microsoft {
namespace windows {
namespace fs {

} // namespace fs 
} // namespace windows 
} // namespace microsoft 
} // namespace os 
} // namespace nadir 
