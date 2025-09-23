#pragma once

#include <functional>
#include <vector>

namespace utils {
    template <typename T>
    using ReferenceList = std::vector<std::reference_wrapper<T>>;
}