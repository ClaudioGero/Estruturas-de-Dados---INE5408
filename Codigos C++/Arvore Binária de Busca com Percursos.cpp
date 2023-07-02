#include "array_list.h"

namespace structures {

template<typename T>
class BinaryTree {
public:
    ~BinaryTree() {
        delete root;
    }

    // Insere um elemento na árvore
    void insert(const T& data) {
        if (root == nullptr) {
            root = new Node(data);
        } else {
            root->insert(data);
        }
        size_++;
    }

    // Remove um elemento da árvore
    void remove(const T& data) {
        if (root != nullptr && root->data == data) {
            delete root;
            root = nullptr;
            size_--;
        } else if (root != nullptr) {
            if (root->remove(data)) {
                size_--;
            }
        }
    }

    // Verifica se a árvore contém um elemento específico
    bool contains(const T& data) const {
        if (root != nullptr) {
            return root->contains(data);
        }
        return false;
    }

    // Verifica se a árvore está vazia
    bool empty() const {
        return size_ == 0;
    }

    // Retorna o tamanho da árvore
    std::size_t size() const {
        return size_;
    }

    // Retorna uma lista com os elementos da árvore em pré-ordem
    ArrayList<T> pre_order() const {
        ArrayList<T> result;
        if (root != nullptr) {
            root->pre_order(result);
        }
        return result;
    }

    // Retorna uma lista com os elementos da árvore em ordem simétrica
    ArrayList<T> in_order() const {
        ArrayList<T> result;
        if (root != nullptr) {
            root->in_order(result);
        }
        return result;
    }

    // Retorna uma lista com os elementos da árvore em pós-ordem
    ArrayList<T> post_order() const {
        ArrayList<T> result;
        if (root != nullptr) {
            root->post_order(result);
        }
        return result;
    }

private:
    struct Node {
        explicit Node(const T& data) : data(data),
        left(nullptr),
        right(nullptr) {}

        ~Node() {
            delete left;
            delete right;
        }

        T data;
        Node* left;
        Node* right;

        // Insere um elemento na subárvore
        void insert(const T& data_) {
            if (data_ < data) {
                if (left == nullptr) {
                    left = new Node(data_);
                } else {
                    left->insert(data_);
                }
            } else if (data_ > data) {
                if (right == nullptr) {
                    right = new Node(data_);
                } else {
                    right->insert(data_);
                }
            }
        }

        // Remove um elemento da subárvore
        bool remove(const T& data_) {
            if (data_ < data) {
                if (left == nullptr) {
                    return false;
                } else if (left->data == data_) {
                    delete left;
                    left = nullptr;
                    return true;
                } else {
                    return left->remove(data_);
                }
            } else if (data_ > data) {
                if (right == nullptr) {
                    return false;
                } else if (right->data == data_) {
                    delete right;
                    right = nullptr;
                    return true;
                } else {
                    return right->remove(data_);
                }
            }
            return false;
        }

        // Verifica se a subárvore contém um elemento específico
        bool contains(const T& data_) const {
            if (data_ < data) {
                if (left == nullptr) {
                    return false;
                } else {
                    return left->contains(data_);
                }
            } else if (data_ > data) {
                if (right == nullptr) {
                    return false;
                } else {
                    return right->contains(data_);
                }
            }
            return true;
        }

        // Percorre a subárvore em pré-ordem e adiciona elementos na lista
        void pre_order(ArrayList<T>& v) const {
            v.push_back(data);
            if (left != nullptr) {
                left->pre_order(v);
            }
            if (right != nullptr) {
                right->pre_order(v);
            }
        }
        // Percorre a subárvore em ordem simétrica e adiciona elementos na lista
        void in_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->in_order(v);
            }
            v.push_back(data);
            if (right != nullptr) {
                right->in_order(v);
            }
        }

        // Percorre a subárvore em pós-ordem e adiciona elementos na lista
        void post_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->post_order(v);
            }
            if (right != nullptr) {
                right->post_order(v);
            }
            v.push_back(data);
        }
    };

    Node* root = nullptr;
    std::size_t size_ = 0u;
};

}  // namespace structures
