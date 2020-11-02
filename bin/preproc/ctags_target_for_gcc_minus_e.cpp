# 1 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino"
/*

 * Math Game

 * By: HokuHakase @ Hoku's Lab

 * Copyright (C) 2020

 * All Rights Reserved.

 * 

 * You may use, modify and redistribute the code

 * under the terms of the GNU Lesser General Public License

 * as published by the Free Software Foundation

 * version 2.1 or any later version.

 * 

 * I want to see what you make out of this! Send me a PM at:

 * Twitter: @HokuHakase

 * Discord: Hoku#4444

 * Arduboy Community: HokuHakase

 */
# 18 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino"
// Including the required libraries.
# 20 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino" 2
# 21 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino" 2

// Defining some preprocessor directives used throughout the game
//#define DEBUGMODE // COMMENT TO DEACTIVATE DEBUG MODE
# 32 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino"
// Defining an instance of Arduboy used to access the library
Arduboy2 arduboy;
Tinyfont tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());
char allLetters[101];

// Defining gameplay-related variables
byte gameState;
byte gamespace[6][6];
byte currentPosX;
byte currentPosY;
byte selectMode; //0 = gamespace movement, 1 = number selected
byte targetResult;

// ===========================
// GAMEPLAY-SPECIFIC FUNCTIONS
// ===========================

void NewGame(){
  currentPosX = 0;
  currentPosY = 0;

  selectMode = 0;

  targetResult = 0;

  for(byte i = 0; i < 6; i++){
    for(byte j = 0; j < 6; j++){
      gamespace[i][j] = random(0, 10);
    }
  }

  FindNextResult();
}

void FindNextResult(){
  byte nextPosX, nextPosY, secondNumberDir, firstResult, secondResult;
  //secondNumberDir: 0 = top, 1 = right, 2 = bottom, 3 = left

  nextPosX = random(0, 6);
  nextPosY = random(0, 6);
  secondNumberDir = random(0,4);

  firstResult = gamespace[nextPosX][nextPosY];

  switch(secondNumberDir){
    case 0:
      if(nextPosX == 0){
        secondResult = gamespace[nextPosX+1][nextPosY];
      }else{
        secondResult = gamespace[nextPosX-1][nextPosY];
      }
      break;
     case 1:
      if(nextPosY == 6 -1){
        secondResult = gamespace[nextPosX][nextPosY-1];
      }else{
        secondResult = gamespace[nextPosX][nextPosY+1];
      }
      break;
     case 2:
      if(nextPosX == 6 -1){
        secondResult = gamespace[nextPosX-1][nextPosY];
      }else{
        secondResult = gamespace[nextPosX+1][nextPosY];
      }
     break;
     case 3:
      if(nextPosY == 0){
        secondResult = gamespace[nextPosX][nextPosY+1];
      }else{
        secondResult = gamespace[nextPosX][nextPosY-1];
      }
      break;
     default:
      secondResult = 0;
      break;
  }

  targetResult = firstResult + secondResult;

}

// ==========================
// ARDUINO-SPECIFIC FUNCTIONS
// ==========================

// The setup function is run once, initialize stuff there
void setup() {
  //Initiate the arduboy2 instance
  arduboy.begin();

  //Set the target framerate if we want something else than the default 60
  arduboy.setFrameRate(30);

  // Initialize the random seed with analog pin 0 to get a fairly random input
  // TODO: Find a way to make random seeds working
  //Serial.begin(9600);
  //randomSeed(analogRead(0));

  // create all ascii letters from 32-126
  size_t newLineCounter = 0;
  for (size_t i = 0; i < 100; i++) {
    if ((i % 26) == 0) {
      allLetters[i] = '\n';
      newLineCounter++;
    }
    else{
      allLetters[i] = (char) (i+32) - newLineCounter;
    }
  }
  allLetters[100] = '\0';

  gameState = 0;
}

// The loop function runs once every frame/cycle
// Most of the game logic goes there
void loop() {
  // Pause render until it's time for the next frame
  if(!(arduboy.nextFrame()))
    return;

  // Clear the screen
  arduboy.clear();

  // Poll buttons (Needed for justPress to work)
  arduboy.pollButtons();
  if(gameState == 0){
    arduboy.setCursor(8, 8);
    arduboy.print("Press A to start");
    if(arduboy.justPressed(
# 162 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino" 3
                          (1 << (
# 162 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino"
                          3
# 162 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino" 3
                          )) 
# 162 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino"
                          /**< The A button value for functions requiring a bitmask */)){
      gameState = 1;
      NewGame();
    }
  }else if(gameState == 1){
    // Some test stuff with Tinyfont





    // Logic to draw the tiles on the screen
    for(byte i = 0; i < 6; i++){
      for(byte j = 0; j < 6; j++){
        int16_t tilePosX = (8 +(i*8)+(i*1));
        int16_t tilePosY = (5 +(j*8)+(j*1));
        if((i == currentPosX) && (j == currentPosY)){
          arduboy.drawRect(tilePosX-1, tilePosY-1, 8 +2, 8 +2);
        }
        arduboy.drawRect(tilePosX,
                         tilePosY,
                         8,
                         8);
        tinyfont.setCursor(tilePosX+2, tilePosY+2);
        tinyfont.print(gamespace[i][j]);
      }
    }

    // Logic to draw the info section of the screen
    arduboy.setCursor(68, 8);
    arduboy.print(targetResult);

    if(arduboy.justPressed(
# 194 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino" 3
                          (1 << (
# 194 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino"
                          7
# 194 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino" 3
                          )) 
# 194 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino"
                          /**< The Up button value for functions requiring a bitmask */)){
      if(currentPosY > 0){
        currentPosY--;
      }
    }
    if(arduboy.justPressed(
# 199 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino" 3
                          (1 << (
# 199 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino"
                          4
# 199 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino" 3
                          )) 
# 199 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino"
                          /**< The Down button value for functions requiring a bitmask */)){
      if(currentPosY < (6 -1)){
        currentPosY++;
      }
    }
    if(arduboy.justPressed(
# 204 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino" 3
                          (1 << (
# 204 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino"
                          5
# 204 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino" 3
                          )) 
# 204 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino"
                          /**< The Left button value for functions requiring a bitmask */)){
      if(currentPosX > 0){
        currentPosX--;
      }
    }
    if(arduboy.justPressed(
# 209 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino" 3
                          (1 << (
# 209 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino"
                          6
# 209 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino" 3
                          )) 
# 209 "d:\\Assets\\GameDev\\Projects\\Arduboy\\MathGame\\MGSource\\mathGame\\mathGame.ino"
                          /**< The Right button value for functions requiring a bitmask */)){
      if(currentPosX < (6 -1)){
        currentPosX++;
      }
    }
  }
  // Render the screen
  arduboy.display();

}
