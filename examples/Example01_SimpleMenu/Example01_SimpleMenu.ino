
//      ******************************************************************
//      *                                                                *
//      *          Example to shows how to create a simple menu          *
//      *                                                                *
//      *            S. Reifel & Co.                4/22/2023            *
//      *                                                                *
//      ******************************************************************

//
// This sketch shows how to use the "TouchUserInterfaceForArduino" to create a  
// simple menu with three commands.  
// 
// Documentation for the "TouchUserInterfaceForArduino" library can be found at:
//    https://github.com/Stan-Reifel/TouchUserInterfaceForArduino
//

// ***********************************************************************


#include <Arduino.h>
#include <SPI.h>
#include <TouchUserInterfaceForArduino.h>
#include <UI_Fonts.h>


//
// create the user interface object
//
TouchUserInterfaceForArduino ui;


//
// IO pin definitions, BE SURE TO: configure these values to match your hardware
//
const int LCD_CS_PIN     = 1;
const int LCD_DC_PIN     = 4;
const int TOUCH_CS_PIN   = 5;
const int SPI_MOSI_PIN   = 3;
const int SPI_MISO_PIN   = 0;
const int SPI_SCK_PIN    = 2;


// ---------------------------------------------------------------------------------
//                                 Setup the hardware
// ---------------------------------------------------------------------------------

void setup() 
{
  //
  // These example were written using a Raspberry Pi Pico Arduino board.  The following 3 lines
  // are used to setup the Pico's SPI port.  Other processors will not need this code.
  //
#ifdef ARDUINO_ARCH_RP2040
  SPI.setTX(SPI_MOSI_PIN);
  SPI.setRX(SPI_MISO_PIN);
  SPI.setSCK(SPI_SCK_PIN);
#endif

  //
  // initialize the ArduinoTouchUI
  //
  ui.begin(LCD_CS_PIN, LCD_DC_PIN, TOUCH_CS_PIN, LCD_ORIENTATION_LANDSCAPE_4PIN_LEFT, UI_Font_13_Bold);
}


// ---------------------------------------------------------------------------------
//           Define the menus and top level loop, place menus after setup()
// ---------------------------------------------------------------------------------

//
// Notes on building the menu table:
//
// The first line in the table always defines what type of menu it is, either a 
// Main Menu, or a Sub Menu.  The table's last line marks the end of the table.  
// In between are menu items, each line represents one menu choice the user will
// see displayed.
//
// There are three types of menu items: Commands, Toggles, and Sub Menus. In this
// sketch we are only going to explore "Commands".
//
// A MENU_ITEM_TYPE_COMMAND line in the table adds a button to the menu.  When 
// pressed, the specified function is executed.  In the second field is the text 
// displayed on the button.  A pointer to the function is entered in the third 
// field.  The last field should always be NULL.


//
// for each menu, create a forward declaration with "extern"
//
extern MENU_ITEM mainMenu[];


//
// the main menu
//
MENU_ITEM mainMenu[] = {
  {MENU_ITEM_TYPE_MAIN_MENU_HEADER,   "Example One - Simple Menu",   MENU_COLUMNS_1,            mainMenu},
  {MENU_ITEM_TYPE_COMMAND,            "Count to ten",                commandCountToTen,         NULL},
  {MENU_ITEM_TYPE_COMMAND,            "Gettsburg address",           commandGettsburgAddress,   NULL},
  {MENU_ITEM_TYPE_COMMAND,            "Draw some shapes",            commandDrawShapes,         NULL},
  {MENU_ITEM_TYPE_END_OF_MENU,        "",                            NULL,                      NULL}
};



//
// display the menu, then execute commands selected by the user
//
void loop() 
{  
  ui.displayAndExecuteMenu(mainMenu);
}



// ---------------------------------------------------------------------------------
//                            Commands executed from the menu
// ---------------------------------------------------------------------------------

//
// menu command to "Count To Ten"
//
void commandCountToTen(void)
{  
  //
  // draw title bar showing at the top of the screen
  //
  ui.drawTitleBar("Count To Ten");

  //
  // count to ten, showing the digits on the screen, when done return to the menu
  //
  for(int i = 1; i <= 10; i++)
  {
    //
    // blank the screen below the Title Bar
    //
    ui.clearDisplaySpace();
    
    //
    // show the count number on the LCD screen
    //
    ui.lcdSetCursorXY(160, 130);
    ui.lcdPrintCentered(i);

    //
    // delay for a half second while showing the count value
    //
    delay(500);
  }
}



//
// menu command to "Show the Gettysburg Address"
//
void commandGettsburgAddress(void)
{  
  //
  // draw title bar showing with the "Back" button
  //
  ui.drawTitleBarWithBackButton("Gettsburg Address");

  //
  // blank the screen below the Title Bar
  //
  ui.clearDisplaySpace();
  
  //
  // print some text in the LCD's display space
  //
  ui.lcdSetCursorXY(160, 100);
  ui.lcdPrintCentered("Four score and seven years ago our fathers");
  ui.lcdSetCursorXY(160, 120);
  ui.lcdPrintCentered("brought forth on this continent, a new nation,");
  ui.lcdSetCursorXY(160, 140);
  ui.lcdPrintCentered("conceived in Liberty, and dedicated to the");
  ui.lcdSetCursorXY(160, 160);
  ui.lcdPrintCentered("proposition that all men are created equal.");


  //
  // wait for the user presses the "Back" button, then return to the main menu
  //
  while(true)
  {
    ui.getTouchEvents();

    if (ui.checkForBackButtonClicked())
      return;
  }
}



//
// menu command to "Draw shapes"
//
void commandDrawShapes(void)
{  
  //
  // draw title bar showing with the "Back" button
  //
  ui.drawTitleBarWithBackButton("Draw Shapes");

  //
  // blank the screen below the Title Bar
  //
  ui.clearDisplaySpace();
  
  //
  // print some random shapes in the LCD's display space
  //
  int radius = random(20, 50);
  int x = random(55, 260);
  int y = random(100, 140);
  uint16_t color = LCD_GREEN;
  ui.lcdDrawFilledCircle(x, y, radius, color);

  x = random(55, 260);
  y = random(100, 140);
  int w = random(20, 50);
  color = LCD_RED;
  ui.lcdDrawFilledTriangle(x, y,   x-w/2, y+w,   x+w/2, y+w,  color);

  x = random(55, 260);
  y = random(100, 140);
  w = random(20, 50);
  int h = random(20, 50);
  color = LCD_YELLOW;
  ui.lcdDrawFilledRectangle(x, y, w, h, color);


  //
  // wait for the user presses the "Back" button, then return to the main menu
  //
  while(true)
  {
    ui.getTouchEvents();

    if (ui.checkForBackButtonClicked())
      return;
  }
}
