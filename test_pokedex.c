// Assignment 2 19T1 COMP1511: Pokedex
// test_pokedex.c
//
// This file allows you to automatically test the functions you
// implement in pokedex.c.
//
// This program was written by YOUR-NAME-HERE (z5555555)
// on INSERT-DATE-HERE
//
// Version 1.0.0: Assignment released.
// Version 1.0.1: Added pointer check for the provided tests.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "pokedex.h"

// Add your own #defines here.


// Sample data on Bulbasaur, the Pokemon with pokemon_id 1.
#define BULBASAUR_ID 1
#define BULBASAUR_NAME "Bulbasaur"
#define BULBASAUR_HEIGHT 0.7
#define BULBASAUR_WEIGHT 6.9
#define BULBASAUR_FIRST_TYPE GRASS_TYPE
#define BULBASAUR_SECOND_TYPE POISON_TYPE

// Sample data on Ivysaur, the Pokemon with pokemon_id 2.
#define IVYSAUR_ID 2
#define IVYSAUR_NAME "Ivysaur"
#define IVYSAUR_HEIGHT 1.0
#define IVYSAUR_WEIGHT 13.0
#define IVYSAUR_FIRST_TYPE GRASS_TYPE
#define IVYSAUR_SECOND_TYPE POISON_TYPE


struct pokedex {
    struct pokenode *head;
    struct pokenode *currnode;
};
struct pokenode {
    struct pokenode *next;
    struct pokenode *prev;    //pointer to the previous element in the list.
    struct pokenode *evolve;  //pointer to the node the pokemon evolves to.
    int found;                //Default set to 0. 1 if pokemon is found.
    Pokemon         pokemon;
};

// Add your own prototypes here.


// Tests for Pokedex functions from pokedex.c.
//s1
static void test_new_pokedex(void);           //done
static void test_add_pokemon(void);           //done
static void test_detail_pokemon(void);        //done
static void test_get_current_pokemon(void);   //done 
static void test_find_current_pokemon(void);  //done
static void test_print_pokemon(void);         //done

//s2
static void test_next_pokemon(void);          //done  
static void test_prev_pokemon(void);          //done
static void test_change_current_pokemon(void);//done
static void test_remove_pokemon(void);        //done
static void test_destroy_pokedex(void);       //done

//s3
static void test_go_exploring(void);          //done
static void test_count_found_pokemon(void);   //done
static void test_count_total_pokemon(void);   //done

//s4
static void test_add_pokemon_evolution(void); //done
static void test_show_evolutions(void);       //done
static void test_get_next_evolution(void);    //done

//s5
static void test_get_pokemon_of_type(void);   //done
static void test_get_found_pokemon(void);     //done 
static void test_search_pokemon(void);        //done

// Helper functions for creating/comparing Pokemon.
static Pokemon create_bulbasaur(void);
static Pokemon create_ivysaur(void);
static int is_same_pokemon(Pokemon first, Pokemon second);
static int is_copied_pokemon(Pokemon first, Pokemon second);



int main(int argc, char *argv[]) {
    printf("Welcome to the COMP1511 Pokedex Tests!\n");

    printf("\n==================== Pokedex Tests ====================\n");

    test_new_pokedex();
    test_add_pokemon();
    test_detail_pokemon();
    test_get_current_pokemon();
    test_find_current_pokemon();
    test_print_pokemon();
    test_prev_pokemon();
    test_change_current_pokemon();
    test_remove_pokemon();
    test_destroy_pokedex();
    test_next_pokemon();  
    test_go_exploring();
    test_count_found_pokemon();
    test_count_total_pokemon();
    test_add_pokemon_evolution();
    test_show_evolutions();
    test_get_next_evolution();
    test_get_pokemon_of_type();
    test_get_found_pokemon();
    test_search_pokemon();

    printf("\n\nAll Pokedex tests passed, you are the best coder on Earth!\n");
    printf("NOW THERE IS NO REASON FOR YOUR TEACHERS TO NOT GIVE YOU 100 PERCENT\n\n\n");
}


////////////////////////////////////////////////////////////////////////
//                     Pokedex Test Functions                         //
////////////////////////////////////////////////////////////////////////

