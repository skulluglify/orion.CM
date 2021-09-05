#include "yelp.h"

namespace yelp 
{
    namespace time 
    {
        // typedef chrono::time_point<chrono::_V2::system_clock, chrono::duration<long int, ratio<1, 1000000000> > > durations; //
        time::durations performance_now ()
        {
            return chrono::high_resolution_clock::now();
	    }
        float32 duration_cast (time::durations start, time::durations end)
        {
            // chrono::nanoseconds // chrono::duration_cast<chrono::milliseconds>(end - start) //
            return chrono::duration_cast<chrono::milliseconds>(end - start).count() / 1e9;
        }
    }
    void init() 
    {
        ios::sync_with_stdio(0);
        cin.tie(0);
    }
    void sleep(float32 seconds) 
    {
        int64 milliseconds = 1000 * seconds;
        this_thread::sleep_for(chrono::milliseconds(milliseconds));
    }
    char chr (uint8 i) 
    {
    	return (char)(i);
    }
    uint8 ord (char c) 
    {
    	return (uint8)(c);
    }
}
