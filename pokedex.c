// Assignment 2 19T1 COMP1511: Pokedex
// pokedex.c
//
// This program was written by YOUR-NAME-HERE (z5238561)
// on 25-Apr-2019
//
// Version 1.0.0: Assignment released.
// Version 1.0.1: Minor clarifications about `struct pokenode`.
// Version 1.1.0: Moved destroy_pokedex function to correct location.
// Version 1.1.1: Renamed "pokemon_id" to "id" in change_current_pokemon.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pokedex.h"
#include <ctype.h>

// Add your own #defines here.


// Note you are not permitted to use arrays in struct pokedex,
// you must use a linked list.
//
// You are also not permitted to use arrays in any of the functions
// below.
//
// The only exception is that char arrays are permitted for
// search_pokemon and functions it may call, as well as the string
// returned by pokemon_name (from pokemon.h).
//
// You will need to add fields to struct pokedex.
// You may change or delete the head field.

struct pokedex {
    struct pokenode *head;
    struct pokenode *currnode;
};

//////////////////////my function signatures (declarations)://///////////////
struct pokenode *createpokenode(Pokemon pokemon);                          //
void insertnode(Pokedex pokedex,struct pokenode *poke);                    //
void print(struct pokenode *currnode);                                     //
void insert_copied_node(Pokedex pokedex_new ,struct pokenode *old_node);   //
void insert_found_nodes(Pokedex pokedex_new ,struct pokenode *old_node);   //
static char *turn_to_lower(char *input);                                   //
static int compare_text(char *input, char *dex_name);                      //
/////////////////////////////////////////////////////////////////////////////

// You don't have to use the provided struct pokenode, you are free to
// make your own struct instead.
// If you use the provided struct pokenode, you will need to add fields
// to it to store other information.

struct pokenode {
    struct pokenode *next;
    struct pokenode *prev;    //pointer to the previous element in the list.
    struct pokenode *evolve;  //pointer to the node the pokemon evolves to.
    int found;                //Default set to 0. 1 if pokemon is found.
    Pokemon         pokemon;
};

// Add any other structs you define here.


// Add prototypes for any extra functions you create here.


// You need to implement the following 20 functions.
// In other words, replace the lines calling fprintf & exit with your code.
// You can find descriptions of what each function should do in pokedex.h


Pokedex new_pokedex(void) {
    Pokedex new_pokedex = malloc(sizeof (struct pokedex));
    assert(new_pokedex != NULL);
    // add your own code here
    new_pokedex->head = NULL;
    new_pokedex->currnode = NULL;
    return new_pokedex;
}


////////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                          //
////////////////////////////////////////////////////////////////////////

//question 1:
void add_pokemon(Pokedex pokedex, Pokemon pokemon) {
    //creating the new pokemon.
    struct pokenode *poke = createpokenode(pokemon);    
    //inserting the newly created node into the pokedex.
    insertnode(pokedex, poke);
}

//question 2:
void detail_pokemon(Pokedex pokedex) {
    //if the pokedex is empty return nothing.
    if (pokedex->head == NULL) {
        return;
    } else {
        print(pokedex->currnode);  //print function prints the details of 
    }                              //currently selected pokenode.
}

//question 3:
Pokemon get_current_pokemon(Pokedex pokedex) {
    //i there are no pokemons.....EXIT....
    if (pokedex->currnode == NULL) {
        fprintf(stderr, "Exiting because there are no pokemons in pokedex.c\n");
        exit(1);
    } else {
        return pokedex->currnode->pokemon;  
    }
}

//question 4:
void find_current_pokemon(Pokedex pokedex) {
    if (pokedex->currnode == NULL) {
        return;
    } else {
        pokedex->currnode->found = 1; //if list is not empty set the current 
    }                                 //pokemon to be found.
}

