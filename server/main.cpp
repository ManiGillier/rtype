#include <iostream>
#include "./RType.hpp"

int main(int argc, char **argv)
{
    try {
        return RType(argc, argv).launch();
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return 84;
    }
}
