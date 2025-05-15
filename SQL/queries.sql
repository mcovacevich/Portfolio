<<<<<<< HEAD
-- Queries realizadas sobre la DB Chinook
-- Listar para cada track el nombre del mismo, el genero y el media_type
SELECT t.Name, g.Name, mt.Name
FROM Track as t
    INNER JOIN Genre as g ON g.GenreId = t.GenreID
    INNER JOIN MediaType as mt ON mt.MediaTypeId = t.MediaTypeId


-- Listar la cantidad de tracks que tiene cada género

SELECT g.Name, COUNT(t.TrackId) as CantidadTracks
FROM Genre as g
    INNER JOIN Track as t ON t.GenreId = g.GenreId
GROUP BY g.Name

-- Obtener los artistas que no tienen álbumes. Dar al menos dos soluciones distintas
-- Una
SELECT art.Name
FROM Artist as art 
    LEFT JOIN Album as alb ON alb.ArtistId = art.ArtistId
WHERE alb.AlbumId IS NULL
ORDER BY art.Name ASC

--Otra
SELECT Artist.Name
FROM Artist
EXCEPT -- Esto es como A - B
SELECT art.Name
FROM Artist as art
    INNER JOIN Album as alb ON alb.ArtistId = art.ArtistId

--Otra mas

SELECT Artist.Name
FROM Artist
WHERE Artist.ArtistId NOT IN (SELECT DISTINCT ArtistId FROM Album)
ORDER BY Name ASC

-- Listar el nombre y la cantidad de tracks de los artistas con mas de 50 tracks, ordenados
-- por cantidad de tracks de forma ascendente

SELECT art.Name, COUNT(t.TrackId) as CantTracks 
FROM Artist as art 
    INNER JOIN Album as alb ON alb.ArtistId = art.ArtistId
    INNER JOIN Track as t ON t.AlbumId = alb.AlbumId
GROUP BY art.Name
HAVING COUNT(t.TrackId) > 50
ORDER BY cantTracks

-- Para cada cliente obtener la cantidad de empleados que viven en la misma ciudad 
-- ordenados descendentemente por cantidad de empleados.

SELECT c.CustomerId, COUNT(e.EmployeeId) as CantEmpleados
FROM Customer as c
LEFT JOIN Employee as e ON e.City = c.City
GROUP BY C.CustomerId
ORDER BY cantEmpleados DESC

-- Obtener el dinero recaudado por cada empleado durante cada año.
-- ¿Como extraer un campo de una fecha?

SELECT e.LastName, datepart(year, i.invoiceDate) as year, SUM(i.total) as total
FROM Employee as e
INNER JOIN Customer as c ON c.SupportRepId = e.EmployeeId
INNER JOIN Invoice as i ON i.CustomerId = c.CustomerId
GROUP BY e.EmployeeId, datepart(year, i.invoiceDate), e.LastName
ORDER BY e.LastName ASC, year ASC

-- Obtener la cantidad de pistas de audio que tengan una duracion
-- superior a la duracion promedio de todas las pistas de audio. Ademas, obtener la sumatoria 
-- de la duracion de todas esas pistas en minutos.


SELECT COUNT(t.TrackId) as CantMayorAlPromedio, SUM(Milliseconds / 1000 / 60) as DuracionTotal
FROM Track as t 
WHERE t.Milliseconds > (SELECT AVG(Milliseconds) FROM Track)

-- a) Crear una vista que devuelva las playlists que tienen al menos una
-- pista del genero “Rock”

SELECT DISTINCT p.playlistId, p.Name 
FROM Playlist as p
INNER JOIN PlaylistTrack as pt ON pt.PlaylistId = p.PlaylistId
INNER JOIN Track as t ON t.TrackId = pt.TrackId
INNER JOIN Genre as g ON g.GenreId = t.GenreId
WHERE g.Name = 'Rock'


--IF OBJECT_ID('RockyPlaylists', 'V') IS NOT NULL
-- DROP VIEW RockyPlaylists
--GO

create view RockyPlaylists as
select distinct P.PlaylistId, P.Name 
from Playlist P
where P.PlaylistId = any (
select Pt.PlaylistId from PlaylistTrack Pt
inner join Track T on Pt.TrackId = T.TrackId
inner join Genre G on T.GenreId = G.GenreId
where G.Name = 'Rock')

SELECT * FROM dbo.RockyPlaylists

-- b) Obtener de forma concisa la cantidad de playlists que no poseen pistas de dicho genero

SELECT COUNT(p.PlaylistId) 
FROM Playlist p
WHERE p.PlaylistId NOT IN (SELECT r.PlaylistId FROM RockyPlaylists as r)

-- Obtener las playlists mas caras. (Ayuda: primero obtener el ‘precio’ de cada playlist.)

WITH Precios AS (
    SELECT p.PlaylistId, SUM(t.UnitPrice) as PrecioPlaylist
    FROM Playlist as p
    INNER JOIN PlaylistTrack as pt ON pt.PlaylistId = p.PlaylistId
    INNER JOIN Track as t ON t.TrackId = pt.TrackId
    GROUP BY p.PlaylistId, p.Name
)
SELECT pr.PlaylistId, pr.PrecioPlaylist
FROM Precios as pr
WHERE pr.PrecioPlaylist = (SELECT MAX(PR1.PrecioPlaylist) FROM Precios as PR1)















