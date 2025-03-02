#include <stdio.h>
#include <stdlib.h>

typedef struct Nodes{

    int integer;
    struct Nodes *next; 
}Node;

Node *create_node(int integer){

    Node *new_node = (Node *) malloc(sizeof(Node));

    if(new_node == NULL){
        perror("Error while dinamically allocate memory.\n");
        exit(EXIT_FAILURE);
    }

    new_node->integer = integer;
    new_node->next = NULL;

    return new_node;
}

void add_node(Node **head, int integer){

    Node *new_node = create_node(integer);
    new_node->next = *head;
    *head = new_node;
}

void free_list(Node *head){

    Node *aux;
    while(head){
        aux = head;
        head = head->next;
        free(aux);
    }
}


int main(int argc, char **argv){

    if(argc !=3 ){
        perror("Not enough arguments.\n");
        exit(-1);
    }

    FILE *input_file = fopen(argv[1], "rb");

    if(input_file == NULL){
        perror("Error while opening file.\n");
        exit(-1);
    }

    int maximum = 0;
    int minimum = 99999999;
    long long total = 0;
    int count = 0;
    int one_byte_count = 0;
    int two_byte_count = 0;
    int four_byte_count = 0;
    Node *head = NULL;

    while(1){
        unsigned char sof;
        if(fread(&sof, 1, 1, input_file) != 1){
            break;
        }
        
        unsigned char length;
        
        fread(&length, 1, 1, input_file);
        
        int integer = 0;

        switch(length){
            case 0x01: {
                one_byte_count++;
                fread(&integer, 1,1, input_file);
            }
            case 0x02:{
                two_byte_count++;
                fread(&integer, 2, 1, input_file);
            }
            case 0x04:{
                four_byte_count++;
                fread(&integer, 4, 1, input_file);
            }
        }
        total+=integer;
        count++;
        if(integer > maximum) maximum = integer;
        if(integer < minimum) minimum = integer;    
    }

    fclose(input_file);

    FILE *output_file = fopen(argv[2], "w");

    if(output_file == NULL){
        perror("Error while opening file.\n");
        exit(-1);
    }

    fprintf(output_file, "Maximum integer: %d\n", maximum);
    fprintf(output_file, "MInimum integer: %d\n", minimum);
    fprintf(output_file, "%.2f\n", (double) total/count);
    fprintf(output_file, "No 1 byte: %d\n", one_byte_count);
    fprintf(output_file, "No 2 byte: %d\n", two_byte_count);
    fprintf(output_file, "No 4 byte: %d\n", four_byte_count);

    fclose(output_file);

    free_list(head);
    return 0;

}