repetir
    escribir('\n Introducza un número (0 para salir) \n\t --> ');
    leer(dato);

    selector (dato)
        caso 0: escribir('\n\t Fin del ejemplo casos\n');
        caso 1: escribir('\n primer caso --> ');          escribir(dato);
        caso 2: escribir('\n segundo caso: ');            escribir(2 * dato);
        caso 3: escribir('\ntercer caso: ');              escribir(3 * dato);
        default  escribir('\n\t caso por defecto: ');     escribir(- dato);
     fin_selector; # Fin de la sentencia "switch"

 hasta (dato = 0); # Fin del bucle "repeat"
