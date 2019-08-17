#ifndef TOML11_FORWARD_DECLARATION_HPP
#define TOML11_FORWARD_DECLARATION_HPP
#include <unordered_map>
#include <vector>
#include <string>
#include <iosfwd>
#include <cstdint>

namespace toml
{

struct discard_comments;
struct preserve_comments;

using key = std::string;

template<typename Comment,
         template<typename ...> class Table,
         template<typename ...> class Array>
class basic_value;

using value = basic_value<discard_comments, std::unordered_map, std::vector>;
using array = std::vector<value>;
using table = std::unordered_map<key, value>;

enum class value_t  : std::uint8_t;

using boolean        = bool;
using integer        = std::int64_t;
using floating       = double;

enum class string_t : std::uint8_t;
struct string;

enum class month_t  : std::uint8_t;
struct local_date;
struct local_time;
struct local_datetime;
struct time_offset;
struct offset_datetime;

struct exception;
struct syntax_error;
struct type_error;
struct internal_error;

template<typename T>
struct from;
template<typename T>
struct into;

template<typename T>
struct success;
template<typename T>
struct failure;
template<typename T, typename E>
struct result;

template<typename Comment,
         template<typename ...> class Table,
         template<typename ...> class Array>
struct serializer;

struct source_location;

} // toml
#endif//TOML11_FORWARD_DECLARATION_HPP
