/*Ej1 - Con el objetivo de mejorar la integridad de la base de datos,
en concreto con el teléfono que se añade, vamos a modificar la tabla
votantes incluyendo una restricción para limitar que el atributo del 
teléfono solo pueda tomar valores cuyo primer dígito sea el 6 o el 7. 
Para comprobar su validez, debemos añadir un votante a la BD. */
ALTER TABLE votantes
ADD CONSTRAINT ck_tlf CHECK (telefono LIKE '6%' OR telefono LIKE '7%');

INSERT INTO votantes (dni, nombrecompleto, estudiosSuperiores,
                    situacionLaboral, email, localidad, fechanacimiento,
                    telefono)
    VALUES(26827577, 'Juan', 'Basicos',
            'Estudiante', 'jl@gmail.com', 1, '26/04/2004',
            116053694);

/*Ej2 - Siguiendo el ejercicio anterior, ahora debemos comprobar que el
campo de correo electrónico de dicha tabla sea apto, para ello debe
contar con un identificador, seguido del símbolo “@” que a su vez 
continúe con un dominio cualquiera y un “.” seguido de una extensión 
cualquiera. Para comprobar su validez, debemos añadir un votante a la
base de datos*/
CLEAR SCREEN;
ALTER TABLE votantes
ADD CONSTRAINT ck_correo CHECK (email LIKE '%_@%_._%');

INSERT INTO votantes (dni, nombrecompleto, estudiosSuperiores,
                    situacionLaboral, email, localidad, fechanacimiento,
                    telefono)
    VALUES(26827577, 'Juan', 'Basicos',
            'Estudiante', '@gmail.com', 1, '26/04/2004',
            616053694); --Habría que probar todos los caso pero vaya

/*Ej3 - Implemente un trigger que valide el número de habitantes de las
localidades. Si se intenta modificar dicho valor, el número de 
habitantes deberá estar entre 1 y 4.000.000. En caso de ocurrir lo
anterior deberá modificar el valor que se intentó insertar, y en su 
lugar deberá mantener el valor previo. Hacer dos comprobaciones, 
actualizando el valor de la localidad cuyo identificador sea 2 a 
150.000 habitantes y luego modificarlo para que sea 0. Finalmente, la
localidad 2 deberá tener 150.000 habitantes y el trigger haberse 
disparado en la segunda actualización. */
/*
trigger's struct
CREATE {OR REPLACE} TRIGGER nombre_trigger
        [BEFORE | AFTER] --cuando queremos que se ejecue
        [INSERT | DELETE | UPDATE {OF columnas}] [ OR [INSERT| DELETE|UPDATE {OF columnas}]...]
        ON table_name
        [FOR EACH ROW [WHEN condicion disparo]] --registros sobre los que se aplica, puede sesgarse a una cond

*/
CLEAR SCREEN;
SET SERVEROUTPUT ON;

CREATE OR REPLACE TRIGGER trg1
BEFORE UPDATE OF numeroHabitantes
ON localidades
FOR EACH ROW WHEN (new.numeroHabitantes < 1 OR 
                    new.numeroHabitantes > 4000000)
BEGIN
    IF :NEW.numeroHabitantes < 1 OR :NEW.numeroHabitantes > 4000000 THEN
        :NEW.numeroHabitantes := :OLD.numeroHabitantes;
        DBMS_OUTPUT.PUT_LINE('Valor inválido detectado. Se mantiene el valor anterior: ' || :OLD.numeroHabitantes);
    END IF;
END;

UPDATE localidades 
SET numerohabitantes = 0 
WHERE idlocalidad = 2;

SELECT idlocalidad, numerohabitantes
FROM localidades
WHERE idlocalidad = 2;


/*Ej4 - Desarrollar un bloque de PL/SQL que, sin utilizar triggers, 
compruebe si al insertar una nueva localidad se supera el número máximo
de habitantes permitido (valor existente en la tabla de provincias) para
la provincia a la que pertenece. En caso de que se exceda dicho límite,
deberá lanzarse una excepción que impida la inserción de la nueva
localidad. */
CLEAR SCREEN;
SET SERVEROUTPUT ON;

DECLARE
    prov provincias.idprovincia%type := 1;
    total provincias.numeroHabitantes%type;
    suma INT := 0;
    n NUMBER := 26042004;
    
    CURSOR c 
    IS SELECT *
    FROM localidades
    WHERE prov = provincia;
    
    except EXCEPTION;
BEGIN
    SELECT numeroHabitantes
    INTO total
    FROM provincias
    WHERE idProvincia = prov;
    --
    FOR i IN c LOOP
        IF i.provincia = prov THEN
            suma := suma + i.numerohabitantes;
        END IF;
    END LOOP;
    --
    IF (suma + n) > total THEN
        RAISE except; --salta exception
    END IF;
    --
    INSERT INTO localidades (idlocalidad, nombre, numerohabitantes,
                                provincia)
        VALUES(89, 'Cabra', n, prov);
    --
    EXCEPTION
        WHEN except THEN
            DBMS_OUTPUT.PUT_LINE('? ERROR: SE SUPERA EL LÍMITE DE HABITANTES');
            RAISE_APPLICATION_ERROR(-20001, 'No se puede insertar la localidad: supera el límite de habitantes de la provincia');
    --
END;

/*Ej5 - Como mejora sobre el ejercicio anterior, se pide desarrollar un
trigger en PL/SQL que actualice automáticamente el número de habitantes
de una provincia cada vez que se inserte, modifique o elimine una 
localidad asociada a dicha provincia */
CREATE OR REPLACE TRIGGER trg_ej5
AFTER INSERT OR DELETE OR UPDATE OF numeroHabitantes
ON localidades
FOR EACH ROW
BEGIN
    --1º hay que comprobar que op se está realizando para llevar 
    -- a cabo cada acción
    IF INSERTING THEN
        UPDATE provincias
        SET numeroHabitantes = numeroHabitantes + :NEW.numeroHabitantes
        WHERE idProvincia = :NEW.provincia;
    ELSIF DELETING THEN
        UPDATE provincias
        SET numeroHabitantes = numeroHabitantes - :OLD.numeroHabitantes
        WHERE idProvincia = :OLD.provincia;
    ELSIF UPDATING THEN
        UPDATE provincias
        SET numeroHabitantes = numeroHabitantes - :OLD.numeroHabitantes + :NEW.numeroHabitantes
        WHERE idProvincia = :NEW.provincia;
    END IF;
END;

/*Sacamos el número de habitantes por provincia antes de añadir 100.000
habitantes a la provincia con identificador 5:*/
SELECT idprovincia, numerohabitantes FROM provincias;

--  añadimos con la instrucción insert:
INSERT INTO localidades(idlocalidad, nombre, numerohabitantes,
                        provincia)
    VALUES(47, 'Lucena', 200, 1);
    
--Por último, volvemos a mostrar los habitantes de las provincias:
SELECT idprovincia, numerohabitantes FROM provincias;

-- Posteriormente lo eliminamos con la instrucción delete:
DELETE FROM localidades WHERE idlocalidad = 47;

-- Y el resultado debe ser el mismo que en el comienzo del ejercicio
SELECT idprovincia, numerohabitantes FROM provincias;

 -- los ejs de pl no van a ser supercomplejos ó cosas excatas
 -- aunque no van a ser fáciles

UPDATE localidades
SET numerohabitantes = 100
WHERE idlocalidad = 47;





