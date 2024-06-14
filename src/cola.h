#ifndef COLA_H
#define COLA_H
#include <iostream>
#include <stdexcept>

template <typename T>
class Cola {
private:
    class Nodo {
    public:
        T value;
        Nodo* next;

        Nodo(T val) : value(val), next(nullptr) {}
    };

    Nodo* front;
    Nodo* rear;
    int size;

public:
    // Constructor
    Cola() : front(nullptr), rear(nullptr), size(0) {}

    ~Cola() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }

    void enqueue(const T& value) {
        Nodo* nuevoNodo = new Nodo(value);
        if (isEmpty()) {
            front = rear = nuevoNodo;
        } else {
            rear->next = nuevoNodo;
            rear = nuevoNodo;
        }
        size++;
    }

    T dequeue() {
        if (isEmpty()) {
            throw std::out_of_range("La cola está vacía");
        }
        Nodo* nodoAEliminar = front;
        T value = nodoAEliminar->value;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete nodoAEliminar;
        size--;
        return value;
    }

    T getElement(int pos) const {
        if (pos < 0 || pos >= size) {
            throw std::out_of_range("Posición inválida");
        }
        Nodo* actual = front;
        for (int i = 0; i < pos; i++) {
            actual = actual->next;
        }
        return actual->value;
    }

        T getFront() const {
        if (isEmpty()) {
            throw std::out_of_range("La cola está vacía");
        }
        return front->value;
    }
};
#endif 
