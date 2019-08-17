#include "toml.hpp"

#ifndef TOML11_BUILD_LIBRARY
#error "defining a macro TOML11_BUILD_LIBRARY is required to build a library"
#endif

namespace toml
{

template class basic_value<discard_comments,  std::unordered_map, std::vector>;
template class basic_value<preserve_comments, std::unordered_map, std::vector>;
template class basic_value<discard_comments,  std::map, std::vector>;
template class basic_value<preserve_comments, std::map, std::vector>;

template basic_value<discard_comments,  std::unordered_map, std::vector> parse(const std::string& fname);
template basic_value<preserve_comments, std::unordered_map, std::vector> parse(const std::string& fname);
template basic_value<discard_comments,  std::map, std::vector>           parse(const std::string& fname);
template basic_value<preserve_comments, std::map, std::vector>           parse(const std::string& fname);

template struct serializer<discard_comments,  std::unordered_map, std::vector>;
template struct serializer<preserve_comments, std::unordered_map, std::vector>;
template struct serializer<discard_comments,  std::map, std::vector>;
template struct serializer<preserve_comments, std::map, std::vector>;

template std::string format(const basic_value<discard_comments,  std::unordered_map, std::vector>&, std::size_t, int, bool, bool);
template std::string format(const basic_value<preserve_comments, std::unordered_map, std::vector>&, std::size_t, int, bool, bool);
template std::string format(const basic_value<discard_comments,  std::map, std::vector>&, std::size_t, int, bool, bool);
template std::string format(const basic_value<preserve_comments, std::map, std::vector>&, std::size_t, int, bool, bool);

template std::ostream& operator<<(std::ostream&, const basic_value<discard_comments,  std::unordered_map, std::vector>&);
template std::ostream& operator<<(std::ostream&, const basic_value<preserve_comments, std::unordered_map, std::vector>&);
template std::ostream& operator<<(std::ostream&, const basic_value<discard_comments,  std::map, std::vector>&);
template std::ostream& operator<<(std::ostream&, const basic_value<preserve_comments, std::map, std::vector>&);

} // toml
