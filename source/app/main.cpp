#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#if defined (_MSC_VER)
#include <Windows.h>
#include <openssl/applink.c>
#endif
#include <tbb/task_scheduler_init.h>
#include <boost/filesystem/operations.hpp>
#include <OSless/curl_config.hpp>
#include <OSless/crypto.hpp>
#include <OSless/platform.hpp>
#include <OSless/qthread.hpp>
#include <OSless/scoped_mt_safe_ssl.hpp>
#include <qengine/environment.hpp>
#include <qengine/features.hpp>
#include <qengine/file_system.hpp>
#include <qengine/settings_allowed.hpp>
#include <qengine/settings_manager.hpp>
#include "server/batch_app.hpp"
#include "server/service_db.hpp"
#include "server/service_dbfibrillator.hpp"
#include "server/service_multitenant.hpp"
#include "server/ssl_environment.hpp"


std::string convert_to_UTF8(const wchar_t * str)
{
    std::wstring aux(str);

    return convert_to_UTF8(aux);
}

std::string convert_to_UTF8(const std::wstring & str)
{
#if defined (_MSC_VER)
    static_assert(sizeof(wchar_t) == 2, "Wrong sizeof");
    boost::u32_to_u8_iterator<boost::u16_to_u32_iterator<std::wstring::const_iterator>>
            begin(str.begin()), end(str.end());
#elif defined (__linux__)
    static_assert(sizeof(wchar_t) == 4, "Wrong sizeof");
    boost::u32_to_u8_iterator<std::wstring::const_iterator> begin(str.begin()), end(str.end());
#else
#error Unsupported compiler!!
#endif

    std::string rv(begin, end);

    return rv;
}


#if defined (_MSC_VER)
int wmain(int argc, wchar_t *argv[])
{
    std::vector<std::string> argv_vector;
    for (int i(1); i < argc; ++i)
    {
        argv_vector.push_back(OSless::platform::convert_to_UTF8(argv[i]));
    }
#elif defined (__linux__)
int main(int argc, char *argv[])
{
    // This avoids problems in systems with wrong locale
    OSless::platform::qsetenv("LC_ALL", "C");

    std::vector<std::string> argv_vector;
    for (int i(1); i < argc; ++i)
    {
        argv_vector.push_back(std::string(argv[i]));
    }
#else
#error Unsupported compiler!!
#endif

    int rv = EXIT_SUCCESS;

    try {

    }
    } catch (std::exception & e) {
        std::cerr << e.what() << std::endl;
        rv = EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Unknown exception" << std::endl;
        rv = EXIT_FAILURE;
    }

    return rv;
}
