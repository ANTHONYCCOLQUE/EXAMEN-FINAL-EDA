#include <iostream>
#include "graficarKDtree.h"

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
    void printTree(Node* node, int depth) {
        if (node != nullptr) {
            printTree(node->right, depth + 1);
            for (int i = 0; i < depth; ++i) {
                std::cout << " ";
            }
            std::cout << "(" << node->p.x << ", " << node->p.y << ")" << std::endl;
            printTree(node->left, depth + 1);
        }
    }

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
    }

    // Function to print the tree diagram
    void printTree() {
        printTree(root, 0);
    }

    // Función para obtener el nivel de un punto en el árbol
    int getLevel(Point point) {
        return findLevel(root, point, true, 0);
    }
};

int main() {
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
    x3 = 17; y3 = 15;
    x4 = 6; y4 = 12;
    x5 = 13; y5 = 15;
    x6 = 9; y6 = 1;
    x7 = 10; y7 = 19;



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
    tree.insert(Point(x6, y6));
    Point queryPoint6(x6, y6);
    int level6 = tree.getLevel(queryPoint6);
    tree.insert(Point(x7, y7));
    Point queryPoint7(x7, y7);
    int level7 = tree.getLevel(queryPoint7);

    // Print the tree diagram
    tree.printTree();

    std::cout << std::endl;

    //crear las matrices
    std::string** miMatrizP = crearMatriz(filas, columnas);
    std::string** miMatrizC = crearMatriz(filas, columnas);

    // se crea el marco de la matriz
    inicializarMatrizT(miMatrizP, miMatrizC, filas, columnas);

    // se dibujan los puntos y KDtree
    inicializarMatrizR(miMatrizP, miMatrizC, filas,  columnas, esPar(level1+1) ,  x1,  tamanoMatriz -y1 ) ;
    inicializarMatrizR(miMatrizP, miMatrizC, filas,  columnas, esPar(level2+1) ,  x2,  tamanoMatriz -y2 ) ;
    inicializarMatrizR(miMatrizP, miMatrizC, filas,  columnas, esPar(level3+1) ,  x3,  tamanoMatriz -y3 ) ;
    inicializarMatrizR(miMatrizP, miMatrizC, filas,  columnas, esPar(level4+1) ,  x4,  tamanoMatriz -y4 ) ;
    inicializarMatrizR(miMatrizP, miMatrizC, filas,  columnas, esPar(level5+1) ,  x5,  tamanoMatriz -y5 ) ;
    inicializarMatrizR(miMatrizP, miMatrizC, filas,  columnas, esPar(level6+1) ,  x6,  tamanoMatriz -y6 ) ;
    inicializarMatrizR(miMatrizP, miMatrizC, filas,  columnas, esPar(level7+1) ,  x7,  tamanoMatriz -y7 ) ;

    // imprime la matriz
    imprimirMatriz(miMatrizP, filas, columnas);

    std::cout << level1+1 << " " << level2+1 << " " << level3+1 << " " << level4+1 << " " << level5+1 << " " << level6+1 << " " << level7+1 << std::endl;


    // Liberar la memoria
    liberarMatriz(miMatrizP, filas);
    liberarMatriz(miMatrizC, filas);

    //int level = tree.getNodeLevel(Point(17, 15));


    return 0;
}
