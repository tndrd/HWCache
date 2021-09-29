#include <iostream>
#include <unordered_map>
#include <list> 
#include <string>
#include <cassert>
#include <vector>
#include <limits>
#include <algorithm>

namespace Caches
{
    template <typename T>
    using VectorIt_t = typename std::vector<T>::iterator;

    template <typename T>
    using cVectorIt_t = typename std::vector<T>::const_iterator;

    template <typename T>
    using ListIt_t = typename std::list<T>::iterator;

    template <typename T>
    using cListIt_t = typename std::list<T>::const_iterator;

}