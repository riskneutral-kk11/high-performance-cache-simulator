#include <cstdint>
#include <iostream>
#include <string>
#include <bitset> 
#include <bit>

constexpr unsigned uint16_t cache_size = 4096; // 4kb
constexpr unsigned uint8_t cache_line_size = 64; // 64 bytes 
constexpr unsigned uint8_t N = 4; // number of cache-lines in each set (associtivity)

// Each CacheSet must fit in 1 Cache-line
struct alignas(64) CacheSet { 
    // dirty bit, valid bit, and tags
    uint64_t tag[N]; // 8*N bytes = 32 bytes offset = 0,
    uint8_t dirty_bit[N]; //  offset = 32
    uint8_t valid_bit[N]; //  offset = 36

};

class Cache{
private: 
    static constexpr unsigned int cache_sets = cache_size / (cache_line_size * N) ;

    // Bit Manipulation Stuff
    static constexpr uint8_t offset_bits = std::countr_zero(cache_line_size);
    static constexpr uint8_t set_bits = std::countr_zero(cache_sets);
    static constexpr uint8_t set_mask = cache_sets - 1;

    inline void parse_address(u_int64_t addr){
        cache_set = (addr >> offset_bits) & set_mask;
        tag = addr >> (offset_bits + set_bits);
    }



public: 
    CacheSet cache[cache_sets];

    void read(uint64_t addr){
        uint32_t cache_set;
        uint64_t tag;

        parse_address(addr);

        // look for the 'tag' in the particular cacheset;
        
    }

};

int main(){
    std::string input_bits = "0111111111111100011111111111110001111111111111000111111111111100"; // random 64 bit integer 
    std::bitset<64> bits(input_bits);
    uint64_t addr = bits.to_ullong();

    Cache cache; 
    cache.read(addr);
    return 0;
}