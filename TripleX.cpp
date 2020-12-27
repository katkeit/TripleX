#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// Prototypes
void MenuOptions(int OptionNum);
void PlayGame(int SetDifficulty, int DoTutorial);
bool RunGame(int Rounds, int Difficulty, int IncreaseDifficulty, bool LimitedTries, int MaxTries, string Mode);

int main()
{
    int UserOption;

    // Seed rand to system's time.
    srand(time(NULL));

    // Loop through the menu options.
    do
    {
        cout << "Welcome to TripleX!\n\n";
        cout << "Select a menu option.\n";
        cout << "1. Play\n";
        cout << "2. Info\n";
        cout << "3. Exit\n";

        cin >> UserOption;

        // User inputs a menu option between 1-3, otherwise will be prompted to try again.
        while(!cin || UserOption < 1 || UserOption > 3) // cin will trigger fail (1) when input cannot be converted to int.
        {
            cin.clear();
            cin.ignore();

            cout << "Please reselect a menu option as a number.\n";
            cin >> UserOption;
        }
        
        MenuOptions(UserOption);

    } while (UserOption != 3);  // Option 3 closes the game.

    return 0;
}

// Performs what menu option the user selected.
void MenuOptions(int OptionNum)
{
    int Difficulty, DoTutorial;

    switch(OptionNum)
    {
        case 1: // Play TripleX
        {
            cout << "\nSelect your difficulty to start at?\n";
            cout << "1. Easy\n";
            cout << "2. Normal\n";
            cout << "3. Hard\n";

            cin >> Difficulty;

            while(!cin || Difficulty < 1 || Difficulty > 3)
            {
                cin.clear();
                cin.ignore();

                cout << "Please reselect the difficulty as a number.\n";
                cin >> Difficulty;
            }

            cout << "\nDo you wish to start the tutorial? (Recommended for beginner players)\n";
            cout << "1. Yes\n";
            cout << "2. No \n";

            cin >> DoTutorial;

            while(!cin || DoTutorial < 1 || DoTutorial > 2)
            {
                cin.clear();
                cin.ignore();

                cout << "Please reselect whether to skip the tutorial or not.\n";
                cin >> DoTutorial;
            }

            PlayGame(Difficulty, DoTutorial);
            break;
        }
        case 2: // Give information on TripleX
        {
            cout << "Information:\n\n";
            cout << "TripleX is a number game that will give you hints to help you solve the puzzle. There are multiple rounds and you only have so many tries.\n";
            cout << "Need help? Try out the tutorial! To access the tutorial, play the game, set your difficulty, and select yes for the tutorial!";
            break;
        }
        default: // All else fails, push terminal message.
        {
            if(OptionNum != 3)
                cout << "Menu option not recognized! Option: " << OptionNum << endl;
            break;
        }
    }
}

// Sets up the game's settings and starts the game.
void PlayGame(int SetDifficulty, int DoTutorial)
{
    // Tutorial settings.
    const int TutorialMaxRounds = 2;
    const int TutorialDifficulty = 4;
    const int TutorialMaxTries = 1;

    // General settings.
    const int MaxRounds = 5;
    const int IncreaseDifficulty = 2;
    const int MaxTries = 5;

    // Mode settings.
    const int EasyDifficulty = 5;
    const int NormalDifficulty = 7;
    const int HardDifficulty = 10;

    bool IsCompleted; // Is the game completed?

    if(DoTutorial == 1) // Option 1 for starting tutorial.
    {
        cout << "\nWelcome to the tutorial!\n";
        cout << "During the tutorial, you will have two rounds and unlimited tries. This will give you the opporunity to understand the game.\n\n";
        
        RunGame(TutorialMaxRounds, TutorialDifficulty, IncreaseDifficulty, false, TutorialMaxTries, "Tutorial");

        cout << "\nCongratulations on completing the tutorial! The real game is about to begin!\n";
    }

    if(SetDifficulty == 1)
        IsCompleted = RunGame(MaxRounds, EasyDifficulty, IncreaseDifficulty, true, MaxTries, "Easy");
    else if (SetDifficulty == 2)
        IsCompleted = RunGame(MaxRounds, NormalDifficulty, IncreaseDifficulty, true, MaxTries, "Normal");
    else
        IsCompleted = RunGame(MaxRounds, HardDifficulty, IncreaseDifficulty, true, MaxTries, "Hard");
    
    if(IsCompleted)
        cout << "CONGRATULATIONS! You have successfully beat the game!\n\n";
    else
        cout << "Better luck next time! Consider trying the tutorial or playing the game on an easier difficulty.\n\n";
}

// Run the game according the game's settings.
bool RunGame(int Rounds, int Difficulty, int IncreaseDifficulty, bool LimitedTries, int MaxTries, string Mode)
{
    int NumberA, NumberB, NumberC;
    int Guess1, Guess2, Guess3;
    int Sum, Product, GuessSum, GuessProduct;
    int Tries = MaxTries;

    bool HasWon = true;
    
    cout << "\nWelcome to TripleX!\n";
    cout << "Let's play!\n\n";


    for(int i = 1; i <= Rounds; i++)
    {
        cout << "-- Difficulty: " << Mode << "\t -- Level: " << i << " / " << Rounds << "\t -- Tries: " << Tries << endl << endl;

        NumberA = (rand() % Difficulty) + i;
        NumberB = (rand() % Difficulty) + i;
        NumberC = (rand() % Difficulty) + i;
        

        Sum = NumberA + NumberB + NumberC;
        Product = NumberA * NumberB * NumberC;

        cout << "Hints:\n";
        cout << "The sum of the three numbers is: " << Sum << endl;
        cout << "The product of the three numbers is: " << Product << endl << endl;
        cout << "Type in your three guesses in the following format: # # # (1 1 1)\n";

        do
        {
            cin >> Guess1;
            cin >> Guess2;
            cin >> Guess3;

            GuessSum = Guess1 + Guess2 + Guess3;
            GuessProduct = Guess1 * Guess2 * Guess3;

            if(!cin)
                cout << "\nGuesses were typed in an incorrect format!\n";
            else if(GuessSum != Sum || GuessProduct != Product)
            {
                if(Mode != "Tutorial")
                {
                    Tries -= 1;
                    cout << "\nTry again! Remaining tries: " << Tries << endl;
                }
                else
                    cout << "\nTry again! You can do it!\n";
            }   

            cin.clear();
            cin.ignore();

        } while ((GuessSum != Sum || GuessProduct != Product) && Tries > 0);
        
        
        if(GuessSum == Sum && GuessProduct == Product)
        {
            cout << "\nGood job! You got the correct answer!\n\n";
            Difficulty += IncreaseDifficulty;
        }

        if(Tries <= 0)
            HasWon = false;
    }

    return HasWon;
}