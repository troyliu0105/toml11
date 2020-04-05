//     Copyright Toru Niina 2017.
// Distributed under the MIT License.
#ifndef TOML11_STRING_HPP
#define TOML11_STRING_HPP
#include <algorithm>
#include <string>
#include <cstdint>
#if __cplusplus >= 201703L
#if __has_include(<string_view>)
#include <string_view>
#endif
#endif
#include "macro.hpp"

namespace toml
{

enum class string_t : std::uint8_t
{
    basic   = 0,
    literal = 1,
};

struct string
{
    using backend_type           = std::string;
    using traits_type            = typename backend_type::traits_type;
    using value_type             = typename backend_type::value_type;
    using allocator_type         = typename backend_type::allocator_type;
    using size_type              = typename backend_type::size_type;
    using difference_type        = typename backend_type::difference_type;
    using reference              = typename backend_type::reference;
    using const_reference        = typename backend_type::const_reference;
    using pointer                = typename backend_type::pointer;
    using const_pointer          = typename backend_type::const_pointer;
    using iterator               = typename backend_type::iterator;
    using const_iterator         = typename backend_type::const_iterator;
    using reverse_iterator       = typename backend_type::reverse_iterator;
    using const_reverse_iterator = typename backend_type::const_reverse_iterator;

#ifdef TOML11_STRING_VIEW_AVAILABLE
    using backend_view_type = std::string_view;
#endif

    string()  = default;
    ~string() = default;
    string(const string& s) = default;
    string(string&& s)      = default;
    string& operator=(const string& s) = default;
    string& operator=(string&& s)      = default;

    string(const backend_type& s): kind(string_t::basic), str(s){}
    string(const backend_type& s, string_t k):   kind(k), str(s){}
    string(const char* s):        kind(string_t::basic), str(s){}
    string(const char* s,        string_t k):   kind(k), str(s){}

    string(backend_type&& s): kind(string_t::basic), str(std::move(s)){}
    string(backend_type&& s, string_t k):   kind(k), str(std::move(s)){}

    string& operator=(const backend_type& s)
    {
        this->kind = string_t::basic;
        this->str  = s;
        return *this;
    }
    string& operator=(backend_type&& s)
    {
        this->kind = string_t::basic;
        this->str  = std::move(s);
        return *this;
    }

    operator backend_type&       () &      noexcept {return str;}
    operator backend_type const& () const& noexcept {return str;}
    operator backend_type&&      () &&     noexcept {return std::move(str);}

    string& operator+=(const char*         rhs) {str += rhs;     return *this;}
    string& operator+=(const char          rhs) {str += rhs;     return *this;}
    string& operator+=(const backend_type& rhs) {str += rhs;     return *this;}
    string& operator+=(const string&       rhs) {str += rhs.str; return *this;}

    iterator        begin()       noexcept {return str.begin();}
    iterator        end()         noexcept {return str.end();}
    const_iterator  begin() const noexcept {return str.begin();}
    const_iterator  end()   const noexcept {return str.end();}
    const_iterator cbegin() const noexcept {return str.cbegin();}
    const_iterator cend()   const noexcept {return str.cend();}

    reverse_iterator        rbegin()       noexcept {return str.rbegin();}
    reverse_iterator        rend()         noexcept {return str.rend();}
    const_reverse_iterator  rbegin() const noexcept {return str.rbegin();}
    const_reverse_iterator  rend()   const noexcept {return str.rend();}
    const_reverse_iterator crbegin() const noexcept {return str.crbegin();}
    const_reverse_iterator crend()   const noexcept {return str.crend();}

    size_type size()     const noexcept {return str.size();}
    size_type length()   const noexcept {return str.length();}
    size_type max_size() const noexcept {return str.max_size();}
    size_type capacity() const noexcept {return str.capacity();}
    bool      empty()    const noexcept {return str.empty();}

    void resize (size_type n, value_type c) {str.resize(n, c); return;}
    void resize (size_type n)               {str.resize(n);    return;}
    void reserve(size_type n)               {str.reserve(n);   return;}

    void shrink_to_fit() {str.shrink_to_fit(); return;}
    void clear()         {str.clear();         return;}

    const_reference operator[](size_type i) const noexcept {return str[i];}
    reference       operator[](size_type i)       noexcept {return str[i];}
    const_reference at(size_type i) const {return str.at(i);}
    reference       at(size_type i)       {return str.at(i);}

