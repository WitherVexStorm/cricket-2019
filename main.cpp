#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <vector>

static const int RUN_MAP_LENGTH = 64;
static const int TEAM_SIZE = 11;
static const int MAX_WICKETS = 10;

class Batsman
{
    protected:
        int runsScored;
        int ballsFaced;
        int fours;
        int sixes;
        int fifties;
        int centuries;
        int innings;
        int notOuts;
    
    public:
        Batsman()
        {
            runsScored = 0;
            ballsFaced = 0;
            fours = 0;
            sixes = 0;
            fifties = 0;
            centuries = 0;
            innings = 0;
            notOuts = 0;
        }

        int getRunsScored()
        {
            return runsScored;
        }

        int getBallsFaced()
        {
            return ballsFaced;
        }

        int getFours()
        {
            return fours;
        }

        int getSixes()
        {
            return sixes;
        }

        int getFifties()
        {
            return fifties;
        }

        int getCenturies()
        {
            return centuries;
        }

        int getNotOuts()
        {
            return notOuts;
        }

        int getInnings()
        {
            return innings;
        }

        void startInnings()
        {
            ++innings;
        }

        void endInnings()
        {
            ++notOuts;
            updateStatistics();
        }

        void updateStatistics()
        {
            if (runsScored >= 100)
            {
                ++centuries;
            } else
            if (runsScored >= 50)
            {
                ++fifties;
            }
        }

        void batTo(int run)
        {
            ++ballsFaced;
            if (run == -1)
            {
                updateStatistics();
                return;
            }
            if (run == 4)
            {
                fours++;
            }
            else if (run == 6)
            {
                sixes++;
            }
            runsScored += run;
        }

        void printStats()
        {
            std::cout << "  Runs Scored: " << runsScored << "\n";
            std::cout << "  Balls Faced: " << ballsFaced << "\n";
            std::cout << "  Fours: " << fours << "\n";
            std::cout << "  Sixes: " << sixes << "\n";
            std::cout << "  Fifties: " << fifties << "\n";
            std::cout << "  Centuries: " << centuries << "\n";
            std::cout << "  Batting Stints: " << innings << "\n";
            std::cout << "  Not Outs: " << notOuts << "\n";
        }
};

class Bowler
{
    protected:
        int ballsBowled;
        int runsGiven;
        int wicketsTaken;
        int maidenOvers;
        int hattricks;
        int fiveWicketHauls;
        int innings;
        int consequtiveWickets;
        int isMaidenOver;
    
    public:
        Bowler()
        {
            ballsBowled = 0;
            runsGiven = 0;
            wicketsTaken = 0;
            maidenOvers = 0;
            hattricks = 0;
            fiveWicketHauls = 0;
            innings = 0;
            consequtiveWickets = 0;
            isMaidenOver = 0;
        }

        int getBallsBowled()
        {
            return ballsBowled;
        }

        int getRunsGiven()
        {
            return runsGiven;
        }

        int getWicketsTaken()
        {
            return wicketsTaken;
        }

        int getMaidenOvers()
        {
            return maidenOvers;
        }

        int getHattricks()
        {
            return hattricks;
        }

        int getFiveWicketHauls()
        {
            return fiveWicketHauls;
        }

        int getInnings()
        {
            return innings;
        }

        void startInnings()
        {
            ++innings;
        }

        void endInnings()
        {
            isMaidenOver = 0;
            updateStatistics();
        }

        void updateStatistics()
        {
            if (wicketsTaken >= 5)
            {
                ++fiveWicketHauls;
            }
        }

        int bowl(int * run_map)
        {
            if (ballsBowled % 6 == 0)
            {
                if (isMaidenOver)
                {
                    ++maidenOvers;
                }
                isMaidenOver = 1;
            }
            int run = run_map[rand() % RUN_MAP_LENGTH];
            ++ballsBowled;
            runsGiven += run == -1 ? 0 : run;
            if (run != 0 && run != -1)
            {
                isMaidenOver = 0;
            }
            if (run == -1)
            {
                ++wicketsTaken;
                if (++consequtiveWickets == 3)
                {
                    ++hattricks;
                    consequtiveWickets = 0;
                }
            } else 
            {
                consequtiveWickets = 0;
            }
            return run;
        }

