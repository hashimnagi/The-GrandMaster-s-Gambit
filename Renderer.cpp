#include"Renderer.h"
#include<iostream>

using namespace std;


//static const definitions
const int Renderer::TILE_SIZE;
const int Renderer::BOARD_PX;
const int Renderer::SIDE_BAR;
const int Renderer::WINDOW_W;
const int Renderer::WINDOW_H;


//constructor

Renderer::Renderer( )
    : win(sf::VideoMode({ ( unsigned ) WINDOW_W, ( unsigned ) WINDOW_H }) ,
             "The GrandMaster's Gambit") {
    win.setFramerateLimit(60);
}

//Texture index layout
//White: K = 0 ; Q = 1 ; R = 2 ; B = 3 ; N = 4 ; P = 5
//Black: K = 6 ; Q = 7 ; R = 8 ; B = 9 ; N = 10 ; P = 11

int Renderer::getTextureIndex(PiecesType type , Color color)const {

    int base;

    if ( color == Color::WHITE ) {
        base = 0;
    }
    else {
        base = 6;
    }

    switch ( type ) {
        case PiecesType::KING:   
            return base + 0;
        case PiecesType::QUEEN:  
            return base + 1;
        case PiecesType::ROOK:   
            return base + 2;
        case PiecesType::BISHOP: 
            return base + 3;
        case PiecesType::KNIGHT: 
            return base + 4;
        case PiecesType::PAWN:   
            return base + 5;
        default:                
            return -1;
    }

}


bool Renderer::loadAssets( ) {
    // ── Loaded font 
    // Uses Windows built-in Arial font
    if ( !font.openFromFile("C:/Windows/Fonts/arial.ttf") ) {
        cout << "ERROR: Could not load font!\n";
        return false;
    }
        // ── Loaded piece PNGs 

    string files [ 12 ] = {
        "assets/peices/w_king_2x.png",   
        "assets/peices/w_queen_2x.png",
        "assets/peices/w_rook_2x.png",
        "assets/peices/w_bishop_2x.png",
        "assets/peices/w_knight_2x.png",
        "assets/peices/w_pawn_2x.png",
        "assets/peices/b_king_2x.png",
        "assets/peices/b_queen_2x.png",
        "assets/peices/b_rook_2x.png",
        "assets/peices/b_bishop_2x.png",
        "assets/peices/b_knight_2x.png",
        "assets/peices/b_pawn_2x.png"
    };

    for ( int i = 0; i < 12; i++ ) {
        if ( !piecesTexture [ i ].loadFromFile(files [ i ]) ) {
            cout << "ERROR: Could not load " << files [ i ] << "\n";
            return false;
        }
        // Smoothed scaling for PNG images
        piecesTexture [ i ].setSmooth(true);
    }
    cout << "All assets loaded successfully!\n";
    return true;
}

bool Renderer::isOpen( ) const {
    return win.isOpen( );
}

void Renderer::drawBoard(int selRow , int selCol) {
    for ( int i = 0; i < 8; i++ ) {
        for ( int j = 0; j < 8; j++ ) {
            sf::RectangleShape tile({ ( float ) TILE_SIZE, ( float ) TILE_SIZE });
            tile.setPosition({ ( float ) ( j * TILE_SIZE ), ( float ) ( i * TILE_SIZE ) });

            // Alternating tile color
            bool isLight;
            if ( ( i + j ) % 2 == 0 ) {
                isLight = true;
            }
            else {
                isLight = false;
            }

            if ( isLight ) {
                tile.setFillColor(lightTile);
            }
            else {
                tile.setFillColor(darkTile);
            }

            win.draw(tile);


            // Yellow highlight on selected tile
            if ( i == selRow && j == selCol ) {
                float tileSize = ( float ) TILE_SIZE;

                sf::RectangleShape highlight;
                highlight.setSize({ tileSize, tileSize });

                float posX = ( float ) ( j * TILE_SIZE );
                float posY = ( float ) ( i * TILE_SIZE );

                highlight.setPosition({ posX, posY });
                highlight.setFillColor(hlColors);

                win.draw(highlight);
            }
        }
    }

    for ( int i = 0; i < 8; i++ ) {
        sf::Text colLabel(font , std::string(1 , char('a' + i)) , 14);
        colLabel.setFillColor(sf::Color(180 , 180 , 180));

        colLabel.setPosition({
            float(i * TILE_SIZE + TILE_SIZE - 16),
            float(BOARD_PX - 18)
        });

        sf::Text rowLabel(font , std::to_string(8 - i) , 14);
        rowLabel.setFillColor(sf::Color(180 , 180 , 180));

        rowLabel.setPosition({4.f,float(i * TILE_SIZE + 4)});

        win.draw(rowLabel);
    }
      
}

