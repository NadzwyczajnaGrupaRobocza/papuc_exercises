#include "InstructionLexer.hpp"

#include <functional>
#include <iostream>
#include <regex>
#include <utility>
#include <vector>

#include "boost/algorithm/string/trim.hpp"

#include "boost/range/algorithm.hpp"
#include "boost/tokenizer.hpp"

Tokens InstructionLexer::parseInstructions(const std::string& input)
{
    boost::tokenizer<boost::char_separator<char>> lineTokenizer{
        input, boost::char_separator<char>{"\n"}};
    Tokens tokens;
    for (const auto& line : lineTokenizer)
    {
        if (line.at(0) != ' ')
        {
            boost::copy(parseLabel(line), std::back_inserter(tokens));
        }
        else
        {
            boost::copy(parseLine(line), std::back_inserter(tokens));
        }
    }
    return tokens;
}

Tokens InstructionLexer::parseLabel(const std::string& label)
{
    const auto labelRegEx = std::regex{R"!([a-zA-Z_]+:)!"};
    if (regexMatcher(label, labelRegEx))
    {
        return {{TokenType::Label,
                 getLabelValue(label.substr(0, label.size() - 1))}};
    }
    else
    {
        throw UnknownInstruction{"Invalid label: " + label};
    }
}

bool InstructionLexer::regexMatcher(const std::string& text,
                                    const std::regex& pattern)
{
    return std::regex_match(text, pattern);
}

Tokens InstructionLexer::parseLine(const std::string& line)
{
    boost::tokenizer<boost::char_separator<char>> instructionTokenizer{
        line, boost::char_separator<char>{" "}};
    Tokens tokens;
    for (const auto& token : instructionTokenizer)
    {
        boost::copy(parseInstruction(token), std::back_inserter(tokens));
    }
    return tokens;
}

const auto alwaysZeroValue = [](const std::string&) -> Token::ValueType {
    return 0;
};

Token::ValueType InstructionLexer::getLabelValue(const std::string& label)
{
    const auto labelPosition = labels.find(label);
    if (labelPosition == labels.end())
    {
        return labels[label] = nextLabelValue++;
    }
    else
    {
        return labelPosition->second;
    }
}

const auto convertToUnsigned = [](const std::string& text) -> Token::ValueType {
    return static_cast<unsigned char>(
        std::stoi(text.substr(text.find_first_of(',') + 1)));
};

Tokens InstructionLexer::parseInstruction(const std::string& instruction)
{
    const auto trimmedInstruction = trimWhitespacesOnFront(instruction);
    if (trimmedInstruction.empty())
    {
        return {};
    }
    using TextToTokens = std::vector<
        std::tuple<std::regex, TokenType,
                   std::function<Token::ValueType(const std::string&)>>>;
    const std::string u8Regex{"[0-9]{1,2}|1[0-9]{1,2}|2[0-4][0-9]|25[0-5]"};
    using std::placeholders::_1;
    const TextToTokens acceptableInstructions{
        {std::regex{"out"}, TokenType::Out, alwaysZeroValue},
        {std::regex{"\\(0\\),a"}, TokenType::ZeroWithBracketsA,
         alwaysZeroValue},
        {std::regex{"ld"}, TokenType::Ld, alwaysZeroValue},
        {std::regex{"a," + u8Regex}, TokenType::A, convertToUnsigned},
        {std::regex{"b," + u8Regex}, TokenType::B, convertToUnsigned},
        {std::regex{"rlca"}, TokenType::Rlca, alwaysZeroValue},
        {std::regex{"rrca"}, TokenType::Rrca, alwaysZeroValue},
        {std::regex{"djnz"}, TokenType::Djnz, alwaysZeroValue},
        {std::regex{"[a-zA-Z_]+"}, TokenType::LabelRef,
         std::bind(&InstructionLexer::getLabelValue, this, _1)}};

    const auto instructionPosition =
        std::find_if(acceptableInstructions.begin(),
                     acceptableInstructions.end(), [&](const auto& tokenMap) {
                         return this->regexMatcher(trimmedInstruction,
                                                   std::get<0>(tokenMap));
                     });
    if (instructionPosition != acceptableInstructions.end())
    {
        return {{std::get<1>(*instructionPosition),
                 std::get<2>(*instructionPosition)(trimmedInstruction)}};
    }
    throw UnknownInstruction{"Unknown instruction: " + instruction};
}

std::string
InstructionLexer::trimWhitespacesOnFront(const std::string& instruction)
{
    return boost::algorithm::trim_left_copy_if(instruction, [](auto character) {
        return character == ' ' || character == '\t';
    });
}
