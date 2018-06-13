#include "Statek.h"

Statek::Statek() {
}

Statek::Statek(int dlugosc) {
    this->dlugosc = dlugosc;
    this->czy_zatopiony = false;
}

bool Statek::czy_mozna_utworzyc_statek(Plansza *plansza, int orientacja, int x_index, int y_index) {
    Pole *pole = plansza->macierz_pol[y_index][x_index];
    for (int i=-1; i<dlugosc+1; i++) {
        for (int j=-1; j<2; j++) {
            int x_pozycja;
            int y_pozycja;

            if (orientacja == ORIENTACJA_POZIOMA) {
                x_pozycja = pole->x_pozycja + i;
                y_pozycja = pole->y_pozycja + j;
            } else {
                x_pozycja = pole->x_pozycja + j;
                y_pozycja = pole->y_pozycja + i;
            }

            if (x_pozycja >= 0 && x_pozycja < plansza->szerokosc && y_pozycja >= 0 && y_pozycja < plansza->wysokosc) {
                if (plansza->macierz_pol[y_pozycja][x_pozycja]->czy_nalezy_do_statku) {
                    return false;
                }
            } else if (i >= 0 && i < dlugosc && j == 0) {
                return false;
            }
        }
    }
    return true;
}

void Statek::utworz_statek(Plansza *plansza, int orientacja, int x_index, int y_index) {
    Pole *pole = plansza->macierz_pol[y_index][x_index];
    this->x_index = x_index;
    this->y_index = y_index;
    this->orientacja = orientacja;
    for (int i=-1; i<dlugosc+1; i++) {
        for (int j=-1; j<2; j++) {
            int x_pozycja;
            int y_pozycja;

            if (orientacja == ORIENTACJA_POZIOMA) {
                x_pozycja = pole->x_pozycja + i;
                y_pozycja = pole->y_pozycja + j;
            } else {
                x_pozycja = pole->x_pozycja + j;
                y_pozycja = pole->y_pozycja + i;
            }

            if (x_pozycja >= 0 && x_pozycja < plansza->szerokosc && y_pozycja >= 0 && y_pozycja < plansza->wysokosc) {
                Pole *pole_biezace = plansza->macierz_pol[y_pozycja][x_pozycja];
                if (i >= 0 && i < dlugosc && j == 0) {
                    pole_biezace->czy_nalezy_do_statku = true;
                    pola.push_back(pole_biezace);
                } else {
                    pola_sasiednie.push_back(pole_biezace);
                }
            }
        }
    }
}

bool Statek::czy_trafiony_zatopiony() {
    bool czy_byl_zatopiony = czy_zatopiony;
    czy_zatopiony = sprawdz_czy_zatopiony();
    return !czy_byl_zatopiony && czy_zatopiony;
}

void Statek::odkryj_sasiednie_pola() {
    for (int i=0; i < pola_sasiednie.size(); i++) {
        pola_sasiednie[i]->czy_odkryte = true;
    }
}

bool Statek::sprawdz_czy_zatopiony() {
    if (czy_zatopiony) {
        return true;
    }
    for(int i=0; i<dlugosc; i++) {
        if (!pola[i]->czy_odkryte){
            return false;
        }
    }
    return true;
}

void Statek::operator--(int) {
    odkryj_sasiednie_pola();
}


