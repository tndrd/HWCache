cmake_minimum_required(VERSION 3.10)
project(HWC_Cache_tndrd)

function(build_cache chname)

add_library(${chname} INTERFACE
    include/caches.h
    include/${chname}.h
)
target_include_directories(${chname}
    INTERFACE include
    INTERFACE src
)

endfunction()

build_cache(LFU)
build_cache(LRU)
build_cache(IDL)


add_library(page_t STATIC include/page.h src/page.cpp)
target_include_directories(page_t
    PUBLIC  include
    PRIVATE src
)

add_library(hit_count
    INTERFACE include/hit_count.h
)
target_include_directories(hit_count
    INTERFACE include
)
target_link_libraries(hit_count
    INTERFACE LFU
    INTERFACE LRU
    INTERFACE IDL
    INTERFACE page_t
)

add_executable(e2e src/e2e.cpp)
target_link_libraries(e2e hit_count)