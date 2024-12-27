-- write a SQL query to list the titles of all movies with a release date on or after 2018, in alphabetical order
SELECT title 
FROM movies m
WHERE m.year >= 2018
ORDER BY m.title ASC;