
//      ******************************************************************
//      *                                                                *
//      *     Example to shows how to set the display's orientation      *
//      *             choose between Portrait and Landscape              *
//      *                                                                *
//      *            S. Reifel & Co.                4/22/2023            *
//      *                                                                *
//      ******************************************************************


//
// This sketch shows how to use the "TouchUserInterfaceForArduino" to set the 
// screen's orientation.
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
  // These example were written using a Raspberry Pi Pico Arduino board.  The following 5 
  // lines are used to setup the Pico's SPI port.  Other processors will not need this code.
  //
#ifdef ARDUINO_ARCH_RP2040
  SPI.setTX(SPI_MOSI_PIN);
  SPI.setRX(SPI_MISO_PIN);
  SPI.setSCK(SPI_SCK_PIN);
#endif

  //
  // this is where you set the display's orientation, choosing between Portrait 
  // and Landscape modes by uncommenting the one you want
  //
//ui.begin(LCD_CS_PIN, LCD_DC_PIN, TOUCH_CS_PIN, LCD_ORIENTATION_PORTRAIT_4PIN_TOP, UI_Font_13_Bold);
  ui.begin(LCD_CS_PIN, LCD_DC_PIN, TOUCH_CS_PIN, LCD_ORIENTATION_LANDSCAPE_4PIN_LEFT, UI_Font_13_Bold);
//ui.begin(LCD_CS_PIN, LCD_DC_PIN, TOUCH_CS_PIN, LCD_ORIENTATION_PORTRAIT_4PIN_BOTTOM, UI_Font_13_Bold);
//ui.begin(LCD_CS_PIN, LCD_DC_PIN, TOUCH_CS_PIN, LCD_ORIENTATION_LANDSCAPE_4PIN_RIGHT, UI_Font_13_Bold);
}


// ---------------------------------------------------------------------------------
//           Define the menus and top level loop, place menus after setup()
// ---------------------------------------------------------------------------------

//
// for each menu, create a forward declaration with "extern"
//
extern MENU_ITEM mainMenu[];


//
// the main menu
//
MENU_ITEM mainMenu[] = {
  {MENU_ITEM_TYPE_MAIN_MENU_HEADER,   "Example Two - Portrait Mode",   MENU_COLUMNS_1,               mainMenu},
  {MENU_ITEM_TYPE_COMMAND,            "Count to ten",                  commandCountToTen,            NULL},
  {MENU_ITEM_TYPE_COMMAND,            "First law of robotics",         commandFirstLawOfRobotics,    NULL},
  {MENU_ITEM_TYPE_COMMAND,            "Draw one hundred dots",         commandDraw100Dots,           NULL},
  {MENU_ITEM_TYPE_END_OF_MENU,        "",                              NULL,                         NULL}
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
  // draw the digits using a larger font
  //
  ui.lcdSetFont(UI_Font_16_Bold);

  
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
    ui.lcdSetCursorXY(ui.displaySpaceCenterX, ui.displaySpaceCenterY - 10);
    ui.lcdPrintCentered(i);

    //
    // delay for a quarter second while showing the count value
    //
    delay(250);
  }
}



//
// menu command to "First Law Of Robotics"
//
void commandFirstLawOfRobotics(void)
{  
  //
  // draw title bar showing with the "Back" button
  //
  ui.drawTitleBarWithBackButton("First Law of Robotics");

  //
  // blank the screen below the Title Bar
  //
  ui.clearDisplaySpace();

  //
  // set the font for drawing the text
  //
  ui.lcdSetFont(UI_Font_13);
  
  //
  // print some text in the LCD's display space
  //
  int y = ui.displaySpaceCenterY - (2 * 18);
  ui.lcdSetCursorXY(ui.displaySpaceCenterX, y);
  ui.lcdPrintCentered("A robot may not injure a");

  y += 18;
  ui.lcdSetCursorXY(ui.displaySpaceCenterX, y);
  ui.lcdPrintCentered("human being or, through");

  y += 18;
  ui.lcdSetCursorXY(ui.displaySpaceCenterX, y);
  ui.lcdPrintCentered(" inaction, allow a human");
  
  y += 18;
  ui.lcdSetCursorXY(ui.displaySpaceCenterX, y);
  ui.lcdPrintCentered("being to come to harm.");


  //
  // wait for the user to press the "Back" button, then return to the main menu
  //
  while(true)
  {
    ui.getTouchEvents();

    if (ui.checkForBackButtonClicked())
      return;
  }
}



//
// menu command to "Draw dots"
//
void commandDraw100Dots(void)
{  
  //
  // draw title bar showing with the "Back" button
  //
  ui.drawTitleBarWithBackButton("Draw Dots");

  //
  // blank the screen below the Title Bar
  //
  ui.clearDisplaySpace();
  
  //
  // draw 100 random circles
  //
  for (int i = 0; i < 100; i++)
  {
    int radius = 20;
    int x = random(25, ui.displaySpaceWidth - 25);
    int y = random(25, ui.displaySpaceHeight - 25);
    uint16_t color = random(0, 0xffff);
    ui.lcdDrawFilledCircle(ui.displaySpaceLeftX + x, ui.displaySpaceTopY + y, radius, color);
  }

  //
  // wait for the user to press the "Back" button, then return to the main menu
  //
  while(true)
  {
    ui.getTouchEvents();

    if (ui.checkForBackButtonClicked())
      return;
  }
}
