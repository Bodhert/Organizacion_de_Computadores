#include <iostream>
#include <regex>
#include <string>
#include <stdio.h>
#include <cstddef>
#include <fstream>
#include <bitset>
#include <fstream>

using namespace std;

map<string,int> symbols;
map<string,int> dest;
map<string,int> comp;
map<string,int> jump;

int variablePos;


bool isAinstruction(string toParse)
{
    regex Ainstruction("(\\\s*@)([a-zA-Z_$][a-zA-Z_$0-9\\.]*$|([[:digit:]]+))");
    return regex_match(toParse,Ainstruction);
}

bool isCinstruction(string toParse)
{
 regex Cinstruction("\\\s*(A|D|M|MD|AM|AD|AMD)\\\s*\\=\\\s*(A|D|M)\\\s*(\\+|-|&|\\|)\\\s*(A|D|M|1)\\\s*");
 return regex_match(toParse,Cinstruction);
}

bool isCinstruction1(string toParse)
{
   regex Cinstruction1("\\\s*(A|D|M|MD|AM|AD|AMD)\\\s*\\=\\\s*(A|D|M|0|1|-1|!M|!D|!A)\\\s*");
   return regex_match(toParse,Cinstruction1);
}

bool isCinstruction2(string toParse)
{
 regex Cinstruction2("\\\s*(D|0)\\\s*;\\\s*(JGT|JEQ|JGE|JLT|JNE|JLE|JMP)\\\s*");
 return regex_match(toParse,Cinstruction2);
}

bool isCommentWithInstuctionA(string toParse)
{
    regex Acomment("(\\\s*@)[a-zA-Z_$][a-zA-Z_$0-9\\.]*\\\s*//\\\s*.*\\\s*");
    return regex_match(toParse,Acomment);
}

bool isCommentWithInstuctionC(string toParse)
{
    regex CinstructionComment("\\\s*(A|D|M|MD|AM|AD|AMD)\\\s*\\=\\\s*(A|D|M)\\\s*(\\+|-)\\\s*(A|D|M|1)\\\s*//\\\s*.*\\\s*");
    return regex_match(toParse, CinstructionComment);
}

bool isCommentWithInstuctionC1(string toParse)
{
    regex CinstructionComment1("\\\s*(A|D|M|MD|AM|AD|AMD)\\\s*\\=\\\s*(A|D|M|0|1|-1|!M|!D|!A)\\\s*//\\\s*.*\\\s*");
    return regex_match(toParse,CinstructionComment1);
}

bool isCommentWithInstuctionC2(string toParse)
{
    regex CinstructionComment2("\\\s*(D|0)\\\s*;\\\s*(JGT|JEQ|JGE|JLT|JNE|JLE|JMP)\\\s*//\\\s*.*\\\s*");
    return regex_match(toParse,CinstructionComment2);
}

bool isCommentTag(string toParse)
{
    regex tagComment("\\\s*\\\(\\\s*[a-zA-Z_$][a-zA-Z_$0-9\\.]*\\\s*\\\)\\\s*//\\\s*.*\\\s*");
    return regex_match(toParse,tagComment);
}


bool isLineComment(string toParse)
{
    regex simpleComment("\\\s*//\\\s*.*\\\s*");
    return regex_match(toParse,simpleComment);
}

bool isEmptyLine(string toParse)
{
    regex blank("\\\s*");
    return regex_match(toParse,blank);
}

bool isTag(string toParse)
{
    regex tag("\\\s*\\\(\\\s*[a-zA-Z_$][a-zA-Z_$0-9\\.]*\\\s*\\\)\\\s*");
    return regex_match(toParse,tag);
}

string cleanTag(string TagToclean)
{

    string clean = "";
    size_t firstBracket = TagToclean.find_first_of("(");
    size_t lastBracket = TagToclean.find_last_of(")");

    for(size_t i = firstBracket+1; i < lastBracket; ++i)
    {
        clean += TagToclean[i];
    }

    return clean;
}

string cleanTagWithComments(string TagToclean)
{
    string clean = "";
    size_t firstBracket = TagToclean.find_first_of("(");
    size_t findComment = TagToclean.find_first_of("//");

    for(size_t i = firstBracket+1; i < findComment && TagToclean[i] != ')'; ++i)
    {
        clean += TagToclean[i];
    }

    return clean;

}
void assignTags(string tag, int pos)
{
    symbols[tag] = pos;
}

string cleanAinstruction(string toClean)
{
    string clean = "";
    size_t findAt = toClean.find_first_of("@");
    for(size_t i = findAt+1; i < toClean.size() && toClean[i] != ' '; ++i)
    {
        clean += toClean[i];
    }

    return clean;
}

