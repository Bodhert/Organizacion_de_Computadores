#include<regex>
#include<string>
using namespace std;
class Parser{

private:
        string _file_name;

public:
    string currentCommand;
    Parser(string file_name);
    bool hasMoreCommands();
    void advance();
    string commandType();
    string arg1();
    int arg2();
    int line();
};
