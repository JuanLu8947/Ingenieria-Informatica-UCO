/*Ej1: Mostrar el nombre de pila (sin apellidos), nombre de localidad y
nombre de comunidad de los votantes pertenecientes a las localidades 
1, 3 ó 9. Personaliza el título de dichas columnas
*/ 
SELECT SUBSTR(v.nombrecompleto, 1, INSTR(v.nombrecompleto, ' ')) NAME,
        l.nombre LOCALIDAD, pr.comunidad, l.idlocalidad
FROM votantes v, localidades l, provincias pr
WHERE l.idlocalidad = v.localidad 
AND l.provincia = pr.idprovincia
AND l.idlocalidad IN (1,3,9);

--Ej2: Ordenar las localidades en base a su identificador de localidad
SELECT l1.nombre || ' va antes de ' || l2.nombre Ordenacion
FROM localidades l1, localidades l2
WHERE l2.idlocalidad = l1.idlocalidad+1;

SELECT l.idlocalidad+1
FROM localidades l;

/*Ej3: Obtener el nombre de las localidades que tienen un número de
habitantes mayor que la localidad del votante que es el segundo votante
de más edad de entre todos los votantes existentes en la base de datos
*/
SELECT l.nombre 
FROM localidades l
WHERE l.numerohabitantes > (SELECT l.numerohabitantes 
                            FROM localidades l, votantes v
                            WHERE l.idlocalidad = v.localidad
                            AND v.fechanacimiento = (SELECT MIN(v.fechanacimiento)
                                                    FROM votantes v
                                                    WHERE v.fechanacimiento != (SELECT MIN(v.fechanacimiento)
                                                                                FROM votantes v)));

SELECT l.numerohabitantes 
FROM localidades l, votantes v
WHERE l.idlocalidad = v.localidad
AND v.fechanacimiento = (SELECT MIN(v.fechanacimiento)
                        FROM votantes v
                        WHERE v.fechanacimiento != (SELECT MIN(v.fechanacimiento)
                                                    FROM votantes v)); --nHab-2ºmayor-edad

SELECT MIN(v.fechanacimiento)
FROM votantes v
WHERE v.fechanacimiento != (SELECT MIN(v.fechanacimiento)
                            FROM votantes v); 
--
/*Ej4: Mostrar el nombre completo de los votantes, número de localidad 
a la que pertenecen y “mayoria edad” (mostrará: 'mayor edad' y
'menor edad' en lugar de su fecha de nacimiento en función de si tienen
más de 50 años o no). Los resultados de esta consulta sólo recogerán a
los votantes de las localidades 2, 4 y 8 y quedarán ordenados por la
nueva columna de “mayoria edad”.
*/ --sign
SELECT v.nombrecompleto, v.localidad, 
CASE 
    WHEN ((SYSDATE - v.fechanacimiento) / 365) > 50 THEN 'mayor edad'
    ELSE 'menor edad'
END AS "MAYORIA EDAD", (SYSDATE - v.fechanacimiento) / 365 AS "EDAD"
FROM votantes v
WHERE v.localidad IN (2, 4, 8)
ORDER BY 4;

/*Ej5: Muestra el nombre de las localidades, su número de habitantes y
el nombre de la comunidad a la que pertenecen. Se recogerán sólo
aquellas localidades cuyo número de provincia sea el 1, 2, o 3 y
que tengan mayor número de habitantes que alguna de las localidades de
la provincia número 4.
*/
SELECT l.nombre, l.numerohabitantes, pr.comunidad, pr.idprovincia
FROM localidades l, provincias pr
WHERE pr.idprovincia = l.provincia
AND pr.idprovincia IN (1,2,3)
AND l.numerohabitantes > ANY(SELECT l.numerohabitantes 
                            FROM localidades l, provincias pr
                            WHERE pr.idprovincia = l.provincia
                            AND pr.idprovincia IN 4);

SELECT l.numerohabitantes 
FROM localidades l, provincias pr
WHERE pr.idprovincia = l.provincia
AND pr.idprovincia IN 4;

/*Ej6: Obtener el nombre de los votantes cuya participación ha sido
menor que la media de participaciones de todos los votantes a pesar de
encontrarse en situación laboral de 'Activo'.
*/
SELECT v.nombrecompleto, count(*), v.situacionlaboral
FROM votantes v, consultas c
WHERE c.votante = v.dni
AND v.situacionlaboral LIKE 'Activo'
HAVING count(*) < (SELECT AVG(count(c.votante))
                    FROM consultas c
                    GROUP BY c.votante)
GROUP BY v.nombrecompleto, v.situacionlaboral;

SELECT AVG(count(c.votante))
FROM consultas c
GROUP BY c.votante; 

/*Ej7: Mostrar el nombre de las localidades ordenadas de mayor a menor
nivel de estudios Superiores medio de sus votantes
*/
SELECT l.nombre, AVG(DECODE(v.estudiossuperiores, 'Basicos', 1, 'Superiores', 2, 'Doctorado', 3, 0)) Estudios
FROM localidades l, votantes v
WHERE l.idlocalidad = v.localidad
GROUP BY l.nombre
ORDER BY 2 DESC;

SELECT l.nombre
FROM localidades l, votantes v
WHERE l.idlocalidad = v.localidad
GROUP BY l.nombre
ORDER BY AVG(DECODE(v.estudiossuperiores, 'Basicos', 1, 'Superiores', 2, 'Doctorado', 3, 0)) DESC;

/*Ej8: Mostrar aquellas localidades cuyos votantes tienen un nivel de
estudios superiores medio mayor que todas las medias de estudios superiores
de las provincias.
*/
SELECT l.nombre
FROM localidades l, votantes v
WHERE l.idlocalidad = v.localidad
HAVING AVG(DECODE(v.estudiossuperiores, 'Basicos', 1, 'Superiores', 2, 'Doctorado', 3, 0))
        > ALL(SELECT AVG(DECODE(v.estudiossuperiores, 'Basicos', 1, 'Superiores', 2, 'Doctorado', 3, 0))
            FROM votantes v, localidades l
            WHERE l.idlocalidad = v.localidad)
GROUP BY l.nombre;

SELECT l.nombre, l.idlocalidad, pr.nombre, pr.idprovincia
FROM localidades l, provincias pr, votantes v
WHERE l.provincia = pr.idprovincia
AND l.idlocalidad = v.localidad
GROUP BY l.nombre, l.idlocalidad, pr.nombre, pr.idprovincia
HAVING AVG(DECODE(v.estudiossuperiores, 'Basicos', 1, 'Superiores', 2, 'Doctorado', 3, 0))
        > ALL(SELECT AVG(DECODE(v2.estudiossuperiores, 'Basicos', 1, 'Superiores', 2, 'Doctorado', 3, 0))
            FROM votantes v2, localidades l2
            WHERE l2.idlocalidad = v2.localidad)
ORDER BY 2;

