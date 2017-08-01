#include<iostream>
#include<ctime>
#include<stdint.h>

int main()
{
	std::clock_t start = clock();
	int count_5 = 0;
	int count_7 = 0;
	int64_t loop = 1000000000;
	for (int i = 1; i <= loop; i++)
	{
		if (i % 5  == 0) {
			count_5 ++;

		}
		
		if (i % 7 == 0) {
			count_7 ++;
		}

	}

	std::cout << "There are " << count_5 << " numbers below 10E9 that can be divided by 5.\n";
	
	std::cout << "There are " << count_7 << " numbers below 10E9 that can be divided by 7.\n";

	std::clock_t end = clock();
	std::cout << "Total time: " << (double)(end-start)/CLOCKS_PER_SEC << " s.\nTotal 10E9 loops\n";

}
