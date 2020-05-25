#include "codegen.h"
string Gen::filename = "3addcode.txt";
int Gen::label_num = 1;
int Gen::temp_num = 1;
string tab = "\t";

void Gen::write2File(string content){
    fstream f;
    f.open(filename, ios::out);
    f << content << endl;
}

string genFuncName(string func_name){
    return func_name + ":\n"; 
}

string genCall(string func_name, int argc){
    return tab + "call " + func_name + ", " + to_string(argc) + '\n';
}

string genAssignOperation(string lval, string rval){
    return tab + lval + " := " + rval + '\n';
}

string genRetCode(Expression* E){
    string code = "";
    code += E->code;
    code += tab + "return " + E->place + "\n\n";
    return code;
}
string genParam(string id_name){
    return tab + "param " + id_name + '\n';
}

string genLabel(string label){
    return label + ":\n";
}

string genIfGotoOperation(string exp, string label){
    return tab + "if" + ' ' + exp + ' ' + "goto " + label + '\n'; 
}

string genGotoOperation(string label){
    return tab + "goto " + label + '\n';
}
string genBinaryOperation(string lval, string op, string rval){
    return lval + ' ' + op + ' ' + rval;
}

string Gen::newtemp(){
    return "t" + to_string(temp_num++);
}

string Gen::newlabel(){
    return "L" + to_string(label_num++);
}

string Gen::genCode(vector<Statement*>* gloabal_decl_list){
    string code = "";
    for(Statement* global_decl : *gloabal_decl_list){
        code += global_decl->code;
    }
    write2File(code);
    return code;
}
string genArg(vector<Expression*>* arg_list){
    string code = "";
    for(Expression* arg : *arg_list){
        code += tab + "param " + ((Identifier*)arg)->name + '\n';
    }
    return code;
    
}
void Gen::genFunctionInvoke(Expression*& E, Identifier* id, vector<Expression*>* arg_list){
    string code = "";
    /* Searching function:id from symbol table
       if function:id has return value , genreate
       a temp value and assign the function to it */
    /* not implement (2020.5.24) */
    code += genArg(arg_list);
    code += genCall(id->name, arg_list->size());
    E->code = code;
}

void Gen::genBinary(Expression*& E, Expression* E1, Expression* E2, string op){
    string place = "";
    string code = "";
    
    /* E->place = newtemp(); 
        E->code = E1->code || E2->code || "E.place := E1.place + E2.place"
    */
    place = newtemp();
    if(E1->code != "")
        code += E1->code;
    if(E2->code != "")
        code += E2->code;

    string binop = genBinaryOperation(E1->place, op, E2->place);
    code += genAssignOperation(place, binop);

    E->place = place;
    E->code = code;
}

void Gen::genRelop(Expression*& E, Expression* E1, Expression* E2, string op){
    /*
        E.place = newtemp();
        newlabel1 = newlabel();
        newlabel2 = newlabel()
        E.code = if E1.place relop E2.place goto newlabel1
        goto newlabel2
        label1:
        E.place = 1
        label2:
        E.place = 0
    */
    /*string code = "";
    string place = "";
    place = newtemp();
    string L1 = newlabel();
    string L2 = newlabel();
    if(E1->code != "" && E2->code != "")
        code += "if " + E1->place + op + E2->place + " goto " + L1 + "\n";
    code += "goto " + L2 + "\n";
    code += L1 + "\n";
    code += place + ":=1\n";
    code += L2 + ":\n" + place + ":=0\n";
    E->code = code;
    E->place = place;*/
}

void Gen::genRetStmt(Statement*& S, Expression* E){
    string code = "";
    code = genRetCode(E);
    S->code = code;
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

void Gen::genReal10(Expression*& E, Real10* num){
    /* E->place = num.val */
    E->place = to_string(num->val);
    E->code = "";
}

void Gen::genIfStmt(Statement*& S, Expression* E, Statement* S1, Statement* S2){
    string code = "";
    string place = "";
    /* Code of E(relop expression) */
    string op = E->type;
    string l_code = E->left->code;
    string r_code = E->right->code;
    string l_place = E->left->place;
    string r_place = E->right->place;
    string label_1 = newlabel();
    string label_2 = newlabel();
    string bin = genBinaryOperation(l_place, op, r_place);
    code = l_code + r_code;
    code += genIfGotoOperation(bin, label_1);
    code += genGotoOperation(label_2);
    code += genLabel(label_1);

    /* Code of S1(true statement) */
    code += S1->code;
    if(!S2){
        code += genLabel(label_2);
    }
    else{
        /* label_3 is S->next */
        string label_3 = newlabel();
        S->next = label_3;
        code += genGotoOperation(S->next);
        code += genLabel(label_2);
        code += S2->code;
        code += genLabel(S->next);
    }
    S->code = code;

}
void Gen::genFunction(Statement*& F, Identifier* id, Statement* block){
    string code = "";
    code = genFuncName(id->name);
    code += block->code;
    F->code = code;
}


/* Assign node is root (need to write S->code to file) */
void Gen::genAssign(Assign*& S, Identifier* id, Expression* E){
    string place = "";
    string code = "";
    
    /* S->code = E->code || "id->place := E->place" */
    code += E->code;
    code += genAssignOperation(id->place, E->place);
    S->code = code;
    
}

void Gen::genWhileStmt(Statement*& S, Expression* E, Statement* S1){
    string code = "";
    string begin_label = newlabel();
    code += genLabel(begin_label);
    /* Code of E(relop Expression) */
    string op = E->type;
    string l_code = E->left->code;
    string r_code = E->right->code;
    string l_place = E->left->place;
    string r_place = E->right->place;
    E->True = newlabel();
    //E->False = newlabel();
    code += l_code + r_code;
    //cout << r_place << endl;
    string bin = genBinaryOperation(l_place, op, r_place);
    code += genIfGotoOperation(bin, E->True);
    code += genGotoOperation(begin_label);
    code += genLabel(E->True);

    /* Code of S1 */
    code += S1->code;
    code += genGotoOperation(begin_label);
    //code += genLabel(E->False);
    S->code = code;
}