=======
-- Queries realizadas sobre la DB Chinook
-- Listar para cada track el nombre del mismo, el genero y el media_type
SELECT t.Name, g.Name, mt.Name
FROM Track as t
    INNER JOIN Genre as g ON g.GenreId = t.GenreID
    INNER JOIN MediaType as mt ON mt.MediaTypeId = t.MediaTypeId


-- Listar la cantidad de tracks que tiene cada género

SELECT g.Name, COUNT(t.TrackId) as CantidadTracks
FROM Genre as g
    INNER JOIN Track as t ON t.GenreId = g.GenreId
GROUP BY g.Name

-- Obtener los artistas que no tienen álbumes. Dar al menos dos soluciones distintas
-- Una
SELECT art.Name
FROM Artist as art 
    LEFT JOIN Album as alb ON alb.ArtistId = art.ArtistId
WHERE alb.AlbumId IS NULL
ORDER BY art.Name ASC

--Otra
SELECT Artist.Name
FROM Artist
EXCEPT -- Esto es como A - B
SELECT art.Name
FROM Artist as art
    INNER JOIN Album as alb ON alb.ArtistId = art.ArtistId

--Otra mas

SELECT Artist.Name
FROM Artist
WHERE Artist.ArtistId NOT IN (SELECT DISTINCT ArtistId FROM Album)
ORDER BY Name ASC

-- Listar el nombre y la cantidad de tracks de los artistas con mas de 50 tracks, ordenados
-- por cantidad de tracks de forma ascendente

SELECT art.Name, COUNT(t.TrackId) as CantTracks 
FROM Artist as art 
    INNER JOIN Album as alb ON alb.ArtistId = art.ArtistId
    INNER JOIN Track as t ON t.AlbumId = alb.AlbumId
GROUP BY art.Name
HAVING COUNT(t.TrackId) > 50
ORDER BY cantTracks

-- Para cada cliente obtener la cantidad de empleados que viven en la misma ciudad 
-- ordenados descendentemente por cantidad de empleados.

SELECT c.CustomerId, COUNT(e.EmployeeId) as CantEmpleados
FROM Customer as c
LEFT JOIN Employee as e ON e.City = c.City
GROUP BY C.CustomerId
ORDER BY cantEmpleados DESC

-- Obtener el dinero recaudado por cada empleado durante cada año.
-- ¿Como extraer un campo de una fecha?

SELECT e.LastName, datepart(year, i.invoiceDate) as year, SUM(i.total) as total
FROM Employee as e
INNER JOIN Customer as c ON c.SupportRepId = e.EmployeeId
INNER JOIN Invoice as i ON i.CustomerId = c.CustomerId
GROUP BY e.EmployeeId, datepart(year, i.invoiceDate), e.LastName
ORDER BY e.LastName ASC, year ASC

-- Obtener la cantidad de pistas de audio que tengan una duracion
-- superior a la duracion promedio de todas las pistas de audio. Ademas, obtener la sumatoria 
-- de la duracion de todas esas pistas en minutos.


SELECT COUNT(t.TrackId) as CantMayorAlPromedio, SUM(Milliseconds / 1000 / 60) as DuracionTotal
FROM Track as t 
WHERE t.Milliseconds > (SELECT AVG(Milliseconds) FROM Track)

-- a) Crear una vista que devuelva las playlists que tienen al menos una
-- pista del genero “Rock”

SELECT DISTINCT p.playlistId, p.Name 
FROM Playlist as p
INNER JOIN PlaylistTrack as pt ON pt.PlaylistId = p.PlaylistId
INNER JOIN Track as t ON t.TrackId = pt.TrackId
INNER JOIN Genre as g ON g.GenreId = t.GenreId
WHERE g.Name = 'Rock'


--IF OBJECT_ID('RockyPlaylists', 'V') IS NOT NULL
-- DROP VIEW RockyPlaylists
--GO

create view RockyPlaylists as
select distinct P.PlaylistId, P.Name 
from Playlist P
where P.PlaylistId = any (
select Pt.PlaylistId from PlaylistTrack Pt
inner join Track T on Pt.TrackId = T.TrackId
inner join Genre G on T.GenreId = G.GenreId
where G.Name = 'Rock')

SELECT * FROM dbo.RockyPlaylists

-- b) Obtener de forma concisa la cantidad de playlists que no poseen pistas de dicho genero

SELECT COUNT(p.PlaylistId) 
FROM Playlist p
WHERE p.PlaylistId NOT IN (SELECT r.PlaylistId FROM RockyPlaylists as r)

-- Obtener las playlists mas caras. (Ayuda: primero obtener el ‘precio’ de cada playlist.)

WITH Precios AS (
    SELECT p.PlaylistId, SUM(t.UnitPrice) as PrecioPlaylist
    FROM Playlist as p
    INNER JOIN PlaylistTrack as pt ON pt.PlaylistId = p.PlaylistId
    INNER JOIN Track as t ON t.TrackId = pt.TrackId
    GROUP BY p.PlaylistId, p.Name
)
SELECT pr.PlaylistId, pr.PrecioPlaylist
FROM Precios as pr
WHERE pr.PrecioPlaylist = (SELECT MAX(PR1.PrecioPlaylist) FROM Precios as PR1)















>>>>>>> aeec9c0a972807c774581558be61f93ba49ddadc