        void printStats()
        {
            std::cout << "  Balls Bowled: " << ballsBowled << "\n";
            std::cout << "  Runs Given: " << runsGiven << "\n";
            std::cout << "  Wickets Taken: " << wicketsTaken << "\n";
            std::cout << "  Maiden Overs: " << maidenOvers << "\n";
            std::cout << "  Hattricks: " << hattricks << "\n";
            std::cout << "  Five Wicket Hauls: " << fiveWicketHauls << "\n";
            std::cout << "  Bowling Stints: " << innings << "\n";
        }
};

class Player: public Batsman, public Bowler
{
    private:
        char name[32];

    public:
        Player(const char * _name)
        {
            strcpy(name, _name);
        }

        const char * getName()
        {
            return name;
        }

        void printStats()
        {
            std::cout << "Player: " << name << "\n";
            Batsman::printStats();
            Bowler::printStats();
        }

        void updateStatisticsFrom(const Player& player)
        {
            runsScored += player.runsScored;
            ballsFaced += player.ballsFaced;
            fours += player.fours;
            sixes += player.sixes;
            fifties += player.fifties;
            centuries += player.centuries;
            notOuts += player.notOuts;
            Batsman::innings += player.Batsman::innings;
            ballsBowled += player.ballsBowled;
            runsGiven += player.runsGiven;
            wicketsTaken += player.wicketsTaken;
            maidenOvers += player.maidenOvers;
            hattricks += player.hattricks;
            fiveWicketHauls += player.fiveWicketHauls;
            Bowler::innings += player.Bowler::innings;
        }
};

class Team
{
    private:
        char name[32];
        struct flag
        {
            unsigned char role : 2;
            unsigned char hasBowled : 1;
            unsigned char isTired : 1;
            unsigned char tiredLevel : 4;
        } flags[TEAM_SIZE];
        Player * players[TEAM_SIZE];

    public:
        enum gamerole
        {
            EMPTY,
            BATSMAN,
            BOWLER,
            ALLROUNDER
        };

        Team(const char * _name)
        {
            strcpy(name, _name);
            for (int i = 0; i < TEAM_SIZE; i++)
            {
                players[i] = nullptr;
                flags[i].role = EMPTY;
                flags[i].hasBowled = 0;
                flags[i].isTired = 0;
                flags[i].tiredLevel = 0;
            }
        }

        const char * getName()
        {
            return name;
        }

        Player * getPlayer(int index)
        {
            return players[index];
        }

        int getRole(int index)
        {
            return flags[index].role;
        }

        void addBatsman(Player * player, int index)
        {
            flags[index].role = BATSMAN;
            players[index] = player;
        }

        void addBowler(Player * player, int index)
        {
            flags[index].role = BOWLER;
            players[index] = player;
        }

        void addAllRounder(Player * player, int index)
        {
            flags[index].role = ALLROUNDER;
            players[index] = player;
        }

        Player * selectBatsman(int& previousBatsmanIndex)
        {
            players[++previousBatsmanIndex]->Batsman::startInnings();
            return players[previousBatsmanIndex];
        }

