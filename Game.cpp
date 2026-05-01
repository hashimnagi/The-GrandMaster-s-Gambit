// Game.cpp
#pragma warning(disable: 4996)  
#include "Game.h"
#include <iostream>
#include <string>

using namespace std;

Game::Game(string name1 , string name2)
    : player1(name1 , Color::WHITE) ,
    player2(name2 , Color::BLACK) ,
    gameOver(false) {

    currentPlayer = &player1;
    board.intiailize( );

}

bool Game::parseInput(const string &input , int &row , int &col) const {
    if ( input.length( ) < 2 )
        return false;

    col = input [ 0 ] - 'a';
    row = 8 - ( input [ 1 ] - '0' );

    return board.isInBounds(row , col);
}

bool Game::isInCheck(Color color) const {
    int kingRow;
    int kingCol;
    board.findKing(color , kingRow , kingCol);

    Color opponent;

    if ( color == Color::WHITE ) {
        opponent = Color::BLACK;
    }
    else {
        opponent = Color::WHITE;
    }

    for ( int i = 0; i < 8; i++ ) {
        for ( int j = 0; j < 8; j++ ) {
            Piece *p = board.getPiece(i , j);

            // skip empty squares
            if ( p == nullptr ) {
                continue;
            }

            // skip own pieces
            if ( p->getColor( ) != opponent ) {

                continue;
            }

            // check if this opponent piece can attack the king
            if ( p->isValidMove(i , j , kingRow , kingCol , board.getGrid( )) ) {

                return true;
            }
        }
    }
    return false;
}

