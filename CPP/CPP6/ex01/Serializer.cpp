#include "Serializer.hpp"

// pointeur → entier : reinterpret_cast réinterprète les bits bruts
uintptr_t Serializer::serialize(Data* ptr) {
    return reinterpret_cast<uintptr_t>(ptr);
}

// entier → pointeur : même opération inverse
Data* Serializer::deserialize(uintptr_t raw) {
    return reinterpret_cast<Data*>(raw);
}

//reinterpret_cast ne convertis pas il modifie l'interpretation des bits.