#include "LedToken.hpp"

#include <gsl/gsl_assert>
#include <gtest/gtest.h>
#include <sstream>
#include <vector>

namespace lz
{
std::pair<std::string, int> splitTokenSI(const LedToken token)
{
    return token.split<std::string, int>(',');
}

std::pair<std::string, std::string> splitTokenSS(const LedToken token)
{
    return token.split<std::string, std::string>(',');
}

void expectCreateLedToken(const std::string& token)
{
    EXPECT_EQ(token, LedToken{token}.str());
}

void expectCopyingLedToken(const std::string& token)
{
    LedToken led{token};
    EXPECT_EQ(led.str(), LedToken{led}.str());
}

void expectMovingLedToken(const std::string& token)
{
    EXPECT_EQ(token, LedToken{LedToken(token)}.str());
}

void expectPrintingLedToken(const std::string& token)
{
    std::stringstream output;
    output << LedToken{token};
    EXPECT_EQ(token, output.str());
}

void expectSplittedStringString(const LedToken& token,
                                const std::string& expectedFirst,
                                const std::string& expectedSecond)
{
    const auto splitted = token.split<std::string, std::string>(',');
    EXPECT_EQ(expectedFirst, splitted.first);
    EXPECT_EQ(expectedSecond, splitted.second);
}

static std::vector<std::string> test_values{"ala", "bala", "token23",
                                            "i tu byl sobie token"};

TEST(LedTokenTest, creation)
{
    for (const auto& value : test_values)
    {
        expectCreateLedToken(value);
    }
}

TEST(LedTokenTest, copying)
{
    for (const auto& value : test_values)
    {
        expectCopyingLedToken(value);
    }
}

TEST(LedTokenTest, moving)
{
    for (const auto& value : test_values)
    {
        expectMovingLedToken(value);
    }
}

TEST(LedTokenTest, printing)
{
    for (const auto& value : test_values)
    {
        expectPrintingLedToken(value);
    }
}

TEST(LedTokenTest, splitStringInt)
{
    const auto splitted = LedToken{"a,23"}.split<std::string, int>(',');
    EXPECT_EQ("a", splitted.first);
    EXPECT_EQ(23, splitted.second);
}

TEST(LedTokenTest, splitStringString)
{
    expectSplittedStringString(LedToken{"a,23"}, "a", "23");
    expectSplittedStringString(LedToken{"a, "}, "a", " ");
}

TEST(LedTokenTest, splitStringIntTooShortTokenShouldThrow)
{
    EXPECT_THROW(splitTokenSI(LedToken{""}), gsl::fail_fast);
    EXPECT_THROW(splitTokenSI(LedToken{","}), gsl::fail_fast);
    EXPECT_THROW(splitTokenSI(LedToken{" ,"}), gsl::fail_fast);
    EXPECT_THROW(splitTokenSI(LedToken{", "}), gsl::fail_fast);

    EXPECT_THROW(splitTokenSI(LedToken{"    "}), gsl::fail_fast);
    EXPECT_THROW(splitTokenSI(LedToken{"      ,"}), gsl::fail_fast);
    EXPECT_THROW(splitTokenSI(LedToken{",     "}), gsl::fail_fast);
    EXPECT_THROW(splitTokenSI(LedToken{"   ,   "}), std::exception);
    EXPECT_THROW(splitTokenSI(LedToken{",12"}), std::exception);
}

TEST(LedTokenTest, splitStringStringTooShortTokenShouldThrow)
{
    EXPECT_THROW(splitTokenSS(LedToken{""}), gsl::fail_fast);
    EXPECT_THROW(splitTokenSS(LedToken{","}), gsl::fail_fast);
    EXPECT_THROW(splitTokenSS(LedToken{" ,"}), gsl::fail_fast);
    EXPECT_THROW(splitTokenSS(LedToken{", "}), gsl::fail_fast);
    EXPECT_THROW(splitTokenSS(LedToken{"    "}), gsl::fail_fast);
    EXPECT_THROW(splitTokenSS(LedToken{"      ,"}), gsl::fail_fast);
    EXPECT_THROW(splitTokenSS(LedToken{",     "}), gsl::fail_fast);
    EXPECT_THROW(splitTokenSS(LedToken{",12"}), std::exception);
}
}
