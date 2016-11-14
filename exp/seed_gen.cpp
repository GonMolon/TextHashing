#include <iostream>
#include <random>

int main() 
{
    std::cout << std::random_device()() << std::endl;
}
