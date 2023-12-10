//Це консольна версія гри Змійка. Написана під вінду, тому може не працювати на лінуксі, але це не точно, я не перевіряв
//управління відбуваєтся за допомогою клавіш A S D W на будь якій розкладці клавіатури
//вихід з гри за допомогою клавіши ESC


#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>


#define width 30
#define height 15
#define fruit '+'
#define snake_head '0'
#define snake_body_segment '*'
#define border '#'
#define free_space ' '


enum direction {
    up, down, left, right
};

enum direction direction_of_move = right;

char playing_field[height][width];

int snake_bogy_X[width * height];
int snake_bogy_Y[width * height];
int snake_length = 0;

int apple_X = 15, apple_Y = 5;
int snake_head_X = 5, snake_head_Y = 5;

int score = 0, max_score = 0, deaths = 0;

bool game_over = false;
bool exit_game = false;


//оновлення ігрового поля, розміщення на ньому об'єктів гри
void update_playing_field() {

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            if (i == apple_Y && j == apple_X) {
                playing_field[i][j] = fruit;
            }
            else if (i == 0 || i == (height - 1) || j == 0 || j == (width - 1)) {
                playing_field[i][j] = border;
            }
            else if (i == snake_head_Y && j == snake_head_X) {
                playing_field[i][j] = snake_head;
            }
            else {
                playing_field[i][j] = free_space;
            }
            for (int k = 0; k < snake_length; k++) {

                if (snake_bogy_Y[k] == i && snake_bogy_X[k] == j) {

                    playing_field[i][j] = snake_body_segment;
                }
            }
        }
    }
}


//вивід игрово поля та різних показників
void drawing_playing_field() {

    system("cls");

    printf("snake game\nif you want to quit the program, click Escape\n\n");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c", playing_field[i][j]);
        }
        printf("\n");
    }

    printf("\nScore: %d\n", score);
    printf("Max score: %d\n", max_score);
    printf("Length of snake: %d\n", snake_length);
    printf("Deaths: %d\n", deaths);
}


//управління змійкою (заборона на поворот на 180 градусів) та вихід з гри через Esc
void snake_control() {

    if ((GetAsyncKeyState('W') & 0x8001) && (direction_of_move != down)) {
        direction_of_move = up;
    }

    else if ((GetAsyncKeyState('S') & 0x8001) && (direction_of_move != up)) {
        direction_of_move = down;
    }

    else if ((GetAsyncKeyState('D') & 0x8001) && (direction_of_move != left)) {
        direction_of_move = right;
    }

    else if ((GetAsyncKeyState('A') & 0x8001) && (direction_of_move != right)) {
        direction_of_move = left;
    }
    else if (GetAsyncKeyState(VK_ESCAPE) & 0x8001) {
        exit_game = true;
        game_over = true;
    }

}


//рух змійки
void move_snake() {

    for (int i = snake_length - 1; i > 0; i--) {
        snake_bogy_X[i] = snake_bogy_X[i - 1];
        snake_bogy_Y[i] = snake_bogy_Y[i - 1];
    }

    snake_bogy_X[0] = snake_head_X;
    snake_bogy_Y[0] = snake_head_Y;

    if (direction_of_move == up) {
        snake_head_Y--;
    }
    else if (direction_of_move == down) {
        snake_head_Y++;
    }
    else if (direction_of_move == right) {
        snake_head_X++;
    }
    else if (direction_of_move == left) {
        snake_head_X--;
    }

}


//перевірка на зіткнення
void collision_check() {

    if (playing_field[snake_head_Y][snake_head_X] == border || playing_field[snake_head_Y][snake_head_X] == snake_body_segment) {
        deaths++;
        game_over = true;
    }
}


//поїдання фрукта
void eat_fruit() {

    if (playing_field[snake_head_Y][snake_head_X] == fruit) {

        do {
            apple_X = rand() % (width - 2) + 1;
            apple_Y = rand() % (height - 2) + 1;
        } while (playing_field[apple_Y][apple_X] != free_space);

        snake_length++;
        score += 10;
        if (score > max_score) {
            max_score = score;
        }
        Sleep(10);
    }

}


//стартові налаштування
void settings_for_new_game() {
    direction_of_move = right;
    game_over = false;
    snake_head_X = 5, snake_head_Y = 5;
    score = 0;
    apple_X = 15, apple_Y = 5;
    snake_length = 0;
}


int main() {
    while (!exit_game) {

        settings_for_new_game();

        while (!game_over && !exit_game) {
            update_playing_field();
            drawing_playing_field();
            snake_control();
            move_snake();
            eat_fruit();
            collision_check();
            Sleep(150);
        }

        //system("cls");
        printf("\nGame over\n");
        Sleep(1000);
    }

    printf("\nExit\n");
    Sleep(500);

    return 0;
}