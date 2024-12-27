-- write a SQL query to list the names of all people who starred in Toy Story
SELECT DISTINCT p.name 
FROM people p 
JOIN stars s ON s.person_id = p.id 
JOIN movies m ON s.movie_id = m.id 
WHERE m.title LIKE "%Toy Story%";