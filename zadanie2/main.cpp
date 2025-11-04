#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>

struct Point {
    float x;
    float y;
};

struct NearestPoints {
    Point point1;
    Point point2;
};

bool Read(Point *&points, unsigned int &n);
int findConvexHull(Point *points, unsigned int n);
NearestPoints findNearestPoints(Point *points, unsigned int n);

int main() {
    Point *data = nullptr;
    unsigned int size = 0;

    if (!Read(data, size)) {
        delete[] data;
        data = nullptr;
        return 1;
    }

    NearestPoints zad3 = findNearestPoints(data, size);

    delete[] data;
    data = nullptr;
    return 0;
}

bool Read(Point *&points, unsigned int &n){
    std::cout << "Enter filename: ";
    std::string filename;
    std::cin >> filename;

    std::ifstream file(filename);

    if (file.is_open()) {
        file >> n;

        points = new Point[n];

        float x,y;

        for (int i = 0; i < n; i++) {
            file >> x >> y;
            points[i].x = x;
            points[i].y = y;
        }

        file.close();
        return true;
    } else {
        std::cout << "Couldn't open file";
        return false;
    }
}

int findConvexHull(Point *points, unsigned int n) {

    if (n < 3) {
        return -1;
    }

    Point p0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {}
    }
}


NearestPoints findNearestPoints(Point *points, unsigned int n) {
    float minD = std::numeric_limits<float>::max();
    Point point1 = {0.0,0.0};
    Point point2 = {0.0,0.0};

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            float x = points[j].x - points[i].x;
            float y = points[j].y - points[i].y;

            float d = sqrt((x * x) + (y * y));

            if (d < minD) {
                minD = d;

                point1 = points[i];
                point2 = points[j];
            }
        }
    }

    std::cout << "Najblizsze punkty: [(" << point1.x << "," << point1.y << "),(" << point2.x << "," << point2.y << ")]" << ", d = " <<  minD << std::endl;

    return {point1, point2};
}