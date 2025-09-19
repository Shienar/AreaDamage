# AreaDamage
This repository contains a comma seperated list of all player->target ability IDs that are considered to be area-of-effect attacks in The Elder Scrolls Online.

The data from this list resulted from manual testing, and some item sets might be missing from this list.

The list contains abilities that are not considered area damage but were still worth testing and making note of (e.g. Tide King's Gaze, Azureblight, etc.).

The csv is sorted by the following columns: Category (A-Z) -> Subcategory 1 (A-Z) -> Subcategory 2 (A-Z) -> Subcategory 3 (A-Z) -> Ability Name (A-Z) -> Ability ID (Smallest to Largest).

Empty fields in the csv are denoted by a dash ("-").

This repo also contains a simple C program in the utils folder that generates "output.lua", a commented lua table, from the csv values.