//question 5:
void print_pokemon(Pokedex pokedex) {
    //Creating a temporary pointer to point to the head of the pokedex.
    struct pokenode *temp = pokedex->head;
    while (temp != NULL) {
        //CASE 1: the printed node is the one currently selected.
        if (temp == pokedex->currnode) {
            printf("-->");
            printf(" #%03d: ", pokemon_id(temp->pokemon));    
            char *name = pokemon_name(temp->pokemon);
            //If the pokemon is not found print *'s.
            if (temp->found == 0) {            
                int loop = 0; 
                while (name[loop] != '\0') {
                    printf("*");
                    loop++;
                }
                printf("\n");
            } else {               
                printf("%s\n", name);  //if found then just print the name.
            }
        } else { //CASE 2: the node is NOT the currently selected one.
            printf("    ");
            printf("#%03d: ", pokemon_id(temp->pokemon));    
            char *name = pokemon_name(temp->pokemon);
            if (temp->found == 0) {            
                int loop = 0; 
                while(name[loop] != '\0') {
                    printf("*");
                    loop++;
                }
                printf("\n");
            } else {
                printf("%s\n", name);
            }
        }
        temp = temp->next;    
    }
}

////////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                          //
////////////////////////////////////////////////////////////////////////

//question 1:
void next_pokemon(Pokedex pokedex) {
    if (pokedex->head == NULL) {
        return;               //if the list is empty, do nothing.
    } else {
        struct pokenode *temp = pokedex->currnode;
        if (temp->next == NULL) { // if there is only one element in the list,
            return;               // do nothing.
        } else {  //else move the currnode to the next node.
            pokedex->currnode = temp->next; 
        }
    }
}

//question 2:
void prev_pokemon(Pokedex pokedex) {
    if (pokedex->head == NULL) {         
        return;               //if the list is empty, do nothing.
    } else {
        struct pokenode *temp = pokedex->currnode;
        if (temp->prev == NULL){  // if there is only one element in the list,
            return;               // do nothing.
        } else {   //else move the currnode to the next node.
            pokedex->currnode = temp->prev;
        }
    }
}

//question 3:
void change_current_pokemon(Pokedex pokedex, int id) {
    //Creating a temporary pointer to point to the head of the pokedex.
    struct pokenode *temp = pokedex->head;
    //stop_loop will stop the loop if the id is matched!!!
    int stop_loop = 0;
    while (temp != NULL && stop_loop == 0) {
        if (pokemon_id(temp->pokemon) == id) {
            pokedex->currnode = temp; //set currnode to be temp
            stop_loop = 1;  //stop the loop when the match is found.
        }
        temp = temp->next;
    }
}

//question 4:
void remove_pokemon(Pokedex pokedex) {
    if (pokedex->head != NULL){
        //Creating a temporary pointer to point to the head of the pokedex.
        struct pokenode *temp = pokedex->currnode;
        if (temp->prev == NULL && temp->next == NULL) {
            //removing the only node in the list.
            pokedex->head = NULL;
        } else if (temp->prev == NULL && temp->next != NULL) {  
            //removing the first node in the list.
            temp->next->prev = temp->prev;
            pokedex->head = temp->next;
            //setting the next node as the current node.
            pokedex->currnode = temp->next;
        } else if (temp->next == NULL && temp->prev != NULL) {
            //removing the last node in the list.
            temp->prev->next = temp->next;
            //setting the previous node as the current node.
            pokedex->currnode = temp->prev;
        } else if (temp->next != NULL && temp->prev != NULL) {
            //removing node in the middle of the list.
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            //setting the next node as the current node.
            pokedex->currnode = temp->next;
        }
        destroy_pokemon(temp->pokemon);
        free(temp);    
    }
}

//question 5:           
void destroy_pokedex(Pokedex pokedex) {
    //if the list is not empty.....
    if (pokedex->head != NULL) {
        //pointer destroy is the node being destroyed.
        struct pokenode *destroy = pokedex->head;
        //temp will save the nexte node of the node being destroyed.
        struct pokenode *temp = NULL;
        while (destroy != NULL) {
            temp = destroy->next; //store the next node.
            destroy_pokemon(destroy->pokemon); //destroy the current node.
            free(destroy); //free the current node
            destroy = temp; //now the next node is the next to be destroyed.
        }
    }
    free(pokedex);
}

