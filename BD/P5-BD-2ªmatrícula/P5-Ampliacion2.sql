/*Ej1: Muestre el nombre de los presidentes de partidos que cumpla con la
condici�n de que tanto su nombre como sus dos apellidos terminan en �o�. 
En este ejercicio no podr� hacer uso del comando WHERE.
*/
CLEAR SCREEN;
SET SERVEROUTPUT ON;

DECLARE
    CURSOR c IS SELECT * FROM partidos;
    apellido2 partidos.presidente%type;
    apellido1 partidos.presidente%type;
    name partidos.presidente%type;
    apellidos partidos.presidente%type;
BEGIN
     FOR i IN c LOOP   
        apellido2 := SUBSTR(i.presidente, INSTR(i.presidente, ' ', 1, 2)+1);
        apellidos := SUBSTR(i.presidente, INSTR(i.presidente, ' ')+1);
        apellido1 := SUBSTR(apellidos, 1, INSTR(apellidos, ' ')-1);
        name := SUBSTR(i.presidente, 1, INSTR(i.presidente, ' ')-1);
        IF name LIKE '%o' AND apellido1 LIKE '%o' AND apellido2 LIKE '%o' THEN
            DBMS_OUTPUT.PUT_LINE(i.presidente);
            --DBMS_OUTPUT.PUT_LINE(name || apellido1 || apellido2);
        END IF;
    END LOOP;
END;

/*Ej2: Mostrar el cronograma en la creaci�n de todos los partidos 
pol�ticos que tenemos en la tabla partidos. Mostrar la fecha de creaci�n 
de cada partido y, hasta la creaci�n del siguiente partido, mostrar el 
tiempo que ha pasado entre medias, indicando los a�os, meses y d�as. 
*/ --duda
CLEAR SCREEN;
SET SERVEROUTPUT ON;

DECLARE
    CURSOR c 
    IS SELECT * 
    FROM partidos
    ORDER BY fechacreacion;
    
    fecha_ant DATE := NULL;
    years INT := 0;
    meses INT := 0;
    dias INT := 0;
    diferencia INT;
BEGIN
    FOR i IN c LOOP
        /*SI quisieramos el tiempo de creacion de los partidos:
        years := TO_CHAR(SYSDATE, 'YYYY') - TO_CHAR(i.fechacreacion, 'YYYY');
        meses := TO_CHAR(SYSDATE, 'MM') - TO_CHAR(i.fechacreacion, 'MM');
        dias := TO_CHAR(SYSDATE, 'DD') - TO_CHAR(i.fechacreacion, 'DD');*/
        --Pero, nos pide diferencia de tiempos entre partidos
        IF fecha_ant IS NOT NULL THEN
            diferencia := i.fechacreacion - fecha_ant;
            
            years := FLOOR(diferencia/365.25); --.25
            
            meses := FLOOR((diferencia - years*365.25)/30.4375); --.44
            
            dias := ROUND(diferencia - years*365.25 - meses*30.4375);
            
            DBMS_OUTPUT.PUT_LINE('(Pasan ' || years || ' a�os, ' || meses || ' meses y ' || dias || ' dias)');
        END IF;
        DBMS_OUTPUT.PUT_LINE('El dia ' || TO_CHAR(i.fechacreacion, 'DD/MM/YYYY') || ' se creo el partido ' || i.nombrecompleto);
        fecha_ant := i.fechacreacion;
    END LOOP;
END;

