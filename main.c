#include "include/raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h"
#include <stdio.h>

#define BOARD_SIZE 10
#define GAP 2
#define PADDING 30
#define BUTTON_SIZE 30
#define WINDOW_WIDTH ((BOARD_SIZE * BUTTON_SIZE + (GAP * BOARD_SIZE)) * 2) + 3 * PADDING
#define WINDOW_HEIGHT (BOARD_SIZE * BUTTON_SIZE + (GAP * BOARD_SIZE)) + 2 * PADDING

enum GAME_STATE
{
    BOARD_INITIALIZED,
    PLACE_SHIP,
    GAME_STARTED,
    PLAYER1_TURN,
    PLAYER2_TURN,
    PLAYER1_WIN,
    PLAYER2_WIN,
};

typedef enum
{
    EMPTY = 0,
    SINGLE_DECKER,
    DOUBLE_DECKER,
    TRIPPLE_DECKER,
    FOUR_DECKER,
    SHOOTED = 100,
    MARKED = 200,
} FIELD_STATE;

typedef struct
{
    unsigned char row;
    unsigned char col;
    FIELD_STATE state;
} Field;

typedef struct
{
    Field boardPlayer1[BOARD_SIZE][BOARD_SIZE]; // Plansza gracza 1
    Field Player1Shoots[BOARD_SIZE][BOARD_SIZE];
    Field boardPlayer2[BOARD_SIZE][BOARD_SIZE]; // Plansza gracza 2
    Field Player2Shoots[BOARD_SIZE][BOARD_SIZE];
    int gameState; // Stan gry (np. czy trwa gra, czy jest zakończona)
} Game;

// Zmienna globalna która będzie przechowywać stan gry
Game game;

int initGame()
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            game.boardPlayer1[row][col] = (Field){row, col, EMPTY};
            game.boardPlayer2[row][col] = (Field){row, col, EMPTY};
            game.Player1Shoots[row][col] = (Field){row, col, EMPTY};
            game.Player2Shoots[row][col] = (Field){row, col, EMPTY};
        }
    }
    game.boardPlayer1[5][5].state = SINGLE_DECKER;
    game.boardPlayer1[2][4].state = SHOOTED;
    game.boardPlayer1[2][7].state = MARKED;
    game.gameState = BOARD_INITIALIZED;
    return 1;
}

void fieldAction(Field *field)
{
    if (field->state == EMPTY)
    {
        field->state = SHOOTED;
    }
    printf("Shooted %i %i\n", field->col, field->row);
}

void drawBoard(char player)
{
    
    ClearBackground(RAYWHITE);
    const short len = player == 1 ? 0 : 400; 
    for(int x = 0; x < BOARD_SIZE; x++){
        for(int y = 0; y < BOARD_SIZE; y++){
            Rectangle rec = {10+(x*30)+len, 10+(y*30), BUTTON_SIZE, BUTTON_SIZE};
            if(player == 1){
                switch(game.boardPlayer1[x][y].state) {
                    case EMPTY: 
                        DrawRectangleRec(rec, (Color){255, 255, 255, 255});
                    break;
                    case SINGLE_DECKER || DOUBLE_DECKER || TRIPPLE_DECKER || FOUR_DECKER: 
                        DrawRectangleRec(rec, (Color){200, 200, 200, 255});
                    break;
                    case SHOOTED: 
                        DrawRectangleRec(rec, (Color){40, 240, 40, 255});
                    break;
                    case MARKED: 
                        DrawRectangleRec(rec, (Color){70, 70, 255, 255});
                    break;
                    default:
                    break;
                }
            }
            if(player == 2){
                switch(game.boardPlayer2[x][y].state) {
                    case EMPTY: 
                        DrawRectangleRec(rec, (Color){255, 255, 255, 255});
                    break;
                    case SINGLE_DECKER || DOUBLE_DECKER || TRIPPLE_DECKER || FOUR_DECKER: 
                        DrawRectangleRec(rec, (Color){0, 0, 0, 255});
                    break;
                    case SHOOTED: 
                    break;
                    case MARKED: 
                    break;
                    default:
                    break;
                }
            }
             if (CheckCollisionPointRec(GetMousePosition(), rec))
            {
                DrawRectangleRec(rec, (Color){200, 200, 200, 255});
            }
            DrawRectangleLinesEx(rec, 1, BLACK);
        }
    }
}

int main(void)
{

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "BattleShips.exe");
    initGame();

    // Load an image and set it as the window icon
    Image icon = LoadImage("resources/ship.png"); // Replace "your_icon.png" with the path to your image
    SetWindowIcon(icon);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        drawBoard(1);
        drawBoard(2);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}