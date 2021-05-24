#include <iostream>

struct liczba
{
	int dana;
	liczba *next;
};

void print_values(liczba* glowa) {
	std::cout << "\nValues: ";
	while (glowa != NULL) {
		std::cout << glowa->dana << " ";
		glowa = glowa->next;
	}

	std::cout << std::endl;
}

void zamiana(liczba **glowa)
{
	if (*glowa == NULL || (*glowa)->next == NULL)
	{
		return;
	}
		
	
	liczba* aktualna, *tmp;

	aktualna = tmp = *glowa;

	while (aktualna->next != NULL)
	{
		tmp = aktualna;
		aktualna = aktualna->next;
	}

	tmp->next = *glowa;
	aktualna->next = (*glowa)->next;
	(*glowa)->next = NULL;
	*glowa = aktualna;
	
}

void wypisz(liczba *adres)
{

	if (adres != NULL)
	{

		std::cout << adres->dana << " ";

		adres = adres->next;

		wypisz(adres);
	}
}

int main()
{
	liczba* glowa, * aktualna, * poprzednia, * tmp;
	int nowa;

	aktualna = NULL;
	poprzednia = NULL;
	glowa = aktualna;

	//tworzenie listy
	std::cout << "Wprowadz liczbe:";
	std::cin >> nowa;
	std::cout << std::endl;

	while (nowa > 9)
	{
		poprzednia = aktualna;
		aktualna = new liczba;
		aktualna->dana = nowa;
		aktualna->next = NULL;
		if (poprzednia != NULL)
		{
			poprzednia->next = aktualna;
		}
		else
		{
			glowa = aktualna;
		}
	

		std::cout << "Wprowadz liczbe:";
		std::cin >> nowa;
		std::cout << std::endl;
	}

	std::cout << "Rezultat po wprowadzeniu elementow listy:";
	if (glowa == NULL)
	{
		std::cout << "Lista pusta!\n";
	}
	else
	{
		wypisz(glowa);
	}

	std::cout << std::endl;

	//usuwanie liczb parzystych
	aktualna = glowa;
	poprzednia = NULL;

	while (aktualna != NULL)
	{
		if (aktualna->dana % 2 == 0)
		{
			if (aktualna == glowa)
			{
				glowa = glowa->next;
			}	
			else
			{
				poprzednia->next = aktualna->next;
			}

			tmp = aktualna;
			aktualna = aktualna->next;

			delete tmp;
		}
		else
		{
			poprzednia = aktualna;
			aktualna = aktualna->next;
		}
	}

	std::cout << "Po usunieciu liczb parzystych:\n";
	if (glowa == NULL)
	{
		std::cout << "lista pusta\n";
	}
	else
	{
		wypisz(glowa);
	}
	std::cout << std::endl;	

	//zamiana pierwszego z ostatnim elementem


	/*
	if (glowa != NULL)
	{
		tmp = new liczba;
		tmp2 = new liczba;


		aktualna = glowa;

		tmp = aktualna;

		tmp2 = aktualna;

		while (aktualna->next != NULL)
		{
			tmp = aktualna;
			aktualna = aktualna->next;
		}

		tmp->next = glowa;
		aktualna->next = glowa->next;
		glowa->next = NULL;
		glowa = aktualna;

		delete tmp;
		delete tmp2;
	}
	*/

	zamiana(&glowa);
	
	
	std::cout << "Po zamianie pierwszego elementu listy z ostatnim:\n";
	
	if (glowa == NULL)
	{
		std::cout << "lista pusta\n";
	}
	else
	{
		print_values(glowa);
	}
	std::cout << std::endl;


	//zwalnianie pamieci

	while (glowa != NULL)
	{
		poprzednia = glowa;
		glowa = glowa->next;
		delete poprzednia;
	}

	std::cout << "Pamiec zwolniona\n";

	system("Pause");
	return 0;
}