    const_reference front() const {return str.front();}
    reference       front()       {return str.front();}
    const_reference back()  const {return str.back();}
    reference       back()        {return str.back();}

    const_pointer c_str() const noexcept {return str.c_str();}
    const_pointer data()  const noexcept {return str.data();}

    string substr(size_type pos = 0, size_type n = backend_type::npos) const
    {
        return string(this->str.substr(pos, n), this->kind);
    }

    // ------------------------------------------------------------------------

    template<typename Target>
    size_type find(const Target& target, size_type pos = 0) const noexcept
    {
        return str.find(target, pos);
    }
    size_type find(const value_type* target, size_type pos, size_type n) const
    {
        return str.find(target, pos, n);
    }

    template<typename Target>
    size_type rfind(const Target& target, size_type pos = 0) const noexcept
    {
        return str.rfind(target, pos);
    }
    size_type rfind(const value_type* target, size_type pos, size_type n) const
    {
        return str.rfind(target, pos, n);
    }

    template<typename Target>
    size_type find_first_of(const Target& target, size_type pos = 0) const noexcept
    {
        return str.find_first_of(target, pos);
    }
    size_type find_first_of(const value_type* target, size_type pos, size_type n) const
    {
        return str.find_first_of(target, pos, n);
    }
    template<typename Target>
    size_type find_last_of(const Target& target, size_type pos = 0) const noexcept
    {
        return str.find_last_of(target, pos);
    }
    size_type find_last_of(const value_type* target, size_type pos, size_type n) const
    {
        return str.find_last_of(target, pos, n);
    }

    template<typename Target>
    size_type find_first_not_of(const Target& target, size_type pos = 0) const noexcept
    {
        return str.find_first_not_of(target, pos);
    }
    size_type find_first_not_of(const value_type* target, size_type pos, size_type n) const
    {
        return str.find_first_not_of(target, pos, n);
    }
    template<typename Target>
    size_type find_last_not_of(const Target& target, size_type pos = 0) const noexcept
    {
        return str.find_last_not_of(target, pos);
    }
    size_type find_last_not_of(const value_type* target, size_type pos, size_type n) const
    {
        return str.find_last_not_of(target, pos, n);
    }

    // ------------------------------------------------------------------------

    void push_back(value_type c) {str.push_back(c);}
    void pop_back ()             {str.pop_back();}

    // ------------------------------------------------------------------------

    string& append(const backend_type& other)
    {
        str.append(other);
        return *this;
    }
    string& append(const backend_type& other, size_type pos,
                   size_type n = backend_type::npos)
    {
        str.append(other, pos, n);
        return *this;
    }
    string& append(const value_type* other)
    {
        str.append(other);
        return *this;
    }
    string& append(const value_type* other, size_type pos)
    {
        str.append(other, pos);
        return *this;
    }
    string& append(const size_type n, value_type c)
    {
        str.append(n, c);
        return *this;
    }
    string& append(std::initializer_list<value_type> il)
    {
        str.append(std::move(il));
        return *this;
    }
    template<typename InputIterator>
    string& append(InputIterator first, InputIterator last)
    {
        str.append(first, last);
        return *this;
    }

    // ------------------------------------------------------------------------

    string& assign(const backend_type& t)
    {
        str.assign(t);
        return *this;
    }
    string& assign(const backend_type& t, size_type pos,
                   size_type n = backend_type::npos)
    {
        str.assign(t, pos, n);
        return *this;
    }
    string& assign(const value_type* t)
    {
        str.assign(t);
        return *this;
    }
    string& assign(const value_type* t, size_type pos)
    {
        str.assign(t, pos);
        return *this;
    }
    string& assign(const size_type n, value_type c)
    {
        str.assign(n, c);
        return *this;
    }
    string& assign(std::initializer_list<value_type> il)
    {
        str.assign(std::move(il));
        return *this;
    }
    template<typename InputIterator>
    string& assign(InputIterator first, InputIterator last)
    {
        str.assign(first, last);
        return *this;
    }

