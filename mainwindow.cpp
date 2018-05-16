/*
 * Richard Poulson
 * Definitions for mainwindow and its methods/attributes.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    srand (time(NULL)); // set the seed for the timer
    ui_->setupUi(this);
    this->scene_ = new QGraphicsScene;
    QGraphicsView * view = ui_->graphicsView;
    this->timer_ = new QTimer(this);
    connect(this->timer_, SIGNAL(timeout()), this, SLOT(TimerSlot())); // used for timing events
    view->setScene(this->scene_);
    view->setSceneRect(0,0,view->frameSize().width() - 5,view->frameSize().height() - 5);
    view->setStyleSheet("background-color: #c8920f;"); // set the color of the canvas behind the game board.
    game_over_ = false; // if true, the application should quit

    InitializeGameBoard();
    BeginIntroduction();
    SetUpPlayers();
    this->show();
    InitialRound();
    PlayGame();
}

MainWindow::~MainWindow()
{
    delete ui_;
}
void MainWindow::InitializeGameBoard() {
    // this algorithm calculates the horizontal and vertical offset of each resource tile.  It then populates
    // the game board with the different kinds of resource tiles.
    for(int i = 0; i < NUM_ROWS; i++) {
        // the third row should have the full number of columns.  Other columns will have less
        int num_of_columns = NUM_ROWS - abs(3 - i);
        int initial_x = this->board_x_coord_ + (ResourceTile::get_width() / 2) * abs(3 - i);
        // the "+ 1" is to correct for the overlapping edges of the tiles.
        int y_coordinate = this->board_y_coord_ + ((ResourceTile::get_height() * 3/4)+1) * i;
        for(int j = 0; j < num_of_columns; j++) {
            ResourceTile * new_tile;
            int number = rand() % 12 + 1; // assign the tile a number between 1-12
            // if this Tile will be an Edge Tile, create a new Edge Tile
            if(IsEdgeTile(i, j, (int)NUM_ROWS, num_of_columns)) {
                new_tile = new EdgeTile(initial_x + ((ResourceTile::get_width()+1) * j), y_coordinate, i, j, number);
            }
            // otherwise, create a Resource Tile at rondom
            else {
                new_tile = RandomTile(initial_x + ((ResourceTile::get_width()+1) * j), y_coordinate, i, j, number);
                connect(new_tile, &ResourceTile::TileMousePressed, this, &MainWindow::TileSelected);
            }
            // add the new Tile to the game board
            this->game_board_[i][j] = new_tile;
            // add the new Tile to the scene
            this->scene_->addItem(new_tile);
        }
    }
}
void MainWindow::TileSelected(ResourceTile * tile) {
    // if another Tile was selected, first un-select that Tile
    if(this->selected_ != NULL) { this->selected_->ToggleSelected(); }
    this->selected_ = tile;
    this->selected_->ToggleSelected();
    this->selected_->update();
}
bool MainWindow::IsEdgeTile(const int row, const int col, const int max_row, const int max_col) {
    // these are the conditions of an EdgeTile
    if( (row == 0) || (row == (max_row - 1)) || (col == 0) || (col == (max_col - 1))) { return true; }
    return false;
}

void MainWindow::on_rollDiceButton_clicked()
{
    ui_->diceRollLabel->setText(QString::number(rand() % 12 + 1));
}
ResourceTile * MainWindow::RandomTile(const int x_translation, const int y_translation, const int row, const int col, const int number) {
    int random = rand() % 3;
    if(random == 0) { return new StoneTile(x_translation, y_translation, row, col, number); }
    if(random == 1) { return new MetalTile(x_translation, y_translation, row, col, number); }
    if(random == 2) { return new PetroleumTile(x_translation, y_translation, row, col, number); }
}

void MainWindow::BeginIntroduction() {
    QMessageBox msgBox;
    msgBox.setText("Welcome to Calamity Central...");
    msgBox.setInformativeText("It is the year 2200..humanity has driven itself to extinction, along with much of the life on the planet...");
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
    msgBox.setText("");
    msgBox.setInformativeText("Now, only small bands of sentient robots remain.  Can you and your band manage to survive in this harsh wasteland?");
    msgBox.exec();
}
void MainWindow::SetUpPlayers() {
    InitializeLabelArray();
    this->num_of_players_ = QInputDialog::getInt(this, tr(""), tr("How many human players (1-4)?"), 1, 1, 4, 1, Q_NULLPTR, Qt::Popup);
    for(int i = 0; i < 4; i++) {
        if((i+1) <= this->num_of_players_) {
            QString player_name = QInputDialog::getText(this, "", "Name of Player " + QString::number(i + 1), QLineEdit::Normal, "", Q_NULLPTR);
            Player * new_player = new Player(player_name, i);
            this->players_[i] = new_player;
            this->player_labels_[i].value("name")->setText(player_name);
        }
        else {
            Player * new_player = new Player("<AI>", i);
            this->players_[i] = new_player;
            this->player_labels_[i].value("name")->setText("<AI>");
        }
    }
    UpdateLabelText();
}
void MainWindow::InitializeLabelArray() {
    player_labels_[0].insert("name", this->ui_->player1NameLabel);
    player_labels_[1].insert("name", this->ui_->player2NameLabel);
    player_labels_[2].insert("name", this->ui_->player3NameLabel);
    player_labels_[3].insert("name", this->ui_->player4NameLabel);
    player_labels_[0].insert("stone", this->ui_->stonePlayer1Label);
    player_labels_[1].insert("stone", this->ui_->stonePlayer2Label);
    player_labels_[2].insert("stone", this->ui_->stonePlayer3Label);
    player_labels_[3].insert("stone", this->ui_->stonePlayer4Label);
    player_labels_[0].insert("metal", this->ui_->metalPlayer1Label);
    player_labels_[1].insert("metal", this->ui_->metalPlayer2Label);
    player_labels_[2].insert("metal", this->ui_->metalPlayer3Label);
    player_labels_[3].insert("metal", this->ui_->metalPlayer4Label);
    player_labels_[0].insert("petroleum", this->ui_->petroleumPlayer1Label);
    player_labels_[1].insert("petroleum", this->ui_->petroleumPlayer2Label);
    player_labels_[2].insert("petroleum", this->ui_->petroleumPlayer3Label);
    player_labels_[3].insert("petroleum", this->ui_->petroleumPlayer4Label);
    player_labels_[0].insert("points", this->ui_->pointsPlayer1Label);
    player_labels_[1].insert("points", this->ui_->pointsPlayer2Label);
    player_labels_[2].insert("points", this->ui_->pointsPlayer3Label);
    player_labels_[3].insert("points", this->ui_->pointsPlayer4Label);
}
void MainWindow::UpdateLabelText() {
    for(int i = 0; i < 4; i++) {
        this->player_labels_[i].value("stone")->setText(QString::number(this->players_[i]->get_stone()));
        this->player_labels_[i].value("metal")->setText(QString::number(this->players_[i]->get_metal()));
        this->player_labels_[i].value("petroleum")->setText(QString::number(this->players_[i]->get_petroleum()));
        this->player_labels_[i].value("points")->setText(QString::number(this->players_[i]->get_points()));
    }
}
void MainWindow::InitialRound() {
    for(int i = 0; i < 4; i++) {
        QMessageBox msgBox(QMessageBox::NoIcon, "", "Player " + QString::number(i+1) + ", please select a tile to build your shelter", QMessageBox::Ok, Q_NULLPTR);
        msgBox.exec();
        ClearSelectedTile();
        this->timer_->start(1000);
    }
}
void MainWindow::DetermineWinnerExists() {
    for(int i = 0; i < 4; i++) {
        if(players_[i]->get_points() >= 0) {
            WinnerDeclared(players_[i]);
        }
    }
}
void MainWindow::PlayGame() {
    while (game_over_ == false) {
        for(int i = 0; i < 4; i++) {
            if(game_over_ == false) {
                current_player_ = players_[i];
                TakeTurn(current_player_);
                DetermineWinnerExists();
            }
            else { this->close(); }
        }
    }
}
void MainWindow::TakeTurn(Player * current_player) {
    PromptToTrade(current_player);
    PromptToBuild(current_player);
}
void MainWindow::PromptToBuild(Player * current_player) {
    QMessageBox msgBox;
    msgBox.setInformativeText("The current player is prompted to build a new structure.");
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}
void MainWindow::PromptToTrade(Player * current_player) {
    QMessageBox msgBox;
    msgBox.setInformativeText("The current player is asked if he/she wants to trade resources.");
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}
void MainWindow::WinnerDeclared(Player * player) {
    if(game_over_ != true) {
        game_over_ = true;
        QMessageBox msgBox(QMessageBox::NoIcon, "", player->get_name() + " won the game, thanks for playing! (couldn't get it to close automatically)", QMessageBox::Ok, Q_NULLPTR);
        msgBox.exec();
        this->close();
    }
}
void MainWindow::ClearSelectedTile() {
    if(this->selected_ != Q_NULLPTR) {
        this->selected_->ToggleSelected();
        this->selected_ = Q_NULLPTR;
    }
}
void MainWindow::TimerSlot() { }
