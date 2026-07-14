# file finder

## algorythem

- fuzzy finder

## searching

1. Finding

- subsequent matching
- search key has to be in order but not next to eachother

1. Ranking

search key: setup

- exact matches at the top > "setup"
- less mathing lower int the ranking > "s_e_t_up"
- the more the letter the next are to eachother the higher the score
- matching casing like for "bf" to "bar_foo" has higher score than "barfoo"
- small bonus for first character matching
- if two things are tied then the shorter one wins

## Programm process

on Start:

1. first thread scans for files and index the paths to memory
2. secons thread renders ui (optional)

on input:

1. Filter every loadet file
2. update to check for new found filees
