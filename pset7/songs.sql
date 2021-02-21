-- SQL query to list names of all songs in the database
SELECT name FROM songs;

-- SQL query to list names of all songs in increasing order of tempo
SELECT name FROM songs ORDER BY tempo ASC;

-- SQL query to list names of to the top 5 longest songs in descending order of length
SELECT name FROM songs ORDER BY duration_ms DESC LIMIT 5;

-- SQL query to list names of any songs that have danceability, energy and valence greater then 0.75
SELECT name FROM songs WHERE danceability > 0.75 AND energy > 0.75 AND valence > 0.75;

-- SQL query that returns the average energy of all the songs
SELECT AVG(energy) FROM songs;

-- SQL query that lists the names of songs that are by Post Malone
SELECT name FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = 'Post Malone');

-- SQL query that returns the average energy of songs that are by Drake
SELECT AVG(energy) FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = 'Drake');

-- SQL query that lists the names of the songs that feature other artists
SELECT name FROM songs WHERE name LIKE '%feat.%';