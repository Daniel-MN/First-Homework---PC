#include "hunt.h"
#include <stdio.h>

/* Task 1 - Axii */

uint16_t find_spell(uint64_t memory)
{
    /*
     * The spell is 16 bits and they are in the memory exactly after 5
     * consecutive bits of 1:
     *
     *            high                                             low
     *                [][][x]...[x][x][x][1][1][1][1][1][]...[][][]
     *                    |----16bits---|
     *                          Spell
     *
     * There is only 1 group of 5 consecutive bits of 1 and the other groups
     * have less than consecutive bits of 1
     * Steps:
     * - find 5 consecutive bits of 1
     * - the NEXT 16 bits == spell
     */

    uint16_t res = -1;

    /* TODO */
    int OK = 0;
    int i = -1;
    int j;
    uint64_t mask;

    //OK arata daca s-au gasit 5 biti consecutivi de 1
    while (OK == 0){
        i++;
        //31 = 11111 in baza 2
        mask = 31UL << i;
        if ((memory & mask) == mask){
            OK = 1;
        }
    }
    /*sare peste cei 5 biti de 1 ca sa ajunga la primul bit pe
     *pe care este spell:
     */ 
    i = i + 5;

    res = 0;

    //verifica fiecare bit din spell si il scrie in res:
    for (j = i; j <= i + 15; j++){
        mask = 1UL << j;
        if (memory & mask){
            res = res + (1 << (j - i));
        }
    }

    return res;
}


uint16_t find_key(uint64_t memory)
{
    /*
     * The key is 16 bits and they are in the memory exactly before 3
     * consecutive bits of 1:
     *
     *                high                                           low
     *                     [][][][1][1][1][x][x]...[x][x][]...[][][]
     *                                    |----16bits---|
     *                                           Key
     * Steps:
     * - find 3 consecutive bits of 1
     * - the PREVIOUS 16 bits == key
     */

    uint16_t res = -1;

    /* TODO */

    int OK = 0;
    int i = 62;
    int j;
    uint64_t mask;
    //OK
    while (OK == 0){
        i--;
        mask = 7UL << i;
        if ((memory & mask) == mask){
            OK = 1;
        }
    }
    i = i - 16;

    res = 0;

    for (j = i; j <= i + 15; j++){
        mask = 1UL << j;
        if (memory & mask){
            res = res + (1 << (j - i));
        }
    }

    return res;
}


uint16_t decrypt_spell(uint16_t spell, uint16_t key)
{
    /*
     * Find the spell knowing that
     * spell_encrypted = spell_plaintext ^ key
     */

    uint16_t res = -1;

    /* TODO */

    /*     spell_encrypted = spell_plaintext ^ key <=>
	 * <=> spell_encrypted ^ key = spell_plaintext ^ key ^ key <=>
	 * <=> spell_plaintext = spell_encrypted ^ key
     * Explicatia detaliata se gaseste in fisierul readme.
     */

    res = spell ^ key;

    return res;
}


/* Task 2 - Sword Play */

uint32_t choose_sword(uint16_t enemy)
{
    /*
     * Help Geralt construct a sword that will give him an advantage in battle.
     * The steps we will follow:
     * - choose the corect sword
     * - brand the sword with the correct runes such that the equation
     * for that specific enemy type is true
     *
     * How does the sword look (Sword template):
     *  [][][][] [0][0][0]...[0][0][0] [][][][][][][][][][][][][][][][]
     *  -------- --------------------- --------------------------------
     *     Type    Does not matter      The "Value" such that the equation
     *                               from 2 holds depending on the enemy type
     *    4 bits      12 bits                     16 bits
     *
     * 1. Type of the sword:
     * - 1001 - Silver Sword - for monsters
     * - 0110 - Steel Sword - for humans
     *
     *  If the number of active bits from variable "enemy" is even == Monster
     *  else == Human
     *
     * 2.
     * Monster Equation:
     *    Value ^ (Enemy & (1 - Enemy)) = 0
     *
     * Human Equation:
     *    Value + Enemy = 0
     */

    uint32_t res = -1;

    /* TODO */

    uint16_t mask, value;
    int nr = 0;
    int i;
    
    //numara cati biti sunt activi in variabila "enemy":
    for (i = 0; i <= 15; i++){
        mask = 1 << i;
        if (enemy & mask){
            nr++;
        }
    }

    /* Daca numarul lor este par atunci pregatim o sabie pentru
     * monster, else pentru human
     */
    if (nr % 2 == 0){
        // 1001 in baza 2 = 9
        res = 9 << 28;
        // folosind acelasi rationament ca la decrypt_spell, obtin:
        // (detalii in readme)
        value = (enemy & (1 - enemy));
        res = res + value;
    } else {
        // 0110 in baza 2 = 6
        res = 6 << 28;
        value = 0 - enemy;
        res = res + value;
    }

    return res;
}


