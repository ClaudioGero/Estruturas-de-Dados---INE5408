#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <stdexcept>

namespace structures {

template <typename T>
class ArrayList {
public:
    ArrayList();
    explicit ArrayList(std::size_t max_size);
    ~ArrayList();

    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool full() const;
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    T& at(std::size_t index);
    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;
    const T& operator[](std::size_t index) const;

private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures

#endif

template <typename T>
structures::ArrayList<T>::ArrayList() {
    max_size_ = DEFAULT_MAX;
    contents = new T[max_size_];
    size_ = 0;
}

template <typename T>
structures::ArrayList<T>::ArrayList(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    size_ = 0;
}

template <typename T>
structures::ArrayList<T>::~ArrayList() {
    delete[] contents;
}

template <typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

template <typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full()) {
        throw std::out_of_range("Lista cheia");
    } else {
        contents[size_] = data;
        size_++;
    }
}

template <typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    if (full()) {
        throw std::out_of_range("Lista cheia");
    } else {
        for (int i = size_; i > 0; i--) {
            contents[i] = contents[i - 1];
        }
        contents[0] = data;
        size_++;
    }
}

template <typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full()) {
        throw std::out_of_range("Lista cheia");
    } else if (index > size_) {
        throw std::out_of_range("Posição inválida");
    } else {
        for (std::size_t i = size_; i > index; i--) {
            contents[i] = contents[i - 1];
        }
        contents[index] = data;
        size_++;
    }
}

template <typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full()) {
        throw std::out_of_range("Lista cheia");
    } else {
        std::size_t i = 0;
        for (; i < size_; i++) {
            if (contents[i] > data) {
                insert(data, i);
                break;
            }
        }
        if (i == size_) {
            insert(data, i);
        }
    }
}

template <typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    } else if (index >= size_) {
        throw std::out_of_range("Posição inválida");
    } else {
        T data = contents[index];
        for (std::size_t i = index; i < size_ - 1; i++) {
            contents[i] = contents[i + 1];
        }
        size_--;
        return data;
    }
}

template <typename T>
T structures::ArrayList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    } else {
        T data = contents[size_ - 1];
        size_--;
        return data;
    }
}

template <typename T>
T structures::ArrayList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    } else {
        T data = contents[0];
        for (std::size_t i = 0; i < size_ - 1; i++) {
            contents[i] = contents[i + 1];
        }
        size_--;
        return data;
    }
}

template <typename T>
void structures::ArrayList<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    } else {
        for (std::size_t i = 0; i < size_; i++) {
            if (contents[i] == data) {
                pop(i);
                return;
            }
        }
        throw std::out_of_range("Elemento inválido");
    }
}

template <typename T>
bool structures::ArrayList<T>::full() const {
    return size_ == max_size_;
}

template <typename T>
bool structures::ArrayList<T>::empty() const {
    return size_ == 0;
}

template <typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    for (std::size_t i = 0; i < size_; i++) {
        if (contents[i] == data) {
            return true;
        }
    }
    return false;
}

template <typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    if (contains(data)) {
        for (std::size_t i = 0; i < size_; i++) {
            if (contents[i] == data) {
                return i;
            }
        }
    }
    return -1;
}

template <typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}

template <typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

template <typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Posição inválida");
    }
    return contents[index];
}

template <typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    return contents[index];
}

template <typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Posição inválida");
    }
    return contents[index];
}

template <typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    return contents[index];
}
