#include <iostream>
#include <boost/program_options.hpp>
#include <gtest/gtest.h>
#include "convenience.hpp"
#include "environment.hpp"

nlp_test::Environment env;

static void parse_params(int argc, char *argv[], boost::program_options::variables_map & vm)
{
    boost::program_options::options_description desc("Allowed options");

    desc.add_options()
        (nlp_test::Environment::HELP_OPTION.c_str(), "Show Google Test help")
        (nlp_test::Environment::APP_OPTION.c_str(), boost::program_options::value<std::string>(), 
                "Path to application binary (mandatory)")
    ;

    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).run(), vm);
    boost::program_options::notify(vm);

    if (!vm.count("app")) {
        throw std::runtime_error("Wrong syntax\n" + convenience::to_string(desc));
    }
}


int main(int argc, char *argv[])
{
    int rv(EXIT_FAILURE);

    try {
        ::testing::InitGoogleTest(&argc, argv);

        boost::program_options::variables_map vm;
        parse_params(argc, argv, vm);
        env = std::move(nlp_test::Environment(vm));

        rv = RUN_ALL_TESTS();
    } catch (const std::exception & e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "ERROR: Unexpected exception found" << std::endl;
    }

    return rv;
}
