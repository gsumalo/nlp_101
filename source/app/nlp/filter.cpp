#include "filter.hpp"
#include <cstdint>
#include <boost/lambda/lambda.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>

namespace nlp {

// Definition of tokens used by the grammar
namespace tokens {
    static const char * ampersand = "&";
    static const char * conjunction_and = "and";
    static const char * hyphen = "-";
    static const char * indefinite_one = "a";

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
    static const char * forty = "forty";
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


///
/// This class implements grammar able to filter numbers and transform them by means of semantic
//  actions.
template <typename IteratorIn>
class Grammar: public boost::spirit::qi::grammar<IteratorIn>
{
public:
    Grammar() = delete;

    ///
    /// Parameterized constructor. It configure the grammar and set the output for the semantic actions
    /// \param out Output stream used to write the filtered / unfiltered data.
    explicit Grammar(std::ostream & out)
        : Grammar::base_type(m_unstructured_text_), m_out_(out)
    {
        // Definition of the grammar

        m_zero_ = (boost::spirit::ascii::no_case[tokens::zero]       [boost::spirit::qi::_val = 0]);
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

        m_natural_units_ %= (m_one_unit_
                | m_other_units_
            );

        m_dozens_to_20_ %= (boost::spirit::ascii::no_case[tokens::ten] [boost::spirit::qi::_val = 10]
                | boost::spirit::ascii::no_case[tokens::eleven]        [boost::spirit::qi::_val = 11]
                | boost::spirit::ascii::no_case[tokens::twelve]        [boost::spirit::qi::_val = 12]
                | boost::spirit::ascii::no_case[tokens::thirteen]      [boost::spirit::qi::_val = 13]
                | boost::spirit::ascii::no_case[tokens::fourteen]      [boost::spirit::qi::_val = 14]
                | boost::spirit::ascii::no_case[tokens::fifteen]       [boost::spirit::qi::_val = 15]
                | boost::spirit::ascii::no_case[tokens::sixteen]       [boost::spirit::qi::_val = 16]
                | boost::spirit::ascii::no_case[tokens::seventeen]     [boost::spirit::qi::_val = 17]
                | boost::spirit::ascii::no_case[tokens::eighteen]      [boost::spirit::qi::_val = 18]
                | boost::spirit::ascii::no_case[tokens::nineteen]      [boost::spirit::qi::_val = 19]
            );

        m_dozens_from_20_simple_ %= (boost::spirit::ascii::no_case[tokens::twenty] [boost::spirit::qi::_val = 20]
                | boost::spirit::ascii::no_case[tokens::thirty]                    [boost::spirit::qi::_val = 30]
                | boost::spirit::ascii::no_case[tokens::forty]                     [boost::spirit::qi::_val = 40]
                | boost::spirit::ascii::no_case[tokens::fifty]                     [boost::spirit::qi::_val = 50]
                | boost::spirit::ascii::no_case[tokens::sixty]                     [boost::spirit::qi::_val = 60]
                | boost::spirit::ascii::no_case[tokens::seventy]                   [boost::spirit::qi::_val = 70]
                | boost::spirit::ascii::no_case[tokens::eighty]                    [boost::spirit::qi::_val = 80]
                | boost::spirit::ascii::no_case[tokens::ninety]                    [boost::spirit::qi::_val = 90]
            );

        m_dozens_from_20_ = (m_dozens_from_20_simple_ [boost::spirit::qi::_val = boost::spirit::qi::_1]
                >> -(boost::spirit::qi::lexeme[tokens::hyphen]
                        >> m_natural_units_ [boost::spirit::qi::_val += boost::spirit::qi::_1])
            );

        m_all_dozens_ %= (m_dozens_to_20_
                | m_dozens_from_20_
                | m_natural_units_
            );

        m_ambiguous_one_ %= (m_one_unit_
                | boost::spirit::ascii::no_case[tokens::indefinite_one] [boost::spirit::qi::_val = 1]
            );

        m_conjunction_ = (boost::spirit::ascii::no_case[tokens::conjunction_and]
                | boost::spirit::ascii::no_case[tokens::ampersand]
            );

        m_hundreds_suffix_ = (boost::spirit::ascii::no_case[tokens::hundred]
                        [boost::spirit::qi::_val = boost::spirit::qi::_r1 * 100]
                >> -(-(+(boost::spirit::ascii::blank) >> m_conjunction_)
                        >> +(boost::spirit::ascii::blank)
                        >> m_all_dozens_ [boost::spirit::qi::_val += boost::spirit::qi::_1])
            );

        m_trailing_hundreds_ = (m_natural_units_ [boost::spirit::qi::_a = boost::spirit::qi::_1]
                >> +(boost::spirit::ascii::blank)
                >> m_hundreds_suffix_(boost::spirit::qi::_a) [boost::spirit::qi::_val = boost::spirit::qi::_1]
            );

        m_leading_hundreds_ = ((m_ambiguous_one_ | m_other_units_) [boost::spirit::qi::_a = boost::spirit::qi::_1]
                >> +(boost::spirit::ascii::blank)
                >> m_hundreds_suffix_(boost::spirit::qi::_a) [boost::spirit::qi::_val = boost::spirit::qi::_1]
            );

        m_trailing_general_ %= (m_trailing_hundreds_
                | m_all_dozens_
            );

        m_leading_general_ %= (m_leading_hundreds_
                | m_all_dozens_
                | m_ambiguous_one_
            );

        m_thousands_suffix_ = (boost::spirit::ascii::no_case[tokens::thousand]
                        [boost::spirit::qi::_val = boost::spirit::qi::_r1 * 1000]
                >> -(+(boost::spirit::ascii::blank)
                        >> m_trailing_general_ [boost::spirit::qi::_val += boost::spirit::qi::_1])
            );

        m_trailing_thousands_ = ((m_trailing_general_ [boost::spirit::qi::_a = boost::spirit::qi::_1]
                >> -(+(boost::spirit::ascii::blank)
                        >> m_thousands_suffix_(boost::spirit::qi::_a) [boost::spirit::qi::_a = boost::spirit::qi::_1]))
                [boost::spirit::qi::_val = boost::spirit::qi::_a]
            );

        m_leading_thousands_ = (m_leading_general_ [boost::spirit::qi::_a = boost::spirit::qi::_1]
                >> +(boost::spirit::ascii::blank)
                >> m_thousands_suffix_(boost::spirit::qi::_a) [boost::spirit::qi::_val = boost::spirit::qi::_1]
            );

        m_millions_suffix_ = (boost::spirit::ascii::no_case[tokens::million]
                        [boost::spirit::qi::_val = boost::spirit::qi::_r1 * 1000000]
                >> -(+(boost::spirit::ascii::blank)
                        >> m_trailing_thousands_ [boost::spirit::qi::_val += boost::spirit::qi::_1])
            );

        m_leading_millions_ = (m_leading_general_ [boost::spirit::qi::_a = boost::spirit::qi::_1]
                >> +(boost::spirit::ascii::blank)
                >> m_millions_suffix_(boost::spirit::qi::_a) [boost::spirit::qi::_val = boost::spirit::qi::_1]
            );

        m_one_billion_ = (m_ambiguous_one_ [boost::spirit::qi::_val = boost::spirit::qi::_1]
                >> +(boost::spirit::ascii::blank)
                >> boost::spirit::ascii::no_case[tokens::billion] [boost::spirit::qi::_val *= 1000000000]
            );

        m_structured_number_ %= (m_one_billion_
                | m_leading_millions_
                | m_leading_thousands_
                | m_leading_hundreds_
                | m_all_dozens_
                | m_zero_
            );

        m_unstructured_text_ = *(m_structured_number_ [m_out_ << boost::spirit::qi::_1]
                | boost::spirit::ascii::char_ [m_out_ << boost::lambda::_1]
            );
    }

private:
    std::ostream & m_out_;
    boost::spirit::qi::rule<IteratorIn> m_unstructured_text_, m_conjunction_;
    boost::spirit::qi::rule<IteratorIn, uint64_t()> m_zero_, m_one_unit_, m_other_units_, m_natural_units_,
            m_all_units_, m_dozens_to_20_, m_dozens_from_20_simple_, m_dozens_from_20_, m_all_dozens_,
            m_ambiguous_one_, m_trailing_general_, m_leading_general_, m_one_billion_, m_structured_number_;
    boost::spirit::qi::rule<IteratorIn, uint64_t(),boost::spirit::locals<uint64_t>> m_trailing_hundreds_,
            m_leading_hundreds_, m_trailing_thousands_, m_leading_thousands_, m_leading_millions_;
    boost::spirit::qi::rule<IteratorIn, uint64_t(uint64_t)> m_hundreds_suffix_, m_thousands_suffix_,
            m_millions_suffix_;
};


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
