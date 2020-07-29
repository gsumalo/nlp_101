#ifndef ENVIRONMENT_HPP_
#define ENVIRONMENT_HPP_

#include <boost/filesystem/path.hpp>
#include <boost/program_options.hpp>

namespace nlp_test {

///
/// It encapsulates the parameters provided to the custom test runner
///
class Environment
{
public:
    Environment() = default;
    explicit Environment(const boost::program_options::variables_map & options);
    Environment(const Environment &) = default;
    Environment(Environment &&) = default;

    Environment & operator=(const Environment &) = default;
    Environment & operator=(Environment &&) = default;

    ///
    /// It provides the path to the application binary
    /// \return The path to the application binary
    ///
    const auto & application() const
    {
        return m_application_;
    }

    ///
    /// Labels of the accepted flags (DRY rule)
    ///
    static const std::string APP_OPTION;
    static const std::string HELP_OPTION;

private:
    boost::filesystem::path m_application_;     // The path to the application binary
};

}   // namespace nlp_test

#endif // ENVIRONMENT_HPP_