        Player * selectBowler(int& previousBowlerIndex, int maxOversPerBowler)
        {
            for (int i = TEAM_SIZE-1; i >= 0; --i)
            {
                if (flags[i].tiredLevel == 11)
                {
                    flags[i].isTired = 1;
                }
                if (i != previousBowlerIndex)
                {
                    flags[i].tiredLevel = flags[i].tiredLevel > 0 ? flags[i].tiredLevel - 1 : 0;
                    if (flags[i].tiredLevel == 0)
                    {
                        flags[i].isTired = 0;
                    }
                    if ((flags[i].role == BOWLER || flags[i].role == ALLROUNDER) && players[i]->getBallsBowled() < maxOversPerBowler * 6 && !flags[i].isTired)
                    {
                        previousBowlerIndex = i;
                        flags[i].tiredLevel += 2;
                        if (!flags[i].hasBowled)
                        {
                            flags[i].hasBowled = 1;
                            players[i]->Bowler::startInnings();
                        }
                        return players[i];
                    }
                }
            }
            return nullptr;
        }

        static Team * fromFile(std::string filename)
        {
            std::ifstream file(filename + ".txt");
            std::string name;
            std::string role;
            int battingOrder = -1;
            Team * team = new Team(filename.c_str());
            while (!file.eof())
            {
                std::getline(file, name, '-');
                std::getline(file, role, '\n');
                if (role == "Batsman")
                {
                    team->addBatsman(new Player(name.c_str()), ++battingOrder);
                } else 
                if (role == "Bowler")
                {
                    team->addBowler(new Player(name.c_str()), ++battingOrder);
                } else 
                if (role == "AllRounder")
                {
                    team->addAllRounder(new Player(name.c_str()), ++battingOrder);
                }
            }
            file.close();
            return team;
        }

        ~Team()
        {
            for (int i = 0; i < TEAM_SIZE; i++)
            {
                delete players[i];
            }
        }
};

#define declareResult(x, r) {\
    std::stringstream ss;\
    ss << x;\
    strcpy(scorecard.result, ss.str().c_str());\
    std::cout << "\n" << ss.str() << "\n";\
    return r;\
}

class CricketGame
{
    public:
        enum gametype
        {
            T20_GAME,
            ODI_GAME,
            TEST_GAME
        };

        class BattingReport
        {
            public:
                char playerName[32];
                int runs;
                int balls;
                int fours;
                int sixes;
                int notOut;
                BattingReport *next;

                BattingReport(const char * _playerName)
                {
                    strcpy(playerName, _playerName);
                    runs = 0;
                    balls = 0;
                    fours = 0;
                    sixes = 0;
                    notOut = 0;
                    next = nullptr;
                }

                void print(int batsmanNumber)
                {
                    if (balls > 0)
                    {
                        std::cout << batsmanNumber << ") " << std::left << std::setw(20) << playerName << std::right << ": " << runs << "/" << balls << (notOut ? " not out" : "") << "\n";
                    }
                    else
                    {
                        std::cout << batsmanNumber << ") " << std::left << std::setw(20) << playerName << std::right << ": " << "Did not bat.\n";
                    }
                }
        };

        class BowlingReport
        {
            public:
                char playerName[32];
                int balls;
                int runs;
                int wickets;
                int maidens;
                BowlingReport *next;

                BowlingReport(const char * _playerName)
                {
                    strcpy(playerName, _playerName);
                    balls = 0;
                    runs = 0;
                    wickets = 0;
                    maidens = 0;
                    next = nullptr;
                }

                void print(int bowlerNumber)
                {
                    std::cout << bowlerNumber << ") " << std::left << std::setw(20) << playerName << std::right << ": " << std::setw(3) << balls / 6 << "." << balls % 6 << " - " << std::setw(3) << maidens << " - " << std::setw(3) << runs << " - " << std::setw(3) << wickets << "\n";
                }
        };

