#include <iostream>
#include "arbolAVL.cpp"
#include "arbolBinario.cpp"
#include "arbolRB.cpp"
#include <iomanip>
#include <windows.h> 

using namespace std;

void menuAVL() {
    AVLTree avlTree;

    int dataToInsert[] = {1,2,3,4,5,6,7,8,9,10};
    int dataSize = sizeof(dataToInsert) / sizeof(dataToInsert[0]);

    for (int i = 0; i < dataSize; i++) {
        avlTree.insert(dataToInsert[i]);
    }

}

void menuBinario() {
    BinaryTree bTree;

    int dataToInsert[] = {10,9,8,7,6,5,4,2};
    int dataSize = sizeof(dataToInsert) / sizeof(dataToInsert[0]);

    for (int i = 0; i < dataSize; i++) {
        bTree.insert(dataToInsert[i]);
    }
    
	}

void menuRB() {
    RedBlackTree rbTree;

    int dataToInsert[] = {10, 5, 3, 8, 12, 11, 14, 2, 7, 9};
    int dataSize = sizeof(dataToInsert) / sizeof(dataToInsert[0]);

    for (int i = 0; i < dataSize; i++) {
        rbTree.insert(dataToInsert[i]);
        //rbTree.visualizeTree();
    }
}

int obtenerAnchoConsola() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwSize.X;
}

void imprimirLinea() {
    cout << setfill('=') << setw(obtenerAnchoConsola()) << "=" << setfill(' ') << endl;
}

void imprimirTitulo(const string& titulo) {
    int anchoConsola = obtenerAnchoConsola();
    int espacios = (anchoConsola - titulo.length()) / 2;

    cout << setw(espacios + titulo.length()) << titulo << endl;
}

int main() {
    int opcion;
    do {
        system("cls"); // Limpia la consola (Windows)
        imprimirLinea();
        imprimirTitulo("ESTRUCTURA DE DATOS AVANZADOS");
        imprimirTitulo("PROYECTO TRABAJO FINAL");
        imprimirLinea();
        cout << "\nMenu Principal:" << endl;
        cout << "1. Visualizar Arbol AVL" << endl;
        cout << "2. Visualizar Arbol Binario" << endl;
        cout << "3. Visualizar Arbol Rojo-Negro" << endl;
        cout << "4. Salir" << endl;
        imprimirLinea();
        cout << "\nElige una opcion: ";
        cin >> opcion;
		system("cls");
        switch (opcion) {
            case 1:
                menuAVL();
                break;
            case 2:
                menuBinario();
                break;
            case 3:
                menuRB();
                break;
            case 4:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción no válida" << endl;
        }
    } while (opcion != 4);

    return 0;
}