/*Ej1: Muestre por pantalla el cla?sico “Hola mundo”,
pero adema?s muestre la fecha actual. 
*/
CLEAR SCREEN;
SET SERVEROUTPUT ON;
--DECLARE
BEGIN
    DBMS_OUTPUT.PUT_LINE('Hola mundo, hoy es el día ' || SYSDATE);
    --DataBaseMeSSage_
END;

/*Ej2: Mostrar el nombre completo y el correo electrónico del votante 
con DNI 30983712
*/
CLEAR SCREEN;
SET SERVEROUTPUT ON;
DECLARE
    v_name votantes.nombrecompleto%type;
    v_email votantes.email%type;
BEGIN
    SELECT nombrecompleto, email 
    INTO v_name, v_email 
    FROM votantes
    WHERE dni LIKE '30983712';
    DBMS_OUTPUT.PUT_LINE(v_name || ' con correo: ' || v_email);
END;

/*Ej3: Mostrar sólo el nombre (primer nombre, sin apellidos) y
el correo electrónico del votante con DNI 30983712
*/
CLEAR SCREEN;
SET SERVEROUTPUT ON;
DECLARE
    v_name votantes.nombrecompleto%type;
    v_email votantes.email%type;
BEGIN
    SELECT SUBSTR(nombrecompleto, 1, INSTR(nombrecompleto, ' ')-1), email 
    INTO v_name, v_email 
    FROM votantes
    WHERE dni LIKE '30983712';
    DBMS_OUTPUT.PUT_LINE(v_name || ' con correo: ' || v_email);
END;

/*Ej4: El votante con DNI 30983712 desea que lo llamen Pepe en lugar de 
Jose. Sin embargo, este cambio no puede realizarse oficialmente en la
base de datos puesto que no es su nombre real. Crear un script en PL/SQL
para que se muestre el nombre completo de dicho votante pero apareciendo
Pepe en lugar de Jose.
*/
CLEAR SCREEN;
SET SERVEROUTPUT ON;
DECLARE
    v_apellidos votantes.nombrecompleto%type;
BEGIN
    SELECT SUBSTR(nombrecompleto, INSTR(nombrecompleto, ' ')+1, LENGTH(nombrecompleto)) 
    INTO v_apellidos 
    FROM votantes
    WHERE dni LIKE '30983712';
    DBMS_OUTPUT.PUT_LINE('Pepe ' || v_apellidos);
END;

--Ej5: Muestre el nombre completo y el DNI del votante ma?s longevo
CLEAR SCREEN;
SET SERVEROUTPUT ON;
DECLARE
    v_name votantes.nombrecompleto%type;
    v_dni votantes.dni%type;
BEGIN
    SELECT nombrecompleto, dni
    INTO v_name, v_dni
    FROM votantes
    WHERE fechanacimiento = (SELECT MIN(fechanacimiento) 
                            FROM votantes);
    DBMS_OUTPUT.PUT_LINE('El señor ' || v_name || ' con dni ' || v_dni || ' es el votante más longevo');
END;

/*Ej6: Se ha decidido que a los votantes más jóvenes y más viejos se les
va a hacer una cuenta de la Universidad de Córdoba, guardando el nombre
de usuario que tenían ya en sus cuentas originales. Se necesita mostrar
por pantalla la información, cómo quedaría, sin modificar la base de datos. 
*/
CLEAR SCREEN;
SET SERVEROUTPUT ON;
DECLARE
    v_name votantes.nombrecompleto%type;
    v_email votantes.email%type;
BEGIN
    SELECT nombrecompleto, email
    INTO v_name, v_email
    FROM votantes
    WHERE fechanacimiento = (SELECT MIN(fechanacimiento)
                            FROM votantes);
    DBMS_OUTPUT.PUT_LINE(v_name || ' -- Email: ' || v_emaiL);
    SELECT nombrecompleto, email
    INTO v_name, v_email
    FROM votantes
    WHERE fechanacimiento = (SELECT MAX(fechanacimiento) 
                            FROM votantes);
    DBMS_OUTPUT.PUT_LINE(v_name || ' -- Email: ' || v_emaiL);
