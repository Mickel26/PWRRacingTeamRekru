#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>


//Struktura do punktów z pliku
struct Point {
    float x;
    float y;
};

//Struktura na 2 najbliższe punkty
struct NearestPoints {
    Point point1;
    Point point2;
};

//Funkcja odczytuje dane z pliku i zapisuje je do tablicy, zwraca True lub False w zależności od tego czy uda się odczytać plik
bool Read(Point *&points, unsigned int &n);

//Funkcja sprawdza kierunek w którym idą 3 punkty i zwraca:
//0 = są na jdnej linii
//1 = zgodny z ruchem wskazówek zegara
//2 = przeciwko ruchu wskazówek zegara
int orientation(Point p, Point q, Point r);

//algorytm Jarvisa aby uzyskać otoczkę
void findConvexHull(Point *points, unsigned int n);
//prosta funckja zwracają strukturę (2 najblizsze punkty) oraz oblicza i wypisuje rowanie prsotej tych punktów
NearestPoints findNearestPoints(Point *points, unsigned int n);

int main() {
    Point *data = nullptr;
    unsigned int size = 0;

    if (!Read(data, size)) {
        delete[] data;
        data = nullptr;
        return 1;
    }

    findConvexHull(data, size);
    NearestPoints zad3 = findNearestPoints(data, size);

    delete[] data;
    data = nullptr;
    return 0;
}

bool Read(Point *&points, unsigned int &n){
    std::cout << "Nazwa pliku: ";
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
        return false;
    }
}

int orientation(Point p, Point q, Point r) {
    int o = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (o == 0) return 0;
    else if (o > 0) return 1;
    else return 2;
}

void findConvexHull(Point *points, unsigned int n) {
    //jeśli puntków jest mniej niż 3, nie ma otoczki
    if (n < 3) {
        return;
    }

    //vector z punktami należącymi do otoczki
    std::vector<Point> hull;

    //szukanie punktu najbardziej wysuniętego w lewo
    int l = 0;

    for (int i = 1; i < n; i++) {
        if (points[i].x < points[l].x) {
            l = i;
        }
    }

    int p = l;
    int q = 0;

    //pętla zaczyna od pierwszego punktu p i działa dopóki do niego nie wróci
    do {
        hull.push_back(points[p]);

        //wybranie kolejnego punktu
        q = (p + 1) % n;

        for (unsigned int i = 0; i < n; i++) {
            //sprawdzenie czy q czy i powinno być następnym punktem
            if (orientation(points[p], points[i], points[q]) == 2) {
                q = i;
            }
        }

        p = q;
    } while (p != l);

    std::cout << "Otoczka: ";
    for (auto & i : hull) {
        std::cout << "(" << i.x << "," << i.y << "),";
    }
}

NearestPoints findNearestPoints(Point *points, unsigned int n) {
    float minD = std::numeric_limits<float>::max();
    Point point1 = {0.0,0.0};
    Point point2 = {0.0,0.0};

    //porównywanie odgległości między punktami points[i] i points[j], zapisywanie wartości jeśli mniejsza niż dotychczasowa najmniejsza
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

    std::cout << "\nNajblizsze punkty: [(" << point1.x << "," << point1.y << "),(" << point2.x << "," << point2.y << ")]" << ", d = " <<  minD << std::endl;

    return {point1, point2};
}