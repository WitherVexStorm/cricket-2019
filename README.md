# cricket-2019
---

Cricket Simulator with T20, ODI and Test match support, plus Bilateral Series and Tournaments!

Made By: Jaideep Shekhar

## Features
---

- Play a game with team against any other team!
- View the entire match, ball by ball!
- View full scorecard and player statistics for both teams!
- Customise your teams to your liking!
- Three game modes available: T20, ODI and TEST!
- Bilateral Series also available!
- Play series of upto 7 games!
- Knockout Tournament also available!
- Lead your team to victory against 3 opponents!
- 4 teams available by default!
- Easily create your own teams!
- Simple executable, no plugins or installers required!

## How to play
---

### Basic Usage:
---

1) `git clone` the repo.
2) Compile the executable with `g++ -std=c++11 main.c -o cricket2019`
3) Play with `./cricket2019`

### Custom Teams:
---

Add a text file with 11 player names and their role (ie "Batsman", "AllRounder" or "Bowler") separated by hyphens ("-").

Example:
```
Rohit Sharma-Batsman
Hardik Pandya-AllRounder
Jasprit Bumrah-Bowler
```

Already provided teams:
1) [India](India.txt)
2) [England](England.txt)
3) [Australia](Australia.txt)
4) [South Africa](SouthAfrica.txt)

### Setup a Series
---

See `testSeries` function in `main.cpp`.

### Setup a Tournament
---

See `testTournament` function in `main.cpp`.
