#include<string>
using namespace std;

class CodeWriter
{
private :
    string _out_file;
public :
    CodeWriter(string out_file);
    void fileName(string out_file);
    void writeAritmetic(string command);
    void writePushPop(string command,string segment, int index);
    void writeIf(string label);
    void writeLabel(string label);
    void writeGoto(string label);
    void writeFunction(string functionName, int numLocals);
    void close();
    void write();
};
