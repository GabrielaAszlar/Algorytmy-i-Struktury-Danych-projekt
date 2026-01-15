#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(NULL)); // generator liczb losowych

    int M, N;

    cout << "Podaj liczbe wierszy (M): ";
    cin >> M;
    cout << "Podaj liczbe kolumn (N): ";
    cin >> N;
    cout << endl;


    // Tworzenie tablicy o wymiarach MxN
    vector<vector<int>> tablica(M, vector<int>(N));

    cout << "Wylosowana tablica:" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            tablica[i][j] = rand() % 2;
            cout << tablica[i][j] << " ";
        }
        cout << endl;
    }

    int max_pole = 0;
    int max_wys = 0;
    int max_szer = 0;

    // Algorytm sprawdzajacy
    // Wybieramy lewy górny róg prostok¹ta (w1, k1)
    for (int w1 = 0; w1 < M; w1++) {
        for (int k1 = 0; k1 < N; k1++) {

            // Wybieramy prawy dolny róg prostok¹ta (w2, k2)
            for (int w2 = w1; w2 < M; w2++) {
                for (int k2 = k1; k2 < N; k2++) {

                    // Sprawdzamy, czy wewnatrz tego prostokata sa SAME zera
                    bool same_zera = true;

                    for (int i = w1; i <= w2; i++) {
                        for (int j = k1; j <= k2; j++) {
                            if (tablica[i][j] == 1) {
                                same_zera = false;
                                break;
                            }
                        }
                        if (!same_zera) break;
                    }

                    // Jesli prostokat jest poprawny (zawiera same zera) to liczymy pole
                    if (same_zera) {
                        int wysokosc = w2 - w1 + 1;
                        int szerokosc = k2 - k1 + 1;
                        int aktualne_pole = wysokosc * szerokosc;

                        if (aktualne_pole > max_pole) {
                            max_pole = aktualne_pole;
                            max_wys = wysokosc;
                            max_szer = szerokosc;
                        }
                    }
                }
            }
        }
    }
    cout << endl;

    // Wyswietlamy wynik
    cout << "Rozmiar najwiekszej podtablicy z samych zer: " << max_wys << "x" << max_szer << endl;
    cout << "Jej pole to: " << max_pole << endl;

    return 0;
}
