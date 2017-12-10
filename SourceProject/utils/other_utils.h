#include <iostream>
#include <ctime>

using namespace std;

namespace linukey{
namespace utils{

time_t get_now_time(){
    return time(NULL);
}

}
}
