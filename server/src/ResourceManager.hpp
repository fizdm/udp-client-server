#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <string>
#include <fstream>
#include <optional>

class ResourceManager {
public:
    static constexpr inline ushort MAX_RESOURCE_CONTENT_SIZE{1024};
    static constexpr inline ushort MAX_RESOURCE_NAME_SIZE{64};

    static std::optional<std::string> GetResource(const std::string& resource) {
        std::ifstream resorceFile("data/" + resource);

        if (!resorceFile) {
            return std::nullopt;
        }

        std::string resourceSs(std::istreambuf_iterator<char>(resorceFile), {});
        return resourceSs;
    }
};

#endif //RESOURCEMANAGER_HPP
