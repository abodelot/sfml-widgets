// for Windows and Linux OS. Helper to load assets

#ifndef __APPLE__
#include "ResourcePath.hpp"

std::string chk::getResourcePath(const std::string& relativePath)
{
    return "resources/" + relativePath;
}

#endif