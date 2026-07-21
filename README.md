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

## Further todos

- better ui
  - Highlight matching - done
  - toggle path to file
  - if window is wide enough make split view of selectet file
- QOL (quality of live)
  - make shift enter to open file in $EDITOR
  - copy path to clipboard
  - flags to toggle settings - done
    - threads - done
    - absolute/relative starting path - done
    - all files (.git, .cache, ...) - done
- improve scoring system
  - matches after _, - or camel/pascal case
  - file extension matching
  - consecuative character matching

## flags

-a /--all show all files (even ".git" and so)
-t {} -- enter amount of threads
--relative -- display the relative path
{} path to start from
TODO: maybe implement flag for output (in editor, clipboard, stdout)