END;

/*Ej7: Los dos votantes más jóvenes se han enamorado y han tenido un
bebé, que se llama Juan. Mostrar el nombre y apellidos del bebé
considerando que el votante más joven pondrá el segundo apellido y el
siguiente más joven pondrá el primer apellido
*/
CLEAR SCREEN;
SET SERVEROUTPUT ON;
DECLARE
    v_apellido2 votantes.nombrecompleto%type;
    v_apellido1 votantes.nombrecompleto%type;
BEGIN
    SELECT SUBSTR(nombrecompleto, 
                INSTR(nombrecompleto, ' ')+1, 
                LENGTH(nombrecompleto))
    INTO v_apellido2
    FROM votantes
    WHERE fechanacimiento = (SELECT MAX(fechanacimiento) 
                            FROM votantes);
    --
    SELECT SUBSTR(v_apellido2, 1, INSTR(v_apellido2, ' ')-1)
    INTO v_apellido2
    FROM votantes
    WHERE fechanacimiento = (SELECT MAX(fechanacimiento) 
                            FROM votantes);
    --
    SELECT SUBSTR(nombrecompleto, 
                INSTR(nombrecompleto, ' ')+1, 
                LENGTH(nombrecompleto))
    INTO v_apellido1
    FROM votantes
    WHERE fechanacimiento = (SELECT MAX(v.fechanacimiento) 
                            FROM votantes v
                            WHERE v.fechanacimiento != (SELECT MAX(v1.fechanacimiento)
                                                        FROM votantes v1));
    --
    SELECT SUBSTR(v_apellido1, 1, INSTR(v_apellido1, ' ')-1)
    INTO v_apellido1
    FROM votantes
    WHERE fechanacimiento = (SELECT MAX(v.fechanacimiento) 
                            FROM votantes v
                            WHERE v.fechanacimiento != (SELECT MAX(v1.fechanacimiento)
                                                        FROM votantes v1));
    DBMS_OUTPUT.PUT_LINE('El hijo se llama Juan ' || v_apellido1 || ' ' || v_apellido2);
END;
/*
INSTR(cadena, subcadena [, posición_inicio [, ocurrencia ] ])
*/

/*Ej8: Sin utilizar ninguna subconsulta, crea un procedimiento PL/SQL
que sume la cantidad de habitantes que tienen las dos localidades con
menor identificador. A continuación, obtenga cuantas localidades existen 
con un numero de habitantes mayor que la suma de las dos localidades anteriores.
*/
CLEAR SCREEN;
SET SERVEROUTPUT ON;
DECLARE
    n_hab_1 localidades.numerohabitantes%type;
    n_hab_2 localidades.numerohabitantes%type;
    n_hab localidades.numerohabitantes%type;
    minID_1 localidades.idlocalidad%type;
    minID_2 localidades.idlocalidad%type;
    cont NUMBER := 0;
BEGIN
    SELECT MIN(idlocalidad)
    INTO minID_1
    FROM localidades;
    --
    SELECT numerohabitantes
    INTO n_hab_1
    FROM localidades
    WHERE idlocalidad = minID_1;
    --
    DBMS_OUTPUT.PUT_LINE('La localidad ' || minID_1 || ' tiene ' || n_hab_1 || ' habitantes');
    --
    SELECT MIN(idlocalidad)
    INTO minID_2
    FROM localidades
    WHERE idlocalidad != minID_1;
    --
    SELECT numerohabitantes
    INTO n_hab_2
    FROM localidades
    WHERE idlocalidad = minID_2;
    --
    DBMS_OUTPUT.PUT_LINE('La localidad ' || minID_2 || ' tiene ' || n_hab_2 || ' habitantes');
    --
    n_hab := n_hab_1 + n_hab_2;
    --
    SELECT count(*)
    INTO cont
    FROM localidades
    WHERE numerohabitantes > n_hab;
    --
    DBMS_OUTPUT.PUT_LINE('Hay ' || cont || ' ciudades con más habitantes que ' || n_hab || ' habitantes, que es la suma de habitantes de las dos localidades con IDs más pequeños');
END;


