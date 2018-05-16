/*
 * @author: Richard Poulson
 * Declarations for mainwindow
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>
#include <QMessageBox>
#include <QInputDialog>
#include <stdlib.h>     // srand, rand
#include <time.h>       // time
#include <stdio.h>
#include <iostream>     // for debugging, will remove when finished
#include "ResourceTile.h"
#include "MetalTile.h"
#include "EdgeTile.h"
#include "StoneTile.h"
#include "PetroleumTile.h"
#include "player.h"
#include <QThread>

#define NUM_ROWS 7 // the number of rows and columns in the game.

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
enum Mode { PLAYING = 0, STOPPED = 1, INITIAL = 2 };
public:
    explicit MainWindow(QWidget *parent = 0);
    // uses the row and column arguments to determine if the Tile should be an EdgeTile.
    bool IsEdgeTile(const int row, const int col, const int max_row, const int max_col);
    // populates the game board with resource tiles.
    void InitializeGameBoard();
    // return a pointer to a random resource tile.
    ResourceTile * RandomTile(const int x_translation, const int y_translation, const int row, const int col, const int number);
    void BeginIntroduction();
    void SetUpPlayers();
    void InitializeLabelArray();
    void UpdateLabelText();
    void InitialRound();
    void PlayGame();
    void TakeTurn(Player * current_player);
    void PromptToBuild(Player * current_player);
    void PromptToTrade(Player * current_player);
    void DetermineWinnerExists();
    void WinnerDeclared(Player * player);
    void ClearSelectedTile();
    ~MainWindow();

private:
    int board_x_coord_ = 30; // coordinate of the left-most edge of the game board.
    int board_y_coord_ = 30; // coordinate of the upper-most edge of the game board.
    Ui::MainWindow *ui_;
    QGraphicsScene *scene_;
    QMap<QString, QLabel *> player_labels_[4];
    Player * players_[4];
    Player * current_player_;
    int num_of_players_;
    bool game_over_;
    Mode current_mode_;

    QTimer * timer_;
    int current_time_index_;
    ResourceTile * game_board_[NUM_ROWS][NUM_ROWS];
    ResourceTile * selected_; // pointer to the resource tile that is currently selected.

private slots:
    // receives a signal when a resource tile is selected.
    void TileSelected(ResourceTile * tile);
    // receives a signal when the roll dice button is clicked.
    void on_rollDiceButton_clicked();
    void TimerSlot();
};

#endif // MAINWINDOW_H
