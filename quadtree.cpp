#include <iostream>
#include <vector>
#include "graficarQuad-tree.h"

class PointQ {
public:
    double x, y;

    PointQ(double x, double y) : x(x), y(y) {}
};

class QuadtreeNode {
public:
    double x, y, width, height;
    std::vector<PointQ> points;
    QuadtreeNode* children[4];

    QuadtreeNode(double x, double y, double width, double height) : x(x), y(y), width(width), height(height) {
        for (int i = 0; i < 4; ++i) {
            children[i] = nullptr;
        }
    }

    ~QuadtreeNode() {
        for (int i = 0; i < 4; ++i) {
            delete children[i];
        }
    }

    bool hasChildren() const {
        for (int i = 0; i < 4; ++i) {
            if (children[i] != nullptr) {
                return true;
            }
        }
        return false;
    }

    void subdivide() {
        double halfWidth = width / 2;
        double halfHeight = height / 2;

        children[0] = new QuadtreeNode(x, y, halfWidth, halfHeight);
        children[1] = new QuadtreeNode(x + halfWidth, y, halfWidth, halfHeight);
        children[2] = new QuadtreeNode(x, y + halfHeight, halfWidth, halfHeight);
        children[3] = new QuadtreeNode(x + halfWidth, y + halfHeight, halfWidth, halfHeight);
    }

    int getIndex(const PointQ& p) {
        int index = -1;
        double verticalMidpoint = x + (width / 2);
        double horizontalMidpoint = y + (height / 2);

        bool topQuadrant = (p.y < horizontalMidpoint);
        bool bottomQuadrant = (p.y >= horizontalMidpoint);

        if (p.x < verticalMidpoint) {
            if (topQuadrant) {
                index = 0;
            } else if (bottomQuadrant) {
                index = 2;
            }
        } else if (p.x >= verticalMidpoint) {
            if (topQuadrant) {
                index = 1;
            } else if (bottomQuadrant) {
                index = 3;
            }
        }

        return index;
    }

    void insert(const PointQ& p) {
        if (hasChildren()) {
            int index = getIndex(p);

            if (index != -1) {
                children[index]->insert(p);
                return;
            }
        }

        points.push_back(p);

        if (points.size() > 4 && !hasChildren()) {
            subdivide();

            for (const auto& point : points) {
                int index = getIndex(point);
                if (index != -1) {
                    children[index]->insert(point);
                }
            }

            points.clear();
        }
    }

    void queryRange(const double xRangeMin, const double yRangeMin, const double xRangeMax, const double yRangeMax, std::vector<PointQ>& result) {
        if (x + width < xRangeMin || x > xRangeMax || y + height < yRangeMin || y > yRangeMax) {
            return;
        }

        for (const auto& point : points) {
            if (point.x >= xRangeMin && point.x <= xRangeMax && point.y >= yRangeMin && point.y <= yRangeMax) {
                result.push_back(point);
            }
        }

        if (hasChildren()) {
            for (int i = 0; i < 4; ++i) {
                children[i]->queryRange(xRangeMin, yRangeMin, xRangeMax, yRangeMax, result);
            }
        }
    }

};

struct Range {
    int a;
    int b;
    int c;
    int d;
    

    Range(int a, int b, int c, int d ) : a(a), b(b), c(c), d(d) {}
};

int cero(int num){
    if (num<0){
        return 0;
    }
    return num;
}

int cero1(int num, int num2){
    if (num == 0){
        return 0;
    }
    return num+num2;
}

void Rangos2(std::vector<Range>& puntos,int Ma, int x1, int x2 ) {
    int nun = 0;
    puntos.push_back(Range(x1,x2,x1+Ma,x2+Ma));
    puntos.push_back(Range(x1,x2+Ma,x1+Ma,x2+(2*Ma)));
    puntos.push_back(Range(x1+Ma,x2,x1+(2*Ma),x2+Ma));
    puntos.push_back(Range(x1+Ma,x2+Ma,x1+(2*Ma),x2+(2*Ma)));
}



void imprimirPuntos(const std::vector<Range>& puntos) {
    for (const Range& punto : puntos) {
        std::cout << "Punto: (" << punto.a << ", " << punto. b << ", " << punto. c << ", " << punto. d << ")\n";
    }
}



void queryAndPrintPointsInRange( QuadtreeNode& quadtree, double xRangeMin, double yRangeMin, double xRangeMax, double yRangeMax) {
    std::vector<PointQ> result;
    quadtree.queryRange(xRangeMin, yRangeMin, xRangeMax, yRangeMax, result);

    // Print the result
    for (const auto& point : result) {
        std::cout << "Point (" << point.x << ", " << point.y << ")\n";
    }
}


int queryAndPrintInRange( QuadtreeNode& quadtree, double xRangeMin, double yRangeMin, double xRangeMax, double yRangeMax) {
    int contPoint  = 0;
    std::vector<PointQ> result;
    quadtree.queryRange(xRangeMin, yRangeMin, xRangeMax, yRangeMax, result);
    contPoint = result.size();

    return contPoint ;
}

