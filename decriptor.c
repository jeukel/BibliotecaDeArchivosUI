#include <stdio.h>
#include "decriptor.h"

static char* commandLine;

char* NextWord() {
    string bhla = EMPTY_STRING;
    int cut = this->line.find(' ');
    bhla = this->line.substr(ZE_ROW, cut);
    this->line =  this->line.substr(cut + ONE_BYTE, this->line.length());
    return bhla;
}
char* charToStr(char* pChar){
    string toReturn = EMPTY_STRING;
    toReturn.assign(pChar , sizeof(pChar));
    return toReturn;
}

array<char*> arrayCharToSL(SimpleList<char*> toConvert){
    array<char*> toReturn (toConvert.getLenght());
    int i = ZE_ROW;
    while(toConvert.getLenght() != ZE_ROW){
        toReturn[i] = *toConvert.getHead()->getElement();
        toConvert.deleteHead();
        i++;
    }
    return toReturn;
}
array<int> arrayCharToSL(SimpleList<int> toConvert){
    array<int> toReturn (toConvert.getLenght());
    int i = ZE_ROW;
    while(toConvert.getLenght() != ZE_ROW){
        toReturn[i] = *toConvert.getHead()->getElement();
        toConvert.deleteHead();
        i++;
    }
    return toReturn;
}

int ColNameToIndex(string pName) {
    string ColName = EMPTY_STRING;
    int Index = MINUS_ONE;
    SimpleList<char*>* temp = &this->cNames;
    for (unsigned int i = ZE_ROW; i < cNames.getLenght(); i++) {
        ColName = *(temp->getHead()->getElement());
        if (ColName.compare(pName)) {
            Index=i;
            break;
        }else{
            temp->deleteHead();
        }
    }
    return Index;
}
int StrToInt (string ToParse) {
    int number  = atoi(ToParse.c_str());
    return number;
}

