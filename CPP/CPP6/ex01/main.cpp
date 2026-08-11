#include <iostream>
#include "Serializer.hpp"

int main() {
    Data* original = new Data();
    original->value = 42;
    original->name  = "test";

    std::cout << "Original pointer : " << original << std::endl;
    std::cout << "Data.value       : " << original->value << std::endl;
    std::cout << "Data.name        : " << original->name << std::endl;

    uintptr_t addressAsInteger = Serializer::serialize(original);
    std::cout << "\nAddress as integer : " << addressAsInteger << std::endl;

    Data* recovered = Serializer::deserialize(addressAsInteger);
    std::cout << "Recovered pointer  : " << recovered << std::endl;
    std::cout << "Data.value         : " << recovered->value << std::endl;
    std::cout << "Data.name          : " << recovered->name << std::endl;

    if (recovered == original)
        std::cout << "\nSuccess: pointers are equal" << std::endl;
    else
        std::cout << "\nFailure: pointers differ" << std::endl;

    delete original;
    return 0;
}