/* Task 3 - The Witcher Trials */

uint32_t trial_of_the_grasses(uint16_t cocktail)
{
    /*
     * To become a witcher one must survive a cocktail of different
     * herbs. The body should generate the correct antibodies to
     * neutralize the given cocktail.
     *
     *
     * The antibodies need to respect the following properties:
     *   (antibodies_high & cocktail) ^ (antibodies_low | cocktail) = 0
     *   antibodies_low & antibodies_high = 0
     *   antibodies_low | antibodies_high = cocktail
     *
     * Where:
     *  [][][]...[][][] | [][][]...[][][]
     *  ---------------   ---------------
     *  antibodies_high    antibodies_low
     *      16 bits           16 bits
     *      -------------------------
     *              antibodies
     */

    uint32_t res = -1;

    /* TODO */

    //Explicatia se afla in readme.
    res = cocktail << 16;

    return res;
}


uint8_t trial_of_forrest_eyes(uint64_t map)
{
    /*
     * For the next trail, the candidate is tied up and blindfolded.
     * They are also taken to a forest and they should return until
     * the next morning.
     *
     * The candidate knows that there are 4 possibilities for the forest:
     * Brokilon, Hindar, Wolven Glade and Caed Dhu.
     *
     * The candidate also knows those forests by heart, but first you
     * need to identify the forest.
     *
     * The characteristics for 3 of the forests are as follows:
     * - Brokilon - has ONLY groups of 4 trees (or a forest without any tree)
     *   Ex: a group of 4 trees: "...00111100..."
     * - Hindar - has ONLY 2 trees in the MIDDLE
     * - Wolven Glade - FULL of trees
     *
     * The "map" variable encodes the following information:
     * - 1 tree
     * - 0 patch of grass
     *
     * You should put in the "res" variable the index for the identified
     * forrest.
     * - Brokilon - index 0
     * - Hindar - index 1
     * - Wolven Glade - index 2
     * - Caed Dhu - index 3
     */

    uint8_t res = -1;

    /* TODO */

    uint64_t mask;
    int i=-1;

    //testeaza daca sunt doar 2 copaci in mijloc:
    mask = 3UL << 31;
    if (map == mask){
        return 1;
    } else {
        res = 0;
    }

    //testeaza daca padurea are doar grupuri de 4 copaci:
    while (res == 0 && i < 63){
        i++;
        mask = 1UL << i;
        if (map & mask){
            if (map & (mask << 1)){
                if (map & (mask << 2)){
                    if (map & (mask << 3)){
                        if ((map & (mask << 4)) == 0){
                            i = i + 4;
                        } else {
                            res = 2;
                        }
                    } else {
                        res = 2;
                    }
                } else {
                    res = 2;
                }
            } else {
                res = 2;
            }
        }
    }

    /*testeaza daca padurea este plina de copaci, daca exista
     *vreun loc in care nu exista copac atunci obtinem res = 3,
     *adica ne aflam in padurea Caed Dhu:
     */
    if (res == 2){
        for (i = 0; i <= 63; i++){
            mask = 1UL << i;
            if ((map & mask) == 0){
                i = 64;
                res = 3;
            }
        }
    }

    return res;
}


uint8_t trial_of_the_dreams(uint32_t map)
{
    /*
     * For this final trial, the candidates go into a trance and when
     * they woke up they would be a fully fledged witcher.
     *
     * For this task, you need to help the witcher find the number
     * of steps that would take the candidate from the dream realm to
     * the real world.
     *
     * The "map" variable would have only 2 bits of 1:
     * - candidate location
     * - portal location
     *
     * You should put in the "res" variable the distance from the
     * candidate position to the portal.
     *
     *  Ex:
     *  [0][0][0][0][0][0]....[1][0][0][0][0][1][0]....[0][0][0]
     *
     *  res = 5
     */

    uint8_t res = -1;

    /* TODO */

    uint64_t mask;
    int i, j, OK;
    OK = 0;
    i = -1;

    //cauta primul bit activ din map, OK devine 1 cand il gaseste:
    while (OK == 0){
        i++;
        mask = 1UL << i;
        if (map & mask){
            OK = 1;
        }
    }
    //in variabila i se retine pozitia primului bit activ

    //cauta al doilea bit activ din map:
    //OK devine 1 cand il gaseste
    j = i;
    OK = 0;
    while (OK == 0){
        j++;
        mask = 1UL << j;
        if (map & mask){
            OK = 1;
        }
    }
    //in variabila j ramane pozitia celui de-al doilea bit activ

    res = j - i;

    return res;
}
