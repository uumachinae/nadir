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
///   File: String.hpp
///
/// Author: $author$
///   Date: 12/22/2018
///////////////////////////////////////////////////////////////////////
#ifndef _PATRONA_BASE_STRING_HPP
#define _PATRONA_BASE_STRING_HPP

#include "patrona/base/Base.hpp"

#define PATRONA_STRING_DEFAULT_SIZE 128

namespace patrona {

typedef ImplementBase StringTImplements;
typedef Base StringTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: StringT
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char_t, typename TEnd = TChar, TEnd VEnd = 0,
 typename TSize = size_t, TSize VSize = PATRONA_STRING_DEFAULT_SIZE,
 class TImplements = StringTImplements, class TExtends = StringTExtends>

class _EXPORT_CLASS StringT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TChar char_t;
    typedef TSize size_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    StringT(const char_t* chars, size_t length)
    : m_writeBuffer(m_defaultBuffer), m_readBuffer(m_defaultBuffer),
      m_size(VSize), m_length(0), m_tell(0),
      m_freeBuffer(false), m_fixedSize(false) {
        Append(chars, length);
    }
    StringT(const char_t* chars)
    : m_writeBuffer(m_defaultBuffer), m_readBuffer(m_defaultBuffer),
      m_size(VSize), m_length(0), m_tell(0),
      m_freeBuffer(false), m_fixedSize(false) {
        Append(chars);
    }
    StringT(const StringT& copy)
    : m_writeBuffer(m_defaultBuffer), m_readBuffer(m_defaultBuffer),
      m_size(VSize), m_length(0), m_tell(0),
      m_freeBuffer(false), m_fixedSize(false) {
        Append(copy);
    }
    StringT()
    : m_writeBuffer(m_defaultBuffer), m_readBuffer(m_defaultBuffer),
      m_size(VSize), m_length(0), m_tell(0),
      m_freeBuffer(false), m_fixedSize(false) {
    }
    virtual ~StringT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual StringT& Assign(const StringT& copy) {
        return Append(copy.Chars(), copy.Length());
    }
    virtual StringT& Assign(const char_t* chars) {
        return Append(chars, _length_of(chars));
    }
    virtual StringT& Assign(const char_t* chars, size_t length) {
        return Append(chars, length);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual StringT& Append(const StringT& copy) {
        return Append(copy.Chars(), copy.Length());
    }
    virtual StringT& Append(const char_t* chars) {
        return Append(chars, _length_of(chars));
    }
    virtual StringT& Append(const char_t* chars, size_t length) {
        if ((chars) && (0 < length)) {
            size_t newSize = (m_tell+length);
            if (m_size <= newSize) {
                if (m_fixedSize) {
                    length = m_size-m_tell;
                } else {
                    if (!(_adjust_to_size(_new_size_of(newSize)))) {
                        length = 0;
                    }
                }
            }
            if (length) {
                _copy_to(m_writeBuffer+m_tell, chars, length);
                if ((m_tell += length) > m_length) {
                    if ((m_length = m_tell) < m_size) {
                        m_writeBuffer[m_tell] = (char_t)(VEnd);
                    }
                }
            }
        }
        return *this;
    }
    virtual StringT& Clear() {
        if ((m_writeBuffer)) {
            if (m_size > (m_length = (m_tell = 0))) {
                m_writeBuffer[m_tell] = (char_t)(VEnd);
            }
        }
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Compare(const StringT& to) const {
        return Compare(to.Chars(), to.Length());
    }
    virtual int Compare(const char_t* toChars) const {
        return Compare(toChars, _length_of(toChars));
    }
    virtual int Compare(const char_t* toChars, size_t toLength) const {
        int unequal = 2;
        const char_t* thisChars = 0;
        char_t toChar = 0, thisChar = 0;
        size_t thisLength = 0;
        ssize_t lendiff = 0;

        if (!(thisChars = (this->Chars()))) {
            return (toChars)?(-1):(1);
        }
        if (0 < (lendiff = (toLength - (thisLength = this->Length())))) {
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

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual char_t* Buffer() const {
        return m_writeBuffer;
    }
    virtual const char_t* Chars() const {
        return m_readBuffer;
    }
    virtual size_t Length() const {
        return m_length;
    }
    virtual size_t Size() const {
        return m_size;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual StringT& operator = (const StringT& copy) {
        return Assign(copy.Chars(), copy.Length());
    }
    virtual int operator != (const StringT& to) const {
        return Compare(to);
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t adjust_size(size_t newSize) {
        if (!m_writeBuffer) {
            return 0;
        }
        if (m_size < (newSize)) {
            if (m_fixedSize) {
                return 0;
            } else {
                if (1 > (_adjust_to_size(_new_size_of(newSize)))) {
                    return 0;
                }
            }
        }
        return m_size;
    }
    virtual size_t _adjust_to_size(size_t size) {
        bool freeBuffer = false;
        char_t* buffer = 0;

        if (!m_writeBuffer) {
            return 0;
        }
        if (size <= m_size) {
            return m_size;
        }
        if (!(freeBuffer = m_freeBuffer)) {
            m_freeBuffer = true;
        }
        if (!(buffer = _alloc_buffer(size))) {
            m_freeBuffer = freeBuffer;
            return 0;
        }
        if (m_writeBuffer) {
            if (m_length > 0) {
                _copy_to(buffer, m_writeBuffer, m_length);
            }
            if ((m_writeBuffer != m_defaultBuffer) && (freeBuffer)) {
                _free_buffer(m_writeBuffer);
            }
        }
        m_writeBuffer = buffer;
        m_readBuffer = buffer;
        m_size = size;
        return m_size;
    }
    virtual char_t* _alloc_buffer(size_t size) const {
        char_t* chars = new char_t[size];
        return chars;
    }
    virtual void _free_buffer(char_t* buffer) const {
        delete[] buffer;
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
        return ((size/VSize)+1)*VSize;
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
        const char_t endChar = ((char_t)(VEnd));
        size_t length = 0;
        for (length = 0; ((*chars) != endChar); chars++) {
            length++;
        }
        return length;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    char_t m_defaultBuffer[VSize], *m_writeBuffer;
    const char_t* m_readBuffer;
    size_t m_size, m_length, m_tell;
    bool m_freeBuffer, m_fixedSize;
};

} // namespace patrona 

#endif // _PATRONA_BASE_STRING_HPP 
