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

borrar_pantalla;
lugar(10,10);
escribir('Introduce tu nombre --> ');
leer_cadena(nombre);

borrar_pantalla;
lugar(10,10);
escribir(' Bienvenido/a << ');
escribir(nombre);
escribir(' >> a \'interpreter.exe\'.');

lugar(40,10);
escribir('Pulsa una tecla para continuar');
leer_cadena( pausa);

repetir 

 # Opciones disponibles

 borrar_pantalla;
 lugar(10,10);
 escribir(' Factorial de un número --> 1 ');

 lugar(11,10);
 escribir(' Máximo común divisor ----> 2 ');

 lugar(12,10);
 escribir(' Finalizar ---------------> 0 ');

 lugar(15,10);
 escribir(' Elige una opcion ');

 leer(opcion);

 borrar_pantalla;

 # Fin del programa
 si (opcion = 0)       		
    entonces  
        lugar(10,10);
        escribir(nombre);
        escribir(': gracias por usar el intérprete ');
 si_no 					
	# Factorial de un número
	si (opcion = 1)
   	    entonces
			lugar(10,10);
			escribir(' Factorial de un numero  ');

			lugar(11,10);
			escribir(' Introduce un numero entero ');
			leer(N);

			factorial := 1;

       		for i desde 2 hacia N paso 1 hacer
	            factorial := factorial * i;
	        fin_para;

        	# Resultado
			lugar(15,10);
			escribir(' El factorial de ');
			escribir(N);
			escribir(' es ');
			escribir(factorial);

	si_no 
	   	# Máximo común divisor
		si (opcion = 2)
			entonces
				lugar(10,10);
				escribir(' Máximo común divisor de dos números ');

				lugar(11,10);
                escribir(' Algoritmo de Euclides ');

                lugar(12,10);
                escribir(' Escribe el primer número ');
                leer(a);

                lugar(13,10);
                escribir(' Escribe el segundo número ');
                leer(b);

                # Se ordenan los números
				si (a < b)
					entonces 
						auxiliar := a;
						a := b;
						b := auxiliar;
				fin_si;

				# Se guardan los valores originales
					A1 := a;
					B1 := b;

				# Se aplica el método de Euclides	
				resto  := a mod b;

				mientras (resto <> 0) hacer
					a :=  b;
					b := resto;
					resto := a mod b;
				fin_mientras;
         
				# Se muestra el resultado
				lugar(15,10);
				escribir(' Máximo común divisor de ');
				escribir(A1);
				escribir(' y ');
				escribir(B1);
				escribir(' es ---> ');
				escribir(b);

		# Resto de opciones
 		si_no  
			lugar(15,10);
		    escribir(' Opcion incorrecta ');
		fin_si;   
  	fin_si;                 
  fin_si;                          

 lugar(40,10); 
 escribir('\n Pulse una tecla para continuar --> ');
 leer_cadena(pausa);
 
hasta (opcion = 0);             

# Despedida final
borrar_pantalla;
lugar(10,10);
escribir('El programa ha concluido');
