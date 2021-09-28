#include "yelp.h"

yelp::time::durations yelp::time::performance_now ()
{
    return chrono::high_resolution_clock::now();
}

FLOAT yelp::time::duration_cast (time::durations start, time::durations end)
{
    // chrono::nanoseconds // chrono::duration_cast<chrono::milliseconds>(end - start) //
    return chrono::duration_cast<chrono::milliseconds>(end - start).count() / 1e9;
}


fn yelp::init() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

fn yelp::sleep(FLOAT seconds) 
{
    int64 milliseconds = 1000 * seconds;
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

char yelp::chr (uint8 i) 
{
    return (char)(i);
}

uint8 yelp::ord (char c) 
{
    return (uint8)(c);
}

string yelp::bin (uint8 n) 
{
    // size_t N = sizeof();
    return bitset<8>(n).to_string();
}

// string yelp::bin (uint16 n) 
// {
//     // size_t N = sizeof();
//     return bitset<16>(n).to_string();
// }

// string yelp::bin (uint32 n) 
// {
//     // size_t N = sizeof();
//     return bitset<32>(n).to_string();
// }

// string yelp::bin (uint64 n) 
// {
//     // size_t N = sizeof();
//     return bitset<64>(n).to_string();
// }