#include "maths.h"

#ifdef USE_MATHS
    #include "sqrt/sqrt.h"
#else
    #include <cmath>
#endif

namespace math
{
double sqrt(double value)
{
    double result = 0.0;
#ifdef USE_MATHS
    result = math::detail::sqrt(value);
#else
    result = std::sqrt(value);
#endif
    return result;
}
}