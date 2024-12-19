#pragma once

#include <iostream>

// board size
const int k_board_size = 3;

// Struct to represent a move
struct Move {
    char player = ' '; // X or O
    int row = 0;
    int column = 0;
};

enum class GameState
{
    START,
    ONGOING,
    X_WIN,
    O_WIN,
    TIE,
    NUM_STATES
};

class TicTacToe {
private:
    char m_board[k_board_size][k_board_size];
    char m_next_turn;
    Move* m_game_log;
    int m_game_log_size;
    GameState m_game_state;

    // Helper function to check for a win
    bool checkWin(char player);

public:
    // Default constructor
    TicTacToe();

    // Destructor
    ~TicTacToe();

    void printBoard() const;
    bool isMoveValid(const Move& move) const;
    void updateGameLog(const Move& move);
    void updateGameState();
    void makeMove(const Move& move);
    void playOnce();
    void play();

    GameState getGameState() const;
};
