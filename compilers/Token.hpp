#pragma once

#include <iostream>

#include "Enums.h"

class Token {
 public:
  std::string _lexema;
  Categoria _atributo;

  Token(std::string lexema, Categoria atributo)
      : _lexema(lexema), _atributo(atributo) {}

  Token() : _lexema("END"), _atributo(END) {}

  bool operator==(const Token& in) const {
    return in._lexema == this->_lexema && in._atributo == this->_atributo;
  }
};

//Allows printing Tokens on the Google Test failing reports
std::ostream& operator<<(std::ostream& os, Token token) {
  os << "<";
  switch (token._atributo) {
    case Categoria::numero:
      os << "numero";
      break;
    case Categoria::opsuma:
      os << "opsuma";
      break;
    case Categoria::END:
      os << "END";
      break;
    case Categoria::parentesis_abrir:
      os << "Parentesis Abris";
      break;
    case Categoria::parentesis_cerrar:
      os << "Parentesis Cerrar";
      break;
  }
  os << ", " << token._lexema << ">";
  return os;
}
