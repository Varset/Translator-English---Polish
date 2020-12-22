/*
 Celem programu jest stworzenie słownika polsko-angielskiego i angielsko-polskiego.
Na początku działania programu wybierany jest język podstawowy; w trakcie działania powinna istnieć możliwość jego zmiany.
Użytkownik podaje słowo w języku podstawowym a program wyszukuje jego tłumaczenie, przy czym wyszukiwanie powinno działać
również dla początkowego fragmentu wyrazu, np.: wpisanie słowa kot powinno zaowocować znalezieniem tłumaczeń cat (kot) oraz kitty (kotek).
Zbiór dostępnych słów przechowywany jest w pliku. Program powinien umożliwiać dodawanie, edycję oraz usuwanie wyrazów zawartych w słowniku.
Każde słowo ma tylko jedno tłumaczenie, słowa nie mogą się powtarzać w żadnym języku.
Do realizacji należy wykorzystać dwie listy powiązane ze sobą. Listy powinny przechowywać słowa w porządku alfabetycznym.
Przykładowa struktura może wyglądać następująco:
struct lista
{
  char *slowo;
  struct lista *nast.;
  struct lista *tłumaczenie;
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DMAX 30
#define DMAXSL 100

typedef struct
{
    char pl[DMAX];
    char ang[DMAX];
    int index; // Jesli index == 0 , to mamy wolne miejsce
}Slowo;

typedef struct
{
    Slowo slowo[DMAXSL];
}Slownik;


/*
1) Wstaw nowe słowo;
2) Ogólny widok słownika;
3) Usuń słowo;
4) Wyszukaj słowo w języku angielskim i przetłumacz je na polski;
5) Importuj słowa;
6) Eksportuj słowa;
7) Wyjście;
*/
int main()
{
    Slownik slownik;
    Slownik coppySlownik;
    int opcja;
    int wroc=0;
    char null[1];
    int i, k;
    int LicznikPustychSlotow;
    int pozycja;
    int operacjaUsuwania;
    int opcjaSzukania;
    int usunacIndex;
    int szukanieIndex;
    char slowo[DMAX];
    char usunacPl[DMAX];
    char usunacAng[DMAX];
    char impNazwaPliku[DMAX];
    char expNazwaPliku[DMAX];

    FILE *input;
    FILE *output;

    null[0]='\0';
    null[1]='\0';

    for (i=0; i<DMAXSL; i++)
    {
        slownik.slowo[i].index=DMAXSL+1;
        strcpy(slownik.slowo[i].pl, null);
        strcpy(slownik.slowo[i].ang, null);
    }

    printf("POLSKO-ANGIELSKI TLUMACZ");

    do
    {
        printf("\n\n\n\n___________________________________________________________________________________________\n");
        printf("1) Wstaw nowe slowo\n");
        printf("2) Ogolny widok slownika\n");
        printf("3) Usun slowo\n");
        printf("4) Wyszukaj slowo w jezyku angielskim i przetlymacz go na polski\n");
        printf("5) Importuj slowa\n");
        printf("6) Eksportuj slowa\n");
        printf("7) Wyjscie\n");
        printf("Opcja: ");
        scanf("%d", &opcja);
        printf("\n\n");

        switch (opcja)
        {
        case 1:
        {
            printf("Ta opcja umozliwia wstawienie nowego slowa\n");
            printf("Prosze wstawic zadane dane.\n");
            printf("___________________________________________________________________________________________\n");
            LicznikPustychSlotow=100;
            //Operacji
            for (i=0; i<DMAXSL; i++)
            {
                if (slownik.slowo[i].index != (DMAXSL+1))
                {
                    LicznikPustychSlotow--;
                }
            }
            if (LicznikPustychSlotow!=0)
            {
                pozycja = DMAXSL - LicznikPustychSlotow;
                printf("Masz %d pustych slotow. Planujesz wstawic slowo do pozycji %d.\n", LicznikPustychSlotow, pozycja);
                printf("Wpisz slowo w angielksim: ");
                scanf("%s", slownik.slowo[pozycja].ang);
                printf("Wpisz slowo w polskim: ");
                scanf("%s", slownik.slowo[pozycja].pl);
                slownik.slowo[pozycja].index=pozycja;
            } else
            {
                printf("Nie masz wolnego miejsca. Mozesz podac nowe slowo, ale ostatnie zostanie zamienione.\n");
                printf("Wpisz slowo w angielksim: ");
                scanf("%s", slownik.slowo[DMAXSL-1].ang);
                printf("Wpisz slowo w polskim: ");
                scanf("%s", slownik.slowo[DMAXSL-1].pl);
                slownik.slowo[DMAXSL-1].index=DMAXSL-1;
            }
            printf("___________________________________________________________________________________________\n");
            printf("Jesli chesz wrocic do glownej strony, prosze wpisac 0.\n");
            printf("Jesli chesz wyjsc, wprowadz inna dowolna liczbe.\n");
            printf("Wybor: ");
            scanf("%d", &wroc);
            break;
        }

        case 2:
            {
                printf("Ta opcja pozwala cie obejrzec wszystkie slowy w slowniku.\n");
                printf("___________________________________________________________________________________________\n");
                //Operacji
                for (i=0; i<DMAXSL; i++)
                {
                    if (slownik.slowo[i].index!=(DMAXSL+1))
                    {
                        printf("Index: %d\n", slownik.slowo[i].index);
                        printf("Slowo w angielskim: %s\n", slownik.slowo[i].ang);
                        printf("Slowo w polskim: %s\n", slownik.slowo[i].pl);
                        printf("___________________________________________________________________________________________\n");
                    }
                }
                printf("Jesli chesz wrocic do glownej strony, prosze wpisac 0.\n");
                printf("Jesli chesz wyjsc, wprowadz inna dowolna liczbe.\n");
                printf("Wybor: ");
                scanf("%d", &wroc);
                break;
            }

        case 3:
            {
                printf("Ta opcja pozwoli cie usunac slowo.\n");
                printf("Prosze podac potrzebne dane.\n");
                printf("___________________________________________________________________________________________\n");
                //Operacja
                printf("Mozesz usunac slowo uzywajac jego index, lub uzywajac slowo w angielskim albo w polskim.\n");
                printf("Prosze wybrac jak planujesz usunac slowo.\n");
                printf("1) Usunac slowo uzywajac index.\n");
                printf("2) Usunac, uzywajac slowo w polskim.\n");
                printf("3) Usunac, uzywajac slowo w angielskim.\n");
                printf("Operacja: ");
                scanf("%d", &operacjaUsuwania);
                if(operacjaUsuwania==1)
                {
                    //Usunac slowo uzywajac jego index
                    printf("Wpisz index slowa: ");
                    scanf("%d", &usunacIndex);
                    for(i=0; i<DMAXSL; i++)
                    {
                        if(usunacIndex==slownik.slowo[i].index)
                        {
                            slownik.slowo[i].index=DMAXSL+1;
                            strcpy(slownik.slowo[i].ang, null);
                            strcpy(slownik.slowo[i].pl, null);
                        }
                    }
                }
                else if (operacjaUsuwania==2)
                {
                    //Usunac, uzywajac slowo w polskim
                    printf("Wpisz slowo w Polskim");
                    scanf("%s", usunacPl);
                    for (i=0; i<DMAXSL; i++)
                    {
                        if (strcmp(usunacPl, slownik.slowo[i].pl)==0)
                        {
                            slownik.slowo[i].index=DMAXSL+1;
                            strcpy(slownik.slowo[i].pl, null);
                            strcpy(slownik.slowo[i].ang, null);
                        }
                    }
                }
                else if(operacjaUsuwania==3)
                {
                    //Usunac, uzywajac slowo w angielskim
                    printf("Wpisz slowo w Angielskim");
                    scanf("%s", usunacAng);
                    for(i=0; i<DMAXSL; i++)
                    {
                        if (strcmp(usunacAng, slownik.slowo[i].ang)==0)
                        {
                            slownik.slowo[i].index=DMAXSL+1;
                            strcpy(slownik.slowo[i].pl, null);
                            strcpy(slownik.slowo[i].ang, null);
                        }
                    }
                }
                for(i=0; i<DMAXSL;i++)
                {
                    coppySlownik.slowo[i].index=DMAXSL+1;
                    strcpy(coppySlownik.slowo[i].ang, null);
                    strcpy(coppySlownik.slowo[i].pl, null);
                }
                // TERAZ MUSZE ZMIENIC LISTE
                k=0;
                for(i=0; i<DMAXSL; i++)
                {
                    if(slownik.slowo[i].index!=DMAXSL+1)
                    {
                        coppySlownik.slowo[i].index=k;
                        strcpy(coppySlownik.slowo[i].ang, slownik.slowo[i].ang);
                        strcpy(coppySlownik.slowo[i].pl, slownik.slowo[i].pl);
                        slownik.slowo[i].index=DMAXSL+1;
                        strcpy(slownik.slowo[i].ang, null);
                        strcpy(slownik.slowo[i].pl, null);
                        k++;
                    }
                }
                for (i=0; i<DMAXSL; i++)
                {
                    slownik.slowo[i].index=coppySlownik.slowo[i].index;
                    strcpy(slownik.slowo[i].ang, coppySlownik.slowo[i].ang);
                    strcpy(slownik.slowo[i].pl, coppySlownik.slowo[i].pl);
                }
                printf("___________________________________________________________________________________________\n");
                printf("Jesli chesz wrocic do glownej strony, prosze wpisac 0.\n");
                printf("Jesli chesz wyjsc, wprowadz inna dowolna liczbe.\n");
                printf("Wybor: ");
                scanf("%d", &wroc);
                break;
            }
        case 4:
            {
                printf("Ta opcja pozwala cie szukac slowo w slowniku.\n");
                printf("Mozesz wpisac polski slowo, i jak wynik zobaczysz tlumaczenie.\n");
                printf("Mozesz wpisac angielskie slowo, i jak wynik zobaczysz tlumaczenie.\n");
                printf("Mozesz tez szukac slow uzywajac je index.\n");
                printf("1) Wpisac Angielski slowo i przetlumaczyc go.\n");
                printf("2) Wpisac Polskie slowo o przetlumaczyc go.\n");
                printf("3) Wpisac index i zobaczyc Polskie i Angielskie slowo");
                printf("Opcja: ");
                scanf("%d", &opcjaSzukania);
                if (opcjaSzukania==1)
                {
                    // Szukac angielskiego slowa i tlumaczyc go
                    printf("Wpisz slowo w angielskim: ");
                    scanf("%s", slowo);
                    printf("WYNIK: \n");
                    for (i=0; i<DMAXSL; i++)
                    {
                        if (strcmp(slowo, slownik.slowo[i].ang)==0)
                        {
                            printf("Index: %d\n", slownik.slowo[i].index);
                            printf("Slowo w Angielskim: %s\n", slownik.slowo[i].ang);
                            printf("Slowo w Polskim: %s\n", slownik.slowo[i].pl);
                        }
                    }
                    printf("Jesli wynik jest pusty, to znaczy ze nie moze przetlumaczyc podanego slowa.\n");
                    printf("Prosze, poczekaj na aktualizacje.\n");
                }
                else if(opcjaSzukania==2)
                {
                    printf("Wpisz slowo w polskim: ");
                    scanf("%s", slowo);
                    printf("WYNIK: \n");
                    for (i=0; i<DMAXSL; i++)
                    {
                        if (strcmp(slowo, slownik.slowo[i].pl)==0)
                        {
                            printf("Index: %d\n", slownik.slowo[i].index);
                            printf("Slowo w Angielskim: %s\n", slownik.slowo[i].ang);
                            printf("Slowo w Polskim: %s\n", slownik.slowo[i].pl);
                        }
                    }
                    printf("Jesli wynik jest pusty, to znaczy ze nie moze przetlumaczyc podanego slowa.\n");
                    printf("Prosze, poczekaj na aktualizacje.\n");
                }
                else if(opcjaSzukania==3)
                {
                    //SZUKANIE ZA POMOCA INDEKSU
                    printf("Wpisz index: ");
                    scanf("%d", &szukanieIndex);
                    printf("WYNIK: \n");
                    printf("Index: %d\n", slownik.slowo[szukanieIndex].index);
                    printf("Slowo w Angielskim: %s\n", slownik.slowo[szukanieIndex].ang);
                    printf("Slowo w Polskim: %s\n", slownik.slowo[szukanieIndex].pl);
                }
                printf("___________________________________________________________________________________________\n");
                //OPERACJI
                printf("___________________________________________________________________________________________\n");
                printf("Jesli chesz wrocic do glownej strony, prosze wpisac 0.\n");
                printf("Jesli chesz wyjsc, wprowadz inna dowolna liczbe.\n");
                printf("Wybor: ");
                scanf("%d", &wroc);
                break;
            }
        case 5:
            {
                printf("Ta opcja pozwoli cie importowanie danych.\n");
                printf("___________________________________________________________________________________________\n");
                //OPERACJI
                printf("Wpisz nazwe pliku: ");
                scanf("%s", impNazwaPliku);
                input=fopen(impNazwaPliku, "r");
                for (i=0; i<DMAXSL; i++)
                {
                    fscanf(input, "Index: %d) %s - %s\n", &slownik.slowo[i].index, slownik.slowo[i].ang, slownik.slowo[i].pl);
                }
                fclose(input);
                printf("___________________________________________________________________________________________\n");
                printf("Jesli chesz wrocic do glownej strony, prosze wpisac 0.\n");
                printf("Jesli chesz wyjsc, wprowadz inna dowolna liczbe.\n");
                printf("Wybor: ");
                scanf("%d", &wroc);
                break;
            }
        case 6:
            {
                printf("Ta opcja pozwoli cie exportowanie danych.\n");
                printf("___________________________________________________________________________________________\n");
                //OPERACJI
                printf("Gdzie chcesz zapisac dane?\n");
                printf("Prosze podac nazwe pliku txt. Prosze napisac w taki sposob (name.txt).\n");
                printf("Plik: ");
                scanf("%s", expNazwaPliku);
                output=fopen(expNazwaPliku, "w");
                if (output)
                {
                    for (i=0; i<DMAXSL; i++)
                    {
                        fprintf(output, "Index: %d) %s - %s\n", slownik.slowo[i].index, slownik.slowo[i].ang, slownik.slowo[i].pl);
                    }
                }
                fclose(output);
                printf("___________________________________________________________________________________________\n");
                printf("Jesli chesz wrocic do glownej strony, prosze wpisac 0.\n");
                printf("Jesli chesz wyjsc, wprowadz inna dowolna liczbe.\n");
                printf("Wybor: ");
                scanf("%d", &wroc);
                break;
            }
        default:
            wroc=1;
            break;
        }
    }while (wroc==0);
    printf("\n___________________________________________________________________________________________\n");
    printf("Do widzenia!\n");
    return 0;
}

