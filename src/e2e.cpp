#include "IDL.hpp"
#include "LFU.hpp"
#include "LRU.hpp"
#include "page.hpp"
#include <cstring>

const size_t MAX_PARAM_LENGTH = 5;

using namespace Caches;

int main (int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Error: no parameter; \"LRU\", \"LFU\", \"Ideal\" expected" << std::endl;
        return 1;
    }

    char* cache_name = argv[1];

    size_t hits = -1;

    if (!strncmp(cache_name, "LRU", MAX_PARAM_LENGTH))
    {
        hits = count_hits<LRU_cache_t, page_t, int, page_t (&)(int)>(slow_get_page);
    }
    else if (!strncmp(cache_name, "LFU", MAX_PARAM_LENGTH))
    {
        hits = count_hits<LFU_cache_t, page_t, int, page_t (&)(int)>(slow_get_page);
    }
    else if (!strncmp(cache_name, "Ideal", MAX_PARAM_LENGTH))
    {
        hits = count_hits<Ideal_cache_t, page_t, int, page_t (&)(int)>(slow_get_page);
    }
    else
    {
        std::cout << "Error: wrong parameter; \"LRU\", \"LFU\", \"Ideal\" expected" << std::endl;
        return 2;
    }

    std::cout << hits << std::endl;

    return 0;
}