string cleanAinstructionWithComments(string toClean)
{
    string clean = "";
    size_t findAt = toClean.find_first_of("@");
    size_t findComment = toClean.find_first_of("//");

    for(size_t i = findAt+1; i < findComment && toClean[i] != ' '; ++i)
    {
        clean += toClean[i];
    }

    return clean;

}
string encodeAinstruction(string aIns)
{
    int num = atoi(aIns.c_str());
    if(!(num == 0 && aIns[0] != '0'))
    {

        int temp  = 0 ;
        temp |= num;
        string ans = bitset<16>(temp).to_string();
        return ans;
    }
    else
    {
        if(!symbols.count(aIns))
        {
            symbols[aIns] = variablePos;
            variablePos++;   // controlar variable pos que no me sobreescriba los simbolos especiales
        }

        num = symbols[aIns];
        int temp  = 0 ;
        temp |= num;
        string ans = bitset<16>(temp).to_string();
        return ans;
    }

}

string cleanCinstructions(string cIns)
{
    string clean = "";
    for(int i = 0; i < cIns.size();++i)
    {
        if(cIns[i] != ' ') clean += cIns[i];
    }

    return clean;

}

string cleanCinstructionsWithComments(string cIns)
{
    string clean = "";
    size_t findComment = cIns.find_first_of("//");
    for(size_t i = 0 ; i < findComment; ++i )
    {
        if(cIns[i]!=' ' ) clean += cIns[i];
    }

    return clean;
}

string encodeCinstruction(string cIns, int type)
{

    if(type == 0)
    {
       string dest1 = "";
       string comp1 = "";
       size_t findEquals = cIns.find_first_of("=");
       for(size_t i = 0; i < findEquals; ++i)  dest1 += cIns[i];
       for(size_t i = findEquals+1; i < cIns.size(); ++i) comp1 += cIns[i];

       if(!dest.count(dest1))
       {
           cout << dest1 << " is an invalid destination " << endl;
           return " ";
       }

       if(!comp.count(comp1))
       {
            cout << comp1 << " is an invalid component " << endl;
            return " ";
       }

        int temp = 0;
        temp |= dest[dest1];
        temp |= comp[comp1];
        string ans = bitset<16>(temp).to_string();
        return ans;
    }
    else
    {
        string comp1 = "";
        string jump1 = "";
       size_t findSemicolon = cIns.find_first_of(";");
       for(size_t i = 0; i < findSemicolon; ++i)  comp1 += cIns[i];
       for(size_t i = findSemicolon+1; i < cIns.size(); ++i) jump1 += cIns[i];

       if(!comp.count(comp1))
       {
           cout << comp1 << " is an invalid componet " << endl;
           return " ";
       }

       if(!jump.count(jump1))
       {
            cout << jump1 << " is not a valid jump " << endl;
            return " ";
       }

        int temp = 0;
        temp |= comp[comp1];
        temp |= jump[jump1];
        string ans = bitset<16>(temp).to_string();
        return ans;
    }

}

void initialize()
{
    symbols.clear();
    dest.clear();
    comp.clear();
    jump.clear();
    variablePos = 16;

    symbols["R0"] = 0;
    symbols["R1"] = 1;
    symbols["R2"] = 2;
    symbols["R3"] = 3;
    symbols["R4"] = 4;
    symbols["R5"] = 5;
    symbols["R6"] = 6;
    symbols["R7"] = 7;
    symbols["R8"] = 8;
    symbols["R9"] = 9;
    symbols["R10"] = 10;
    symbols["R11"] = 11;
    symbols["R12"] = 12;
    symbols["R13"] = 13;
    symbols["R14"] = 14;
    symbols["R15"] = 15;
    symbols["SCREEN"] = 16384;
    symbols["KBD"] = 24576;
    symbols["SP"] = 0;
    symbols["LCL"] = 1;
    symbols["ARG"] = 2;
    symbols["THIS"] = 3;
    symbols["THAT"] = 4;

    dest["M"] = 57352;
    dest["D"] = 57360;
    dest["MD"] = 57368;
    dest["A"] = 57376;
    dest["AM"] = 57384;
    dest["AD"] = 57392;
    dest["AMD"] = 57400;

    comp["0"] = 60032;
    comp["1"] = 61376;
    comp["-1"] = 61120;
    comp["D"] = 58112;
    comp["A"] = 60416;
    comp["!D"] = 58176;
    comp["!A"] = 60480;
    comp["-D"] = 58304;
    comp["-A"] = 60608;
    comp["D+1"] = 59328;
    comp["A+1"] = 60864;
    comp["D-1"] = 58240;
    comp["A-1"] = 60544;
    comp["D+A"] = 57472;
    comp["D-A"] = 58560;
    comp["A-D"] = 57792;
    comp["D&A"] = 57344;
    comp["D|A"] = 58688;
    comp["M"] = 64512;
    comp["!M"] = 64576;
    comp["-M"] = 64704;
    comp["M+1"] = 64960;
    comp["M-1"] = 64640;
    comp["D+M"] = 61568;
    comp["D-M"] = 62656;
    comp["M-D"] = 61888;
    comp["D&M"] = 61440;
    comp["D|M"] = 62784;

    jump["JGT"] = 57345;
    jump["JEQ"] = 57346;
    jump["JGE"] = 57347;
    jump["JLT"] = 57348;
    jump["JNE"] = 57349;
    jump["JLE"] = 57350;
    jump["JMP"] = 57351;


}

