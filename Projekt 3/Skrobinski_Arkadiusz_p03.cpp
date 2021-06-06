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
wezel* znajdz(wezel* wez, std::string wyraz)
{
    if (wez == NULL || wyraz == wez->wyraz)
    {
        return wez;
    }

    if (wyraz < wez->wyraz)
    {
        return znajdz(wez->lewy, wyraz);
    }
    else
    {
        return znajdz(wez->prawy, wyraz);
    }
}

wezel* parent(wezel* wez, std::string wyraz)
{
    if (wez->prawy == znajdz(wez, wyraz) || wez->lewy == znajdz(wez, wyraz))
    {
        return wez;
    }
    else
    {
        return parent(wez->lewy, wyraz);
        return parent(wez->prawy, wyraz);
    }
}


//usuwanie podanego wyrazu
void usun(wezel* adres, std::string nwyraz)
{
    wezel* dousuniecia = znajdz(adres, nwyraz);
    wezel* poprzednik = parent(adres, nwyraz);

    if (adres != NULL)
    {
        if (dousuniecia->prawy == NULL && dousuniecia->lewy == NULL)
        {
            if (poprzednik->lewy == dousuniecia)
            {
                poprzednik->lewy = NULL;
            }
            else if (poprzednik->prawy == dousuniecia)
            {
                poprzednik->prawy = NULL;
            }

            delete dousuniecia;
        }
        else if (dousuniecia->prawy == NULL && dousuniecia->lewy)
        {
            if (poprzednik->lewy == dousuniecia)
            {
                poprzednik->lewy = dousuniecia->lewy;

                delete dousuniecia;
            }
            else if (poprzednik->prawy == dousuniecia)
            {
                poprzednik->prawy = dousuniecia->lewy;

                delete dousuniecia;
            }
        }
        else if (dousuniecia->prawy && dousuniecia->lewy == NULL)
        {
            if (poprzednik->lewy == dousuniecia)
            {
                poprzednik->lewy = dousuniecia->prawy;
                delete dousuniecia;
            }
            else if (poprzednik->prawy == dousuniecia)
            {
                poprzednik->prawy = dousuniecia->prawy;
                delete dousuniecia;
            }
        }
        else if (dousuniecia->prawy && dousuniecia->lewy)
        {
            if (poprzednik->lewy == dousuniecia)
            {
                poprzednik->lewy = dousuniecia->prawy;
                delete dousuniecia;
            }
            else if (poprzednik->prawy == dousuniecia)
            {
                poprzednik->prawy = dousuniecia->prawy;
                delete dousuniecia;
            }
        }
            


    }

    wyswietl(adres);
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

    zwalpamiec(korzen);
    std::cout << "Pamiec zwolniona!\n";
}



int main()
{
    wyrazy();


    return 0;
}
