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
"Michalak","Szewczyk","Ostrowski","Tomaszewski","Zalewski","Wroblewski","Pietrzak"};

std::string pozycje[4] = { "Bramkarz", "Obronca", "Pomocnik", "Napastnik" };


struct pilkarz 
{
    std::string nazwisko;
    int wiek;
    std::string pozycja;

    pilkarz* next;
};



void List(pilkarz *adres, int jwiek, std::string jpoz, int jwartosc, std::string &pozz)
{
    pilkarz* poprzedni, * aktualny;

    int l_br = 0;

    //tworzenie
    poprzedni = NULL;
    aktualny = NULL;
    adres = NULL;

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
            adres = aktualny;
        }
        else
        {
            poprzedni->next = aktualny;
        }
    }
    
    //wypisywanie
    int id = 1;

    aktualny = adres;

    while (aktualny != NULL)
    {
        if (jwiek == aktualny->wiek && jpoz==aktualny->pozycja)
        {
            std::cout << id << "." << aktualny->nazwisko << " " << aktualny->pozycja << " " << aktualny->wiek << "\n\n";
        }
        
        id++;

       aktualny = aktualny->next;
    }

    //usuwanie pierwszego zawodnika o wieku wiekszym od jwartosc
    aktualny = adres;
    int jeden = 0;
    while (aktualny->next != NULL)
    {
        poprzedni = aktualny;
        aktualny = aktualny->next;
        if (jeden == 0 && aktualny->wiek>jwartosc)
        {
            
            if (aktualny->next != NULL)
            {
                poprzedni->next = aktualny->next;
                poprzedni = aktualny;
                aktualny = aktualny->next;
                pozz = poprzedni->pozycja;
                delete poprzedni;
            }
            else
            {
                pozz = aktualny->pozycja;
                delete aktualny;
                aktualny = poprzedni;
                aktualny->next = NULL;
            }

           
        }
    }

    //srednia wieku zawodnikow

    int suma = 0;
    int l_elementow = 0;
    double srednia;

    aktualny = adres;

    while (aktualny != NULL)
    {
        suma = suma + aktualny->wiek;
        l_elementow++;
        aktualny = aktualny->next;
    }

    srednia = static_cast<double>(suma) / l_elementow;

    return srednia;

    //zwalnianie pamieci

    aktualny = adres;

    while(aktualny != NULL)
    {
        poprzedni = aktualny;
        aktualny = aktualny->next;
        delete poprzedni;
    }
    std::cout << "\n\nPamiec zwolniona!\n\n";
}



int main()
{
    pilkarz zawodnik;
    std::string pozycjausunietego;

    srand(time(NULL));

    List(&zawodnik, 22,"Obronca", 30, pozycjausunietego);

    std::cout << "Pozycja usunietego zawodnika:" << pozycjausunietego << "\n\n";

    return 0;
}
