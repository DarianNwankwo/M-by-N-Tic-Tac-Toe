//
//  main.cpp
//  MbyN_Tic_Tac_Toe
//
//  Created by Darian Nwankwo on 2/9/16.
//  Copyright © 2016 Darian Nwankwo. All rights reserved.
//

#include <iostream>
#include <string>
#include <iomanip>
#include "player.hpp"
#define ASCII_ALPHABET_OFFSET 65
#define ASCII_UPPERCASE -32

const int MIN_PLAYERS = 2, MAX_PLAYERS = 9,
          MAX_ROWS = 27, MAX_COLUMNS = 50,
          MIN_ROWS = 3, MIN_COLUMNS = 3,
          LOWERCASE = 32, A_SPACE = 32;

void introduction();
int howManyPlayers();
int stoin(std::string);
int pow(int, int);
std::string *playerName(int);
void formatName(std::string &);
bool isEmpty(std::string);
int getRowAmount(std::string &);
int getColumnAmount(std::string &);
void displayBoardConstraints();
void displayBoard(std::string [][MAX_COLUMNS], int, int);
int getPlayerDecision(std::string [][MAX_COLUMNS], int, int, Player [], int);
void clearBoard(std::string [][MAX_COLUMNS], int, int);
void print(std::string, int);
void displayInputConstraints();
void to_upper(char &);
int aWinner(std::string [][MAX_COLUMNS], int, int, Player [], int, int, int, int);
void displayStatistics(Player [], int, int);
int longestName(Player [], int);
bool playAgain();
bool verticalWin(std::string [][MAX_COLUMNS], int, int, int &, int, int);
bool horizontalWin(std::string [][MAX_COLUMNS], int, int, int &, int, int);
bool diagonalWin(std::string [][MAX_COLUMNS], int, int, int &, int, int);


int main() {
    int games_played = 0;
    introduction();
    int amount_of_players = howManyPlayers();
    Player *user_number = new Player[amount_of_players];
    std::string player_inputs[MAX_ROWS][MAX_COLUMNS];
    
    std::string *name = nullptr;
    char piece = 'a';
    for (int user = 0; user < amount_of_players; user++) {
        name = playerName(user);
        formatName(name[0]);
        formatName(name[1]);
        user_number[user].setFirstName(name[0]);
        user_number[user].setLastName(name[1]);
        user_number[user].setPiece( char(piece + user) );
        std::cout << user_number[user].getFirstName() << "'s piece ==> " << user_number[user].getPiece() << std::endl;
        
        if (user == 0) {
            user_number[user].goesFirst();
        } else {
            user_number[user].doesNotGoFirst();
        }
        
    }
    
    int winner;
    int rows, cols;
    std::string r, c;
    do {
        do {
            displayBoardConstraints();
            rows = getRowAmount(r);
            cols = getColumnAmount(c);
        } while (rows < MIN_ROWS || rows > MAX_ROWS ||
                cols < MIN_COLUMNS || cols > MAX_COLUMNS);
        
        clearBoard(player_inputs, rows, cols);
        do {
            displayBoard(player_inputs, rows, cols);
            displayInputConstraints();
            winner = getPlayerDecision(player_inputs, rows, cols, user_number, amount_of_players);
        } while (winner == -1);
        displayBoard(player_inputs, rows, cols);
        games_played++;
        displayStatistics(user_number, amount_of_players, games_played);
    } while (playAgain());

    
    return 0;
}

/**
 Explains the game to the users
 */
void introduction() {
    std::cout << "This program will allow up to " << MAX_PLAYERS << " players, but no less than\n"
              << MIN_PLAYERS << " players, to play a game of your specified size of Tic-Tac-Toe.\n"
              << "Each player will be assigned a piece upon entering his/her name. Enjoy!\n" <<
    std::endl;
}