--Se puede usar TRUNC ? -< si
--Se puede usar MONTH_BETWEEN? -< evitar
--Se puede usar EXTRACT(YEAR FROM ? -< no
--Se puede usar ADD_MONTHS ? -< no

/*Ej3: Encuentre la suma total de los resultados de cada partido 
pol�tico en todos los resultados de eventos,
*/
CLEAR SCREEN;
SET SERVEROUTPUT ON;

DECLARE 
    CURSOR p IS SELECT idpartido, nombrecompleto FROM partidos;
    CURSOR e IS SELECT partido, resultado FROM eventos_resultados;
    partido p%rowtype;
    evento e%rowtype;
    total NUMBER := 0;
BEGIN
    FOR i IN p LOOP
        total := 0;
        FOR j IN e LOOP
            IF i.idpartido = j.partido THEN
                total := total + j.resultado;
            END IF;
        END LOOP;
        DBMS_OUTPUT.PUT_LINE(i.nombrecompleto || ' -> ' || total);
    END LOOP;
END;

/*Ej4: Insertar un nuevo partido pol�tico en la tabla partidos. El 
nuevo partido tendr� el identificador 6. Todos los partidos, incluido el
6, se repartir�n el presupuesto en este a�o. Actualiza el presupuesto de
los partidos de manera que el presupuesto nuevo sea igual para todos 
suponiendo el presupuesto global de todos los partidos existentes antes
de la inserci�n del nuevo partido con identificador 6.
*/
CLEAR SCREEN;
SET SERVEROUTPUT ON;

DELETE FROM partidos WHERE idpartido = 6;

DECLARE
    CURSOR c IS SELECT * FROM partidos;
    total INT := 0;
    n INT := 0;
BEGIN
    INSERT INTO partidos(idPartido, nombreCompleto, siglas, direccion,
                        ciudad, presidente, fechaCreacion, presupuesto)
        VALUES(6, 'Adelante Andalucia', 'AA' , 'C/', 'Sevilla', 'Antonio Moreno', '03/12/95', 0);
    FOR i IN c LOOP
        total := total + i.presupuesto;
        n := n + 1;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Se ha a�adido el partido Adelante Andaluc�a con un presupuesto de ' || ROUND(total/n, 2));
    DBMS_OUTPUT.PUT_LINE('Los partidos quedan as�: ');
    FOR i IN c LOOP
        DBMS_OUTPUT.PUT_LINE('  - ' || i.nombrecompleto || ' -> ' || ROUND(total/n,0));
    END LOOP;
END;

/*Ej5: Vamos a estudiar la actividad de los votantes seg�n su d�cada de
nacimiento. En base a la participaci�n de cada votante, le asignaremos 
una categor�a (�alta� si han participado en m�s de 4 consultas, �media�
si han participado 2 o 3 veces y �baja� no participaron o lo hicieron 
solo una vez.
*/
CLEAR SCREEN;
SET SERVEROUTPUT ON;

DECLARE
    CURSOR c 
    IS SELECT v.nombrecompleto, v.fechanacimiento,
            count(*) as cont
    FROM votantes v, consultas c
    WHERE c.votante = v.dni
    GROUP BY v.nombrecompleto, v.fechanacimiento
    ORDER BY v.fechanacimiento;
    part varchar2(6);
    --decada varchar2(5);
    --decada_actual varchar2(5);
    decada DATE;
    decada_actual DATE;
BEGIN
    FOR i IN c LOOP
        IF i.cont > 4 THEN
            part := 'alta';
        ELSIF i.cont >= 2 THEN
            part := 'media';
        ELSE
            part := 'baja';
        END IF;
        decada := SUBSTR(TO_CHAR(i.fechanacimiento, 'YYYY'),1, 3) || '0';
        
        IF decada_actual IS NULL OR decada != decada_actual THEN
            DBMS_OUTPUT.PUT_LINE('D�cada del ' || decada);
            decada_actual := decada;
        END IF;
        DBMS_OUTPUT.PUT_LINE('  - ' || i.nombrecompleto || ' tuvo una participaci�n ' || part);
    END LOOP;
END;

/*Ej6: Marcar en una nueva columna en la tabla votantes 
�BorrarPocaParticipacion� a aquellos votantes que no hayan participado
en un m�nimo de 3 consultas.
*/
CLEAR SCREEN;
SET SERVEROUTPUT ON;

ALTER TABLE votantes
DROP COLUMN BorrarPocaParticipacion;

-- Agregar la columna si no existe
ALTER TABLE votantes 
ADD BorrarPocaParticipacion NUMBER(1) DEFAULT 0;

DECLARE
    CURSOR c 
    IS SELECT count(c.votante) as cont, v.dni 
    FROM votantes v, consultas c
    WHERE v.dni = c.votante
    GROUP BY v.dni;
    tot INT := 0;
BEGIN
    FOR i IN c LOOP
        IF i.cont < 3 THEN
            tot := tot +1;
            UPDATE votantes
            SET BorrarPocaParticipacion = 1
            WHERE i.dni = dni;
        END IF;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Se han incluido un total de ' || tot || ' registros a true (1) en la columna BorrarPocaParticipacion');
END;

SELECT nombrecompleto, borrarpocaparticipacion 
FROM votantes;

--UPDATE TABLE? -< si
--ALTER TABLE? 

/*Ej7: Crear una nueva tabla que almacene las comunidades que ya hay 
registradas en la tabla provincias. Esta nueva tabla, llamada 
�Comunidades�, debe tener su id de comunidad (n�mero, primary key), el 
nombre de la comunidad (cadena de texto), n�mero de habitantes 
(sumatorio de todas las provincias de la comunidad) y la tasa de 
habitabilidad (porcentual con respecto al total de comunidades). Una 
vez que se cree esta nueva tabla �Comunidades�, el contenido de la 
misma debe mostrarse.
*/
CLEAR SCREEN;
SET SERVEROUTPUT ON; 

DROP TABLE comunidades;

CREATE TABLE comunidades(idComunidad number(3) primary key,
                        nombreComunidad varchar2(64) not null,
                        numeroHabitantesComunidad number(32) not null,
                        tasaHabitabilidad float(3) not null);

/*DROP TABLE provincias //CASCADE CONSTRAINTS

create table provincias
	(idProvincia number(3) primary key,
	nombre varchar2(64) not null,
	numeroHabitantes number(38) not null,
	comunidad varchar2(64) not null,
    constraint fk_comunidad foreign key (comunidad) references comunidades(nombreComunidad));

ALTER TABLE provincias
ADD CONSTRAINT fk_comunidad 
FOREIGN KEY (comunidad) 
REFERENCES comunidades(nombreComunidad);*/
--Conclusi�n no se puede hacer una foreing key

DECLARE
    CURSOR c 
    IS SELECT p.comunidad, SUM(p.numerohabitantes) as n_hab
    FROM provincias p
    GROUP BY p.comunidad;
    id INT := 1;
    total FLOAT := 0.0;
    tasa FLOAT;
BEGIN
    FOR i IN c LOOP
        total := total + i.n_hab;
    END LOOP;
    FOR i IN c LOOP
        tasa := ROUND((i.n_hab / total)*100,2);
        INSERT INTO comunidades(idcomunidad, nombreComunidad, 
                                numerohabitantescomunidad, 
                                tasaHabitabilidad)
            VALUES(id , i.comunidad, i.n_hab, tasa);
        DBMS_OUTPUT.PUT_LINE('Se ha a�adido la comunidad de ' || i.comunidad || '(ID ' || id || ') con un total de ' || i.n_hab || ' habitantes (tasa del ' || tasa || '%)');
        id := id+1;
    END LOOP;
    /*
    Posteriormente, vamos a a�adir una comunidad (ID 6) que no est� 
    a�adida ya previamente, con la cantidad de habitantes que deseemos. 
    Por ejemplo, el Principado de Asturias, con un total de 1012837
    habitantes. 
    */
    total := total + 1012837;
    tasa := ROUND((1012837/total)*100,2);
    INSERT INTO comunidades(idcomunidad, nombreComunidad, 
                                numerohabitantescomunidad, 
                                tasaHabitabilidad)
            VALUES(6, 'Principado de Asturias', 1012837, tasa);
    DBMS_OUTPUT.PUT_LINE('Nueva comunidad: Principado de Asturias (ID 6) con un total de 1012837 habitantes (tasa del ' || tasa || '%)');
    id := 0;
    FOR i IN c LOOP
        id := id+1;
        tasa := ROUND((i.n_hab / total)*100,2);
        DBMS_OUTPUT.PUT_LINE('Se ha actualizado la tasa de la comunidad de ' || i.comunidad || '(ID ' || id || ') con un total de ' || i.n_hab || ' habitantes (tasa del ' || tasa || '%)');
    END LOOP;
END;

SELECT SUM(numerohabitantes), comunidad 
FROM provincias
GROUP BY comunidad;



