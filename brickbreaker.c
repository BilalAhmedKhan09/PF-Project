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

// Draw the game area
void draw_game() {
    // Clear screen
    system("cls");
	
	int padding = (CONSOLE_WIDTH - WIDTH) / 2;
    if (padding < 0) padding = 0;
    
    // Place paddle
    for (int i = 0; i < PADDLE_WIDTH; i++) {
        game_area[paddle_y][paddle_x + i] = '=';
    }

    // Place ball
    game_area[ball_y][ball_x] = '*';

    // Print the game area
    for (int i = 0; i < HEIGHT; i++) {
    	for (int j = 0; j < padding; j++) {
            printf(" ");
        }
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", game_area[i][j]);
        }
        printf("\n");
    }

    // Remove paddle and ball for next frame
    for (int i = 0; i < PADDLE_WIDTH; i++) {
        game_area[paddle_y][paddle_x + i] = ' ';
    }
    game_area[ball_y][ball_x] = ' ';
	
	for (int j = 0; j < padding; j++) {
        printf(" ");
    }
    
    // Display score
    printf("Score: %d\n", score);
}

// Move paddle
void move_paddle(char direction) {
    if (direction == 'a' && paddle_x > 1) {
        paddle_x--;
    } else if (direction == 'd' && paddle_x + PADDLE_WIDTH < WIDTH - 1) {
        paddle_x++;
    }
}

// Update ball position and handle collisions
int update_ball() {
	ball_x += ball_dx;
    ball_y += ball_dy;

    // Ball collision with walls
    if (ball_x <= 1 || ball_x >= WIDTH - 2) {
        ball_dx = -ball_dx;
    }
    if (ball_y <= 1) {
        ball_dy = -ball_dy;
    }

    // Ball collision with paddle
    if (ball_y == paddle_y - 1 && ball_x >= paddle_x && ball_x < paddle_x + PADDLE_WIDTH) {
        ball_dy = -ball_dy;
    }

    // Ball collision with bricks
    if (bricks[ball_y][ball_x] == 1) {
        bricks[ball_y][ball_x] = 0;
        game_area[ball_y][ball_x] = ' ';
        ball_dy = -ball_dy;
	    score += 10;
		return 0;    
		}

	    // Game over condition
	    if (ball_y >= HEIGHT) {
	    	system("cls");
	    	printf("\t\t\t\t------------------------------\t\t\t");
	    	for(int i=0;i<3;i++){
	    		for(int j=0;j<26;j++){
	    			if(j==13 && i==1){
	    				printf("\n\t\t\t\t| Game Over! Final Score: %d |\n\t\t\t\t Press space to exit\t\t\t\t", score);
	    				
					}
	    		}
	    		printf("\n\t\t\t\t|                            |\n");
			}
			printf("\t\t\t\t------------------------------\t\t\t");
	       	return 1;
		}
	return 0;		
}