void getCreationArguments () {
    string col = EMPTY_STRING;
    int split = ZE_ROW;
    int cut = ZE_ROW;
    int saiz = ZE_ROW;

    cut = this->line.find(SPACE_CHAR);
    while (line != EMPTY_STRING) {
        split = this->line.find(COLON);
        col = this->line.substr(ZE_ROW, split);
        saiz = StrToInt(this->line.substr(split+ONE_BYTE, cut-(split-ONE_BYTE))); //~ substr is not reliable
        this->line = this->line.substr(cut+ONE_BYTE, this->line.length());

        RegSaiz += saiz;
        cNames.append(const_cast<char*>( col.c_str()));
        cSais.append(saiz);
    }
}
void getValuedArguments () {
    string valiu = EMPTY_STRING;
    string col = EMPTY_STRING;
    int split = ZE_ROW;
    int cut = ZE_ROW;

    cut = this->line.find(SPACE_CHAR);
    while (line != EMPTY_STRING) {
        split = this->line.find(COLON);
        col = this->line.substr(ZE_ROW, split);
        valiu = this->line.substr(split+ONE_BYTE, cut-(split-ONE_BYTE)); //~ substr is not reliable
        this->line = this->line.substr(cut+ONE_BYTE, this->line.length());

        //RegSaiz += saiz;
        cNames.append(const_cast<char*>( col.c_str()));
        cValius.append(const_cast<char*>(valiu.c_str()));
    }
}
void askForValidCommand(){
    string command;
    std::getline(std::cin , command);
    this->line = command;
    decript();
}
void getArguments() {
    string col = EMPTY_STRING;
    int cut = ZE_ROW;

    cut = this->line.find(SPACE_CHAR);
    while (line != FROM) {
        col = this->line.substr(ZE_ROW, cut);
        this->line = this->line.substr(cut+ONE_BYTE, this->line.length());

        cNames.append(const_cast<char*>( col.c_str()));
    }
}
void decript () {

    string fName = EMPTY_STRING;
    string cName = EMPTY_STRING;
    string uName = EMPTY_STRING;

    string firstWord = NextWord();
    if (!this->isServer){
        if (firstWord == CREATE) {
            if (this->root){
                string toCompare = NextWord();
                if (toCompare == TABLE) {
                    fileName = NextWord();
                    getCreationArguments(); //RegSize, cSais, cNames
                    if (NextWord()== USING){
                        if (NextWord()== RAID){
                            int  RAID = this->StrToInt(NextWord());
                            array<char*> aNames = this->arrayCharToSL(this->cNames);
                            array<int> aSais = this->arrayCharToSL(this->cSais);
                            //RM->createNewFile(&RegSaiz ,&aSais, &aNames ,&fileName,
                              //                &RAID , &commandLine);
                            askForValidCommand();
                        }else{
                            cout << INVALID_COMMAND << endl;
                            askForValidCommand();
                        }
                    } else {
                        int RAID = NOT_RAID;
                        array<char*> aNames = this->arrayCharToSL(this->cNames);
                        array<int> aSais = this->arrayCharToSL(this->cSais);
                        //RM->createNewFile(&RegSaiz ,&aSais, &aNames ,&fileName, &RAID,
                          //                &commandLine);
                        askForValidCommand();
                    }
                }else if (toCompare == USER) {
                    uName = NextWord();
                    if (NextWord() == PASSWORD) {
                        FS->createUser(uName, NextWord());
                        askForValidCommand();
                    }else{
                        cout << INVALID_COMMAND << endl;
                        askForValidCommand();
                    }
                }else if (toCompare == INDEX){
                    if (NextWord() == ON){
                        //                fName = NextWord();
                        //                cName = NextWord();
                        cout << NYI << endl;
                        askForValidCommand();
                    }else{
                        cout << INVALID_COMMAND << endl;
                        askForValidCommand();
                    }
                }else{
                    cout << INVALID_COMMAND << endl;
                    askForValidCommand();
                }
            }else{
                cout << INVALID_COMMAND << endl;
                askForValidCommand();
            }

        }else if (firstWord == INSERT) {
            if (NextWord() == INTO){
                fName = NextWord();
                getValuedArguments();
                array<char*> aNames = this->arrayCharToSL(this->cNames);
                array<char*> aValiuz = this->arrayCharToSL(this->cValius);
                FS->writeNewLineToFile(&fName, &aNames, &aValiuz);
                askForValidCommand();
            } else {
                cout << INVALID_COMMAND << endl;
                askForValidCommand();
            }

        } else if (firstWord == SELECT) {
            getArguments();
            if (NextWord() == FROM) {
                fName = NextWord();
                if (this->root || this->currentUser->CanWrite(fName)){
                    const char* firstElement;// = cNames.elementAt(0)->getElement();
                    if (firstElement == ASTERISC) {
                        FS->readFromFile(fileName , EMPTY_STRING, ZE_ROW);
                        askForValidCommand();
                    } else {
                        for (int i = ZE_ROW; i<cNames.getLenght(); i++) {
                            string toPass (const_cast<char*>(*(cNames.elementAt(i)->getElement())));
                            FS->readFromFile(fileName, toPass, i);
                            askForValidCommand();
                        }
                    }
                }else{
                    cout << INVALID_COMMAND << endl;
                    askForValidCommand();
                }
            }else{
                cout << INVALID_COMMAND << endl;
                askForValidCommand();
            }

        }else if (firstWord == UPDATE) {
            fName = NextWord();
            if (this->root || this->currentUser->CanWrite(fName)){
                if (NextWord() == SET) {
                    getValuedArguments();
                    array<char*> arrToPass = this->arrayCharToSL(this->cValius);
                    array<char*> arrColToPass = this->arrayCharToSL(this->cNames);
                    for (int i = ZE_ROW; i <= cNames.getLenght(); i++) {
                        string toPass (const_cast<char*>(arrToPass[i]));
                        string ColToPass (const_cast<char*>(arrToPass[i]));
                        FS->update(toPass, fName, ZE_ROW, ColToPass );
                    }
                    askForValidCommand();
                }else{
                    cout << INVALID_COMMAND << endl;
                    askForValidCommand();
                }
            } else{
                cout << INVALID_COMMAND << endl;
                askForValidCommand();
            }
        }else if (firstWord == DELETE) {
            if (NextWord() == FROM) {
                fName = NextWord();
                if (this->root || this->currentUser->CanWrite(fName)){
                    cName = NextWord();
                    uName = NextWord();
                    FS->deleteData(fName , cName , uName);
                    askForValidCommand();
                }else{
                    cout << INVALID_COMMAND << endl;
                    askForValidCommand();
                }
            }else{
                cout << INVALID_COMMAND << endl;
                askForValidCommand();
            }
        }else if (firstWord == COMPRESS){
            if(this->root){
                if (NextWord() == TABLE){
                    //            fName = NextWord();
                    cout << NYI << endl;
                    askForValidCommand();
                }else{
                    cout << INVALID_COMMAND <<endl;
                    askForValidCommand();
                }
            }else{
                cout << INVALID_COMMAND <<endl;
                askForValidCommand();
            }
        }else if (firstWord == BACKUP){
            if (this->root){
                if (NextWord() == TABLE){
                    fName = NextWord();
                    FS->backUpFile(NextWord());
                    askForValidCommand();
                }else{
                    cout << INVALID_COMMAND <<endl;
                    askForValidCommand();
                }
            }else{
                cout << INVALID_COMMAND << endl;
                askForValidCommand();
            }
        }else if (firstWord == RESTORE){
            if (this->root){
                if (NextWord() == TABLE){
                    fName = NextWord();
                    FS->restoreFile(fName);
                    askForValidCommand();
                }else{
                    cout << INVALID_COMMAND <<endl;
                    askForValidCommand();
                }
            }else{
                cout << INVALID_COMMAND << endl;
                askForValidCommand();
            }

        }else if (firstWord == DROP){
            if ( this->root){
                if (NextWord() == USER) {
                    uName = NextWord();
                    FS->dropUser(uName);
                    askForValidCommand();
                }else{
                    cout << INVALID_COMMAND <<endl;
                    askForValidCommand();
                }
            }else{
                cout << INVALID_COMMAND << endl;
                askForValidCommand();
            }
        }else if (firstWord == GRANT){
            if ( this->root){
                string permit = NextWord();
                //cout << permit <<endl;
                if (NextWord() == ON) {
                    fName = NextWord();
                    if (NextWord() == TO) {
                        uName = NextWord();
                        FS->grantPermission(uName, permit, fName);
//                        askForValidCommand();
                    }else{
                        cout << INVALID_COMMAND << endl;
//                        askForValidCommand();
                    }
                }else{
                    cout << INVALID_COMMAND <<endl;
//                    askForValidCommand();
                }
            }else{
                cout << INVALID_COMMAND << endl;
//                askForValidCommand();
            }
        }else if (firstWord == REVOKE){
            if ( this->root){
                string permit = NextWord();
                if (NextWord() == ON) {
                    fName = NextWord();
                    if (NextWord() == TO) {
                        uName = NextWord();
                        FS->revokePermission(uName, permit, fName);
                        askForValidCommand();
                    }else{
                        cout << INVALID_COMMAND << endl;
                        askForValidCommand();
                    }
                }else{
                    cout << INVALID_COMMAND << endl;
                    askForValidCommand();
                }
            }else{
                cout << INVALID_COMMAND << endl;
                askForValidCommand();
            }
        }else{
            if (firstWord !=  EXIT){
                cout << INVALID_COMMAND << endl;
                askForValidCommand();
            }
        }
    } else {
        if (firstWord == CREATE) {
            string toCompare = NextWord();
            if (toCompare == TABLE) {
                fileName = NextWord();
                getCreationArguments(); //RegSize, cSais, cNames
                if (NextWord()== USING){
                    if (NextWord()== RAID){
                        int  RAID = this->StrToInt(NextWord());
                        array<char*> aNames = this->arrayCharToSL(this->cNames);
                        array<int> aSais = this->arrayCharToSL(this->cSais);
                        //RM->createNewFile(&RegSaiz ,&aSais, &aNames ,&fileName,
                          //                &RAID , &commandLine);
                    }else{
                        cout << INVALID_COMMAND << endl;
                    }
                } else {
                    int RAID = NOT_RAID;
                    array<char*> aNames = this->arrayCharToSL(this->cNames);
                    array<int> aSais = this->arrayCharToSL(this->cSais);
                    //RM->createNewFile(&RegSaiz ,&aSais, &aNames ,&fileName, &RAID,
                      //                &commandLine);
                }
            }else if (toCompare == USER) {
                uName = NextWord();
                if (NextWord() == PASSWORD) {
                    FS->createUser(uName, NextWord());
                }else{
                    cout << INVALID_COMMAND << endl;
                }
            }else if (toCompare == INDEX){
                if (NextWord() == ON){
                    //                fName = NextWord();
                    //                cName = NextWord();
                    cout << NYI << endl;
                }else{
                    cout << INVALID_COMMAND << endl;
                }
            }else{
                cout << INVALID_COMMAND << endl;
            }
        }else if (firstWord == INSERT) {
            if (NextWord() == INTO){
                fName = NextWord();
                //            FS->writeNewLineToFile(&fName, &cData, &cPos);
            }else{
                cout << INVALID_COMMAND << endl;
            }
        }else if (firstWord == SELECT) {
            cName = NextWord();
            if (NextWord()== FROM) {
                fName = NextWord();
                if (cName == ASTERISC) {
                    //filesystem->readFromFile(&NextWord(), &cNames());
                } else {
                    //filesystem->readFromFile(&fileName , &ColNameToIndex(cName), &ONE_BYTE);
                }
            }else{
                cout << INVALID_COMMAND << endl;
            }
        }else if (firstWord == UPDATE) {
            fName = NextWord();
            if (NextWord() == SET) {
                cName = NextWord();
                if (NextWord() == TO) {
                    getCreationArguments();
                    //filesystem->update("&Daniel", &fName, ONE_BYTE , ONE_BYTE);
                }else{
                    cout << INVALID_COMMAND << endl;
                }
            } else{
                cout << INVALID_COMMAND << endl;
            }
        }else if (firstWord == DELETE) {
            if (NextWord() == FROM) {
                fName = NextWord();
                cName = NextWord();
                uName = NextWord();
                FS->deleteData(fName , cName , uName);
            }else{
                cout << INVALID_COMMAND << endl;
            }
        }else if (firstWord == COMPRESS){
            if (NextWord() == TABLE){
                //            fName = NextWord();
                cout << NYI << endl;
            }else{
                cout << INVALID_COMMAND <<endl;
            }
        }else if (firstWord == BACKUP){
            if (NextWord() == TABLE){
                fName = NextWord();
                FS->backUpFile(NextWord());
            }else{
                cout << INVALID_COMMAND <<endl;
            }
        }else if (firstWord == RESTORE){
            if (NextWord() == TABLE){
                fName = NextWord();
                FS->restoreFile(NextWord());
            }else{
                cout << INVALID_COMMAND <<endl;
            }

        }else if (firstWord == DROP){
            if (NextWord() == USER) {
                uName = NextWord();
                FS->dropUser(uName);
            }else{
                cout << INVALID_COMMAND <<endl;
            }
        }else if (firstWord == GRANT){
            string permit = NextWord();
            if (NextWord() == ON) {
                fName = NextWord();
                if (NextWord() == TO) {
                    uName = NextWord();
                    FS->grantPermission(uName, permit, fName);
                }else{
                    cout << INVALID_COMMAND << endl;
                }
            }else{
                cout << INVALID_COMMAND <<endl;
            }
        }else if (firstWord == REVOKE){
            string permit = NextWord();
            if (NextWord() == ON) {
                fName = NextWord();
                if (NextWord() == TO) {
                    uName = NextWord();
                    FS->revokePermission(uName, permit, fName);
                }else{
                    cout << INVALID_COMMAND << endl;
                }
            }else{
                cout << INVALID_COMMAND << endl;
            }
        }else{
            cout << INVALID_COMMAND << endl;
        }
    }
}

