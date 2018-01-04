#include "tablesystem/TestTableSystem.h"
//#include "tablesystem/Index/TreeIndex/TreeIndex.h"
//#include "shellsystem/frontend/lex.yy.c"
//#include "shellsystem/frontend/SQLParser.tab.c"

extern int yyparse();

/**
 *  中文
 */
int myMain(int (* yyparse) (void)) {
    //runTestTableSystem();
    yyparse();
    return 0;
}
