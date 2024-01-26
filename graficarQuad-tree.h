#include <iostream>
#include <string>
#include <cstdlib> 

// Función para crear una matriz de strings
std::string** crearMatrizQ(int filas, int columnas) {
    std::string** matriz = new std::string*[filas];
    for (int i = 0; i < filas; ++i) {
        matriz[i] = new std::string[columnas];
    }
    return matriz;
}

// Función para imprimir la matriz de strings

void imprimirMatrizQ(std::string** matriz, int filas, int columnas) {
    std::cout << "Matriz de strings:" << std::endl;
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


void inicializarMatrizTQ(std::string** matrizP,std::string** matrizC, int filas, int columnas) {
int cont1 =0;
int cont2a =0;
int cont2b =0;
    for (int i = 0; i < filas; ++i) {
        cont1 = 0;
        //cont2 = 0;
        for (int j = 0; j < columnas; ++j) { 
        //cont2 = 0;
            
            if( i == 0 || i == filas -1){
                matrizP[i][j] = "-";
                matrizC[i][j] = "*";
                
                if (j % 4 == 0 ){
                     matrizP[i][j] = "+";
                     matrizC[i][j] = "*";
                }
     
                if (j ==3+cont1 ){

                     matrizP[i][j] = "*";
                     matrizC[i][j] = "*";
                     cont1 = cont1 +4;
                     
                }

                
            } else{
                if ((j == 0 || j == columnas -1 ) && i>0 && i<filas-1){
                    matrizP[i][j] = "|";
                    matrizC[i][j] = "*";
                    
                    if (i % 4 == 0 ){
                        matrizP[i][j] = "+";
                        matrizC[i][j] = "*";
                    }
                    if ((i == 1+cont2a && j==0) || (i == 1+cont2b && j==columnas -1 )){
                        matrizP[i][j] = "*";
                        matrizC[i][j] = "*";
                        if (j==0){
                         cont2a = cont2a+4;
                        }
                        if (j==columnas -1){
                         cont2b = cont2b+4;
                        }
                    }
     
                }else{
                matrizP[i][j] = " ";
                matrizC[i][j] = " ";
                }
            }
       
        }
    } 
}


void inicializarMatrizRQ(std::string** matrizP,std::string** matrizC, int filas, int columnas, int x, int y ) {

        for (int i = 0; i < filas; ++i) {
                if (i > y*4){
                    if (matrizC[i][x*4] == "*"){
                    break;
                    }
                    matrizP[i][x*4] = "|";
                    matrizC[i][x*4] = "*";
                }
        }
        for (int i = filas; i >= 0; i--) {
                if (i < y*4){
                    if (matrizC[i][x*4] == "*"){
                    break;
                    }
                    matrizP[i][x*4] = "|";
                    matrizC[i][x*4] = "*";
                }
        }
    

            for (int j = columnas; j >= 0; j--) {
                if (j < x*4){
                    if (matrizC[y*4][j] == "*"){
                    break;
                    }
                    matrizP[y*4][j] = "-";
                    matrizC[y*4][j] = "*";
                }
            }
            for (int j = 0; j < columnas; ++j) {
                if (j > x*4){
                    if (matrizC[y*4][j] == "*"){
                    break;
                    }
                    matrizP[y*4][j] = "-";
                    matrizC[y*4][j] = "*";
                }
            }
    
    matrizP[y*4][x*4] = "+";
    matrizC[y*4][x*4] = "*";
}


void liberarMatrizQ(std::string** matriz, int filas) {
    for (int i = 0; i < filas; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

void inicializarPQ(std::string** matrizP,std::string** matrizC, int x, int y ) {
    matrizP[(y*4)-3][(x*4)-1] = "x";
    matrizC[(y*4)-3][(x*4)-1] = "*";
}

