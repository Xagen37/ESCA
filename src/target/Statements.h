/// @file Statements.h
///
/// @brief Класс всех состояний анализируемого кода
///
/// @author alexust27
/// Contact: ustinov1998s@gmail.com
///
#pragma once
#include <map>
#include <set>
#include <string>
#include <vector>

#include "llvm/Support/Casting.h"
#include "llvm/Support/ExtensibleRTTI.h"

enum STATEMENTS
{
    COMPOUND,
    VarAssigmentNew,
    VarAssigmentFromFoo,
    VarAssigmentFromPointer,
    DELETE,
    Return,
    IF,
    TRY,
    UNKNOWN,
};

namespace Target
{
/// @brief Общий класс для всех состояний анализируемого кода
class Statement : public llvm::RTTIExtends<Statement, llvm::RTTIRoot>
{
public:
    inline static char ID = 0;
    virtual STATEMENTS GetType()
    {
        return STATEMENTS::UNKNOWN;
    }

    virtual ~Statement() = default;
};
// char Statement::ID = 0;

/// @brief Составное состояние, содержит несколько состояний
class CompoundStatement : public llvm::RTTIExtends<CompoundStatement, Statement>
{
public:
    inline static char ID = 0;;
    CompoundStatement() = default;

    void AddState( Statement *st );

    const std::vector<Statement *> &GetStates() const;

    STATEMENTS GetType() override
    {
        return STATEMENTS::COMPOUND;
    }

    class IsInOptions
    {
    public:
        bool isThen = false;
        bool isElse = false;
        bool isTry = false;
        bool isCatch = false;
        bool isFor = false;
        bool isWhile = false;
    };

    void SetOptions( const CompoundStatement::IsInOptions &otherOptions );

    CompoundStatement::IsInOptions GetOptions() const;

    virtual ~CompoundStatement()
    {
        for( auto s : statements )
        {
            delete s;
        }
    }

private:

    IsInOptions op;
    std::vector<Statement *> statements;
};


class VarAssigmentFromFooStatement : public llvm::RTTIExtends<VarAssigmentFromFooStatement, Statement>
{
public:
    VarAssigmentFromFooStatement( const std::string &varName, const std::string &fooName, const std::string &loc,
                                  bool isDecl );

    STATEMENTS GetType() override
    {
        return STATEMENTS::VarAssigmentFromFoo;
    }

    inline static char ID = 0;;
    bool isDecl;
    std::string varName;
    std::string fooName;
    std::string loc;
};


class VarAssigmentFromPointerStatement : public llvm::RTTIExtends<VarAssigmentFromPointerStatement, Statement>
{
public:
    VarAssigmentFromPointerStatement( const std::string &varName, const std::string &rhsName,
                                      const std::string &loc, bool isDecl );

    STATEMENTS GetType() override
    {
        return STATEMENTS::VarAssigmentFromPointer;
    }

    inline static char ID = 0;;
    std::string varName;
    std::string loc;
    std::string rhsName;
    bool isDecl;
};

/// auto x = new X;
class VarAssigmentNewStatement : public llvm::RTTIExtends<VarAssigmentNewStatement, Statement>
{
public:
    VarAssigmentNewStatement( const std::string &varName, bool isArray, const std::string &loc, bool isDecl );

    STATEMENTS GetType() override
    {
        return STATEMENTS::VarAssigmentNew;
    }

    inline static char ID = 0;;
    std::string varName;
    std::string loc;
    bool isArray;
    bool isDecl;
};


class DeleteStatement : public llvm::RTTIExtends<DeleteStatement, Statement>
{
public:
    DeleteStatement( const std::string &name, bool isArray );

    STATEMENTS GetType() override
    {
        return STATEMENTS::DELETE;
    }

    inline static char ID = 0;;
    std::string name;
    bool isArray;
};


class ReturnStatement : public llvm::RTTIExtends<ReturnStatement, Statement>
{
public:
    explicit ReturnStatement( const std::string &returnVarName );

    STATEMENTS GetType() override
    {
        return STATEMENTS::Return;
    }

    inline static char ID = 0;;
    std::string returnVarName;
};

class IfStatement : public llvm::RTTIExtends<IfStatement, Statement>
{
public:
    IfStatement( Target::CompoundStatement *thenSt, Target::CompoundStatement *elseSt, const std::string &condStr,
                 const std::string &elseStr );

    STATEMENTS GetType() override
    {
        return STATEMENTS::IF;
    }

    virtual ~IfStatement()
    {
        if( elseSt )
            delete elseSt;
        if( thenSt )
            delete thenSt;
    }

    inline static char ID = 0;;
    CompoundStatement *thenSt = nullptr;
    CompoundStatement *elseSt = nullptr;
    std::string condStr;
    std::string elseStr;
};


class TryStatement : public llvm::RTTIExtends<TryStatement, Statement>
{
public:
    TryStatement( CompoundStatement *trySt, CompoundStatement *catchSt ) : trySt(trySt), catchSt(catchSt)
    {
    }

    STATEMENTS GetType() override
    {
        return STATEMENTS::TRY;
    }

    virtual ~TryStatement()
    {
        if( trySt )
            delete trySt;
        if( catchSt )
            delete catchSt;
    }

    inline static char ID = 0;;
    CompoundStatement *trySt = nullptr;
    CompoundStatement *catchSt = nullptr;
};


} // target