void Rangos3( std::string** matrizP,std::string** matrizC, int filas, int columnas, int tamanoMatriz,  QuadtreeNode& quadtree ) {
    if (queryAndPrintInRange(quadtree,0,0,tamanoMatriz-1,tamanoMatriz-1) > 1){
        inicializarMatrizRQ(matrizP, matrizC, filas,  columnas, tamanoMatriz/2,tamanoMatriz/2 ) ;
    }
    std::vector<Range> puntos1;
    std::vector<Range> puntos2;
    std::vector<Range> puntos3;

    Rangos2(puntos1, tamanoMatriz/2, 0,0);
    for (const auto& point : puntos1) {
        Rangos2(puntos2, tamanoMatriz/4, point.a, point.b);
    }

    for (const auto& point : puntos2) {
        Rangos2(puntos3, tamanoMatriz/8, point.a, point.b);
    }


    for (const auto& point : puntos1) {
        if (queryAndPrintInRange(quadtree,cero(point.a),cero(point.b),cero(point.c-1),cero(point.d-1)) > 1 ){
           inicializarMatrizRQ(matrizP, matrizC, filas,  columnas, (point.a)+4, abs((point.b+4)-tamanoMatriz )) ; 
        }
    }
     
    for (const auto& point2 : puntos2) {
        if (queryAndPrintInRange(quadtree,cero(point2.a),cero(point2.b),cero(point2.c-1),cero(point2.d-1)) > 1 ){
           inicializarMatrizRQ(matrizP, matrizC, filas,  columnas, (point2.a)+2, abs((point2.b+2)-tamanoMatriz )) ; 
        }
    }
    
    for (const auto& point3 : puntos3) {
        if (queryAndPrintInRange(quadtree,cero(point3.a),cero(point3.b),cero(point3.c-1),cero(point3.d-1)) > 1 ){
           inicializarMatrizRQ(matrizP, matrizC, filas,  columnas, (point3.a)+1, abs((point3.b+1)-tamanoMatriz )) ; 
        }
    }
    
    

}

// Función para generar números aleatorios
	vector<PointQ> generateRandomPoints(int count, int max_x, int max_y) {
	    mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
	    uniform_int_distribution<> distrib_x(0, max_x);
	    uniform_int_distribution<> distrib_y(0, max_y);
	
	    vector<PointQ> points;
	    for (int i = 0; i < count; ++i) {
	        int x = distrib_x(gen);
	        int y = distrib_y(gen);
	        points.push_back(PointQ(x, y));
	    }
	
	    return points;
	}

/*
int main() {
    QuadtreeNode quadtree(0, 0, 16, 16);
    int tamanoMatriz = 16;
    //tamaño de la matriz en conslola 
    int filas = tamanoMatriz*5-(tamanoMatriz-1); 
    int columnas = tamanoMatriz*5-(tamanoMatriz-1);
    std::string** miMatrizP = crearMatriz(filas, columnas);
    std::string** miMatrizC = crearMatriz(filas, columnas);

    // Insert points into the quadtree
    quadtree.insert(Point(1, 1));
    quadtree.insert(Point(2, 2));
    quadtree.insert(Point(2, 3));
    quadtree.insert(Point(12, 10));
    quadtree.insert(Point(14, 9));
    quadtree.insert(Point(4, 12));
    quadtree.insert(Point(4, 13));
    quadtree.insert(Point(13, 4));
    quadtree.insert(Point(13, 3));
    quadtree.insert(Point(7, 7));
    quadtree.insert(Point(7, 8));
    quadtree.insert(Point(14, 10));
    quadtree.insert(Point(14, 8));

  
    inicializarMatrizT(miMatrizP, miMatrizC, filas, columnas);

    //graficar puntos
    inicializarP(miMatrizP, miMatrizC,  1+1,  abs(1+1-(tamanoMatriz+1))) ;
    inicializarP(miMatrizP, miMatrizC,  2+1,  abs(2+1-(tamanoMatriz+1))) ;
    inicializarP(miMatrizP, miMatrizC,  2+1,  abs(3+1-(tamanoMatriz+1))) ;
    inicializarP(miMatrizP, miMatrizC,  12+1,  abs(10+1-(tamanoMatriz+1))) ;
    inicializarP(miMatrizP, miMatrizC,  14+1,  abs(9+1-(tamanoMatriz+1))) ;
    inicializarP(miMatrizP, miMatrizC,  4+1,  abs(12+1-(tamanoMatriz+1))) ;
    inicializarP(miMatrizP, miMatrizC,  4+1,  abs(13+1-(tamanoMatriz+1))) ;
    inicializarP(miMatrizP, miMatrizC,  13+1,  abs(4+1-(tamanoMatriz+1))) ;
    inicializarP(miMatrizP, miMatrizC,  13+1,  abs(3+1-(tamanoMatriz+1))) ;
    inicializarP(miMatrizP, miMatrizC,  7+1,  abs(7+1-(tamanoMatriz+1))) ;
    inicializarP(miMatrizP, miMatrizC,  7+1,  abs(8+1-(tamanoMatriz+1))) ;
    inicializarP(miMatrizP, miMatrizC,  14+1,  abs(10+1-(tamanoMatriz+1))) ;
    inicializarP(miMatrizP, miMatrizC,  14+1,  abs(8+1-(tamanoMatriz+1))) ;
  

    Rangos3(miMatrizP,miMatrizC,filas, columnas, tamanoMatriz,quadtree  );

    imprimirMatriz(miMatrizP, filas, columnas);
    liberarMatriz(miMatrizP, filas);
    liberarMatriz(miMatrizC, filas);




    return 0;
}*/
