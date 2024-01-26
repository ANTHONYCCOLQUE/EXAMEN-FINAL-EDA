#include <iostream>
#include <vector>
#include "arbolAVL.cpp"
#include "arbolBinario.cpp"
#include "arbolRB.cpp"
#include "KDtree.cpp"
#include <iomanip>
#include "quadtree.cpp"
#include <windows.h> 
#include <chrono>

using namespace std;

void menuAVL() {
    int opc;

  
    do {
    	AVLTree avlTree;  // Mueve la creación del objeto fuera del bucle
		AVLTree avlree2;
		vector<int> randomNumbersAVL;
        // Mostrar título del menú AVL
        cout << "==============================" << endl;
        cout << "       Menu Arbol AVL" << endl;
        cout << "==============================" << endl;

        // Mostrar opciones
        cout << "1. Ingresar datos manualmente" << endl;
        cout << "2. Ingresar datos aleatoriamente" << endl;
        cout << "3. Volver al Menu Principal" << endl;
		cout << "==============================" << endl;
        cout << "Elige una opcion: ";
        cin >> opc;
        system("cls");

        switch (opc) {
        case 1:
            // AVL MANUAL
            int n, dato;

            cout << "Digite cantidad de digitos: ";
            cin >> n;

            for (int i = 0; i < n; i++) {
                cout << "Inserte dato: ";
                cin >> dato;
                avlTree.insert(dato);
            }
            break;

        case 2:
            //avl bTree2;
            int count; 
			cout<< "Ingrese cantidad de numeros aleatorios a generar: ";
			cin >> count;
		    randomNumbersAVL= generateRandomNumbersAVL(count);
			
			cout<<" \nNumeros aleatorios generados: ";
			cout<<"[ ";
			for (int i = 0 ; i < count ; i++){
				cout << randomNumbersAVL[i] <<" - ";
			}
			cout<<" ]\n";
		    
		    
		    for (int i = 0; i<randomNumbersAVL.size(); i++){
		    	avlTree.insert(randomNumbersAVL[i]);
			}

            break;

        case 3:

            cout << "Saliendo...";
            break;

        default:
            cout << "Opcion NO valida !!\n\n";
        }

    } while (opc != 3);

}



void menuBinario() {
    int opc;

    
    do {
    	BinaryTree bTree;  // Mueve la creación del objeto fuera del bucle
		BinaryTree bTree2;
    	vector <int> num;
        cout << "==============================" << endl;
        cout << "       Menu Arbol Binario" << endl;
        cout << "==============================" << endl;

        // Mostrar opciones
        cout << "1. Ingresar datos manualmente" << endl;
        cout << "2. Ingresar datos aleatoriamente" << endl;
        cout << "3. Volver al Menu Principal" << endl;
		cout << "==============================" << endl;
        cout << "Elige una opcion: ";
        cin >> opc;
        system("cls");

        switch (opc) {
        case 1:
            // binary MANUAL
            int n, dato;

            cout << "Digite cantidad de digitos: ";
            cin >> n;

            for (int i = 0; i < n; i++) {
                cout << "Inserte dato: ";
                cin >> dato;
                bTree.insert(dato);
            }
            break;

        case 2:
            //BinaryTree bTree2;
            int count;
            cout << "Ingrese la cantidad de numeros aleatorios a generar: ";
            cin >> count;
			
			
			
			cout<< "\nDatos generados aleatoriamente: [ ";
			//for ( int i = 0; i < count ; i++){
			//	num.push_back(count);
			//}
			//for ( int i = 0; i < count ; i++){
		//		cout<<numbersF[i]<<", ";
			//}
			
			
			
            bTree2.insertRandomNumbers(count);

            break;

        case 3:

            cout << "Saliendo...";
            break;

        default:
            cout << "Opcion NO valida !!\n\n";
        }

    } while (opc != 3);
}