void Renderer::drawPieces(const Board &board) {
    for ( int i = 0; i < 8; i++ ) {
        for ( int j = 0; j < 8; j++ ) {
            Piece *p = board.getPiece(i , j);
            if ( p == nullptr ) {
                continue;
            }
                
            int index = getTextureIndex(p->getType( ) , p->getColor( ));

            if ( index < 0 ) {
                continue;
            }

            sf::Sprite sprite(piecesTexture [ index ]);


            float padding = 4.f;

            sf::Vector2u textSize = piecesTexture [ index ].getSize( );

            float scale_X = ( TILE_SIZE - padding * 2 ) / ( float ) textSize.x;
            float scale_Y = ( TILE_SIZE - padding * 2 ) / ( float ) textSize.y;
            sprite.setScale({ scale_X, scale_Y });


            sprite.setPosition({
               ( float ) ( j * TILE_SIZE ) + padding,
               ( float ) ( i * TILE_SIZE ) + padding });

            win.draw(sprite);
        }
    }
}

void Renderer::drawValidDots(const Board &board ,
                             const vector<pair<int , int>> &moves) {
    for ( const pair<int , int> &move : moves ) {
        int row = move.first;
        int col = move.second;

        bool hasEnemy = ( board.getPiece(row , col) != nullptr );

        if ( hasEnemy ) {
            sf::CircleShape ring(TILE_SIZE / 2.0f - 4.0f);
            ring.setFillColor(sf::Color::Transparent);
            ring.setOutlineColor(sf::Color(200 , 50 , 50 , 180));
            ring.setOutlineThickness(5.0f);

            ring.setPosition({
                col * TILE_SIZE + 4.0f,
                row * TILE_SIZE + 4.0f
            });

            win.draw(ring);
        }
        else {
            float radius = 12.0f;
            float x = col * TILE_SIZE + TILE_SIZE / 2.0f - radius;
            float y = row * TILE_SIZE + TILE_SIZE / 2.0f - radius;

            sf::CircleShape dot(radius);
            dot.setFillColor(sf::Color(30 , 30 , 30 , 100));

            dot.setPosition({ x, y });

            win.draw(dot);
        }
    }
}

