#ifndef TOML11_MACRO_HPP
#define TOML11_MACRO_HPP

// Here we define utility macros.
// TODO: move other feature-checking macros defined in other headers to here

#if __cplusplus >= 201703L
#  define TOML11_CXX17_AVAILABLE
#elif  __cplusplus >= 201402L
#  define TOML11_CXX14_AVAILABLE
#elif  __cplusplus >= 201103L
#  define TOML11_CXX11_AVAILABLE
#else
#  error "toml11 requires C++11 or later"
#endif

#ifdef TOML11_CXX17_AVAILABLE
#  if __has_include(<string_view>)
#    define TOML11_STRING_VIEW_AVAILABLE
#  endif // <string_view>
#endif // c++17

// Related to the issue #97.
//
// It is known that `std::vector::insert` and `std::vector::erase` in
// the standard library implementation included in GCC 4.8.5 takes
// `std::vector::iterator` instead of `std::vector::const_iterator`.
// Because of the const-correctness, we cannot convert a `const_iterator` to
// an `iterator`. It causes compilation error in GCC 4.8.5.
//
#if defined(__GNUC__) && defined(__GNUC_MINOR__) && defined(__GNUC_PATCHLEVEL__) && !defined(__clang__)
#  if (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) <= 40805
#    define TOML11_WORKAROUND_GCC_4_8_X_STANDARD_LIBRARY_IMPLEMENTATION
#  endif
#endif

// Also, std::string::insert(..., initializer_list) has a bug of the same kind.
// In GCC 8.x.y, std::basic_string::insert() with std::initializer_list has the
// following signature.
//
// ```
// void insert(iterator, initializer_list<charT>);
// ```
//
// It is different from the spec. It should be
//
// ```
// iterator insert(const_iterator, initializer_list<charT>);
// ```
//
// We need to avoid this. This problem is resolved in GCC 9.
//
// cf. https://gcc.gnu.org/bugzilla/show_bug.cgi?id=83328
//
#if defined(__GNUC__) && defined(__GNUC_MINOR__) && defined(__GNUC_PATCHLEVEL__) && !defined(__clang__)
#  if (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) < 90000
#    define TOML11_WORKAROUND_GCC_8_X_Y_STANDARD_LIBRARY_IMPLEMENTATION
#  endif
#endif


#endif// TOML11_MACRO_HPP
