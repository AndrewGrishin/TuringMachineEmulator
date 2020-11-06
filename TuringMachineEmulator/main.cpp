//
//  main.cpp
//  TuringMachineEmulator
//
//  Created on 2020.04.16
//  Copyright © 2020. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ^ - nothing to write
// _ - write space

class TuringMachine
{
private:
    string alphabet;
    vector<string> statuses;
    struct operation{
        char written;
        char directionToGo;
        string statusToGo;
    };
    vector<vector<operation>> arrayCommands;
    
    void inputStatuses(){
        string status;
        getline(cin, status);
        // vector for strings of commands (not separated
        // buffer string to save each command in line
        string k("");
        // process of splitting and filling in the f vector
        for (int i = 0; i < status.size() + 1; i++){
            if (i == status.size()) { statuses.push_back(k); break; }
            
            if (status[i] != ' '){
                k += status[i];
            } else {
                statuses.push_back(k);
                k = "";
            }
        }
    }
    
    operation splitOnCommands2(string na){
        // "what to write","next status","where to go next", example: 4,q4,R
        operation a;
        a.written = na[0];
        a.directionToGo = na[2];
        for (int i = 4; i < na.size(); i++){
            a.statusToGo += na[i];
        }
        return a;
    }
    
    vector<operation> splitOnCommands(string na){
        // vector for strings of commands (not separated
        vector<string>f;
        // buffer string to save each command in line
        string k("");
        // process of splitting and filling in the f vector
        for (int i = 0; i < na.size() + 1; i++){
            if (i == na.size()) f.push_back(k);
            
            if (na[i] != ' '){
                k += na[i];
            } else {
                f.push_back(k);
                k = "";
            }
        }
        // creat vector to save splitted commands
        vector<operation>s;
        // filling in vector s with help of splitOnCommands2 (split each "word" on part and return type operation, completed command piece)
        for (int i = 0; i < f.size(); i++){
            s.push_back(splitOnCommands2(f[i]));
        }
        // return vector of commands (type - operation)
        return s;
    }
    
    int searchMatchAlphabet(char element){
        for (int i = 0; i < alphabet.size(); i++){
            if (element == alphabet[i]){
                return i;
            }
        }
        return -1;
    }
    
    int searchMatchStatus(string element){
        for (int i = 0; i < statuses.size(); i++){
            if (element == statuses[i]){
                return i;
            }
        }
        return -1;
    }
    
public:
    TuringMachine(){
        // input available alphabet of Machine
        cout << "Alphabet." << endl;
        cout << "Answer: "; getline(cin, alphabet);
        // input available alphabet of Machine
        cout << endl;
        cout << "Status. ((!) chronological order (!))" << endl;
        cout << "Answer: "; inputStatuses();
        // input instructions
        cout << endl << "Instructions (\"0\" to stop)" << endl;
        while (true){
            // string for saving instructions
            string na("");
            getline(cin, na);
            // checking if it is time to break the cycle
            if (na == "0") break;
            // filling vector with vectors of operation type variables (filling in Turing's matrix)
            arrayCommands.push_back(splitOnCommands(na));
        }
    }
    
