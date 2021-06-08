#include <iostream>
#if defined(HAVE_LOG) && defined(HAVE_EXP)
    #include <cmath>
#endif

#include "table.h"

namespace math
{
namespace detail
{

double sqrt(const double value)
{
    if (value < 0)
        return 0;

    if (value < 10) {
        double result = sqrt_table[static_cast<unsigned>(value)];
        std::cout << "computing sqrt of " << value << ", result : " << result
            << " use table." << std::endl;
        return result;
    }

#if defined(HAVE_LOG) && defined(HAVE_EXP)
    double result = exp(log(value) * 0.5);
    std::cout << "computing sqrt of " << value << ", result : " << result
        << " use log and exp." << std::endl;
#else
    double result = value;
#endif
    return result;
}

}
}