        class InningsReport
        {
            private:
                char * numbers[TEAM_SIZE] = {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th"};

            public:
                char teamName[32];
                int runs;
                int wickets;
                int balls;
                int runrate;
                int fallofwickets[MAX_WICKETS];
                BattingReport *firstBatsman;
                BowlingReport *firstBowler;
                InningsReport *next;

                InningsReport(const char * _teamName)
                {
                    strcpy(teamName, _teamName);
                    runs = 0;
                    wickets = 0;
                    balls = 0;
                    runrate = 0;
                    firstBatsman = nullptr;
                    firstBowler = nullptr;
                    next = nullptr;
                }

                void addNewBattingReport(BattingReport *batsman)
                {
                    if (firstBatsman == nullptr)
                    {
                        firstBatsman = batsman;
                    }
                    else
                    {
                        BattingReport *temp = firstBatsman;
                        while (temp->next != nullptr)
                        {
                            temp = temp->next;
                        }
                        temp->next = batsman;
                    }
                }

                void addNewBowlingReport(BowlingReport *bowler)
                {
                    if (firstBowler == nullptr)
                    {
                        firstBowler = bowler;
                    }
                    else
                    {
                        BowlingReport *temp = firstBowler;
                        while (temp->next != nullptr)
                        {
                            temp = temp->next;
                        }
                        temp->next = bowler;
                    }
                }

                void print(int inningsNumber)
                {
                    std::cout << "\n" << numbers[inningsNumber - 1] << " Innings (" << teamName << " Batting):\n";
                    std::cout << "Score: " << runs << "/" << wickets << " in " << balls/6 << "." << balls%6 << " overs.\n";
                    std::cout << "Run Rate: " << runrate / 100.0 << "\n";
                    std::cout << "Batting:\n";
                    BattingReport *batsman = firstBatsman;
                    for (int i = 0; batsman; batsman = batsman->next)
                    {
                        std::cout << std::setw(3);
                        batsman->print(++i);
                    }
                    std::cout << "Bowling:\n";
                    BowlingReport *bowler = firstBowler;
                    for (int i = 0; bowler; bowler = bowler->next)
                    {
                        std::cout << std::setw(3);
                        bowler->print(++i);
                    }
                    std::cout << "Fall of Wickets: ";
                    for (int i = 0; i < wickets; i++)
                    {
                        std::cout << i+1 << " - " << fallofwickets[i] << ", ";
                    }
                    std::cout << "\n";
                }

                ~InningsReport()
                {
                    BattingReport *batsman = firstBatsman;
                    while (batsman)
                    {
                        BattingReport *temp = batsman;
                        batsman = batsman->next;
                        delete temp;
                    }
                    BowlingReport *bowler = firstBowler;
                    while (bowler)
                    {
                        BowlingReport *temp = bowler;
                        bowler = bowler->next;
                        delete temp;
                    }
                }
        };

        class ScoreCard
        {
            public:
                char gameType[5];
                char result[64];
                InningsReport * firstInnings;

                void addNewInnings(InningsReport *innings)
                {
                    if (firstInnings == nullptr)
                    {
                        firstInnings = innings;
                    }
                    else
                    {
                        InningsReport *temp = firstInnings;
                        while (temp->next != nullptr)
                        {
                            temp = temp->next;
                        }
                        temp->next = innings;
                    }
                }

                void print()
                {
                    std::cout << "Scorecard:\n";
                    std::cout << "Game Type: " << gameType << "\n";
                    std::cout << "Result: " << result << "\n";
                    InningsReport *innings = firstInnings;
                    for (int i = 0; innings; innings = innings->next)
                    {
                        innings->print(++i);
                    }
                }

                ~ScoreCard()
                {
                    InningsReport *innings = firstInnings;
                    while (innings)
                    {
                        InningsReport *temp = innings;
                        innings = innings->next;
                        delete temp;
                    }
                }
        } scorecard;

    private:
        Team * team1;
        Team * team2;
        int * runmap;
        int overs;

        int t20_run_map[RUN_MAP_LENGTH] = {-1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 6, 6, 6, 6};
        int odi_run_map[RUN_MAP_LENGTH] = {-1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 4, 4, 4, 4, 4, 6, 6};
        int test_run_map[RUN_MAP_LENGTH] = {-1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 3, 4, 4, 4, 4, 6};