void secondPass(string file)
{
    ifstream fileToRead(file);
	string input;
	string ans = "";
	bool write = true;
    int lineCounter = 1;
	int asmLineCounter = 0;


	while(getline(fileToRead,input))
    {
        if(isAinstruction(input))
        {
          string Ains = cleanAinstruction(input);
          string instruction = encodeAinstruction(Ains);
          ans += instruction + '\n';
        }
        else if(isCommentWithInstuctionA(input))
        {
            string Ains = cleanAinstructionWithComments(input);
            string instruction = encodeAinstruction(Ains);
            ans += instruction + '\n';
        }
        else if(isCinstruction(input))
        {
            string cIns = cleanCinstructions(input);
            string instruction = encodeCinstruction(cIns,0);
            if(instruction == " ") break;
            ans += instruction + '\n';
        }
        else if(isCommentWithInstuctionC(input))
        {
            string cIns = cleanCinstructionsWithComments(input);
            string instruction = encodeCinstruction(cIns,0);
            if(instruction == " ") break;
            ans += instruction + '\n';
        }
        else if(isCinstruction1(input))
        {
            string cIns = cleanCinstructions(input);
            string instruction = encodeCinstruction(cIns,0);
            if(instruction == " ") break;
            ans += instruction + '\n';
        }
        else if(isCommentWithInstuctionC1(input))
        {
            string cIns = cleanCinstructionsWithComments(input);
            string instruction = encodeCinstruction(cIns,0);
            if(instruction == " ") break;
            ans += instruction + '\n';
        }
        else if(isCinstruction2(input))
        {
            string cIns = cleanCinstructions(input);
            string instruction = encodeCinstruction(cIns,1);
            if(instruction == " ") break;
            ans += instruction + '\n';
        }
        else if(isCommentWithInstuctionC2(input))
        {
            string cIns = cleanCinstructionsWithComments(input);
            string instruction = encodeCinstruction(cIns,1);
            if(instruction == " ") break;
            ans += instruction + '\n';
        }

    }

     ofstream out("test.hack");
     out << ans;
     fileToRead.seekg(0,fileToRead.beg);

}

void firstPass(string file)
{
	ifstream fileToRead(file);
	string input;
	int lineCounter = 1;
	int asmLineCounter = 0;
	while(getline(fileToRead,input))
	{
	    if(isTag(input))
        {
            //cout << lineCounter << " tag " << endl;
            string tag = cleanTag(input);
            assignTags(tag,asmLineCounter);
        }
        else if(isCommentTag(input))
        {
            string tag = cleanTagWithComments(input);
            assignTags(tag,asmLineCounter);
        }
        else if(isAinstruction(input))
        {
            //cout << lineCounter << " A instrution" << endl;
            asmLineCounter++;
        }
        else if(isCinstruction(input) || isCinstruction1(input) ||
                isCinstruction2(input))
        {
            //cout << lineCounter << " C instrution" << endl;
            asmLineCounter++;
        }
        else if(isCommentWithInstuctionA(input) || isCommentWithInstuctionC(input)
                || isCommentWithInstuctionC1(input)
                || isCommentWithInstuctionC2(input))
        {
            //cout << lineCounter << " commentary whit insturction" << endl;
            asmLineCounter++;
        }
        else if(isLineComment(input))
        {
            //cout << lineCounter << " line comment " << endl;
        }
        else if(isEmptyLine(input))
        {
            //cout << lineCounter << " Empty Line " << endl;
        }
        else
        {
           cout << "Syntax error: unrecognized expression at line: " << lineCounter << endl;
           break;
        }

        lineCounter++;
	}

    fileToRead.seekg(0,fileToRead.beg);

}

int main(int argc, char* argv[])
{
    initialize();
    if(argv[1] != NULL)
    {
        firstPass(argv[1]);
        secondPass(argv[1]);
    }
    else cout << "The execution should be: .exe nameOfyourfile.asm" << endl;

	return 0;
}
