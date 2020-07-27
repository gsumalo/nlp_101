#include <iostream>
#include <string_view>
#include <vector>
#include <boost/regex/pending/unicode_iterator.hpp>
#include "nlp/filter.hpp"

namespace convenience {

std::string convert_to_UTF8(std::wstring_view str)
{
#if defined (_MSC_VER)
    static_assert(sizeof(wchar_t) == 2, "Wrong sizeof");
    boost::u32_to_u8_iterator<boost::u16_to_u32_iterator<decltype(str)::const_iterator>> begin(str.begin()), 
            end(str.end());
#elif defined (__linux__)
    static_assert(sizeof(wchar_t) == 4, "Wrong sizeof");
    boost::u32_to_u8_iterator<decltype(str)::const_iterator> begin(str.begin()), end(str.end());
#else
#error Unsupported!!
#endif

    std::string rv(begin, end);

    return rv;
}

}   // namespace convenience

#if defined (_MSC_VER)
int wmain(int argc, wchar_t *argv[])
{
    std::vector<std::string> argv_vector;
    for (int i(1); i < argc; ++i) {
        argv_vector.push_back(convenience::convert_to_UTF8(argv[i]));
    }
#elif defined (__linux__)
int main(int argc, char *argv[])
{
    std::vector<std::string> argv_vector;
    for (int i(1); i < argc; ++i) {
        argv_vector.push_back(std::string(argv[i]));
    }
#else
#error Unsupported!!
#endif

    int rv = EXIT_SUCCESS;

    try {
        nlp::filter(std::cin, std::cout);
    } catch (std::exception & e) {
        std::cerr << e.what() << std::endl;
        rv = EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Unknown exception" << std::endl;
        rv = EXIT_FAILURE;
    }

    return rv;
}
