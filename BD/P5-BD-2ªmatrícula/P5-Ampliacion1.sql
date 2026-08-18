/*Ej1: Obtener aquellos votantes cuyo DNI sea impar e incluir el percentil
de participación en consultas con respecto a todos los participantes en
consultas. Es decir, si es la persona que más ha participado, debe mostrarse 
percentil 100, mientras que la persona que menos haya participado, 
debe mostrar percentil 0.*/
CLEAR SCREEN;
SET SERVEROUTPUT ON;
DECLARE
    CURSOR c IS SELECT v.dni, v.nombreCompleto,
                        count(*) AS cont
    FROM votantes v, consultas c
    WHERE v.dni = c.votante AND MOD(v.dni, 2) != 0
    GROUP BY v.dni, v.nombreCompleto
    ORDER BY v.dni DESC;
    
    percentil FLOAT;
    min_c NUMBER;
    max_c NUMBER;
BEGIN
    SELECT MAX(count(c.votante)), MIN(count(c.votante))
    INTO max_c, min_c
    FROM consultas c
    GROUP BY c.votante;
        
    FOR i IN c LOOP      
        percentil := (i.cont - min_c) / (max_c - min_c) *100;
        DBMS_OUTPUT.PUT_LINE(i.dni || ' está en el percentil ' || ROUND(percentil, 3));
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('El rango considerado es [' || min_c || ', ' || max_c || ']');
END;

--ROUND & MOD se pueden usar

--Percentil = (n_consulas – min_consults) / (max_consults – min_consults) * 100
/*
n_consults = n_max_consult
min_consulta -> menor participacion
max_consulta -> mayor participacion
*/

/*Ej2: Obtener los votantes y calcular la longitud de su DNI. Si la longitud
del mismo es incorrecta (menor o mayor que 8 caracteres), maneja una
excepción personalizada que registre el DNI erróneo en una nueva tabla
llamada “DNIERRORES” con el motivo del error (solamente incluir dos
atributos, el DNI y el motivo del error). Además, se debe mostrar la
cantidad de DNIs que han fallado junto con el total de DNIs 
(crear solo un contador en este ejercicio).*/
CLEAR SCREEN;
SET SERVEROUTPUT ON;

DROP TABLE DNIERRORES;

CREATE TABLE DNIERRORES(dni number(8) primary key,
                        motivo varchar2(64));

DECLARE
    CURSOR c IS SELECT * FROM  votantes;
    n_dni NUMBER;
    cont NUMBER := 0;
BEGIN 
    SELECT count(*)
    INTO n_dni
    FROM votantes;
    FOR i IN c LOOP
        IF LENGTH(i.dni) != 8 THEN
            DBMS_OUTPUT.PUT_LINE(i.dni);
            cont:=cont+1;
            INSERT INTO DNIERRORES(dni, motivo) 
            VALUES(i.dni, 'Longitud incorrecta');
        END IF;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Ha fallado ' || cont || ' DNI del total de ' || n_dni || ' DNIs');
END;

/*Ej3: Queremos obtener un resumen de los resultados que ha obtenido cada
partido político en cada tipo de evento. El resumen se hará obteniendo la
media del resultado obtenido por cada partido político para cada tipo de
evento (locales, autonómicas, generales y europeas). El objetivo es saber
si hay relación entre el tipo de elecciones y el resultado que un partido
político obtiene para ese ámbito (tipo de evento). 
Esta media la categorizaremos de la siguiente forma:
? Resultado malo si la media está en el rango [0, 0.1).
? Resultado medio si la media está en el rango [0.1, 0.3).
? Resultado bueno si la media está en el rango [0.3, infinito).
Los resultados se mostrarán ordenados alfabéticamente por cada partido.
*/
CLEAR SCREEN;
SET SERVEROUTPUT ON;
DECLARE
    CURSOR c IS SELECT p.nombreCompleto, e.tipo, AVG(e_r.resultado) AS media
    FROM eventos e, eventos_resultados e_r, partidos p
    WHERE p.idpartido = e_r.partido 
    AND e.idevento = e_r.evento
    GROUP BY p.nombreCompleto, e.tipo
    ORDER BY p.nombrecompleto, e.tipo;
    resultado varchar(10);
