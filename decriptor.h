#ifndef DECRIPTOR_H
#define DECRIPTOR_H

decriptor(string pline, user* pCurrentuser, bool pRoot, bool pServer );

char* line;
char* fileName;
SimpleList<char*> pNames;
SimpleList<char*> cNames;
SimpleList<char*> cValius;
SimpleList<int> cSais;
int RegSaiz;

char *NextWord();
char* charToStr(char* pChar);

array<char*> arrayCharToSL(SimpleList<char*> toConvert);
array<int> arrayCharToSL(SimpleList<int> toConvert);

int ColNameToIndex(string pName);
int StrToInt (string ToParse);

void getCreationArguments ();
void getValuedArguments ();
void askForValidCommand();
void getArguments();
void decript ();


#endif // DECRIPTOR_H
