#ifndef STATEFSM_H
#define STATEFSM_H

#include <vector>
#include <deque>
#include <memory>

#include "TypesFSM.h"
#include "../SMT/FormulaSMT.h"

typedef std::vector<VersionedVariable> VarStorage;
typedef std::deque<std::shared_ptr<FormulaSMT> > FormulaStorage;
typedef std::string ConditionEvent;

std::string FormulaeToString( const FormulaStorage &formulae );

std::string FormulaeToStringSat( const FormulaStorage &formulae );

/// @brief Одно из состояний автомата (одна операция)
struct StateFSM
{
    FSMID id = -1;

    /// @brief Входящие ребра, по которым можно прийти в это состояние
    std::vector<FSMID> incoming;

    /// @brief Исходящие ребра, по которым можно пройти из этого состояния
    std::vector<FSMID> outgoing;

    VarStorage allocPointers;
    VarStorage allocArrays;
    VarStorage delPointers;
    VarStorage delArrays;
    VarStorage nullPtrs;
    VarStorage notNullPtrs;

    /// Хранилище формул, которые в дальнейшем будут переданы в smt решатель
    FormulaStorage formulae;

    bool isEnd = false;
    bool isBranchLeaf = false; //Former leaf in which there is

    inline bool IsLeaf() const
    {
        return (!isEnd) && outgoing.empty();
    }
};

bool operator==( const StateFSM &lhs, const StateFSM &rhs );

bool operator<( const StateFSM &lhs, const StateFSM &rhs );

//typedef shared_ptr<StateFSM> StateFSMPtr;

#endif
