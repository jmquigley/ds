#include <iostream>

#include "node.h"
#include "uuid/uuid.h"

template<typename T>
Node<T>::Node() {

    uuid_t uuid;
    uuid_generate_random(uuid);

    std::cout << "UUID: '" << uuid << "'" << std::endl;
}

template<typename T>
Node<T>::Node(T data) {
}

template<typename T>
Node<T>::~Node() {
}
