#include "communication.h"
#include "util_comm.h"

#include <stdio.h>


/* Task 1 - The Beginning */

void send_byte_message(void)
{
    /* TODO
     * Send the encoding of the characters: R, I, C, K
     */

    send_squanch(18);
    send_squanch(9);
    send_squanch(3);
    send_squanch(11);

}


void recv_byte_message(void)
{
    /* TODO
     * Receive 5 encoded characters, decode them and print
     * them to the standard output (as characters)
     *
     * ATTENTION!: Use fprintf(stdout, ...)
     */
    int i;
    uint8_t character_encoded;
    for (i = 1; i <= 5; i++){
        character_encoded = recv_squanch();
        fprintf(stdout, "%c", character_encoded+64);
    }

}


void comm_byte(void)
{
    /* TODO
     * Receive 10 encoded characters and send each character (the character is
     * still encoded) 2 times
     */

    int i;
    uint8_t character_encoded;
    for (i = 1; i <= 10; i++){
        character_encoded = recv_squanch();
        send_squanch(character_encoded);
        send_squanch(character_encoded);
    }
}


/* Task 2 - Waiting for the Message */

void send_message(void)
{
    /* TODO
     * Send the message: HELLOTHERE
     * - send the encoded length
     * - send each character encoded
     */
    
    //cripteaza lungimea mesajului(10 << 2), apoi il trimite: 
    send_squanch(10 << 2);
    //trimite mesajul litera cu litera:
    send_squanch(8);
    send_squanch(5);
    send_squanch(12);
    send_squanch(12);
    send_squanch(15);
    send_squanch(20);
    send_squanch(8);
    send_squanch(5);
    send_squanch(18);
    send_squanch(5);

}


void recv_message(void)
{
    /* TODO
     * Receive a message:
     * - the first value is the encoded length
     * - length x encoded characters
     * - print each decoded character
     * 
     * ATTENTION!: Use fprintf(stdout, ...)
     */
    uint8_t x, character_encoded;
    int i;

    x = recv_squanch();
    x = x << 2;
    x = x >> 4;
    fprintf(stdout,"%d",x);

    for (i = 1; i <= x; i++){
        character_encoded = recv_squanch();
        fprintf(stdout, "%c", character_encoded + 64);
    }

}


void comm_message(void)
{
    /* TODO
     * Receive a message from Rick and do one of the following depending on the
     * last character from the message:
     * - 'P' - send back PICKLERICK
     * - anything else - send back VINDICATORS
     * You need to send the messages as you did at the previous tasks:
     * - encode the length and send it
     * - encode each character and send them
     */

    uint8_t x, character_encoded;
    //x = lungimea mesajului lui Rick pe care o decodez:
    x = recv_squanch();
    x = x << 2;
    x = x >> 4;

    int i;
    //primesc mesajul litera cu litera, in variabila
    //character_encoded ramanand in final ultima litera
    //din mesaj:
    for (i = 1; i <= x; i++){
        character_encoded = recv_squanch();
    }
    //in functie de ultima litera citita trimite
    //un mesaj:
    if (character_encoded == 16){
        send_squanch(10 << 2);
        send_squanch(16);
        send_squanch(9);
        send_squanch(3);
        send_squanch(11);
        send_squanch(12);
        send_squanch(5);
        send_squanch(18);
        send_squanch(9);
        send_squanch(3);
        send_squanch(11);
    } else {
        send_squanch(11 << 2);
        send_squanch(22);
        send_squanch(9);
        send_squanch(14);
        send_squanch(4);
        send_squanch(9);
        send_squanch(3);
        send_squanch(1);
        send_squanch(20);
        send_squanch(15);
        send_squanch(18);
        send_squanch(19);
    }
}


/* Task 3 - In the Zone */

void send_squanch2(uint8_t c1, uint8_t c2)
{
    /* TODO
     * Steps:
     * - "merge" the character encoded in c1 and the character encoded in c2
     * - use send_squanch to send the newly formed byte
     */

    uint8_t mask, c1_c2_encoded;
    //in c1_c2_encoded se vor codifica cele doua caractere
    c1_c2_encoded = 0;
    int i;
    for (i = 0; i <= 3; i++){
        mask = 1 << i;
        if (c2 & mask){
            c1_c2_encoded = c1_c2_encoded + (mask << i);
            //ia fiecare bit activ din c2 si il pune pe pozitiile pare
            //i (de la initializarea lui mask ) + i = 2*i
        }
        if (c1 & mask){
            c1_c2_encoded = c1_c2_encoded + (mask << (i + 1));
            //ia fiecare bit activ din c1 si il pune pe pozitiile impare
            //i (de la initializarea lui mask ) + i + 1 = 2*i + 1
        }
    }
    send_squanch(c1_c2_encoded);
}


uint8_t decode_squanch2(uint8_t c)
{
    /*
     * Decode the given byte:
     * - split the two characters as in the image from ocw.cs.pub.ro
     */

    uint8_t res = -1;

    /* TODO */
    uint8_t mask, k;
    int i;
    res = 0;
    for (i = 0; i <= 7; i++){
        mask = 1 << i;
        if (i % 2 == 0 && (c & mask)){
            k = mask >> (i/2);
            res = res + k;
            //bitul de pe 0 se duce pe pozitia 0 in res
            //bitul de pe 2 se duce pe pozitia 1 in res
            //bitul de pe 4 se duce pe pozitia 2 in res
            //bitul de pe 6 se duce pe pozitia 3 in res
        }
        if (i % 2 == 1 && (c & mask)){
            k = mask >> (i/2);
            k = k << 3;
            res = res + k;
            //bitul de pe 1 se duce pe pozitia 4 in res
            //bitul de pe 3 se duce pe pozitia 5 in res
            //bitul de pe 5 se duce pe pozitia 6 in res
            //bitul de pe 7 se duce pe pozitia 7 in res
        }
    }

    return res;
}
