#include "Transposition_Table.h"

transposition_table::transposition_table(const uint32_t size)
{
    size_ = size;
    table_.resize(size);
}

uint32_t transposition_table::hash(uint64_t const key)
{
    return key%size_;
}

void transposition_table::set(uint64_t const key, const int value)
{
    return set(hash(key), key, value);
}

void transposition_table::set(const uint32_t index, uint64_t const key, const int value)
{
    table_[index].key = key;
    table_[index].value = value;
}

bool transposition_table::has(uint64_t const key)
{
    return  has(hash(key), key);
}

bool transposition_table::has(const uint32_t index, uint64_t const key)
{
    return table_[index].key == key;
}

int transposition_table::get(uint64_t const key)
{
    return get(hash(key));
}

int transposition_table::get(const uint32_t index)
{
    return table_[index].value;
}






