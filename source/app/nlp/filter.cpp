#include "filter.hpp"
#include <cctype>
#include <map>
#include "grammar.hpp"

namespace nlp {

void filter(std::istream & input, std::ostream & output)
{
    // Definition of multi_pass iterators
    std::istreambuf_iterator<char> input_it(input);
    auto in_begin(boost::spirit::make_default_multi_pass(input_it));
    auto in_end(boost::spirit::make_default_multi_pass(decltype(input_it)()));

    Grammar<decltype(in_begin)> filter(output);

    // Performing filtering / transformation.
    if (!boost::spirit::qi::parse(in_begin, in_end, filter)) {
        // NOTE: This should never happen because the grammar is expected to consume any data.
        throw std::runtime_error("Unexpected error found - Please, contact the developer and report this issue");
    }
}

}   // namespace nlp
