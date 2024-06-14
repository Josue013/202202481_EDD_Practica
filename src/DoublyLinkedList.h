#ifndef LISTA_DOBLE_ENLAZADA_H
#define LISTA_DOBLE_ENLAZADA_H
#include <iostream>
#include <stdexcept> 
#include <string> 

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(T data) : data(data), next(nullptr), prev(nullptr) {}
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        Node<T>* actual = head;
        while (actual != nullptr) {
            Node<T>* next = actual->next;
            delete actual;
            actual = next;
        }
    }

    void prepend(T data) {
        Node<T>* nuevoNodo = new Node<T>(data);
        if (head == nullptr) {
            head = tail = nuevoNodo;
        } else {
            nuevoNodo->next = head;
            head->prev = nuevoNodo;
            head = nuevoNodo;
        }
    }

    void append(T data) {
        Node<T>* nuevoNodo = new Node<T>(data);
        if (tail == nullptr) {
            head = tail = nuevoNodo;
        } else {
            nuevoNodo->prev = tail;
            tail->next = nuevoNodo;
            tail = nuevoNodo;
        }
    }

    int getSize() const {
        int size = 0;
        Node<T>* actual = head;
        while (actual != nullptr) {
            size++;
            actual = actual->next;
        }
        return size;
    }

    T getElement(int pos) const {
        if (pos < 0 || pos >= getSize()) {
            throw std::out_of_range("Posición inválida");
        }
        Node<T>* actual = head;
        for (int i = 0; i < pos; i++) {
            actual = actual->next;
        }
        return actual->data;
    }

    void eliminarDelFinal() {
        if (tail != nullptr) {
            Node<T>* nodoAEliminar = tail;
            tail = tail->prev;
            if (tail != nullptr) {
                tail->next = nullptr;
            } else {
                head = nullptr;
            }
            delete nodoAEliminar;
        }
    }

    void eliminarDelInicio() {
        if (head != nullptr) {
            Node<T>* nodoAEliminar = head;
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
            delete nodoAEliminar;
        }
    }

    T buscarPorNumeroDePasaporte(const std::string& numeroDePasaporte) const {
        Node<T>* actual = head;
        while (actual != nullptr) {
            if (actual->data.getNumeroDePasaporte() == numeroDePasaporte) {
                return actual->data;
            }
            actual = actual->next;
        }
        throw std::runtime_error("No se encontró ese número de pasaporte");
    }

    void ordenarPorNumeroDeAsiento() {
        if (head == nullptr) {
            return;
        }
        Node<T>* actual = head;
        while (actual->next != nullptr) {
            Node<T>* next = actual->next;
            while (next != nullptr) {
                if (actual->data.getAsiento() > next->data.getAsiento()) {
                    T temp = actual->data;
                    actual->data = next->data;
                    next->data = temp;
                }
                next = next->next;
            }
            actual = actual->next;
        }
    }

    void ordenarPorNumeroDeVuelo() {
        if (head == nullptr) {
            return;
        }
        Node<T>* actual = head;
        while (actual->next != nullptr) {
            Node<T>* next = actual->next;
            while (next != nullptr) {
                if (actual->data.getVuelo() > next->data.getVuelo()) {
                    T temp = actual->data;
                    actual->data = next->data;
                    next->data = temp;
                }
                next = next->next;
            }
            actual = actual->next;
        }
    }
};

#endif 
