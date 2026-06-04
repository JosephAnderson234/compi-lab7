#ifndef VISITOR_H
#define VISITOR_H
#include "ast.h"
#include <list>
#include <unordered_map>
#include "environment.h"


class BinaryExp;
class NumberExp;
class Program;
class PrintStm;
class AssignStm;
class FunDec;
class ReturnStm;
class Body;
class VarDec;
class FcallExp;
class BoolExp;

class Visitor {
public:
    virtual int visit(BinaryExp* exp) = 0;
    virtual int visit(NumberExp* exp) = 0;
    virtual int visit(BoolExp* exp) = 0;
    virtual int visit(IdExp* exp) = 0;
    virtual int visit(Program* p) = 0;
    virtual int visit(PrintStm* stm) = 0;
    virtual int visit(AssignStm* stm) = 0;

    virtual int visit(ReturnStm* stm) = 0;
    virtual int visit(VarDec* vd) = 0;
    virtual int visit(Body* b) = 0;
    virtual int visit(FunDec* fd) = 0;
    virtual int visit(FcallExp* stm) = 0;

};



class PrintVisitor : public Visitor {
public:

    int visit(BinaryExp* exp) override;
    int visit(NumberExp* exp) override;
    int visit(BoolExp* exp) override;
    int visit(IdExp* exp) override;
    int visit(Program* p) override ;
    int visit(PrintStm* stm) override;
    int visit(AssignStm* stm) override;
    int visit(ReturnStm* stm) override;
    int visit(VarDec* vd) override;
    int visit(Body* b) override;
    int visit(FunDec* fd) override;
    int visit(FcallExp* stm) override;

    void imprimir(Program* program); 
};

class EVALVisitor : public Visitor {
public:
    Environment<int> env;
    unordered_map<string, FunDec*> envfun;
    int retval;
    bool retcall;
    int visit(BinaryExp* exp) override;
    int visit(NumberExp* exp) override;
    int visit(BoolExp* exp) override;
    int visit(Program* p) override ;
    int visit(IdExp* exp) override;
    int visit(PrintStm* stm) override;
    int visit(AssignStm* stm) override;
    int visit(ReturnStm* stm) override;
    int visit(VarDec* vd) override;
    int visit(Body* b) override;
    int visit(FunDec* fd) override;
    int visit(FcallExp* stm) override;
    void interprete(Program* program);
};



#endif // VISITOR_H