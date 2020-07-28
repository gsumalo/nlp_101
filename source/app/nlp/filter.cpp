#include "filter.hpp"
#include <cctype>
#include <map>
#include "grammar.hpp"

namespace nlp {
/*
static const std::map<std::string, std::string> tokens = {
    {"zero",               "0"},
    {"one",                "1"},
    {"two",                "2"},
    {"three",              "3"},
    {"four",               "4"},
    {"five",               "5"},
    {"six",                "6"},
    {"seven",              "7"},
    {"eight",              "8"},
    {"nine",               "9"},
    {"ten",               "10"},
    {"eleven",            "11"},
    {"twelve",            "12"},
    {"thirteen",          "13"},
    {"fourteen",          "14"},
    {"fifteen",           "15"},
    {"sixteen",           "16"},
    {"seventeen",         "17"},
    {"eighteen",          "18"},
    {"nineteen",          "19"},
    {"twenty",            "20"},
    {"thirty",            "30"},
    {"fourty",            "40"},
    {"fifty",             "50"},
    {"sixty",             "60"},
    {"seventy",           "70"},
    {"eighty",            "80"},
    {"ninety",            "90"},
    {"hundred",          "100"},
    {"thousand",        "1000"},
    {"million",      "1000000"},
    {"billion",   "1000000000"},
};
*/
//void filter_1(std::istream & input, std::ostream & output)
//{
//    std::string word;
//    auto character(input.get());
//
//    while (!input.eof()) {
//        if (std::isalpha(character)) {
//            word = character;
//
//            while (std::isalpha(input.peek()) && !input.eof()) {
//                word += input.get();
//            }
//
//            output << word;
//        } else {
//            output.put(character);
//        }
//
//        character = input.get();
//    }
//}

void filter_2(std::istream & input, std::ostream & output)
{
    std::istreambuf_iterator<char> input_it(input);
    auto in_begin(boost::spirit::make_default_multi_pass(input_it));
    auto in_end(boost::spirit::make_default_multi_pass(decltype(input_it)()));

    Grammar<decltype(in_begin)> filter(output);

    if (!boost::spirit::qi::parse(in_begin, in_end, filter)) {
        throw std::runtime_error("Unexpected error found");
    }
}

}   // namespace nlp
