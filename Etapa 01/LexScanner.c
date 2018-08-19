#include <stdio.h>
#include "tokens.h"

extern int yylex();
extern int yylineno;
extern char* yytext;
int run;

int isRunning(){
    if(yylex() == 0){
        run = 0;
    }
    else{
        run = 1;
    }

    return run;
}

int main(void)
{
    int ntoken;

    while(isRunning()){
        ntoken = yylex();
        printf("%d\n", ntoken);
    }

    return 0;

}
