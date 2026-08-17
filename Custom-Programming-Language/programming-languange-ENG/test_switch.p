repeat
    print('\n Introducza un número (0 para salir) \n\t --> ');
    read(dato);

    switch (dato)
        case 0: print('\n\t Fin del ejemplo casos\n');
        case 1: print('\n primer caso --> ');          print(dato);
        case 2: print('\n segundo caso: ');            print(2 * dato);
        case 3: print('\ntercer caso: ');              print(3 * dato);
        default  print('\n\t caso por defecto: ');     print(- dato);
     end_switch; # Fin de la sentencia "switch"

 until (dato = 0); # Fin del bucle "repeat"
