template <class T>
Node<T>::Node() {
    uuid_t uuid;
    uuid_generate_random(uuid);
    std::cout << "UUID: '" << uuid << "'" << std::endl;
}

template <class T>
Node<T>::Node(T data) {}

template <class T>
Node<T>::~Node() {}
