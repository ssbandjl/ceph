#include <iostream>
#include <string>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define STRX(x) #x
#define STR(x) STRX(x)
// #define __FFL__ __FILE__ ":" STR(__LINE__)
// #define __FFL__ STR(__func__) " " STR(__FILENAME__) ":" STR(__LINE__)
#define __FUNC__ __func__ << " (" << __LINE__ << ") "

#define __FFL__ __func__ << " " << __FILE__ << ":" << __LINE__

int main()
{
    std::cout << __FFL__ << std::endl;
}