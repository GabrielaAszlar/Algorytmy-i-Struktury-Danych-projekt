#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

// Funkcja oblicza maksymalne pole z samych zer
int obliczMaxPole(const vector<vector<int>>& tablica) {
    if (tablica.empty()) return 0;

    int M = tablica.size();     // liczba wierszy
    int N = tablica[0].size();  // liczba kolumn
    int max_pole = 0;

    // Wyber lewego gornego rogu (w1, k1)
    for (int w1 = 0; w1 < M; w1++) {
        for (int k1 = 0; k1 < N; k1++) {
            // Wybór prawego dolnego rogu (w2, k2)
            for (int w2 = w1; w2 < M; w2++) {
                for (int k2 = k1; k2 < N; k2++) {

                    bool same_zera = true;
                    // Sprawdzamy kazda komorke od (w1, k1) do (w2, k2)
                    for (int i = w1; i <= w2; i++) {
                        for (int j = k1; j <= k2; j++) {
                            // Jesli znajdziemy chociaz jedna jedynke przerywamy
                            if (tablica[i][j] == 1) {
                                same_zera = false;
                                break;
                            }
                        }
                        if (!same_zera) break;
                    }

                    // Obliczanie pola, jesli znaleziono prostokat z samych zer
                    if (same_zera) {
                        int wysokosc = w2 - w1 + 1;
                        int szerokosc = k2 - k1 + 1;
                        int aktualne_pole = wysokosc * szerokosc;

                        // Sprawdzamy czy to najwieksze pole
                        if (aktualne_pole > max_pole) {
                            max_pole = aktualne_pole;
                        }
                    }
                }
            }
        }
    }

    return max_pole;
}

// Funckje testujace poprawnosc algorytmu

int test1() {
    // Klasyczna macierz mieszana
    vector<vector<int>> macierz = {
        {1, 0, 0, 1},
        {1, 0, 0, 1},
        {1, 1, 1, 0}
    };
    int wynik = obliczMaxPole(macierz);
    cout << "Test 1: Macierz mieszana" << endl;
    cout << "Wynik: " << obliczMaxPole(macierz) << " (Poprawny: 4)" << endl << endl;
    return wynik;
}

int test2() {
    // Macierz samych zer
    vector<vector<int>> macierz = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    int wynik = obliczMaxPole(macierz);
    cout << "Test 2: Macierz samych zer" << endl;
    cout << "Wynik: " << obliczMaxPole(macierz) << " (Poprawny: 9)" << endl << endl;
    return wynik;
}

int test3() {
    // Macierz samych jedynek
    vector<vector<int>> macierz = {
        {1, 1, 1},
        {1, 1, 1}
    };
    int wynik = obliczMaxPole(macierz);
    cout << "Test 3: Macierz samych jedynek" << endl;
    cout << "Wynik: " << obliczMaxPole(macierz) << " (Poprawny: 0)" << endl << endl;
    return wynik;
}

int main() {

// Zapis wynikow do pliku tekstowego (wynik.txt)
    fstream plikWynik;
    plikWynik.open("wynik.txt", ios::out | ios::app);

    plikWynik << "Wynik Test 1: " << test1() << endl;
    plikWynik << "Wynik Test 2: " << test2() << endl;
    plikWynik << "Wynik Test 3: " << test3() << endl;


    // Odczyt z pliku tekstowego (dane.txt)
    ifstream plikDane("dane.txt"); // otwieramy plik do odczytu

    if(plikDane.good()){
        int w, k;
        plikDane >> w >> k; // Wczytujemy wymiary

        if (w > 0 && k > 0) {
            // Tworzymy macierz o wczytanych wymiarach
            vector<vector<int>> macierzZPliku(w, vector<int>(k));

            for (int i = 0; i < w; i++) {
                for (int j = 0; j < k; j++) {
                    plikDane >> macierzZPliku[i][j];
                }
            }

            // Obliczamy wynik
            int wynikZPliku = obliczMaxPole(macierzZPliku);

            // Wypisujemy na ekran
            cout << "Test z pliku (dane.txt)" << endl;
            cout << "Wczytano macierz " << w << "x" << k << endl;
            cout << "Wynik: " << wynikZPliku << endl;

            // Zapisujemy do pliku z wynikami
            plikWynik << "Wynik z pliku dane.txt: " << wynikZPliku << endl;
    }
    }
    plikDane.close(); // Zamykamy plik z danymi

    plikWynik.close(); // Zamykamy plik z wynikami

    return 0;
}
