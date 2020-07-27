#include <gtest/gtest.h>

struct ConsoleIO
{
    std::string m_provided;
    std::string m_expected;
};

static const ConsoleIO console_IO_cases[] = {
    {"Hello World!!", "Hello World!!"},
};

class ConsoleIOTest: public ::testing::TestWithParam<ConsoleIO>
{
};

TEST_P(ConsoleIOTest, Basic)
{
    try {
//        const auto & param(GetParam());



    } catch(...) {
        FAIL();
    }
}

INSTANTIATE_TEST_CASE_P(, ConsoleIOTest, ::testing::ValuesIn(console_IO_cases));
