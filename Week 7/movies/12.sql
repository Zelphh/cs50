SELECT movies.title
FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.id = (
    SELECT people.id
    FROM people
    WHERE people.name = 'Bradley Cooper'
) AND movies.id IN (
    SELECT movies.id
    FROM people
    JOIN stars ON people.id = stars.person_id
    JOIN movies ON stars.movie_id = movies.id
    WHERE people.id = (
        SELECT people.id
        FROM people
        WHERE people.name = 'Jennifer Lawrence'
    )
);



