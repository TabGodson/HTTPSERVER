#include <iostream>
#include <ctime>
#include <cstring>
#include <thread>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

namespace http
{
class server;

class server
{
private:
int listen_num = 1;
struct thrset
{

}
thrset* thrsetting;
thread* thr;
public:
bool* runing;
static void thrfuc(thrset* setting)
{

}
}

}