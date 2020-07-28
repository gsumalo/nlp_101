#ifndef NLP_GRAMMAR_HPP_
#define NLP_GRAMMAR_HPP_

#include <cstdint>
#include <boost/lambda/lambda.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>

namespace nlp {

template <typename IteratorIn>
class Grammar: public boost::spirit::qi::grammar<IteratorIn>
{
public:
    explicit Grammar(std::ostream & out)
        : Grammar::base_type(m_unstructured_text_), m_out_(out)
    {
        m_structured_number_ = boost::spirit::ascii::no_case["one"] [boost::spirit::qi::_val = 1];

        m_unstructured_text_ = *(m_structured_number_ [m_out_ << boost::spirit::qi::_1]
                | boost::spirit::ascii::char_ [m_out_ << boost::lambda::_1]
            );
    }

private:
    std::ostream & m_out_;
    boost::spirit::qi::rule<IteratorIn> m_unstructured_text_;
    boost::spirit::qi::rule<IteratorIn, uint64_t()> m_structured_number_;

};

}   // namespace nlp

#endif // NLP_GRAMMAR_HPP_
