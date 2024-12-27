-- write a SQL query to determine the average rating of all movies released in 2012
SELECT AVG(rating) 
FROM ratings r 
JOIN movies m ON r.movie_id = m.id 
WHERE m.year = 2012;