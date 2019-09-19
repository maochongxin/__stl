//
// Created by 毛崇鑫 on 2019/9/19.
//

#ifndef STL_ALLOC_H
#define STL_ALLOC_H

#include <cstdlib>

namespace STD {
    class Alloc {
    private:
        static const size_t ALIGN = 8;
        static const size_t MAXBYTES = 128;
        static const size_t NFREELISTS = (MAXBYTES / ALIGN);
    private:
        union obj {
            union obj* next;
            char client[1];
        };
        static obj* free_list[NFREELISTS];

    private:
        static char* start_list;
        static char* end_list;
        static size_t heap_size;

    private:
        static size_t ROUND_UP(size_t bytes) {
            return ((bytes + ALIGN - 1) & ~(ALIGN - 1));
        }
        static size_t FREELIST_INDEX(size_t bytes) {
            return (((bytes) + ALIGN - 1) / ALIGN - 1);
        }
        static void* refill(size_t n);
        static char* chunk_alloc(size_t size, size_t& nobjs);

    public:
        static void* alloc(size_t bytes);
        static void deallocate(void* ptr, size_t bytes);
        static char* chunk_alloc(void* ptr, size_t old_sz, size_t new_sz);
    };
}

#endif //STL_ALLOC_H
