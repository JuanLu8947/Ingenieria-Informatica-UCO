--Ej 1: Obtener el nombre de todos los votantes cuyo
--segundo apellido acaba en “n”.
SELECT v.nombrecompleto
FROM votantes v
WHERE v.nombrecompleto LIKE '%n';

--Ej2: Obtener el DNI de todos los votantes que tengan
--al menos tres 5s en su DNI.
SELECT v.dni
FROM votantes v
WHERE v.dni LIKE '%5%5%5%';

--Ej 3: Obtener el nombre de aquellos votantes cuya
--fecha de nacimiento sea posterior al 1 de Enero de 1990.
SELECT v.nombrecompleto
FROM votantes v
WHERE v.fechanacimiento > '01/01/1990';

--Ej 4: Obtener el nombre del votante y el nombre de la localidad 
--de aquellos votantes que han ejercido el voto en
--una localidad que tiene más de 300000 habitantes
SELECT v.nombrecompleto, l.nombre
FROM votantes v, localidades l
WHERE l.numerohabitantes > 300000
AND l.idlocalidad = v.localidad;

--Ej5: Obtener el nombre del votante y el nombre de la comunidad
--de aquellos votantes que han ejercido el voto en
--una localidad que tiene más de 300000 habitantes
SELECT v.nombrecompleto, p.comunidad
FROM votantes v, provincias p, localidades l
WHERE l.numerohabitantes > 300000
AND v.localidad = l.idlocalidad
AND l.provincia = p.idprovincia;

--Ej6: Obtener el identificador del partido y 
--el número de datos o consultas que se tiene para
--dicho partido de entre todos los partidos sobre los que
--se han realizado alguna consulta.
SELECT p.idpartido "partido", count(*) "conteo"
FROM partidos p, consultas_datos cd
WHERE cd.partido = p.idpartido
GROUP BY p.idpartido;

--Ej7: es igual


--Ej8: Mostrar el nombre del partido político
--sobre el que se han realizado más de 10  consultas
SELECT p.nombrecompleto
FROM partidos p, consultas_datos cd
WHERE cd.partido = p.idpartido
HAVING count(*)>10
GROUP BY p.nombrecompleto;

--Ej9: Mostrar el nombre del partido 
--y el número de consultas realizadas para
--aquellos partidos que aparecen en más de 10 consultas.
SELECT p.nombrecompleto, count(*) "conteo"
FROM partidos p, consultas_datos cd
WHERE cd.partido = p.idpartido
HAVING count(*)>10
GROUP BY p.nombrecompleto;

--Ej10: Mostrar el nombre de los partidos 
--y el número de consultas realizadas para
--cada partido considerando sólo aquellas consultas
--en las que el encuestado ha contestado afirmativamente a
--votar a dicho partido y con una certidumbre
--por encima del 80%
SELECT p.nombrecompleto, count(*) "conteo"
FROM partidos p, consultas_datos cd
WHERE cd.partido = p.idpartido 
AND cd.certidumbre > 0.8
GROUP BY p.nombrecompleto;