/**
 Returns the number of users that are playing the board game
*/
int howManyPlayers() {
    std::string players = "";
    do {
        std::cout << "Enter the amount of players. Input must be in between " << MIN_PLAYERS
                  << " and " << MAX_PLAYERS << ": ";
        std::getline(std::cin, players);
    } while (stoin(players) < MIN_PLAYERS || stoin(players) > MAX_PLAYERS);
    
    return stoin(players);
}

/**
 Converts strings into integers
 
 @param string
 */

int stoin(std::string num) {
    bool isNum = true;
    int number = 0, ndx;
    
    for (ndx = 0; ndx < num.length(); ndx++) {
        if (num[ndx] < '0' || num[ndx] > '9') {
            isNum = false;
        }
    }
    
    if (isNum) {
        for (ndx = 0; ndx < num.length(); ndx++) {
            number += (num[ndx] - '0') * pow(10, num.length() - (ndx + 1));
        }
    } else {
        number = -1;
    }
    
    return number;
}

/**
 Raises a base to the exponent power
 
 @param int - base number
 @param int - exponent
 */
int pow(int base, int exp) {
    int result = 1, counter = 1;
    
    while (counter <= exp) {
        result *= base;
        counter++;
    }
    
    return result;
}

/**
 Returns a memory address that points to the users first and last name
 */
std::string *playerName(int player_number) {
    std::string *full_name = new std::string[2];
    do {
        std::cout << "Enter player " << (player_number + 1) << "'s full name: ";
        std::cin >> full_name[0];
        std::cin.ignore();
        std::getline(std::cin, full_name[1]);
    } while(isEmpty(full_name[1]));
    
    return full_name;
}

/**
 Formats a string with the first value in each name capitalized
 ex: "kHeNSU-ra Love el" ==> "Khensu-ra Love El"
 
 @param string - a name
 */
void formatName(std::string &name) {
    int num_of_chars = name.length();
    
    if (name[0] >= 'a' && name[0] <= 'z') {
        name[0] = name[0] - LOWERCASE;
    }
    
    for (int ndx = 1; ndx < num_of_chars; ndx++) {
        if ((name[ndx] >= 'A' && name[ndx] <= 'Z') && name[ndx - 1] != A_SPACE) {
            name[ndx] = name[ndx] + LOWERCASE;
        } else if ((name[ndx] >= 'a' && name[ndx] <= 'z') && name[ndx - 1] == A_SPACE) {
            name[ndx] = name[ndx] - LOWERCASE;
        }
    }
    
}

/**
 Determines if a string contains only spaces
 
 @param string - a phrase or word
 */
bool isEmpty(std::string word) {
    bool onlySpaces = true;
    
    for (int ndx = 0; ndx < word.length(); ndx++) {
        if (word[ndx] != A_SPACE) {
            onlySpaces = false;
        }
    }
    
    return onlySpaces;
}

/**
 Retrieves the number of rows for the game board from the user
 */
int getRowAmount(std::string &r) {
    std::cout << "Enter the number of rows: ";
    std::getline(std::cin, r);
    
    return stoin(r);
}

/**
 Retrieves the number of rcolumns for the game board from the user
 */
int getColumnAmount(std::string &c) {
    std::cout << "Enter the number of columns: ";
    std::getline(std::cin, c);
    
    return stoin(c);
}

/**
 Displays the constraints that the game board has in its configuration
 */
void displayBoardConstraints() {
    std::cout << "\nThe game board can only have a maximum of " << MAX_ROWS << " rows and a minimum of " << MIN_ROWS << "." << std::endl;
    std::cout << "The game board is also restricted to a maximum of " << MAX_COLUMNS << " columns and a minimum of " << MIN_COLUMNS << "." << std::endl;
}

/**
 Clears the board
 
 @param char [][] - an array of inputs for the game board
 @param int - the amount of rows in the game board
 @param int - the amount of cols in the game board
 */
void clearBoard(std::string inputs[][MAX_COLUMNS], int rows, int columns) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            inputs[r][c] = " ";
        }
    }
}

