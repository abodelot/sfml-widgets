#ifdef _WIN32
#include "ResourcePath.hpp"

std::string chk::getResourcePath(const std::string &relativePath)
{
    return "resources/" + relativePath;
}

#endif