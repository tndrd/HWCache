#include "page.h"
#include <cassert>

#include "../include/IDL.h"
#include "../include/LRU.h"
#include "../include/LFU.h"

using namespace Caches;

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

template<>
  size_t count_hits<Ideal_cache_t, page_t, int, page_t (&)(int)>(page_t (&get_function)(int))
  {
      size_t hits = 0;
      size_t nelements_in;
      size_t cache_size;

      std::cin >> cache_size >> nelements_in;
      assert(std::cin.good());
      
      Ideal_cache_t<page_t> cache {cache_size};
      std::vector<int> datastream;
      
      for (int i = 0; i < nelements_in; ++i)
      {
        int key;
        std::cin >> key;
        assert(std::cin.good());
        datastream.push_back(key);
      }
      
      hits = cache.predict_hits(datastream, get_function);

      return hits;
  }