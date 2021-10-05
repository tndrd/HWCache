#include <cstring>
#include <iostream>
#include "../include/hit_count.h"

const size_t MAX_PARAM_LENGTH = 3;

using namespace Caches;

int main (int argc, char** argv)
{
    if (argc != 3)
    {
        std::cout << "Error: wrong parameters; \"LRU\"/\"LFU\"/\"IDL\" and test_path expected" << std::endl;
        return 1;
    }

    char* cache_name = argv[1];
    char* test_name  = argv[2];

    size_t hits = -1;
    try
    {
        if (!strncmp(cache_name, "LRU", MAX_PARAM_LENGTH))
        {
            hits = count_hits<LRU_cache_t, page_t, int, page_t (&)(int)>(slow_get_page, test_name);
        }
        else if (!strncmp(cache_name, "LFU", MAX_PARAM_LENGTH))
        {
            hits = count_hits<LFU_cache_t, page_t, int, page_t (&)(int)>(slow_get_page, test_name);
        }
        else if (!strncmp(cache_name, "IDL", MAX_PARAM_LENGTH))
        {
            hits = count_hits<Ideal_cache_t, page_t, int, page_t (&)(int)>(slow_get_page, test_name);
        }
        else
        {
            std::cout << "Error: wrong parameter; \"LRU\", \"LFU\", \"IDL\" expected" << std::endl;
            return 2;
        }

        std::cout << hits << std::endl;
    }
    
    catch(const char*)
    {
        std::cout << "Error: can't open test input file \"" << test_name << "\".\n";
    }
    
    return 0;
}
