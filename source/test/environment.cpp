#include "environment.hpp"

namespace nlp_test {

const std::string Environment::APP_OPTION("app");
const std::string Environment::HELP_OPTION("help");

Environment::Environment(const boost::program_options::variables_map & options)
{
    m_application_ = options[APP_OPTION].as<std::string>();

    if (!std::filesystem::exists(m_application_)) {
        throw std::runtime_error(m_application_.string() + " does not exist");
    }
}

}   // namespace nlp_test
