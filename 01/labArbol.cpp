#include <iostream>
#include <fstream>
using namespace std;
struct nodo{
    int nro;
    struct nodo *izq, *der;
};

typedef struct nodo *ArbolBinario;

ArbolBinario crearNodo(int x) {
    ArbolBinario nuevoNodo = new(struct nodo);
    nuevoNodo->nro = x;
    nuevoNodo->izq = NULL;
    nuevoNodo->der = NULL;
    return nuevoNodo;
}

void insertar(ArbolBinario &arbol, int x) {
    if(arbol==NULL)
    arbol = crearNodo(x);
    else if(x < arbol->nro)
    insertar(arbol->izq, x);
    else if(x > arbol->nro)
    insertar(arbol->der, x);
}

void preOrden(ArbolBinario arbol) {
    if(arbol!=NULL) {
        cout << arbol->nro <<" ";
        preOrden(arbol->izq);
        preOrden(arbol->der);
    }
}

void enOrden(ArbolBinario arbol) {
    if(arbol!=NULL) {
        enOrden(arbol->izq);
        cout << arbol->nro << " ";
        enOrden(arbol->der);
    }
}

void postOrden(ArbolBinario arbol) {
    if(arbol!=NULL) {
        postOrden(arbol->izq);
        postOrden(arbol->der);
        cout << arbol->nro << " ";
    }
}
//recorriendo arbol
void generar(ArbolBinario arbol, ofstream& fich) {
    if (arbol != NULL) {
        fich << "  " << arbol->nro << ";\n";
        if (arbol->izq != NULL) {
            fich << "  " << arbol->nro << " -- " << arbol->izq->nro << ";\n";
            generar(arbol->izq, fich);
        }
        if (arbol->der != NULL) {
            fich << "  " << arbol->nro << " -- " << arbol->der->nro << ";\n";
            generar(arbol->der, fich);
        }
    }
}

int main() {
    ArbolBinario arbol = NULL;
    cout << "\n ...EJEMPLO DE ARBOL BINARIO... \n";

    // LEYENDO FICHERO
    ifstream archivo("dataArbol.txt");
    while (!archivo.eof()) {
        int dato;
        archivo >> dato;
        insertar(arbol, dato);
    }
    archivo.close();

    // GENERAR ARCHIVO DOT
    ofstream fich("arbol1.dot");
        if (!fich){
            std::cout << "ERROR AL ABRIR" << std::endl;
            exit(EXIT_FAILURE);
        }

        fich << "graph A {" << "\n";
        generar(arbol, fich);
        fich << "}";
        fich.close();
        system("dot -Tpng arbol1.dot -o arbolTest1.png");
        system("start arbolTest1.png");

    cout << "\nRecorridos del ArbolBinario\n";
    cout << "\nEn orden : "; enOrden(arbol);
    cout << "\nPre Orden : "; preOrden(arbol);
    cout << "\nPost Orden : "; postOrden(arbol);
    cout << endl << endl;
    return 0;
}  

