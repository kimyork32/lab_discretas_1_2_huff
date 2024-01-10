#include <iostream>
#include "menu.h"
#include "grafo.h"

using namespace std;

int main()
{
    int n = 4;
    Grafo grafo(n);
    menu(grafo);
    return 0;
}