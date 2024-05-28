-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT year, month, day, description
FROM crime_scene_reports
WHERE description LIKE '%duck%';
-- Just one robbery involvind a duck -> 07/28/2023
-- Three witnesses are pesent in the time (10:15) -> Humphrey Street bakery
-- Each of their interview transcripts mentions the bakery

SELECT name, transcript
FROM interviews
WHERE day = 28
AND month = 7
AND year = 2023;
-- Found three interesting interviews
-- 1. Thief left the place with a car
-- 2. Thief was in a atm on Leggett Street before in the morning (withdrawing some money)
-- 3. Thief called someone, they were planning to take the earliest flight out of Fiftyville tomorrow

SELECT license_plate, hour
FROM bakery_security_logs
WHERE day = 28
AND month = 7
AND year = 2023
AND hour = 10
AND activity = 'exit';
-- Get some license plates that exit the bakery near the robbery time

SELECT account_number, transaction_type, amount
FROM atm_transactions
WHERE day = 28
AND month = 7
AND year = 2023
AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';
-- Get the number of bank accounts that withdraw money on the robbery day

SELECT id, destination_airport_id FROM flights
WHERE day = 29
AND month = 7
AND year = 2023
AND destination_airport_id != (
    SELECT id
    FROM airports
    WHERE abbreviation = 'CSF'
)
ORDER BY hour, minute
LIMIT 1;
-- Get the earliest flight out of Fiftyville after the day of the robbery

SELECT passport_number FROM passengers
WHERE flight_id = (
    SELECT id FROM flights
    WHERE day = 29
    AND month = 7
    AND year = 2023
    AND destination_airport_id != (
        SELECT id
        FROM airports
        WHERE abbreviation = 'CSF'
    )
    ORDER BY hour, minute
    LIMIT 1
);
-- Get the passport numbers of the early flight out of the city

SELECT caller
FROM phone_calls
WHERE year = 2023
AND month = 7
AND day = 28
AND duration <= 60;
-- Check Phone Calls During the Time Frame and Tap Into Call

SELECT people.name
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.origin_airport_id = airports.id
WHERE airports.city = 'Fiftyville'
AND flights.year = 2023
AND flights.month = 7
AND flights.day = 29
AND flights.hour = 8
AND flights.minute = 20;
-- Find names of the passegenrs on the early flight out of the city

SELECT people.name FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE phone_calls.year = 2023
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration <= 60;
-- Find the names of the callers in the day of the robbery

SELECT people.name
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE year = 2023
AND month = 7
AND day = 28
AND atm_location = 'Leggett Street';
-- Find the names of the people associated with withdraws in the day

SELECT p.name from people p
JOIN bakery_security_logs ON p.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.day = 28
AND bakery_security_logs.month = 7
AND bakery_security_logs.year = 2023
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute BETWEEN 15 AND 25;
-- Find the names of associated with exits in the bakery

-- Just Bruce apears in all of the lists, he is the killer
-- The accomplice must be the receiver of early phone call in the day

SELECT people.name
FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE phone_calls.year = 2023
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration <= 60
AND phone_calls.caller = '(367) 555-5533';
-- Check the phone call of Bruce to get the name of the accomplice
