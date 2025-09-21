# AreaDamage
This repository contains a comma seperated list of all player->target ability IDs that are considered to be area-of-effect attacks in The Elder Scrolls Online.

The data from this list resulted from manual testing, and some item sets might be missing from this list.

The list contains abilities that are not considered area damage but were still worth testing and making note of (e.g. Tide King's Gaze, Azureblight, etc.).

The csv is sorted by the following columns: Category (A-Z) -> Subcategory 1 (A-Z) -> Subcategory 2 (A-Z) -> Subcategory 3 (A-Z) -> Ability Name (A-Z) -> Ability ID (Smallest to Largest).

Empty fields in the csv are denoted by a dash ("-").

UTILS

TableBuilder generates table.lua, a commented lua table containing the information from the csv.

ScriptBuilder generates a query-script.txt that, when pasted into the "New Script" part of ESOLogs' Query section, will allow you to filter for AOE abilities or non-AOE abilities. 

TODO

- The damage from the sorcerer class mastery script on mender's bond when you have no pets active is considered to be AOE damage, but the abilityID has not yet been recorded. The abilityID needs to be recorded, and the data row needs to be properly sorted.
