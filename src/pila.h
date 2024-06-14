#ifndef PILA_H
#define PILA_H
#include <iostream>

template <typename T>
class Pila
{
private:
    struct Nodo
    {
        T data;
        Nodo *next;
    };

    Nodo *top;

public:
    Pila() : top(nullptr) {}
    ~Pila();

    void push(const T &valor);
    void pop();
    T topPila() const;
    bool isEmpty() const;
    void clear();
    int getSize(const Pila<T> &pila);
    T getElement(const Pila<T> &pila, int posicion);
};

template <typename T>
Pila<T>::~Pila()
{
    clear();
}

template <typename T>
void Pila<T>::push(const T &valor)
{
    Nodo *nuevoNodo = new Nodo{valor, top};
    top = nuevoNodo;
}

template <typename T>
void Pila<T>::pop()
{
    if (top != nullptr)
    {
        Nodo *nodoAEliminar = top;
        top = top->next;
        delete nodoAEliminar;
    }
    else
    {
        std::cerr << "Error: La pila está vacía, no se puede pop." << std::endl;
    }
}

template <typename T>
T Pila<T>::topPila() const {
    if (top != nullptr) {
        return top->data;
    } else {
        std::cerr << "Error: La pila está vacía, no se puede obtener la top." << std::endl;
        throw std::runtime_error("La pila está vacía"); // Lanza una excepción en lugar de devolver un valor por defecto
    }
}

template <typename T>
bool Pila<T>::isEmpty() const
{
    return top == nullptr;
}

template <typename T>
void Pila<T>::clear()
{
    while (!isEmpty())
    {
        pop();
    }
}

// Metodo para obtener el tamaño de la pila sin que reciba parametros
template <typename T>
int getSize(const Pila<T> &pila)
{
    int tamano = 0;
    typename Pila<T>::Nodo *nodoActual = pila.top;
    while (nodoActual != nullptr)
    {
        tamano++;
        nodoActual = nodoActual->next;
    }
    return tamano;
}



// Metodo para obtener un elemento de la pila
template <typename T>
T getElement(const Pila<T> &pila, int posicion)
{
    if (posicion < 0)
    {
        std::cerr << "Error: La posición no puede ser negativa." << std::endl;
        return T(); 
    }

    typename Pila<T>::Nodo *nodoActual = pila.top;
    for (int i = 0; i < posicion && nodoActual != nullptr; i++)
    {
        nodoActual = nodoActual->next;
    }

    if (nodoActual != nullptr)
    {
        return nodoActual->data;
    }
    else
    {
        std::cerr << "Error: La posición está fuera de rango." << std::endl;
        return T(); 
    }
};

#endif 
