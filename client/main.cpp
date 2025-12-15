
#include "manager/ClientManager.hpp"

auto main(int ac, char **av) -> int
{
    ClientManager manager;

    manager.launch(ac, av);
}
