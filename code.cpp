#include "code.h"

#include <iomanip>
#include <iostream>

using namespace std;

// constructor
TicTacToe::TicTacToe()
    : m_next_turn('X'), m_game_log(nullptr), m_game_log_size(0), m_game_state(GameState::START)
{
    for(int i = 0; i < k_board_size; i++)
    {
        for(int j = 0; j < k_board_size; j++)
        m_board[i][j] = ' ';
    }
}

// destructor
TicTacToe::~TicTacToe()
{
    delete[] m_game_log;
}

// print board
void TicTacToe::printBoard() const
{
    for(int i = 0; i < k_board_size; i++)
    {
        for(int j = 0; j < k_board_size; j++)
        {
            cout << m_board[i][j];
            
            if (j < k_board_size - 1)
            cout << " | ";
        }
        
        cout << endl;
        
        if (i < k_board_size - 1)
        cout << "---------\n";
    }
}

bool TicTacToe::isMoveValid(const Move& move) const
{
    if(move.row < 1 || move.row > k_board_size || move.column < 1 || move.column > k_board_size)
    return false;

    if(m_board[move.row - 1][move.column - 1] != ' ')
    return false;

    if(move.player != m_next_turn)
    return false;

    if(m_game_state != GameState::ONGOING && m_game_state != GameState::START)
    return false;

    return true;
}

void TicTacToe::updateGameLog(const Move& move)
{
    Move* new_log = new Move[m_game_log_size + 1];
    
    for(int i = 0; i < m_game_log_size; ++i)
    new_log[i] = m_game_log[i];
    
    new_log[m_game_log_size] = move;
    
    delete[] m_game_log;
    m_game_log = new_log;
    
    ++m_game_log_size;
}

bool TicTacToe::checkWin(char player)
{
    for(int i = 0; i < k_board_size; ++i)
    {
        if((m_board[i][0] == player && m_board[i][1] == player && m_board[i][2] == player) || (m_board[0][i] == player && m_board[1][i] == player && m_board[2][i] == player))
        return true;
    }

    if((m_board[0][0] == player && m_board[1][1] == player && m_board[2][2] == player) || (m_board[0][2] == player && m_board[1][1] == player && m_board[2][0] == player))
    return true;

    return false;
}

void TicTacToe::updateGameState()
{
    // X win
    if(checkWin('X'))
    m_game_state = GameState::X_WIN;
    else if(checkWin('O'))
    m_game_state = GameState::O_WIN;
    else 
    {
        bool is_tie = true;
        for (int i = 0; i < k_board_size; ++i)
        {
            for (int j = 0; j < k_board_size; ++j)
            {
                if (m_board[i][j] == ' ')
                {
                    is_tie = false;
                    break;
                }
            }
            if(!is_tie) break;
        }

        if(is_tie)
        m_game_state = GameState::TIE;
        else 
        m_game_state = GameState::ONGOING;
    }
}

void TicTacToe::makeMove(const Move& move)
{
    if(isMoveValid(move))
    {
        m_board[move.row - 1][move.column - 1] = move.player;
        
        updateGameLog(move);
        
        m_next_turn = (m_next_turn == 'X') ? 'O' : 'X';
        
        updateGameState();
    }
    else
    {
        cout << "The move is not valid" << endl;
    }
}


// single turn
void TicTacToe::playOnce()
{
    if (m_game_state == GameState::X_WIN || m_game_state == GameState::O_WIN || m_game_state == GameState::TIE)
    {
        cout << "The game has already ended" << endl;
        switch (m_game_state)
        {
        case GameState::X_WIN:
            cout << "Player X won" << endl;
            break;
        case GameState::O_WIN:
            cout << "Player O won" << endl;
            break;
        case GameState::TIE:
            cout << "It's a tie!" << endl;
            break;
        default:
            break;
        }
        return;
    }
    
    printBoard();
    
    Move move;
    cout << "What is the next move? ";
    cin >> move.player >> move.row >> move.column;
    
    makeMove(move);
}

void TicTacToe::play()
{
    while (m_game_state == GameState::START || m_game_state == GameState::ONGOING)
    playOnce();

    printBoard();
    
    switch (m_game_state)
    {
        case GameState::X_WIN:
            cout << "Player X won" << endl;
            break;
        case GameState::O_WIN:
            cout << "Player O won" << endl;
            break;
        case GameState::TIE:
            cout << "It's a tie!" << endl;
            break;
        default:
            cout << "Balls" << endl;
            break;
    }
}

GameState TicTacToe::getGameState() const {
    return m_game_state;
}
