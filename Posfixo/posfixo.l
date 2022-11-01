%{
#include "posfixo.tab.h"
%}

%%

[\n\t ]  

\+    { return MAIS; }
\-    { return MENOS; }
\*    { return ASTERISCO;  }
\/    { return DIV;  }
and   { return AND; }
or    { return OR; }
a     { return IDENT_INT;   }
b     { return IDENT_BOOL;   }

%%

