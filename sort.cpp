#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//	Bubble Sort 1000 items:
//  Best    - 0.001s
//	Random  - 0.008s
//  Worst   - 0.005s

void bubble_sort(int *begin, int *end)
{
	int *last = end + 1;
	while(last != begin) {
		int *newlast = begin;

		for(int *i = begin; i != last; i++) {
			if(*(i - 1) > *i) {
				swap(i, i - 1);
				newlast = i;
			}
		}
		last = newlast;
	}
}

//	Stooge Sort 1000 items:
//  Best    - 0.237s
//	Random  - 0.248s
//  Worst   - 0.288s

void stooge_sort(int *begin, int *end)
{
	if(*begin > *end)
		swap(begin, end);
	if((end - begin) > 1) {
		int t = (end - begin + 1) / 3;
		stooge_sort(begin    , end - t);
		stooge_sort(begin + t, end    );
		stooge_sort(begin    , end - t);
	}
}

//	Insertion Sort 1000 items:
//  Best    - 0.002
//	Random  - 0.003s
//  Worst   - 0.004s

void insertion_sort(int *begin, int *end)
{
	for(int *i = begin + 1; i != end + 1; i++) {
		int *j = i;
		while(j > 0 && *(j - 1) > *j) {
			swap(j, j--);
		}
	}
}

int main(int argc, char** argv)
{
	std::srand(std::time(NULL));

	if(argc < 3) {
		std::cout << "Please specify vector length and mode\n";
		return 0;
	}

	char *end;
	int len = strtol(argv[1], &end, 10);

	int mode = strtol(argv[2], &end, 10);

	std::vector<int> vec;

	switch(mode) {
		// Sorted
		case 0:
			for(int i = 0; i < len; i++)
				vec.push_back(i);
			break;
		// Random state
		case 1:	
			for(int i = 0; i < len; i++)
				vec.push_back(std::rand() % 100);
			break;
		case 2:
		// Inverse sorted (worst case)
			for(int i = 0; i < len; i++)
				vec.push_back(len - i);
			break;
	}

	quick_sort(&vec[0], &vec.back());

	for(int i = 0; i < vec.size() - 1; i++)
		std::cout << vec[i] << ", ";
	std::cout << vec[vec.size() - 1] << '\n';
}
