
//      ******************************************************************
//      *                                                                *
//      *    Example shows how to create a menu with buttons arranged    *
//      *                           in columns                           *
//      *                                                                *
//      *            S. Reifel & Co.                4/22/2023            *
//      *                                                                *
//      ******************************************************************

//
// This sketch shows how to use the "TouchUserInterfaceForArduino" to create a
// menu with the buttons arranged in columns.  Note the size of the buttons are 
// automatically sized to fill the screen.  
// 
// Documentation for the "TouchUserInterfaceForArduino" library can be found at:
//    https://github.com/Stan-Reifel/TouchUserInterfaceForArduino
//

// ***********************************************************************

#include <Arduino.h>
#include <SPI.h>
#include <TouchUserInterfaceForArduino.h>

//
// Fonts: UI_Font_9  
//        UI_Font_10  UI_Font_10_Bold
//        UI_Font_11  UI_Font_11_Bold
//                    UI_Font_12_Bold
//        UI_Font_13  UI_Font_13_Bold
//        UI_Font_14  UI_Font_14_Bold
//        UI_Font_15  UI_Font_15_Bold
//                    UI_Font_16_Bold
//
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
// A menu can have as many buttons as you like, simply by adding more entries to the menu 
// table.  Buttons are sized such that they always fill the screen, adding more causes
// them to be shorter in height.  In many cases it is advantageous to arrange a menu's 
// buttons in two or more columns.  Columns of buttons often look better, are easier to  
// touch, and you can fit more on a single screen.
//
// The buttons on a menu can be arranged in 1, 2, 3 or 4 columns.  The number of columns 
// is set in the third field of the menu table's first line by inserting one of these 
// values:
//           MENU_COLUMNS_1, MENU_COLUMNS_2, MENU_COLUMNS_3, or MENU_COLUMNS_4
//
// So far all of our examples have placed the menu buttons in a single column.  In this
// example we will use two columns.


//
// for each menu, create a forward declaration with "extern"
//
extern MENU_ITEM mainMenu[];


//
// the main menu
//
MENU_ITEM mainMenu[] = {
  {MENU_ITEM_TYPE_MAIN_MENU_HEADER,  "Example Three - Menus with Columns",   MENU_COLUMNS_2,     mainMenu},
  {MENU_ITEM_TYPE_COMMAND,           "Count to one",                         commandCountTo1,    NULL},
  {MENU_ITEM_TYPE_COMMAND,           "Count to two",                         commandCountTo2,    NULL},
  {MENU_ITEM_TYPE_COMMAND,           "Count to three",                       commandCountTo3,    NULL},
  {MENU_ITEM_TYPE_COMMAND,           "Count to four",                        commandCountTo4,    NULL},
  {MENU_ITEM_TYPE_COMMAND,           "Count to five",                        commandCountTo5,    NULL},
  {MENU_ITEM_TYPE_COMMAND,           "Count to six",                         commandCountTo6,    NULL},
  {MENU_ITEM_TYPE_END_OF_MENU,       "",                                     NULL,               NULL}
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
// menu command to "Count To 1"
//
void commandCountTo1(void)
{  
  ui.drawTitleBar("Count To One");
  showCount(1);
}


//
// menu command to "Count To 2"
//
void commandCountTo2(void)
{  
  ui.drawTitleBar("Count To Two");
  showCount(2);
}


//
// menu command to "Count To 3"
//
void commandCountTo3(void)
{  
  ui.drawTitleBar("Count To Three");
  showCount(3);
}


//
// menu command to "Count To 4"
//
void commandCountTo4(void)
{  
  ui.drawTitleBar("Count To Four");
  showCount(4);
}


//
// menu command to "Count To 5"
//
void commandCountTo5(void)
{  
  ui.drawTitleBar("Count To Five");
  showCount(5);
}


//
// menu command to "Count To 6"
//
void commandCountTo6(void)
{  
  ui.drawTitleBar("Count To Six");
  showCount(6);
}



//
// display a screen that counts
//
void showCount(int countValue)
{
  //
  // draw the digits using a larger font
  //
  ui.lcdSetFont(UI_Font_14_Bold);
  ui.lcdSetFont(UI_Font_13_Bold);
  ui.lcdSetFont(UI_Font_16_Bold);

  
  //
  // count to ten, showing the digits on the screen, when done return to the menu
  //
  for(int i = 1; i <= countValue; i++)
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
    delay(350);
  }
}
