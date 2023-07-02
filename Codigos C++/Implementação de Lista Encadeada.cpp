#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>


namespace structures {

//! ...
template<typename T>
class LinkedList {
 public:
    //! ...

    LinkedList() {}  // construtor padrão

    ~LinkedList() {  // destrutor
        clear();
    }
    void
     clear() {  // limpar lista
        while (!empty())
            pop_front();
    }

    void push_back(const T& data) {  // inserir no fim
        if (empty()) {
            push_front(data);
        } else {
            insert(data, size());
        }
    }

    void push_front(const T& data) {  // inserir no início
        Node *novo = new Node(data);  //  auxiliar.
        if (novo == nullptr) {
            throw std::out_of_range("ERRO LISTA CHEIA!!!");
        }

        novo-> next(head);
        head = novo;
        size_++;
    }

    void insert(const T& data, std::size_t index) {  // inserir na posição
        if (index > size_|| index < 0) {
            throw std::out_of_range("ERRO NA POSIÇÃO!!!");
        }

        if (index == 0) {
            push_front(data);
        } else {
            Node *novo, *last;  //   auxiliares
            novo = new Node(data);

            if (novo == nullptr)
                throw std::out_of_range("ERRO LISTA CHEIA!!!");
            last = head;

            for (auto  i = 1u; i < index ; i++) {
                last = last -> next();
            }

            novo -> next(last -> next());
            last -> next(novo);
            size_++;
        }
    }

    void insert_sorted(const T& data) {  //  inserir em ordem
        Node *atual;
        std::size_t pos;
        if (empty()) {
            push_front(data);
        } else {
            atual = head;
            pos = 0;
            while (atual -> next() != NULL && data > atual -> data()) {
                atual = atual -> next();
                pos++;
            }

            if (data > atual -> data())  // acabou a lista.
                insert(data, pos + 1);
            else
                insert(data, pos);
        }
    }

    T& at(std::size_t index) {  //  acessar um elemento na posição index
        if (index >= size()) {
           throw std::out_of_range("POSIÇÃO INVÁLIDA!!!");
        }

        auto pos = head;
        for (auto i = 0u; i < index; ++i) {
            pos = pos->next();
        }

        return pos->data();
    }

    T pop(std::size_t index) {  //  retirar da posição
        if (empty()) {
            throw std::out_of_range("LISTA VAZIA!!!");
        }

        if (index >= size() || index < 0) {
            throw std::out_of_range("ERRO NA POSIÇÃO!!!");
        }

        if (index == 0) {
            return pop_front();
        }
        Node *last = end(index);
        Node *kick = last -> next();
        T back = kick -> data();
        last -> next(kick -> next());
        size_--;
        delete kick;
        return back;
    }

    T pop_back() {  //  retirar do fim
        return pop(size() - 1);
    }

    T pop_front() {  //  retirar do início
        if (empty()) {
            throw std::out_of_range("ERRO LISTA CHEIA");
        }
        auto saiu = head;
        T back = saiu -> data();
        head = saiu -> next();
        size_--;
        delete saiu;
        return back;
    }

    void remove(const T& data)  {   //   remover específico
        pop(find(data));
    }

    bool empty() const {   //   lista vazia
        return size() == 0;
    }

    bool contains(const T& data) const {   //   contém
        return find(data) != size();
    }

    std::size_t find(const T& data) const {  //  posição do dado
        std::size_t temp = 0;
        Node *pos = head;
        while (temp < size()) {
            if (pos->data() == data) {
                break;
            }
            pos = pos->next();
            temp++;
        }
        return temp;
    }

    std::size_t size() const {   //  tamanho da lista
        return size_;
    }

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* end(std::size_t index) {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < index; ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif

