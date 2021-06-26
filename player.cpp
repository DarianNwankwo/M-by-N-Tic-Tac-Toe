//
//  player.cpp
//  Tic_Tac_Toe
//
//  Created by Darian Nwankwo on 1/21/16.
//  Copyright © 2016 Darian Nwankwo. All rights reserved.
//

#include "player.hpp"

std::string Player::getName() const {
    /// Returns the player's name
    return (first_name + " " + last_name);
}

Player::Player() {
    wins = 0;
    losses = 0;
    draws = 0;
}

char Player::getPiece() const {
    /// Returns the player's piece
    return piece;
}

void Player::setPiece(char c) {
    /// Save the player's piece
    piece = c;
}

int Player::getWins() const {
    /// Returns player's wins
    return wins;
}
void Player::addToWins() {
    /// Add one to wins
    wins++;
}
int Player::getLosses() const {
    /// Return player's losses
    return losses;
}
void Player::addToLosses() {
    /// Add one to losses
    losses++;
}
int Player::getDraws() const {
    /// Return player's draws
    return draws;
}
void Player::addToDraws() {
    /// Add one to draws
    draws++;
}

std::string Player::getFirstName() const {
    /// Get the player's first name
    return first_name;
}

void Player::setFirstName(std::string fn) {
    first_name = fn;
}

std::string Player::getLastName() const {
    return last_name;
}

void Player::setLastName(std::string ln) {
    last_name = ln;
}

void Player::goesFirst() {
    /// Sets the player's flag for moving first to true
    move_first = true;
}

void Player::doesNotGoFirst() {
    /// Sets the player's flag for moving first to false
    move_first = false;
}

bool Player::isFirst() {
    return move_first;
}