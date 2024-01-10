#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Nodo {
    char letra;
    int cantidad;
    Nodo *sig;
    Nodo *izq, *der;
};

void contarLetras(string nombreArchivo, vector<int> &frecuencia) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        exit(EXIT_FAILURE);
    }

    char caracter;
    while (archivo.get(caracter)) {
        if (isalpha(caracter)) {
            frecuencia[caracter - 'a']++;
        }
    }

    archivo.close();
}

void ordenar(Nodo *&lista, Nodo *nuevoNodo) {
    Nodo *actual = lista;
    Nodo *anterior = nullptr;

    while (actual != nullptr && actual->cantidad < nuevoNodo->cantidad) {
        anterior = actual;
        actual = actual->sig;
    }

    if (anterior == nullptr) {
        nuevoNodo->sig = lista;
        lista = nuevoNodo;
    }
    else {
        anterior->sig = nuevoNodo;
        nuevoNodo->sig = actual;
    }
}

Nodo *crearNodo(char letra, int cantidad) {
    Nodo *nuevoNodo = new Nodo;
    nuevoNodo->letra = letra;
    nuevoNodo->cantidad = cantidad;
    nuevoNodo->sig = nullptr;
    nuevoNodo->izq = nullptr;
    nuevoNodo->der = nullptr;

    return nuevoNodo;
}

void arbolHuffman(Nodo *&lista) {
    while (lista->sig != nullptr) {
        Nodo *nodo1 = lista;
        Nodo *nodo2 = lista->sig;

        Nodo *nuevoNodo = crearNodo('$', nodo1->cantidad + nodo2->cantidad);
        nuevoNodo->izq = nodo1;
        nuevoNodo->der = nodo2;

        lista = lista->sig->sig;

        ordenar(lista, nuevoNodo);
    }
}

void generarArchivoDot(Nodo *raiz, ofstream &archivoDot) {
    if (raiz != nullptr) {
        archivoDot << "  \"" << raiz->letra << " (" << raiz->cantidad << ")\"";

        if (raiz->izq != nullptr || raiz->der != nullptr) {
            archivoDot << " [shape=circle]";
        }

        archivoDot << ";\n";

        if (raiz->izq != nullptr) {
            archivoDot << "  \"" << raiz->letra << " (" << raiz->cantidad << ")\" -> \"" << raiz->izq->letra << " (" << raiz->izq->cantidad << ")\" [label=\"0\"];\n";
            generarArchivoDot(raiz->izq, archivoDot);
        }

        if (raiz->der != nullptr) {
            archivoDot << "  \"" << raiz->letra << " (" << raiz->cantidad << ")\" -> \"" << raiz->der->letra << " (" << raiz->der->cantidad << ")\" [label=\"1\"];\n";
            generarArchivoDot(raiz->der, archivoDot);
        }
    }
}

void imprimirArbolGraphviz(Nodo *raiz, const string &nombreArchivo) {
    ofstream archivoDot(nombreArchivo + ".dot");

    if (archivoDot.is_open()) {
        archivoDot << "digraph ArbolHuffman {\n";
        generarArchivoDot(raiz, archivoDot);
        archivoDot << "}\n";
        archivoDot.close();

        system(("dot -Tpng " + nombreArchivo + ".dot -o " + nombreArchivo + ".png").c_str());

        cout << "Arbol de Huffman impreso en " << nombreArchivo << ".png" << endl;
    }
    else {
        cout << "Error al abrir el archivo DOT." << endl;
    }
}

void printList(Nodo *lista) {
    while (lista != nullptr) {
        cout << "Letra: " << lista->letra << ", Cantidad: " << lista->cantidad << endl;
        lista = lista->sig;
    }
}

void decodificar(Nodo *raiz, const string &codigo) {
    Nodo *actual = raiz;

    for (char bit : codigo) {
        if (bit == '0') {
            actual = actual->izq;
        }
        else if (bit == '1') {
            actual = actual->der;
        }

        if (actual->izq == nullptr && actual->der == nullptr) {
            cout << actual->letra;
            actual = raiz;
        }
    }

    cout << endl;
}

int main(){
    string nombreArchivo = "letras.txt";
    vector<int> frecuencia(26, 0);

    contarLetras(nombreArchivo, frecuencia);

    Nodo *listaOrdenada = nullptr;

    for (int i = 0; i < 26; i++) {
        if (frecuencia[i] > 0) {
            Nodo *nuevoNodo = crearNodo('a' + i, frecuencia[i]);
            ordenar(listaOrdenada, nuevoNodo);
        }
    }
    cout << "Lista ordenada por frecuencia:" << endl;
    printList(listaOrdenada);
    arbolHuffman(listaOrdenada);

    imprimirArbolGraphviz(listaOrdenada, "arbol_huffman");

    string W1 = "000";
    cout << "Decodificacion '" << W1 << "': ";
    decodificar(listaOrdenada, W1);

    string W2 = "100011001101";
    cout << "Decodificacion '" << W2 << "': ";
    decodificar(listaOrdenada, W2);

    string W3 = "110001001101";
    cout << "Decodificacion '" << W3 << "': ";
    decodificar(listaOrdenada, W3);

    while (listaOrdenada != nullptr) {
        Nodo *temp = listaOrdenada; 
        listaOrdenada = listaOrdenada->sig;
        delete temp;
    }
    return 0;
}