void menuRB() {
    int opc;
	
    do {
    	RedBlackTree rbTree;
   	 	RedBlackTree rbTree2;
		vector<int> randomNumbers;
        cout << "==============================" << endl;
        cout << "      Menu Arbol Red-Black" << endl;
        cout << "==============================" << endl;

        // Mostrar opciones
        cout << "1. Ingresar datos manualmente" << endl;
        cout << "2. Ingresar datos aleatoriamente" << endl;
        cout << "3. Volver al Menu Principal" << endl;
		cout << "==============================" << endl;
        cout << "Elige una opcion: ";
        cin >> opc;
        system("cls");

        switch (opc) {
        case 1:
            // AVL MANUAL
            int n, dato;

            cout << "Digite cantidad de digitos: ";
            cin >> n;

            for (int i = 0; i < n; i++) {
                cout << "Inserte dato: ";
                cin >> dato;
                rbTree.insert(dato);
            }
            break;

        case 2:
            //RB RbTree2;
            int count; 
			cout<< "Ingrese cantidad de numeros aleatorios a generar: ";
			cin >> count;
		    randomNumbers = generateRandomNumbersRB(count);
			
			cout<<" \nNumeros aleatorios generados: ";
			cout<<"[ ";
			for (int i = 0 ; i < count ; i++){
				cout << randomNumbers[i] <<" - ";
			}
			cout<<" ]\n";
		    
		    
		    for (int i = 0; i<randomNumbers.size(); i++){
		    	rbTree2.insert(randomNumbers[i]);
			}

            break;

        case 3:

            cout << "Saliendo...";
            break;

        default:
            cout << "Opcion NO valida !!\n\n";
        }

    } while (opc != 3);

}
void menuKdTree(){
	int opc;
	
	
    do {
    	KDTree tree;
		KDTree tree2;
		vector<int> randomNumbers;
		
		
		int tamanoMatriz = 22;
			
	    //tamaño de la matriz en conslola 
	    int filas = tamanoMatriz*3-(tamanoMatriz-1); 
	    int columnas = tamanoMatriz*5-(tamanoMatriz-1);
	
		 //crear las matrices
	    std::string** miMatrizP = crearMatriz(filas, columnas);
	    std::string** miMatrizC = crearMatriz(filas, columnas);
	
	    // se crea el marco de la matriz
	    inicializarMatrizT(miMatrizP, miMatrizC, filas, columnas);
    	
        cout << "==============================" << endl;
        cout << "         Menu KdTree" << endl;
        cout << "==============================" << endl;

        // Mostrar opciones
        cout << "1. Ingresar datos manualmente" << endl;
        cout << "2. Ingresar datos aleatoriamente" << endl;
        cout << "3. Volver al Menu Principal" << endl;
		cout << "==============================" << endl;
        cout << "Elige una opcion: ";
        cin >> opc;
        system("cls");

        switch (opc) {
        case 1:
            // kdtree MANUAL	    
		    
		    int cant, x1, y1;
			cout <<"Digite cantidad de puntos a insertar: ";
		    cin >> cant;
		    
		    for (int i = 0; i < cant; i++){
		    	cout <<"Digite valor de x"<<i+1<<": ";
		    	cin >> x1;
		    	cout << "\nDigite valor de y"<<i+1<<": ";
		    	cin >> y1;
		    	
		    	cout << "\nInsertando ("<< x1 << "," << y1 <<") \n";
				
				tree.insert(Point(x1, y1));
			    Point queryPoint1(x1, y1);
			    int level1 = tree.getLevel(queryPoint1);
			    inicializarMatrizR(miMatrizP, miMatrizC, filas,  columnas, esPar(level1+1) ,  x1,  tamanoMatriz -y1 ) ;
			    cout << "Insertando ("<< x1 << "," << y1 <<" ) \n";
			    imprimirMatriz(miMatrizP, filas, columnas);
			    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Espera a que el usuario presione Enter
		    	
			}
		    
		    // Liberar la memoria
		    liberarMatriz(miMatrizP, filas);
		    liberarMatriz(miMatrizC, filas);
		    
            break;

        case 2:
			
			int count; 
			cout<< "Ingrese cantidad de puntos aleatorios a generar: ";
			cin >> count;
			
			count = count * 2;
			
		    randomNumbers = generateRandomNumbers(count);
			
			cout<<" \nPuntos aleatorios generados: ";
			cout<<"[ ";
			for (int i = 0 ; i < count ; i=i+2){
				cout << " ("<<randomNumbers[i]<<","<<randomNumbers[i+1]<<"); ";
			}
			cout<<" ]\n";
		    
		    
			for (int i=0 ; i< count; i=i+2){
				int x1 = randomNumbers[i];
				int y1 = randomNumbers[i+1];
				
				cout << "Insertando ("<< x1 << "," << y1 <<") \n";
				
				tree2.insert(Point(x1, y1));
			    Point queryPoint1(x1, y1);
			    int level1 = tree2.getLevel(queryPoint1);
			    inicializarMatrizR(miMatrizP, miMatrizC, filas,  columnas, esPar(level1+1) ,  x1,  tamanoMatriz -y1 ) ;
			    cout << "Insertando ("<< x1 << "," << y1 <<" ) \n";
			    imprimirMatriz(miMatrizP, filas, columnas);
			    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Espera a que el usuario presione Enter
			}
			
			// Liberar la memoria
		    liberarMatriz(miMatrizP, filas);
		    liberarMatriz(miMatrizC, filas);

            break;

        case 3:

            cout << "Saliendo...";
            break;

        default:
            cout << "Opcion NO valida !!\n\n";
        }

    } while (opc != 3);
}

