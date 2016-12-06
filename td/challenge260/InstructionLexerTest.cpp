#include "InstructionLexer.hpp"

#include "gtest/gtest.h"

using namespace ::testing;

struct InstructionLexerTest : public Test
{
    InstructionLexer parser;

    Token createTokenWithZeroValue(TokenType type)
    {
        return {type, 0};
    }

    const Token::ValueType nextLabelValue{1};
};

TEST_F(InstructionLexerTest, ParserShouldRejectNotFullInstuctionLd)
{
    EXPECT_THROW(parser.parseInstructions(" ld a,"),
                 InstructionLexer::UnknownInstruction);
}

TEST_F(InstructionLexerTest, ParserShouldParseLdAInstruction)
{
    const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Ld),
                                {TokenType::A, 1}};
    EXPECT_EQ(expectedTokens, parser.parseInstructions(" ld a,1"));
}

TEST_F(InstructionLexerTest, ParserShouldDeclineUnknownWithoutWhitespaceOnFront)
{
    EXPECT_THROW(parser.parseInstructions("out (0),a"),
                 InstructionLexer::UnknownInstruction);
}

TEST_F(InstructionLexerTest, ParserShouldAcceptInstructionOut)
{
    const Tokens expectedTokens{
        createTokenWithZeroValue(TokenType::Out),
        createTokenWithZeroValue(TokenType::ZeroWithBracketsA)};
    EXPECT_EQ(expectedTokens, parser.parseInstructions(" out (0),a"));
}

TEST_F(InstructionLexerTest, ParserShouldAcceptEmptyLine)
{
    const Tokens expectedTokens{};
    EXPECT_EQ(expectedTokens, parser.parseInstructions(""));
}

TEST_F(InstructionLexerTest, ParserShouldAcceptInstructionOutWithWhitespaces)
{
    const Tokens expectedTokens{
        createTokenWithZeroValue(TokenType::Out),
        createTokenWithZeroValue(TokenType::ZeroWithBracketsA)};
    EXPECT_EQ(expectedTokens, parser.parseInstructions(" \t    out (0),a"));
}

TEST_F(InstructionLexerTest, ParserShouldAcceptTwoInstructions)
{
    const Tokens expectedTokens{
        createTokenWithZeroValue(TokenType::Out),
        createTokenWithZeroValue(TokenType::ZeroWithBracketsA),
        createTokenWithZeroValue(TokenType::Out),
        createTokenWithZeroValue(TokenType::ZeroWithBracketsA)};
    EXPECT_EQ(expectedTokens,
              parser.parseInstructions(" out (0),a\n out (0),a"));
}

TEST_F(InstructionLexerTest, ParserShouldThrowIfSecondInstructionIsInvalid)
{
    EXPECT_THROW(parser.parseInstructions(" out (0),a\ninvalid"),
                 InstructionLexer::UnknownInstruction);
}

TEST_F(InstructionLexerTest, ParserShouldAcceptTwoInstructionsWithEmptyLine)
{
    const Tokens expectedTokens{
        createTokenWithZeroValue(TokenType::Out),
        createTokenWithZeroValue(TokenType::ZeroWithBracketsA),
        createTokenWithZeroValue(TokenType::Out),
        createTokenWithZeroValue(TokenType::ZeroWithBracketsA)};
    EXPECT_EQ(expectedTokens,
              parser.parseInstructions(" out (0),a\n \n out (0),a"));
}

TEST_F(InstructionLexerTest, ParserShouldAbleToGetMinusToLoad)
{
    EXPECT_THROW(parser.parseInstructions(" ld a,-1"),
                 InstructionLexer::UnknownInstruction);
}

TEST_F(InstructionLexerTest, ParserShouldAbleToGet256ToLoad)
{
    EXPECT_THROW(parser.parseInstructions(" ld b,256"),
                 InstructionLexer::UnknownInstruction);
}

TEST_F(InstructionLexerTest, ParserShouldParseLdBInstruction)
{
    const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Ld),
                                {TokenType::B, 10}};
    EXPECT_EQ(expectedTokens, parser.parseInstructions(" ld b,10"));
}

TEST_F(InstructionLexerTest, ParserShouldParseRlcaInstruction)
{
    const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Rlca)};
    EXPECT_EQ(expectedTokens, parser.parseInstructions(" rlca"));
}

