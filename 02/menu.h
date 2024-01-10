#ifndef MENU_H
#define MENU_H

#include "grafo.h"

void menu(Grafo& grafo) {
    bool quit = false;
    int opc;
    std::vector<int> camino;
    std::vector<bool> visitado(grafo.getMatrizAdyacencia().size(), false);

    while (!quit) {
        std::cout << "\nMENU:\n"
            << "1) Imprimir matriz\n"
            << "2) Nueva matriz\n"
            << "3) Modificar valor\n"
            << "4) Exportar matriz\n"
            << "5) Importar matriz\n"
            << "6) Graphiz\n"
            << "7) DFS\n"
            << "8) Salir\n"
            << "Ingrese una opcion: ";
        std::cin >> opc;

        switch (opc) {
            case 1:
                std::cout << "Matriz actual:\n";
                grafo.print();
                break;

            case 2:
                std::cout << "Inserte valores:\n";
                grafo.input();
                break;

            case 3:
                grafo.modify();
                break;

            case 4:
                std::cout << "Matriz guardada\n";
                grafo.save();
                break;

            case 5:
                std::cout << "Matriz importada\n";
                grafo.importarMatriz();
                break;

            case 6:
                grafo.graphiz();
                break;
            case 7:
                int v1, v2;
                std::cout << "v0: ";
                std::cin >> v1;
                std::cout << "vf: ";
                std::cin >> v2;
                camino.clear();
                visitado.assign(grafo.getMatrizAdyacencia().size(), false);
                grafo.DFS(v1, v2, camino, visitado);
                break;
            case 8:
                quit = true;
                break;
            default:
                std::cout << "Opción inválida" << std::endl;
        }
    }
}

#endif