    public:
        CricketGame(Team * t1, Team * t2, gametype mode)
        {
            team1 = t1;
            team2 = t2;
            switch (mode)
            {
                case T20_GAME:
                    overs = 20;
                    runmap = t20_run_map;
                    strcpy(scorecard.gameType, "T20");
                    break;
                case ODI_GAME:
                    overs = 50;
                    runmap = odi_run_map;
                    strcpy(scorecard.gameType, "ODI");
                    break;
                case TEST_GAME:
                    overs = 450;
                    runmap = test_run_map;
                    strcpy(scorecard.gameType, "TEST");
                    break;
            }
        }

        int play()
        {
            int runs = 0;
            int wickets = 0;
            int oversLeft = overs;

            if (runmap == test_run_map)
            {
                playInnings(team2, team1, oversLeft, runs, wickets = 0, false);
                playInnings(team1, team2, oversLeft, runs = -runs, wickets = 0, false);

                if (runs > 0 && runs < 200 || runs < -200)
                {
                    Team * temp = team1;
                    team1 = team2;
                    team2 = temp;
                } else runs = -runs;
            }

            playInnings(team2, team1, oversLeft, runs, wickets = 0, false);
            if (runmap != test_run_map) oversLeft = overs;
            if (runmap == test_run_map && runs < 0)
            {
                declareResult(team2->getName() << " won by an innings and " << -runs << " runs.", -1);
            }
            playInnings(team1, team2, oversLeft, runs = -runs, wickets = 0, true);

            if (runs > 0)
            {
                declareResult(team2->getName() << " won by " << MAX_WICKETS - wickets << " wickets.", -1);
            }
            if (runs < 0)
            {
                declareResult(team1->getName() << " won by " << -runs << " runs.", 1);
            }
            declareResult("Match tied.", 0);
        }

        void startInnings(Team * battingTeam, Team * bowlingTeam, Team * _battingTeam, Team * _bowlingTeam)
        {
            for (int i = 0; i < TEAM_SIZE; ++i)
            {
                switch(_battingTeam->getRole(i))
                {
                    case Team::BATSMAN:
                        battingTeam->addBatsman(new Player(_battingTeam->getPlayer(i)->getName()), i);
                        break;
                    case Team::BOWLER:
                        battingTeam->addBowler(new Player(_battingTeam->getPlayer(i)->getName()), i);
                        break;
                    case Team::ALLROUNDER:
                        battingTeam->addAllRounder(new Player(_battingTeam->getPlayer(i)->getName()), i);
                        break;
                }
                switch(_bowlingTeam->getRole(i))
                {
                    case Team::BATSMAN:
                        bowlingTeam->addBatsman(new Player(_bowlingTeam->getPlayer(i)->getName()), i);
                        break;
                    case Team::BOWLER:
                        bowlingTeam->addBowler(new Player(_bowlingTeam->getPlayer(i)->getName()), i);
                        break;
                    case Team::ALLROUNDER:
                        bowlingTeam->addAllRounder(new Player(_bowlingTeam->getPlayer(i)->getName()), i);
                        break;
                }
            }
        }

