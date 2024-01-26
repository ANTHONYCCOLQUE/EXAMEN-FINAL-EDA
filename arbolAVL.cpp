#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <string>
#include <set>
#include <ctime>
#include <random>
#include <vector>

using namespace std;

vector<int> numbers;

struct AVLNode {
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;

public:
    AVLTree() : root(nullptr) {}
	
	~AVLTree() {
        // Llama a la función de liberación para liberar la memoria del árbol
        deleteTree(root);
    }
    
	void deleteTree(AVLNode* node) {
        if (node != nullptr) {
            // Recursivamente libera la memoria de los nodos del subárbol izquierdo y derecho
            deleteTree(node->left);
            deleteTree(node->right);
            // Libera el nodo actual
            delete node;
        }
    }
    int height(AVLNode* node) {
        if (node == nullptr) return 0;
        return node->height;
    }

    int balanceFactor(AVLNode* node) {
        if (node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        return y;
    }

    AVLNode* insert(AVLNode* node, int data, std::string& explanation) {
        if (node == nullptr) {
            explanation += "Insertar: " + std::to_string(data) + "\n";
            return new AVLNode(data);
        }

        if (data < node->data) {
            node->left = insert(node->left, data, explanation);
        } else if (data > node->data) {
            node->right = insert(node->right, data, explanation);
        } else {
            // Duplicados no permitidos en este ejemplo
            return node;
        }

        node->height = 1 + std::max(height(node->left), height(node->right));

        int balance = balanceFactor(node);
		
		if (balance > 1 && data < node->left->data) {
			visualizeTree(node, "Antes de Rotacion");
            explanation += "Desequilibrio detectado. Realizando rotacion simple a la derecha en " + std::to_string(node->data) + ".\n";
            std::cout << explanation; // Imprimir la explicación antes de visualizar el árbol
            explanation.clear(); // Limpiar la explicación después de imprimir
            //visualizeTree(node, "Antes de Rotación");
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return rightRotate(node);
        }
		
		
        // Casos de desequilibrio
        if (balance > 1 && data < node->left->data) {
            visualizeTree(node, "Antes de Rotacion");
            explanation += "Desequilibrio detectado. Realizando rotacion simple a la derecha en " + std::to_string(node->data) + ".\n";
            //visualizeTree(node, "Antes de Rotación");
			std::this_thread::sleep_for(std::chrono::seconds(1));
            return rightRotate(node);
        }
        if (balance < -1 && data > node->right->data) {
            visualizeTree(node, "Antes de Rotacion");
            explanation += "Desequilibrio detectado. Realizando rotacion simple a la izquierda en " + std::to_string(node->data) + ".\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return leftRotate(node);
        }
        if (balance > 1 && data > node->left->data) {
            visualizeTree(node, "Antes de Rotacion");
            explanation += "Desequilibrio detectado. Realizando rotacion doble a la izquierda-derecha en " + std::to_string(node->data) + ".\n";
            node->left = leftRotate(node->left);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return rightRotate(node);
        }
        if (balance < -1 && data < node->right->data) {
            visualizeTree(node, "Antes de Rotacion");
            explanation += "Desequilibrio detectado. Realizando rotacion doble a la derecha-izquierda en " + std::to_string(node->data) + ".\n";
            node->right = rightRotate(node->right);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return leftRotate(node);
        }

        return node;
    }

    void insert(int data) {
        std::string explanation;
        root = insert(root, data, explanation);
        std::cout << explanation; // Imprimir la explicación antes de visualizar el árbol
        visualizeTree(root, "Despues de Insertar " + std::to_string(data));
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Añadido para mejor visualización
        system("pause"); // Añadido para detener la ejecución entre inserciones
    }

    void inOrderTraversal(AVLNode* node, int depth, int left, int right, std::string matrix[][122]) {
        if (node != nullptr && depth < 16 && left < right) {
            int mid = (left + right) / 2;

            // Imprimir el número en el centro
            std::string nodeValue = std::to_string(node->data);
            int startIdx = mid - nodeValue.size() / 2;

            for (size_t i = 0; i < nodeValue.size(); ++i) {
                matrix[depth][startIdx + i] = nodeValue[i];
            }

            inOrderTraversal(node->left, depth + 2, left, mid - 1, matrix);
            inOrderTraversal(node->right, depth + 2, mid + 1, right, matrix);
        }
    }

    void visualizeTree(AVLNode* node, const std::string& title) {
        const int HEIGHT = 18;
        const int WIDTH = 122;
        std::string matrix[HEIGHT][WIDTH];

        // Inicializar la matriz con espacios y dibujar el marco
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (i == 0 || i == HEIGHT - 1) {
                    matrix[i][j] = "-";
                } else if (j == 0 || j == WIDTH - 1) {
                    matrix[i][j] = "|";
                } else {
                    matrix[i][j] = " ";
                }
            }
        }

        inOrderTraversal(node, 2, 1, WIDTH - 2, matrix); // Ajustamos los índices para el marco

        // Imprimir la matriz con el marco
        std::cout << std::endl << "============================" << std::endl;
        std::cout << title << ":" << std::endl;
        std::cout << "============================" << std::endl;
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                std::cout << matrix[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << "============================" << std::endl << std::endl;
    }
    /*
    void insertRandomNumbers(int count) {
        mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());

        root = nullptr;  // Reinicia el árbol antes de insertar nuevos números

        //vector<int> numbers;
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

vector<int> generateRandomNumbersAVL(int count) {
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
    AVLTree avlTree;

    int dataToInsert[] = {20,10,90,60,33,59}; 
    int dataSize = sizeof(dataToInsert) / sizeof(dataToInsert[0]);

    for (int i = 0; i < dataSize; i++) {
        avlTree.insert(dataToInsert[i]);
    }
    
	
	int count; 
	cout<< "Ingrese cantidad de numeros aleatorios a generar: ";
	cin >> count;
    vector<int> randomNumbersAVL = generateRandomNumbersAVL(count);
	
	cout<<" \nNumeros aleatorios generados: ";
	cout<<"[ ";
	for (int i = 0 ; i < count ; i++){
		cout << randomNumbersAVL[i] <<" - ";
	}
	cout<<" ]\n";
    
    
    for (int i = 0; i<randomNumbersAVL.size(); i++){
    	avlTree.insert(randomNumbersAVL[i]);
	}

    

    return 0;
}*/

