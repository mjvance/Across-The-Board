/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>

using namespace std;

int rollDice()
{
    int dieOneRolledValue = (rand() % 6) + 1;
    int dieTwoRolledValue = (rand() % 6) + 1;
    int diceSum = dieOneRolledValue + dieTwoRolledValue;
    
    //cout << "Dice Rolled!!! " << dieOneRolledValue << " and " << dieTwoRolledValue << " advance horse " << diceSum << endl;
    //cout << dieOneRolledValue + dieTwoRolledValue << endl; // Verify dice statistics

    return dieOneRolledValue + dieTwoRolledValue;
}

int main()
{
    const int racesToRun = 100000;
    const int horsesToScratch = 4;
    bool highStakes = false;
    
    enum PrintLevel
    {
        summary,
        stats
    };
    
    int printLevel = stats;

    srand(time(NULL));

    const int numHorses = 11;
    
    const int rollsToWin[numHorses] = 
    {
        3,  // 2
        6,  // 3
        8,  // 4
        11, // 5
        14, // 6
        17, // 7
        14, // 8
        11, // 9
        8,  // 10
        6,  // 11
        3   // 12
    };
    
    int horsePosition[numHorses];
    int timesWon[numHorses];
    for(int horseIndex = 0; horseIndex < numHorses; horseIndex++)
    {
        horsePosition[horseIndex] = 0;
        timesWon[horseIndex] = 0;
    }
    
    int racesRun = 0;
    int potSize = 0;
    
    while(racesRun < racesToRun)
    {
        bool winner = false;
        int winningHorseNumber = 0;
        
        // Scratch horses
        
        int horsesScratched = 0;
        if(horsesToScratch >= numHorses)
        {
            cout << "Must race at least one horse!" << endl;
            return -1;
        }
        
        while(horsesScratched < horsesToScratch)
        {
            int rolledDiceSum = rollDice();
            int scratchedHorseIndex = (rolledDiceSum - 2);
    
            if((horsePosition[scratchedHorseIndex]) == 0)
            {
                horsesScratched += 1;
                horsePosition[scratchedHorseIndex] -= horsesScratched;
                
                potSize += (highStakes ? (horsesScratched * 4) : 4);
            }
            else
            {
                if(highStakes)
                {
                    potSize -= horsePosition[scratchedHorseIndex];
                }
                else
                {
                    potSize += 1;
                }
            }
        }

        // Begin the race!!!

        while(!winner)
        {
            // Roll the dice!
            int rolledDiceSum = rollDice();
            int rolledHorseIndex = (rolledDiceSum - 2);
            
            // Advance the horse if it is not scratched
            if((horsePosition[rolledHorseIndex]) >= 0)
            {
                horsePosition[rolledHorseIndex] += 1;
                if(horsePosition[rolledHorseIndex] == rollsToWin[rolledHorseIndex])
                {
                    winningHorseNumber = rolledDiceSum;
                    winner = true;
                }
            }
            else
            {
                if(highStakes)
                {
                    potSize -= horsePosition[rolledHorseIndex];
                }
                else
                {
                    potSize += 1;
                }
            }
        }
        
        if(printLevel == summary)
        {
            cout << endl << "Winning Horse Number = " << winningHorseNumber << "!!!" << endl << endl;
        }
        else if(printLevel == stats)
        {
            cout << winningHorseNumber;
        }
        
        for(int horseIndex = 0; horseIndex < numHorses; horseIndex++)
        {
            if(printLevel == summary)
            {
                int horseNum = horseIndex + 2;
                
                if(horseNum == winningHorseNumber)
                {
                    cout << "Horse " << horseNum << " won the race!!!" << endl;
                }
                else if(horsePosition[horseIndex] >= 0)
                {
                    cout << "Horse " << horseNum << " finished " << rollsToWin[horseIndex] - horsePosition[horseIndex] << " rolls away from the line!" << endl;
                }
                else
                {
                    cout << "Horse " << horseNum << " was scratched! (" << horsePosition[horseIndex] << ")" << endl;
                }
            }
            
            // Reset the horses!
            horsePosition[horseIndex] = 0;
        }
        
        if(printLevel == summary)
        {
            cout << "Total pot size for this race was " << potSize << "!!!" << endl;
        }
        else if(printLevel == stats)
        {
            cout << "\t" << potSize << endl;
        }
        
        potSize = 0;
        racesRun++;
    }

    return 0;
}
