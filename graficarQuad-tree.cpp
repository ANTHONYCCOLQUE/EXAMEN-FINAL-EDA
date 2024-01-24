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

// Función para inicializar la matriz de strings
/*
void inicializarMatriz(std::string** matriz, int filas, int columnas) {
    char letra = 'A';
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            matriz[i][j] = letra++;
        }
    }
}
*/

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
                if (i < y*2){
                    if (matrizC[i][x*4] == "*"){
                    break;
                    }
                    matrizP[i][x*4] = "|";
                    matrizC[i][x*4] = "*";
                }

        }
            for (int j = columnas; j >= 0; j--) {
                if (j < x*4){
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

    matrizP[y*2][x*4] = "x";
    matrizC[y*2][x*4] = "*";
}

// Función para liberar la memoria de la matriz de strings
void liberarMatriz(std::string** matriz, int filas) {
    for (int i = 0; i < filas; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

bool esPar(int numero) {
    return numero % 2 == 0;
}


int main() {

  
    int numero = 11;

    int nivel1 = 1;

    int nivel2 = 2;

    // 1

    int x1 ;
    int y1 ;
    x1 = 3;
    y1 = numero -6;

    // 2

    int x2 ;
    int y2 ;
    x2 = 2;
    y2 = numero -7;

    int x3 ;
    int y3 ;
    x3 = 5;
    y3 = numero -2;


    // 3

    int x4 ;
    int y4 ;
    x4 = 6;
    y4 = numero -7;

    int x5 ;
    int y5 ;
    x5 =1;
    y5 = numero -4;


    // 4

    int x8 ;
    int y8 ;
    x8 = 9;
    y8 = numero -1;

    int x9 ;
    int y9 ;
    x9 = 8;
    y9 = numero -9;





    
    int filas = numero*3-(numero-1); //23
    int columnas = numero*5-(numero-1); //45


    // Crear e inicializar la matriz de strings
    std::string** miMatrizP = crearMatriz(filas, columnas);
    std::string** miMatrizC = crearMatriz(filas, columnas);

    inicializarMatrizT(miMatrizP, miMatrizC, filas, columnas);
    inicializarMatrizR(miMatrizP, miMatrizC, filas,  columnas, esPar(1) ,  x1,  y1 ) ;
    imprimirMatriz(miMatrizP, filas, columnas);

    inicializarMatrizR(miMatrizP, miMatrizC, filas,  columnas, esPar(2) ,  x2,  y2 ) ;
    imprimirMatriz(miMatrizP, filas, columnas);
    inicializarMatrizR(miMatrizP, miMatrizC, filas,  columnas, esPar(2) ,  x3,  y3 ) ;
    imprimirMatriz(miMatrizP, filas, columnas);

    inicializarMatrizR(miMatrizP, miMatrizC, filas,  columnas, esPar(3) ,  x4,  y4 ) ;
    imprimirMatriz(miMatrizP, filas, columnas);
    inicializarMatrizR(miMatrizP, miMatrizC, filas,  columnas, esPar(3) ,  x5,  y5 ) ;
    imprimirMatriz(miMatrizP, filas, columnas);

    inicializarMatrizR(miMatrizP, miMatrizC, filas,  columnas, esPar(4) ,  x8,  y8 ) ;
    imprimirMatriz(miMatrizP, filas, columnas);
    inicializarMatrizR(miMatrizP, miMatrizC, filas,  columnas, esPar(4) ,  x9,  y9 ) ;



    // Imprimir la matriz de strings
    imprimirMatriz(miMatrizP, filas, columnas);



    // Liberar la memoria
    liberarMatriz(miMatrizP, filas);
    liberarMatriz(miMatrizC, filas);

    return 0;
}