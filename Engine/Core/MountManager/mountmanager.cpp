#include <filesystem>
#include <stdexcept>

#include <MountManager/mountmanager.h>


MountManager::MapPoint MountManager::m_pathTable;

std::string MountManager::normalizePath(const std::string &path)
{
    if (path.empty()) return "/";

    std::string result;
    bool lastWasSlash = false;

    for (char c: path) {
        if (c == '\\') c = '/';

        if (c == '/') {
            if (!lastWasSlash) {
                result += "/";
                lastWasSlash = true;
            }
        } else {
            result += c;
            lastWasSlash = false;
        }
    }

    if (result.size() > 1 && result.back() == '/') {
        result.pop_back();
    }

    return result;
}

void MountManager::mount(const std::string &inProgPath, const std::string &sysPath)
{
    if (!std::filesystem::exists(sysPath)) {
        throw std::runtime_error("SysPath \"" + sysPath + "\" not exists");
    }
    if (m_pathTable.contains(normalizePath(inProgPath))) {
        throw std::runtime_error("ProgPath \"" + inProgPath + "\" alrady exists");
    }

    m_pathTable[normalizePath(inProgPath)] = normalizePath(sysPath);
}

void MountManager::unmount(const std::string &inProgPath)
{
    if (!m_pathTable.contains(normalizePath(inProgPath))) {
        throw std::runtime_error("ProgPath \"" + inProgPath + "\" not exists");
    }

    m_pathTable.erase(normalizePath(inProgPath));
}

std::string MountManager::resolve(const std::string &path)
{
    std::string cleanPath = normalizePath(path);

    auto exactMatch = m_pathTable.find(cleanPath);
    if (exactMatch != m_pathTable.end()) {
        return exactMatch->second;
    }

    std::string bestMatch;
    std::string bestReplacement;

    for (const auto& [inProgPath,sysPath] : m_pathTable) {

        // if (inProgPath == "/") continue;

        std::string inProgramPathPrefix = inProgPath + "/";

        if (cleanPath.find(inProgramPathPrefix) != std::string::npos && inProgPath.length() > bestMatch.length()) {
            bestMatch = inProgPath;
            bestReplacement = sysPath;
        }

    }

    if (!bestMatch.empty()) {
        return bestReplacement + cleanPath.substr(bestMatch.length());
    }

    auto rootMount = m_pathTable.find("/");
    if (rootMount != m_pathTable.end()) {
        return rootMount->second + cleanPath;
    }

    return cleanPath;


}

bool MountManager::hasPoint(const std::string &inProgPath)
{
    return m_pathTable.find(normalizePath(inProgPath)) != m_pathTable.end();
}

void MountManager::clean()
{
    m_pathTable.clear();
}



MountManager::MapPoint MountManager::avaiblePaths()
{
    return m_pathTable;
}
