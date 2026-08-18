/*Ej1: Mediante bucles para cursores, obtener el nombre de todos los
votantes cuyo DNI acaba igual que el identificador de su localidad más 1.
*/
--1. LOOP
CLEAR SCREEN;
SET SERVEROUTPUT ON;
DECLARE
    CURSOR c 
    IS SELECT * 
    FROM votantes
    WHERE SUBSTR(dni, LENGTH(dni)) = localidad+1;
    salida votantes%rowtype;
    cont NUMBER := 0;
BEGIN
    OPEN c;
    LOOP
        FETCH c INTO salida;
        EXIT WHEN c%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE(salida.nombrecompleto);
        cont := cont +1;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Hay un total de ' || cont || ' votantes');
    CLOSE c;
END;

--2. FOR
CLEAR SCREEN;
SET SERVEROUTPUT ON;
DECLARE
    CURSOR c 
    IS SELECT * 
    FROM votantes
    WHERE SUBSTR(dni, LENGTH(dni)) = localidad+1;
    cont NUMBER := 0;
BEGIN
    FOR i IN c LOOP
        DBMS_OUTPUT.PUT_LINE(i.nombrecompleto);
        cont := cont+1;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Hay un total de ' || cont || ' votantes');
END;

--3. WHILE
CLEAR SCREEN;
SET SERVEROUTPUT ON;
DECLARE
    CURSOR c 
    IS SELECT * 
    FROM votantes
    WHERE SUBSTR(dni, LENGTH(dni)) = localidad+1;
    cont NUMBER := 0;
    salida votantes%rowtype;
BEGIN
    OPEN c;
    FETCH c INTO salida;
    WHILE c%FOUND LOOP
        DBMS_OUTPUT.PUT_LINE(salida.nombrecompleto);
        FETCH c INTO salida;
        cont := cont +1;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Hay un total de ' || cont || ' votantes');
    CLOSE c;
END;

/*Ej2: Obtener el nombre de todos los votantes así como el nombre de la
localidad en la que viven teniendo en cuenta que todos los que sean de la
provincia de Córdoba (identificador de localidad 1, 2 y 3) se han mudado
a Madrid.
*/
CLEAR SCREEN;
SET SERVEROUTPUT ON;
DECLARE
    CURSOR c 
    IS SELECT nombrecompleto, localidad 
    FROM votantes;
    cont NUMBER := 0;
    ciudad localidades.nombre%type;
BEGIN
    FOR i IN c LOOP
        IF i.localidad IN (1,2,3) THEN 
            i.localidad := 9;
        END IF;
        SELECT l.nombre
        INTO ciudad
        FROM localidades l
        WHERE i.localidad = l.idlocalidad;
        DBMS_OUTPUT.PUT_LINE(i.nombrecompleto || ' es de ' || ciudad);
        IF ciudad = 'Madrid' THEN
            cont := cont+1;
        END IF;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Hay un total de ' || cont || ' votantes de Madrid');
END;

/*Ej3: Mostrar los DNIs de los votantes en orden, indicando va antes que
otro. El último DNI (el más pequeño) se indicará que es el más pequeño
*/
CLEAR SCREEN;
SET SERVEROUTPUT ON;
DECLARE
    CURSOR c 
    IS SELECT dni
    FROM votantes
    ORDER BY dni DESC;
    dni_ votantes.dni%type;
BEGIN
    FOR i IN c LOOP
        DBMS_OUTPUT.PUT_LINE(dni_ || ' va antes que '|| i.dni);
        dni_ := i.dni;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE(dni_ || ' es el menor');
END;

/*Ej4: Obtener el DNI del votante y el numero de veces que dicho votante
ha participado en una consulta, mostrando el resultado de manera
descendente en cuanto a número de participaciones. Sólo se mostrarán 
aquellos votantes cuya participación ha sido mayor que la media de
participaciones de todos los votantes. 
*/
CLEAR SCREEN;
SET SERVEROUTPUT ON;
DECLARE
    CURSOR c 
    IS SELECT votante, count(votante)
    FROM consultas
    HAVING count(*) > (SELECT AVG(count(votante))
                        FROM consultas
                        GROUP BY votante)
    GROUP BY votante
    ORDER BY 2 DESC;
    cont NUMBER := 0;
BEGIN
    FOR i IN c LOOP
        SELECT count(*) 
        INTO cont 
        FROM consultas
        WHERE i.votante = votante;
        DBMS_OUTPUT.PUT_LINE(i.votante || ' ha participado ' || cont || ' veces');
    END LOOP;
END;



