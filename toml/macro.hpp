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
#if defined(__GNUC__) && defined(__GNUC_MINOR__) && defined(__GNUC_PATCHLEVEL__) && !defined(__clang__)
#  if (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) <= 40805
#    define TOML11_WORKAROUND_GCC_4_8_X_STANDARD_LIBRARY_IMPLEMENTATION
#  endif
#endif

#endif// TOML11_MACRO_HPP
