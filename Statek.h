#ifndef ADAM_FLESZAR_STATEK_H
#define ADAM_FLESZAR_STATEK_H

#include <vector>
#include "Pole.h"
#include "Plansza.h"

static const int ORIENTACJA_POZIOMA = 0;
static const int ORIENTACJA_PIONOWA = 1;

class Statek {
private:
    int x_index;
    int y_index;
    int orientacja;
    int dlugosc;
    vector<Pole*> pola;
    vector<Pole*> pola_sasiednie;
    bool czy_zatopiony;

    bool sprawdz_czy_zatopiony();

public:
    Statek();
    Statek(int dlugosc);

    bool czy_mozna_utworzyc_statek(Plansza *plansza, int orientacja, int x_index, int y_index);
    void utworz_statek(Plansza *plansza, int orientacja, int x_index, int y_index);
    bool czy_trafiony_zatopiony();
    void odkryj_sasiednie_pola();

    void operator--(int);

    friend class Gracz;
    friend class Interfejs;
};



#endif //ADAM_FLESZAR_STATEK_H
