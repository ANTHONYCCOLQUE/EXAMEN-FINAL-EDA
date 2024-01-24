#include <cmath>
#include <iostream>
#include "graficarQuad-tree.h"
using namespace std;
 
// Used to hold details of a point
struct Point {
    int x;
    int y;
    Point(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
    Point()
    {
        x = 0;
        y = 0;
    }
};
 
// The objects that we want stored in the quadtree
struct Node {
    Point pos;
    int data;
    Node(Point _pos, int _data)
    {
        pos = _pos;
        data = _data;
    }
    Node() { data = 0; }
};
 
// The main quadtree class
class Quad {
    // Hold details of the boundary of this node
    Point topLeft;
    Point botRight;
 
    // Contains details of node
    Node* n;
 
    // Children of this tree
    Quad* topLeftTree;
    Quad* topRightTree;
    Quad* botLeftTree;
    Quad* botRightTree;
 
public:
    Quad()
    {
        topLeft = Point(0, 0);
        botRight = Point(0, 0);
        n = NULL;
        topLeftTree = NULL;
        topRightTree = NULL;
        botLeftTree = NULL;
        botRightTree = NULL;
    }
    Quad(Point topL, Point botR)
    {
        n = NULL;
        topLeftTree = NULL;
        topRightTree = NULL;
        botLeftTree = NULL;
        botRightTree = NULL;
        topLeft = topL;
        botRight = botR;
    }
    void insert(Node*);
    Node* search(Point);
    bool inBoundary(Point);
};
 
// Insert a node into the quadtree
void Quad::insert(Node* node)
{
    if (node == NULL)
        return;
 
    // Current quad cannot contain it
    if (!inBoundary(node->pos))
        return;
 
    // We are at a quad of unit area
    // We cannot subdivide this quad further
    if (abs(topLeft.x - botRight.x) <= 1
        && abs(topLeft.y - botRight.y) <= 1) {
        if (n == NULL)
            n = node;
        return;
    }
 
    if ((topLeft.x + botRight.x) / 2 >= node->pos.x) {
        // Indicates topLeftTree
        if ((topLeft.y + botRight.y) / 2 >= node->pos.y) {
            if (topLeftTree == NULL)
                topLeftTree = new Quad(
                    Point(topLeft.x, topLeft.y),
                    Point((topLeft.x + botRight.x) / 2,
                          (topLeft.y + botRight.y) / 2));
            topLeftTree->insert(node);
        }
 
        // Indicates botLeftTree
        else {
            if (botLeftTree == NULL)
                botLeftTree = new Quad(
                    Point(topLeft.x,
                          (topLeft.y + botRight.y) / 2),
                    Point((topLeft.x + botRight.x) / 2,
                          botRight.y));
            botLeftTree->insert(node);
        }
    }
    else {
        // Indicates topRightTree
        if ((topLeft.y + botRight.y) / 2 >= node->pos.y) {
            if (topRightTree == NULL)
                topRightTree = new Quad(
                    Point((topLeft.x + botRight.x) / 2,
                          topLeft.y),
                    Point(botRight.x,
                          (topLeft.y + botRight.y) / 2));
            topRightTree->insert(node);
        }
 
        // Indicates botRightTree
        else {
            if (botRightTree == NULL)
                botRightTree = new Quad(
                    Point((topLeft.x + botRight.x) / 2,
                          (topLeft.y + botRight.y) / 2),
                    Point(botRight.x, botRight.y));
            botRightTree->insert(node);
        }
    }
}
 
// Find a node in a quadtree
Node* Quad::search(Point p)
{
    // Current quad cannot contain it
    if (!inBoundary(p))
        return NULL;
 
    // We are at a quad of unit length
    // We cannot subdivide this quad further
    if (n != NULL)
        return n;
 
    if ((topLeft.x + botRight.x) / 2 >= p.x) {
        // Indicates topLeftTree
        if ((topLeft.y + botRight.y) / 2 >= p.y) {
            if (topLeftTree == NULL)
                return NULL;
            return topLeftTree->search(p);
        }
 
        // Indicates botLeftTree
        else {
            if (botLeftTree == NULL)
                return NULL;
            return botLeftTree->search(p);
        }
    }
    else {
        // Indicates topRightTree
        if ((topLeft.y + botRight.y) / 2 >= p.y) {
            if (topRightTree == NULL)
                return NULL;
            return topRightTree->search(p);
        }
 
        // Indicates botRightTree
        else {
            if (botRightTree == NULL)
                return NULL;
            return botRightTree->search(p);
        }
    }
};
 
// Check if current quadtree contains the point
bool Quad::inBoundary(Point p)
{
    return (p.x >= topLeft.x && p.x <= botRight.x
            && p.y >= topLeft.y && p.y <= botRight.y);
}
 
// Driver program
int main()
{
    int x1,x2,x3;
    int y1,y2,y3;

    x1 = 1; y1 = 1;
    x2 = 2; y2 = 5;
    x3 = 7; y3 = 6;
    
    int numero = 11;
    int filas = numero*3-(numero-1); 
    int columnas = numero*5-(numero-1); 

    std::string** miMatrizP = crearMatriz(filas, columnas);
    std::string** miMatrizC = crearMatriz(filas, columnas);
    Quad center(Point(0, 0), Point(11, 11));

    inicializarMatrizT(miMatrizP, miMatrizC, filas, columnas);
    Node a(Point(1, 1), 1);
    inicializarMatrizR(miMatrizP, miMatrizC, filas,  columnas,  x1,  numero -y1 ) ;
    imprimirMatriz(miMatrizP, filas, columnas);
    Node b(Point(2, 5), 2);
    inicializarMatrizR(miMatrizP, miMatrizC, filas,  columnas,  x2,  numero -y2 ) ;
        imprimirMatriz(miMatrizP, filas, columnas);
    Node c(Point(7, 6), 3);
    inicializarMatrizR(miMatrizP, miMatrizC, filas,  columnas,  x3,  numero -y3 ) ;
        imprimirMatriz(miMatrizP, filas, columnas);
    return 0;
}