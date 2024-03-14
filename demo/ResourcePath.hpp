#pragma once
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include <string>

namespace chk
{
/**
 * \brief Get absolute path of file specified
 * \param relativePath file relative to `Resources/` directory
 * \return The absolute file path
 */
std::string getResourcePath(const std::string &relativePath);
} // namespace chk