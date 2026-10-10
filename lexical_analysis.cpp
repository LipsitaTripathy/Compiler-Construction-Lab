#include <iostream>
#include <string>
#include <cctype>
#include <unordered_set>
using namespace std;

int main()
{
    unordered_set<string> keywords = {
        "int", "char", "float", "double", "void",
        "if", "else", "for", "while", "do",
        "return", "break", "continue", "switch",
        "case", "default", "long", "short",
        "const", "struct", "sizeof"
    };

    string code;
    cout << "Enter a line of C source code:\n";
    getline(cin, code);

    cout << "\nLexical Analysis:\n";

    for (int i = 0; i < (int)code.length();)
    {
        if (isspace(static_cast<unsigned char>(code[i])))
        {
            i++;
            continue;
        }

        if (isalpha(static_cast<unsigned char>(code[i])) ||
            code[i] == '_')
        {
            string token;

            while (i < (int)code.length() &&
                   (isalnum(static_cast<unsigned char>(code[i])) ||
                    code[i] == '_'))
            {
                token += code[i++];
            }

            if (keywords.count(token))
                cout << token << " : Keyword\n";
            else
                cout << token << " : Identifier\n";
        }
        else if (isdigit(static_cast<unsigned char>(code[i])))
        {
            string token;

            while (i < (int)code.length() &&
                   (isdigit(static_cast<unsigned char>(code[i])) ||
                    code[i] == '.'))
            {
                token += code[i++];
            }

            cout << token << " : Number\n";
        }
        else if (i + 1 < (int)code.length() &&
                 (code.substr(i, 2) == "==" ||
                  code.substr(i, 2) == "!=" ||
                  code.substr(i, 2) == "<=" ||
                  code.substr(i, 2) == ">=" ||
                  code.substr(i, 2) == "++" ||
                  code.substr(i, 2) == "--" ||
                  code.substr(i, 2) == "&&" ||
                  code.substr(i, 2) == "||"))
        {
            cout << code.substr(i, 2) << " : Operator\n";
            i += 2;
        }
        else
        {
            char ch = code[i++];

            if (string("+-*/%=<>!&|").find(ch) != string::npos)
                cout << ch << " : Operator\n";
            else if (string(";,(){}[].").find(ch) != string::npos)
                cout << ch << " : Special Symbol\n";
            else
                cout << ch << " : Unknown Symbol\n";
        }
    }

    return 0;
}
