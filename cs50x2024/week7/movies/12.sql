-- write a SQL query to list the titles of all movies in which both Bradley Cooper and Jennifer Lawrence starred
SELECT DISTINCT m.title
FROM movies m
JOIN stars s ON s.movie_id = m.id
JOIN people p ON s.person_id = p.id
WHERE m.id IN (
    SELECT movie_id
    FROM stars s1
    JOIN people p1 ON s1.person_id = p1.id
    WHERE p1.name = 'Bradley Cooper'
)
AND m.id IN (
    SELECT movie_id
    FROM stars s2
    JOIN people p2 ON s2.person_id = p2.id
    WHERE p2.name = 'Jennifer Lawrence'
);