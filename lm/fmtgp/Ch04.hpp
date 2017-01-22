#pragma once
#include <utility>

using integer = int;
using line_segment = double;

std::pair<integer, line_segment> quotient_remainder(line_segment a, line_segment b);
integer quotient(line_segment, line_segment);
line_segment largest_doubling(line_segment, line_segment);
line_segment half(line_segment);
