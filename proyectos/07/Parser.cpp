#include<regex>

regex memoryAccess(R"(((^\s*)(push|pop)\s+(argument|local|static|constant|this|that|pointer|temp)\s+([1-9]\d*|0))(\s*(\/\/.*)?)$)");


Parser::Parser(string file_name)
{
    _file_name = file_name;
}

Parser::hasMoreCommands(string in)
{
    return regex_match(in,memoryAccess);
}




/*
regex rr (R"(((^\s*)(push|pop)\s+(argument|local|static|constant|this|that|pointer|temp)\s+([1-9]\d*|0))(\s*(\/\/.*)?)$)");
	bool c = regex_match("    pop pointer 1",rr);
	cout << c;
*/
