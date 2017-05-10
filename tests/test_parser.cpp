#define BOOST_TEST_MODULE "test_barekey"
#ifdef UNITTEST_FRAMEWORK_LIBRARY_EXIST
#include <boost/test/unit_test.hpp>
#else
#define BOOST_TEST_NO_LIB
#include <boost/test/included/unit_test.hpp>
#endif
#include <toml/acceptor.hpp>
#include <toml/parser.hpp>
#include <toml/from_toml.hpp>
#include <iostream>


BOOST_AUTO_TEST_CASE(test_parse_basic_inline_string)
{
    typedef toml::parse_basic_inline_string parser;
    typedef toml::is_basic_inline_string<toml::charactor> acceptor;
    {
        const std::string source("\"simple\"");
        const std::string expected("simple");
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string source("\"I'm a string. \\\"You can quote me\\\". Name\\tJos\\u00E9\\nLocation\\tSF.\"");
        const std::string expected("I'm a string. \"You can quote me\". Name\tJosé\nLocation\tSF.");
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string source("dummy");
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(!result.first.ok());
        BOOST_CHECK(result.second == source.begin());
    }
}

BOOST_AUTO_TEST_CASE(test_parse_basic_multiline_string)
{
    typedef toml::parse_basic_multiline_string parser;
    typedef toml::is_basic_multiline_string<toml::charactor> acceptor;
    {
        //XXX ifdef windows platform
        const std::string source("\"\"\"\nRoses are red\nViolets are blue\"\"\"");
        const std::string expected("Roses are red\nViolets are blue");
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string source("\"\"\"\nThe quick brown \\\n\n  fox jumps over \\\n    the lazy dog.\"\"\"");
        const std::string expected("The quick brown fox jumps over the lazy dog.");
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string source("\"\"\"\nThe quick brown \\\n    fox jumps over \\\n    the lazy dog.\\\n    \"\"\"");
        const std::string expected("The quick brown fox jumps over the lazy dog.");
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string source("dummy");
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(!result.first.ok());
        BOOST_CHECK(result.second == source.begin());
    }
}

BOOST_AUTO_TEST_CASE(test_parse_literal_inline_string)
{
    typedef toml::parse_literal_inline_string parser;
    typedef toml::is_literal_inline_string<toml::charactor> acceptor;
    {
        const std::string source("'C:\\Users\\nodejs\\templates'");
        const std::string expected("C:\\Users\\nodejs\\templates");
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string source("'\\\\ServerX\\admin$\\system32\\'");
        const std::string expected("\\\\ServerX\\admin$\\system32\\");
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string source("'Tom \"Dubs\" Preston-Werner'");
        const std::string expected("Tom \"Dubs\" Preston-Werner");
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string source("'<\\i\\c*\\s*>'");
        const std::string expected("<\\i\\c*\\s*>");
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string source("dummy");
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(!result.first.ok());
        BOOST_CHECK(result.second == source.begin());
    }
}

BOOST_AUTO_TEST_CASE(test_parse_literal_multiline_string)
{
    typedef toml::parse_literal_multiline_string parser;
    typedef toml::is_literal_multiline_string<toml::charactor> acceptor;
    {
        const std::string source("'''I [dw]on't need \\d{2} apples'''");
        const std::string expected("I [dw]on't need \\d{2} apples");
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string source("'''\nThe first newline is \ntrimmed in raw strings.\n    All other whitespace\n    is preserved.'''");
        const std::string expected("The first newline is \ntrimmed in raw strings.\n    All other whitespace\n    is preserved.");
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string source("dummy");
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(!result.first.ok());
        BOOST_CHECK(result.second == source.begin());
    }
}

BOOST_AUTO_TEST_CASE(test_parse_string)
{
    typedef toml::parse_string parser;
    typedef toml::is_string<toml::charactor> acceptor;
    {
        const std::string source("\"string\"");
        const std::string expected("string");
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string source("\"\"\"string\"\"\"");
        const std::string expected("string");
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string source("'string'");
        const std::string expected("string");
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string source("'''string'''");
        const std::string expected("string");
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string source("dummy");
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(!result.first.ok());
        BOOST_CHECK(result.second == source.begin());
    }
}

BOOST_AUTO_TEST_CASE(test_integer)
{
    typedef toml::parse_integer parser;
    typedef toml::is_integer<toml::charactor> acceptor;
    {
        const std::string   source("42");
        const toml::Integer expected(42);
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string   source("+42");
        const toml::Integer expected(42);
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string   source("-42");
        const toml::Integer expected(-42);
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string   source("-4_2");
        const toml::Integer expected(-42);
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string source("dummy");
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(!result.first.ok());
        BOOST_CHECK(result.second == source.begin());
    }
}

