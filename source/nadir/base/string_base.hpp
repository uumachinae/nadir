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
///   File: string_base.hpp
///
/// Author: $author$
///   Date: 1/13/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_BASE_STRING_BASE_HPP
#define _NADIR_BASE_STRING_BASE_HPP

#include "nadir/base/base.hpp"

#define NADIR_BASE_STRING_BASE_DEFAULT_SIZE 128

namespace nadir {

typedef implement_base string_base_implements;
typedef base string_base_extends;
///////////////////////////////////////////////////////////////////////
///  Class: string_baset
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char_t, typename TSize = size_t,
 TSize VDefaultSize = NADIR_BASE_STRING_BASE_DEFAULT_SIZE,
 typename TEndChar = TChar, TEndChar VEndChar = 0,
 class TExtends = string_base_extends,
 class TImplements = string_base_implements>

class _EXPORT_CLASS string_baset
: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TChar char_t;
    typedef TSize size_t;
    typedef TEndChar end_char_t;
    enum { default_size = VDefaultSize };
    enum { end_char = VEndChar };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    string_baset(const char_t* chars, size_t length) {
        construct();
        append(chars, length);
    }
    string_baset(const char_t* chars) {
        construct();
        append(chars);
    }
    string_baset(const string_baset& copy) {
        construct();
        append(copy.c_str(), copy.length());
    }
    string_baset() {
        construct();
    }
    virtual ~string_baset(){
        if ((m_writeBuffer != m_defaultBuffer)) {
            if ((m_writeBuffer) && (m_freeBuffer)) {
                _free_buffer(m_writeBuffer);
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    string_baset& assign(const char_t* chars, size_t length) {
        clear();
        return append(chars, length);
    }
    string_baset& assign(const char_t* chars) {
        clear();
        return append(chars);
    }
    string_baset& assign(const string_baset& copy) {
        clear();
        return append(copy.c_str(), copy.length());
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    string_baset& append(const char_t* chars, size_t length) {
        if ((chars) && (0 < length)) {
            size_t newSize = (m_tell+length);
            if (m_size <= newSize) {
                if (m_fixedSize)
                    length = m_size-m_tell;
                else
                if (!(_adjust_to_size(_new_size_of(newSize))))
                    length = 0;
            }
            if (length) {
                _copy_to(m_writeBuffer+m_tell, chars, length);
                if ((m_tell += length) > m_length)
                if ((m_length = m_tell) < m_size)
                    m_writeBuffer[m_tell] = ((char_t)end_char);
            }
        }
        return *this;
    }
    string_baset& append(const char_t* chars) {
        return append(chars, _length_of(chars));
    }
    string_baset& append(const string_baset& copy) {
        return append(copy.c_str(), copy.length());
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    string_baset& clear() {
        if ((m_writeBuffer)) {
            if (m_size > (m_length = (m_tell = 0))) {
                m_writeBuffer[m_tell] = ((char_t)end_char);
            }
        }
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int compare(const string_baset& to) {
        return compare(to.c_str(), to.length());
    }
    virtual int compare(const char_t* toChars, size_t toLength) {
        int unequal = 2;
        const char_t* thisChars = 0;
        char_t toChar = 0, thisChar = 0;
        size_t thisLength = 0;
        ssize_t lendiff = 0;

        if (!(thisChars = (c_str()))) {
            return (toChars)?(-1):(1);
        }

        if (0 < (lendiff = (toLength - (thisLength = length())))) {
            toLength = thisLength;
            unequal = -1;
        } else {
            if (lendiff) {
                unequal = 1;
            }
        }

        if (toLength > 0) {
            do {
                if ((thisChar = *(thisChars++)) > (toChar = *(toChars++))) {
                    return 1;
                } else {
                    if (thisChar < toChar) {
                        return -1;
                    }
                }
            } while (--toLength > 0);
        }
        return unequal;
    }
    virtual int compare(const char_t* toChars) {
        return compare(toChars, _length_of(toChars));
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual string_baset& operator = (const string_baset& copy) {
        assign(copy.c_str(), copy.length());
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual char_t* buffer() const {
        return str();
    }
    virtual const char_t* chars() const {
        return c_str();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual char_t* str() const {
        return m_writeBuffer;
    }
    virtual const char_t* c_str() const {
        return m_readBuffer;
    }
    virtual size_t length() const {
        return m_length;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void construct() {
        m_freeBuffer = m_fixedSize = false;
        m_size = default_size;
        m_length = m_tell = 0;
        m_readBuffer = m_writeBuffer = m_defaultBuffer;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t adjust_size(size_t newSize) {
        if (m_writeBuffer) {
            if (m_size < (newSize)) {
                if (!m_fixedSize) {
                    if (0 < (_adjust_to_size(_new_size_of(newSize)))) {
                        return m_size;
                    }
                }
            } else {
                return m_size;
            }
        }
        return 0;
    }
    virtual size_t _adjust_to_size(size_t size) {
        if (m_writeBuffer) {
            if (size > m_size) {
                bool freeBuffer = false;
                char_t* buffer = 0;

                if (!(freeBuffer = m_freeBuffer)) {
                    m_freeBuffer = true;
                }
                if ((buffer = _alloc_buffer(size))) {
                    if (m_length > 0) {
                        _copy_to(buffer, m_writeBuffer, m_length);
                    }
                    if ((m_writeBuffer != m_defaultBuffer) && (freeBuffer)) {
                        _free_buffer(m_writeBuffer);
                    }
                    m_readBuffer = m_writeBuffer = buffer;
                    m_size = size;
                    return m_size;
                } else {
                    m_freeBuffer = freeBuffer;
                }
            } else {
                return m_size;
            }
        }
        return 0;
    }
    virtual size_t _new_size_of(size_t size) const {
        // Lets increase the buffer size by default buffer
        // sized chunks. Note the desired new size is always
        // needed size + 1. The size in chunks is calculated
        // as (new size + (chunk size - 1)) / chunk size.
        // since new size = needed size + 1 then we have
        // chunks = (needed size + chunk size) / chunk size.
        // Finally we need bytes which is chunks * chunk size
        // which can be reduced to
        // ((needed size / chunk size) + 1) * chunk size
        //
        return ((size/default_size)+1)*default_size;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t _copy_to(char_t* to, const char_t* from, size_t size) const {
        size_t length = 0;

        for (length = size; size; --size) {
            (*to++) = (*from++);
        }
        return length;
    }
    virtual size_t _length_of(const char_t* chars) const {
        const char_t endChar(((char_t)end_char));
        size_t length = 0;

        for (length = 0; ((*chars) != endChar); chars++) {
            length++;
        }
        return length;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual char_t* _alloc_buffer(size_t size) const {
        char_t* chars = new char_t[size];
        return chars;
    }
    virtual void _free_buffer(char_t* buffer) const {
        delete[] buffer;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool m_freeBuffer;
    bool m_fixedSize;

    size_t m_size;
    size_t m_length;
    size_t m_tell;

    const char_t* m_readBuffer;
    char_t* m_writeBuffer;
    char_t m_defaultBuffer[default_size];
};

typedef string_baset<char_t> string_base;
typedef string_baset<wchar_t> wstring_base;
typedef string_baset<tchar_t> tstring_base;

} // namespace nadir

#endif // _NADIR_BASE_STRING_BASE_HPP 
