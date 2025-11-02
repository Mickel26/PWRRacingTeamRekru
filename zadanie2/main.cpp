#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <vector>

struct NearestPoints {
    std::pair<double, double> point1;
    std::pair<double, double> point2;
};

bool Read(double (*&points)[2], unsigned int &n);
std::vector<std::pair<double, double>> findHalo(std::vector<std::pair<double, double>> data);
NearestPoints findNearestPoints(double (*points)[2], unsigned int n);

int main() {
    double (*data)[2] = nullptr;
    unsigned int size = 0;

    if (!Read(data, size)) {
        return 1;
    }

    findNearestPoints(data, size);

    delete[] data;
    data = nullptr;
    return 0;
}

bool Read(double (*&points)[2], unsigned int &n){
    std::cout << "Enter filename: ";
    std::string filename;
    std::cin >> filename;

    std::ifstream file(filename);

    if (file.is_open()) {
        file >> n;

        points = new double[n][2];

        double x,y;

        for (int i = 0; i < n; i++) {
            file >> x >> y;
            points[i][0] = x;
            points[i][1] = y;
        }

        file.close();
        return true;
    } else {
        std::cout << "Couldn't open file";
        return false;
    }
}

/*std::vector<std::pair<double, double>> findHalo(std::vector<std::pair<double, double>> data) {


    return data;
}*/

NearestPoints findNearestPoints(double (*points)[2], unsigned int n) {
    double minD = std::numeric_limits<double>::max();
    std::pair<double, double> point1;
    std::pair<double, double> point2;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            double x = points[j][0] - points[i][0];
            double y = points[j][1] - points[i][1];

            double d = sqrt((x * x) + (y * y));
            if (d < minD) {
                minD = d;
                point1 = {points[i][0], points[i][1] };
                point2 = {points[j][0], points[j][1] };
            }
        }
    }

    std::cout << "Najblizsze punkty: [(" << point1.first << "," << point1.second << "),(" << point2.first << "," << point2.second << ")]" << ", d = " <<  minD << std::endl;

    return {point1, point2};
}