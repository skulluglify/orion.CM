// #include <iostream>
#include "extras/orion.h"

// using namespace std;

int main() 
{
    yelp::init();
	// _setmode(_fileno(stdout), _O_U16TEXT);
	// cout << "\xb1[1;32;40m say glob! \xb1[0m\n" << endl;
	// printf("\e[1;32;40m say glob! \e[0m\n");
	yelp::time::durations a = yelp::time::performance_now();
	bytes name = "Ahmad Asy SyafiQ";
	cout << name << endl;
	cout << yelp::ord('s') << endl;
	cout << yelp::chr(115) << endl;
	int i = 1;
	int index = 1;
	while (true) 
	{
		char chars = '#';
		// char chars = cin.get();
		// std::cout << chars;
		// 86 22
		if (index > 7) 
		{
			index = 1;
		}

		printf("\e[0;3%d;4%dm%c\e[0m", index, index, chars);
		printf("\e[0;3%d;4%dm%c\e[0m", index, index, chars);
		printf("\e[0;3%d;4%dm%c\e[0m", index, index, chars);
		printf("\e[0;3%d;4%dm%c\e[0m", index, index, chars);
		
		if (i > 1000)
		{
			break;
		}
		yelp::sleep(0.002);
		index++;
        i++;
	}
	yelp::time::durations b = yelp::time::performance_now();
	cout << endl;
	float32 count = yelp::time::duration_cast(a, b);
    cout << "=======================================================================" << endl;
	cout << count << endl;
	cout << "=======================================================================" << endl;
	return 0;
}
