#ifndef ENVIRONMENT_HPP_
#define ENVIRONMENT_HPP_

#include <boost/filesystem/path.hpp>
#include <boost/program_options.hpp>

namespace nlp_test {

class Environment
{
public:
    Environment() = default;
    explicit Environment(const boost::program_options::variables_map & options);
    Environment(const Environment &) = default;
    Environment(Environment &&) = default;

    Environment & operator=(const Environment &) = default;
    Environment & operator=(Environment &&) = default;

    const auto & application() const
    {
        return m_application_;
    }

    static const std::string APP_OPTION;
    static const std::string HELP_OPTION;

private:
    boost::filesystem::path m_application_;
};

}   // namespace nlp_test

#endif // ENVIRONMENT_HPP_