TEST_F(InstructionLexerTest, ParserShouldParseRrcaInstruction)
{
    const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Rrca)};
    EXPECT_EQ(expectedTokens, parser.parseInstructions(" rrca"));
}

TEST_F(InstructionLexerTest, ParserShouldParseDjnzInstruction)
{
    const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Djnz)};
    EXPECT_EQ(expectedTokens, parser.parseInstructions(" djnz"));
}

TEST_F(InstructionLexerTest, ParserShouldParseALabel)
{
    const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Label)};
    EXPECT_EQ(expectedTokens, parser.parseInstructions("a:"));
}

TEST_F(InstructionLexerTest, ParserShouldParseALabelWithUnderscore)
{
    const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Label)};
    EXPECT_EQ(expectedTokens, parser.parseInstructions("_:"));
}

TEST_F(InstructionLexerTest, ParserShouldNotAcceptLabelWithWhitespaces)
{
    EXPECT_THROW(parser.parseInstructions(" label:"),
                 InstructionLexer::UnknownInstruction);
}

TEST_F(InstructionLexerTest,
       ParserShouldNotParseDjnzWithLabelRefWithouPreviosLabel)
{
    EXPECT_THROW(parser.parseInstructions(" djnz w"),
                 InstructionLexer::UnknownLabel);
}

TEST_F(InstructionLexerTest, ParserShouldParseDjnzWithLabelRefA)
{
    const Tokens expectedTokensLabel{
        createTokenWithZeroValue(TokenType::Label)};
    EXPECT_EQ(expectedTokensLabel, parser.parseInstructions("a:"));

    const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Djnz),
                                createTokenWithZeroValue(TokenType::LabelRef)};
    EXPECT_EQ(expectedTokens, parser.parseInstructions(" djnz a"));
}

TEST_F(InstructionLexerTest, ParserShouldParseDjnzWithLabelRef_)
{
    const Tokens expectedTokensLabel{
        createTokenWithZeroValue(TokenType::Label)};
    EXPECT_EQ(expectedTokensLabel, parser.parseInstructions("_:"));

    const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Djnz),
                                createTokenWithZeroValue(TokenType::LabelRef)};
    EXPECT_EQ(expectedTokens, parser.parseInstructions(" djnz _"));
}

TEST_F(InstructionLexerTest, ParserShouldMakeSameLabelToHaveSameValue)
{
    const Tokens expectedTokensLabel{
        createTokenWithZeroValue(TokenType::Label)};
    EXPECT_EQ(expectedTokensLabel, parser.parseInstructions("_:"));

    const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Djnz),
                                createTokenWithZeroValue(TokenType::LabelRef)};
    EXPECT_EQ(expectedTokens, parser.parseInstructions(" djnz _"));

    const Tokens expectedTokensFromSecondInstruction{
        createTokenWithZeroValue(TokenType::Djnz),
        createTokenWithZeroValue(TokenType::LabelRef)};
    EXPECT_EQ(expectedTokensFromSecondInstruction,
              parser.parseInstructions(" djnz _"));
}

TEST_F(InstructionLexerTest, ParserShouldReturnDifferentValueForDifferntLabels)
{
    const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Label)};
    EXPECT_EQ(expectedTokens, parser.parseInstructions("_:"));

    const Tokens expectedTokensSecond{{TokenType::Label, nextLabelValue}};
    EXPECT_EQ(expectedTokensSecond, parser.parseInstructions("q:"));
}

TEST_F(InstructionLexerTest, ParserShouldMatchLabelWithLabelRef)
{
    const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Label)};
    EXPECT_EQ(expectedTokens, parser.parseInstructions("_:"));

    const Tokens expectedTokensSecond{{TokenType::Label, nextLabelValue}};
    EXPECT_EQ(expectedTokensSecond, parser.parseInstructions("q:"));

    const Tokens expectedTokensThird{createTokenWithZeroValue(TokenType::Djnz),
                                     {TokenType::LabelRef, nextLabelValue}};
    EXPECT_EQ(expectedTokensThird, parser.parseInstructions(" djnz q"));
}

TEST_F(InstructionLexerTest, ParserShouldParseLdAInstruction255)
{
    const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Ld),
                                {TokenType::A, 255}};
    EXPECT_EQ(expectedTokens, parser.parseInstructions(" ld a,255"));
}
