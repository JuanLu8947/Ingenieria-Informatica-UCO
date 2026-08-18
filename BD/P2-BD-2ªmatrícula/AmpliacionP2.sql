--Ej1: Obtener el DNI de todos los votantes que tengan dos 6s 
--en su teléfono, pero contemplar que no tienen más de tres
SELECT v.dni, v.telefono
FROM votantes v
WHERE v.telefono LIKE '%6%6%' 
AND v.telefono NOT LIKE '%6%6%6%';

--Ej2: Obtener el DNI de todos los votantes que tengan tres 6s 
--en su teléfono, pero contemplar que no tienen más de tres, 
--dos de ellos deben estar juntos
SELECT v.dni, v.telefono
FROM votantes v
WHERE v.telefono LIKE '%66%6%' OR v.telefono LIKE '%6%66%'
AND v.telefono NOT LIKE '%6%6%6%6%';

--Ej3: Mostrar aquella localidad cuyo número de habitantes 
--acaba igual que su número de provincia, 
--mostrando también el nombre de la provincia a la que pertenece
SELECT l.nombre, l.numerohabitantes, p.nombre, p.idprovincia
FROM localidades l, provincias p
WHERE l.provincia = p.idprovincia
AND SUBSTR(l.numerohabitantes, LENGTH(l.numerohabitantes)) = p.idprovincia;

/*[WHERE]
SUBSTR(cadena original, 
        posición en la q se empieza la extracción, 
        [longitud extracción])
Con posiciones negativas empieza desde atrás
*/

--Ej4: Mostrar el nombre completo de los votantes cuyo
--teléfono acaba igual que su DNI
SELECT v.nombrecompleto, v.telefono, v.dni
FROM votantes v
WHERE SUBSTR(v.telefono, LENGTH(v.telefono)) = SUBSTR(v.dni, LENGTH(v.dni));

--Ej5: Mostrar el nombre completo de aquellos votantes que
--contienen al menos una 'S' y
--cuya fecha de nacimiento es anterior al 12 de febrero de 1990.
SELECT v.nombrecompleto, v.fechanacimiento
FROM votantes v
WHERE v.fechanacimiento < '12/02/1990'
AND v.nombrecompleto LIKE '%s%';

--Ej6: Obtener todos los votantes que han participado en alguna consulta. 
--Dichos votantes deben aparecer en orden decreciente de DNI
SELECT DISTINCT v.nombrecompleto, v.dni
FROM votantes v, consultas c
WHERE v.dni = c.votante
ORDER BY v.dni DESC;

--Ej7: Mostrar el DNI de aquellos votantes que han participado
--en más de tres consultas
SELECT c.votante
FROM consultas c
HAVING count(*)>3
GROUP BY c.votante;

--Ej8: Mostrar el nombre completo de los votantes que han participado
--en más de tres consultas y 
--especificar en cuentas consultas participaron (en orden creciente)
SELECT v.nombrecompleto, count(*)
FROM votantes v, consultas c
WHERE v.dni = c.votante
HAVING count(*)>3
GROUP BY v.nombrecompleto
ORDER BY 2 ASC;

--Ej9: Obtener el nombre de los votantes y el nombre de su localidad 
--para aquellos votantes que han sido consultados en 
--una localidad que tiene más de 300000 habitantes
SELECT v.nombrecompleto, l.nombre, l.numerohabitantes
FROM votantes v, localidades l
WHERE v.localidad = l.idlocalidad
AND l.numerohabitantes > 300000;

--Ej10: Mostrar el nombre de cada partido político y 
--la máxima certidumbre que tiene para sus consultas
SELECT p.nombrecompleto, MAX(cd.certidumbre)
FROM partidos p, consultas_datos cd
WHERE cd.partido = p.idpartido
GROUP BY p.nombrecompleto;

--Ej11: Mostrar el nombre del votante y su certidumbre media en
--todas las consultas en las que ha respondido de manera afirmativa
SELECT v.nombrecompleto, AVG(cd.certidumbre)
FROM votantes v, consultas_datos cd, consultas c
WHERE cd.consulta = c.idconsulta AND c.votante = v.dni
GROUP BY v.nombrecompleto;

--Ej12: Mostrar el nombre del votante y su certidumbre media en
--todas las consultas en las que ha respondido de manera afirmativa
--ÚNICAMENTE para aquellos votantes cuya 
--certidumbre media está entre 0'5 y 0'8.
SELECT v.nombrecompleto, AVG(cd.certidumbre), cd.respuesta
FROM votantes v, consultas_datos cd, consultas c
WHERE cd.consulta = c.idconsulta AND c.votante = v.dni
AND cd.respuesta LIKE 'Si'
HAVING AVG(cd.certidumbre) BETWEEN 0.5 AND 0.8
GROUP BY v.nombrecompleto, cd.respuesta;

--Ej13: Mostrar el nombre de los partidos y la certidumbre media 
--obtenida para cada partido considerando solo aquellas consultas
--en las que el encuestado ha contestado negativamente 
--a votar a dicho partido y 
--con una certidumbre significativa (por encima del 60%)
SELECT p.nombrecompleto, AVG(cd.certidumbre), cd.respuesta
FROM partidos p, consultas_datos cd
WHERE cd.partido = p.idpartido
AND cd.respuesta LIKE 'No'
AND cd.certidumbre > 0.6
GROUP BY p.nombrecompleto, cd.respuesta;






