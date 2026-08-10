#  Programa que convierte un número entero a código binario.

escribir('Programa que convierte un número entero a código binario \n');
escribir('Introduce un número entero: \n');
leer(n);

r := ' ';

mientras (n <> 0) hacer
	si ((n mod 2) = 0) entonces
		#concatenación con 0
		r := '0' || r;  
	si_no
		#concatenación con 1
		r := '1' || r;
	fin_si

	# Cociente de la división entera
       n := n // 2;
fin_mientras;

escribir('Número en código binario: ' || r || '\n');
