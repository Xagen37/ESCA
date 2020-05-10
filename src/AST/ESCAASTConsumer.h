#ifndef ESCAASTConsumer_h
#define ESCAASTConsumer_h

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/DeclGroup.h>

#include "ESCAASTVisitor.h"
#include "../utils/common.h"

class ESCAASTConsumer : public clang::ASTConsumer
{
public:
    /// @brief Переопределяемая функция для прохода по AST дереву нашим AST visitor
    bool HandleTopLevelDecl( clang::DeclGroupRef DR ) override
    {
        std::string loc;
        for( auto it : DR )
        {
            loc = it->getLocation().printToString(it->getASTContext().getSourceManager());
            if( loc.find(Options::Instance().analyzeFile) == std::string::npos )
            {
                return true;
            }
//            it->dump();
            visitor.TraverseDecl(it);

//            it->getLocation().printToString()
//            it->dump();
            // Traverse the declaration using our AST visitor.
        }

//        std::cout << "heeerrrree" << std::endl;
        return true;
    }

private:
    ESCAASTVisitor visitor;
};

#endif