BOOST_AUTO_TEST_CASE(test_float)
{
    typedef toml::parse_float parser;
    typedef toml::is_float<toml::charactor> acceptor;
    {
        const std::string source("42.0");
        const toml::Float expected(42.0);
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string source("+42.0");
        const toml::Float expected(42.0);
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string source("-42.0");
        const toml::Float expected(-42.0);
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string source("-4_2.0");
        const toml::Float expected(-42.0);
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string source("-42e0");
        const toml::Float expected(-42.0);
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string source("-42.0e0");
        const toml::Float expected(-42.0);
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string source("dummy");
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(!result.first.ok());
        BOOST_CHECK(result.second == source.begin());
    }
}

BOOST_AUTO_TEST_CASE(test_parse_boolean)
{
    typedef toml::parse_boolean parser;
    typedef toml::is_boolean<toml::charactor> acceptor;
    {
        const std::string   source("true");
        const toml::Boolean expected(true);
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string   source("false");
        const toml::Boolean expected(false);
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(result.first.ok());
        BOOST_CHECK_EQUAL(result.first.get(), expected);
        BOOST_CHECK(result.second == acceptor::invoke(source.begin()));
    }
    {
        const std::string   source("T");
        const auto result = parser::invoke(source.cbegin());
        BOOST_CHECK(!result.first.ok());
        BOOST_CHECK(result.second == source.begin());
    }
}



