/// @file common.h
///
/// @brief Файл в котором храняться общие данные для всего проекта
///
/// @author alexust27
/// Contact: ustinov1998s@gmail.com
///
#ifndef ESCA_COMMON_H
#define ESCA_COMMON_H

#include <set>
#include <string>
#include <vector>

class CommonStorage
{
public:

    CommonStorage( CommonStorage const & ) = delete;

    CommonStorage &operator=( CommonStorage const & ) = delete;

    static CommonStorage &Instance()
    {
        static CommonStorage instance;
        return instance;
    }

    /// @brief Флаг быстроты анализа
    bool needFast;

    /// @brief Файл, который сейчас анализируется
    std::string analyzeFile;

    /// @brief Метод устанавливает пути (которые следиет исключить из анализа AST дерева)
    /// @param inclPaths - пути до директорий где хранятся библиотеки (#include<some_lib>)
    void SetIncludeDirs( const std::vector<std::string> &inclPaths );

    /// @brief Метод проверяет находится ли файл в include директориях
    /// @param file - путь до файла который нужно проверить
    /// @return true - если файл внутри директории, false иначе
    bool InIncludeDirs( const std::string &file );

    /// @brief Метод добавляет файл к уже проанализированным файлам
    /// @param file - имя файла
    /// @return false - если такой файл уже был добавлен, true - операция прошла успешно
    bool AddAnalyzeFile( const std::string &file );

    /// @brief Метод проверяет проанализирован ли файл
    /// @param file - файла, который нужно проверить
    /// @return true - если файл уже проанализирован, false - иначе
    bool IsAlreadyAnalyzed( const std::string &file );

private:

    /// @brief Пути до include директорий
    std::vector<std::string> includeDirs;

    /// @brief Проанализированные файлы
    std::set<std::string> analyzedFiles;

    /// @brief Конструктор
    CommonStorage()
    {
        needFast = false;
    };

};


#endif //ESCA_COMMON_H
