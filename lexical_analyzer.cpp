#include<bits/stdc++.h>
using namespace std;

bool isKeyword(const string &word) {
    vector<string> keywords = {"int", "float", "string", "double", "char"};
    return find(keywords.begin(), keywords.end(), word) != keywords.end();
}

bool isIdentifier(const string &word) {
    if (word.empty() || (!isalpha(word[0]) && word[0] != '_'))
        return false;
    for (char c : word) {
        if (!isalnum(c) && c != '_')
            return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s;
    while (getline(cin, s)) {
        cout << "The expression is: " << s << "\n";

        map<string, vector<string>> result;
        string tmp = "";
        string ans = "valid\n";
        bool semi = false, eq = false;
        int star_loc=-1,identifier_loc=-1;

        for (int i = 0; i < s.size(); i++) {
            char ch = s[i];

            if(ch =='=') eq = true;

            if (ch == '=' && result["identifier"].size() > 1)
                ans = "Invalid\n";
            if(ch == '*' && star_loc == -1)star_loc = i;

            if (ch == '=' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ',' || ch == ';') {
                if (!tmp.empty()) {
                    if (isKeyword(tmp))
                        result["keyword"].push_back(tmp);
                    else if (isIdentifier(tmp)){
                        result["identifier"].push_back(tmp);
                        if(identifier_loc==-1)identifier_loc=i;
                    }
                    else
                        result["invalid"].push_back(tmp);
                    tmp = "";
                }
                string op(1, ch);
                result["special_symbol"].push_back(op);
                continue;
            }

            if (isspace(ch)) {
                if (!tmp.empty()) {
                    if (isKeyword(tmp))
                        result["keyword"].push_back(tmp);
                    else if (isIdentifier(tmp))
                        result["identifier"].push_back(tmp);
                    else
                        result["invalid"].push_back(tmp);
                    tmp = "";
                }
                continue;
            }
            tmp += ch;
        }

        if (!tmp.empty()) {
            if (isKeyword(tmp))
                result["keyword"].push_back(tmp);
            else if (isIdentifier(tmp))
                result["identifier"].push_back(tmp);
            else
                result["invalid"].push_back(tmp);
        }

        set<string> identifier;
        set<string> keywords;
        set<string> special_symbol;

        for (auto &entry : result) {
            if (entry.first == "identifier") {
                for (auto &i : entry.second)
                    identifier.insert(i);
            }
            if (entry.first == "keyword") {
                for (auto &i : entry.second)
                    keywords.insert(i);
            }
            if (entry.first == "special_symbol") {
                for (auto &i : entry.second){
                    special_symbol.insert(i);
                }
            }
        }

        
        cout << "Identifier: ";
        for (auto it = identifier.begin(); it != identifier.end(); ++it) {
            if (it != identifier.begin())
                cout << ", ";
            cout << *it;
        }
        cout << endl;

        cout << "Keywords: ";
        for (auto it = keywords.begin(); it != keywords.end(); ++it) {
            if (it != keywords.begin())
                cout << ", ";
            cout << *it;
        }
        cout << endl;

        char z=' ';
        cout << "Special_symbol: ";
        for (auto it = special_symbol.begin(); it != special_symbol.end(); ++it) {
            if (it != special_symbol.begin())
                cout << " ";
            cout << *it;
            if(*it == ";")semi = true;
            if(*it == ",")z=',';
        }
        cout << endl;

        if(!eq){
            if( result["identifier"].size()>2 ){
                ans="Invalid\n";
            }
            if( (result["identifier"].size()==1 && result["special_symbol"].size()==1) || 
                result["special_symbol"].size()==2 && result["identifier"].size()==1 && star_loc < identifier_loc && (star_loc!=-1 && identifier_loc!=-1)  ||
                special_symbol.size()==2 && z==',' && result["identifier"].size()  ==  result["special_symbol"].size())
                ans="Valid\n";
            else{
                ans= "Invalid\n";
            }
        }

        if (keywords.size() != 1  || !semi)
            ans = "Invalid\n";               
        
        cout << ans << endl ;
    }
    return 0;
}