    void play(){
        cout << endl;
        cout << "Initial word." << endl;
        cout << "Answer: "; string answer(""); cin >> answer;
        char input[answer.size() + 1000]; for (int i = 0; i < answer.size() + 1000; i++) input[i] = '_';
        for (unsigned long i = (answer.size() + 1000) / 2; i < ((answer.size() + 1000) / 2) + answer.size(); i++)
            input[i] = answer[i - (answer.size() + 1000) / 2];
        //-----------------------------//
        int stringIndex(0), colomnIndex(0); unsigned long pointerInWord((answer.size() + 1000) / 2);
        while (true){
            // search colomn
            colomnIndex = searchMatchAlphabet(input[pointerInWord]);
            // write character
            switch (arrayCommands[stringIndex][colomnIndex].written) {
                case '^':
                    // do not write anything
                    break;
                case '_':
                default:
                    input[pointerInWord] = arrayCommands[stringIndex][colomnIndex].written;
                    break;
            }
            // change direction of header
            switch (arrayCommands[stringIndex][colomnIndex].directionToGo) {
                case 'L':
                    pointerInWord--;
                    break;
                case 'R':
                    pointerInWord++;
                default:
                    break;
            }
            // update string index (change status) and checking if it is time to stop
            if (arrayCommands[stringIndex][colomnIndex].statusToGo == "!") {
                break;
            } else {
                // search for next status to go to
                stringIndex = searchMatchStatus(arrayCommands[stringIndex][colomnIndex].statusToGo);
            }
        }
        //-----------------------------//
        cout << "Result: ";
        for (int i = 0; i < sizeof(input) / sizeof(input[i]); i++){
            if (input[i] != '_' && !(input[i-1] != '_' && input[i] == '_' && input[i+1] != '_')){
                if (input[i] != '_' && input[i+1] == '_' && input[i-1] == '_' && input[i-2] != '_')
                    cout << " " << input[i];
                else
                    cout << input[i];
            }
        }
        cout << endl;
    }
    
    void printCommands(){
        cout << endl;
        for (int i = 0; i < arrayCommands.size(); i++){
            for (int j = 0; j < arrayCommands[i].size(); j++){
                cout << arrayCommands[i][j].written << "," << arrayCommands[i][j].directionToGo << "," << arrayCommands[i][j].statusToGo << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    TuringMachine a = TuringMachine();
    a.play();
    return 0;
}

/* Devision by 2
0,R,q0 0,R,q1 1,R,q0 1,R,q1 2,R,q0 2,R,q1 3,R,q0 3,R,q1 4,R,q0 4,R,q1 ^,R,q2
5,R,q0 5,R,q1 6,R,q0 6,R,q1 7,R,q0 7,R,q1 8,R,q0 8,R,q1 9,R,q0 9,R,q1 ^,R,q3
X,X,XX X,X,XX X,X,XX X,X,XX X,X,XX X,X,XX X,X,XX X,X,XX X,X,XX X,X,XX 0,N,q4
X,X,XX X,X,XX X,X,XX X,X,XX X,X,XX X,X,XX X,X,XX X,X,XX X,X,XX X,X,XX 1,N,q4
^,L,q4 ^,L,q4 ^,L,q4 ^,L,q4 ^,L,q4 ^,L,q4 ^,L,q4 ^,L,q4 ^,L,q4 ^,L,q4 ^,L,q5
^,L,q5 ^,L,q5 ^,L,q5 ^,L,q5 ^,L,q5 ^,L,q5 ^,L,q5 ^,L,q5 ^,L,q5 ^,L,q5 ^,R,!
0
*/
/* Multiplying by 2
0,R,X 1,R,X 2,R,X 3,R,X 4,R,X 5,R,X 6,R,X 7,R,X 8,R,X 9,R,X ^,L,Y
0,L,Y 2,L,Y 4,L,Y 6,L,Y 8,L,Y 0,L,Z 2,L,Z 4,L,Z 6,L,Z 8,L,Z ^,R,!
1,L,Y 3,L,Y 5,L,Y 7,L,Y 9,L,Y 1,L,Z 3,L,Z 5,L,Z 7,L,Z 9,L,Z 1,R,!
0
*/
/* Reverse
^,R,q0 ^,R,q0 X,X,XX X,X,XX %,L,q1
^,L,q1 ^,L,q1 X,X,XX X,X,XX =,R,q2
_,N,q3 _,N,q6 X,X,XX _,L,q8 ^,R,q2
X,X,XX X,X,XX ^,L,q4 X,X,XX ^,L,q3
^,L,q4 ^,L,q4 X,X,XX X,X,XX a,R,q5
^,R,q5 ^,R,q5 ^,R,q2 X,X,XX X,X,XX
X,X,XX X,X,XX ^,L,q7 X,X,XX ^,L,q6
^,L,q7 ^,L,q7 X,X,XX X,X,XX b,R,q5
X,X,XX X,X,XX _,L,q9 X,X,XX ^,L,q8
^,L,q9 ^,L,q9 X,X,XX X,X,XX ^,R,!
0
*/
