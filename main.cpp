#include <iostream>
#include <ctime>
#include <cstdlib>

size_t STRING_SIZE = 128;


    int dealerReveal(char** Doors, int choice) {
         srand(time(NULL));
         choice--;
         int dealerChoice = rand() % 3;
         while ((dealerChoice == choice) || !strcmp(Doors[dealerChoice], "Car")) {
            dealerChoice = rand() % 3;
    }

    return dealerChoice;
}
    void shuffle(char** Doors, int n) {

        char* temp = (char*)malloc(STRING_SIZE);
        srand(time(NULL));
        for (int i = n - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            strcpy_s(temp, STRING_SIZE, Doors[i]);
            strcpy_s(Doors[i], STRING_SIZE, Doors[j]);
            strcpy_s(Doors[j], STRING_SIZE, temp);
        }
        free(temp);
    };

    void printDoors(char** Doors) {
        std::cout << Doors[0] << " " << Doors[1] << " " << Doors[2] << "\n";
    };

    void chooseDoors(char** Doors, float* wins, float* losses) {
        int choice, y_Or_n, tempchoice, dealerChoice;
        std::cout << "Pick a door 1, 2, or 3.\n"
            << "There is a Goat behind two of the doors," <<
            " and a car behind one of them.\n";
        std::cin >> choice;
        tempchoice = choice;

        while (choice != 1 && choice != 2 && choice != 3) {
            std::cout << "Enter a Valid Number (1, 2, or 3).\n";
            std::cin >> choice;
        }
        dealerChoice = dealerReveal(Doors, choice); 
        std::cout << "You chose Door " << choice << " There is a " << Doors[dealerChoice] 
            << " behind Door " << dealerChoice+1 << " Would you like to switch to the other door, " 
            << "or stick with the one you have?\n" << "Choose '1' to Switch, and '2' to Stay: ";
        std::cin >> y_Or_n;
        while (y_Or_n != 1 && y_Or_n != 2) {
            std::cout << "\nPlease choose a valid selectiong ('1' or '2').\n";
            std::cin >> y_Or_n;
        }
        if (y_Or_n == 1) {
            for (choice = 0; choice == (tempchoice-1) || choice == dealerChoice; choice++) {};
            std::cout << "You chose to switch to Door " << choice+1
                << " there is a " << Doors[choice] 
                << " behind that door.";
            if (strcmp(Doors[choice], "Car")) {
                (*losses)++;
            }
            else {
                (*wins)++;
            }
        }
        else {
            std::cout << "You chose to stay with Door " << choice
                << " there is a " << Doors[choice-1] << " behind that door.";
            if (strcmp(Doors[choice-1], "Car")) {
                (*losses)++;
            }
            else {
                (*wins)++;
            }
        }
    }

    void Percentage(float* wins, float* losses) {
        float winpercentage, losspercentage;
        float total = *wins + *losses;
        winpercentage = ((*wins) / total) * 100;
        losspercentage = ((*losses) / total) * 100;
        std::cout << "\nWin Percentage: " << winpercentage << "%";
        std::cout << "\nLoss Percentage: " << losspercentage << "%";
    }


int main(int argc, char* argv[])
{
    int quit;
    float wins, losses;
    wins = 0;
    losses = 0;
    char** Doors = new char* [3];
    for (size_t i = 0; i < 3; ++i)
    {
        Doors[i] = (char*)malloc(STRING_SIZE);
    }
    strcpy_s(Doors[0], STRING_SIZE, "Car");
    strcpy_s(Doors[1], STRING_SIZE, "Goat");
    strcpy_s(Doors[2], STRING_SIZE, "Goat");

    std::cout << "The Purpose of this project is to prove the Monte Hall Problem.\n"
        << "The more you play the more it proves the statistics.\n\n";

    do {
        shuffle(Doors, 3);
        chooseDoors(Doors, &wins, &losses);
        std::cout << "\nWins: " << wins;
        std::cout << "\nLosses: " << losses;
        Percentage(&wins, &losses);
        std::cout << "\n\nWould you like to play again?\n"
            << "Press '1' to quit or '2'to play again: ";
        std::cin >> quit;
        while (quit != 1 && quit != 2) {
            std::cout << "\nChoose a valid selection: ";
            std::cin >> quit;
        }
        system("cls");
    } while (quit != 1);
    for (size_t i = 0; i < 3; ++i)
    {
        delete Doors[i];
    }

    return 0;
}