    // ------------------------------------------------------------------------
    // The following macro will be used from insert, erase, and replace.
    // This will be undef-ed later.
    //
    // It is known that `std::vector::insert` and `std::vector::erase` in
    // the standard library implementation included in GCC 4.8.5 takes
    // `std::vector::iterator` instead of `std::vector::const_iterator`.
    // Because of the const-correctness, we cannot convert a `const_iterator` to
    // an `iterator`. It causes compilation error in GCC 4.8.5.

#ifdef TOML11_WORKAROUND_GCC_4_8_X_STANDARD_LIBRARY_IMPLEMENTATION
// C++03 library implementations. GCC 4.8.x does not update the implementation.
#  define TOML11_GCC48X_WORKAROUND_ITERATOR    iterator
#  define TOML11_GCC48X_WORKAROUND_RETURN_TYPE void
#else
// C++11 library implementations
#  define TOML11_GCC48X_WORKAROUND_ITERATOR    const_iterator
#  define TOML11_GCC48X_WORKAROUND_RETURN_TYPE iterator
#endif

#ifdef TOML11_WORKAROUND_GCC_8_X_Y_STANDARD_LIBRARY_IMPLEMENTATION
#  define TOML11_GCC8XY_WORKAROUND_ITERATOR    iterator
#  define TOML11_GCC8XY_WORKAROUND_RETURN_TYPE void
#else
#  define TOML11_GCC8XY_WORKAROUND_ITERATOR    const_iterator
#  define TOML11_GCC8XY_WORKAROUND_RETURN_TYPE iterator
#endif

    string& insert(size_type pos1, const backend_type& t)
    {
        str.insert(pos1, t);
        return *this;
    }
    string& insert(size_type pos1, const backend_type& t,
                   size_type pos2, size_type n = backend_type::npos)
    {
        str.insert(pos1, t, pos2, n);
        return *this;
    }
    string& insert(size_type pos1, const value_type* t)
    {
        str.insert(pos1, t);
        return *this;
    }
    string& insert(size_type pos, const value_type* t, size_type n)
    {
        str.insert(pos, t, n);
        return *this;
    }
    string& insert(size_type pos, size_type n, value_type c)
    {
        str.insert(pos, n, c);
        return *this;
    }

    iterator insert(TOML11_GCC48X_WORKAROUND_ITERATOR p, value_type c)
    {
        return str.insert(p, c);
    }
    TOML11_GCC48X_WORKAROUND_RETURN_TYPE
    insert(TOML11_GCC48X_WORKAROUND_ITERATOR p, size_type n, value_type c)
    {
        return str.insert(p, n, c);
    }
    template<class InputIterator>
    TOML11_GCC48X_WORKAROUND_RETURN_TYPE
    insert(TOML11_GCC48X_WORKAROUND_ITERATOR p,
           InputIterator first, InputIterator last)
    {
        return str.insert(p, first, last);
    }
    TOML11_GCC8XY_WORKAROUND_RETURN_TYPE
    insert(TOML11_GCC8XY_WORKAROUND_ITERATOR p,
           std::initializer_list<value_type> il)
    {
        return str.insert(p, std::move(il));
    }

    // ------------------------------------------------------------------------

    string&  erase(size_type pos = 0, size_type n = backend_type::npos)
    {
        str.erase(pos, n);
        return *this;
    }
    iterator erase(TOML11_GCC48X_WORKAROUND_ITERATOR p)
    {
        return str.erase(p);
    }
    iterator erase(TOML11_GCC48X_WORKAROUND_ITERATOR first,
                   TOML11_GCC48X_WORKAROUND_ITERATOR last)
    {
        return str.erase(first, last);
    }

    // ------------------------------------------------------------------------

