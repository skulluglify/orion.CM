#include "yelp.h"

yelp::time::durations yelp::time::performance_now ()
{
    return chrono::high_resolution_clock::now();
}

f32 yelp::time::duration_cast (time::durations start, time::durations end)
{
    /* chrono::nanoseconds // chrono::duration_cast<chrono::milliseconds>(end - start) */
    return chrono::duration_cast<chrono::milliseconds>(end - start).count() / 1e9;
}


fn yelp::init() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

fn yelp::sleep(f32 seconds) 
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
