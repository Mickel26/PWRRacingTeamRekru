#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <vector>

std::vector<std::pair<double, double>> Read();
std::vector<std::pair<double, double>> findHalo(std::vector<std::pair<double, double>> data);
std::pair<std::pair<double, double>, double> findNearestPoints(std::vector<std::pair<double, double>> data);

int main() {
    std::vector<std::pair<double, double>> data = Read();

    /*for (const auto [x, y] : data) {
        std:: cout << x << ' ' << y << std::endl;
    }*/

    findHalo(data);
    findNearestPoints(data);

    return 0;
}

std::vector<std::pair<double, double>> Read() {
    std::cout << "Enter filename: ";
    std::string filename = "";
    std::cin >> filename;

    std::ifstream file(filename);
    int n = 0;
    std::vector<std::pair<double, double>> data;

    if (file.is_open()) {
        file >> n;
        data.reserve(n);

        double x,y;

        for (int i = 0; i < n; i++) {
            file >> x >> y;
            data.push_back({x,y});
        }

        file.close();
    } else {
        std::cout << "Couldn't open file";
    }

    return data;
}

std::vector<std::pair<double, double>> findHalo(std::vector<std::pair<double, double>> data) {


    return data;
}

std::pair<std::pair<double, double>, double> findNearestPoints(std::vector<std::pair<double, double>> data) {
    double minD = std::numeric_limits<double>::max();
    std::pair<double, double> point1;
    std::pair<double, double> point2;

    for (int i = 0; i < data.size() - 1; i++) {
        for (int j = i + 1; j < data.size(); j++) {
            double x = data[j].first - data[i].first;
            double y = data[j].second - data[i].second;

            double d = sqrt((x * x) + (y * y));
            if (d < minD) {
                minD = d;
                point1 = data[i];
                point2 = data[j];
            }
        }
    }

    std::cout << "Najblizsze punkty: [(" << point1.first << "," << point1.second << "),(" << point2.first << "," << point2.second << ")]" << ", d = " <<  minD << std::endl;

    return make_pair(point1, minD);
}