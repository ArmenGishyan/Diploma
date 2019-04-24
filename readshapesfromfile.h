#ifndef READSHAPESFROMFILE_H
#define READSHAPESFROMFILE_H

#include <string>
#include <fstream>
#include <vector>
#include <string>

class ReadWriteFile
{
public:
    ReadWriteFile(const std::string& fileName, std::ios_base::openmode mode);
    std::vector<std::string> getLinesFromFile();
    void appendInFile(const std::string& file);

private:
    std::ifstream m_file;
};

#endif // READSHAPESFROMFILE_H
