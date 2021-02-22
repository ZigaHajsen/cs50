-- Day: 28
-- Month: 7
-- Year: 2020
-- Street: Chamberlin Street

SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28 AND street = 'Chamberlin Street';

-- description:
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

    SELECT id, transcript
    FROM interviews
    WHERE month = 7 AND day = 28 AND transcript LIKE '%courthouse%';

    -- id | transcript
    -- 161 | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away.
    -- If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.

        SELECT id, name, phone_number, passport_number
        FROM people
        WHERE license_plate IN
        (
            SELECT license_plate
            FROM courthouse_security_logs
            WHERE month = 7 AND day = 28 AND hour = 10 AND minute <= 25 AND minute >= 15 AND activity = 'exit'
        );

        --id     | name      | phone_number   | passport_number
        --221103 | Patrick   | (725) 555-4692 | 2963008352
        --243696 | Amber     | (301) 555-4174 | 7526138472
        --396669 | Elizabeth | (829) 555-5269 | 7049073643
        --398010 | Roger     | (130) 555-0289 | 1695452385
        --467400 | Danielle  | (389) 555-5198 | 8496433585
        --514354 | Russell   | (770) 555-1861 | 3592750733
        --560886 | Evelyn    | (499) 555-9472 | 8294398571
        --686048 | Ernest    | (367) 555-5533 | 5773159633

    -- 162 | I don't know the thief's name, but it was someone I recognized.
    -- Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.

        SELECT id, name, phone_number, passport_number
        FROM people
        WHERE id IN
        (
            SELECT person_id
            FROM bank_accounts
            WHERE account_number IN
            (
                SELECT account_number
                FROM atm_transactions
                WHERE month = 7 AND day = 28 AND atm_location = 'Fifer Street' AND transaction_type = 'withdraw'
            )
        );

        --id     | name      | phone_number   | passport_number
        --395717 | Bobby     | (826) 555-1652 | 9878712108
        --396669 | Elizabeth | (829) 555-5269 | 7049073643
        --438727 | Victoria  | (338) 555-6650 | 9586786673
        --449774 | Madison   | (286) 555-6063 | 1988161715
        --458378 | Roy       | (122) 555-4581 | 4408372428
        --467400 | Danielle  | (389) 555-5198 | 8496433585
        --514354 | Russell   | (770) 555-1861 | 3592750733
        --686048 | Ernest    | (367) 555-5533 | 5773159633

    -- 163 | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute.
    -- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
    -- The thief then asked the person on the other end of the phone to purchase the flight ticket.

        SELECT id, name, phone_number, passport_number
        FROM people
        WHERE phone_number IN
        (
            SELECT caller
            FROM phone_calls
            WHERE month = 7 AND day = 28 AND duration <= 60
        );

        --id     | name     | phone_number   | passport_number
        --395717 | Bobby    | (826) 555-1652 | 9878712108
        --398010 | Roger    | (130) 555-0289 | 1695452385
        --438727 | Victoria | (338) 555-6650 | 9586786673
        --449774 | Madison  | (286) 555-6063 | 1988161715
        --514354 | Russell  | (770) 555-1861 | 3592750733
        --560886 | Evelyn   | (499) 555-9472 | 8294398571
        --561160 | Kathryn  | (609) 555-5876 | 6121106406
        --686048 | Ernest   | (367) 555-5533 | 5773159633
        --907148 | Kimberly | (031) 555-6622 | 9628244268

        SELECT id, name, phone_number, passport_number
        FROM people
        WHERE phone_number IN
        (
            SELECT receiver
            FROM phone_calls
            WHERE month = 7 AND day = 28 AND duration <= 60 AND (caller = '(770) 555-1861' OR caller = '(367) 555-5533')
        );

--CURRENT SUSPECTS                                          CURRENT ACOMPLICES                                      FLIGHT ID
--id     | name     | phone_number   | passport_number      id     | name     | phone_number   | passport_number
--514354 | Russell  | (770) 555-1861 | 3592750733-          847116 | Philip   | (725) 555-3243 | 3391710505         18
--686048 | Ernest   | (367) 555-5533 | 5773159633-          864400 | Berthold | (375) 555-8161 |                    36-


SELECT flight_id, passport_number
FROM passengers
WHERE flight_id IN
(
    SELECT id
    FROM flights
    WHERE origin_airport_id IN
    (
        SELECT id
        FROM airports
        WHERE city = 'Fiftyville'
    )
    AND month = 7 AND day = 29
)
AND passport_number = '3592750733' OR passport_number = '5773159633';

    SELECT id
    FROM flights
    WHERE id = 18 OR id = 36
    ORDER BY hour;

--CURRENT SUSPECTS                                          CURRENT ACOMPLICES                                      FLIGHT ID
--id     | name     | phone_number   | passport_number      id     | name     | phone_number   | passport_number
--686048 | Ernest   | (367) 555-5533 | 5773159633-          864400 | Berthold | (375) 555-8161 |                    36-


SELECT city
FROM airports
WHERE id IN
(
    SELECT destination_airport_id
    FROM flights
    WHERE id = 36
);

--CURRENT SUSPECTS                                          CURRENT ACOMPLICES                                      FLIGHT ID   GOING TO
--id     | name     | phone_number   | passport_number      id     | name     | phone_number   | passport_number
--686048 | Ernest   | (367) 555-5533 | 5773159633-          864400 | Berthold | (375) 555-8161 |                    36-         London