void menuQuadTree() {
    int opc;
    QuadtreeNode quadtree(0, 0, 16, 16);
    QuadtreeNode quadtree2(0, 0, 16, 16);
    int tamanoMatriz = 16;
    int filas = tamanoMatriz * 5 - (tamanoMatriz - 1);
    int columnas = tamanoMatriz * 5 - (tamanoMatriz - 1);
    std::string** miMatrizP = crearMatriz(filas, columnas);
    std::string** miMatrizC = crearMatriz(filas, columnas);
	vector<PointQ> randomPoints;
    do {
        inicializarMatrizTQ(miMatrizP, miMatrizC, filas, columnas);
        cout << "==============================" << endl;
        cout << "        Menu QuadTree" << endl;
        cout << "==============================" << endl;

        // Mostrar opciones
        cout << "1. Ingresar datos manualmente" << endl;
        cout << "2. Ingresar datos aleatoriamente" << endl;
        cout << "3. Volver al Menu Principal" << endl;
		cout << "==============================" << endl;
        cout << "Elige una opcion: ";
        cin >> opc;
        system("cls");

        switch (opc) {
            case 1:
                int cantidadDePuntos;
                cout << "Ingrese la cantidad de puntos: ";
                cin >> cantidadDePuntos;

                for (int i = 0; i < cantidadDePuntos; ++i) {
                    double x, y;
                    cout << "Ingrese las coordenadas para el punto " << (i + 1) << " (x y): ";
                    cin >> x >> y;
                    quadtree.insert(PointQ(x, y));
                    inicializarPQ(miMatrizP, miMatrizC, x + 1, abs(y + 1 - (tamanoMatriz + 1)));
                    Rangos3(miMatrizP, miMatrizC, filas, columnas, tamanoMatriz, quadtree);
                    imprimirMatrizQ(miMatrizP, filas, columnas);
                }
                break;

            case 2:
                int count;
                cout << "Ingrese cantidad de puntos aleatorios a generar: ";
                cin >> count;
                randomPoints = generateRandomPoints(count, 15, 15);
                cout << "\nPuntos aleatorios generados: [ ";
                for (const auto& punto : randomPoints) {
                    cout << "(" << punto.x << "," << punto.y << "); ";
                    //quadtree2.insert(PointQ(punto.x, punto.y));  // Insertar el punto en el Quadtree
                }
                cout << "]\n";
                
                for (const auto& punto : randomPoints) {
                    quadtree2.insert(PointQ(punto.x, punto.y));
					inicializarPQ(miMatrizP, miMatrizC, punto.x + 1, abs(punto.y + 1 - (tamanoMatriz + 1)));
                    Rangos3(miMatrizP, miMatrizC, filas, columnas, tamanoMatriz, quadtree2);
                    cout << "Insertando (" << punto.x << "," << punto.y << " )\n";
                    imprimirMatrizQ(miMatrizP, filas, columnas);
                    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Espera a que el usuario presione Enter
                	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
                break;

            case 3:
                cout << "Saliendo...";
                break;

            default:
                cout << "Opcion NO valida !!\n\n";
        }
    } while (opc != 3);

    liberarMatrizQ(miMatrizP, filas);
    liberarMatrizQ(miMatrizC, filas);
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
        cout << "4. Visualizar KdTree " << endl;
        cout << "5. Visualizar QuadTree "<< endl;
        cout << "6. Salir" << endl;
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
                menuKdTree();
                break;
            case 5:
            	menuQuadTree();
            case 6:
            	cout << "Saliendo..." << endl;
            	break;
            default:
                cout << "Opcion NO valida !!\n\n";
        }
    } while (opcion != 6);

    return 0;
}
