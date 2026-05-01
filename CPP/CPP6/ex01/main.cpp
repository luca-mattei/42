#include <iostream>
#include "Serializer.hpp"

int main() {
    Data* original = new Data();
    original->value = 42;
    original->name  = "test";

    std::cout << "Original pointer : " << original << std::endl;
    std::cout << "Data.value       : " << original->value << std::endl;
    std::cout << "Data.name        : " << original->name << std::endl;

    uintptr_t raw = Serializer::serialize(original);
    std::cout << "\nSerialized (int) : " << raw << std::endl;

    Data* result = Serializer::deserialize(raw);
    std::cout << "Deserialized ptr : " << result << std::endl;
    std::cout << "Data.value       : " << result->value << std::endl;
    std::cout << "Data.name        : " << result->name << std::endl;

    if (result == original)
        std::cout << "\nSuccess: pointers are equal" << std::endl;
    else
        std::cout << "\nFailure: pointers differ" << std::endl;

    delete original;
    return 0;
}