#ifndef CMDCOMPOSER_H
#define CMDCOMPOSER_H
#include "BaseCmd.h"
#include "Cmd.h"
#include "Connector.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

class CmdComposer {
    public:
        CmdComposer() { };
        BaseCmd* compose(istringstream &ss, BaseCmd* head = 0) {
            string tstr;
            vector<string> v;
            int conType = -1; //default no connector
            
            while (ss >> tstr) { //quotation marks
                if (tstr.at(0) == '"') {
                    bool isFinished = false;
                    tstr = tstr.substr(1, tstr.size() - 1);
                    while (!isFinished) {
                        string tstr2;
                        if (ss >> tstr2) {
                            int i;
                            for (i = 0; i < tstr2.size(); ++i) {
                                if(tstr2.at(i) == '"') {
                                    isFinished = true;
                                    break;
                                }
                            }
                            if (isFinished) {
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
                        else {
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
                    bool isComment = false;
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
                
                
                v.push_back(tstr);
                
            }
            char** args = new char*[v.size() + 1];
            //dynamically allocate mem
            for (int i = 0; i < v.size(); ++i) {
                args[i] = new char[v.at(i).size() + 1];
                strcpy(args[i], v.at(i).c_str());
            }
            args[v.size()] = 0;
            
            BaseCmd* tempCmd = new Cmd(args);
            
            if(head == 0) {
                head = tempCmd;
            }
            else {
                head->addRight((tempCmd));
            }
            if(conType == -1) {
                return head;
            }
            else {
                BaseCmd* newCon = new Connector((ConType)conType);
                newCon->addLeft(head);
                head = newCon;
                return compose(ss, head);
            }
        };
};

#endif