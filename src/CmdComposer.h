#ifndef CMDCOMPOSER_H
#define CMDCOMPOSER_H
#include "BaseCmd.h"
#include "Cmd.h"
#include "Connector.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <string.h>
#include "ParenCmd.h"

using namespace std;

class CmdComposer {
    public:
        CmdComposer() { };
        BaseCmd* compose(istringstream &ss, BaseCmd* head = 0) {
            string tstr;
            vector<string> v;
            int conType = -1; //default no connector
            BaseCmd* parenCmd = 0; //keeps track of whether there is a parenthesis
            while (ss >> tstr) { 
                
                                       //command or not
                if(tstr.at(0) == '(') { //deciphers parenthesis 
                    tstr = tstr.substr(1);
                    int numParen = 1;
                    char c; //character read
                    bool inQuotes = false; //keeps track of quotations
                    
                    
                    while ( (numParen > 0) ) {
                        if (!(ss.get(c))) {
                            cout << "> ";
                            string tempString;
                            string space = " ";
                            getline(cin, tempString);
                            tempString = space + tempString;
                            ss.str(tempString);
                            ss.clear();
                            c = ss.get();
                        }
                        if (c == '"') {
                            inQuotes = !inQuotes; //toggle quotes
                        }
                        else if (c == '(' && !inQuotes) {
                            numParen++;
                        }
                        else if (c == ')' && !inQuotes) {
                            numParen--;
                        }
                        tstr += c;
                        
                    }
                    tstr = tstr.substr(0, tstr.size() - 1);
                    istringstream strin(tstr);
                    parenCmd = new ParenCmd(this->compose(strin));
                }
                if (tstr.at(0) == '"') { //quotation marks
                    bool isFinished = false;
                    tstr = tstr.substr(1, tstr.size() - 1);
                    if (tstr.find('"') != string::npos) { //for single word quotation marks (why?)
                        isFinished = true;
                        for (int i = tstr.find('"'); i < tstr.size() - 1; i++) {
                            tstr.at(i) = tstr.at(i+1);
                        }
                        tstr = tstr.substr(0, tstr.size() - 1);
                    }
                    while (!isFinished) { //keep parsing until quotation mark closers are met
                                          //remove closing quotation marks
                        string tstr2;
                        if (ss >> tstr2) {
                            int i;
                            for (i = 0; i < tstr2.size(); ++i) { //search for quotation marks
                                if(tstr2.at(i) == '"') {
                                    isFinished = true;
                                    break;
                                }
                            }
                            if (isFinished) { //if quotation marks are found remove them
                                for ( ; i < tstr2.size() - 1; ++i) {
                                    tstr2.at(i) = tstr2.at(i + 1);
                                }
                                tstr2 = tstr2.substr(0, tstr2.size() - 1);
                            }
                            if (tstr.at(tstr.size() - 1) != '\n') {
                                 tstr += " ";    
                            }
                            tstr += tstr2;
                        }
                        else {  //deal with multi-line quotations
                            string tempstr;
                            cout << "> ";
                            tstr += '\n';
                            getline(cin, tempstr);
                            ss.str(tempstr);
                            ss.clear();
                        }
                    }
                } //end quotation marks
                else {
                    bool isComment = false; // deal with comments
                    for (int i = 0; i < tstr.size(); ++i) {
                        if(tstr.at(i) == '#') {
                            tstr = tstr.substr(0, i);
                            isComment = true;
                        }
                    }
                    if (isComment) break;
                }
                
                if(tstr.at(tstr.size() - 1) == ';') {
                    conType = next; //semicolon
                    v.push_back(tstr.substr(0, tstr.size() - 1));
                    break;
                }
                else if(strcmp(tstr.c_str(), "||") == 0) {
                    conType = failure; 
                    break;
                }
                else if(strcmp(tstr.c_str(), "&&") == 0) {
                    conType = success;
                    break;
                }
                
                
                v.push_back(tstr); //push_back arguments
                
            }
            char** args = new char*[v.size() + 1];
            //dynamically allocate mem for arguments
            for (int i = 0; i < v.size(); ++i) {
                args[i] = new char[v.at(i).size() + 1];
                strcpy(args[i], v.at(i).c_str());
            }
            args[v.size()] = 0;
            
            BaseCmd* tempCmd = (parenCmd == 0) ? new Cmd(args) : parenCmd; //create new command with arguments
            
            if(head == 0) { //no connector
                head = tempCmd;
            }
            else {
                head->addRight((tempCmd)); //place new command in tree if not first command
            }
            if(conType == -1) { //base case return if there's no next connector
                return head;
            }
            else { //recursively construct commands from the rest of the line
                BaseCmd* newCon = new Connector((ConType)conType);
                newCon->addLeft(head);
                head = newCon;
                return compose(ss, head);
            }
        };
};

#endif
