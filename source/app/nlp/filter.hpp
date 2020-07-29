#ifndef NLP_FILTER_HPP_
#define NLP_FILTER_HPP_

#include <iostream>

namespace nlp {

///
/// Façade for the filtering grammar. It abstracts the details to parse and apply the grammar
/// \param input Input stream with the data to be filtered
/// \param output Output stream where the filtered / transformed data will be written to
///
void filter(std::istream & input, std::ostream & output);

}   // namespace nlp

#endif // NLP_FILTER_HPP_
