--Ej1:
SELECT * FROM votantes;
SELECT * FROM provincias;
SELECT * FROM partidos;
SELECT * FROM localidades;
SELECT * FROM eventos resultados;
SELECT * FROM eventos;
SELECT * FROM consultas datos;
SELECT * FROM consultas;

--Ej2: Comprobar que todas las tablas han sido creadas correctamente
SELECT  table_name FROM user_tables;

--Ej3: Obtener descripciones de las diferentes tablas creadas mediante el script. 
DESCRIBE votantes;
DESCRIBE provincias;
DESCRIBE partidos;
DESCRIBE localidades;
DESCRIBE eventos resultados;
DESCRIBE eventos;
DESCRIBE consultas datos;
DESCRIBE consultas;

--Ej4: Realizar el borrado de la tabla votantes. Analizar por qu� el comando da un error y hacer lo posible para conseguir borrar la tabla socio. Una vez conseguido, borrar el resto de tablas de la base de datos hasta comprobar que no existe ninguna tabla en la base de datos.
DROP TABLE votantes CASCADE CONSTRAINTS;
DROP table consultas_datos;
DROP table consultas;
DROP table eventos_resultados CASCADE CONSTRAINTS;
DROP table eventos CASCADE CONSTRAINTS;
DROP table localidades;
DROP table partidos CASCADE CONSTRAINTS;
DROP table provincias;

--Ej5:
INSERT INTO votantes VALUES(30653845, 'Maria Gonzalez Ramirez', 'Doctorado', 'Activo', 'goram@telefonica.es', 1,'21/8/1989', 677544822);

--Ej6: Comprobar que todos los campos han sido insertados correctamente, utilizando el comando:
SELECT * FROM votantes;

--Ej7: Realizar el borrado de la inserci�n que acabamos de hacer sobre la tabla votantes. Comprobar que dicho votante ha sido efectivamente borrado de la base de datos, comparando los resultados de la instrucci�n del ejercicio anterior y los actuales.
DELETE FROM votantes WHERE dni=30653845;
SELECT * FROM votantes;

--Ej8: . Realizar diferentes inserciones sobre cada una de las diferentes tablas existentes y comprobar que dichas inserciones fueron realizadas correctamente.
                         --ID,                                                                  FechaFundaci�n, Presupuesto
INSERT INTO partidos VALUES(26, 'NombrePartido', 'Siglas', 'Direcci�n', 'Localidad', 'Presidente', '27/05/1987', 600);
SELECT * FROM partidos;
                        --ID, Evento, Votante, Fecha
INSERT INTO consultas VALUES(900, 10, 27, '11/09/2015');
SELECT * FROM consultas;
                            --ID,          N� hab.
INSERT INTO provincias VALUES(14, "Nombre", 100000000, 'Comunidad Aut�noma');
SELECT * FROM provincias;
                            --ID,           N� hab, Provincia
INSERT INTO localidades VALUES(22, "Nombre", 300000, 10);
SELECT * FROM localidades;
                        --ID,  
INSERT INTO eventos VALUES(33, "Nombre", "11/01/17", "Tipo Elecciones", "M�s Detalles");
SELECT * FROM eventos;
                        --ID, Consula, Partido, Respuesta, Certidumbre
INSERT INTO consultas_datos VALUES(88, 77, 8, "No", 0,13);
SELECT * FROM consultas_datos;
                                --ID, Evento, Partido, Resultado
INSERT INTO eventos_resultados VALUES(54, 20, 30, 0,04);
SELECT * FROM eventos_resultados;

--Ej9: Mostrar el nombre de los eventos que tienen lugar y que se encuentran en la tabla eventos, as� como su tipo ('Europeas', 'Generales', 'Autonomicas', 'Locales', 'Otras') y la fecha en la que se desarrollar�n. �nicamente se deber� mostrar el nombre del evento, el tipo y la fecha del mismo. 
SELECT nombre, tipo, fecha FROM eventos;

--Ej10: Realizar la concatenaci�n del nombre del evento y su tipo, de manera que s�lo se mostrar� lo que se muestra m�s abajo. El nombre de la columna ser� �Convocatoria�.
SELECT nombre || ' de tipo ' || tipo "Convocatoria" FROM eventos;

--Ej11: Realizar concatenaciones de columnas en diferentes tablas de la base de datos. De esta forma, los alumnos se familiarizar�n con la consulta SELECT y con el renombrado de columnas.
SELECT l.nombre || p.nombre
FROM localidades l, provincias p
WHERE l.provincia = p.idprovincia;
