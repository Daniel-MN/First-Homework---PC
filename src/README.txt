//Mușuroi Daniel-Nicușor
//313CB
//PC - Tema 1

			Part 1 - Bits & Pieces

		Part 1.1 - Bit by Bit
	
	Functiile de la acest task (get_bit, flip_bit, activate_bit, clear_bit)
sunt destul de usor de realizat fiind folosite operatii elementare pe biti
(exista cateva explicatii sub forma de comentarii). Unele dintre acestea vor fi
folosite la celelalte task-uri.

		Part 1.2 - One gate to rule them all

	Functiile and_gate, not_gate, or_gate, xor_gate au fost realizate
folosind schemele logice ale portilor de pe ocw.cs.pub.ro. De asemenea, 
functiile or_gate si xor_gate au fost realizate folosind si functiile and_gate
si not_gate.

	Pentru functia xor_gate puteam folosi doar nand_gate, dar am preferat
sa folosesc or_gate, and_gate si not_gate astfel:
a ^ b = !(!(a & !(a & b)) & !(b & !(a & b))) =
      = (a & !(a & b)) | (b & !(a & b)) =
      = (a & (!a | !b)) | (b & (!a | !b)) =
      = (a & !b) | (!a & b)

		Part 1.3 - Just Carry the Bit

	Functia full_adder: Se observa ca suma este a^b^c, iar carry este
((a ^ b) & c) | (a & b). Astfel suma va fi pe bitul 0 al res, iar carry
va fi pe bitul 1.
	Functia ripple_carry_adder calculeaza full_adder pentru bitul de pe
pozitia i a lui a, pentru bitul de pe pozitia i a lui b si pentru carry-ul
obtinut la full_adder-ul anterior. Pentru primul full_adder (care foloseste
bitul de pe pozitia 0 de la a si bitul de pe pozitia 0 de la b), folosesc 
carry = 0.


			Part 2 - Shut up Morty!

		Part 2.1 - The Beginning

	Functiile send_byte_message, recv_byte_message si comm_byte folosesc
instructiuni simple si functiile send_squanch si recv_squanch.

		Part 2.2 - Waiting for the Message

	Functia send_message doar codifica lungimea, o trimite, apoi trimite
mesajul "HELLOTHERE" litera cu litera
	
	Functia recv_message primeste lungimea mesajului, o decodifica si apoi
primeste fiecare caracter din mesaj si il printeaza.
	
	Functia comm_message primeste lungimea mesajului de la Rick,
o decodifica, primeste mesajul de la Rick si in functie de ultima litera, 
trimite un mesaj specific ( initial lungimea mesajului codificata si apoi
mesajul litera cu litera.

		Part 2.3 - In the Zone

	Functia send_squanch2 ia bitii din c2 si ii pune pe pozitiile pare 
si bitii din c1 si ii pune pe pozitiile impare in variabila c1_c2_encoded,
pe care o trimite. c1 = codul pentru caracterul 1, c2 = codul pentru 
caracterul 2.
	
	Functia decode_squanch2 ia bitii din c de pe pozitiile pare si ii 
pune pe primele 4 pozitii in res si bitii din c de pe pozitiile impare si 
ii pune pe ultimele 4 pozitii in res.


			Part 3 - Toss a coin to your Witcher

		Part 3.1 - Axii

	Functia find_spell cauta un grup de 5 biti activi, incepand cu
bitul de pe locul 0, apoi trece fiecare bit din memory corespunzator spell
in rezultatul pe care il returneaza functia.
	
	Functia find_key cauta primul grup de 3 biti activi, incepand cu
bitul de pe locul 63, apoi trece fiecare bit din memory corespunzator key
in rezultatul pe care il returneaza functia.
	
	Functia decrypt_spell:
	a b a^b a^b^b
	0 0  0    0
	0 1  1    0
        1 0  1    1
        1 1  0    1
	Asadar a^b^b=a. Deci, facand operatiile bit cu bit obtinem:
	    spell_encrypted = spell_plaintext ^ key <=>
	<=> spell_encrypted ^ key = spell_plaintext ^ key ^ key <=>
	<=> spell_plaintext = spell_encrypted ^ key.

		
		Part 3.2 - Sword Play

	Functia choose_sword stabileste daca inamicul ("enemy") este 
monster sau human, apoi calculeaza runele care trebuie folosite in functie
de inamic (calculeaza "value" in functie de "enemy"):
	Pentru monster:
	    Value ^ (Enemy & (1 - Enemy)) = 0 <=>
	<=> Value ^ (Enemy & (1 - Enemy)) ^ (Enemy & (1 - Enemy)) = 0 ^
^ ^ (Enemy & (1 - Enemy)) <=>
	<=> Value = (Enemy & (1 - Enemy))
	Pentru Human:
	Value + Enemy = 0 <=> Value = 0 - Enemy

		Part 3.3 - The Witcher Trials

	Functia trial_of_the_grasses:

	(antibodies_high & cocktail) ^ (antibodies_low | cocktail) = 0
         antibodies_low & antibodies_high = 0
         antibodies_low | antibodies_high = cocktail
	Voi trece relatiile de mai sus in operatii pe biti, folosind
notatiile:
	li = bitul i din antibodies_low
	hi = bitul i din antibodies_high
	ci = bitul i din cocktail
(oricare i de la 0 la 15)
	& = *
	| = +
si obtin:
	(hi * ci) ^ (li + ci) = 0 ,(1)
	li * hi = 0 ,(2)
	li + hi = ci ,(3)
	(3) => (li + hi) * li = ci * li <=> li * li + hi * li = ci * li <=>
<=> li + hi * li = ci * li <=> li * (1 + hi) = ci * li <=> li = ci * li ,(4)
	(1) si (4) => (hi * ci) ^ (ci * li + ci ) = 0 <=> 
<=> (hi * ci) ^ (ci * (li + 1)) = 0 <=> (hi * ci) ^ ci = 0 <=>
<=> hi * ci = ci => (folosind (3)) hi * (li + hi) = ci <=>
<=> hi * li + hi = ci <=> hi * (li + 1) = ci <=> hi = ci ,(5)
	(2) si (5) => li * ci = 0
	Din li * ci = 0 si (4) => li = 0 ,(6)
	Astfel, din (5) si (6) obtin ca: 
	antibodies_high = cocktail
	antibodies_low = 0

	Functia trial_of_forrest_eyes testeaza prima data daca suntem in
padurea Hindar, apoi daca ne aflam in padurea Broklin si in final daca
suntem in padurea Wolven Glade. Daca pica toate cele trei teste inseamna
ca ne aflam in padurea Caed Dhu.

	Functia trial_of_the_dreams cauta locatia candidatului si 
locatia portalului, iar apoi calculeaza distanta dintre cele doua.