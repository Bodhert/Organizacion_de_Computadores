#include<regex>
class Parser{
private:
        string _file_name;

public:
    Parser(string file_name);
    bool hasMoreCommands(string in);
    void advance();
    string commandType(string in);
    string arg1(string in);
    int arg2(string in);
}
