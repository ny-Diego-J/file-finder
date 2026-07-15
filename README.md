# fuzzy File finder

## algorythem

- fuzzy finding

## searching

1. Finding

- subsequent matching
- search key has to be in order but not next to eachother

1. Ranking

search key: setup

- exact matches at the top > "setup"
- less matching = lower in the ranking > "s_e_t_up"
- the more of the letters are next to eachother = higher score
- if two things are tied then the shorter one wins for simplicity

## Programm process

on Start:

1. first thread scans for files and index the paths to memory
2. secons thread renders ui (optional)

on input:

1. Filter every loadet file
2. update to check for new found filees
