-- SQL query to list the titles and release years of all Harry Potter movies, in chronological order
SELECT title, year 
FROM movies 
WHERE title LIKE 'Harry Potter%' 
ORDER BY year;

-- SQL query to determine the birth year of Emma Stone
SELECT birth 
FROM people 
WHERE name = 'Emma Stone';

-- SQL query to list the titles of all movies with a release date on or after 2018, in alphabetical order
SELECT title 
FROM movies 
WHERE year >= 2018 
ORDER BY title;

-- SQL query to determine the number of movies with an IMDb rating of 10.0
SELECT COUNT(movie_id) 
FROM ratings 
WHERE rating = 10.0;

-- SQL query to list the titles and release years of all Harry Potter movies, in chronological order
SELECT title, year 
FROM movies 
WHERE title LIKE 'Harry Potter%' 
ORDER BY year;

-- SQL query to determine the average rating of all movies released in 2012
SELECT AVG(rating) 
FROM ratings JOIN movies ON movies.id = ratings.movie_id 
WHERE year = 2012; 

-- SQL query to list all movies released in 2010 and their ratings, in descending order by rating.
-- For movies with the same rating, order them alphabetically by title
SELECT title, rating 
FROM movies JOIN ratings ON movies.id = ratings.movie_id 
WHERE year = 2010 
ORDER BY rating DESC, title;

-- SQL query to list the names of all people who starred in Toy Story
SELECT name 
FROM people JOIN stars ON stars.person_id = people.id JOIN movies ON movies.id = stars.movie_id WHERE title = 'Toy Story'

-- SQL query to list the names of all people who starred in a movie released in 2004, ordered by birth year
SELECT name 
FROM people JOIN stars ON stars.person_id = people.id JOIN movies ON movies.id = stars.movie_id WHERE year = 2004 
ORDER BY birth;

-- SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0
SELECT name 
FROM people JOIN directors ON directors.person_id = people.id JOIN ratings ON ratings.movie_id = directors.movie_id 
WHERE rating >= 9.0;

-- SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated
SELECT title
FROM people JOIN stars ON stars.person_id = people.id JOIN movies ON movies.id = stars.movie_id JOIN ratings ON ratings.movie_id = movies.id
WHERE name = 'Chadwick Boseman'
ORDER BY rating DESC
LIMIT 5;

-- SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred
SELECT title
FROM people JOIN stars ON stars.person_id = people.id JOIN movies ON movies.id = stars.movie_id
WHERE name = 'Johnny Depp'
INTERSECT
SELECT title
FROM people JOIN stars ON stars.person_id = people.id JOIN movies ON movies.id = stars.movie_id
WHERE name = 'Helena Bonham Carter';

-- SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred
SELECT name
FROM stars JOIN people ON stars.person_id = people.id
WHERE movie_id IN (SELECT movie_id FROM people JOIN stars ON stars.person_id = people.id WHERE birth = 1958 AND name = 'Kevin Bacon')
AND name != 'Kevin Bacon';