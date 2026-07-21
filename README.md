# fuzzy File finder
[![wakatime](https://wakatime.com/badge/user/a5e23dff-7bc5-43ed-8866-74c17b3691df/project/4a3479fe-dc07-4d35-bb4b-3d9eef39695f.svg)](https://wakatime.com/badge/user/a5e23dff-7bc5-43ed-8866-74c17b3691df/project/4a3479fe-dc07-4d35-bb4b-3d9eef39695f)

## algorythem

- fuzzy finding

## searching

1. Finding

- subsequent matching
- search key has to be in order but not next to each other

1. Ranking

search key: setup

- exact matches at the top > "setup"
- less matching = lower in the ranking > "s_e_t_up"
- the more of the letters are next to each other = higher score
- if two things are tied then the shorter one wins for simplicity

## Programm process

on Start:

1. first thread scans for files and index the paths to memory
2. second thread renders UI (optional)

on input:

1. Filter every loaded file
2. update to check for new found files

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
