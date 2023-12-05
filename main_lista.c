
#include <stdio.h>
#include "doubly_linked_list.h"
#include <stdlib.h>

//Program pozwalający użytkownikowi na wykonywanie dowolnej operacji na liście dwukierunkowej z poziomu konsoli (menu tekstowe).
//W tym celu zaimplementowano listę wiązaną dwukierunkową, opartą o struktury oraz API

//Program, pozwala użytkownikowi na wykonywanie podstawowych operacji na liście dwukierunkowej.
//
//Na początek program alokuje pamięć na listę.
//
//Jeżeli nie uda się zaalokować żądanego obszaru pamięci program wyswietla komunikat Failed to allocate memory i zwraca kod błędu 8.
//W przypadku wprowadzenia przez użytkownika błędnych znaków program bezzwłocznie kończy działanie z kodem błędu 1 i komunikatem Incorrect input.
//Jeżeli udało się utworzyć listę, program pta użytkownika o wybór operacji:
//
//0 - Zakończenie działania programu.
//1 - Dodanie elementu na koniec listy.
//Program pobiera od użytkownika wartość, która ma zostać dodana do listy.
//2 - Usunięcie ostatniego elementu z listy.
//Program powinien wyświetlić wartość elementu.
//Jeżeli lista jest pusta to program powinien wyświetlić komunikat List is empty.
//3 - Dodanie elementu na początek listy.
//Program pobiera od użytkownika wartość, która ma zostać dodana do listy,
//4 - Usunięcie pierwszego elementu z listy.
//Program powinien wyświetlić wartość elementu.
//Jeżeli lista jest pusta program powinien wyświetlić komunikat List is empty.
//5 - Dodanie elementu do listy na pozycji podanej przez użytkownika.
//Program pobiera od użytkownika wartość do dodania a następnie indeks, pod który ma zostać dodany nowy element.
//W przypadku podania błędnych danych program powinien wyświetlić komunikat Index out of range i kontynuować działanie,
//6 - Usunięcie elementu spod indeksu podanego przez użytkownika z listy.
//Program powinien wyświetlić wartość elementu.
//Jeżeli lista jest pusta program powinien wyświetlić komunikat List is empty
//W przeciwnym przypadku program pobiera od użytkownika indeks elementu do usunięcia.
//W przypadku podania błędnych danych program powinien wyświetlić komunikat Index out of range i kontynuować działanie.
//7 - Wyświetlenie wartości ostatniego elementu listy.
//Jeżeli lista jest pusta program powinien wyświetlić komunikat List is empty.
//8 - Wyświetlenie wartości pierwszego elementu listy.
//Jeżeli lista jest pusta program powinien wyświetlić komunikat List is empty.
//9 - Sprawdzanie czy lista jest pusta. Program powinien wypisać:
//1 jeżeli lista jest pusta lub
//0 w przeciwnym przypadku.
//10 - Wyświetlenie liczby elementów znajdujących się w liście.
//11 - Usunięcie wszystkich elementów z listy.
//12 - Wyświetlenie wartości elementu spod indeksu indeksu index listy.
//Jeżeli lista jest pusta program powinien wyświetlić komunikat List is empty.
//W przeciwnym przypadku program pobiera od użytkownika indeks, spod którego ma zostać wyświetlona wartość.
//W przypadku podania błędnych danych program powinien wyświetlić komunikat Index out of range i kontynuować działanie.
//13 - Wyświetlenie wartości wszystkich elementów znajdujących się w liście.
//14 - Wyświetlenie od końca wartości wszystkich elementów znajdujących się w liście.
//W przypadku podania innej wartości program powinien wyswietla komunikat Incorrect input data i kontynuuje działanie.
int main()
{

    struct doubly_linked_list_t *dll = dll_create();
    if(dll == NULL){
        printf("Failed to allocate memory");
        return 8;
    }

    int index;
    int temp;
    int err_code;
    int option;
    int value;
    int count=0;
    while (1){
        printf("Co chcesz zrobic\n");
        if(scanf("%d", &option) != 1){
            printf("Incorrect input");
            dll_clear(dll);
            free(dll);

            return 1;
        }

        switch (option) {
            case 0:
                dll_clear(dll);
                free(dll);
                return 0;
            case 1:
                printf("Podaj liczbe:\n");
                if (scanf("%d", &value) != 1) {
                    printf("Incorrect input");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                if (dll_push_back(dll, value) == 2)
                {
                    printf("Failed to allocate memory");
                    dll_clear(dll);
                    free(dll);
                    return 8;
                }
                count += 1;
                break;
            case 2:
                temp = dll_pop_back(dll, &err_code);
                if (err_code == 1 || err_code == 2) {
                    printf("List is empty\n");
                }
                if (err_code == 0) {
                    printf("%d\n", temp);
                }
                count--;
                break;
            case 3:
                printf("Podaj liczbe:\n");
                if (scanf("%d", &value) != 1) {
                    printf("Incorrect input\n");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                if (dll_push_front(dll, value) == 2) {
                    printf("Failed to allocate memory\n");
                    dll_clear(dll);
                    free(dll);

                    return 8;
                }
                count += 1;
                break;
            case 4:
                temp = dll_pop_front(dll, &err_code);
                if (err_code == 1 || err_code == 2) {
                    printf("List is empty\n");
                }
                if (err_code == 0) {
                    printf("%d\n", temp);
                }
                count--;
                break;
            case 5:
                printf("Podaj liczbe\n");
                if (scanf("%d", &value) != 1) {
                    printf("Incorrect input\n");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                printf("Podaj indeks\n");
                if (scanf("%d", &index) != 1) {
                    printf("Incorrect input\n");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                temp = dll_insert(dll, index, value);
                if(temp == 1){
                    printf("Index out of range\n");
                }
                if (temp == 2) {
                    printf("Failed to allocate memory\n");
                    dll_clear(dll);
                    free(dll);
                    return 8;
                }
                count++;
                break;
            case 6:

                if (dll_is_empty(dll)) {
                    printf("List is empty\n");
                    break;
                }

                printf("Podaj indeks\n");
                if (scanf("%d", &index) != 1) {
                    printf("Incorrect input\n");
                    dll_clear(dll);
                    free(dll);

                    return 1;
                }

                temp = dll_remove(dll, index, &err_code);
                if (err_code == 1) {
                    printf("Index out of range\n");
                }
                if (err_code == 0) {
                    printf("%d\n", temp);
                }
                count--;
                break;
            case 7:
                temp = dll_back(dll, &err_code);
                if (err_code == 1) {
                    printf("List is empty\n");
                }
                if (err_code == 0) {
                    printf("%d\n", temp);
                }
                break;
            case 8:
                temp = dll_front(dll, &err_code);
                if (err_code == 1) {
                    printf("List is empty\n");
                }
                if (err_code == 0) {
                    printf("%d\n", temp);
                }
                break;
            case 9:
                if (dll_is_empty(dll)) {
                    printf("1\n");
                } else {
                    printf("0\n");
                }
                break;
            case 10:
                temp = dll_size(dll);
                printf("%d\n",temp);
                break;
            case 11:
                dll_clear(dll);
                break;
            case 12:
                if(dll_is_empty(dll)){
                    printf("List is empty\n");
                    break;
                }

                printf("Podaj indeks\n");
                if (scanf("%d", &index) != 1) {
                    printf("Incorrect input\n");
                    dll_clear(dll);
                    free(dll);

                    return 1;
                }

                temp = dll_at(dll,index,&err_code);
                if(err_code == 1){
                    printf("Index out of range\n");
                }
                if(err_code == 0){
                    printf("%d\n", temp);
                }
                break;
            case 13:
                if(!dll_is_empty(dll)){
                    dll_display(dll);
                }
                else{
                    printf("List is empty\n");
                }
                break;
            case 14:
                if(!dll_is_empty(dll)){
                    dll_display_reverse(dll);
                }
                else{
                    printf("List is empty\n");
                }
                break;
            default:
                printf("Incorrect input data\n");
                break;
        }
    }
}
