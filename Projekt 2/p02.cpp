#include <iostream>


//########################
//###  Z M I E N N E   ###
//########################

int const l_pilkarzy = 400;

int max_br = 3;//maxymalna liczba bramkarzy, aby liczba zawodników grających na tej pozycji nie przewyższała liczby zawodników na innych pozycjach

//########################


std::string nazwiska[50] = { "Nowak", "Kowalski", "Wisniewski",
"Wojcik", "Kowalczyk", "Kaminski", "Lewandowski", "Zielinski", "Wozniak",
"Szymanski", "Dabrowski", "Kozlowski", "Jankowski", "Mazur", "Wojciechowski",
"Kwiatkowski", "Krawczyk", "Kaczmarek", "Piotrowski", "Grabowski", "Zajac",
"Krol", "Pawlowski", "Michalski", "Wrobel", "Jablonski", "Wieczorek",
"Nowakowski", "Majewski", "Olszewski", "Stepien","Jaworski","Dudek","Adamczyk",
"Malinowski","Pawlak","Gorski","Sikora","Nowicki","Witkowski","Walczak","Baran","Rutkowski",
"Michalak","Szewczyk","Ostrowski","Tomaszewski","Zalewski","Wroblewski","Pietrzak" };

std::string pozycje[4] = { "Bramkarz", "Obronca", "Pomocnik", "Napastnik" };


struct pilkarz
{
    std::string nazwisko;
    int wiek;
    std::string pozycja;

    pilkarz* next;
};

pilkarz* poprzedni, * aktualny;


float List(pilkarz* adres, int jwiek, std::string jpoz, int jwartosc, std::string& pozz)
{


    //wypisywanie
    int id = 1;

    aktualny = adres;

    while (aktualny != NULL)
    {
        if (jwiek == aktualny->wiek && jpoz == aktualny->pozycja)
        {
            std::cout << id << "." << aktualny->nazwisko << " " << aktualny->pozycja << " " << aktualny->wiek << "\n\n";
        }

        id++;

        aktualny = aktualny->next;
    }

    //usuwanie pierwszego zawodnika o wieku wiekszym od jwartosc
    aktualny = adres;

    while (aktualny != NULL)
    {
        if (jwartosc > aktualny->wiek)
        {
            if (poprzedni != NULL)
            {
                pozz = aktualny->pozycja;
                poprzedni->next = aktualny->next;
                delete aktualny;
                aktualny = poprzedni->next;
                break;
            }
            else
            {
                pozz = aktualny->pozycja;
                poprzedni = aktualny;
                aktualny = aktualny->next;
                delete poprzedni;
                break;
            }

        }
        else
        {
            poprzedni = aktualny;
            aktualny = aktualny->next;
        }

    }

    aktualny = NULL;

    //srednia wieku zawodnikow

    int suma = 0;
    int l_elementow = 0;
    float srednia;

    aktualny = adres;

    while (aktualny != NULL)
    {
        suma = suma + aktualny->wiek;
        l_elementow++;
        aktualny = aktualny->next;
    }

    srednia = static_cast<double>(suma) / l_elementow;

    //zwalnianie pamieci

    aktualny = adres;

    while (aktualny != NULL)
    {
        poprzedni = aktualny;
        aktualny = aktualny->next;
        delete poprzedni;
    }
    std::cout << "\n\nPamiec zwolniona!\n\n";

    //srednia
    return srednia;
}



int main()
{
    pilkarz* glowa;

    int l_br = 0;

    //tworzenie
    poprzedni = NULL;
    aktualny = NULL;
    glowa = NULL;

    for (int i = 0; i < l_pilkarzy; i++)
    {

        poprzedni = aktualny;
        aktualny = new pilkarz;


        aktualny->nazwisko = nazwiska[rand() % 31];
        aktualny->wiek = rand() % 18 + 18;
        aktualny->pozycja = pozycje[rand() % 4];

        if (aktualny->pozycja == "Bramkarz")
        {
            l_br++;
            while (l_br > 3)
            {
                aktualny->pozycja = pozycje[rand() % 4];
                if (aktualny->pozycja != "Bramkarz")
                {
                    l_br--;
                }
            }
        }

        aktualny->next = NULL;

        if (poprzedni == NULL)
        {
            glowa = aktualny;
        }
        else
        {
            poprzedni->next = aktualny;
        }
    }


    pilkarz zawodnik;
    std::string pozycjausunietego;

    srand(time(NULL));

    std::cout << "Srednia wieku zawodnikow:" << List(glowa, 22, "Obronca", 30, pozycjausunietego) << "\n";

    std::cout << "Pozycja usunietego zawodnika:" << pozycjausunietego << "\n\n";

    return 0;
}