#pragma once

#include <vector>
#include "FlexScanner.hpp"
#include "Token.hpp"

namespace utec {
namespace compilers {

// Grammar:
// S -> AB
// A -> aA | a      ===>    a [A]
// B -> bB | b      ===>    b [B]

// Gramatica:
// exp -> exp opsuma term | term
// opsuma -> + | -
// term -> term opmult factor | factor
// opmult -> *
// factor -> (exp) | numero

// Gramatica modificada:
// exp -> term {opsuma term}
// opsuma -> + | -
// term -> factor {opmult factor}
// opmult -> *
// factor -> (exp) | numero



class Parser {
 public:
  Parser(std::istream& arg_yyin, std::ostream& arg_yyout) : scanner(arg_yyin, arg_yyout) {}
  
  void expect(Categoria cat_expected){
    auto token = scanner.query_token();
    if (token._atributo == cat_expected){
      scanner.get_token();
    } else{
      errors.push_back("caracter " + token._lexema + " unexpected");
    }
  }

  void factor()
  {
    if (scanner.query_token()._atributo == Categoria::parentesis_abrir)
    {
      exp();
      expect(Categoria::parentesis_cerrar);
    }
    else
    {
      expect(Categoria::numero);
    }
  }

  void opmult()
  {
    expect(Categoria::opmult);
  }

 
  void term() {
    factor();
    while (scanner.query_token()._atributo == Categoria::opmult)
    {
      opmult();
      factor();
    }
  }

  void opsuma()
  {
    expect(Categoria::opsuma);
  }

  
  void exp(){
    term();
    while (scanner.query_token()._atributo == Categoria::opsuma)
    {
      opsuma();
      term();
    }
  }


  std::vector<std::string> parse() {
    exp();
    expect(Categoria::END);
    return errors;

    // if( scanner.query_token()._atributo == Categoria::END 
    //   && errors.empty())
    //   return true;
    // return false;
  }

 private:
  std::vector<std::string> errors;
  FlexScanner scanner;
};

}  // namespace compilers
}  // namespace utec