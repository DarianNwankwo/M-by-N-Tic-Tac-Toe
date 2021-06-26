//
//  player.hpp
//  Tic_Tac_Toe
//
//  Created by Darian Nwankwo on 1/21/16.
//  Copyright © 2016 Darian Nwankwo. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include <string>

class Player {
    /// Tic Tac Toe player class
private:
    std::string name;
    std::string first_name;
    std::string last_name;
    char piece;
    int wins;
    int losses;
    int draws;
    bool move_first;
    
public:
    // Class constructor
    Player();
    
    // Methods regarding the player's name
    std::string getName() const;
    std::string getFirstName() const;
    void setFirstName(std::string);
    std::string getLastName() const;
    void setLastName(std::string);
    
    // Methods regarding the player's piece
    char getPiece() const;
    void setPiece(char);
    
    // Methods regarding the player's score
    int getWins() const;
    void addToWins();
    int getLosses() const;
    void addToLosses();
    int getDraws() const;
    void addToDraws();
    
    // Methods regarding the player's move
    void goesFirst();
    void doesNotGoFirst();
    bool isFirst();
    
};

#endif /* player_hpp */
