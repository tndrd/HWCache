#include "page.h"
#include <cassert>
#include <fstream>
#include <string>

#include "../include/IDL.h"
#include "../include/LRU.h"
#include "../include/LFU.h"

const char* FILE_NOT_FOUND_MSG = "Test file not found";

using namespace Caches;

template<template<typename DataT, typename KeyT = int> typename CacheT, typename DataT, typename KeyT = int, typename GetF>
size_t count_hits(GetF get_function, const std::string& filename)
{   
    std::ifstream fs;
    fs.open(filename, std::fstream::in);  

    if(!fs) {throw FILE_NOT_FOUND_MSG;}

    size_t nelements_in = 0;
    size_t cache_size = 0;
    fs >> cache_size >> nelements_in;
    assert(fs.good());

    CacheT<DataT> cache {cache_size};
    
    size_t hits = 0;
    for (int i = 0; i < nelements_in; ++i)
    {
        KeyT key;
        fs >> key;
        
        if (cache.lookup_update(key, get_function))
        hits += 1;
    }
    
    fs.close();

    return hits;
}

template<>
size_t count_hits<Ideal_cache_t, page_t, int, page_t (&)(int)>(page_t (&get_function)(int), const std::string& filename)
{   
    std::ifstream fs;
    fs.open(filename, std::fstream::in);  

    if(!fs) {throw FILE_NOT_FOUND_MSG;}

    size_t nelements_in = 0;
    size_t cache_size = 0;
    fs >> cache_size >> nelements_in;
    assert(fs.good());

    Ideal_cache_t<page_t> cache {cache_size};
    std::vector<int> datastream;
    
    for (int i = 0; i < nelements_in; ++i)
    {
        int key = 0;
        fs >> key;
        fflush(stdout);
        datastream.push_back(key);
    }
    
    fs.close();

    return cache.predict_hits(datastream, get_function);
}