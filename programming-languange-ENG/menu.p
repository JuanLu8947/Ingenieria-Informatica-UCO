(*
  Asignatura:    Procesadores de Lenguajes

  Titulación:    Ingeniería Informática
  Especialidad:  Computación
  Curso:         Tercero
  Cuatrimestre:  Segundo

  Departamento:  Informática y Análisis Numérico
  Centro:        Escuela Politécnica Superior de Córdoba
  Universidad de Córdoba
 
  Curso académico: 2024 - 2025

  Fichero de ejemplo para interpreter.exe
*)

# Bienvenida

clearscreen;
place(10,10);
print('Introduce tu nombre --> ');
read_string(nombre);

clearscreen;
place(10,10);
print(' Bienvenido/a << ');
print(nombre);
print(' >> a \'interpreter.exe\'.');

place(40,10);
print('Pulsa una tecla para continuar');
read_string( pausa);

repeat 

 # Opciones disponibles

 clearscreen;
 place(10,10);
 print(' Factorial de un número --> 1 ');

 place(11,10);
 print(' Máximo común divisor ----> 2 ');

 place(12,10);
 print(' Finalizar ---------------> 0 ');

 place(15,10);
 print(' Elige una opcion ');

 read(opcion);

 clearscreen;

 # Fin del programa
 if (opcion = 0)       		
    then  
        place(10,10);
        print(nombre);
        print(': gracias por usar el intérprete ');
 else 					
	# Factorial de un número
	if (opcion = 1)
   	    then
			place(10,10);
			print(' Factorial de un numero  ');

			place(11,10);
			print(' Introduce un numero entero ');
			read(N);

			factorial := 1;

       		for i from 2 to N step 1 do
	            factorial := factorial * i;
	        end_for;

        	# Resultado
			place(15,10);
			print(' El factorial de ');
			print(N);
			print(' es ');
			print(factorial);

	else 
	   	# Máximo común divisor
		if (opcion = 2)
			then
				place(10,10);
				print(' Máximo común divisor de dos números ');

				place(11,10);
                print(' Algoritmo de Euclides ');

                place(12,10);
                print(' Escribe el primer número ');
                read(a);

                place(13,10);
                print(' Escribe el segundo número ');
                read(b);

                # Se ordenan los números
				if (a < b)
					then 
						auxiliar := a;
						a := b;
						b := auxiliar;
				end_if;

				# Se guardan los valores originales
					A1 := a;
					B1 := b;

				# Se aplica el método de Euclides	
				resto  := a mod b;

				while (resto <> 0) do
					a :=  b;
					b := resto;
					resto := a mod b;
				end_while;
         
				# Se muestra el resultado
				place(15,10);
				print(' Máximo común divisor de ');
				print(A1);
				print(' y ');
				print(B1);
				print(' es ---> ');
				print(b);

		# Resto de opciones
 		else  
			place(15,10);
		    print(' Opcion incorrecta ');
		end_if;   
  	end_if;                 
  end_if;                          

 place(40,10); 
 print('\n Pulse una tecla para continuar --> ');
 read_string(pausa);
 
until (opcion = 0);             

# Despedida final
clearscreen;
place(10,10);
print('El programa ha concluido');