        void playInnings(Team * _bowlingTeam, Team * _battingTeam, int& oversLeft, int& runDifference, int& wickets, int isFinalInnings)
        {
            Team * battingTeam = new Team(_battingTeam->getName());
            Team * bowlingTeam = new Team(_bowlingTeam->getName());
            startInnings(battingTeam, bowlingTeam, _battingTeam, _bowlingTeam);
            std::cout << "\nNew Innings: " << bowlingTeam->getName() << " is bowling and " << battingTeam->getName() << " is batting.\n";
            int runs = 0;
            int balls = 0;
            int bowlerIndex = -1;
            int batsmanIndex = -1;
            InningsReport * innings = new InningsReport(battingTeam->getName());
            Player * bowler = bowlingTeam->selectBowler(bowlerIndex, overs/5);
            Player * striker = battingTeam->selectBatsman(batsmanIndex);
            Player * nonStriker = battingTeam->selectBatsman(batsmanIndex);
            while (balls/6 < oversLeft && wickets < MAX_WICKETS && (!isFinalInnings || runDifference <= 0))
            {
                std::cout << "Over " << std::setw(3) << balls/6 << "( " << std::left << std::setw(20) << bowler->getName() << std::right << " ): ";
                do {
                    int run = bowler->bowl(runmap);
                    striker->batTo(run);
                    runs += run == -1 ? 0 : run;
                    runDifference += run == -1 ? 0 : run;
                    ++balls;
                    std::cout << std::setw(3) << run;
                    if (isFinalInnings && runDifference > 0)
                    {
                        break;
                    }
                    if (run == -1)
                    {
                        innings->fallofwickets[wickets] = runs;
                        if (++wickets == MAX_WICKETS)
                        {
                            break;
                        }
                        striker = battingTeam->selectBatsman(batsmanIndex);
                    }
                    else if(run % 2 == 1)
                    {
                        Player * temp = striker;
                        striker = nonStriker;
                        nonStriker = temp;
                    }
                } while (balls % 6 != 0);
                Player *temp = striker;
                striker = nonStriker;
                nonStriker = temp;
                bowler = bowlingTeam->selectBowler(bowlerIndex, overs/5);
                std::cout << " - " << runs << "/" << wickets << " - b" << bowlerIndex << " - ";
                std::cout << striker->getName() << "(" << striker->getRunsScored() << "/" << striker->getBallsFaced() << ")" << "     ";
                std::cout << nonStriker->getName() << "(" << nonStriker->getRunsScored() << "/" << nonStriker->getBallsFaced() << ")\n";
                if (runmap == test_run_map && (oversLeft - balls/6) % 90 == 0)
                {
                    std::cout << "Stumps on Day " << 5 - (oversLeft - balls/6)/90 << " : "; 
                    std::cout << battingTeam->getName() << " is " << (runDifference > 0 ? "leading" : "trailing") << " by " << (runDifference > 0 ? runDifference : -runDifference) << " runs.\n\n";
                }
            }
            oversLeft -= balls/6;
            std::cout << "End of Innings: " << battingTeam->getName() << " scored " << runs << " runs for " << wickets << " wickets.\n";
            if (runmap == test_run_map)
            {
                std::cout << battingTeam->getName() << " is " << (runDifference > 0 ? "leading" : "trailing") << " by " << (runDifference > 0 ? runDifference : -runDifference) << " runs.\n\n";
            } else std::cout << "\n";
            endInnings(innings, runs, wickets, balls, nonStriker, striker, battingTeam, bowlingTeam, _battingTeam, _bowlingTeam);
            delete battingTeam;
            delete bowlingTeam;
        }

        void endInnings(InningsReport * innings, int runs, int wickets, int balls, Player * striker, Player * nonStriker, Team * battingTeam, Team * bowlingTeam, Team * _battingTeam, Team * _bowlingTeam)
        {
            nonStriker->Batsman::endInnings();
            if (wickets < MAX_WICKETS)
            {
                striker->Batsman::endInnings();
            }
            innings->runs = runs;
            innings->wickets = wickets;
            innings->balls = balls;
            innings->runrate = runs * 600.0 / balls;
            for (int i = 0; i < TEAM_SIZE; ++i)
            {
                if (bowlingTeam->getRole(i) == Team::gamerole::BOWLER || bowlingTeam->getRole(i) == Team::gamerole::ALLROUNDER)
                {
                    Player *player = bowlingTeam->getPlayer(i);
                    BowlingReport *bowler = new BowlingReport(player->getName());
                    bowler->balls = player->getBallsBowled();
                    bowler->runs = player->getRunsGiven();
                    bowler->wickets = player->getWicketsTaken();
                    bowler->maidens = player->getMaidenOvers();
                    innings->addNewBowlingReport(bowler);
                    _bowlingTeam->getPlayer(i)->updateStatisticsFrom(*player);
                }
                Player * player = battingTeam->getPlayer(i);
                BattingReport *batsman = new BattingReport(player->getName());
                batsman->runs = player->getRunsScored();
                batsman->balls = player->getBallsFaced();
                batsman->fours = player->getFours();
                batsman->sixes = player->getSixes();
                batsman->notOut = player->getNotOuts();
                innings->addNewBattingReport(batsman);
                _battingTeam->getPlayer(i)->updateStatisticsFrom(*player);
            }
            scorecard.addNewInnings(innings);
        }