////////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                          //
////////////////////////////////////////////////////////////////////////

//question 1:
void go_exploring(Pokedex pokedex, int seed, int factor, int how_many) {
    //First check if there is any id within the given factor range.
    struct pokenode *check_factor = pokedex->head;
    int id_in_range = 0;  //if the id is in the given range this will be 1.  
    while (check_factor != NULL) {
        //get the id of the current pokemon
        int pok_id = pokemon_id(check_factor->pokemon);
        if (pok_id < factor && pok_id >= 0) {
            id_in_range = 1;
        }
        check_factor = check_factor->next;
    }
    if (id_in_range == 0) {
        fprintf(stderr, "exiting because there are no pokemon _ids within the factor range!!\n");
        exit(1); 
    }
    
    //Now make a random node set to found.
    srand(seed);
    int loop = 0;
    while(loop < how_many){
        struct pokenode *temp = pokedex->head;
        int discover_id = rand() % factor;
        while (temp != NULL){
            if (pokemon_id(temp->pokemon) == discover_id) {
                temp->found = 1;
                loop++;
            }
            temp = temp->next;
        }        
    }
}

//question 2:
int count_found_pokemon(Pokedex pokedex) {
    //Creating a temporary pointer to point to the head of the pokedex.
    struct pokenode *temp = pokedex->head;
    //found counter will count the total number of pokemons that are found.
    int found_counter = 0;
    while (temp != NULL) {
        if(temp->found == 1){
            found_counter++;
        }
        temp = temp->next;
    }
    return found_counter;
}

