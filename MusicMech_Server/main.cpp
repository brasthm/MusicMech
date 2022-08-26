#include <iostream>
#include "../src/Network/Server.h"
#include "../src/main.h"

int main() {
    IS_SERVER = true;
    std::cout << "Server started at " << sf::IpAddress::getLocalAddress() << "/" << sf::IpAddress::getPublicAddress() << std::endl;

    Server s;
    s.run();
    return 0;
}
