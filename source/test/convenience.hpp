#ifndef CONVENIENCE_HPP_
#define CONVENIENCE_HPP_

#include <sstream>

namespace convenience {

template <typename T>
std::string to_string(const T & value)
{
    std::ostringstream aux;
    aux.exceptions(std::ios::badbit | std::ios::failbit);

    aux << value;

    auto rv(aux.str());
    return rv;
}


}   // namespace convenience

#endif // CONVENIENCE_HPP_