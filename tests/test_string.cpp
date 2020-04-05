#define BOOST_TEST_MODULE "test_string"
#include <boost/test/unit_test.hpp>
#include <toml.hpp>

BOOST_AUTO_TEST_CASE(test_basic_string)
{
    {
        const toml::string str("basic string");
        std::ostringstream oss;
        oss << str;
        BOOST_TEST(oss.str() == "\"basic string\"");
    }
    {
        const std::string  s1 ("basic string");
        const toml::string str(s1);
        std::ostringstream oss;
        oss << str;
        BOOST_TEST(oss.str() == "\"basic string\"");
    }
    {
        const toml::string str("basic string", toml::string_t::basic);
        std::ostringstream oss;
        oss << str;
        BOOST_TEST(oss.str() == "\"basic string\"");
    }
    {
        const std::string  s1 ("basic string");
        const toml::string str(s1, toml::string_t::basic);
        std::ostringstream oss;
        oss << str;
        BOOST_TEST(oss.str() == "\"basic string\"");
    }
}

BOOST_AUTO_TEST_CASE(test_basic_ml_string)
{
    {
        const toml::string str("basic\nstring");
        std::ostringstream oss1;
        oss1 << str;
        std::ostringstream oss2;
        oss2 << "\"\"\"\nbasic\nstring\\\n\"\"\"";
        BOOST_TEST(oss1.str() == oss2.str());
    }
    {
        const std::string  s1 ("basic\nstring");
        const toml::string str(s1);
        std::ostringstream oss1;
        oss1 << str;
        std::ostringstream oss2;
        oss2 << "\"\"\"\nbasic\nstring\\\n\"\"\"";
        BOOST_TEST(oss1.str() == oss2.str());
    }
    {
        const toml::string str("basic\nstring", toml::string_t::basic);
        std::ostringstream oss1;
        oss1 << str;
        std::ostringstream oss2;
        oss2 << "\"\"\"\nbasic\nstring\\\n\"\"\"";
        BOOST_TEST(oss1.str() == oss2.str());

    }
    {
        const std::string  s1 ("basic\nstring");
        const toml::string str(s1, toml::string_t::basic);
        std::ostringstream oss1;
        oss1 << str;
        std::ostringstream oss2;
        oss2 << "\"\"\"\nbasic\nstring\\\n\"\"\"";
        BOOST_TEST(oss1.str() == oss2.str());
    }
}


BOOST_AUTO_TEST_CASE(test_literal_string)
{
    {
        const toml::string str("literal string", toml::string_t::literal);
        std::ostringstream oss;
        oss << str;
        BOOST_TEST(oss.str() == "'literal string'");
    }
    {
        const std::string  s1 ("literal string");
        const toml::string str(s1, toml::string_t::literal);
        std::ostringstream oss;
        oss << str;
        BOOST_TEST(oss.str() == "'literal string'");
    }
}

BOOST_AUTO_TEST_CASE(test_literal_ml_string)
{
    {
        const toml::string str("literal\nstring", toml::string_t::literal);
        std::ostringstream oss1;
        oss1 << str;
        std::ostringstream oss2;
        oss2 << "'''\nliteral\nstring'''";
        BOOST_TEST(oss1.str() == oss2.str());

    }
    {
        const std::string  s1 ("literal\nstring");
        const toml::string str(s1, toml::string_t::literal);
        std::ostringstream oss1;
        oss1 << str;
        std::ostringstream oss2;
        oss2 << "'''\nliteral\nstring'''";
        BOOST_TEST(oss1.str() == oss2.str());
    }
}

BOOST_AUTO_TEST_CASE(test_string_add_assign)
{
    // string literal
    {
        toml::string str("foo");
        str += "bar";
        BOOST_TEST(str.str == "foobar");
    }
    // std::string
    {
        toml::string str("foo");
        std::string str2("bar");
        str += str2;
        BOOST_TEST(str.str == "foobar");
    }
    // toml::string
    {
        toml::string str("foo");
        toml::string str2("bar");
        str += str2;
        BOOST_TEST(str.str == "foobar");
    }
#if __cplusplus >= 201703L
    // std::string_view
    {
        toml::string str("foo");
        str += std::string_view("bar");
        BOOST_TEST(str == "foobar");
    }
#endif
    // std::string += toml::string
    {
        std::string  str("foo");
        toml::string str2("bar");
        str += str2;
        BOOST_TEST(str == "foobar");
    }
}

// check commonly-used member methods

BOOST_AUTO_TEST_CASE(test_string_size_related_methods)
{
    {
        toml::string str(std::string("foobar"));

        BOOST_TEST(str.size()   == 6u);
        BOOST_TEST(str.length() == 6u);
        BOOST_TEST(str.empty()  == false);

        BOOST_TEST(str.max_size() == str.str.max_size());
        BOOST_TEST(str.capacity() == str.str.capacity());

        str.clear();

        BOOST_TEST(str.size()   == 0u);
        BOOST_TEST(str.length() == 0u);
        BOOST_TEST(str.empty()  == true);

        str.shrink_to_fit(); // check it compiles

        // after shrnik_to_fit, still capacity is not zero. It is because of
        // short string optimization (SSO). Short string can be statically
        // stored in the std::string class without any dynamic allocation.
    }
}

BOOST_AUTO_TEST_CASE(test_string_iterator_related_methods)
{
    {
        toml::string str(std::string("foobar"));

        std::string copied(str.size(), ' ');
        std::copy(str.begin(), str.end(), copied.begin());
        BOOST_TEST(copied == str.str);
    }
    {
        const toml::string str(std::string("foobar"));

        std::string copied(str.size(), ' ');
        std::copy(str.begin(), str.end(), copied.begin());
        BOOST_TEST(copied == str.str);
    }

    {
        toml::string str(std::string("foobar"));

        std::string copied(str.size(), ' ');
        std::copy(str.rbegin(), str.rend(), copied.rbegin());
        BOOST_TEST(copied == str.str);
    }
    {
        const toml::string str(std::string("foobar"));

        std::string copied(str.size(), ' ');
        std::copy(str.rbegin(), str.rend(), copied.rbegin());
        BOOST_TEST(copied == str.str);
    }
}

BOOST_AUTO_TEST_CASE(test_string_element_access)
{
    {
        toml::string str(std::string("foobar"));

        BOOST_TEST(str.front() == 'f');
        BOOST_TEST(str.at(1)   == 'o');
        BOOST_TEST(str[2]      == 'o');
        BOOST_TEST(str.at(3)   == 'b');
        BOOST_TEST(str[4]      == 'a');
        BOOST_TEST(str.back()  == 'r');
    }
    {
        const toml::string str(std::string("foobar"));

        BOOST_TEST(str.front() == 'f');
        BOOST_TEST(str.at(1)   == 'o');
        BOOST_TEST(str[2]      == 'o');
        BOOST_TEST(str.at(3)   == 'b');
        BOOST_TEST(str[4]      == 'a');
        BOOST_TEST(str.back()  == 'r');
    }
}

BOOST_AUTO_TEST_CASE(test_string_substr)
{
    {
        const toml::string str(std::string("foobar"));

        BOOST_TEST(str.substr(0, 3) == "foo");
        BOOST_TEST(str.substr(3, 3) == "bar");
    }
}

