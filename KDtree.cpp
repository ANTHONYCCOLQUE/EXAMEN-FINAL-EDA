#include <iostream>
#include "graficarKDtree.h"
#include <algorithm>
#include <random>
#include <set>
#include <chrono>
#include <vector>

using namespace std;

struct Point {
    int x, y;

    Point(int x, int y) : x(x), y(y) {}
};

struct Node {
    Point p;
    Node* left;
    Node* right;

    Node(Point point) : p(point), left(nullptr), right(nullptr) {}
};

class KDTree {
private:
    Node* root;
	static const int HEIGHT = 22;
    static const int WIDTH = 120;
    char matrix[HEIGHT][WIDTH];
    // Function to insert a point into the tree
    Node* insert(Node* node, Point point, bool compareX) {
        if (node == nullptr) {
            return new Node(point);
        }

        // Compare based on the cutting dimension (x or y)
        if ((compareX && point.x < node->p.x) || (!compareX && point.y < node->p.y)) {
            node->left = insert(node->left, point, !compareX);
        } else {
            node->right = insert(node->right, point, !compareX);
        }

        return node;
    }

    // Function to print the tree diagram (in-order)
    

    // Función para encontrar el nivel de un punto en el árbol
    int findLevel(Node* node, Point point, bool compareX, int level) {
        if (node == nullptr) {
            return -1; // Punto no encontrado en el árbol
        }

        if (node->p.x == point.x && node->p.y == point.y) {
            return level;
        }

        // Compare based on the cutting dimension (x or y)
        if ((compareX && point.x < node->p.x) || (!compareX && point.y < node->p.y)) {
            return findLevel(node->left, point, !compareX, level + 1);
        } else {
            return findLevel(node->right, point, !compareX, level + 1);
        }
    }

public:
    KDTree() : root(nullptr) {}

    // Function to insert a point into the tree
    void insert(Point point) {
        root = insert(root, point, true); // Start with comparing along the x-axis
   		visualizeTree();
    }

    
   
    // Función para obtener el nivel de un punto en el árbol
    int getLevel(Point point) {
        return findLevel(root, point, true, 0);
    }
    
    
    void inOrderTraversal(Node* node, int depth, int left, int right, bool compareX) {
        if (node != nullptr && depth < HEIGHT - 1 && left < right) {
            int mid = (left + right) / 2;

            // Imprimir el punto en el centro
            std::string pointValue = "(" + std::to_string(node->p.x) + ", " + std::to_string(node->p.y) + ")";
            int startIdx = mid - pointValue.size() / 2;

            for (size_t i = 0; i < pointValue.size(); ++i) {
                matrix[depth][startIdx + i] = pointValue[i];
            }

            inOrderTraversal(node->left, depth + 2, left, mid - 1, !compareX);
            inOrderTraversal(node->right, depth + 2, mid + 1, right, !compareX);
        }
    }

    void preOrderTraversal(Node* node, int depth, int left, int right, bool compareX) {
        if (node != nullptr && depth < HEIGHT - 1 && left < right) {
            int mid = (left + right) / 2;

            // Imprimir el punto en el centro
            std::string pointValue = "(" + std::to_string(node->p.x) + ", " + std::to_string(node->p.y) + ")";
            int startIdx = mid - pointValue.size() / 2;

            for (size_t i = 0; i < pointValue.size(); ++i) {
                matrix[depth][startIdx + i] = pointValue[i];
            }

            preOrderTraversal(node->left, depth + 2, left, mid - 1, !compareX);
            preOrderTraversal(node->right, depth + 2, mid + 1, right, !compareX);
        }
    }

    void visualizeTree() {
        initializeMatrix();
        // Comentario o elimina la siguiente línea si no quieres el recorrido en preorden
        preOrderTraversal(root, 1, 0, WIDTH - 1, true);
        inOrderTraversal(root, 1, 0, WIDTH - 1, true);  // Comienza comparando a lo largo del eje x
        printMatrix();
        std::cout << "Presiona Enter para continuar..." << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Espera a que el usuario presione Enter
    }