/**
 Displays the game board
 
 @param char [][] - an array of inputs for the game board
 @param int - the amount of rows in the game board
 @param int - the amount of cols in the game board
 */
void displayBoard(std::string inputs[][MAX_COLUMNS], int rows, int columns) {
    int x_axis = 1, y_axis = 'A';
    std::string dashes = " ---", v_bar = "";
    
    std::cout << std::endl;
    for (int col = 0; col < columns; col++) {
        if (col == 0) {
            std::cout << std::setw(5) << (x_axis);
        }
        else if ((col >= 1 && col <= 8) || col > 9) {
            std::cout << "" << std::setw(4) << (x_axis + col);
        } else if (col == 9) {
            std::cout << "" << std::setw(5) << (x_axis + col);
        }
    }
    std::cout << std::endl << "  ";
    print(dashes, columns);
    
    
    for (int row = 0; row < rows; row++) {
        if (row > 0) {
            std::cout << "  ";
            print(dashes, columns);
        }
        if (row >= 0 && row <= rows) {
            std::cout << char(y_axis + row) << " ";
        }
        for (int col = 0; col < columns; col++) {
            v_bar = "| " + inputs[row][col] + " ";
            if (row <= rows) {
                std::cout << v_bar;
            }
        }
    
        if (row >= 0 && row <= rows) {
            std::cout << "| " << char(y_axis + row);
        }
        std::cout << std::endl;

    }
    std::cout << "  ";
    print(dashes, columns);
    for (int col = 0; col < columns; col++) {
        if (col == 0) {
            std::cout << std::setw(5) << (x_axis);
        }
        else if ((col >= 1 && col <= 8) || col > 9) {
            std::cout << "" << std::setw(4) << (x_axis + col);
        } else if (col == 9) {
            std::cout << "" << std::setw(5) << (x_axis + col);
        }
    }
    print("\n", 1);
}

/**
 Prints the first argument second argument amount of times
 
 @param string - any string
 @param int - the number of times to print the string sequentially
 */
void print(std::string word, int times) {
    for (int i = 0; i < times; i++) {
        std::cout << word;
    }
    std::cout << std::endl;
}

/**
 Retrieves the player's decision for the game board
 
 @param char [][] - an array of inputs for the game board
 @param int - the amount of rows in the game board
 @param int - the amount of cols in the game board
 */
int getPlayerDecision(std::string inputs[][MAX_COLUMNS], int rows, int columns, Player player_num[], int peeps) {
    static int once = 1, user_turn_ndx = -1, starter = 0;
    int isWinner = -1;
    
    if (once == 1) {
        for (int i = 0; i < peeps; i++) {
            if (player_num[i].isFirst()) {
                user_turn_ndx = i;
                starter = i;
            } else {
                player_num[i].doesNotGoFirst();
            }
        }
    } else if (once > 1) {
        if (user_turn_ndx == (peeps - 1)) {
            user_turn_ndx = 0;
        } else {
            user_turn_ndx++;
        }
    }
    once++;
    
    std::string choice;
    int col_index, row_index;
    bool isValid;
    
    do {
        isValid = true;
        do {
            std::cout << "\n\n" << player_num[user_turn_ndx].getFirstName() << ", your piece is '" << player_num[user_turn_ndx].getPiece() << "'. Enter your move: ";
            std::getline(std::cin, choice);
            to_upper(choice[0]);
            
            if (choice.length() == 2) {
                col_index = (choice[1] - '0') - 1;
            } else {
                col_index = (((choice[1] - '0') * 10) + (choice[2] - '0')) - 1;
            }
            row_index = choice[0] - ASCII_ALPHABET_OFFSET;
        } while (choice.length() < 2 || choice.length() > 3 || choice[1] == ' ' || row_index >= rows || col_index >= columns);
        
        isValid = inputs[row_index][col_index] == " ";
        
    } while (!isValid);
    
    std::cout << "Row index: " << row_index << std::endl;
    std::cout << "Col index: " << col_index << std::endl;
    inputs[row_index][col_index] = player_num[user_turn_ndx].getPiece();
    isWinner = aWinner(inputs, rows, columns, player_num, peeps, user_turn_ndx, row_index, col_index);
    
    if (isWinner == 1) {
        once = 1;
        player_num[user_turn_ndx + 1].goesFirst();
        for (int others = 0; others < peeps; others++) {
            if (others != user_turn_ndx + 1) {
                player_num[user_turn_ndx].doesNotGoFirst();
            }
        }
    } else if (isWinner == 0) {
        if (starter == peeps - 1) {
            user_turn_ndx = 0;
        } else {
            user_turn_ndx = starter + 1;
        }
    }
    return isWinner;
    
    
}

