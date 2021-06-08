#include <iostream>
#include <fstream>

//########################
//####  Z M I E N N E ####
//########################

std::string const plik = "wyrazy.txt";

//############################

std::string wyrazzpliku;

//############################

struct wezel
{
    std::string wyraz;

    wezel* lewy;
    wezel* prawy;
};

//dodawanie wezlow
void dodajwezel(wezel *&wez, std::string dana)
{
    

 
    if (wez == NULL)//wyrazy, ktore sie powtarzaja nie zostana dodane do drzewka
    {
        wez = new wezel;
        wez->wyraz = dana;
        wez->lewy = NULL;
        wez->prawy = NULL;
    }
    else if (dana > wez->wyraz)
    {
        dodajwezel(wez->prawy, dana);
    }
    else if (dana < wez->wyraz)
    {
        dodajwezel(wez->lewy, dana);
    }
    
 

    
}

//wyswietlanie posortowanego drzewka (inorder)
void wyswietl(wezel* wez)
{
    if (wez != NULL) 
    {
       
        wyswietl(wez->lewy);
        std::cout << wez->wyraz << " ";
        wyswietl(wez->prawy);

        
    }
    else
    {
        return;
    }

}

//dodawanie wyrazow z klawiatury
void dodajzklaw(wezel *adres)
{
    int ile;
    std::string nwyraz;

    std::cout << "Ile wyrazow chcesz dodac:";
    std::cin >> ile;
    std::cout << "\n";

    for (int i = 0; i < ile; i++)
    {
        std::cout << "Podaj wyraz nr " << i + 1 << ":";
        std::cin >> nwyraz;
        dodajwezel(adres, nwyraz);
    }

    wyswietl(adres);
}

//szukanie wyrazu
void znajdz(wezel* &wez, std::string wyraz, wezel* &poprzednik)
{

    while (wez != NULL && wez->wyraz != wyraz)
    {
        poprzednik = wez;

        if (wyraz < wez->wyraz)
        {
            wez = wez->lewy;
        }
        else
        {
            wez = wez->prawy;
        }
    }
}


wezel* min(wezel* adres)
{
    while (adres->lewy != NULL)
    {
        adres = adres->lewy;
    }

    return adres;
}

//usuwanie podanego wyrazu
void usun(wezel* adres, std::string nwyraz)
{
    wezel* dousuniecia = adres;
    wezel* poprzednik = NULL;

    znajdz(dousuniecia, nwyraz, poprzednik);

    if (adres != NULL)
    {
        if (dousuniecia->lewy == NULL && dousuniecia->prawy == NULL)
        {
            if (dousuniecia != adres)
            {
                if (poprzednik->lewy == dousuniecia)
                {
                    poprzednik->lewy = NULL;
                }
                else
                {
                    poprzednik->prawy = NULL;
                }
            }
            else
            {
                adres = NULL;
            }
            delete dousuniecia;
        }
        else if (dousuniecia->lewy && dousuniecia->prawy)
        {
            wezel* nastepca = min(dousuniecia);

            std::string val = nastepca->wyraz;

            usun(adres, nastepca->wyraz);

            dousuniecia->wyraz = val;
        }
        else
        {
            wezel* dziecko = (dousuniecia->lewy) ? dousuniecia->lewy: dousuniecia->prawy;
            if (dousuniecia != adres)
            {
                if (dousuniecia == poprzednik->lewy)
                {
                    poprzednik->lewy = dziecko;
                }
                else
                {
                    poprzednik->prawy = dziecko;
                }
            }
            else
            {
                adres = dziecko;
            }
                delete dousuniecia;

        }
    }

}

//zwalnienaie pamieci
void zwalpamiec(wezel*& adres) {
    wezel* pom;
    if (adres != NULL) {
        zwalpamiec(adres->lewy);
        zwalpamiec(adres->prawy);
        pom = adres;
        adres = NULL;
        delete pom;
    }

}

void wyrazy()
{
    wezel *korzen;
    korzen = NULL;
    std::string wyraz;
   
    std::ifstream txt;
    txt.open(plik);
    if (txt)
    {
        while (!txt.eof())
        {
            txt >> wyrazzpliku;
          
            dodajwezel(korzen, wyrazzpliku);
        }
    }
    txt.close();

    wyswietl(korzen);
    std::cout << "\n";

    dodajzklaw(korzen);

    std::cout << "\n\n";

    std::cout << "Podaj wyraz ktory chcesz usunac:";
    std::cin >> wyraz;
    std::cout << "\n";
    usun(korzen, wyraz);
    wyswietl(korzen);

    zwalpamiec(korzen);
    std::cout << "Pamiec zwolniona!\n";
}



int main()
{
    wyrazy();


    return 0;
}
