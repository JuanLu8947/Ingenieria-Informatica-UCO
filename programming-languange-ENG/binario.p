#  Programa que convierte un número entero a código binario.

print('Programa que convierte un número entero a código binario \n');
print('Introduce un número entero: \n');
read(n);

r := ' ';

while (n <> 0) do
	if ((n mod 2) = 0) then
		#concatenación con 0
		r := '0' || r;  
	else
		#concatenación con 1
		r := '1' || r;
	end_if

	# Cociente de la división entera
       n := n // 2;
end_while

print('Número en código binario: ' || r || '\n');