/**
 Display the desired format for user input
 */
void displayInputConstraints() {
    std::cout << "\n\nYour move should be specified by row character, followed by column number.\n"
              << "An example entry would be D5, j12, or L10. Your input should not exceed three characters.";
}

/**
 Converts a character to its uppercase counterpart
 
 @param char - an alpha character
 */
void to_upper(char &w) {
    if (w >= 'a' && w <= 'z') {
        w = w + ASCII_UPPERCASE;
    }
}

/**
 Returns true if there is a winning configuration
 */
int aWinner(std::string inputs[][MAX_COLUMNS], int rows, int columns, Player player_num[], int peeps, int a_user, int row_choice, int col_choice) {
    int isWinner = -1;
    int draw = rows * columns;
    static int moves = 0;
    moves++;
    
    if (horizontalWin(inputs, row_choice, col_choice, isWinner, rows, columns)) {
    } else if (verticalWin(inputs, row_choice, col_choice, isWinner, rows, columns)) {
    } else if (diagonalWin(inputs, row_choice, col_choice, isWinner, rows, columns)) {
    } else if (moves == draw) {
        for (int all = 0; all < peeps; all++) {
            player_num[all].addToDraws();
            isWinner = 0;
        }
    }

    if (isWinner == 1) {
        player_num[a_user].addToWins();
        for (int others = 0; others < peeps; others++) {
            if (others != a_user) {
                player_num[others].addToLosses();
            }
        }
        std::cout << "Winner: " << player_num[a_user].getName() << std::endl;
        draw = 0;
    } else if (isWinner == 0) {
        std::cout << "Draw!!!" << std::endl;
        draw = 0;
    }
    
    
    
    return isWinner;
}

/**
 Displays each players wins, losses, and draws
 
 @param Player [] - the players in the game
 @param int - number of players
 */
void displayStatistics(Player players[], int num_players, int games_played) {
    int max_space = longestName(players, num_players);
    std::cout << "\n\nTotal games played = " << games_played << "\n" << std::endl;
    
    
    std::string dashes = " ------";
    std::cout << "" << std::setw(max_space + 7) << "WIN" << std::setw(7)
    << "LOSS" << std::setw(7) << "DRAW" << std::endl;
    std::cout << "" << std::setw(max_space + 8);
    print(dashes, 3);
    
    
    std::string win = "", loss = "", draw = "";
    int space = 0;
    for (int p = 0; p < num_players; p++) {
        space = players[p].getName().length();
        win = "|   " + std::to_string(players[p].getWins()) + "  ";
        loss = "|   " + std::to_string(players[p].getLosses()) + "  ";
        draw = "|   " + std::to_string(players[p].getDraws()) + "  ";
        std::cout << players[p].getName() << "" << std::setw((max_space - space + 1))
                  << " " << win << loss << draw << "|" << std::endl;
        std::cout << "" << std::setw(max_space + 1) << "        ";
        print(dashes, 3);
    }
}

/**
 Returns the length of the lengthiest name of the players
 
 @param Player [] - the players in the game
 @param int - number of players
 */
int longestName(Player players[], int num_players) {
    int longest = 0;
    
    for (int p = 0; p < num_players; p++) {
        if (players[p].getName().length() > longest) {
            longest = players[p].getName().length() + 1;
        }
    }

    return longest;
}

