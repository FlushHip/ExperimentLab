#if defined(_WIN32)
#  if defined(EXPORTING_MATH)
#    define DECLSPEC __declspec(dllexport)
#  else
#    define DECLSPEC __declspec(dllimport)
#  endif
#else // non windows
#  define DECLSPEC
#endif

namespace math
{
double DECLSPEC sqrt(double value);
}