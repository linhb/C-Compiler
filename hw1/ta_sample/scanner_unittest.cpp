#include <stdio.h>
#include <unistd.h>

#include "gtest/gtest.h"

#include "scanner_tokens.h"

unsigned long yylval;
extern FILE *yyin;
extern "C" int yylex();

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

class ScannerTest : public ::testing::Test {    
  protected:
    FILE *test_input;
    
    /* opens a pipe for directing input to the scanner. anything printed to test_input will be read by lex. */
    void SetUp() {
      int fds[2];
      ASSERT_EQ(0, pipe(fds));
      
      yyin = fdopen(fds[0], "r");
      ASSERT_TRUE(yyin);
      
      test_input = fdopen(fds[1], "w");
      ASSERT_TRUE(test_input);
    }
    
    void TearDown() {
      
    }
    
    void ExpectTokenOnly(int token, const char *input) {
      fputs(input, test_input);
      fclose(test_input);
      
      EXPECT_EQ(token, yylex());
      EXPECT_EQ(0ul, yylval);
      EXPECT_EQ(0, yylex());
    }
};

/* a simple test to make sure that the / character is scanned properly */
TEST_F(ScannerTest, SlashTest) {
  fputs("/", test_input);
  fclose(test_input);
  
  EXPECT_EQ(SLASH, yylex());
  EXPECT_EQ(0ul, yylval);
  EXPECT_EQ(0, yylex());
}

/* the next two tests are similar to SlashTest but have been refactored to use the ExpectTokenOnly method from the fixture */
TEST_F(ScannerTest, PlusTest) { this->ExpectTokenOnly(PLUS, "+"); }
TEST_F(ScannerTest, MinusTest) { this->ExpectTokenOnly(MINUS, "-"); }

/* this test ensures that "foobar" is scanned properly as an identifier */
TEST_F(ScannerTest, IdentifierTest) {
  fputs("foobar", test_input);
  fclose(test_input);
  
  EXPECT_EQ(IDENTIFIER, yylex());
  EXPECT_STREQ("foobar", (char *)yylval);
  EXPECT_EQ(0, yylex());
  
  free((char *)yylval);
}

/* this test ensures that an integer is scanned properly */
TEST_F(ScannerTest, IntTest) {
  fputs("3902834", test_input);
  fclose(test_input);
  
  EXPECT_EQ(NUMBER, yylex());
  EXPECT_EQ(3902834ul, ((struct number *)yylval)->value);
  EXPECT_FALSE(((struct number *)yylval)->overflow);
}