bool Game::wouldLeaveKingInCheck(int fr , int fc , int tr , int tc , Color color) const {
    Piece *tempGrid [ 8 ][ 8 ];

    for ( int i = 0; i < 8; i++ )
        for ( int j = 0; j < 8; j++ )
            tempGrid [ i ][ j ] = board.getPiece(i , j);

    tempGrid [ tr ][ tc ] = tempGrid [ fr ][ fc ];
    tempGrid [ fr ][ fc ] = nullptr;

    int kingRow = -1;
    int kingCol = -1;
    for ( int i = 0; i < 8; i++ ) {
        for ( int j = 0; j < 8; j++ ) {
            if ( tempGrid [ i ][ j ] != nullptr &&
                tempGrid [ i ][ j ]->getType( ) == PiecesType::KING &&
                tempGrid [ i ][ j ]->getColor( ) == color ) {
                kingRow = i;
                kingCol = j;
            }
        }
    }

    Color opponent;

    if ( color == Color::WHITE ) {
        opponent = Color::BLACK;
    }
    else {
        opponent = Color::WHITE;
    }

    for ( int i = 0; i < 8; i++ ) {
        for ( int j = 0; j < 8; j++ ) {
            Piece *p = tempGrid [ i ][ j ];
            if ( p != nullptr ) {
                if ( p->getColor( ) == opponent ) {
                    if ( p->isValidMove(i , j , kingRow , kingCol , tempGrid) ) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Game::hasLegalMoves(Color color) const {
    for ( int fr = 0; fr < 8; fr++ )
        for ( int fc = 0; fc < 8; fc++ ) {

            Piece *p = board.getPiece(fr , fc);

            if ( p == nullptr || p->getColor( ) != color ) {
                continue;
            }

            for ( int tr = 0; tr < 8; tr++ )
                for ( int tc = 0; tc < 8; tc++ ) {
                    if ( p->isValidMove(fr , fc , tr , tc , board.getGrid( )) )
                        if ( !wouldLeaveKingInCheck(fr , fc , tr , tc , color) ) {

                            return true;
                        }
                }
        }
    return false;
}

void Game::switchTurn( ) {
    if ( currentPlayer == &player1 ) {
        currentPlayer = &player2;
    }
    else {
        currentPlayer = &player1;
    }
}

void Game::playTurn( ) {
    // using to display board and current player info
    board.display( );
    currentPlayer->DisplayInfo( );

    // warning is displayed if king is in check
    if ( isInCheck(currentPlayer->GetColor( )) )
        cout << "CHECK! Your king is under attack!\n";

    string fromStr , toStr;
    int fromRow , fromCol , toRow , toCol;

    // keep asking until a valid move is entered
    bool validMove = false;
    while ( validMove == false ) {
        cout << currentPlayer->GetName( ) << "'s move (e.g. e2 e4): ";
        cin >> fromStr >> toStr;

        // check input format
        bool fromOk = parseInput(fromStr , fromRow , fromCol);
        bool toOk = parseInput(toStr , toRow , toCol);

        if ( fromOk == false || toOk == false ) {
            cout << "Invalid input. Try again.\n";
            continue;
        }

        // checking if a piece exists at source
        Piece *piece = board.getPiece(fromRow , fromCol);

        if ( piece == nullptr ) {
            cout << "No piece there. Try again.\n";
            continue;
        }

        // checking if piece belongs to current player
        if ( piece->getColor( ) != currentPlayer->GetColor( ) ) {
            cout << "That's not your piece!\n";
            continue;
        }

        // checking if move is valid for this piece
        if ( piece->isValidMove(fromRow , fromCol , toRow , toCol , board.getGrid( )) == false ) {
            cout << "Invalid move for this piece.\n";
            continue;
        }

        // checking if move would leave own king in check
        if ( wouldLeaveKingInCheck(fromRow , fromCol , toRow , toCol , currentPlayer->GetColor( )) ) {
            cout << "That move leaves your king in check!\n";
            continue;
        }

        // all checks passed
        validMove = true;
    }

    // executing the move on the board
    Piece *captured = board.movePiece(fromRow , fromCol , toRow , toCol);

    // getting symbols for move record
    char pieceMoved = board.getPiece(toRow , toCol)->getSymbol( );
    char pieceCapture = '.';

    if ( captured != nullptr )
        pieceCapture = captured->getSymbol( );

    // handling capture
    if ( captured != nullptr ) {
        currentPlayer->IncreaseCaptured( );
        cout << "Captured: " << captured->getSymbol( ) << "\n";
        delete captured;
    }

    // recording this move in history
    if ( record.moveCount < 200 ) {
        Move m(fromRow , fromCol , toRow , toCol , pieceMoved , pieceCapture);
        record.moveHistory [ record.moveCount ] = m;
        record.moveCount++;
    }

    // checking if opponent has any legal moves left
    Color opponent;
    if ( currentPlayer->GetColor( ) == Color::WHITE )
        opponent = Color::BLACK;
    else
        opponent = Color::WHITE;

    if ( hasLegalMoves(opponent) == false ) {
        board.display( );

        // checkmate or stalemate
        if ( isInCheck(opponent) ) {
            cout << "CHECKMATE! " << currentPlayer->GetName( ) << " WINS!\n";

            if ( currentPlayer->GetColor( ) == Color::WHITE )
                record.result = Result::WHITE_WINS;
            else
                record.result = Result::BLACK_WINS;
        }
        else {
            cout << "STALEMATE! It's a draw!\n";
            record.result = Result::STALEMATE;
        }

        // saving game record to file
        fileManager.saveGame(record);

        gameOver = true;
        return;
    }

    // switching to the other player
    switchTurn( );
}

void Game::start( ) {
    // get current date
    time_t t = time(0);
    tm now;
    localtime_s(&now , &t);
    char dateBuf [ 20 ];
    strftime(dateBuf , sizeof(dateBuf) , "%Y-%m-%d" , &now);

    // fill game record
    record.playerName1 = player1.GetName( );
    record.playerName2 = player2.GetName( );
    record.datePlayed = string(dateBuf);
    record.result = Result::ONGOING;
    record.moveCount = 0;

    cout << "Welcome to Chess!\n";
    cout << "========================\n";

    // greet returning players
    if ( fileManager.hasPlayerPlayed(player1.GetName( )) )
        cout << "Welcome back, " << player1.GetName( ) << "!\n";

    if ( fileManager.hasPlayerPlayed(player2.GetName( )) )
        cout << "Welcome back, " << player2.GetName( ) << "!\n";

    // show total games played
    int total = fileManager.getTotalGamesPlayed( );
    if ( total > 0 )
        cout << "Total games played so far: " << total << "\n";

    cout << "\n" << player1.GetName( ) << " (White) vs "
        << player2.GetName( ) << " (Black)\n\n";

   // keep playing until game is over
    while ( gameOver == false ) {
        playTurn( );
    }
}

// store valid moves in a plain array instead of vector
// returns how many valid moves were found
int Game::getValidMoves(int row , int col , int resultRows[ ] , int resultCols[ ]) const {
    int count = 0;

    Piece *p = board.getPiece(row , col);

    // no piece at this square
    if ( p == nullptr )
        return 0;

    // check every square on the board
    for ( int tr = 0; tr < 8; tr++ ) {
        for ( int tc = 0; tc < 8; tc++ ) {
            // check if piece can move there
            bool moveValid = p->isValidMove(row , col , tr , tc , board.getGrid( ));

            // check if it won't leave king in check
            bool safeMove = wouldLeaveKingInCheck(row , col , tr , tc , p->getColor( ));

            if ( moveValid == true && safeMove == false ) {
                resultRows [ count ] = tr;
                resultCols [ count ] = tc;
                count++;
            }
        }
    }

    return count;
}

void Game::startGUI( ) {
    Renderer renderer;

    // try to load assets, fallback to console if failed
    if ( renderer.loadAssets( ) == false ) {
        cout << "Failed to load assets. Falling back to console.\n";
        start( );
        return;
    }

    // setup game record
    time_t t = time(0);
    tm now;
    localtime_s(&now , &t);
    char dateBuf [ 20 ];
    strftime(dateBuf , sizeof(dateBuf) , "%Y-%m-%d" , &now);

    record.playerName1 = player1.GetName( );
    record.playerName2 = player2.GetName( );
    record.datePlayed = string(dateBuf);
    record.result = Result::ONGOING;
    record.moveCount = 0;

    // GUI state variables
    int  selRow = -1;
    int  selCol = -1;
    bool pieceSelected = false;

    // plain arrays instead of vector for valid moves
    int validRows [ 64 ];
    int validCols [ 64 ];
    int validCount = 0;

    // main game loop
    while ( renderer.isOpen( ) == true && gameOver == false ) {
        pair<int , int> clickedTile;

        // stop if window closed
        if ( renderer.pollEvents(clickedTile) == false )
            break;

        int clickRow = clickedTile.first;
        int clickCol = clickedTile.second;

        // only process if a tile was actually clicked
        if ( clickRow != -1 ) {
            // ── FIRST CLICK: select a piece ──────────────────
            if ( pieceSelected == false ) {
                Piece *p = board.getPiece(clickRow , clickCol);

                // select only if it's current player's piece
                if ( p != nullptr && p->getColor( ) == currentPlayer->GetColor( ) ) {
                    selRow = clickRow;
                    selCol = clickCol;
                    pieceSelected = true;
                    validCount = getValidMoves(selRow , selCol , validRows , validCols);
                }
            }

            // ── SECOND CLICK: try to move ─────────────────────
            else {
                // clicked same piece again → deselect
                if ( clickRow == selRow && clickCol == selCol ) {
                    pieceSelected = false;
                    selRow = -1;
                    selCol = -1;
                    validCount = 0;
                }

                // clicked another own piece → switch selection
                else if ( board.getPiece(clickRow , clickCol) != nullptr &&
                         board.getPiece(clickRow , clickCol)->getColor( ) == currentPlayer->GetColor( ) ) {
                    selRow = clickRow;
                    selCol = clickCol;
                    validCount = getValidMoves(selRow , selCol , validRows , validCols);
                }

                // clicked a destination square → check if valid move
                else {
                    // search the valid moves array
                    bool isValid = false;
                    for ( int i = 0; i < validCount; i++ ) {
                        if ( validRows [ i ] == clickRow && validCols [ i ] == clickCol ) {
                            isValid = true;
                            break;
                        }
                    }

                    // valid move → execute it
                    if ( isValid == true ) {
                       // get symbols before move
                        char pieceMoved = board.getPiece(selRow , selCol)->getSymbol( );
                        char pieceCapture = '.';

                        // execute move on board
                        Piece *captured = board.movePiece(selRow , selCol , clickRow , clickCol);

                        // handle capture
                        if ( captured != nullptr ) {
                            pieceCapture = captured->getSymbol( );
                            currentPlayer->IncreaseCaptured( );
                            delete captured;
                        }

                        // record the move
                        if ( record.moveCount < 200 ) {
                            Move m(selRow , selCol , clickRow , clickCol , pieceMoved , pieceCapture);
                            record.moveHistory [ record.moveCount ] = m;
                            record.moveCount++;
                        }

                        // reset selection
                        pieceSelected = false;
                        selRow = -1;
                        selCol = -1;
                        validCount = 0;

                        // find opponent color
                        Color opponent;
                        if ( currentPlayer->GetColor( ) == Color::WHITE )
                            opponent = Color::BLACK;
                        else
                            opponent = Color::WHITE;

                        // check if opponent has no legal moves left
                        if ( hasLegalMoves(opponent) == false ) {
                            // build empty dots vector for final render
                            vector<pair<int , int>> moveDots;

                            // render final board state
                            renderer.render(board , -1 , -1 , moveDots ,
                                player1.GetName( ) , player2.GetName( ) ,
                                currentPlayer->GetColor( ) ,
                                player1.GetCaptured( ) ,
                                player2.GetCaptured( ) ,
                                false);

                            // checkmate or stalemate
                            if ( isInCheck(opponent) == true ) {
                                if ( currentPlayer->GetColor( ) == Color::WHITE )
                                    record.result = Result::WHITE_WINS;
                                else
                                    record.result = Result::BLACK_WINS;

                                cout << "CHECKMATE! " << currentPlayer->GetName( ) << " WINS!\n";
                            }
                            else {
                                record.result = Result::STALEMATE;
                                cout << "STALEMATE! Draw!\n";
                            }

                            fileManager.saveGame(record);
                            gameOver = true;
                        }
                        else {
                            switchTurn( );
                        }
                    }  // ← end of isValid block

                    // invalid destination → deselect
                    else {
                        pieceSelected = false;
                        selRow = -1;
                        selCol = -1;
                        validCount = 0;
                    }
                }  // ← end of "clicked destination" else
            }  // ← end of "second click" else
        }  // ← end of "clickRow != -1" if

        // render every frame — build vector from plain arrays
        vector<pair<int , int>> moveDots;
        for ( int i = 0; i < validCount; i++ )
            moveDots.push_back({ validRows [ i ], validCols [ i ] });

        bool inCheck = isInCheck(currentPlayer->GetColor( ));
        renderer.render(board , selRow , selCol , moveDots ,
            player1.GetName( ) , player2.GetName( ) ,
            currentPlayer->GetColor( ) ,
            player1.GetCaptured( ) ,
            player2.GetCaptured( ) ,
            inCheck);

    }  
}  