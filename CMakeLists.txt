cmake_minimum_required(VERSION 3.10)
project(HWC_Cache_tndrd)

set(TESTS_DIRECTORY ${CMAKE_SOURCE_DIR}/tests)
set(MY_CACHES IDL LFU LRU)

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


foreach(my_cache ${MY_CACHES})
    build_cache(${my_cache})
endforeach()


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

enable_testing()

file(GLOB tests ${TESTS_DIRECTORY}/*.in)
set(i 0)
foreach(test ${tests})
    
    string(REPLACE ".in" "" testpath ${test})
    
    foreach(my_cache ${MY_CACHES})
        set(testname test_${my_cache}_${i})
        add_test(${testname} e2e ${my_cache} ${testpath}.in)
        file(READ ${testpath}_${my_cache}.out expected_output)
        set_tests_properties(${testname} PROPERTIES PASS_REGULAR_EXPRESSION ${expected_output})
    endforeach()

    math(EXPR i "${i} + 1")
endforeach()

