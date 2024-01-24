#include <iostream>
#include <string>
#include <algorithm>

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

public:
    BinaryTree() : root(nullptr) {}

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
};
/*
int main() {
    BinaryTree bTree;

    int dataToInsert[] = {50, 30, 70, 20, 40, 60, 80};
    int dataSize = sizeof(dataToInsert) / sizeof(dataToInsert[0]);

    for (int i = 0; i < dataSize; i++) {
        bTree.insert(dataToInsert[i]);
    }

    return 0;
}*/
