#ifndef LISTADOBLE_H
#define LISTADOBLE_H


#include <iostream>
#include <fstream>
using namespace std;

class NodoDoble{
public:
    string data;
    NodoDoble *next;
    NodoDoble *prev;
    NodoDoble(string data){
        this->data=data;
        next = NULL;
        prev = NULL;
    }
};

class ListaDoble {
private:
    NodoDoble *first;
    NodoDoble *last;
    int size;

public:
    ListaDoble() {
        first = NULL;
        last = NULL;
        size = 0;
    }

    void print() {
        NodoDoble *temp = first;
        int i = 1;
        while (temp != NULL) {
            cout << "Posicion "<<i<<" :"<<temp->data << endl;
            temp = temp->next;
            i++;
        }
    }

    void printEditor() {
        NodoDoble *temp = first;
        int i = 1;
        int b = 98;
        while (temp != NULL) {
            cout <<temp->data;
            if(i==b){
                b += 98;
                cout<<"\n";
                char x = 186;
                cout<<x;
            }
            temp = temp->next;
            i++;
        }
    }

    void deleteList(){
        NodoDoble *next;
        while (first!=NULL){
            next = first->next;
            delete first;
            first = next;
        }
    }

    void prepend(string data) {
        NodoDoble *n = new NodoDoble(data);
        if (first == NULL) {
            first = n;
            last = n;
        } else {
            first->prev=n;
            n->next=first;
            first = n;
        }
        size++;
    }

    void append(string data) {
        NodoDoble *n = new NodoDoble(data);
        if (first == NULL) {
            first = n;
            last = n;
        } else {
            last->next = n;
            n->prev= last;
            last = n;
        }
        size++;
    }

    void insertAt(int pos, string data){
        if(pos>size+1 || pos<1)
        {

            cout<<pos;return;}
        else if (pos==1){
            prepend(data);}
        else if (pos==size+1)
            append(data);
        else if (first!=NULL){
            NodoDoble *n = new NodoDoble(data);
            NodoDoble *cur = first;
            for (int i = 0; i < pos; ++i) {
                cur=cur->next;
            }
            cur->prev->next=n;
            n->prev=cur->prev;
            n->next=cur;
            cur->prev=n;
            size++;
        }
    }

    void removeFirst() {
        if (first->next != NULL) {
            delete first;
            first = NULL;
            last = NULL;
            --size;
        }else if(first != NULL){
            first = first->next;
            delete first->prev;
            first->prev = NULL;
            --size;
        }
    }

    void  removeSpecific(int pos){
        if(pos> size || pos<1)
            return;
        else if (pos == 1)
            removeFirst();
        else if (pos == size)
           removeLast();
        else if (first != NULL){
            NodoDoble *cur= first;
            for (int i = 0; i < pos; ++i) {
                cur = cur->next;
            }
            cur->prev->next= cur->next;
            cur->next->prev=cur->prev;
            delete cur;
            size--;
        }
    }

    void removeLast() {
        if (first->next == NULL) {
            removeFirst();
        } else if (first != NULL) {
            last = last->prev;
            delete last->next;
            last->next =NULL;
            size--;
        }
    }

    int  getSize(){
        return size;
    }

    string getData(int pos){
        if(pos> size || pos<1){
            return "";
        }

        else if (pos == 1)
            return first->data;
        else if (pos == size)
            return last->data;
        else if (first != NULL){
            NodoDoble *cur= first;
            for (int i = 0; i < pos; ++i) {
                cur = cur->next;
            }
            return cur->data;


        }
    }

    /**/
    bool buscarCoincidencias(string text, string reemplazar){
        NodoDoble *temp = first;
        int i = 0;
        int contador = 0;
        while (temp != NULL) {
            i++;
            char caracter = text[contador];
            string s(1,caracter);
            if(temp->data==s){
                contador++;
            }else{
                contador=0;
            }
            if(contador==text.size()){
                eliminarBloque(contador, i);
                contador = 0;
                reemplazarBloque(reemplazar, i);
            }
            temp = temp->next;

        }
        return false; 
    }


    void eliminarBloque(int cantidad, int pos){
        for(int i=0; i<cantidad;i++){
            removeSpecific(pos-1);
        }
    }

    void reemplazarBloque(string text, int pos){
        for(int i=0; i<text.size();i++){
            char caracter = text[i];
            string s(1,caracter);
            insertAt(pos+i,s);
        }
    }

    void generarGraphvizListaDoble(){
        string cadena ="";
        cadena += "digraph G{\n";


        int n = 1;
        NodoDoble * nodoAux = first;
        for (int i = 1; i<size+1;i++)
        {
            cadena +="p";
            string str= to_string(i);
            cadena +=str;
            cadena+="[label = \"";
            cadena+=nodoAux->data;
            cadena+="\" fontname=\"Times New Roman\" shape=parallelogram color=darkorange2];\n";
            n++;
            nodoAux =  nodoAux->next;
        }
        int aux = n;
        int aux2 = n + 1;
        n = 1;


        for (int i = 0; i < aux-2; i++)
        {
            cadena += "p";
            string st= to_string(n);
            cadena +=st;
            cadena+=":c->p";
            string str= to_string(n+1);
            cadena +=str;
            cadena+=";\n";
            n++;
        }

        for (int i = 0; i < aux-2; i++)
        {
            cadena += "p";
            string st= to_string(n);
            cadena +=st;
            cadena+=":c->p";
            string str= to_string(n-1);
            cadena +=str;
            cadena+=";\n";
            n--;
        }

        cadena += "}";
        
         ofstream archivo;
         archivo.open("C:\\Users\\PC\\Desktop\\Bato\\u\\u\\Vacaciones 5\\EDD\\LAB\202202481_EDD_Practica\\edd.txt",ios::out);
         if(archivo.fail()){

             cout<<"no jala el archivo";
             exit(1);
         }
        else{
         archivo<<cadena;
         archivo.close();

         system("dot -Tpng C:\\Users\\PC\\Desktop\\Bato\\u\\u\\Vacaciones 5\\EDD\\LAB\202202481_EDD_Practica\\edd.txt -o C:\\Users\\PC\\Desktop\\Bato\\u\\u\\Vacaciones 5\\EDD\\LAB\202202481_EDD_Practica\\edd.png");
        }
    }

};



#endif // LISTADOBLE_H