// BOOST_AUTO_TEST_CASE(test_parse_local_time)
// {
//     typedef toml::parse_local_time<char> parser;
//     typedef toml::is_local_time<char>  acceptor;
//     {
//         const std::string source("12:34:56");
//         const toml::Datetime expected(12, 34, 56, 0, 0);
//         const toml::Datetime result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         BOOST_CHECK_EQUAL(result, expected);
//     }
//     {
//         const std::string source("12:34:56.7");
//         const toml::Datetime expected(12, 34, 56, 700, 0);
//         const toml::Datetime result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         BOOST_CHECK_EQUAL(result, expected);
//     }
//     {
//         const std::string source("12:34:56.7891");
//         const toml::Datetime expected(12, 34, 56, 789, 100);
//         const toml::Datetime result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         BOOST_CHECK_EQUAL(result, expected);
//     }
// }
//
// BOOST_AUTO_TEST_CASE(test_parse_local_date)
// {
//     typedef toml::parse_local_date<char> parser;
//     typedef toml::is_local_date<char>  acceptor;
//     {
//         const std::string source("1979-09-27");
//         const toml::Datetime expected(1979, 9, 27);
//         const toml::Datetime result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         BOOST_CHECK_EQUAL(result, expected);
//     }
// }
//
// BOOST_AUTO_TEST_CASE(test_parse_local_date_time)
// {
//     typedef toml::parse_local_date_time<char> parser;
//     typedef toml::is_local_date_time<char>  acceptor;
//     {
//         const std::string source("1979-09-27T12:34:56");
//         const toml::Datetime expected(1979, 9, 27, 12, 34, 56, 0, 0);
//         const toml::Datetime result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         BOOST_CHECK_EQUAL(result, expected);
//     }
//     {
//         const std::string source("1979-09-27T12:34:56.789000");
//         const toml::Datetime expected(1979, 9, 27, 12, 34, 56, 789, 0);
//         const toml::Datetime result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         BOOST_CHECK_EQUAL(result, expected);
//     }
// }
//
// BOOST_AUTO_TEST_CASE(test_parse_offset_date_time)
// {
//     typedef toml::parse_offset_date_time<char> parser;
//     typedef toml::is_offset_date_time<char>  acceptor;
//     {
//         const std::string source("1979-09-27T12:34:56Z");
//         const toml::Datetime expected(1979, 9, 27, 12, 34, 56, 0, 0, 0, 0);
//         const toml::Datetime result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         BOOST_CHECK_EQUAL(result, expected);
//     }
//     {
//         const std::string source("1979-09-27T12:34:56.789000Z");
//         const toml::Datetime expected(1979, 9, 27, 12, 34, 56, 789, 0, 0, 0);
//         const toml::Datetime result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         BOOST_CHECK_EQUAL(result, expected);
//     }
//
//     {
//         const std::string source("1979-09-27T12:34:56+07:30");
//         const toml::Datetime expected(1979, 9, 27, 12, 34, 56, 0, 0, 7, 30);
//         const toml::Datetime result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         BOOST_CHECK_EQUAL(result, expected);
//     }
//     {
//         const std::string source("1979-09-27T12:34:56.789000+07:30");
//         const toml::Datetime expected(1979, 9, 27, 12, 34, 56, 789, 0, 7, 30);
//         const toml::Datetime result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         BOOST_CHECK_EQUAL(result, expected);
//     }
//
//     {
//         const std::string source("1979-09-27T12:34:56-07:30");
//         const toml::Datetime expected(1979, 9, 27, 12, 34, 56, 0, 0, -7, -30);
//         const toml::Datetime result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         BOOST_CHECK_EQUAL(result, expected);
//     }
//     {
//         const std::string source("1979-09-27T12:34:56.789000-07:30");
//         const toml::Datetime expected(1979, 9, 27, 12, 34, 56, 789, 0, -7, -30);
//         const toml::Datetime result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         BOOST_CHECK_EQUAL(result, expected);
//     }
// }
//
// BOOST_AUTO_TEST_CASE(test_parse_array)
// {
//     typedef toml::parse_array<char> parser;
//     typedef toml::is_array<char>  acceptor;
//     {
//         const std::string source("[1,2,3]");
//         const toml::Array expected{1, 2, 3};
//         const toml::Array result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//     {
//         const std::string source("[1, 2, 3]");
//         const toml::Array expected{1, 2, 3};
//         const toml::Array result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//     {
//         const std::string source("[ 1,2,3 ]");
//         const toml::Array expected{1, 2, 3};
//         const toml::Array result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//     {
//         const std::string source("[ 1 , 2 , 3 ]");
//         const toml::Array expected{1, 2, 3};
//         const toml::Array result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//     {
//         const std::string source("[ 1 \n,#comment\n 2 ,\n 3\n ]");
//         const toml::Array expected{1, 2, 3};
//         const toml::Array result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//     {
//         const std::string source("[ # empty array\n ]");
//         const toml::Array expected{};
//         const toml::Array result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//     {
//         const std::string source("[ \"] \", ' # ', \n']', # ] \n]");
//         const toml::Array expected{"] ", " # ", "]"};
//         const toml::Array result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//
//     {
//         const std::string source("[ \"Test #11 ]proved that\", 'Experiment #9 was a success' ]");
//         const toml::Array expected{"Test #11 ]proved that", "Experiment #9 was a success"};
//         const toml::Array result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//
//     {
//         const std::string source("[ \"Test #11 ]proved that\", 'Experiment #9 was a success' ]");
//         const toml::Array expected{"Test #11 ]proved that", "Experiment #9 was a success"};
//         const toml::Array result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//
//     {
//         const std::string source("[ [1,2,3] , ['a', 'b', 'c'] ]");
//         const toml::Array expected{{1,2,3}, {"a", "b", "c"}};
//         const toml::Array result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//
//     {
//         const std::string source("[ {foo=1}, {foo=1, bar=2.0}, {foo=1, bar=2.0, baz='str'} ]");
//         const toml::Array expected{{{"foo", 1}}, {{"foo", 1}, {"bar", 2.0}}, {{"foo", 1}, {"bar", 2.0}, {"baz", "str"}}};
//         const toml::Array result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
// }
//
//
// BOOST_AUTO_TEST_CASE(test_parse_inline_table)
// {
//     typedef toml::parse_inline_table<char> parser;
//     typedef toml::is_inline_table<char>  acceptor;
//     {
//         const std::string source("{foo=1,bar=2.0,baz='str'}");
//         const toml::Table expected{{"foo", 1}, {"bar", 2.0}, {"baz", "str"}};
//         const toml::Table result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//     {
//         const std::string source("{ foo=1, bar=2.0, baz='str' }");
//         const toml::Table expected{{"foo", 1}, {"bar", 2.0}, {"baz", "str"}};
//         const toml::Table result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//     {
//         const std::string source("{ foo = 1, bar = 2.0, baz = 'str' }");
//         const toml::Table expected{{"foo", 1}, {"bar", 2.0}, {"baz", "str"}};
//         const toml::Table result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//
//     {
//         const std::string source("{b=true, i=1, f=2.0, d=1907-03-02T07:32:00, s='str', a=[1,2,3], t={foo=1}}");
//         const toml::Table expected{{"b", true}, {"i", 1}, {"f", 2.0},
//                                    {"d", toml::Datetime(1907,3,2,7,32,0,0,0)},
//                                    {"s", "str"}, {"a", {1, 2, 3}},
//                                    {"t", {{"foo", 1}}}};
//         const toml::Table result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
// }
//
// // BOOST_AUTO_TEST_CASE(test_parse_barekey)
// // {
// //     {
// //         const std::string source("hoge");
// //         const std::string result = toml::parse_barekey<char>::invoke(
// //                 source.cbegin(), toml::is_barekey<char>::invoke(source.cbegin()));
// //         BOOST_CHECK_EQUAL(source, result);
// //     }
// //     {
// //         const std::string source("bare-key");
// //         const std::string result = toml::parse_barekey<char>::invoke(
// //                 source.cbegin(), toml::is_barekey<char>::invoke(source.cbegin()));
// //         BOOST_CHECK_EQUAL(source, result);
// //     }
// //     {
// //         const std::string source("bare_key");
// //         const std::string result = toml::parse_barekey<char>::invoke(
// //                 source.cbegin(), toml::is_barekey<char>::invoke(source.cbegin()));
// //         BOOST_CHECK_EQUAL(source, result);
// //     }
// //     {
// //         const std::string source("42");
// //         const std::string result = toml::parse_barekey<char>::invoke(
// //                 source.cbegin(), toml::is_barekey<char>::invoke(source.cbegin()));
// //         BOOST_CHECK_EQUAL(source, result);
// //     }
// // }
//
//
//
// BOOST_AUTO_TEST_CASE(test_key_value_pair)
// {
//     typedef toml::parse_key_value_pair<char> parser;
//     typedef toml::is_key_value_pair<char>  acceptor;
//     {
//         const std::string source("key=1");
//         const std::pair<toml::key, toml::value> expected{"key", 1};
//         const auto result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//     {
//         const std::string source("key =\t1");
//         const std::pair<toml::key, toml::value> expected{"key", 1};
//         const auto result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//     {
//         const std::string source("key = true");
//         const std::pair<toml::key, toml::value> expected{"key", true};
//         const auto result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//     {
//         const std::string source("key = -42");
//         const std::pair<toml::key, toml::value> expected{"key", -42};
//         const auto result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//     {
//         const std::string source("key = -42.0");
//         const std::pair<toml::key, toml::value> expected{"key", -42.};
//         const auto result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//     {
//         const std::string source("key = \"string\"");
//         const std::pair<toml::key, toml::value> expected{"key", "string"};
//         const auto result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//     {
//         const std::string source("key = 1901-01-01T00:00:00");
//         const std::pair<toml::key, toml::value> expected{"key", toml::Datetime(1901, 1,1,0,0,0,0,0)};
//         const auto result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//     {
//         const std::string source("key = [1,2,3]");
//         const std::pair<toml::key, toml::value> expected{"key", {1,2,3}};
//         const auto result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//     {
//         const std::string source("key = {foo=1,bar=2.0,baz='3'}");
//         const std::pair<toml::key, toml::value> expected{"key",
//             {{"foo", 1}, {"bar", 2.0}, {"baz", "3"}}};
//         const auto result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
// }
//
// BOOST_AUTO_TEST_CASE(test_table_definition)
// {
//     typedef toml::parse_standard_table_definition<char> parser;
//     typedef toml::is_table_definition<char>  acceptor;
//     {
//         const std::string source("[foo]");
//         const std::vector<toml::key> expected{"foo"};
//         const auto result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//     {
//         const std::string source("[foo.bar.baz]");
//         const std::vector<toml::key> expected{"foo", "bar", "baz"};
//         const auto result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//     {
//         const std::string source("[foo . bar. baz]");
//         const std::vector<toml::key> expected{"foo", "bar", "baz"};
//         const auto result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//     {
//         const std::string source("[foo . \"bar\" . baz]");
//         const std::vector<toml::key> expected{"foo", "bar", "baz"};
//         const auto result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//     {
//         const std::string source("[foo . \"b\\tar\" . baz]");
//         const std::vector<toml::key> expected{"foo", "b\tar", "baz"};
//         const auto result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
// }
//
// BOOST_AUTO_TEST_CASE(test_array_of_table_definition)
// {
//     typedef toml::parse_array_of_table_definition<char> parser;
//     typedef toml::is_array_of_table_definition<char>  acceptor;
//     {
//         const std::string source("[[foo]]");
//         const std::vector<toml::key> expected{"foo"};
//         const auto result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//     {
//         const std::string source("[[foo.bar.baz]]");
//         const std::vector<toml::key> expected{"foo", "bar", "baz"};
//         const auto result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//     {
//         const std::string source("[[foo . bar. baz]]");
//         const std::vector<toml::key> expected{"foo", "bar", "baz"};
//         const auto result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//     {
//         const std::string source("[[foo . \"bar\" . baz]]");
//         const std::vector<toml::key> expected{"foo", "bar", "baz"};
//         const auto result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
//     {
//         const std::string source("[[foo . \"b\\tar\" . baz]]");
//         const std::vector<toml::key> expected{"foo", "b\tar", "baz"};
//         const auto result = parser::invoke(
//                 source.cbegin(), acceptor::invoke(source.cbegin()));
//         const bool check = result == expected;
//         BOOST_CHECK(check);
//     }
// }
//

