/* File: main.cpp
 * Author: Brogan
 */

#include "main.h"
#include "game/game.h"
#include <iostream>
int main() {
  Game game;  // Allocates the game systems on the heap
  game.run(); // Starts the game loop
              // game destructor handles cleaning when game goes out of scope
  std::cout << "Program terminated" << std::endl;
  return 0;
}