        void printScorecard()
        {
            scorecard.print();
        }

        void printPerformances()
        {
            std::cout << "\nPerformances for Team " << team1->getName() << ":\n";
            for (int i = 0; i < TEAM_SIZE; ++i)
            {
                team1->getPlayer(i)->printStats();
            }
            std::cout << "\nPerformances for Team " << team2->getName() << ":\n";
            for (int i = 0; i < TEAM_SIZE; ++i)
            {
                team2->getPlayer(i)->printStats();
            }
        }
};

class BilateralSeries
{
    private:
        Team * team1;
        Team * team2;
        unsigned char t1score : 4;
        unsigned char t2score : 4;
        CricketGame::gametype mode;

    public:
        enum matches
        {
            CANCELLED,
            LONE_GAME,
            TWO_GAMES,
            THREE_GAMES,
            FOUR_GAMES,
            FIVE_GAMES,
            SIX_GAMES,
            SEVEN_GAMES
        } num_matches;

        BilateralSeries(Team * t1, Team * t2, matches _num_matches, CricketGame::gametype _mode)
        {
            team1 = t1;
            team2 = t2;
            num_matches = _num_matches;
            mode = _mode;
            t1score = 0;
            t2score = 0;
        }

        void play()
        {
            for (int i = 0; i < num_matches; ++i)
            {
                std::cout << "\n\nMatch " << i+1 << " of " << num_matches << ":\n";
                CricketGame game(team1, team2, mode);
                int result = game.play();
                if (result == 1)
                {
                    t1score += 2;
                }
                else if (result == -1)
                {
                    t2score += 2;
                }
                else
                {
                    ++t1score;
                    ++t2score;
                }
                game.printScorecard();
            }
            if (t1score > t2score)
            {
                std::cout << "\n\n\n" << team1->getName() << " won the series " << t1score/2.0 << " - " << t2score/2.0 << ".\n";
            }
            else if (t1score < t2score)
            {
                std::cout << "\n\n\n" << team2->getName() << " won the series " << t2score/2.0 << " - " << t1score/2.0 << ".\n";
            }
            else
            {
                std::cout << "\n\n\n" << "Series tied " << t1score/2.0 << " - " << t2score/2.0 << ".\n";
            }
        }

        ~BilateralSeries()
        {
            delete team1;
            delete team2;
        }
};

class Tournament
{
    private:
        Team * teams[4];
        CricketGame::gametype mode;

    public:
        Tournament(CricketGame::gametype _mode, std::string team1, std::string team2, std::string team3, std::string team4)
        {
            mode = _mode;
            teams[0] = Team::fromFile(team1);
            teams[1] = Team::fromFile(team2);
            teams[2] = Team::fromFile(team3);
            teams[3] = Team::fromFile(team4);
        }

