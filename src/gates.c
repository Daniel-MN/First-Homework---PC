#include "gates.h"

#include <stdio.h>
#include <assert.h>

/* Task 1 - Bit by Bit */

uint8_t get_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint8_t res = -1;

    /* TODO
     *
     * "res" should be 1 if the bit is active, else 0
     */

    /* Daca bitul i este setat atunci nr & (1UL << i)
     * este egal cu 1UL << i, iar daca nu este setat,
     * atunci nr & (1UL << i) este egal cu 0
     */ 
    if (nr & (1UL << i)){
        res = 1;
    } else {
        res = 0;
    }

    return res;
}


uint64_t flip_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

    /* TODO
     *
     * Return the "nr" with the ith bit flipped
     */

    /*Daca bitul i este 1 atunci 1 ^ 1 = 0,
     *iar daca i este 0 atunci 0 ^ 1 = 1.
     */
    res = nr ^ (1UL << i);

    return res;
}


uint64_t activate_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = 0xFF;

    /* TODO
     *
     * Return the "nr" with the ith bit "1"
     */
    
    /* Daca bitul i este 1 atunci
     * 1 | 1 = 1, iar daca este 0
     * atunci 0 | 1 = 1.
     */
    res = nr | (1UL << i);

    return res;
}


uint64_t clear_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

    /* TODO
     *
     * Return the "nr" with the ith bit "0"
     */
    
    /* Bitul i & 0 = 0,
     * iar bitul j & 1 = valoarea
     * bitului j, pentru j != i.
     */
    res = nr & ~(1UL << i);

    return res;
}


/* Task 2 - One Gate to Rule Them All */

uint8_t nand_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    return !(a & b);
}


uint8_t and_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the nand gate to implement the and gate */

    res = nand_gate(nand_gate(a, b), nand_gate(a, b));

    return res;
}


uint8_t not_gate(uint8_t a)
{
    assert (a == 0 || a == 1);

    uint8_t res = -1;

    /* TODO - Use the nand gate to implement the not gate */

    res = nand_gate(a, a);

    return res;
}


uint8_t or_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the previously defined gates to implement the or gate */

    res = nand_gate(not_gate(a), not_gate(b));

    return res;
}


uint8_t xor_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the previously defined gates to implement the xor gate */
    
    // a ^ b = !(!(a & !(a & b)) & !(b & !(a & b))) =
    //       = (a & !(a & b)) | (b & !(a & b)) =
    //       = (a & (!a | !b)) | (b & (!a | !b)) =
    //       = (a & !b) | (!a & b)
    res = or_gate(and_gate(a, not_gate(b)), and_gate(not_gate(a), b));

    return res;
}


/* Task 3 - Just Carry the Bit */

uint8_t full_adder(uint8_t a, uint8_t b, uint8_t c)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);
    assert (c == 0 || c == 1);

    uint8_t res = -1;

    /* TODO - implement the full_adder using the previous gates
     * Since the full_adder needs to provide 2 results, you should
     * encode the sum bit and the carry bit in one byte - you can encode
     * it in whatever way you like
     */

    uint8_t full_adder_sum, full_adder_carry;
    //Calculeaza suma pentru full adder: sum = a ^ b ^ c
    full_adder_sum = xor_gate(xor_gate(a, b), c);
    //Calculeaza carry pentru full adder: 
    // carry = ((a ^ b) & c) | (a & b).
    full_adder_carry = or_gate(and_gate(xor_gate(a, b), c), and_gate(a,b));

    //pe bitul 0 va sta sum, iar pe bitul 1 va sta carry
    res = full_adder_sum + 2 * full_adder_carry;

    return res;
}


uint64_t ripple_carry_adder(uint64_t a, uint64_t b)
{
    uint64_t res = -1;

    /* TODO
     * Use the full_adder to implement the ripple carry adder
     * If there is ANY overflow while adding "a" and "b" then the
     * result should be 0
     */

    int i;
    uint8_t bit_a, bit_b, carry, sum;
    carry = 0;
    res = 0;
    for (i = 0; i <= 63; i++ ){
        /*va face full_adder pentru fiecare pereche de biti
         *(unul din a, unul din b) si carry-ul de la
         *full_adder-ul precedent. Pentru primul 
         *full_adder se va folosi carry = 0;
         */ 
        bit_a = get_bit(a, i);
        bit_b = get_bit(b, i);
        /*se foloseste get_bit pentru extragerea sumei,
         *care se afla pe bitul 0 si a lui carry, care 
         *se afla pe bitul 1:
         */
        sum = get_bit(full_adder(bit_a, bit_b, carry), 0);
        carry = get_bit(full_adder(bit_a, bit_b, carry), 1);
        if (sum){
            res = activate_bit(res, i);
        } else {
            res = clear_bit(res, i);
        }
    }

    /*daca ultimul carry este > 0 atunci va aparea overflow.
     *ultimul carrry fiind folosit teoretic in urmatoarea 
     *adunare pe biti, care nu se face.
     */
    if (carry > 0){
        res = 0;
    }
    return res;
}
