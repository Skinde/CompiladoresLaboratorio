#include <gtest/gtest.h>

#include <strstream>

#include "Parser.hpp"

using namespace utec::compilers;

class ParamTest : public testing::TestWithParam<std::pair<std::string, std::vector<std::string>>> {
};

// Grammar:
// S -> AB
// A -> aA | a
// B -> bB | b

TEST_P(ParamTest, basicTest) {
  std::istrstream str(GetParam().first.c_str());

  Parser parser(str, std::cout);
  EXPECT_EQ(parser.parse(), GetParam().second);
}

INSTANTIATE_TEST_SUITE_P(SimpleTest,
                         ParamTest,
                         testing::Values(
                          std::make_pair("2+2", std::vector<std::string>{"numero", "opsuma", "numero"})
                         ));

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}