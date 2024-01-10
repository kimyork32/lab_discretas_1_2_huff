// grafo.h
#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class Grafo {
private:
    std::vector<std::vector<int>> matrizAdyacencia;

    void MSaveInMpresent() {
        std::ifstream fich("grafoMatrAdy.txt");
        if (!fich.is_open())
        {
            std::cerr << "No se pudo abrir el archivo" << std::endl;
            exit(EXIT_FAILURE);
        }
        std::string linea;
        std::vector<std::vector<int>> Q;
        while (std::getline(fich, linea))
        {
            std::vector<int> fila;
            std::istringstream linea_ss(linea);
            int val;
            while (linea_ss >> val)
            {
                fila.push_back(val);
            }
            Q.push_back(fila);
        }
        fich.close();

        matrizAdyacencia.clear();
        for (const std::vector<int> &fila : Q)
        {
            matrizAdyacencia.push_back(fila);
        }
    }

public:
    Grafo(int size)
    {
        matrizAdyacencia.resize(size, std::vector<int>(size, 0));
        // Otras inicializaciones si es necesario
    }

    void DFS(int v1, int v2, std::vector<int> &camino, std::vector<bool> &visitado)
    {
        visitado[v1] = true;
        camino.push_back(v1);
        if (v1 == v2)
        {
            std::cout << "camino: ";
            for (int i = 0; i < camino.size(); i++)
            {
                std::cout << camino[i];
                if (i < camino.size() - 1)
                    std::cout << " -> ";
            }
            std::cout << std::endl;
        }
        else
        {
            for (int i = 0; i < matrizAdyacencia.size(); i++)
            {
                if (matrizAdyacencia[v1][i] == 1 && !visitado[i])
                {
                    DFS(i, v2, camino, visitado);
                }
            }
        }

        visitado[v1] = false;
        camino.pop_back();
    }

    void graphiz()
    {
        std::ofstream fich("grafo1.dot");

        if (!fich)
        {
            std::cout << "ERROR AL ABRIR" << std::endl;
            exit(EXIT_FAILURE);
        }

        fich << "graph A {"
             << "\n";

        for (int i = 0; i < matrizAdyacencia.size(); i++)
        {
            for (int j = 0; j < matrizAdyacencia.size(); j++)
            {
                if (i > j && matrizAdyacencia[i][j] == 1)
                {
                    fich << " " << j << " -- " << i << ";" << std::endl;
                }
            }
        }
        fich << "}";
        fich.close();

        system("dot -Tpng grafo1.dot -o grafoTest.png");
        system("start grafoTest.png");
    }

    void input(){
        for (int i = 0; i < matrizAdyacencia.size(); i++)
        {
            for (int j = 0; j < matrizAdyacencia.size(); j++)
            {
                if (j > i)
                {
                    std::cout << "M[" << i << "][" << j << "]: ";
                    std::cin >> matrizAdyacencia[i][j];
                    matrizAdyacencia[j][i] = matrizAdyacencia[i][j];
                }
                else if (i == j)
                {
                    matrizAdyacencia[i][j] = 0;
                }
            }
        }
    }

    void print()
    {
        for (const auto &fila : matrizAdyacencia)
        {
            for (const auto &elem : fila)
            {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
    }

    void save()
    {
        std::ofstream fich("grafoMatrAdy.txt");
        if (!fich.is_open())
        {
            std::cerr << "No se pudo abrir el archivo" << std::endl;
            exit(EXIT_FAILURE);
        }

        for (const auto &fila : matrizAdyacencia)
        {
            for (const auto &elem : fila)
            {
                fich << elem << " ";
            }
            fich << std::endl;
        }

        fich.close();
    }

    void modify()
    {
        int f, c, elem;

        std::cout << "f: ";
        std::cin >> f;
        std::cout << "c: ";
        std::cin >> c;

        if (f >= 0 && f < matrizAdyacencia.size() && c >= 0 && c < matrizAdyacencia[0].size())
        {
                std::cout << "M[" << f << "][" << c << "] es " << matrizAdyacencia[f][c] << std::endl;
            std::cout << "nuevo elemento: ";
            std::cin >> elem;
            matrizAdyacencia[f][c] = elem;
            matrizAdyacencia[c][f] = elem;
        }
        else
        {
            std::cout << "error" << std::endl;
        }
    }

    std::vector<std::vector<int>> getMatrizAdyacencia()
    {
        return matrizAdyacencia;
    }

    void importarMatriz()
    {
        MSaveInMpresent();
    }
};

#endif