/**
 Asks the user if they would like to play again
 */
bool playAgain() {
    bool again;
    std::string answer;
    
    std::cout << "Would you like to play again? (Y/N)\n==> ";
    std::getline(std::cin, answer);
    to_upper(answer[0]);
    
    again = answer[0] != 'N';
    
    return again;
}

/**
 Check for the vertical win cases
 */
bool verticalWin(std::string inputs[][MAX_COLUMNS], int row_choice, int col_choice, int &isWinner, int rows, int cols) {
    if ((inputs[row_choice][col_choice] == inputs[row_choice - 1][col_choice]) &&
        inputs[row_choice][col_choice] == inputs[row_choice - 2][col_choice] &&
        (((row_choice - 1 >= 0) && (row_choice - 2 >= 0)))) {
        isWinner = 1;
        to_upper(inputs[row_choice][col_choice][0]);
        to_upper(inputs[row_choice - 1][col_choice][0]);
        to_upper(inputs[row_choice - 2][col_choice][0]);
        return true;
    } else if ((inputs[row_choice][col_choice] == inputs[row_choice + 1][col_choice]) &&
               inputs[row_choice][col_choice] == inputs[row_choice + 2][col_choice] &&
               (((row_choice + 1 < rows) && (row_choice + 2 < rows)) )) {
        isWinner = 1;
        to_upper(inputs[row_choice][col_choice][0]);
        to_upper(inputs[row_choice + 1][col_choice][0]);
        to_upper(inputs[row_choice + 2][col_choice][0]);
        return true;
    } else if ((inputs[row_choice][col_choice] == inputs[row_choice - 1][col_choice]) &&
               (inputs[row_choice][col_choice] == inputs[row_choice + 1][col_choice]) &&
               (row_choice - 1 >= 0 && row_choice + 1 <= rows)) {
        isWinner = 1;
        to_upper(inputs[row_choice][col_choice][0]);
        to_upper(inputs[row_choice + 1][col_choice][0]);
        to_upper(inputs[row_choice - 1][col_choice][0]);
        return true;
    } else {
        return false;
    }
}

/**
 Checks for the horizontal win cases
 */
bool horizontalWin(std::string inputs[][MAX_COLUMNS], int row_choice, int col_choice, int &isWinner, int rows, int cols) {
    if ((inputs[row_choice][col_choice] == inputs[row_choice][col_choice - 1]) &&
        inputs[row_choice][col_choice] == inputs[row_choice][col_choice - 2] &&
        ((col_choice - 1 >= 0 && col_choice - 2 >= 0))) {
        isWinner = 1;
        to_upper(inputs[row_choice][col_choice][0]);
        to_upper(inputs[row_choice][col_choice - 1][0]);
        to_upper(inputs[row_choice][col_choice - 2][0]);
        return true;
        
    } else if ((inputs[row_choice][col_choice] == inputs[row_choice][col_choice + 1]) &&
               inputs[row_choice][col_choice] == inputs[row_choice][col_choice + 2] &&
               ((col_choice + 1 <= cols - 1 && col_choice + 2 <= cols - 1))) {
        isWinner = 1;
        to_upper(inputs[row_choice][col_choice][0]);
        to_upper(inputs[row_choice][col_choice + 1][0]);
        to_upper(inputs[row_choice][col_choice + 2][0]);
        return true;
    } else if ((inputs[row_choice][col_choice] == inputs[row_choice][col_choice - 1]) &&
               (inputs[row_choice][col_choice] == inputs[row_choice][col_choice + 1]) &&
               (col_choice - 1 >= 0 && col_choice + 1 < rows)) {
        isWinner = 1;
        to_upper(inputs[row_choice][col_choice][0]);
        to_upper(inputs[row_choice][col_choice + 1][0]);
        to_upper(inputs[row_choice][col_choice - 1][0]);
        return true;
    } else {
        return false;
    }
}

