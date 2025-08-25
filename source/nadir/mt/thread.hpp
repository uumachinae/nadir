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
///   File: thread.hpp
///
/// Author: $author$
///   Date: 1/15/2018
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_MT_THREAD_HPP
#define _NADIR_MT_THREAD_HPP

#include "nadir/base/ran.hpp"
#include "nadir/base/suspended.hpp"
#include "nadir/base/joined.hpp"
#include "nadir/base/created.hpp"

namespace nadir {
namespace mt {

///////////////////////////////////////////////////////////////////////
///  Class: thread_implementst
///////////////////////////////////////////////////////////////////////
template 
<class TRan = ran, class TSuspended = suspended, class TJoined = joined>

class _EXPORT_CLASS thread_implementst
: virtual public TRan, virtual public TSuspended, virtual public TJoined {
public:
    typedef TRan ran_t;
    typedef TSuspended susupended_t;
    typedef TJoined toined_t;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef thread_implementst<> thread_implements;

typedef thread_implements threadt_implements;
///////////////////////////////////////////////////////////////////////
///  Class: threadt
///////////////////////////////////////////////////////////////////////
template <class TImplements = threadt_implements>

class _EXPORT_CLASS threadt: virtual public TImplements {
public:
    typedef TImplements Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef threadt<> thread;

} // namespace mt 
} // namespace nadir 

#endif // _NADIR_MT_THREAD_HPP 
