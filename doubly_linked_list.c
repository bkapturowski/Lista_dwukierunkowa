
#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

struct doubly_linked_list_t* dll_create(){

    struct doubly_linked_list_t *dll = malloc(sizeof(struct doubly_linked_list_t));
    if(dll == NULL){
        return NULL;
    }

    dll->head = NULL;
    dll->tail = NULL;

    return dll;
}

int dll_push_back(struct doubly_linked_list_t* dll, int value){
    if(dll == NULL){
        return 1;
    }

    struct node_t *temp = malloc(sizeof(struct node_t));
    if(temp == NULL){
        return 2;
    }

    temp->data = value;
    temp->next = NULL;
    temp->prev = dll->tail;


    if(dll->tail != NULL){
        dll->tail->next = temp;
    }

    dll->tail = temp;


    if(dll->head == NULL){
        dll->head = temp;
    }

    return 0;
}
int dll_push_front(struct doubly_linked_list_t* dll, int value){
    if(dll == NULL){
        return 1;
    }

    struct node_t *temp = malloc(sizeof(struct node_t));
    if(temp == NULL){
        return 2;
    }

    temp->data = value;
    temp->prev = NULL;
    temp->next = dll->head;


    if(dll->tail == NULL){
        dll->tail = temp;
    }

    if(dll->head != NULL){
        dll->head->prev = temp;
    }

    dll->head = temp;


    return 0;
}
int dll_pop_front(struct doubly_linked_list_t* dll, int *err_code){
    if(dll == NULL){
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }

    if(dll->head == NULL){
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }

    struct node_t* temp = dll->head;
    int v = temp->data;

    dll->head = temp->next;

    if(dll->head != NULL){
        dll->head->prev = NULL;
    }
    if(dll->head == NULL){
        dll->tail = NULL;
    }

    free(temp);

    if(err_code != NULL){
        *err_code = 0;
    }

    return v;
}
int dll_pop_back(struct doubly_linked_list_t* dll, int *err_code){
    if(dll == NULL){
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }

    if(dll->tail == NULL){
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }

    struct node_t* temp = dll->tail;
    int v = temp->data;

    dll->tail = temp->prev;

    if(dll->tail != NULL){
        dll->tail->next = NULL;
    }
    else{
        dll->head = NULL;
    }

    free(temp);

    if(err_code != NULL){
        *err_code = 0;
    }

    return v;
}

int dll_back(const struct doubly_linked_list_t* dll, int *err_code){
    if(dll == NULL){
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }

    if(dll->tail == NULL){
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }

    struct node_t* temp = dll->tail;
    int v = temp->data;

    if(err_code != NULL){
        *err_code = 0;
    }

    return v;
}
int dll_front(const struct doubly_linked_list_t* dll, int *err_code){
    if(dll == NULL){
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }

    if(dll->head == NULL){
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }

    struct node_t* temp = dll->head;
    int v = temp->data;

    if(err_code != NULL){
        *err_code = 0;
    }

    return v;
}

struct node_t* dll_begin(struct doubly_linked_list_t* dll){
    if(dll == NULL){
        return NULL;
    }
    return dll->head;
}
struct node_t* dll_end(struct doubly_linked_list_t* dll){
    if(dll == NULL){
        return NULL;
    }
    return dll->tail;
}

int dll_size(const struct doubly_linked_list_t* dll){
    if(dll == NULL){
        return -1;
    }

    struct node_t* current = (dll)->head;
    struct node_t* next;

    int counter = 0;
    while (current != NULL) {
        next = current->next;
        counter++;
        current = next;
    }

    return counter;

}
int dll_is_empty(const struct doubly_linked_list_t* dll){
    if(dll == NULL){
        return -1;
    }

    if(dll->head != NULL){
        return 0;
    }

    return 1;
}

int dll_at(const struct doubly_linked_list_t* dll, unsigned int index, int *err_code){
    if(dll == NULL){
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }

    struct node_t* temp = dll->head;

    unsigned int i = 0;
    while (i<index) {
        i++;
        if (temp == NULL) {
            *err_code = 1;
            return 0;
        }
        temp = temp->next;
        if (temp == NULL) {
            if (err_code != NULL) {
                *err_code = 1;
            }
            return 0;
        }
    }

    if(err_code != NULL){
        *err_code = 0;
    }

    return temp->data;
}

int dll_insert(struct doubly_linked_list_t* dll, unsigned int index, int value){
    if(dll == NULL){
        return 1;
    }

    struct node_t *temp = malloc(sizeof(struct node_t));
    if(temp == NULL){
        return 2;
    }

    temp->data = value;

    if(dll_is_empty(dll)){
        dll->head = dll->tail = temp;
        temp->next = temp->prev = NULL;
        return 0;
    }
    if(index == 0){
        dll_push_front(dll,value);
        free(temp);
        return 0;
    }

    struct node_t *current = dll->head;
    unsigned int current_index = 0;

    while (current != NULL && current_index < index - 1)
    {
        current = current->next;
        current_index++;
    }

    // Sprawdzenie poprawności indeksu
    if (current == NULL)
    {
        free(temp);
        return 1;
    }

    // Dodanie nowego elementu na odpowiedniej pozycji
    temp->next = current->next;
    temp->prev = current;

    if (current->next != NULL)
        current->next->prev = temp;
    else
        dll->tail = temp;

    current->next = temp;

    return 0;
}
int dll_remove(struct doubly_linked_list_t* dll, unsigned int index, int *err_code){
    if(dll == NULL){
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }

    if(dll->head == NULL){
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }

    if(index == 0){
        int v = dll_pop_front(dll,0);
        if(err_code != NULL){
            *err_code = 0;
        }
        return v;
    }

    struct node_t *current = dll->head;
    unsigned int current_index = 0;

    while (current != NULL && current_index < index)
    {
        current = current->next;
        current_index++;
    }

    // Sprawdzenie poprawności indeksu
    if (current == NULL)
    {
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }

    // Usunięcie elementu z listy
    int removed_value = current->data;

    if (current->prev != NULL)
        current->prev->next = current->next;
    else
        dll->head = current->next;

    if (current->next != NULL)
        current->next->prev = current->prev;
    else
        dll->tail = current->prev;

    free(current);
    if(err_code != NULL)
        *err_code = 0;
    return removed_value;
}

void dll_clear(struct doubly_linked_list_t* dll){
    if (dll==NULL) {
        return;
    }
    struct node_t *ptr=(dll)->head;
    struct node_t *temp;
    while (ptr) {
        temp=ptr->next;
        free(ptr);
        ptr = temp;
    }
    dll->head = NULL;
    dll->tail = NULL;
}

void dll_display(const struct doubly_linked_list_t* dll){
    if (dll != NULL && dll->head != NULL) {
        struct node_t *temp = dll->head;
        while (temp != NULL){
            printf("%d ",temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}
void dll_display_reverse(const struct doubly_linked_list_t* dll){
    if (dll != NULL && dll->tail != NULL) {
        struct node_t *temp = dll->tail;
        while (temp != NULL){
            printf("%d ",temp->data);
            temp = temp->prev;
        }
        printf("\n");
    }
}