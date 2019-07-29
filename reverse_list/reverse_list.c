#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct ElementStructure{
    struct ElementStructure* next;
    int number;
} Element;

void create(Element** head, int number_of_elements){

    printf("Before malloc\n");

    Element* memory = (Element*)malloc(sizeof(Element));

    printf("After malloc\n");

    *head = memory;

    for(int elem = 0; elem != number_of_elements - 1; ++elem){
        memory[elem].next = memory + elem + 1;
        memory[elem].number = elem;

    }

    memory[number_of_elements - 1].next = NULL;
    memory[number_of_elements - 1].number = number_of_elements - 1;
}

void delete(Element* memory){
    free(memory);
}

void reverse(Element** head){

    // These are relative to the initial list orientation
    Element* previous = NULL;
    Element* current = *head;

    while(current->next != NULL){

        Element* temp_next = current->next;

        // Modigy linkage
        current->next = previous;

        // Update reversal state
        previous = current;
        current = temp_next;
    }

    // Linking the new head
    current->next = previous;

    *head = current;
}

void print(Element* head){

    Element* current = head;

    int elem = 0;
    while(current->next != NULL){
        printf("index %i adress %p number %i next %p\n", elem, current, current->number, current->next);

        elem++;
        current = current->next;
    }

    printf("index %i adress %p number %i next NULL\n", elem, current, current->number);
    printf("\n");
}

int main(){

    Element* linked_list;

    create(&linked_list, 5);
    print(linked_list);

    reverse(&linked_list);
    print(linked_list);

    reverse(&linked_list);
    print(linked_list);

    delete(linked_list);
}
