#pragma once

#include <cstdlib>

#include <glm/glm.hpp>

namespace engine::renderer {
    enum class ImageFormat {

    };

    struct ImageDescriptor {
        ImageFormat format;

        std::size_t mipLevels;

        glm::uvec3 extent;
    };
}