    string& replace(size_type pos1, size_type n1, const backend_type& t)
    {
        str.replace(pos1, n1, t);
        return *this;
    }
    string& replace(size_type pos1, size_type n1, const backend_type& t,
                    size_type pos2, size_type n2 = backend_type::npos)
    {
        str.replace(pos1, n1, t, pos2, n2);
        return *this;
    }
    string& replace(size_type pos1, size_type n1, const value_type* s,
                    size_type n2)
    {
        str.replace(pos1, n1, s, n2);
        return *this;
    }
    string& replace(size_type pos1, size_type n1, const value_type* s)
    {
        str.replace(pos1, n1, s);
        return *this;
    }
    string& replace(TOML11_GCC48X_WORKAROUND_ITERATOR i1,
                    TOML11_GCC48X_WORKAROUND_ITERATOR i2,
                    const backend_type& s)
    {
        str.replace(i1, i2, s);
        return *this;
    }
    string& replace(TOML11_GCC48X_WORKAROUND_ITERATOR i1,
                    TOML11_GCC48X_WORKAROUND_ITERATOR i2,
                    const value_type* s, size_type n)
    {
        str.replace(i1, i2, s, n);
        return *this;
    }
    string& replace(TOML11_GCC48X_WORKAROUND_ITERATOR i1,
                    TOML11_GCC48X_WORKAROUND_ITERATOR i2,
                    const value_type* s)
    {
        str.replace(i1, i2, s);
        return *this;
    }
    string& replace(TOML11_GCC48X_WORKAROUND_ITERATOR i1,
                    TOML11_GCC48X_WORKAROUND_ITERATOR i2,
                    size_type n, value_type c)
    {
        str.replace(i1, i2, n, c);
        return *this;
    }
    template<typename InputIterator>
    string& replace(TOML11_GCC48X_WORKAROUND_ITERATOR i1,
                    TOML11_GCC48X_WORKAROUND_ITERATOR i2,
                    InputIterator first, InputIterator last)
    {
        str.replace(i1, i2, first, last);
        return *this;
    }
    string& replace(TOML11_GCC48X_WORKAROUND_ITERATOR i1,
                    TOML11_GCC48X_WORKAROUND_ITERATOR i2,
                    std::initializer_list<value_type> il)
    {
        str.replace(i1, i2, std::move(il));
        return *this;
    }

#undef TOML11_GCC48X_WORKAROUND_ITERATOR
#undef TOML11_GCC48X_WORKAROUND_RETURN_TYPE
#undef TOML11_GCC8XY_WORKAROUND_ITERATOR
#undef TOML11_GCC8XY_WORKAROUND_RETURN_TYPE

    // ------------------------------------------------------------------------

    template<typename T>
    int compare(const T& t) const
    {
        return str.compare(t);
    }
    template<typename T>
    int compare(size_type pos1, size_type n1, const T& t) const
    {
        return str.compare(pos1, n1, t);
    }
    template<typename T>
    int compare(size_type pos1, size_type n1, const T& t,
                size_type n2 = backend_type::npos) const
    {
        return str.compare(pos1, n1, t, n2);
    }
    template<typename T>
    int compare(size_type pos1, size_type n1, const T& t,
                size_type pos2, size_type n2 = backend_type::npos) const
    {
        return str.compare(pos1, n1, t, pos2, n2);
    }

    // ------------------------------------------------------------------------

    allocator_type get_allocator() const noexcept {return str.get_allocator();}

    size_type copy(value_type* s, size_type n, size_type p = 0) const
    {
        return str.copy(s, n, p);
    }

    void swap(string& other)
    {
        using std::swap;
        swap(this->kind, other.kind);
        swap(this->str,  other.str);
        return;
    }

#ifdef TOML11_STRING_VIEW_AVAILABLE
    explicit string(backend_view_type s): kind(string_t::basic), str(s){}
    string(backend_view_type s, string_t k): kind(k), str(s){}

    string& operator=(backend_view_type s)
    {
        this->kind = string_t::basic;
        this->str  = s;
        return *this;
    }
    explicit operator backend_view_type() const noexcept
    {
        return backend_view_type(str);
    }
    string& operator+=(const backend_view_type& rhs)
    {
        str += rhs;
        return *this;
    }
#endif // <string_view>

#ifdef TOML11_CXX17_AVAILABLE
    // non-const data() method available after C++17
    pointer data() noexcept {return str.data();}
#endif // C++17

