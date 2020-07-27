#include <iostream>
#include <boost/program_options.hpp>
#include <gtest/gtest.h>

static bool parse_params(int argc, char *argv[], boost::program_options::variables_map & vm)
{
    bool rv(true);

    boost::program_options::options_description desc("Allowed options");
    try {
        desc.add_options()
            ("help", "Show Google Test help")
            ("app", boost::program_options::value<std::string>(), "Path to application binary (mandatory)")
        ;

        boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).run(), vm);
        boost::program_options::notify(vm);

        if (vm.count("help") || !vm.count("app")) {
            rv = false;
        }
    } catch(...) {
        rv = false;
    }

    if (!rv) {
        std::cerr << "Wrong syntax\n\nSpecify all the options: " << desc << std::endl;
    }

    return rv;
}


int main(int argc, char *argv[])
{
    int rv(EXIT_FAILURE);

    ::testing::InitGoogleTest(&argc, argv);

    boost::program_options::variables_map vm;
    if (parse_params(argc, argv, vm)
            // && env.init(vm)
            ) {
        try {
            rv = RUN_ALL_TESTS();
        } catch (const std::exception & e) {
            std::cerr << e.what() << std::endl;
        }
    }

    return rv;
}