void Renderer::drawSideBar(const string &p1Name ,
                           const string &p2Name ,
                           Color currentTurn ,
                           int p1Captures ,
                           int p2Captures ,
                           bool inCheck) {
    const float x = BOARD_PX + 20.0f;

    // Background
    sf::RectangleShape background({
        static_cast< float >( SIDE_BAR ),
        static_cast< float >( WINDOW_H )
    });
    background.setPosition({
        static_cast< float >( BOARD_PX ), 0.0f
    });
    background.setFillColor(sidebarBig);
    win.draw(background);

    // Divider
    sf::RectangleShape divider({
        2.0f,
        static_cast< float >( WINDOW_H )
    });
    divider.setPosition({
        static_cast< float >( BOARD_PX ), 0.0f
    });
    divider.setFillColor(sf::Color(82 , 124 , 145));
    win.draw(divider);

    // Title
    sf::Text title(font , "CHESS" , 28);
    title.setFillColor(textColor);
    title.setStyle(sf::Text::Bold);
    title.setPosition({ x, 20.0f });
    win.draw(title);

    sf::RectangleShape line({
        static_cast< float >( SIDE_BAR - 40 ), 2.0f
    });
    line.setFillColor(sf::Color(82 , 124 , 145));

    line.setPosition({ x, 60.0f });
    win.draw(line);

    // ---------- Black Player ----------
    bool blackTurn = ( currentTurn == Color::BLACK );

    sf::Text blackLabel(font , "BLACK" , 14);
    blackLabel.setFillColor(sf::Color(160 , 160 , 160));
    blackLabel.setPosition({ x, 80.0f });
    win.draw(blackLabel);

    sf::Text blackName(font , p2Name , 20);
    if ( blackTurn )
        blackName.setFillColor(textColor);
    else
        blackName.setFillColor(whiteText);

    if ( blackTurn )
        blackName.setStyle(sf::Text::Bold);
    else
        blackName.setStyle(sf::Text::Regular);

    blackName.setPosition({ x, 100.0f });
    win.draw(blackName);

    sf::Text blackCaptures(
        font ,
        "Captured: " + std::to_string(p2Captures) ,
        16
    );
    blackCaptures.setFillColor(sf::Color(160 , 160 , 160));
    blackCaptures.setPosition({ x, 130.0f });
    win.draw(blackCaptures);

    if ( blackTurn ) {
        sf::Text turnArrow(font , "< Your Turn" , 15);
        turnArrow.setFillColor(textColor);
        turnArrow.setPosition({ x, 155.0f });
        win.draw(turnArrow);
    }

    // ---------- Turn Section ----------
    line.setPosition({ x, 300.0f });
    win.draw(line);

    sf::Text turnLabel(font , "TURN" , 14);
    turnLabel.setFillColor(sf::Color(160 , 160 , 160));
    turnLabel.setPosition({ x, 310.0f });
    win.draw(turnLabel);

    string currentPlayer;

    if ( currentTurn == Color::WHITE ) {
        currentPlayer = p1Name;
    }
    else {
        currentPlayer = p2Name;
    }

    string currentColor;

    if ( currentTurn == Color::WHITE ) {
        currentColor = " (White)";
    }
    else {
        currentColor = " (Black)";
    }

    sf::Text turnText(
        font ,
        currentPlayer + currentColor ,
        17
    );
    turnText.setFillColor(textColor);
    turnText.setStyle(sf::Text::Bold);
    turnText.setPosition({ x, 330.0f });
    win.draw(turnText);

    if ( inCheck ) {
        sf::Text check(font , "! IN CHECK !" , 18);
        check.setFillColor(sf::Color(220 , 60 , 60));
        check.setStyle(sf::Text::Bold);
        check.setPosition({ x, 365.0f });
        win.draw(check);
    }

    line.setPosition({ x, 400.0f });
    win.draw(line);

    // ---------- White Player ----------
    bool whiteTurn = ( currentTurn == Color::WHITE );

    sf::Text whiteLabel(font , "WHITE" , 14);
    whiteLabel.setFillColor(sf::Color(160 , 160 , 160));
    whiteLabel.setPosition({ x, 415.0f });
    win.draw(whiteLabel);

    sf::Text whiteName(font , p1Name , 20);
    if ( whiteTurn ) {
        whiteName.setFillColor(textColor);
    }
    else {
        whiteName.setFillColor(whiteText);
    }
    whiteName.setStyle(whiteTurn ? sf::Text::Bold : sf::Text::Regular);
    whiteName.setPosition({ x, 435.0f });
    win.draw(whiteName);

    sf::Text whiteCaptures(
        font ,
        "Captured: " + std::to_string(p1Captures) ,
        16
    );
    whiteCaptures.setFillColor(sf::Color(160 , 160 , 160));
    whiteCaptures.setPosition({ x, 465.0f });
    win.draw(whiteCaptures);

    if ( whiteTurn ) {
        sf::Text turnArrow(font , "< Your Turn" , 15);
        turnArrow.setFillColor(textColor);
        turnArrow.setPosition({ x, 490.0f });
        win.draw(turnArrow);
    }

    // ---------- Help Section ----------
    sf::Text hint(
        font ,
        "Click to select\nClick again to move\nESC to quit" ,
        13
    );
    hint.setFillColor(sf::Color(100 , 120 , 130));
    hint.setPosition({ x, 580.0f });
    win.draw(hint);
}

// ── Main render function ──────────────────────────────────────────
void Renderer::render(const Board &board ,
                      int selRow , int selCol ,
                      const vector<pair<int , int>> &validMoves ,
                      const string &p1Name , const string &p2Name ,
                      Color currentTurn ,
                      int p1Captures , int p2Captures ,
                      bool inCheck) {

    win.clear(sf::Color(22 , 34 , 46));

    drawBoard(selRow , selCol);
    drawValidDots(board , validMoves);
    drawPieces(board);
    drawSideBar(p1Name , p2Name , currentTurn ,
                p1Captures , p2Captures , inCheck);

    win.display( );
}

pair<int , int> Renderer::getTileClicked(int pixelX , int pixelY) const {
    if ( pixelX < 0 || pixelX >= BOARD_PX ||
        pixelY < 0 || pixelY >= BOARD_PX )
        return { -1, -1 }; 

    int col = pixelX / TILE_SIZE;
    int row = pixelY / TILE_SIZE;
    return { row, col };
}

bool Renderer::pollEvents(std::pair<int , int> &clickedTile) {
    clickedTile = std::make_pair(-1 , -1);

    std::optional<sf::Event> event;

    while ( ( event = win.pollEvent( ) ) ) {
        // ── Window close ──
        if ( event->is<sf::Event::Closed>( ) ) {
            win.close( );
            return false;
        }

        // ── Keyboard input ──
        const sf::Event::KeyPressed *key =
            event->getIf<sf::Event::KeyPressed>( );

        if ( key ) {
            if ( key->code == sf::Keyboard::Key::Escape ) {
                win.close( );
                return false;
            }
        }

        // ── Mouse click ──
        const sf::Event::MouseButtonPressed *click =
            event->getIf<sf::Event::MouseButtonPressed>( );

        if ( click ) {
            if ( click->button == sf::Mouse::Button::Left ) {
                clickedTile = getTileClicked(
                    click->position.x ,
                    click->position.y
                );
            }
        }
    }

    return true;
}
