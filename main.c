/** @file */
/*
Projekt PK2 - Gra w statki
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "structs.h"

int main() {
	int m = 6;//ustalasz m i n (na razie tak, potem mo¿e bardziej interaktywnie)
	int n = 3;

	int M = m + 1;	//tutaj ¿eby sobie trochê u³atwiæ zrobi³em zmienne o 1 wiêksze od m i n ¿eby nie pisaæ za ka¿dym razem m+1, n+1
	int N = n + 1;

	FILE* slownik;
	if ((slownik = fopen("slownik.txt", "r")) == NULL) { //sprawdzamy czy istnieje plik slownik.txt
		printf("Nie moge otworzyc pliku!\n");
		exit(1);
	}

	char slowo[] = "";	//zmienne slowo i koniec do zapisywania tymczasowych slów z alfabetu
	char koniec[] = "";

	fpos_t pozycja = 0;	//zmienna do zapisanie pozycji pliku aby wróciæ do miejsca gdzie skoñczyliœmy (pobieranie kolejnego s³owa z kolejki)

	while (fscanf(slownik, "%s", slowo)) {	//pobieranie kolejnego s³owa z kolejki s³ownika
		printf("%s \n", slowo); //tymczasowe wyœwietlanie

		if (strlen(slowo) == m) {	//je¿eli s³owo mniejsze ni¿ m to nie bierzemy pod uwagê
			fgetpos(slownik, &pozycja);	//zapisywanie pozycji w której skoñczyliœmy, aby nie zaczynaæ poenieraæ s³ów z pocz¹tku s³ownika (np. skoñczyliœmy na arbuz wiêc zaczniemy na kolejnym a nie 5 s³ów dalej)
			rewind(slownik);	//powrót do pocz¹tku pliku aby móc porównaæ s³owo (jego koñcówkê) ze wszystkimi s³owami ze s³ownika
			int a = 0;	//zmienna warunkowa, która okreœla czy koñcówka s³owa wyst¹pi³a w s³owniku
			do {
				fscanf(slownik, "%s", koniec);	//pobranie kolejnej koñcówki do porównania ze s³owem
				if (feof(slownik) != 0) break;	//sprawdzenia czy nie wyst¹pi³ koniec pliku (czy sprawdziliœmy wszystkie koñcówki)
				for (int i = n; i < M; i++) {
					if (slowo[i] != koniec[i - n])break;	//sprawdzenie n ostatnicz liter s³owa w koñcówce (czyli czy powinniœmy wykluczyæ s³owo i go nie wypisaæ)
					a++;	//je¿eli kolejne litery siê zgadzaj¹ to a++
				}
				if (a == N)break;	//je¿eli koñcówka zgadza siê z koñcówk¹ s³owa to wykluczamy to s³owo i przerywamy pêtle while
			} while ((slowo[n] >= koniec[0]));	//je¿eli natrafimy na literê o wiêkszej wartoœci (ASCI) to nie ma sensu sprawdzaæ reszty np. pierwsza litera s³owa to a a wiêc bez sensu sprawdzaæ koñcówki zaczynaj¹ce siê od b w górê (plik posortowany alfabetycznie)
			if (a != N) {	//tutaj warunek jeœli nie znaleziono warunku wykluczaj¹cego s³owa ¿eby go wypisaæ jako rozwi¹zanie
				printf("Siema");	//tymczasowe
				//je¿eli nie znalaz³ s³owa od przodu to powinnien szukaæ tego od ty³u(jeszcze nie napisane)
			}
			fsetpos(slownik, &pozycja);	//przywrócenie pozycji pliku przed sprawdzniem koñcówki ¿eby pobieraæ s³owo kolejne z kolei a nie to na którym skoñczyliœmy sprawdzanie koñcówki s³owa w tym przypadku
			a = 0;	//wyzerowanie zmiennej warunkowej
		}
	}

	//printf("%s \n", koniec);

	//free(koniec);
	free(slowo);

	/*char* tabS = malloc(sizeof(char));
	char slowo[] = { "bakata" };
	tabS = slowo;
	printf("%s", tabS);*/

	fclose(slownik);

	return 0;
}