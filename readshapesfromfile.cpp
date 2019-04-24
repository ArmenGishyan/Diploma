#include "readshapesfromfile.h"
#include <assert.h>
#include <fstream>

 ReadWriteFile::ReadWriteFile(const std::string& fileName, std::ios_base::openmode mode)
{
    m_file.open(fileName);
    if(!m_file.is_open()) {
        assert(false);
    }

}

std::vector<std::string> ReadWriteFile::getLinesFromFile()
{
    std::vector<std::string> vecOfLines;
    if(m_file.is_open()) {
        std::string str;
        while (!m_file.eof()) {
            std::getline(m_file, str);
            vecOfLines.push_back(str);
            str.clear();
        }
    }
    return vecOfLines;
}
