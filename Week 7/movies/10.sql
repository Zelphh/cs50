SELECT DISTINCT(name)
FROM directors
JOIN people ON person_id = people.id
JOIN movies ON directors.movie_id = movies.id
JOIN ratings ON movies.id = ratings.movie_id
WHERE rating >= 9;
