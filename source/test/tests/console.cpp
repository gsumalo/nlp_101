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
    // Test case: No filtering case
    {"Hello World!!", "Hello World!!"},

    // Test cases: Example provided in specification (case-insensitive)
    {"one hundred and one", "101"},
    {"One Hundred And One", "101"},

    // Test case: Lowest accepted value
    {"zero",  "0"},

    // Test cases: units
    {"one",   "1"},
    {"two",   "2"},
    {"three", "3"},
    {"four",  "4"},
    {"five",  "5"},
    {"six",   "6"},
    {"seven", "7"},
    {"eight", "8"},
    {"nine",  "9"},

    // Test cases: dozens
    {"ten",          "10"},
    {"eleven",       "11"},
    {"twelve",       "12"},
    {"thirteen",     "13"},
    {"fourteen",     "14"},
    {"fifteen",      "15"},
    {"sixteen",      "16"},
    {"seventeen",    "17"},
    {"eighteen",     "18"},
    {"nineteen",     "19"},
    {"twenty",       "20"},
    {"twenty-one",   "21"},
    {"twenty-two",   "22"},
    {"twenty-three", "23"},
    {"twenty-four",  "24"},
    {"twenty-five",  "25"},
    {"twenty-six",   "26"},
    {"twenty-seven", "27"},
    {"twenty-eight", "28"},
    {"twenty-nine",  "29"},
    {"thirty",       "30"},
    {"thirty-one",   "31"},
    {"forty",        "40"},
    {"fifty",        "50"},
    {"sixty",        "60"},
    {"seventy",      "70"},
    {"eighty",       "80"},
    {"ninety",       "90"},

    // Test cases: hundreds
    {"one hundred",                 "100"},
    {"a hundred",                   "100"},
    {"one hundred one",             "101"},
    {"one hundred & one",           "101"},
    {"a hundred one",               "101"},
    {"two hundred",                 "200"},
    {"two hundred and eleven",      "211"},
    {"two hundred thirty-five",     "235"},
    {"two hundred & thirty-five",   "235"},
    {"two hundred and thirty-five", "235"},

    // Test cases: thousands
    {"one thousand",                                                    "1000"},
    {"a thousand",                                                      "1000"},
    {"one thousand one",                                                "1001"},
    {"one thousand one hundred",                                        "1100"},
    {"ten thousand one hundred",                                        "10100"},
    {"one hundred thousand one hundred",                                "100100"},
    {"one thousand two hundred thirty-four",                            "1234"},
    {"one thousand two hundred and thirty-four",                        "1234"},
    {"twelve thousand",                                                 "12000"},
    {"forty-two thousand three hundred",                                "42300"},
    {"twelve thousand three hundred and forty-five",                    "12345"},
    {"six hundred fifty-four thousand three hundred twenty-one",        "654321"},
    {"six hundred fifty-four thousand three hundred and twenty-one",    "654321"},
    {"six hundred and fifty-four thousand three hundred and twenty-one","654321"},

    // Test cases: millions
    {"one million",                                                                                "1000000"},
    {"a million",                                                                                  "1000000"},
    {"one million one",                                                                            "1000001"},
    {"one million one hundred",                                                                    "1000100"},
    {"one million one hundred and one",                                                            "1000101"},
    {"one million one thousand",                                                                   "1001000"},
    {"one million ten thousand",                                                                   "1010000"},
    {"one million ten thousand one hundred",                                                       "1010100"},
    {"one million one hundred thousand one hundred",                                               "1100100"},
    {"one million one hundred thousand one hundred one",                                           "1100101"},
    {"ten million one hundred thousand one hundred",                                               "10100100"},
    {"one hundred million one hundred thousand one hundred",                                       "100100100"},
    {"nine hundred eighty-seven million six hundred fifty-four thousand three hundred twenty-one", "987654321"},

    // Test case: Highest accepted value
    {"one billion",                 "1000000000"},
    {"a billion",                   "1000000000"},

    // Test case: Next to highest accepted value
    {"two billion",                 "2 billion"},
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
