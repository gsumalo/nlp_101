#ifndef NLP_GRAMMAR_HPP_
#define NLP_GRAMMAR_HPP_

#include <boost/lambda/lambda.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>

namespace nlp {

template <typename IteratorIn, typename IteratorOut>
class Grammar: public boost::spirit::qi::grammar<IteratorIn>
{
public:
    explicit Grammar(IteratorOut & out)
        : Grammar::base_type(m_unstructured_text_), m_out_(out)
    {
        m_unstructured_text_ = *boost::spirit::ascii::char_[std::cout << boost::lambda::_1];
    }

private:
    IteratorOut & m_out_;
    boost::spirit::qi::rule<IteratorIn> m_unstructured_text_;

};

}   // namespace nlp

#endif // NLP_GRAMMAR_HPP_
