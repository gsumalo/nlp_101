#ifndef NLP_GRAMMAR_HPP_
#define NLP_GRAMMAR_HPP_

#include <cstdint>
#include <boost/lambda/lambda.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>

namespace nlp {

namespace tokens {
    static const char * zero = "zero";
    static const char * one = "one";
    static const char * two = "two";
    static const char * three = "three";
    static const char * four = "four";
    static const char * five = "five";
    static const char * six = "six";
    static const char * seven = "seven";
    static const char * eight = "eight";
    static const char * nine = "nine";
    static const char * ten = "ten";
    static const char * eleven = "eleven";
    static const char * twelve = "twelve";
    static const char * thirteen = "thirteen";
    static const char * fourteen = "fourteen";
    static const char * fifteen = "fifteen";
    static const char * sixteen = "sixteen";
    static const char * seventeen = "seventeen";
    static const char * eighteen = "eighteen";
    static const char * nineteen = "nineteen";
    static const char * twenty = "twenty";
    static const char * thirty = "thirty";
    static const char * fourty = "fourty";
    static const char * fifty = "fifty";
    static const char * sixty = "sixty";
    static const char * seventy = "seventy";
    static const char * eighty = "eighty";
    static const char * ninety = "ninety";
    static const char * hundred = "hundred";
    static const char * thousand = "thousand";
    static const char * million = "million";
    static const char * billion = "billion";
}   // namespace tokens


template <typename IteratorIn>
class Grammar: public boost::spirit::qi::grammar<IteratorIn>
{
public:
    explicit Grammar(std::ostream & out)
        : Grammar::base_type(m_unstructured_text_), m_out_(out)
    {
        m_zero_unit_ = (boost::spirit::ascii::no_case[tokens::zero]  [boost::spirit::qi::_val = 0]);
        m_one_unit_ = (boost::spirit::ascii::no_case[tokens::one]    [boost::spirit::qi::_val = 1]);
        m_other_units_ = (boost::spirit::ascii::no_case[tokens::two] [boost::spirit::qi::_val = 2]
                | boost::spirit::ascii::no_case[tokens::three]       [boost::spirit::qi::_val = 3]
                | boost::spirit::ascii::no_case[tokens::four]        [boost::spirit::qi::_val = 4]
                | boost::spirit::ascii::no_case[tokens::five]        [boost::spirit::qi::_val = 5]
                | boost::spirit::ascii::no_case[tokens::six]         [boost::spirit::qi::_val = 6]
                | boost::spirit::ascii::no_case[tokens::seven]       [boost::spirit::qi::_val = 7]
                | boost::spirit::ascii::no_case[tokens::eight]       [boost::spirit::qi::_val = 8]
                | boost::spirit::ascii::no_case[tokens::nine]        [boost::spirit::qi::_val = 9]
            );

        m_all_units_ %= (m_zero_unit_
                | m_one_unit_
                | m_other_units_
            );

        m_one_billion_ = (m_one_unit_ [boost::spirit::qi::_val = boost::spirit::qi::_1]
                >> +(boost::spirit::ascii::blank)
                >> boost::spirit::ascii::no_case[tokens::billion] [boost::spirit::qi::_val *= 1000000000]
            );

        m_structured_number_ %= (m_one_billion_
                | m_all_units_
            );

        m_unstructured_text_ = *(m_structured_number_ [m_out_ << boost::spirit::qi::_1]
                | boost::spirit::ascii::char_ [m_out_ << boost::lambda::_1]
            );
    }

private:
    std::ostream & m_out_;
    boost::spirit::qi::rule<IteratorIn> m_unstructured_text_;
    boost::spirit::qi::rule<IteratorIn, uint64_t()> m_zero_unit_, m_one_unit_, m_other_units_, m_all_units_,
            m_one_billion_, m_structured_number_;

};

}   // namespace nlp

#endif // NLP_GRAMMAR_HPP_
