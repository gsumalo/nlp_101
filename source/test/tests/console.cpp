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

static const ConsoleIO console_IO_cases[] = {
    {"Hello World!!", "Hello World!!"},
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
