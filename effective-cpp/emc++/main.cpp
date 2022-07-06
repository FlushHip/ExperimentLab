#include <iostream>
#include <list>
#include <iomanip>

#include "pimpl/widget.h"

int main(int argc, char **argv) {
	std::cout << "emc" << std::endl;
	Widget widget;
	//auto w = new Widget();
	for (int i = 1; i < 10; ++i) {
		for (int j = 1; j <= i; ++j) {
			std::cout << std::setw(2) << std::setfill(' ') << j << " *" << std::setw(2) << i << " = " << std::setw(2) << i * j
				<< " \n"[j == i];
		}
	}
	return 0;
}
