#include <iostream>
#include <csignal>
#include <cstdlib>
#include <thread>
#include <sstream>
#include "./RType.hpp"

void crashHandler(int sig) {
    std::ostringstream oss;
    oss << "CRASH! Signal: " << sig << " in thread: " 
        << std::this_thread::get_id() << std::endl;
    std::cerr << oss.str();
    std::abort();
}

int main(int argc, char **argv)
{
    signal(SIGSEGV, crashHandler);
    signal(SIGABRT, crashHandler);
    
    try {
        return RType(argc, argv).launch();
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return 84;
    }
}
