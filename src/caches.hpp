#pragma once

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

    template<template<typename DataT, typename KeyT = int> typename CacheT, typename DataT, typename KeyT = int, typename GetF>
    size_t count_hits(GetF get_function)
    {
        size_t hits = 0;
        size_t nelements_in;
        size_t cache_size;

        std::cin >> cache_size >> nelements_in;
        assert(std::cin.good());
        
        CacheT<DataT, KeyT> cache {cache_size};

        for (int i = 0; i < nelements_in; ++i)
        {
            KeyT key;
            std::cin >> key;
            assert(std::cin.good());
            
            if (cache.lookup_update(key, get_function))
            hits += 1;
        }
        
        return hits;
    }

}