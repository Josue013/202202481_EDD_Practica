#ifndef CIRCULARDOBLE_H
#define CIRCULARDOBLE_H
#include <iostream>
#include <fstream>
using namespace std;

class NodoDoble{
public:
    int x;
    int y;
    NodoDoble *next;
    NodoDoble *prev;
    NodoDoble(int x, int y){
        this->x =x;
        this->y =y;
        next = NULL;
        prev = NULL;
    }
};

class CircularDoble
{
public:

    NodoDoble *first;
    NodoDoble *last;
    int size;


    CircularDoble(){
        first = NULL;
        last = NULL;
        size = 0;
    };

    void agregarFinal(int x, int y) {
        NodoDoble *n = new NodoDoble(x, y);
        if (first == NULL) {
            first = n;
            last = n;
            first->next = last;
            first->prev = last;
            last->prev = first;
            last->next = first;
        } else {
            last->next = n;
            n->prev= last;
            last = n;
            last->next = first;
            first->prev = last;
        }
        size++;
    }

    void print() {
        NodoDoble *temp = first;
        int i = 1;
        do{
            cout << "Posicion "<<i<<" :(x)"<<temp->x<<" (y)"<<temp->y<< endl;
            temp = temp->next;
            i++;
        }
        while (temp != first);
    }

    int buscarDoble(int x, int y){
        NodoDoble  *temp = first;
        do{
            if(temp !=NULL){
                if(temp->x == x && temp->y==y){
                    return 2;
                }
                temp = temp->next;
            }
        }while(temp != first);

        return 1;
    }

    int buscarTriple(int x, int y){
        NodoDoble  *temp = first;
        do{
            if(temp !=NULL){
                if(temp->x == x && temp->y==y){
                    return 3;
                }
                temp = temp->next;
            }
        }while(temp != first);

        return 1;
    }
};



class NodoCircular{
public:
    string data;
    bool find;
    NodoCircular *next;
    NodoCircular *prev;
    NodoCircular(string data){
        this->data = data;
        next = NULL;
        prev = NULL;
        find = false;
    }
};


class CircularDiccionario
{
public:

    NodoCircular *first;
    NodoCircular *last;
    int size;


    CircularDiccionario(){
        first = NULL;
        last = NULL;
        size = 0;
    };

    void agregarFinal(string data) {
        NodoCircular *n = new NodoCircular(data);
        if (first == NULL) {
            first = n;
            last = n;
            first->next = last;
            first->prev = last;
            last->prev = first;
            last->next = first;
        } else {
            last->next = n;
            n->prev= last;
            last = n;
            last->next = first;
            first->prev = last;
        }
        size++;
    }

    void reiniciar(){
        NodoCircular *temp = first;
        int i = 1;
        do{
            if(temp != NULL){
                temp->find = false;
                temp = temp->next;
                i++;
            }
        }
        while (temp != first);
    }

    void print() {
        NodoCircular *temp = first;
        int i = 1;
        do{
            cout << "Posicion "<<i<<" :"<<temp->data<< endl;
            temp = temp->next;
            i++;
        }
        while (temp != first);
    }

    void graficar(){
        NodoCircular *temp = first;
        string graph = "digraph f{\nrankdir = LR;\n";
        int i = 0 ;
        do{
          graph += to_string(i)+"[shape = box color = darkorchid1 label=\""+temp->data+"\"];\n";
          temp = temp->next;
          i++;
        }while(temp != first);

        for(int x = 0; x<size-1;x++){
            graph += to_string(x)+"->"+to_string(x+1)+";\n";
            graph += to_string(x+1)+"->"+to_string(x)+";\n";
        }

        graph += to_string(i-1)+"->0"+";\n";
        graph += "0->"+to_string(i-1)+";\n}";
        ofstream archivo;
         archivo.open("C:\\Users\\PC\\Desktop\\Bato\\u\\u\\Vacaciones 5\\EDD\\LAB\202202481_EDD_Practica\\edd.txt",ios::out);
         if(archivo.fail()){

             cout<<"no jala el archivo";
             exit(1);
         }
        else{
         archivo<<graph;
         archivo.close();

         system("dot -Tpng C:\\Users\\PC\\Desktop\\Bato\\u\\u\\Vacaciones 5\\EDD\\LAB\202202481_EDD_Practica\\edd.txt -o C:\\Users\\PC\\Desktop\\Bato\\u\\u\\Vacaciones 5\\EDD\\LAB\202202481_EDD_Practica\\ListaCircularDoble.png");

        }
    }

};
#endif // CIRCULARDOBLE_H