//question 3:
int count_total_pokemon(Pokedex pokedex) {
    //Creating a temporary pointer to point to the head of the pokedex.
    struct pokenode *temp = pokedex->head;
    //total_counter will count the total number of pokemons.
    int total_counter = 0;
    while (temp != NULL) {
        total_counter++;
        temp = temp->next;
    }
    return total_counter;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

//question 1:
void add_pokemon_evolution(Pokedex pokedex, int from_id, int to_id) {
    //First find the node with the id equal to from_id.
    int stop1 = 0;
    struct pokenode *temp1 = pokedex->head;
    while (temp1 != NULL && stop1 == 0) {
        if (pokemon_id(temp1->pokemon) == from_id) {
            stop1 = 1;
        } else {
            temp1 = temp1->next;
        }
    }
    //if no node with the given id exists....Exit.
    if (stop1 == 0) {
        fprintf(stderr, "no pokemon with from_id = %d in your pokedex.\n" , from_id);
        exit(1);
    }
    
    //Now find the node with the id equal to to_id.
    int stop2 = 0;
    struct pokenode *temp2 = pokedex->head;
    while (temp2 != NULL && stop2 == 0) {
        if (pokemon_id(temp2->pokemon) == to_id) {
            stop2 = 1;
        } else {
            temp2 = temp2->next;
        }     
    }
    //if no node with the given id exists....Exit.
    if (stop2 == 0){
        fprintf(stderr, "no pokemon with to_id = %d found in your pokedex.\n" , to_id);
        exit(1);
    }
    
    //set the first nodes evolve to point to the second node.
    temp1->evolve = temp2;
}

//question 2:
void show_evolutions(Pokedex pokedex) {
    //Creating a temporary pointer to point to the current node of the pokedex.
    struct pokenode *temp = pokedex->currnode;
    while (temp != NULL) {
        if (temp->found == 0) {        //print details if not found.
            printf("#%03d ???? [????]", pokemon_id(temp->pokemon));
        } else {                       //print details if found.
            printf("#%03d ", pokemon_id(temp->pokemon));
            printf("%s ", pokemon_name(temp->pokemon));                         
            printf("[");
            printf("%s", pokemon_type_to_string( pokemon_first_type(temp->pokemon)));
            if (pokemon_second_type(temp->pokemon) != NONE_TYPE) {
                printf(", %s", pokemon_type_to_string(pokemon_second_type(temp->pokemon)));
            }
            printf("]");
        }
        //if there is one more evolution print the arrow
        if (temp->evolve != NULL) {
            printf(" --> ");
        } else {    //if not print the new line.
            printf("\n");
        }
        temp = temp->evolve;
    }    
}

//question 3:

int get_next_evolution(Pokedex pokedex) {
    //Creating a temporary pointer to point to the current node of the pokedex.
    struct pokenode *temp = pokedex->currnode;
    int poke_ID; //stores the evolution.
    if(temp->evolve == NULL){
        poke_ID = DOES_NOT_EVOLVE;
    } else {
        temp = temp->evolve;    
        poke_ID = pokemon_id(temp->pokemon);  
    }
    return poke_ID;
}

////////////////////////////////////////////////////////////////////////        
//                         Stage 5 Functions                          //
////////////////////////////////////////////////////////////////////////

//question 1:
Pokedex get_pokemon_of_type(Pokedex pokedex, pokemon_type type) {

    //Making a new struct pokedex to copy specific nodes from pokedex struct.
    Pokedex specific_copy = new_pokedex();                                       
    //creating a temporary pointer that will loop through pokedex  
    struct pokenode *temp = pokedex->head;                                       
    while (temp != NULL) {
        //First check if the pokemon is found.
        if (temp->found == 1) {
            //now check if the pokemon is of the type that we want.
            if (pokemon_first_type(temp->pokemon) == type || 
                pokemon_second_type(temp->pokemon) == type) {
                //insert the pokemon into the new pokedex ~ specific_copy
                insert_copied_node(specific_copy, temp);                        
            }
        }
        temp = temp->next;
    }
    
    return specific_copy;                                                       
   
}

//question 2:
Pokedex get_found_pokemon(Pokedex pokedex) {
    //Making a new struct pokedex to copy found nodes from pokedex struct.
    Pokedex found_copy = new_pokedex();
    //Creating a temporary pointer to point to the head of the pokedex.
    struct pokenode *temp = pokedex->head;
    while (temp != NULL) {
        //Check if the pokemon is found.
        if (temp->found == 1) {
            //insert the pokemon into the new pokedex ~ found_copy
            insert_found_nodes(found_copy, temp);
        }
        temp = temp->next;
    }
    return found_copy;
}

//question 3:
Pokedex search_pokemon(Pokedex pokedex, char *text) {
    //Making a new struct pokedex to copy found nodes from pokedex struct.
    Pokedex search_copy = new_pokedex();
    //Creating a temporary pointer to point to the head of the pokedex.
    struct pokenode *temp = pokedex->head;
    while (temp != NULL) {
        //First check if the pokemon is found.
        if (temp->found == 1) {
            //get the name of the pokemon in the old pokedex.
            char *pokem_name = pokemon_name(temp->pokemon);
            //match will be what the compare_text function returns. 
            int match = compare_text(text, pokem_name);
            if (match == 1) {   
                //if the recived text is a substring then insert the node.
                insert_copied_node(search_copy, temp);
            }
        }
        temp = temp->next;   
    }
    return search_copy;

}

////////////////////////////////////////////////////////////////////////       
//                         My own functions!!!                        // 
////////////////////////////////////////////////////////////////////////

//the create pokenode function as follows creates a new pokenode in the malloced
//space and points it to null!!!!
struct pokenode *createpokenode(Pokemon pokemon) {
    //Lets malloc some memory so we can store pokenode in memory.
    struct pokenode *poke= malloc(sizeof(struct pokenode));
    poke->next = NULL;
    poke->prev = NULL;
    poke->evolve = NULL;
    poke->pokemon = pokemon;
    //all pokemons are default set to be not found.
    poke->found = 0;
    return poke;
}


//the insertnode function inserts the pokenode to the last position of the 
//linked list!! Stage 1:
void insertnode(Pokedex pokedex, struct pokenode *poke) {
    //if the pokedex is empty simply insert the node.
    if (pokedex->head == NULL) {
        pokedex->head = poke;
        pokedex->currnode = poke;
    } else {                   //otherwise insert to the end of the list.
        struct pokenode *temp; 
        temp = pokedex->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = poke; 
        poke->prev = temp;
    }
}



//this it the print function that prints all the details of the currently 
//selected pokemon by calling functions from pokemon.c !!!
void print(struct pokenode *currnode) {
    //if the pokemon is not found hide all the details and print.
    if (currnode->found == 0) {
        char *name = pokemon_name(currnode->pokemon);
        printf("Id: %03d\n", pokemon_id(currnode->pokemon));
        printf("Name: ");
        int loop = 0; 
        //following loop prints stars equal to the number of letters in the name
        while(name[loop] != '\0') {
            printf("*");
            loop++;
        }
        printf("\n");
        printf("Height: --\n");
        printf("Weight: --\n");
        printf("Type: -- \n");
    } else {            //if the pokemon is found then print all details.
        printf("Id: %03d\n", pokemon_id(currnode->pokemon));
        printf("Name: %s\n", pokemon_name(currnode->pokemon));
        printf("Height: %0.1lfm\n", pokemon_height(currnode->pokemon));
        printf("Weight: %0.1lfkg\n", pokemon_weight(currnode->pokemon));
        printf("Type: %s", pokemon_type_to_string( pokemon_first_type(currnode->pokemon)));
        if (pokemon_second_type(currnode->pokemon) != NONE_TYPE) {
            printf(" %s", pokemon_type_to_string( pokemon_second_type(currnode->pokemon)));
        }
        printf("\n");
    }
}

//the insert copied node function inserts the pokenode to the last position of 
//the specific_copy list!! Stage 5:
void insert_copied_node(Pokedex pokedex_new ,struct pokenode *old_node){
    //First we have to malloc memory to store more nodes.
    struct pokenode *node_copy = malloc(sizeof(struct pokenode));
    //Now create the copy of the pokemon
    Pokemon pokemon_copy = new_pokemon(pokemon_id(old_node->pokemon), 
                                pokemon_name(old_node->pokemon), 
                                pokemon_height(old_node->pokemon),
                                pokemon_weight(old_node->pokemon), 
                                pokemon_first_type(old_node->pokemon), 
                                pokemon_second_type(old_node->pokemon));
    
    node_copy->next = NULL;
    node_copy->prev = NULL;
    node_copy->evolve = NULL;
    node_copy->pokemon = pokemon_copy;
    node_copy->found = 1;       //as we are only coping found nodes.
    
   //the following code inserts the new node into the new pokedex(specific_copy)
    if (pokedex_new->head == NULL) {        //if the list is empty.                                           
        pokedex_new->head = node_copy;
        pokedex_new->currnode = node_copy;
    } else {                                //else if the list is not empty.
        struct pokenode *temp; 
        temp = pokedex_new->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node_copy;
        node_copy->prev = temp;
    }
}

//Insert_found_nodes function for stage 5:
void insert_found_nodes(Pokedex pokedex_new ,struct pokenode *old_node){
    //First we have to malloc memory to store more nodes.
    struct pokenode *node_copy = malloc(sizeof(struct pokenode));
    //Now create the copy of the pokemon.
    Pokemon found_pokemon_copy = new_pokemon(pokemon_id(old_node->pokemon), 
                                        pokemon_name(old_node->pokemon), 
                                        pokemon_height(old_node->pokemon),
                                        pokemon_weight(old_node->pokemon), 
                                        pokemon_first_type(old_node->pokemon), 
                                        pokemon_second_type(old_node->pokemon));
    
    node_copy->next = NULL;
    node_copy->prev = NULL;
    node_copy->evolve = NULL;
    node_copy->pokemon = found_pokemon_copy;
    node_copy->found = 1;
    
   //the following code inserts the new node into the new pokedex(specific_copy)
    if (pokedex_new->head == NULL) {        //if the list is empty.                                               
        pokedex_new->head = node_copy;
        pokedex_new->currnode = node_copy;
    } else {                                //else if the list is not empty.
        struct pokenode *temp; 
        temp = pokedex_new->head;
        int stop = 0;
        while (stop == 0) {
            //If the node is being inserted to the front of the list.
            if (temp->prev == NULL && pokemon_id(node_copy->pokemon)<pokemon_id(temp->pokemon)) {
                temp->prev = node_copy;
                node_copy->next = temp;
                pokedex_new->head = node_copy;
                pokedex_new->currnode = node_copy;
                stop = 1;
            } else if (temp->next == NULL && 
                       pokemon_id(node_copy->pokemon)>pokemon_id(temp->pokemon)) {
                //This is the case if the node is being put at the end of list.
                temp->next = node_copy;
                node_copy->prev = temp;
                stop = 1;
            } else if (pokemon_id(node_copy->pokemon)<pokemon_id(temp->next->pokemon)
                       && pokemon_id(node_copy->pokemon)>pokemon_id(temp->pokemon)) {
                //the node is being put between two other nodes.
                node_copy->next = temp->next;
                temp->next = node_copy;
                node_copy->prev = temp;
                
                stop = 1;
            } else {
                //if the insert location has not been found:
                temp = temp->next;
            }
        }
       
    }
}


//This function makes all the letters of the given text set to lower case
//This function is used in the search function in stage 5:
static char *turn_to_lower(char *input) {
    // create a loop counter for the input
    int x = 0;
    int total_characters = 0;
    int loop = 0;
    while (input[loop] != '\0') {
        total_characters++;
        loop++;
    }
    // create new space for storing a lowecase copy of given text for 
    // comparision purposes.
    char *lower_string = malloc(total_characters+1);
    // create a loop counter for lower_string array.
    int y = 0;
    while (input[x] != '\0') {
        lower_string[y] = tolower(input[x]);
        x++;
        y++;
    }
    //lets add a nullteminator at the end!!
    lower_string[y] = '\0';
    return lower_string;
}

//The following function compares two given pieces of text.
//It is used in the search function of Stage 5. 
static int compare_text(char *input, char *dex_name) {
    //changes the given text to all lowercase letters.
    char *input_lower = input;
    input_lower = turn_to_lower(input_lower);
    //counting the total number of letters in the passed argument:
    int total_characters = 0;
    int loop = 0;
    while (input_lower[loop] != '\0') {
        total_characters++;
        loop++;
    }
    
    //change the name of the node we need to compare with the given text to all
    //lowercase letters.
    char *dex_name_lower = dex_name;
    dex_name_lower = turn_to_lower(dex_name_lower);
    
    int flag = 0;       //if the text is the same flag will be one!!
    
    int i = 0;  // i is the input_lower array looper
    while (input_lower[i] != '\0'){
        int total_matched = 0;
        int j = 0;  // j is the dex_name_lower looper
        int stop = 0;
        while (dex_name_lower[j] != '\0' && stop == 0) {
            int copy_location = i; //so we can change the value without changing i
            int copy_name_location = j; //so we can change the value without changing j
            while(input_lower[copy_location] == dex_name_lower[copy_name_location]){
                //if the first letters of both arguments are same then check the next letters.
                if (input_lower[copy_location] == dex_name_lower[copy_name_location]) {
                    copy_name_location++;
                    copy_location++;
                    stop = 1;
                    total_matched++;
                    //if the total matches equals the total characters of argument then stop the loop.
                    if (total_matched == total_characters) {
                        flag = 1;
                        break;
                    }
                }
            }
            j++;
        }
        i++;
    }
    free(input_lower);
    free(dex_name_lower);
    return flag;
}