/**
 Checks for the diagonal win cases
 */
bool diagonalWin(std::string inputs[][MAX_COLUMNS], int row_choice, int col_choice, int &isWinner, int rows, int cols) {
    if ((inputs[row_choice][col_choice] == inputs[row_choice + 1][col_choice + 1]) &&
        inputs[row_choice][col_choice] == inputs[row_choice + 2][col_choice + 2] &&
        ((row_choice + 1 < rows && row_choice + 2 < rows) && (col_choice + 1 <= cols - 1 && col_choice + 2 <= cols - 1))) {
        isWinner = 1;
        to_upper(inputs[row_choice][col_choice][0]);
        to_upper(inputs[row_choice + 1][col_choice + 1][0]);
        to_upper(inputs[row_choice + 2][col_choice + 2][0]);
        return true;
        
    } else if ((inputs[row_choice][col_choice] == inputs[row_choice - 1][col_choice - 1]) &&
               inputs[row_choice][col_choice] == inputs[row_choice - 2][col_choice - 2] &&
               ((row_choice - 1 >= 0 && row_choice - 2 >= 0) && (col_choice - 1 >= 0 && col_choice - 2 >= 0))) {
        isWinner = 1;
        to_upper(inputs[row_choice][col_choice][0]);
        to_upper(inputs[row_choice - 1][col_choice - 1][0]);
        to_upper(inputs[row_choice - 2][col_choice - 2][0]);
        return true;
    } else if ((inputs[row_choice][col_choice] == inputs[row_choice + 1][col_choice + 1]) &&
               (inputs[row_choice][col_choice] == inputs[row_choice - 1][col_choice - 1]) &&
               ((col_choice - 1 >= 0 && col_choice + 1 <= cols - 1) && (row_choice - 1 >= 0 && row_choice + 1 < rows))) {
        isWinner = 1;
        to_upper(inputs[row_choice][col_choice][0]);
        to_upper(inputs[row_choice + 1][col_choice + 1][0]);
        to_upper(inputs[row_choice - 1][col_choice - 1][0]);
        return true;
    } else if ((inputs[row_choice][col_choice] == inputs[row_choice - 1][col_choice + 1]) &&
               inputs[row_choice][col_choice] == inputs[row_choice - 2][col_choice + 2] &&
               ((row_choice - 1 >= 0 && row_choice - 2 >= 0) && (col_choice + 1 <= cols - 1 && col_choice + 2 <= cols - 1))) {
        isWinner = 1;
        to_upper(inputs[row_choice][col_choice][0]);
        to_upper(inputs[row_choice - 1][col_choice + 1][0]);
        to_upper(inputs[row_choice - 2][col_choice + 2][0]);
        return true;
    } else if ((inputs[row_choice][col_choice] == inputs[row_choice + 1][col_choice - 1]) &&
               inputs[row_choice][col_choice] == inputs[row_choice + 2][col_choice - 2] &&
               ((row_choice + 1 < rows && row_choice + 2 < rows) && (col_choice - 1 >= 0 && col_choice - 2 >= 0))) {
        isWinner = 1;
        to_upper(inputs[row_choice][col_choice][0]);
        to_upper(inputs[row_choice + 1][col_choice - 1][0]);
        to_upper(inputs[row_choice + 2][col_choice - 2][0]);
        return true;
    } else if ((inputs[row_choice][col_choice] == inputs[row_choice + 1][col_choice - 1]) &&
               inputs[row_choice][col_choice] == inputs[row_choice - 1][col_choice + 1] &&
               ((row_choice - 1 >= 0 && row_choice + 1 < rows) && (col_choice + 1 <= cols - 1 && col_choice - 1 >= 0))) {
        isWinner = 1;
        to_upper(inputs[row_choice][col_choice][0]);
        to_upper(inputs[row_choice + 1][col_choice - 1][0]);
        to_upper(inputs[row_choice - 1][col_choice + 1][0]);
        return true;
    } else {
        return false;
    }
}