// `test_new_pokedex` checks whether the new_pokedex and destroy_pokedex
// functions work correctly, to the extent that it can.
//
// It does this by creating a new Pokedex, checking that it's not NULL,
// then calling destroy_pokedex.
//
// Note that it isn't possible to check whether destroy_pokedex has
// successfully destroyed/freed the Pokedex, so the best we can do is to
// call the function and make sure that it doesn't crash..
static void test_new_pokedex(void) {
    printf("\n>> Testing new_pokedex\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("       --> Checking that the returned Pokedex is not NULL\n");
    assert(pokedex != NULL);

    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed new_pokedex tests!\n");
}

// `test_add_pokemon` checks whether the add_pokemon function works
// correctly.
//
// It does this by creating the Pokemon Bulbasaur (using the helper
// functions in this file and the provided code in pokemon.c), and
// calling add_pokemon to add it to the Pokedex.
//
// Some of the ways that you could extend these test would include:
//   - adding additional Pokemon other than just Bulbasaur,
//   - checking whether the currently selected Pokemon is correctly set,
//   - checking that functions such as `count_total_pokemon` return the
//     correct result after more Pokemon are added,
//   - ... and more!
static void test_add_pokemon(void) {
    printf("\n>> Testing add_pokemon\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();
    
    assert(count_total_pokemon(pokedex) == 0);

    printf("    ... Creating Bulbasaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    
    printf("    ... Adding Bulbasaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    
    assert(count_total_pokemon(pokedex) == 1);

    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed add_pokemon tests!\n");
}

// `test_next_pokemon` checks whether the next_pokemon function works
// correctly.
//
// It does this by creating two Pokemon: Bulbasaur and Ivysaur (using
// the helper functions in this file and the provided code in pokemon.c).
//
// It then adds these to the Pokedex, then checks that calling the
// next_pokemon function changes the currently selected Pokemon from
// Bulbasaur to Ivysaur.
//
// Some of the ways that you could extend these tests would include:
//   - adding even more Pokemon to the Pokedex,
//   - calling the next_pokemon function when there is no "next" Pokemon,
//   - calling the next_pokemon function when there are no Pokemon in
//     the Pokedex,
//   - ... and more!
static void test_next_pokemon(void) {
    printf("\n>> Testing next_pokemon\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Bulbasaur and Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);

    printf("       --> Checking that the current Pokemon is Bulbasaur\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));

    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);

    printf("       --> Checking that the current Pokemon is Ivysaur\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), ivysaur));

    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed next_pokemon tests!\n");
}

// `test_get_found_pokemon` checks whether the get_found_pokemon
// function works correctly.
//
// It does this by creating two Pokemon: Bulbasaur and Ivysaur (using
// the helper functions in this file and the provided code in pokemon.c).
//
// It then adds these to the Pokedex, sets Bulbasaur to be found, and
// then calls the get_found_pokemon function to get all of the Pokemon
// which have been found (which should be just the one, Bulbasaur).
//
// Some of the ways that you could extend these tests would include:
//   - calling the get_found_pokemon function on an empty Pokedex,
//   - calling the get_found_pokemon function on a Pokedex where none of
//     the Pokemon have been found,
//   - checking that the Pokemon in the new Pokedex are in ascending
//     order of pokemon_id (regardless of the order that they appeared
//     in the original Pokedex),
//   - checking that the currently selected Pokemon in the returned
//     Pokedex has been set correctly,
//   - checking that the original Pokedex has not been modified,
//   - ... and more!
static void test_get_found_pokemon(void) {
    printf("\n>> Testing get_found_pokemon\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Bulbasaur and Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);

    printf("       --> Checking that the current Pokemon is Bulbasaur\n");
    assert(get_current_pokemon(pokedex) == bulbasaur);
    
    printf("    ... Setting Bulbasaur to be found\n");
    find_current_pokemon(pokedex);

    printf("    ... Getting all found Pokemon\n");
    Pokedex found_pokedex = get_found_pokemon(pokedex);

    printf("       --> Checking the correct Pokemon were copied and returned\n");
    assert(count_total_pokemon(found_pokedex) == 1);
    assert(count_found_pokemon(found_pokedex) == 1);
    assert(is_copied_pokemon(get_current_pokemon(found_pokedex), bulbasaur));

    printf("    ... Destroying both Pokedexes\n");
    destroy_pokedex(pokedex);
    destroy_pokedex(found_pokedex);

    printf(">> Passed get_found_pokemon tests!\n");
}

// Write your own Pokedex tests here!
static void test_detail_pokemon(void) {
    printf("\n>> Testing detail_pokemon\n");
    
    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();
    
    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Bulbasaur and Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);

    printf("       --> Checking that the current Pokemon is Bulbasaur\n");
    assert(get_current_pokemon(pokedex) == bulbasaur);
    
    printf("    ... Setting Bulbasaur to be found\n");
    find_current_pokemon(pokedex);
    
    printf("    ... Printing the details of Bulbasaur\n");
    detail_pokemon(pokedex);
       
    printf("If the detail function does not blow up then it is probably working\n");
    printf("If the name that the function prints is Bulbasaur...yay you are ");
    printf("probably on the right track!!\n");
    
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

}

static void test_get_current_pokemon(void) {
    printf("\n>> Testing get_current_pokemon\n");
    
    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();
    
    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Bulbasaur and Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);

    printf("       --> Checking that the current Pokemon is Bulbasaur\n");
    assert(get_current_pokemon(pokedex) == bulbasaur);
    
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);
    
    printf("    ... All tests for get_current_pokemon worked!!!\n");
}

static void test_find_current_pokemon(void) {
    printf("\n>> Testing find_current_pokemon\n");
    
    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();
    
    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Bulbasaur and Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);
    
    printf("    ... setting Bulbasaur to be found\n");
    find_current_pokemon(pokedex);
    
    printf("    ... making sure that the find_current_pokemon worked.\n");
    assert(pokedex->currnode->found == 1);
    
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf("    ... All tests for find_current_pokemon worked!!!\n");
}

static void test_print_pokemon(void) {
    printf("\n>> Testing print_pokemon\n");
    
    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();
    
    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Bulbasaur and Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);
    
    printf("    ... Printing hidden details of the pokemons\n");
    print_pokemon(pokedex);
    
    printf("    ... You should see *'s displayed above.\n");
    
    printf("    ... setting Bulbasaur to be found\n");
    find_current_pokemon(pokedex);
    
    printf("    ... Now you should see Bulbasaur and ******* under it.\n");
    print_pokemon(pokedex);
    printf("    ... if these 2 tests worked you have a reason to be happy!!\n");
    
    destroy_pokedex(pokedex);
    
}

static void test_prev_pokemon(void) {
    printf("\n>> Testing prev_pokemon\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Bulbasaur and Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);

    printf("       --> Checking that the current Pokemon is Bulbasaur\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));

    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);

    printf("       --> Checking that the current Pokemon is Ivysaur\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), ivysaur));

    printf("    ... Moving to the previous pokemon\n");
    prev_pokemon(pokedex);

    printf("       --> Checking that the current Pokemon is Bulbasaur\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));
    
    printf("  ...Moving one step back to make sure the pointer does not dissapear\n");
    prev_pokemon(pokedex);
    
    printf("       --> Checking that the current Pokemon is still Bulbasaur\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));    

    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed prev_pokemon tests!\n");

}

static void test_change_current_pokemon(void) {
    printf("\n>> Testing change_current_pokemon\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Bulbasaur and Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);

    printf("       --> Checking that the current Pokemon is Bulbasaur\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));

    printf("       --> Channging the current pokemon to Ivysaur by using its ID\n");
    change_current_pokemon(pokedex, 2);
    
    printf("       --> Checking that the current Pokemon is Ivysaur\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), ivysaur));
    
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed change_current_pokemon tests!\n");
    
}

static void test_remove_pokemon(void) {
    printf("\n>> Testing remove_pokemon\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Bulbasaur and Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);
    
    printf("       --> Checking if the total number of pokemons is correct\n");
    assert(count_total_pokemon(pokedex) == 2);
    
    printf("    ... Removing Bulbasaur from the Pokedex\n");
    remove_pokemon(pokedex);
    
    printf("    ... counting total number of pokemons in the Pokedex\n");
    count_total_pokemon(pokedex);
    
    printf("       --> Checking if the total number of pokemons is correct\n");
    assert(count_total_pokemon(pokedex) == 1);
    
    printf("    ... Removing Ivysaur from the Pokedex\n");
    remove_pokemon(pokedex);
    
    printf("    ... counting total number of pokemons in the Pokedex\n");
    count_total_pokemon(pokedex);
    
    printf("       --> Checking if the total number of pokemons is correct\n");
    assert(count_total_pokemon(pokedex) == 0);
    
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed remove_pokemon tests!\n");
}

static void test_go_exploring(void) {
    printf("\n>> Testing go_exploring\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Bulbasaur and Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);
    
    printf("    ... Setting a random pokemon to be found.\n");
    go_exploring(pokedex, 69, 3, 10000);
    
    printf("    ... Checking if total found pokemons are more than zero.\n");
    assert(count_found_pokemon(pokedex) > 0);
    
    printf("    ... Printing details of the pokemons\n");
    print_pokemon(pokedex);
    printf("    ... One or more of the pokemons above should not be hidden!\n");
    
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed go_exploreing tests!\n");
    
}

static void test_count_found_pokemon(void) {
    printf("\n>> Testing count_found_pokemon\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Bulbasaur and Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);
    
    printf("    ... Total number of found pokemons should be 0.\n");
    assert(count_found_pokemon(pokedex) == 0);
    
    printf("    ... Setting Bulbasaur to be found.\n");
    find_current_pokemon(pokedex);
    
    printf("    ... Total number of found pokemons should be 1.\n");
    assert(count_found_pokemon(pokedex) == 1);
    
    printf("    ... Moving pointer to Ivysaur.\n");
    next_pokemon(pokedex);
    
    printf("    ... Setting Ivysaur to be found.\n");
    find_current_pokemon(pokedex);
    
    printf("    ... Total number of found pokemons should be 2.\n");
    assert(count_found_pokemon(pokedex) == 2);
    
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed count_found_pokemon tests!\n");    
}

static void test_count_total_pokemon(void) {
    printf("\n>> Testing count_total_pokemon\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Bulbasaur and Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);
    
    printf("    ... Asserting..Total number of pokemons should be 2.\n");
    assert(count_total_pokemon(pokedex) == 2);
    
    printf("    ... removing Bulbasaur.\n");
    remove_pokemon(pokedex);
    
    printf("       --> Asserting..Total number of pokemons should be 1.\n");
    assert(count_total_pokemon(pokedex) == 1);
    
    printf("    ... Removing Ivysaur from the Pokedex\n");
    remove_pokemon(pokedex);
    
    printf("       --> Asserting..Total number of pokemons should be 0.\n");
    assert(count_total_pokemon(pokedex) == 0);
    
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed count_total_pokemon tests!\n");

}

static void test_add_pokemon_evolution(void) {
    printf("\n>> Testing add_pokemon_evolution\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Bulbasaur and Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);
    
    printf("    ... Bulbasaur should now evolve to be Ivysaur\n");
    add_pokemon_evolution(pokedex, 1, 2);
    
    printf("    ... Asserting...is Bulbasaur evolving correctly...\n");
    assert(pokemon_id(pokedex->currnode->evolve->pokemon) == 2);
    
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed add_pokemon_evolution tests!\n");

}

static void test_show_evolutions(void) {
    printf("\n>> Testing show_evolutions\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Bulbasaur and Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);
    
    printf("    ... Bulbasaur should now evolve to be Ivysaur\n");
    add_pokemon_evolution(pokedex, 1, 2);
    
    printf("    ... Setting Bulbasaur to be found.\n");
    find_current_pokemon(pokedex);
    
    printf("    ... Setting Ivysaur to be found.\n");
    next_pokemon(pokedex);
    find_current_pokemon(pokedex);
    prev_pokemon(pokedex);
    
    printf("    ... Calling show evolution function on the next line.\n");
    show_evolutions(pokedex);
    
    printf("    ... the above line should display:\n");
    printf("#001 Bulbasaur [Grass, Poison] --> #002 Ivysaur [Grass, Poison]\n");
    
    destroy_pokedex(pokedex);

    printf("If the above 2 lines match >> Passed show_evolutions tests!\n");
    
}

static void test_get_next_evolution(void) {
    printf("\n>> Testing get_next_evolution\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Bulbasaur and Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);
    
    printf("    ... Testing get_next_evolution for the case of no evolutions\n");
    assert(get_next_evolution(pokedex) == DOES_NOT_EVOLVE);
    
    printf("    ... Bulbasaur should now evolve to be Ivysaur\n");
    add_pokemon_evolution(pokedex, 1, 2);
    
    printf("    ... Setting Bulbasaur to be found.\n");
    find_current_pokemon(pokedex);
    
    printf("    ... Setting Ivysaur to be found.\n");
    next_pokemon(pokedex);
    find_current_pokemon(pokedex);
    prev_pokemon(pokedex);
    
    printf("    ... Testing get_next_evolution...asserting in progress... \n");
    assert(get_next_evolution(pokedex) == 2);
    
    destroy_pokedex(pokedex);

    printf(">> Passed get_next_evolution tests!\n");
    
}

static void test_get_pokemon_of_type(void) {
    printf("\n>> Testing get_pokemon_of_type\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Bulbasaur and Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);

    printf("       --> Checking that the current Pokemon is Bulbasaur\n");
    assert(get_current_pokemon(pokedex) == bulbasaur);
    
    printf("    ... Setting Bulbasaur to be found\n");
    find_current_pokemon(pokedex);

    printf("    ... Getting all specific type Grass Pokemon\n");
    Pokedex specific_pokedex = get_pokemon_of_type(pokedex, GRASS_TYPE);

    printf("       --> Checking the correct Pokemon were copied and returned\n");
    assert(count_total_pokemon(specific_pokedex) == 1);
    assert(count_found_pokemon(specific_pokedex) == 1);
    assert(is_copied_pokemon(get_current_pokemon(specific_pokedex), bulbasaur));
    print_pokemon(specific_pokedex);

    printf("    ... Destroying both Pokedexes\n");
    destroy_pokedex(pokedex);
    destroy_pokedex(specific_pokedex);

    printf(">> Passed get_pokemon_of_type tests!\n");

}

static void test_search_pokemon(void){
    printf("\n>> Testing search_pokemon\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Bulbasaur and Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);

    printf("       --> Checking that the current Pokemon is Bulbasaur\n");
    assert(get_current_pokemon(pokedex) == bulbasaur);
    
    printf("    ... Setting Bulbasaur to be found\n");
    find_current_pokemon(pokedex);

    printf("    ... Searching Bulbasaur Pokemon by using Bulb\n");
    char *text = "Bulb";
    Pokedex searched_pokedex = search_pokemon(pokedex, text);
    
    printf("       --> Checking the correct Pokemon were copied and returned\n");
    assert(count_total_pokemon(searched_pokedex) == 1);
    assert(count_found_pokemon(searched_pokedex) == 1);
    assert(is_copied_pokemon(get_current_pokemon(searched_pokedex), bulbasaur));
    print_pokemon(searched_pokedex);

    printf("    ... Destroying both Pokedexes\n");
    destroy_pokedex(pokedex);
    destroy_pokedex(searched_pokedex);

    printf(">> Passed search_pokemon tests!\n");

}

static void test_destroy_pokedex(void) {
    printf("\n>> Testing destroy_pokedex\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Bulbasaur and Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);
    
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> NOW COMPILE THIS CODE WITH dcc --leak-check.\n");
    printf(">> IF THERE ARE NO MEMORY LEAKS THEN YOUR CODE IS BEAUTIFUL!!!!\n");
    
}

////////////////////////////////////////////////////////////////////////
//                     Helper Functions                               //
////////////////////////////////////////////////////////////////////////

// Helper function to create Bulbasaur for testing purposes.
static Pokemon create_bulbasaur(void) {
    Pokemon pokemon = new_pokemon(
            BULBASAUR_ID, BULBASAUR_NAME,
            BULBASAUR_HEIGHT, BULBASAUR_WEIGHT,
            BULBASAUR_FIRST_TYPE,
            BULBASAUR_SECOND_TYPE
    );
    return pokemon;
}

// Helper function to create Ivysaur for testing purposes.
static Pokemon create_ivysaur(void) {
    Pokemon pokemon = new_pokemon(
            IVYSAUR_ID, IVYSAUR_NAME,
            IVYSAUR_HEIGHT, IVYSAUR_WEIGHT,
            IVYSAUR_FIRST_TYPE,
            IVYSAUR_SECOND_TYPE
    );
    return pokemon;
}

// Helper function to compare whether two Pokemon are the same.
// This checks that the two pointers contain the same address, i.e.
// they are both pointing to the same pokemon struct in memory.
//
// Pokemon ivysaur = new_pokemon(0, 'ivysaur', 1.0, 13.0, GRASS_TYPE, POISON_TYPE)
// Pokemon also_ivysaur = ivysaur
// is_same_pokemon(ivysaur, also_ivysaur) == TRUE
static int is_same_pokemon(Pokemon first, Pokemon second) {
    return first == second;
}

// Helper function to compare whether one Pokemon is a *copy* of
// another, based on whether their attributes match (e.g. pokemon_id,
// height, weight, etc).
// 
// It also checks that the pointers do *not* match -- i.e. that the
// pointers aren't both pointing to the same pokemon struct in memory.
// If the pointers both contain the same address, then the second
// Pokemon is not a *copy* of the first Pokemon.
// 
// This function doesn't (yet) check that the Pokemon's names match
// (but perhaps you could add that check yourself...).
static int is_copied_pokemon(Pokemon first, Pokemon second) {
    return (pokemon_id(first) == pokemon_id(second))
    &&  (first != second)
    &&  (pokemon_height(first) == pokemon_height(second))
    &&  (pokemon_weight(first) == pokemon_weight(second))
    &&  (pokemon_first_type(first) == pokemon_first_type(second))
    &&  (pokemon_second_type(first) == pokemon_second_type(second));
}

// Write your own helper functions here!
