#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <algorithm>
#include <set>
#include <ctime>
#include <random>
#include <vector>
using namespace std;

enum Color { RED, BLACK };

struct RBNode {
    int data;
    RBNode *left, *right, *parent;
    Color color;
    RBNode(int value) : data(value), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
};



class RedBlackTree {
private:
    RBNode* root;
    RBNode* nil; // Nodo nulo para representar hojas

    static const int HEIGHT = 22; // Altura suficiente para 10 nodos.
    static const int WIDTH = 120; // Duplicamos el ancho para una mejor visualización.
    char matrix[HEIGHT][WIDTH];
    std::string explanation; // Variable para almacenar las explicaciones
	 void deleteTree(RBNode* node) {
        if (node != nil) {
            // Recursivamente liberar nodos en el subárbol izquierdo y derecho
            deleteTree(node->left);
            deleteTree(node->right);
            // Liberar el nodo actual
            delete node;
        }
    }
public:
    RedBlackTree() {
        nil = new RBNode(-1);
        nil->color = BLACK;
        root = nil;
    }
	
	~RedBlackTree() {
        // Llamada a la función para liberar la memoria del árbol
        deleteTree(root);
        // Liberar el nodo nulo
        delete nil;
    }
    void leftRotate(RBNode* x) {
        RBNode* y = x->right;
        x->right = y->left;
        if (y->left != nil) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nil) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
        explanation += "Rotacion a la izquierda en " + std::to_string(x->data) + ".\n";
    }

    void rightRotate(RBNode* y) {
        RBNode* x = y->left;
        y->left = x->right;
        if (x->right != nil) {
            x->right->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == nil) {
            root = x;
        } else if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }
        x->right = y;
        y->parent = x;
        explanation += "Rotacion a la derecha en " + std::to_string(y->data) + ".\n";
    }

    void insert(int data) {
	    RBNode* node = new RBNode(data);
	    node->color = RED;
	    node->left = nil;
	    node->right = nil;
	    node->parent = nil;
	
	    explanation.clear(); // Limpiar las explicaciones anteriores
	    explanation += "Insertado: " + std::to_string(data) + " (Antes de Corregir)\n";
	
	    insertBST(node);
	    visualizeTree(); // Visualizar el árbol después de la inserción y antes del balanceo
	    printExplanation(); // Mostrar explicaciones para la inserción antes del balanceo
	    
	    fixInsert(node);
	    
	    explanation.clear(); // Limpiar las explicaciones anteriores del balanceo
	    explanation += "Despues de Corregir la Insercion: " + std::to_string(data) + "\n";
	    visualizeTree(); // Visualizar el árbol después del balanceo
	    printExplanation(); // Mostrar explicaciones para la inserción después del balanceo
}

    void insertBST(RBNode* z) {
        RBNode* y = nil;
        RBNode* x = root;

        while (x != nil) {
            y = x;
            if (z->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        z->parent = y;

        if (y == nil) {
            root = z;
        } else if (z->data < y->data) {
            y->left = z;
        } else {
            y->right = z;
        }
    }

	void fixInsert(RBNode* z) {
	    while (z->parent->color == RED) {
	        if (z->parent == z->parent->parent->left) {
	            RBNode* y = z->parent->parent->right;
	            if (y->color == RED) {
	                // Caso 1: Tanto el padre como el tío de z son rojos
	                explanation += "Caso 1: El padre y el tio son rojos. Recoloreando...\n";
	                z->parent->color = BLACK;
	                y->color = BLACK;
	                z->parent->parent->color = RED;
	                visualizeTree();
	                //printExplanation();
	                explanation.clear();
	                
	                z = z->parent->parent;
	            } else {
	                if (z == z->parent->right) {
	                    // Caso 2: z es el hijo derecho, rotación a la izquierda necesaria
	                    explanation += "Caso 2: z es hijo derecho. Rotacion a la izquierda en " + std::to_string(z->parent->data) + ".\n";
	                    z = z->parent;
	                    leftRotate(z);
	                    visualizeTree();
	                    //printExplanation();
	                    explanation.clear();
	                }
	                // Caso 3: z es el hijo izquierdo, recolorear y rotar a la derecha
	                explanation += "Caso 3: Rotacion a la derecha en " + std::to_string(z->parent->parent->data) + " despues de recolorear.\n";
	                z->parent->color = BLACK;
	                z->parent->parent->color = RED;
	                rightRotate(z->parent->parent);
	                visualizeTree();
	                //printExplanation();
	                explanation.clear();
	            }
	        } else {
	            // Espejo del código anterior con 'right' y 'left' intercambiados
	            RBNode* y = z->parent->parent->left;
	            if (y->color == RED) {
	                // Caso 1
	                explanation += "Caso 1: El padre y el tio son rojos. Recoloreando...\n";
	                z->parent->color = BLACK;
	                y->color = BLACK;
	                z->parent->parent->color = RED;
	                visualizeTree();
	                //printExplanation();
	                explanation.clear();
	
	                z = z->parent->parent;
	            } else {
	                if (z == z->parent->left) {
	                    // Caso 2
	                    explanation += "Caso 2: z es hijo izquierdo. Rotacion a la derecha en " + std::to_string(z->parent->data) + ".\n";
	                    z = z->parent;
	                    rightRotate(z);
	                    visualizeTree();
	                    //printExplanation();
	                    explanation.clear();
	                }
	                // Caso 3
	                explanation += "Caso 3: Rotacion a la izquierda en " + std::to_string(z->parent->parent->data) + " despues de recolorear.\n";
	                z->parent->color = BLACK;
	                z->parent->parent->color = RED;
	                leftRotate(z->parent->parent);
	                visualizeTree();
	                //printExplanation();
	                explanation.clear();
	            }
	        }
    }

    root->color = BLACK;
    explanation += "El color de la raiz se establece en NEGRO.\n";
    //visualizeTree();
    printExplanation();
    explanation.clear();
}

	
	
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

    void visualizeTreeInMatrix(RBNode* node, int depth, int left, int right) {
        if (node == nil || depth >= HEIGHT - 1 || left >= right) return;

        int mid = (left + right) / 2;

        // Imprimir el número en el lado izquierdo
        std::string nodeValue = std::to_string(node->data);
        int startIdx = mid - nodeValue.size() - 1;

        for (size_t i = 0; i < nodeValue.size(); ++i) {
            matrix[depth][startIdx + i] = nodeValue[i];
        }

        matrix[depth][mid - 1] = (node->color == RED) ? 'R' : 'B';
		
		
        visualizeTreeInMatrix(node->left, depth + 2, left, mid - 1);
        visualizeTreeInMatrix(node->right, depth + 2, mid + 1, right);
    }

    void visualizeTree() {
        initializeMatrix();
        visualizeTreeInMatrix(root, 1, 0, WIDTH - 1);
        printMatrix();
        printExplanation();
    }

   	void printExplanation() {
	    std::cout << "Explicacion:" << std::endl;
	    std::cout << explanation;
	    std::this_thread::sleep_for(std::chrono::seconds(1)); // Incrementar el tiempo para mejor visualización
	    system("pause");
}
	/*void insertRandomNumbers(int count) {
        mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());

        root = nullptr;  // Reinicia el árbol antes de insertar nuevos números

        vector<int> numbers;
        for (int i = 1; i <= 100; i++) {
            numbers.push_back(i);
        }

        shuffle(numbers.begin(), numbers.end(), gen);
        numbers.resize(count);

        for (int number : numbers) {
            insert(number);
        }
    }*/
  
};

  vector<int> generateRandomNumbersRB(int count) {
	    mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
	
	    vector<int> numbers;
	    for (int i = 1; i <= 100; i++) {
	        numbers.push_back(i);
	    }
	
	    shuffle(numbers.begin(), numbers.end(), gen);
	    numbers.resize(count);
	
	    return numbers;
}
	/*
int main() {
    RedBlackTree rbTree;

    int dataToInsert[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int dataSize = sizeof(dataToInsert) / sizeof(dataToInsert[0]);

    for (int i = 0; i < dataSize; i++) {
        rbTree.insert(dataToInsert[i]);
        //rbTree.visualizeTree();
    }
    
    int n, dato;
	cout<< "Digite cantidad de digitos: ";
	cin >> n;
    for (int i = 0; i<n; i++){
		cout<<"Inserte dato: ";
		cin >> dato;
		rbTree.insert(dato);		
	}
	
	int count; 
	cout<< "Ingrese cantidad de numeros aleatorios a generar: ";
	cin >> count;
    vector<int> randomNumbers = generateRandomNumbersRB(count);
	
	cout<<" \nNumeros aleatorios generados: ";
	cout<<"[ ";
	for (int i = 0 ; i < count ; i++){
		cout << randomNumbers[i] <<" - ";
	}
	cout<<" ]\n";
    
    
    for (int i = 0; i<randomNumbers.size(); i++){
    	rbTree.insert(randomNumbers[i]);
	}

    return 0;
}*/
