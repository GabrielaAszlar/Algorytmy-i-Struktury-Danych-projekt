#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

// Funkcja pomocnicza
int obliczPoleHistogramu(vector<int> wysokosci) {
    stack<int> stos; // Przechowuje indeksy slupkow
    int maxPole = 0;

    // Dodajemy 0 na koniec stosu, aby miec pewnosc ze wszystkie elementy zostana policzone
    wysokosci.push_back(0);

    for (int i = 0; i < wysokosci.size(); i++) {
        // Petla while wykonuje sie, gdy bieazcy slupek jest nizszy od tego na stosie.
        while (!stos.empty() && wysokosci[i] < wysokosci[stos.top()]) {

            // Pobieramy wysokosc najnowszego slupka ze stosu
            int wysokosc = wysokosci[stos.top()];
            stos.pop();

            // Obliczamy szerokosc prostokata
            int szerokosc = stos.empty() ? i : (i - stos.top() - 1);

            // Aktualizujemy jesli znalezlismy wieksze pole
            maxPole = max(maxPole, wysokosc * szerokosc);
        }
        stos.push(i);
    }
    return maxPole;
}

// Glowna funkcja
int obliczMaxPole (const vector<vector<int>>& macierz) {
    if (macierz.empty()) return 0;

    int wiersze = macierz.size();
    int kolumny = macierz[0].size();
    int globalnyMax = 0;

    // Tablica 'histogram' przechowuje aktualne wysokosci slupkow zer
    // dla aktualnie przetwarzanego wiersza.
    vector<int> histogram(kolumny, 0);

    // Iterujemy przez kazdy wiersz macierzy
    for (int i = 0; i < wiersze; i++) {
        for (int j = 0; j < kolumny; j++) {
            // Jesli mamy 0, slupek rosnie. Jesli 1, slupek sie zeruje.
            if (macierz[i][j] == 0) {
                histogram[j] += 1;
            } else {
                histogram[j] = 0;
            }
        }
        // Obliczamy max pole dla aktualnego wiersza. Uzywamy funkcji pomocniczej
        int maxWiersza = obliczPoleHistogramu(histogram);

        // Sprawdzamy, czy wynik z tego wiersza jest nowym rekordem
        globalnyMax = max(globalnyMax, maxWiersza);
    }

    return globalnyMax;
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

