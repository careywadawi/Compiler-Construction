#include <regex>
#include <map>
#include <iterator>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

map<string, string> roles{
    {"[0-9]+", "Number"},
    {"[a-z]+", "Identifier"},
    {"if|else|do|while|switch|case|break|continue|default|for|auto|const|int|float|double|string|void|char|char*|bool|return|cin|cout|endl|main", "Keyword"},
    {"\\+|\\-|\\*|\\/|\\>|\\<|\\=|\\++|\\==|\\--|\\&&|\\!=|\\+=", "Operator"},
    {"\\;|\\(|\\)|\\{|\\}|\\<|\\>|\\[|\\]|\\&|\\:", "Separator"},
};

map<size_t, pair<string, string>> matches;

void lex(const string &str)
{

    
    for (auto role = roles.begin(); role != roles.end(); ++role)
    {
        regex r(role->first);
        auto words_begin = sregex_iterator(str.begin(), str.end(), r);
        auto words_end = sregex_iterator();


        for (auto it = words_begin; it != words_end; ++it)
        {
            matches[it->position()] = make_pair(it->str(), role->second);
        }
    }

   
    for (auto match = matches.begin(); match != matches.end(); ++match)
    {
        cout << match->second.first << " : " << match->second.second << endl;
    }
}


void analyseProgram(const string &filename)
{
    string line;
    ifstream file(filename);

   
    if (!file.is_open())
    {
        cout << "An error occurred while opening the file" << endl;
        exit(0);
    }

    
    for (line; getline(file, line);)
    {
        lex(line);
    }
    file.close();
}

int main()
{
    analyseProgram("phrase.txt");
}