    // Resto del código...
    void initializeMatrix() {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (i == 0 || i == HEIGHT - 1) matrix[i][j] = '-';
                else if (j == 0 || j == WIDTH - 1) matrix[i][j] = '|';
                else matrix[i][j] = ' ';
            }
        }
    }

    void printMatrix() {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                std::cout << matrix[i][j];
               
            }
            std::cout << std::endl;
        }
    }
};

// Función para generar números aleatorios pares sin repetición
int generarNumeroPar(std::set<int>& numerosGenerados) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribucion(1, 20);  // Ajusta el rango según tus necesidades

    int numero;
    do {
        numero = distribucion(gen);
    } while (numerosGenerados.count(numero) > 0);

    // Asegurarse de que el número sea par
    numero = (numero % 2 == 0) ? numero : numero + 1;

    // Agregar el número al conjunto para evitar repeticiones
    numerosGenerados.insert(numero);

    return numero;
}


vector<int> generateRandomNumbers(int count) {
	    mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
	
	    vector<int> numbers;
	    for (int i = 1; i <= 20; i++) {
	        numbers.push_back(i);
	    }
	
	    shuffle(numbers.begin(), numbers.end(), gen);
	    numbers.resize(count);
	
	    return numbers;
}

/*
int main() {
	
    /*
   	KDTree tree;

    int tamanoMatriz = 22;

    //tamaño de la matriz en conslola 
    int filas = tamanoMatriz*3-(tamanoMatriz-1); 
    int columnas = tamanoMatriz*5-(tamanoMatriz-1);

    // Example usages
    int x1,x2,x3,x4,x5,x6,x7;
    int y1,y2,y3,y4,y5,y6,y7;

    x1 = 3; y1 = 6;
    x2 = 2; y2 = 7;
    x3 = 8; y3 = 9;
    x4 = 1 ; y4 = 5;
	std::set<int> numerosGenerados;

    // Generar coordenadas x e y aleatorias para puntos pares sin repetición
    int x1 = generarNumeroPar(numerosGenerados);
    int y1 = generarNumeroPar(numerosGenerados);
    
    int x2 = generarNumeroPar(numerosGenerados);
    int y2 = generarNumeroPar(numerosGenerados);
    
    int x3 = generarNumeroPar(numerosGenerados);
    int y3 = generarNumeroPar(numerosGenerados);
    
    int x4 = generarNumeroPar(numerosGenerados);
    int y4 = generarNumeroPar(numerosGenerados);

    int x5 = generarNumeroPar(numerosGenerados);
    int y5 = generarNumeroPar(numerosGenerados);



    tree.insert(Point(x1, y1));
    Point queryPoint1(x1, y1);
    int level1 = tree.getLevel(queryPoint1);
    
    tree.insert(Point(x2, y2));
    Point queryPoint2(x2, y2);
    int level2 = tree.getLevel(queryPoint2);
    
    tree.insert(Point(x3, y3));
    Point queryPoint3(x3, y3);
    int level3 = tree.getLevel(queryPoint3);
    
  	tree.insert(Point(x4, y4));
    Point queryPoint4(x4, y4);
    int level4 = tree.getLevel(queryPoint4);
    
    tree.insert(Point(x5, y5));
    Point queryPoint5(x5, y5);
    int level5 = tree.getLevel(queryPoint5);

    // Print the tree diagram
  

    std::cout << std::endl;

    //crear las matrices
    std::string** miMatrizP = crearMatriz(filas, columnas);
    std::string** miMatrizC = crearMatriz(filas, columnas);

    // se crea el marco de la matriz
    inicializarMatrizT(miMatrizP, miMatrizC, filas, columnas);

    // se dibujan los puntos y KDtree
    tree.insert(Point(x1, y1));
    Point queryPoint1(x1, y1);
    int level1 = tree.getLevel(queryPoint1);
    inicializarMatrizR(miMatrizP, miMatrizC, filas,  columnas, esPar(level1+1) ,  x1,  tamanoMatriz -y1 ) ;
    imprimirMatriz(miMatrizP, filas, columnas);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Espera a que el usuario presione Enter
    
    tree.insert(Point(x2, y2));
    Point queryPoint2(x2, y2);
    int level2 = tree.getLevel(queryPoint2);
    inicializarMatrizR(miMatrizP, miMatrizC, filas,  columnas, esPar(level2+1) ,  x2,  tamanoMatriz -y2 ) ;
    imprimirMatriz(miMatrizP, filas, columnas);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Espera a que el usuario presione Enter

    tree.insert(Point(x3, y3));
    Point queryPoint3(x3, y3);
    int level3 = tree.getLevel(queryPoint3);
    inicializarMatrizR(miMatrizP, miMatrizC, filas,  columnas, esPar(level3+1) ,  x3,  tamanoMatriz -y3 ) ;
    imprimirMatriz(miMatrizP, filas, columnas);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Espera a que el usuario presione Enter
    
    tree.insert(Point(x4, y4));
    Point queryPoint4(x4, y4);
    int level4 = tree.getLevel(queryPoint4);
 	inicializarMatrizR(miMatrizP, miMatrizC, filas,  columnas, esPar(level4+1) ,  x4,  tamanoMatriz -y4 ) ;
 	imprimirMatriz(miMatrizP, filas, columnas);
 	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Espera a que el usuario presione Enter
 	
 	tree.insert(Point(x5, y5));
    Point queryPoint5(x5, y5);
    int level5 = tree.getLevel(queryPoint5);
    inicializarMatrizR(miMatrizP, miMatrizC, filas,  columnas, esPar(level5+1) ,  x5,  tamanoMatriz -y5 ) ;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Espera a que el usuario presione Enter

    // imprime la matriz
    imprimirMatriz(miMatrizP, filas, columnas);

    

    // Liberar la memoria
    liberarMatriz(miMatrizP, filas);
    liberarMatriz(miMatrizC, filas);

    //int level = tree.getNodeLevel(Point(17, 15));


    return 0;
}
	*/
	
	/*
	KDTree tree;

    int tamanoMatriz = 22;

    //tamaño de la matriz en conslola 
    int filas = tamanoMatriz*3-(tamanoMatriz-1); 
    int columnas = tamanoMatriz*5-(tamanoMatriz-1);

   
	std::set<int> numerosGenerados;
	 //crear las matrices
    std::string** miMatrizP = crearMatriz(filas, columnas);
    std::string** miMatrizC = crearMatriz(filas, columnas);

    // se crea el marco de la matriz
    inicializarMatrizT(miMatrizP, miMatrizC, filas, columnas);
    
    
	
	int count; 
	cout<< "Ingrese cantidad de puntos aleatorios a generar: ";
	cin >> count;
	
	count = count * 2;
	
    vector<int> randomNumbers = generateRandomNumbers(count);
	
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
    
    return 0;
    
    
    
    // MAnual
    
    KDTree tree;

    int tamanoMatriz = 22;

    //tamaño de la matriz en conslola 
    int filas = tamanoMatriz*3-(tamanoMatriz-1); 
    int columnas = tamanoMatriz*5-(tamanoMatriz-1);

   
	std::set<int> numerosGenerados;
	 //crear las matrices
    std::string** miMatrizP = crearMatriz(filas, columnas);
    std::string** miMatrizC = crearMatriz(filas, columnas);

    // se crea el marco de la matriz
    inicializarMatrizT(miMatrizP, miMatrizC, filas, columnas);
    
    
    
    int cant, x1, y1;
	cout <<" Digite cantidad de puntos a insertar: ";
    cin >> cant;
    
    for (int i = 0; i < cant; i++){
    	cout <<" Digite valor de x"<<i+1<<": ";
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
    
    return 0;
    
    
	
}*/
