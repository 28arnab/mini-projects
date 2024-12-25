-- write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred
SELECT DISTINCT p.name
FROM people p
JOIN stars s ON s.person_id = p.id
JOIN stars s2 ON s2.movie_id = s.movie_id
JOIN people p2 ON s2.person_id = p2.id
WHERE p2.name = 'Kevin Bacon' AND p.name != 'Kevin Bacon';