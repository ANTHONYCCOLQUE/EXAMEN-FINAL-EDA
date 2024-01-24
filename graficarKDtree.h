#include <iostream>
#include <string>

// Función para crear una matriz de strings
std::string** crearMatriz(int filas, int columnas) {
    std::string** matriz = new std::string*[filas];
    for (int i = 0; i < filas; ++i) {
        matriz[i] = new std::string[columnas];
    }
    return matriz;
}

// Función para imprimir la matriz de strings

void imprimirMatriz(std::string** matriz, int filas, int columnas) {
    std::cout << "Matriz de strings:" << std::endl;
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


void inicializarMatrizT(std::string** matrizP,std::string** matrizC, int filas, int columnas) {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) { 
            if( i == 0 || i == filas -1){
                matrizP[i][j] = "-";
                matrizC[i][j] = "*";
                
                if (j % 4 == 0 ){
                     matrizP[i][j] = "+";
                     matrizC[i][j] = "*";
                }

                
            } else{
                if ((j == 0 || j == columnas -1 ) && i>0 && i<filas-1){
                    matrizP[i][j] = "|";
                    matrizC[i][j] = "*";
                    
                    if (i % 2 == 0 ){
                        matrizP[i][j] = "+";
                        matrizC[i][j] = "*";
                    }
                }else{
                matrizP[i][j] = " ";
                matrizC[i][j] = " ";
                }
            }
        }
    } 
}


void inicializarMatrizR(std::string** matrizP,std::string** matrizC, int filas, int columnas, bool is_Par, int x, int y ) {
    if (is_Par == false){
        for (int i = 0; i < filas; ++i) {
                if (i > y*2){
                    if (matrizC[i][x*4] == "*"){
                    break;
                    }
                    matrizP[i][x*4] = "|";
                    matrizC[i][x*4] = "*";
                }
        }
        for (int i = filas; i >= 0; i--) {
                if (i <= y*2){
                    if (matrizC[i][x*4] == "*"){
                    break;
                    }
                    matrizP[i][x*4] = "|";
                    matrizC[i][x*4] = "*";
                }
        }
    }
    if(is_Par == true){
            for (int j = columnas; j >= 0; j--) {
                if (j <= x*4){
                    if (matrizC[y*2][j] == "*"){
                    break;
                    }
                    matrizP[y*2][j] = "-";
                    matrizC[y*2][j] = "*";
                }
            }
            for (int j = 0; j < columnas; ++j) {
                if (j > x*4){
                    if (matrizC[y*2][j] == "*"){
                    break;
                    }
                    matrizP[y*2][j] = "-";
                    matrizC[y*2][j] = "*";
                }
            }
    }
    matrizP[y*2][x*4] = "x";
}


void liberarMatriz(std::string** matriz, int filas) {
    for (int i = 0; i < filas; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

bool esPar(int numero) {
    return numero % 2 == 0;
}
