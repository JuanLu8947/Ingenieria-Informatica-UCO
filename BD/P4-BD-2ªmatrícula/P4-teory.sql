--Un programa de PL/SQL esta? compuesto por bloques
� Estructura de un bloque
[DECLARE]
/*Parte declarativa
La seccio?n declarativa en donde se declaran todas las constantes
y variables que se van a utilizar en la ejecucio?n del bloque
*/
BEGIN
/*Parte de ejecuci�n
La seccio?n de ejecucio?n que incluye las instrucciones a ejecutar en
el bloque PL/SQL
*/
[exception]
/*Parte de excepciones
La seccio?n de excepciones en donde se definen los manejadores
de errores que soportara? el bloque PL/SQL. 
*/
END;

Una variable se declara de la siguiente forma:
identificador [CONST] tipo_dato [NOT NULL] [DEFAULT] [:= expresion]

Al i0 de cada:
CLEAR SCREEN;
SET SERVEROUTPUT ON;

Al final de blq BEGIN:
DBMS_OUTPUT.PUT_LINE();

--Guardar una fila en una variable
salida votantes%rowtype; 
//ahora salida tiene el formato de un votante:
 DNI, name, etc.
 
SELECT * INTO salida FROM votantes;

--Guardar un val en una var (var tipo colum)
v_name votantes.nombrecompleto%type;
SELECT nombrecompleto INTO name FROM votantes;