BEGIN
    FOR i IN c LOOP
        IF i.media < 0.1  THEN
            resultado := 'Malo';
        ELSIF i.media >= 0.1 AND i.media < 0.3  THEN
            resultado := 'Medio';
        ELSE
            resultado := 'Bueno';
        END IF;
        DBMS_OUTPUT.PUT_LINE('El partido ' || i.nombrecompleto || ' generalmente obtuvo un resultado ' || resultado || ' en las elecciones ' || i.tipo);
    END LOOP;
END;

/*Ej4: Crear una nueva tabla, llamada “votantesAntiguos” que incluya la
siguiente informacio?n de aquellos votantes que nacieron antes de 1980:
dni, nombrecompleto, email y fechanacimiento.  Mostrar el nombre de cada
uno de los votantes insertados así como el total de votantes insertados
en dicha tabla. Dicha tabla nueva debe tener un nuevo campo "Sueldo" de
tipo numérico que incluirá el sueldo de los votantes. Dicho sueldo será 
de 1500 euros y se aplica sólo a aquellos que estén en activo. El resto
tendrá un sueldo de 0 euros
*/
CLEAR SCREEN;
SET SERVEROUTPUT ON;

DROP TABLE VOTANTESANTIGUOS;

CREATE TABLE VOTANTESANTIGUOS(dni number(8) primary key,
                            nombreCompleto varchar2(64),
                            email varchar2(32) not null,
                            fechaNacimiento date not null);

DECLARE
    CURSOR c IS SELECT * FROM votantes;
    salario NUMBER;
    cont NUMBER := 0;
BEGIN
    FOR i IN c LOOP
        IF i.fechanacimiento < '01/01/1980' THEN
            IF i.situacionlaboral = 'Activo' THEN
                salario := 1500;
            ELSE
                salario := 0;
            END IF;
            DBMS_OUTPUT.PUT_LINE(i.nombrecompleto ||' (salario de ' || salario || '€) se ha añadido a la nueva tabla');
            INSERT INTO VOTANTESANTIGUOS(dni, nombrecompleto, email, fechanacimiento)
                    VALUES(i.dni, i.nombrecompleto, i.email, i.fechanacimiento);
            cont := cont +1;
        END IF;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Se han añadido un total de ' || cont || ' personas');
END;

/*Ej5: Considerando la tabla “votantesAntiguos” creada en el ejercicio 4, 
mostrar únicamente el nombre (sin apellidos) de cada uno de los votantes
que hay en esa tabla. Para cada uno, mostrar el nombre (sin apellidos) y
el numero de letras que tiene dicho nombre. Por último, indicar el numero
de letras totales que tienen los nombres (sin apellidos) de los votantes
de esa tabla
*/
CLEAR SCREEN;
SET SERVEROUTPUT ON;
DECLARE
    CURSOR c IS SELECT * FROM VOTANTESANTIGUOS;
    total NUMBER := 0;
    cont NUMBER;
    name votantes.nombrecompleto%type;
BEGIN
    FOR i IN c LOOP
        name := SUBSTR(i.nombrecompleto,1, INSTR(i.nombrecompleto, ' ')-1);
        cont := LENGTH(name);
        DBMS_OUTPUT.PUT_LINE(name || ' tiene ' || cont || ' letras');
        total := total + cont;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('En total hay ' || total || ' letras');
END;

/*Ej6: Considerando la tabla “votantesAntiguos” creada en el ejercicio 4, 
ordenar los votantes de dicha tabla según fecha de nacimiento (ASC). 
Recorrer cada votante y calcular el numero de letras que tiene su nombre
(sin apellidos), mostrando, además, los votantes más jóvenes que él que
tengan menos letras que él.
*/
CLEAR SCREEN;
SET SERVEROUTPUT ON;
DECLARE
    CURSOR c IS SELECT * FROM votantesAntiguos vA ORDER BY vA.fechanacimiento;
    fecha DATE;
    --name votantes.nombrecompleto%type;
    cont NUMBER;
BEGIN
    FOR i IN c LOOP
        DBMS_OUTPUT.PUT_LINE(i.nombrecompleto || ' tiene más letras en el nombre que las siguientes personas más jóvenes:');
        cont := LENGTH(SUBSTR(i.nombrecompleto,1, INSTR(i.nombrecompleto, ' ')-1));
    END LOOP;
END;






