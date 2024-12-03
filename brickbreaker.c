#include <stdio.h>
#include <conio.h>
#include <unistd.h> // For sleep()
#define WIDTH 40
#define HEIGHT 20
#define PADDLE_WIDTH 15
#define CONSOLE_WIDTH 120

char game_area[HEIGHT][WIDTH];
int paddle_x, paddle_y;
int ball_x, ball_y;
int ball_dx = 1, ball_dy = -1;
int bricks[5][WIDTH];
int score = 0;

// Initialize the game
void initialize_game() {
    // Clear game area
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            game_area[i][j] = ' ';
        }
    }

    // Add borders
    for (int i = 0; i < WIDTH; i++) {
        game_area[0][i] = '-';
        game_area[HEIGHT - 1][i] = '-';
    }
    for (int i = 0; i < HEIGHT; i++) {
        game_area[i][0] = '|';
        game_area[i][WIDTH - 1] = '|';
    }

    // Initialize paddle
    paddle_y = HEIGHT - 2;
    paddle_x = WIDTH / 2 - PADDLE_WIDTH / 2;

    // Initialize ball
    ball_x = WIDTH / 2;
    ball_y = HEIGHT / 2;

    // Initialize bricks
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j < WIDTH - 1; j++) {
            bricks[i][j] = 1; // Brick exists
            game_area[i][j] = '#';
        }
    }
}

void display_instructions() {
    // Clear the screen
    system("cls");

    // Display the instructions
    printf("\t\t\t\t------------------------------\n");
    printf("\t\t\t\t|       BRICK BREAKER        |\n");
    printf("\t\t\t\t------------------------------\n");
    printf("\t\t\t\t| Instructions:              |\n");
    printf("\t\t\t\t| 1. Use 'A' to move left.   |\n");
    printf("\t\t\t\t| 2. Use 'D' to move right.  |\n");
    printf("\t\t\t\t| 3. Press SPACEBAR to start.|\n");
    printf("\t\t\t\t------------------------------\n");
    printf("\t\t\t\t|          Good Luck!        |\n");
    printf("\t\t\t\t------------------------------\n");

    // Wait for the user to press SPACEBAR
    while (1) {
        if (getch() == ' ') {
            break; // Exit the loop when SPACEBAR is pressed
        }
    }
}

