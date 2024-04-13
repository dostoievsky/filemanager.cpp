#ifndef filemanager_hpp
#define filemanager_hpp

#include <fstream>
#include <filesystem> 
#include <iterator>
#include <algorithm>

inline void
create(const std::string fileName)
{
    std::fstream file(fileName, std::ios::app | std::ios::binary);
    file.close();
}

inline void 
clearFile(const std::string& fileName)
{
    remove(fileName.c_str());
    std::ofstream recreate (fileName.c_str(), std::ios::app);
    recreate.close();
}

inline void 
checkFile(const std::string& fileName)
{
    if(!std::filesystem::exists(fileName.c_str()))
    {
        perror("ERROR: FILE DOES NOT EXIST");
        EXIT_FAILURE;
    }  
}

template <typename Object, typename Container>
void getFile(const std::string& fileName, Container& objects)
{
    std::ifstream in (fileName.c_str(), std::ios::binary);
    Object tempFile;
    while (in >> tempFile)
    {
        objects.push_back(tempFile);
    }
    in.close();
}

template <typename Object>
void setFile(const Object& object, const std::string& fileName)
{
    checkFile(fileName);
    std::ofstream out (fileName.c_str(), std::ios::app | std::ios::binary);
    out << object;
    out.flush();
    out.close();
}

template <typename Object, typename Container>
Object getobject(Object object, const std::string& fileName)
{
    checkFile(fileName);
    Container objects;
    getFile<Object, Container>(fileName, objects);
    for (Object x : objects)
    {
        if (x.getKey() == object.getKey())
        {
            return x;
        }
    }
    return nullptr;
}

template <typename Object, typename Container>
int verifyObject(Object object, const std::string& fileName)
{
    checkFile(fileName);
    Container objects;
    getFile<Object, Container>(fileName, objects);
    for (Object it : objects) 
    {
        if (it.getKey() == object.getKey())
        {
            return 1;
        }
    }
    return 0;
}

template <typename Object, typename Container>
int remove(Object object, const std::string& fileName)
{
    checkFile(fileName);
    Container objects;
    getFile<Object, Container>(fileName, objects);
    typename Container::iterator it;
    for (it = objects.begin(); it != objects.end(); ++it)
    {
        if (it->getKey() == object.getKey())
        {
            objects.erase(it);
            clearFile(fileName);
            for (Object x : objects)
            {
                setFile<Object>(x, fileName);
            }
            return 1;
        }        
    }
    return 0;
}

#endif
