## orion.CM
```cpp
#include "extras/orion.h"

// include yelp, y extensions like python

// init
yelp::init();

// time::performance_now()
yelp::time::durations start = yelp::time::performance_now();
yelp::time::durations end = yelp::time::performance_now();

// time::performance_now() - time::performance_now()
float32 timeit = yelp::time::duration_cast(start, end);

cout << timeit << endl;

// sleep // seconds input
yelp::sleep(2);

// chr 
yelp::chr(115); // s

// ord
yelp::ord('s') // 115
```
- orion.cpp
- orion.h
- yelp.cpp
- yelp.h
