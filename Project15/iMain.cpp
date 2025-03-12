#include "iGraphics.h"
#include <cstdlib>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

struct Square {
    int x, y, size;
    int r, g, b; // Colors
};

// 3 squares
Square squares[3];
int targetIndex; // Index of correct color
int score = 0;
int rounds = 0;
int correctClicks = 0; // To track correct clicks
bool gameOver = false;

void generateSquares() {
    for (int i = 0; i < 3; i++) {
        squares[i].x = 100 + i * 150;  // Adjust position for 3 squares
        squares[i].y = 200;
        squares[i].size = 50;
        // Generate bright colors (avoid too dark shades)
        squares[i].r = 100 + rand() % 156;
        squares[i].g = 100 + rand() % 156;
        squares[i].b = 100 + rand() % 156;
    }
    targetIndex = rand() % 3; // Pick a random target from the 3 squares
}

void iDraw() {
    iClear();

    // Set background color (Gray)
    iSetColor(50, 50, 50);
    iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (gameOver) {
        iSetColor(255, 255, 255);
        iText(SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT / 2, "Game Over!", GLUT_BITMAP_HELVETICA_18);
        return;
    }

    // Display target color
    iSetColor(squares[targetIndex].r, squares[targetIndex].g, squares[targetIndex].b);
    iFilledRectangle(200, 400, 125, 50);
    iSetColor(255, 255, 255);
    iText(220, 420, "Match this!", GLUT_BITMAP_HELVETICA_18);

    // Draw the 3 squares
    for (int i = 0; i < 3; i++) {
        iSetColor(squares[i].r, squares[i].g, squares[i].b);
        iFilledRectangle(squares[i].x, squares[i].y, squares[i].size, squares[i].size);
    }

    // Display score
    char scoreText[20];
    sprintf_s(scoreText, "Score: %d", score);
    iSetColor(255, 255, 255);
    iText(10, 470, scoreText, GLUT_BITMAP_HELVETICA_18);
}

/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/

void iMouseMove(int mx, int my) {
    
}

//*******************************************************************ipassiveMouse***********************************************************************//
void iPassiveMouseMove(int mx, int my) {
    
}

void iMouse(int button, int state, int mx, int my) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !gameOver) {
        for (int i = 0; i < 3; i++) {
            if (mx >= squares[i].x && mx <= squares[i].x + squares[i].size &&
                my >= squares[i].y && my <= squares[i].y + squares[i].size) {
                if (i == targetIndex) {
                    score++; // Correct click
                    correctClicks++;
                }
                rounds++;
                if (correctClicks >= 5) {
                    gameOver = true; // Game Over after 5 correct clicks
                    iSetColor(0, 255, 0); // Green text for winning message
                    iText(SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT / 2, "You Won!", GLUT_BITMAP_HELVETICA_18);
                    break;
                }
                else {
                    generateSquares();
                }
                break;
            }
        }
    }
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/

void iKeyboard(unsigned char key) {
    if (key == '\r') {
        
    }
}

/*
function iSpecialKeyboard() is called whenever user hits special keys like-
function keys, home, end, pg up, pg down, arrows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/

void iSpecialKeyboard(unsigned char key) {
    
}

int main() {
    srand(time(0));
    generateSquares();
    iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Color Matching Clicker");
    iStart();
    return 0;
}
