/** @file */
/*
Projekt PK2 - Gra w statki
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <locale.h>

int main() {
	setlocale(LC_CTYPE, ".1250");

	int m = 6;//ustalasz m i n (na razie tak, potem mo�e bardziej interaktywnie)
	int n = 3;

	/*printf("Podaj m: ");
	scanf("%d", &m);
	printf("\n Podaj n: ");
	scanf("%d", &n);
	printf("\n");*/

	int M = m + 1;	//tutaj �eby sobie troch� u�atwi� zrobi�em zmienne o 1 wi�ksze od m i n �eby nie pisa� za ka�dym razem m+1, n+1
	int N = n + 1;

	FILE* slownik;
	if ((slownik = fopen("slownik.txt", "r")) == NULL) { //sprawdzamy czy istnieje plik slownik.txt
		printf("Nie moge otworzyc pliku!\n");
		exit(1);
	}

	char* slowo = malloc(50 * sizeof(char));	//zmienne slowo i koniec do zapisywania tymczasowych sl�w z alfabetu
	char* koniec = malloc(50 * sizeof(char));

	//char koniec[] = "";

	fpos_t pozycja = 0;	//zmienna do zapisanie pozycji pliku aby wr�ci� do miejsca gdzie sko�czyli�my (pobieranie kolejnego s�owa z kolejki)

	while (fscanf(slownik, "%s", slowo)) {	//pobieranie kolejnego s�owa z kolejki s�ownika
		if (feof(slownik) != 0) {//ko�czenie programu je�li doszli�my do ko�ca pliku
			fclose(slownik);
			free(koniec);
			free(slowo);

			return 0;
		}
		//printf("%s \n", slowo); //tymczasowe wy�wietlanie

		if (strlen(slowo) == m) {	//je�eli s�owo mniejsze ni� m to nie bierzemy pod uwag�
			fgetpos(slownik, &pozycja);	//zapisywanie pozycji w kt�rej sko�czyli�my, aby nie zaczyna� poeniera� s��w z pocz�tku s�ownika (np. sko�czyli�my na arbuz wi�c zaczniemy na kolejnym a nie 5 s��w dalej)
			rewind(slownik);	//powr�t do pocz�tku pliku aby m�c por�wna� s�owo (jego ko�c�wk�) ze wszystkimi s�owami ze s�ownika
			int a = 0;	//zmienna warunkowa, kt�ra okre�la czy ko�c�wka s�owa wyst�pi�a w s�owniku
			do {
				a = 0;
				fscanf(slownik, "%s", koniec);	//pobranie kolejnej ko�c�wki do por�wnania ze s�owem
				if (feof(slownik) != 0) break;	//sprawdzenia czy nie wyst�pi� koniec pliku (czy sprawdzili�my wszystkie ko�c�wki)
				if (strlen(koniec) == n) {
					for (int i = n; i >= 0; i--) {
						if (slowo[m - i] != koniec[a])break;	//sprawdzenie n ostatnich liter s�owa w ko�c�wce (czyli czy powinni�my wykluczy� s�owo i go nie wypisa�)
						a++;	//je�eli kolejne litery si� zgadzaj� to a++
					}
				}
			} while ((slowo[n] >= koniec[0]) && a != N);	//je�eli natrafimy na liter� o wi�kszej warto�ci (ASCI) to nie ma sensu sprawdza� reszty np. pierwsza litera s�owa to a a wi�c bez sensu sprawdza� ko�c�wki zaczynaj�ce si� od b w g�r� (plik posortowany alfabetycznie), oraz je�li zgadza si� ko�c�wka od przodu to r�wnie� przerywamy

			rewind(slownik);

			if (a != N) {	//tutaj warunek je�li nie znaleziono warunku wykluczaj�cego s�owa �eby go wypisa� jako rozwi�zanie
				do {
					a = 0;
					fscanf(slownik, "%s", koniec);	//pobranie kolejnej ko�c�wki do por�wnania ze s�owem
					if (feof(slownik) != 0) break;	//sprawdzenia czy nie wyst�pi� koniec pliku (czy sprawdzili�my wszystkie ko�c�wki)
					if (slowo[m] == koniec[n]) {
						if (strlen(koniec) == n) {
							for (int i = m - 1; i >= n; i--) {
								if (slowo[i] != koniec[a])break;	//sprawdzenie n ostatnich liter s�owa w ko�c�wce (czyli czy powinni�my wykluczy� s�owo i go nie wypisa�)
								a++;	//je�eli kolejne litery si� zgadzaj� to a++
							}
						}
					}
					if (a == n) {
						printf("Rozwiazanie to: ");
						printf("%s", slowo);
						printf(",  koncowka: ");
						printf("%s", koniec);
						printf(" \n");
					}
				} while ((slowo[m - 1] >= koniec[0]) && a != N);
			}
			fsetpos(slownik, &pozycja);	//przywr�cenie pozycji pliku przed sprawdzniem ko�c�wki �eby pobiera� s�owo kolejne z kolei a nie to na kt�rym sko�czyli�my sprawdzanie ko�c�wki s�owa w tym przypadku
			a = 0;//wyzerowanie zmiennej warunkowej
		}
	}
}