        void play()
        {
            CricketGame semifinal1(teams[0], teams[1], mode);
            int result1 = semifinal1.play();
            Team * finalist1 = result1 == 1 ? teams[0] : teams[1];
            Team * loser1 = result1 == 1 ? teams[1] : teams[0];
            std::cout << "\n\n\n" << finalist1->getName() << " won the first semifinal.\n";
            std::cout << loser1->getName() << " will fight for third place.\n\n";
            CricketGame semifinal2(teams[2], teams[3], mode);
            int result2 = semifinal2.play();
            Team * finalist2 = result2 == 1 ? teams[2] : teams[3];
            Team * loser2 = result2 == 1 ? teams[3] : teams[2];
            std::cout << "\n\n\n" << finalist2->getName() << " won the second semifinal.\n";
            std::cout << loser2->getName() << " will fight for third place.\n\n";
            CricketGame final(finalist1, finalist2, mode);
            int finalwinner = final.play();
            Team * winner = finalwinner == 1 ? finalist1 : finalist2;
            Team * runnerup = finalwinner == 1 ? finalist2 : finalist1;
            std::cout << "\n\n\n" << winner->getName() << " won the final.\n";
            CricketGame thirdplace(loser1, loser2, mode);
            int thirdplacewinner = thirdplace.play();
            Team * thirdplacefinisher = thirdplacewinner == 1 ? loser1 : loser2;
            Team * fourthplacefinisher = thirdplacewinner == 1 ? loser2 : loser1;
            std::cout << "\n\n\n" << thirdplacefinisher->getName() << " won the third place match.\n";
            std::cout << "\n\n\n" << winner->getName() << " won the tournament.\n";
            std::cout << runnerup->getName() << " were the runners-up.\n";
            std::cout << thirdplacefinisher->getName() << " finished third.\n";
            std::cout << fourthplacefinisher->getName() << " finished fourth.\n";
        }

        void showLineups()
        {
            std::cout << "\n\nCompeting Teams:\n";
            for (int i = 0; i < 4; i++)
            {
                std::cout << "\n\n" << teams[i]->getName() << ":\n";
                for (int j = 0; j < TEAM_SIZE; j++)
                {
                    std::cout << teams[i]->getPlayer(j)->getName() << "(" << teams[i]->getRole(j) << ")\n";
                }
            }
        }

        ~Tournament()
        {
            for (int i = 0; i < 4; i++)
            {
                delete teams[i];
            }
        }
};

void testGame(CricketGame::gametype mode)
{
    Team * India = Team::fromFile("India");
    Team * Australia = Team::fromFile("Australia");
    std::cout << "\nIndia Team:\n";
    for (int i = 0; i < TEAM_SIZE; i++)
    {
        std::cout << "  " << India->getPlayer(i)->getName() << "(" << India->getRole(i) << ")" << "\n";
    }
    std::cout << "\nAustralia Team:\n";
    for (int i = 0; i < TEAM_SIZE; i++)
    {
        std::cout << "  " << Australia->getPlayer(i)->getName() << "(" << Australia->getRole(i) << ")" << "\n";
    }
    CricketGame game(Australia, India, mode);
    game.play();
    game.printScorecard();
    game.printPerformances();
    delete India;
    delete Australia;
}

void testSeries(BilateralSeries::matches num_matches, CricketGame::gametype mode)
{
    Team * India = Team::fromFile("India");
    Team * Australia = Team::fromFile("Australia");
    std::cout << "India Team:\n";
    for (int i = 0; i < TEAM_SIZE; i++)
    {
        std::cout << India->getPlayer(i)->getName() << "(" << India->getRole(i) << ")" << "\n";
    }
    std::cout << "Australia Team:\n";
    for (int i = 0; i < TEAM_SIZE; i++)
    {
        std::cout << Australia->getPlayer(i)->getName() << "(" << Australia->getRole(i) << ")" << "\n";
    }
    BilateralSeries series(India, Australia, num_matches, mode);
    series.play();
}

void testTournament(CricketGame::gametype mode, std::string team1, std::string team2, std::string team3, std::string team4)
{
    Tournament tournament(mode, team1, team2, team3, team4);
    tournament.showLineups();
    tournament.play();
}

int main() 
{
    srand(time(0));
    testGame(CricketGame::ODI_GAME);
    // testSeries(BilateralSeries::LONE_GAME, CricketGame::T20_GAME);
    // testTournament(CricketGame::T20_GAME, "India", "Australia", "England", "SouthAfrica");
    return 0;
}