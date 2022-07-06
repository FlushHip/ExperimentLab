#include <iostream>
#include <list>
#include <algorithm>

#include <boost/lambda/lambda.hpp>

int main(int argc, char **argv) {
	std::cout << "mec" << std::endl;
	std::list<int> arr{1, 2, 3};
	
	int sum = 0;
	using namespace boost::lambda;
	std::for_each(arr.begin(), arr.end(), sum += _1);
	std::cout << sum << std::endl;
	
	return 0;
}
