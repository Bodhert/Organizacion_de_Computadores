grammar Jack;
class_1: 'class' className '{' classVarDec* subroutineDec* '}';

classVarDec: ('static' | 'field')type varName (',' varName)* ';';

type: 'int' | 'char' | 'boolean' | className;

subroutineDec: ('constructor' | 'function' | 'method')
                ('void' | type) subroutineName '(' parameterList ')'
                subroutineBody;

parameterList: ((type varName)(','type varName)*)?;

subroutineBody: '{' varDec* statements '}';

varDec: 'var' type varName (','varName)* ';';

className : IDENTIFIER;

subroutineName: IDENTIFIER;

varName: IDENTIFIER;

statements: statement*;

statement: letStatement | ifStatement | whileStatement |
           doStatement | returnStatement;

letStatement: 'let' varName ('[' expression ']')? '=' expression ';';

ifStatement: 'if' '(' expression ')' '{' statements '}'
            ('else' '{' statements '}')?;

whileStatement: 'while' '(' expression ')' '{' statements '}'; 

doStatement: 'do' subroutineCall';';

returnStatement: 'return' expression? ';';

expression: term (OP term)*;

term: INTEGERCONSTANT | STRINGCONSTANT | KEYWORDCONSTANT | 
        varName | varName '[' expression ']'| subroutineCall |
        '(' expression ')' | UNARYOP term;

subroutineCall: subroutineName '('expressionList ')' | (className 
                | varName)'.' subroutineName '(' expressionList ')';

expressionList: (expression (','expression)*)?;


INTEGERCONSTANT: [0-9]+; // preguntar si que tan necesario es controlar el rango hasta 32767

STRINGCONSTANT: '"' .*? '"';

IDENTIFIER:  ([a-zA-Z]|'_')([a-zA-Z0-9]|'_')*;

OP: '+' | '-' | '*' | '/' | '&' | '|' | '<' | '>' | '=' ;

UNARYOP: '-' | '~';

KEYWORDCONSTANT: 'true' | 'false' | 'null' | 'this';

KEYWORD : 'class' | 'constructor' | 'function' |
          'method' | 'field' | 'static' | 'var'|
          'int' | 'char' | 'boolean' | 'void' | 'true' | 
          'false' | 'null'  | 'this' | 'let' | 'do' |
          'if' | 'else' | 'while' | 'return';

SYMBOL : '{' | '}' | '(' | ')' | '[' | ']' | '.' | 
         ',' | ';' | '+' | '-' | '*' | '/' | '&' | 
         '|' | '<' | '>' | '=' | '~';
         
WS : [ \t\r\n]+ -> skip ;

COMMENT: '/*' .*? '*/' -> skip;

API_COMMENTS : '/**' .*? '*/' -> skip;

LINE_COMMENT : '//' ~[\r\n]* -> skip;


