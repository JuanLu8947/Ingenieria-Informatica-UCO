/*Ej1: Obtener el nombre de todos los votantes cuyo DNI acaba igual que
el identificador de su localidad más 1. 
*/
SELECT v.nombrecompleto
FROM votantes v, localidades l
WHERE SUBSTR(v.dni, LENGTH(v.dni)) = l.idlocalidad+1
AND l.idlocalidad = v.localidad;
/*
SUBSTR(cadena original, 
        posición en la q se empieza la extracción, 
        [longitud extracción])
*/

/*Ej2: Obtener el nombre de todos los votantes así como
el nombre de la localidad en la que viven teniendo en cuenta que
todos los que sean de la provincia de Córdoba se han mudado a Madrid.
*/--DEOCDE en el WHERE mismo orden
SELECT v.nombrecompleto, DECODE(l.nombre, 'Cordoba', 'Madrid', 'Montilla', 'Madrid', 'Baena', 'Madrid', l.nombre) Nombre --l.nombre --, 
FROM votantes v, localidades l
WHERE --DECODE(l.idlocalidad, 1, 9, 2, 9, 3, 9, l.idlocalidad) = v.localidad AND
v.localidad = l.idlocalidad;
/* 
CASE WHEN _ IN (1,2,3) 
    THEN 'Madrid'
    WHEN _ IN (4,5)
    THEN _
    ELSE _
END
*/


/*Ej3: Mostrar las siglas de aquellos partidos que han participado
un mayor número	de veces en	eventos.
*/
SELECT p.siglas
FROM partidos p, eventos_resultados e_r
WHERE p.idpartido = e_r.partido
HAVING count(*) = MAX(e_r.evento)
GROUP BY p.siglas;

/*Ej4: Obtener el DNI del segundo votante de más edad */
SELECT v.dni
FROM votantes v
WHERE v.fechanacimiento = 
    (SELECT MIN(v.fechanacimiento)
    FROM votantes v
    WHERE v.fechanacimiento != (SELECT MIN(v.fechanacimiento)
                                FROM votantes v));

/*Ej5: Obtener el DNI del votante y el numero de veces que
dicho votante ha participado en una consulta, 
mostrando el resultado de manera descendente
en cuanto a número de participaciones.
*/
SELECT v.dni, count(*)
FROM votantes v, consultas_datos cd, consultas c
WHERE c.votante = v.dni AND cd.consulta = c.idconsulta
GROUP BY v.dni
ORDER BY 2 DESC;

/*Ej6: Obtener el DNI del votante y el numero de veces que
dicho votante ha participado en una consulta, 
mostrando el resultado de manera descendente
en cuanto a número de participaciones. 
Sólo se mostrarán aquellos votantes cuya participación ha sido
mayor que la media de participaciones de todos los votantes.
*/
SELECT c.votante, count(*)
FROM consultas c
HAVING count(*) > (SELECT AVG(count(*))
                    FROM consultas c
                    GROUP BY c.votante)
GROUP BY c.votante
ORDER BY 2 DESC;
/*Ej7: Obtener el nombre de los votantes cuya participación ha sido
mayor que la media de participaciones de todos los votantes.
*/
SELECT v.nombrecompleto
FROM votantes v, consultas c
WHERE v.dni = c.votante
HAVING count(*) > (SELECT AVG(count(*))
                    FROM consultas c
                    GROUP BY c.votante)
GROUP BY v.nombrecompleto;

/*Ej8: Obtener el DNI del votante y el numero de veces que
dicho votante ha participado en una consulta, 
mostrando el resultado de manera descendente
en cuanto a número de participaciones 
y no mostrando los resultados del segundo votante de más edad.
*/
SELECT v.dni, count(*)
FROM votantes v, consultas c
WHERE v.dni = c.votante
AND v.fechanacimiento != 
    (SELECT MIN(v.fechanacimiento)
    FROM votantes v
    WHERE v.fechanacimiento != (SELECT MIN(v.fechanacimiento)
                                FROM votantes v))
GROUP BY v.dni
ORDER BY 2 DESC;



