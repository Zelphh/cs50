SELECT name
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE people.id IN (
    SELECT stars.person_id
    FROM stars
    JOIN people ON stars.person_id = people.id
    WHERE stars.movie_id IN (
        SELECT movies.id
        FROM movies
        JOIN stars ON movies.id = stars.movie_id
        JOIN people ON stars.person_id = people.id
        WHERE people.id IN (
            SELECT people.id
            FROM people
            WHERE people.name = 'Kevin Bacon'
            AND people.birth = 1958
        )
    )
    AND people.name != 'Kevin Bacon'
);
