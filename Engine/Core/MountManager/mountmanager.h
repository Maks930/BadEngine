#ifndef MOUNTMANAGER_H
#define MOUNTMANAGER_H

#include <map>
#include <string>

class MountManager
{
    // InProgramm path -> System Path

    using MapPoint = std::map<std::string, std::string>;

    static MapPoint m_pathTable;

    static std::string normalizePath(const std::string& path);



public:
    static void mount(const std::string& inProgPath, const std::string& sysPath);
    static void unmount(const std::string& inProgPath);
    static std::string resolve(const std::string& path);
    static MapPoint avaiblePaths();
    static bool hasPoint(const std::string& inProgPath);
    static void clean();

};

// std::string operator""_rdir(const char* str,std::size_t len)
// {
//     return MountManager::resolve(str);
// }

#define rdir(x) MountManager::resolve(x)

#endif // MOUNTMANAGER_H
