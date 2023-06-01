#pragma once
#include <cstdint>
#include <vector>
#include "Board.h"

class transposition_table
{

private:
    struct cell
    {
        uint64_t key;
        int value;
    };
    uint32_t size_;
    std::vector<cell> table_;


public:
    
    transposition_table(uint32_t size);
    
    uint32_t hash(uint64_t key);
    void set(uint64_t key, int value);
    void set(uint32_t index, uint64_t key, int value);
    bool has(uint64_t key);
    bool has(uint32_t index, uint64_t key);
    int get(uint64_t key);
    int get(uint32_t index);
    
    
};
