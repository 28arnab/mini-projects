-- Witness 1: Crime Scene Report - Bakery Incident
SELECT csr.description 
FROM crime_scene_reports csr
WHERE csr.street = 'Humphrey Street'
  AND csr.year = 2023
  AND csr.month = 7
  AND csr.day = 28;

-- Witness 1: Bakery Security Logs
SELECT p.name, bsl.activity, bsl.license_plate, bsl.day, bsl.hour, bsl.minute
FROM bakery_security_logs bsl
JOIN people p ON p.license_plate = bsl.license_plate
WHERE bsl.year = 2023 
  AND bsl.month = 7 
  AND bsl.day = 28 
  AND bsl.hour = 10 
  AND bsl.minute BETWEEN 15 AND 25;

-- Witness 2: ATM Transactions - Leggett Street
SELECT a.*, p.name
FROM atm_transactions a
JOIN bank_accounts b ON a.account_number = b.account_number
JOIN people p ON b.person_id = p.id
WHERE a.atm_location = 'Leggett Street' 
  AND a.year = 2023 
  AND a.month = 7 
  AND a.day = 28 
  AND a.transaction_type = 'withdraw';

-- Witness 3: Phone Calls - Short Calls on July 27
SELECT *
FROM phone_calls pc
WHERE pc.year = 2023 
  AND pc.month = 7 
  AND pc.day = 27 
  AND pc.duration < 60;

-- Identifying Flights from Fiftyville
SELECT f.*, origin.full_name AS origin_airport, destination.full_name AS destination_airport
FROM flights f
JOIN airports origin ON f.origin_airport_id = origin.id
JOIN airports destination ON f.destination_airport_id = destination.id
WHERE origin.id = 8 -- Fiftyville's airport ID
  AND f.year = 2023
  AND f.month = 7
  AND f.day = 29
ORDER BY f.hour, f.minute;

-- Check if Bruce or Diana is on the Flight
SELECT p.name
FROM people p
JOIN passengers ps ON p.passport_number = ps.passport_number
WHERE ps.flight_id = 36 -- Flight ID to investigate
  AND p.name IN ('Bruce', 'Diana');

-- Combining Witness Data to Identify the Thief
WITH bakery_logs AS (
    SELECT bsl.license_plate
    FROM bakery_security_logs bsl
    WHERE bsl.year = 2023 
      AND bsl.month = 7 
      AND bsl.day = 28 
      AND bsl.hour = 10 
      AND bsl.minute BETWEEN 15 AND 25
),
atm_data AS (
    SELECT b.account_number
    FROM atm_transactions a
    JOIN bank_accounts b ON a.account_number = b.account_number
    WHERE a.atm_location = 'Leggett Street' 
      AND a.year = 2023 
      AND a.month = 7 
      AND a.day = 28 
      AND a.transaction_type = 'withdraw'
),
phone_logs AS (
    SELECT pc.caller
    FROM phone_calls pc
    WHERE pc.year = 2023 
      AND pc.month = 7 
      AND pc.day = 28 
      AND pc.duration < 60
)
SELECT DISTINCT p.name
FROM people p
JOIN bank_accounts ba ON ba.person_id = p.id
JOIN atm_data ad ON ba.account_number = ad.account_number
JOIN phone_logs pl ON p.phone_number = pl.caller
JOIN bakery_logs bl ON p.license_plate = bl.license_plate;

-- Identify Bruce's Accomplice
SELECT DISTINCT p2.name
FROM phone_calls pc
JOIN people p1 ON pc.caller = p1.phone_number
JOIN people p2 ON pc.receiver = p2.phone_number
WHERE p1.name = 'Bruce' 
  AND pc.year = 2023 
  AND pc.month = 7 
  AND pc.day = 28 
  AND pc.duration < 60;

-- +---------------------------------------------+
-- | Start: Solve the Mystery                    |
-- +---------------------------------------------+
--                     |
--                     v
-- +---------------------------------------------+
-- | Step 1: Analyze Crime Scene Reports         |
-- | - TABLE: crime_scene_reports                |
-- |   Columns: description, street, year,       |
-- |            month, day                       |
-- +---------------------------------------------+
--                     |
--                     v
-- +---------------------------------------------+
-- | Step 2: Investigate Witness 1 - Bakery Logs |
-- | - TABLE: bakery_security_logs               |
-- |   Columns: license_plate, activity,         |
-- |            year, month, day, hour, minute   |
-- | - TABLE: people                             |
-- |   Columns: name, license_plate              |
-- +---------------------------------------------+
--                     |
--                     v
-- +---------------------------------------------+
-- | Step 3: Investigate Witness 2 - ATM Logs    |
-- | - TABLE: atm_transactions                   |
-- |   Columns: account_number, transaction_type,|
-- |            atm_location, year, month, day   |
-- | - TABLE: bank_accounts                      |
-- |   Columns: account_number, person_id        |
-- | - TABLE: people                             |
-- |   Columns: id, name                         |
-- +---------------------------------------------+
--                     |
--                     v
-- +---------------------------------------------+
-- | Step 4: Investigate Witness 3 - Phone Calls |
-- | - TABLE: phone_calls                        |
-- |   Columns: caller, receiver, duration,      |
-- |            year, month, day                 |
-- | - TABLE: people                             |
-- |   Columns: name, phone_number               |
-- +---------------------------------------------+
--                     |
--                     v
-- +---------------------------------------------+
-- | Step 5: Flight Check (Bruce or Diana)       |
-- | - TABLE: flights                            |
-- |   Columns: id, origin_airport_id,           |
-- |            destination_airport_id, year,    |
-- |            month, day, hour, minute         |
-- | - TABLE: airports                           |
-- |   Columns: id, full_name                    |
-- | - TABLE: passengers                         |
-- |   Columns: passport_number, flight_id       |
-- | - TABLE: people                             |
-- |   Columns: passport_number, name            |
-- +---------------------------------------------+
--                     |
--                     v
-- +---------------------------------------------+
-- | Step 6: Combine Evidence                    |
-- | - TABLES: bakery_security_logs              |
-- |            atm_transactions                 |
-- |            bank_accounts                    |
-- |            phone_calls                      |
-- |            people                           |
-- +---------------------------------------------+
--                     |
--                     v
-- +---------------------------------------------+
-- | Step 7: Accomplice Check (Bruce's Calls)    |
-- | - TABLE: phone_calls                        |
-- |   Columns: caller, receiver, duration,      |
-- |            year, month, day                 |
-- | - TABLE: people                             |
-- |   Columns: name, phone_number               |
-- +---------------------------------------------+
--                     |
--                     v
-- +---------------------------------------------+
-- | Solution: Thief + Accomplice Identified     |
-- +---------------------------------------------+
