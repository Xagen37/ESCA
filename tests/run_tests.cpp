#include <iostream>
#include <filesystem>
#include "AST/ASTWalker.h"
#include "target/AnalyzeProcess.h"

const std::vector<std::string> INCLUDE_PATHS = {
        "/usr/include/",
        "/usr/include/c++/9/",
        "/usr/include/x86_64-linux-gnu/",
        "/usr/include/x86_64-linux-gnu/c++/9/",
        "/usr/lib/gcc/x86_64-linux-gnu/9/include/",
//        "/usr/lib/llvm-10/include/",
};


int main()
{
    const std::string RESOURCE_PATH = std::filesystem::current_path().string() + "/examples/";
    std::vector<std::string> files = {
            "test2.cpp",
    };
    std::cout << RESOURCE_PATH << std::endl;

//    freopen("analyze.info", "w", stdout);

    ASTWalker walker(INCLUDE_PATHS);
    CommonStorage::Instance().SetIncludeDirs(INCLUDE_PATHS);
//    walker.SetIncludeDirectories(INCLUDE_PATHS);
    for( const auto &file: files )
    {
        if( !walker.WalkAST(RESOURCE_PATH + file))
        {
            std::cerr << "Failed to walk for file: " << file << std::endl;
        }
        std::cout << "Finish walk file: " << file << std::endl;
    }

    AnalyzeProcess a;
    a.StartAnalyze();

    std::cout << "Working time: " << clock() / CLOCKS_PER_SEC << " sec" << std::endl;
    return 0;
}