    string_t    kind;
    std::string str;
};

inline void swap(string& lhs, string& rhs)
{
    lhs.swap(rhs);
    return;
}

inline bool operator==(const string& lhs, const string& rhs)
{
    return lhs.kind == rhs.kind && lhs.str == rhs.str;
}
inline bool operator!=(const string& lhs, const string& rhs)
{
    return !(lhs == rhs);
}
inline bool operator<(const string& lhs, const string& rhs)
{
    return (lhs.kind == rhs.kind) ? (lhs.str < rhs.str) : (lhs.kind < rhs.kind);
}
inline bool operator>(const string& lhs, const string& rhs)
{
    return rhs < lhs;
}
inline bool operator<=(const string& lhs, const string& rhs)
{
    return !(rhs < lhs);
}
inline bool operator>=(const string& lhs, const string& rhs)
{
    return !(lhs < rhs);
}

inline bool
operator==(const string& lhs, const std::string& rhs) {return lhs.str == rhs;}
inline bool
operator!=(const string& lhs, const std::string& rhs) {return lhs.str != rhs;}
inline bool
operator< (const string& lhs, const std::string& rhs) {return lhs.str <  rhs;}
inline bool
operator> (const string& lhs, const std::string& rhs) {return lhs.str >  rhs;}
inline bool
operator<=(const string& lhs, const std::string& rhs) {return lhs.str <= rhs;}
inline bool
operator>=(const string& lhs, const std::string& rhs) {return lhs.str >= rhs;}

inline bool
operator==(const std::string& lhs, const string& rhs) {return lhs == rhs.str;}
inline bool
operator!=(const std::string& lhs, const string& rhs) {return lhs != rhs.str;}
inline bool
operator< (const std::string& lhs, const string& rhs) {return lhs <  rhs.str;}
inline bool
operator> (const std::string& lhs, const string& rhs) {return lhs >  rhs.str;}
inline bool
operator<=(const std::string& lhs, const string& rhs) {return lhs <= rhs.str;}
inline bool
operator>=(const std::string& lhs, const string& rhs) {return lhs >= rhs.str;}

inline bool
operator==(const string& lhs, const char* rhs) {return lhs.str == std::string(rhs);}
inline bool
operator!=(const string& lhs, const char* rhs) {return lhs.str != std::string(rhs);}
inline bool
operator< (const string& lhs, const char* rhs) {return lhs.str <  std::string(rhs);}
inline bool
operator> (const string& lhs, const char* rhs) {return lhs.str >  std::string(rhs);}
inline bool
operator<=(const string& lhs, const char* rhs) {return lhs.str <= std::string(rhs);}
inline bool
operator>=(const string& lhs, const char* rhs) {return lhs.str >= std::string(rhs);}

inline bool
operator==(const char* lhs, const string& rhs) {return std::string(lhs) == rhs.str;}
inline bool
operator!=(const char* lhs, const string& rhs) {return std::string(lhs) != rhs.str;}
inline bool
operator< (const char* lhs, const string& rhs) {return std::string(lhs) <  rhs.str;}
inline bool
operator> (const char* lhs, const string& rhs) {return std::string(lhs) >  rhs.str;}
inline bool
operator<=(const char* lhs, const string& rhs) {return std::string(lhs) <= rhs.str;}
inline bool
operator>=(const char* lhs, const string& rhs) {return std::string(lhs) >= rhs.str;}

template<typename charT, typename traits>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, const string& s)
{
    if(s.kind == string_t::basic)
    {
        if(std::find(s.str.cbegin(), s.str.cend(), '\n') != s.str.cend())
        {
            // it contains newline. make it multiline string.
            os << "\"\"\"\n";
            for(auto i=s.str.cbegin(), e=s.str.cend(); i!=e; ++i)
            {
                switch(*i)
                {
                    case '\\': {os << "\\\\"; break;}
                    case '\"': {os << "\\\""; break;}
                    case '\b': {os << "\\b";  break;}
                    case '\t': {os << "\\t";  break;}
                    case '\f': {os << "\\f";  break;}
                    case '\n': {os << '\n';   break;}
                    case '\r':
                    {
                        // since it is a multiline string,
                        // CRLF is not needed to be escaped.
                        if(std::next(i) != e && *std::next(i) == '\n')
                        {
                            os << "\r\n";
                            ++i;
                        }
                        else
                        {
                            os << "\\r";
                        }
                        break;
                    }
                    default: {os << *i; break;}
                }
            }
            os << "\\\n\"\"\"";
            return os;
        }
        // no newline. make it inline.
        os << "\"";
        for(const auto c : s.str)
        {
            switch(c)
            {
                case '\\': {os << "\\\\"; break;}
                case '\"': {os << "\\\""; break;}
                case '\b': {os << "\\b";  break;}
                case '\t': {os << "\\t";  break;}
                case '\f': {os << "\\f";  break;}
                case '\n': {os << "\\n";  break;}
                case '\r': {os << "\\r";  break;}
                default  : {os << c;      break;}
            }
        }
        os << "\"";
        return os;
    }
    // the string `s` is literal-string.
    if(std::find(s.str.cbegin(), s.str.cend(), '\n') != s.str.cend() ||
       std::find(s.str.cbegin(), s.str.cend(), '\'') != s.str.cend() )
    {
        // contains newline or single quote. make it multiline.
        os << "'''\n" << s.str << "'''";
        return os;
    }
    // normal literal string
    os << '\'' << s.str << '\'';
    return os;
}

} // toml
#endif// TOML11_STRING_H
