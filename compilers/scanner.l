%{
#include "Enums.h"
%}

%option noyywrap c++


%%
[0-9]+ return Categoria::numero;
"+" return Categoria::opsuma;
"END" return Categoria::END;

\n  return Categoria::END;
\t
.   return Categoria::ERROR;

%%
