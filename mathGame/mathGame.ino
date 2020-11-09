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

// Including the required libraries.
#include <Arduboy2.h>
#include "Tinyfont.h"

// Defining some preprocessor directives used throughout the game
//#define DEBUGMODE // COMMENT TO DEACTIVATE DEBUG MODE
#define TILE_WIDTH 8
#define TILE_HEIGHT 8
#define TILE_SPACING 1
#define GAMESPACE_STARTX 8
#define GAMESPACE_STARTY 5
#define GAMESPACE_WIDTH 6
#define GAMESPACE_HEIGHT 6

// Defining an instance of Arduboy used to access the library
Arduboy2 arduboy;
Tinyfont tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());
char allLetters[101];

// Defining gameplay-related variables
byte gameState;
byte gamespace[GAMESPACE_WIDTH][GAMESPACE_HEIGHT];
byte currentPosX;
byte currentPosY;
byte selectMode; //0 = gamespace movement, 1 = number selected
byte targetResult; // The target number that the player must get
byte firstNumberX, firstNumberY; // Coordinates for the first selected number
byte secondNumberX, secondNumberY; // Coordinates for the second selected number

// ===========================
// GAMEPLAY-SPECIFIC FUNCTIONS
// ===========================

void NewGame(){
  currentPosX = 0;
  currentPosY = 0;

  selectMode = 0;
  
  targetResult = 0;

  for(byte i = 0; i < GAMESPACE_WIDTH; i++){
    for(byte j = 0; j < GAMESPACE_HEIGHT; j++){
      gamespace[i][j] = random(0, 10);
    }
  }

  FindNextResult();
}

void FindNextResult(){
  byte nextPosX, nextPosY, secondNumberDir, firstResult, secondResult;
  //secondNumberDir: 0 = top, 1 = right, 2 = bottom, 3 = left
  
  nextPosX = random(0, GAMESPACE_WIDTH);
  nextPosY = random(0, GAMESPACE_HEIGHT);
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
      if(nextPosY == GAMESPACE_WIDTH-1){
        secondResult = gamespace[nextPosX][nextPosY-1];
      }else{
        secondResult = gamespace[nextPosX][nextPosY+1];
      }
      break;
     case 2:
      if(nextPosX == GAMESPACE_HEIGHT-1){
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
    if(arduboy.justPressed(A_BUTTON)){
      gameState = 1;
      NewGame();
    }
  }else if(gameState == 1){
    // Some test stuff with Tinyfont
    #ifdef DEBUGMODE
      tinyfont.setCursor(64,0);
      tinyfont.print(currentPosX + "," + currentPosY);
    #endif
    
    // Logic to draw the tiles on the screen
    for(byte i = 0; i < GAMESPACE_WIDTH; i++){
      for(byte j = 0; j < GAMESPACE_HEIGHT; j++){
        int16_t tilePosX = (GAMESPACE_STARTX+(i*TILE_WIDTH)+(i*TILE_SPACING));
        int16_t tilePosY = (GAMESPACE_STARTY+(j*TILE_HEIGHT)+(j*TILE_SPACING));
        if((i == currentPosX) && (j == currentPosY)){
          arduboy.drawRect(tilePosX-1, tilePosY-1, TILE_WIDTH+2, TILE_HEIGHT+2);
        }
        arduboy.drawRect(tilePosX,
                         tilePosY,
                         TILE_WIDTH,
                         TILE_HEIGHT);
        tinyfont.setCursor(tilePosX+2, tilePosY+2);
        tinyfont.print(gamespace[i][j]);
      }
    }
  
    // Logic to draw the info section of the screen
    arduboy.setCursor(68, 8);
    arduboy.print(targetResult);
  
    if(arduboy.justPressed(UP_BUTTON)){
      if(selectMode == 1 && currentPosY > firstNumberY-1){
        currentPosY--;
      }else{
        if(currentPosY > 0){
          currentPosY--;
        } 
      }
    }
    if(arduboy.justPressed(DOWN_BUTTON)){
      if(selectMode == 1 && currentPosY < firstNumberY+1){
        currentPosY++;
      }else{
        if(currentPosY < (GAMESPACE_HEIGHT-1)){
          currentPosY++;
        }
      }
    }
    if(arduboy.justPressed(LEFT_BUTTON)){
      if(selectMode == 1 && currentPosX > firstNumberX-1){
        currentPosX--;
      }else{
        if(currentPosX > 0){
          currentPosX--;
        }
      }
    }
    if(arduboy.justPressed(RIGHT_BUTTON)){
      if(selectMode == 1 && currentPosX < firstNumberX+1){
        currentPosX++;
      }else{
        if(currentPosX < (GAMESPACE_WIDTH-1)){
          currentPosX++;
        }
      }
    }

    if(arduboy.justPressed(A_BUTTON)){
      // TODO Switch to second number select
      if(selectMode == 0){
        firstNumberX = currentPosX;
        firstNumberY = currentPosY;
        selectMode = 1;
      }else if(selectMode == 1){
        if(currentPosX == firstNumberX && currentPosY == firstNumberY){
          selectMode = 0;
        }
      }
    }
  }
  // Render the screen
  arduboy.display();
  
}
