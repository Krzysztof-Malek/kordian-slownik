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

	int m = 6;//ustalasz m i n (na razie tak, potem mo¿e bardziej interaktywnie)
	int n = 3;

	/*printf("Podaj m: ");
	scanf("%d", &m);
	printf("\n Podaj n: ");
	scanf("%d", &n);
	printf("\n");*/

	int M = m + 1;	//tutaj ¿eby sobie trochê u³atwiæ zrobi³em zmienne o 1 wiêksze od m i n ¿eby nie pisaæ za ka¿dym razem m+1, n+1
	int N = n + 1;

	FILE* slownik;
	if ((slownik = fopen("slownik.txt", "r")) == NULL) { //sprawdzamy czy istnieje plik slownik.txt
		printf("Nie moge otworzyc pliku!\n");
		exit(1);
	}

	char* slowo = malloc(50 * sizeof(char));	//zmienne slowo i koniec do zapisywania tymczasowych slów z alfabetu
	char* koniec = malloc(50 * sizeof(char));

	//char koniec[] = "";

	fpos_t pozycja = 0;	//zmienna do zapisanie pozycji pliku aby wróciæ do miejsca gdzie skoñczyliœmy (pobieranie kolejnego s³owa z kolejki)

	while (fscanf(slownik, "%s", slowo)) {	//pobieranie kolejnego s³owa z kolejki s³ownika
		if (feof(slownik) != 0) {//koñczenie programu jeœli doszliœmy do koñca pliku
			fclose(slownik);
			free(koniec);
			free(slowo);

			return 0;
		}
		//printf("%s \n", slowo); //tymczasowe wyœwietlanie

		if (strlen(slowo) == m) {	//je¿eli s³owo mniejsze ni¿ m to nie bierzemy pod uwagê
			fgetpos(slownik, &pozycja);	//zapisywanie pozycji w której skoñczyliœmy, aby nie zaczynaæ poenieraæ s³ów z pocz¹tku s³ownika (np. skoñczyliœmy na arbuz wiêc zaczniemy na kolejnym a nie 5 s³ów dalej)
			rewind(slownik);	//powrót do pocz¹tku pliku aby móc porównaæ s³owo (jego koñcówkê) ze wszystkimi s³owami ze s³ownika
			int a = 0;	//zmienna warunkowa, która okreœla czy koñcówka s³owa wyst¹pi³a w s³owniku
			do {
				a = 0;
				fscanf(slownik, "%s", koniec);	//pobranie kolejnej koñcówki do porównania ze s³owem
				if (feof(slownik) != 0) break;	//sprawdzenia czy nie wyst¹pi³ koniec pliku (czy sprawdziliœmy wszystkie koñcówki)
				if (strlen(koniec) == n) {
					for (int i = n; i >= 0; i--) {
						if (slowo[m - i] != koniec[a])break;	//sprawdzenie n ostatnich liter s³owa w koñcówce (czyli czy powinniœmy wykluczyæ s³owo i go nie wypisaæ)
						a++;	//je¿eli kolejne litery siê zgadzaj¹ to a++
					}
				}
			} while ((slowo[n] >= koniec[0]) && a != N);	//je¿eli natrafimy na literê o wiêkszej wartoœci (ASCI) to nie ma sensu sprawdzaæ reszty np. pierwsza litera s³owa to a a wiêc bez sensu sprawdzaæ koñcówki zaczynaj¹ce siê od b w górê (plik posortowany alfabetycznie), oraz jeœli zgadza siê koñcówka od przodu to równie¿ przerywamy

			rewind(slownik);

			if (a != N) {	//tutaj warunek jeœli nie znaleziono warunku wykluczaj¹cego s³owa ¿eby go wypisaæ jako rozwi¹zanie
				do {
					a = 0;
					fscanf(slownik, "%s", koniec);	//pobranie kolejnej koñcówki do porównania ze s³owem
					if (feof(slownik) != 0) break;	//sprawdzenia czy nie wyst¹pi³ koniec pliku (czy sprawdziliœmy wszystkie koñcówki)
					if (slowo[m] == koniec[n]) {
						if (strlen(koniec) == n) {
							for (int i = m - 1; i >= n; i--) {
								if (slowo[i] != koniec[a])break;	//sprawdzenie n ostatnich liter s³owa w koñcówce (czyli czy powinniœmy wykluczyæ s³owo i go nie wypisaæ)
								a++;	//je¿eli kolejne litery siê zgadzaj¹ to a++
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
			fsetpos(slownik, &pozycja);	//przywrócenie pozycji pliku przed sprawdzniem koñcówki ¿eby pobieraæ s³owo kolejne z kolei a nie to na którym skoñczyliœmy sprawdzanie koñcówki s³owa w tym przypadku
			a = 0;//wyzerowanie zmiennej warunkowej
		}
	}
}