#include <boost/process.hpp>
#include <gtest/gtest.h>
#include "test/environment.hpp"

namespace bp = boost::process;

extern nlp_test::Environment env;

struct ConsoleIO
{
    std::string m_provided;
    std::string m_expected;
};

std::ostream & operator<<(std::ostream & out, const ConsoleIO & value)
{
    return out << "{" << value.m_provided << ", " << value.m_expected << "}";
}

static const ConsoleIO console_IO_cases[] = {
    {"Hello World!!",               "Hello World!!"},   // Test case: No filtering case
    {"one hundred and one",         "101"},             // Test case: Example provided in specification
    {"One Hundred And One",         "101"},             // Test case: case-insensitive
    {"zero",                        "0"},               // Test case: Lowest accepted value
    {"one",                         "1"},
    {"two",                         "2"},
    {"three",                       "3"},
    {"four",                        "4"},
    {"five",                        "5"},
    {"six",                         "6"},
    {"seven",                       "7"},
    {"eight",                       "8"},
    {"nine",                        "9"},
    {"ten",                         "10"},              // Test cases: dozens
    {"eleven",                      "11"},
    {"twelve",                      "12"},
    {"thirteen",                    "13"},
    {"fourteen",                    "14"},
    {"fifteen",                     "15"},
    {"sixteen",                     "16"},
    {"seventeen",                   "17"},
    {"eighteen",                    "18"},
    {"nineteen",                    "19"},
    {"twenty",                      "20"},
    {"twenty-one",                  "21"},
    {"twenty-two",                  "22"},
    {"twenty-three",                "23"},
    {"twenty-four",                 "24"},
    {"twenty-five",                 "25"},
    {"twenty-six",                  "26"},
    {"twenty-seven",                "27"},
    {"twenty-eight",                "28"},
    {"twenty-nine",                 "29"},
    {"thirty",                      "30"},
    {"thirty-one",                  "31"},
    {"fourty",                      "40"},
    {"fifty",                       "50"},
    {"sixty",                       "60"},
    {"seventy",                     "70"},
    {"eighty",                      "80"},
    {"ninety",                      "90"},
    {"one hundred",                 "100"},             // Test cases: hundreds
    {"a hundred",                   "100"},
    {"one hundred one",             "101"},
    {"one hundred & one",           "101"},
    {"a hundred one",               "101"},
    {"two hundred",                 "200"},
    {"two hundred and eleven",      "211"},
    {"two hundred thirty-five",     "235"},
    {"two hundred & thirty-five",   "235"},
    {"two hundred and thirty-five", "235"},
    {"one thousand",                "1000"},            // Test cases: thousands
    {"a thousand",                  "1000"},
    {"one million",                 "1000000"},         // Test cases: millions
    {"a million",                   "1000000"},
    {"one billion",                 "1000000000"},      // Test case: Highest accepted value
    {"a billion",                   "1000000000"},
    {"two billion",                 "2 billion"},       // Test case: Next to highest accepted value
};

class ConsoleIOTest: public ::testing::TestWithParam<ConsoleIO>
{
};

TEST_P(ConsoleIOTest, Basic)
{
    try {
        const auto & param(GetParam());

        bp::opstream input;
        bp::ipstream output;
        auto process(bp::child(env.application(), bp::std_out > output, bp::std_in < input));
        
        input << param.m_provided;
        input.flush();
        input.pipe().close();

        std::string result;
        for (auto character(output.get()); !output.eof(); character = output.get()) {
            result += character;
        }

        process.wait();

        ASSERT_EQ(EXIT_SUCCESS, process.exit_code());
        ASSERT_STREQ(param.m_expected.c_str(), result.c_str());
    } catch(...) {
        FAIL();
    }
}

INSTANTIATE_TEST_CASE_P(, ConsoleIOTest, ::testing::ValuesIn(console_IO_cases));
