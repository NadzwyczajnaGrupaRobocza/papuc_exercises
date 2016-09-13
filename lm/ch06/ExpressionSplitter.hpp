#pragma once
#include <vector>
#include <string>

namespace calc
{
class ExpressionSplitter
{
public:
    std::vector<std::string> split(const std::string&);
    bool hasIncompleteInput();

private:
    void appendPreviousIncompleteInput(std::vector<std::string>&);
    void handleIncompleteInput(std::vector<std::string>&);
    std::string lastLineLeftover;
};
}
