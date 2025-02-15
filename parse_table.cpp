#include <bits/stdc++.h>
using namespace std;

typedef map<pair<string, string>, vector<string>> ParsingTable;

bool isTerminal(const string &symbol) {
    return !(symbol[0] >= 'A' && symbol[0] <= 'Z');
}

bool parseString(const ParsingTable &table, const string &startSymbol, vector<string> inputTokens) {
    stack<string> parsingStack;
    parsingStack.push("$");
    parsingStack.push(startSymbol); 
    inputTokens.push_back("$");
    int index = 0;

    while (!parsingStack.empty()) {
        string top = parsingStack.top();
        string currentToken = inputTokens[index];

        cout << "Stack: " << top << ", Input: " << currentToken << endl; 

        if (top == "$" && currentToken == "$") {
            return true; 
        }

        if (top == currentToken) {
            parsingStack.pop();
            index++;
        } else if (isTerminal(top)) {
            cout << "Error: Unexpected token '" << currentToken << "' at position " << index + 1 << endl;
            return false; 
        } else {
            parsingStack.pop(); 
            if (table.find({top, currentToken}) != table.end()) {
                vector<string> production = table.at({top, currentToken});
                if (production[0] != "epsilon") {
                    for (int i = production.size() - 1; i >= 0; i--) {
                        parsingStack.push(production[i]);
                    }
                }
            } else {
                cout << "Error: No valid production found for non-terminal '" << top 
                     << "' and input token '" << currentToken << "'" << endl;
                return false; 
            }
        }
    }
    return false;
}

void displayParsingTable(const ParsingTable &table) {
    cout << "\nParsing Table:\n";
    cout << "-----------------------------------\n";
    cout << setw(10) << "Non-Terminal" << setw(10) << "Input" << setw(20) << "Production" << endl;
    cout << "-----------------------------------\n";
    for (const auto &entry : table) {
        pair<string, string> key = entry.first;
        vector<string> production = entry.second;
        cout << setw(10) << key.first << setw(10) << key.second << setw(20);
        for (const string &symbol : production) {
            cout << symbol << " ";
        }
        cout << endl;
    }
    cout << "-----------------------------------\n";
}

int main() {
    ParsingTable parsingTable;

    parsingTable[{"E", "id"}] = {"T", "E'"};
    parsingTable[{"E", "("}] = {"T", "E'"};
    parsingTable[{"E'", "+"}] = {"+", "T", "E'"};
    parsingTable[{"E'", ")"}] = {"epsilon"};
    parsingTable[{"E'", "$"}] = {"epsilon"};
    parsingTable[{"T", "id"}] = {"F", "T'"};
    parsingTable[{"T", "("}] = {"F", "T'"};
    parsingTable[{"T'", "+"}] = {"epsilon"};
    parsingTable[{"T'", "*"}] = {"*", "F", "T'"};
    parsingTable[{"T'", ")"}] = {"epsilon"};
    parsingTable[{"T'", "$"}] = {"epsilon"};
    parsingTable[{"F", "id"}] = {"id"};
    parsingTable[{"F", "("}] = {"(", "E", ")"};

    displayParsingTable(parsingTable);

    cout << "\nEnter the input string (tokens separated by spaces): ";
    string input;
    getline(cin, input);

    vector<string> inputTokens;
    stringstream ss(input);
    string token;
    while (ss >> token) {
        inputTokens.push_back(token);
    }

    if (parseString(parsingTable, "E", inputTokens)) {
        cout << "\nString is Accepted!" << endl;
    } else {
        cout << "\nString is Rejected!" << endl;
    }

    return 0;
}