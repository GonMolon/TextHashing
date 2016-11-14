#include <iostream>
#include <random>

int main() 
{
    std::cout << (int)std::random_device()() << std::endl;
}
