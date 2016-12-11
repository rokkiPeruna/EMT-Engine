
#ifdef __ANDROID__

#include <string>
#include <sstream>

namespace std
{

template <typename T>
inline string to_string(const T& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

}

#endif
