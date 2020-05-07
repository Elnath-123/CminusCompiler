#include "codegen.h"
string Gen::filename = "3addcode.txt";
int Gen::label = 1;

string Gen::newtemp(){
        return "t" + to_string(label++);
    }

void Gen::write2File(string content){
    fstream f;
    f.open(filename, ios::app | ios::out);
    f << content << endl;
}

void Gen::genBinary(Expression*& E, Expression* E1, Expression* E2, string op){
    string place = "";
    string code = "";
    
    /* E->place = newtemp(); 
        E->code = E1->code || E2->code || "E.place := E1.place + E2.place"
    */
    place = newtemp();
    if(E1->code != "")
        code += E1->code + '\n';
    if(E2->code != "")
        code += E2->code + '\n';
    code += place + ":=" + E1->place + op + E2->place;
    E->place = place;
    E->code = code;
}

void Gen::genParenthesis(Expression*& E, Expression*& E1){
    /* E->place = E1.place 
       E->code = E1->code
    */
    E->place = E1->place;
    E->code = E1->code;
}

/* var: Id, thus "var" is a identifier, the first param is Id for "var" */
void Gen::genId(Identifier*& var, Identifier* Id){
    /* var->place = Id->place */
    Id->place = Id->name;
    var->place = Id->place;
    var->code = "";
}

void Gen::genInt10(Expression*& E, Int10* num){
    /* E->place = num.val */
    E->place = to_string(num->val);
    E->code = "";
}

/* Assign node is root (need to write S->code to file) */
void Gen::genAssign(Assign*& S, Identifier* id, Expression* E){
    string place = "";
    string code = "";
    
    /* S->code = E->code || "id->place := E->place" */
    code += E->code + '\n';
    code += id->place + ":=" + E->place;
    S->code = code;
    write2File(code);
}
