#include <iostream>
#include <string>

const int height = 80;
const int width = 20;

// snake head coordinates
int x, y;

// fruit coordinates
int fruitCoordX, fruitCoordY;

// player score
int score;

// snake tail coordinates array
int snakeTailX[100], snakeTailY[100];

// snake tail length
int snakeTailLen;

enum snakeDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };

snakeDirection sDir;

bool gameOver;

void GameInit() {
  sDir = STOP;
  x = width / 2;
  y = height / 2;
  fruitCoordX = rand() % width;
  fruitCoordY = rand() % height;
  score = 0;
}

void GameRender(std::string playerName) {
  system("cls");

  // Top walls
  for (int i = 0; i < width + 2; i++) {
    std::cout << '-';
  }
  std::cout << "\n";

  for (int i = 0; i < height; i++) {
    for (int j = 0; j <= width; j++) {
      if (j == 0 || j == width) {
        std::cout << "|";
      }
      if (i == y && j == x) {
        std::cout << "0";
      } else if (i == fruitCoordY && j == fruitCoordX) {
        std::cout << "#";
      } else {
        bool prTail = false;
        for (int k = 0; k < snakeTailLen; k++) {
          if (snakeTailX[k] == j && snakeTailY[k] == i) {
            std::cout << "o";
            prTail = true;
          }
        }
        if (!prTail) {
          std::cout << " ";
        }
      }
    }
    std::cout << "\n";
  }

  // Bottom walls
  for (int i = 0; i < width + 2; i++) {
    std::cout << "-";
  }
  std::cout << "\n";

  // Score display
  std::cout << playerName << "'s Score: " << score << "\n";
}

void UpdateGame() {
  int prevX = snakeTailX[0];
  int prevY = snakeTailY[0];
  int prev2X, prev2Y;
  snakeTailX[0] = x;
  snakeTailY[0] = y;

  for (int i = 1; i < snakeTailLen; i++) {
    prev2X = snakeTailX[i];
    prev2Y = snakeTailY[i];
    snakeTailX[i] = prevX;
    snakeTailY[i] = prevY;
    prevX = prev2X;
    prevY = prev2Y;
  }

  switch (sDir) {
  case LEFT:
    x--;
    break;
  case RIGHT:
    x++;
    break;
  case UP:
    y--;
    break;
  case DOWN:
    y++;
    break;
  }

  // Check for collision with wall
  if (x >= width || x < 0 || y >= height || y < 0) {
    gameOver = true;
  }

  // Check for collision with tail
  for (int i = 0; i < snakeTailLen; i++) {
    if (snakeTailX[i] == x && snakeTailY[i] == y) {
      gameOver = true;
    }
  }

  // Check for snake collision with food
  if (x == fruitCoordX && y == fruitCoordY) {
    score += 10;
    fruitCoordX = rand() % width;
    fruitCoordY = rand() % height;
    snakeTailLen++;
  }
}

int SetDifficulty() {
  int dfc, choice;
  std::cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: jazz?";
  std::cin >> choice;
  switch (choice) {
  case '1':
    dfc = 50;
    break;
  case '2':
    dfc = 100;
    break;
  case '3':
    dfc = 150;
    break;
  default:
    dfc = 100;
  }
  return dfc;
}

void UserInput() {
  if (_kbhit()) {
    switch (_getch()) {
    case 'a':
      sDir = LEFT;
      break;
    case 'd':
      sDir = RIGHT;
      break;
    case 's':
      sDir = DOWN;
      break;
    case 'x':
      gameOver = true;
      break;
    }
  }
}

int main() {
  std::string playerName;
  std::cout << "Enter your name: ";
  std::cin >> playerName;
  int dfc = SetDifficulty();

  GameInit();
  while (!gameOver) {
    GameRender(playerName);
    UserInput();
    UpdateGame();
    Sleep(dfc);
  }
  return 0;
}
