#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <ctime>
#include <random>
#include <chrono>

using namespace std;



struct BinaryNode {
    int data;
    BinaryNode* left;
    BinaryNode* right;
    BinaryNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    BinaryNode* root;
    static const int HEIGHT = 22;
    static const int WIDTH = 120;
    char matrix[HEIGHT][WIDTH];
    
    //vector<int> numeros;

public:
    BinaryTree() : root(nullptr) {}
	~BinaryTree() {
        // Llama a la función de liberación para liberar la memoria del árbol
        deleteTree(root);
    }
	vector<int> numeros;
	
    void insert(int data) {
        std::cout << "Insertando: " << data << std::endl;
        root = insertBST(root, data);
        visualizeTree();
    }

    BinaryNode* insertBST(BinaryNode* node, int data) {
        if (node == nullptr) {
            return new BinaryNode(data);
        }

        if (data < node->data) {
            node->left = insertBST(node->left, data);
        } else if (data > node->data) {
            node->right = insertBST(node->right, data);
        }

        return node;
    }

    void inOrderTraversal(BinaryNode* node, int depth, int left, int right) {
        if (node != nullptr && depth < HEIGHT - 1 && left < right) {
            int mid = (left + right) / 2;

            // Imprimir el número en el centro
            std::string nodeValue = std::to_string(node->data);
            int startIdx = mid - nodeValue.size() / 2;

            for (size_t i = 0; i < nodeValue.size(); ++i) {
                matrix[depth][startIdx + i] = nodeValue[i];
            }

            inOrderTraversal(node->left, depth + 2, left, mid - 1);
            inOrderTraversal(node->right, depth + 2, mid + 1, right);
        }
    }

    void visualizeTree() {
	    initializeMatrix();
	    inOrderTraversal(root, 1, 0, WIDTH - 1);
	    printMatrix();
	    std::cout << "Presiona Enter para continuar..." << std::endl;
	    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Espera a que el usuario presione Enter
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
    
    void insertRandomNumbers(int count) {
        mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());

        root = nullptr;  // Reinicia el árbol antes de insertar nuevos números

        vector<int> numbersB;
        for (int i = 1; i <= 100; i++) {
            numbersB.push_back(i);
            
        }

        shuffle(numbersB.begin(), numbersB.end(), gen);
        numbersB.resize(count);

        for (int number : numbersB) {
            numeros.push_back(number);
			insert(number);
         
   	 	}
	}
	
	void Values() {
        cout << "Valores almacenados en el vector: ";
        for (int i = 0 ; i < numeros.size() ;i++) {
            cout << numeros[i]<< " ";
        }
        cout << endl;
    }
    
    void deleteTree(BinaryNode* node) {
        if (node != nullptr) {
            // Recursivamente libera la memoria de los nodos del subárbol izquierdo y derecho
            deleteTree(node->left);
            deleteTree(node->right);
            // Libera el nodo actual
            delete node;
        }
    }

};

	
/*
int main() {
   BinaryTree bTree;

   // int dataToInsert[] = {50, 30, 70, 20, 40, 60, 80};
  //  int dataSize = sizeof(dataToInsert) / sizeof(dataToInsert[0]);
/*	int n, dato;
	cout<< "Digite cantidad de digitos: ";
	cin >> n;
		
				
	for (int i = 0; i<n; i++){
		cout<<"Inserte dato: ";
		cin >> dato;
		bTree.insert(dato);		
	}

	
	
	int count;
    cout << "Ingrese la cantidad de numeros aleatorios a generar: ";
    cin >> count;

	//for (int i = 0; i<count; i++){
//		cout<<numeros[i];		
	//}
	bTree.Values() ;

    bTree.insertRandomNumbers(count);
	
	
	
   // for (int i = 0; i < dataSize; i++) {
   //    bTree.insert(dataToInsert[i]);
   // }

    return 0;
}*/
