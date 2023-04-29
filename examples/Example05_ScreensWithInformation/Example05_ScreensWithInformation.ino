
//      ******************************************************************
//      *                                                                *
//      *       Example shows build screens that display information     *
//      *                                                                *
//      *            S. Reifel & Co.                4/22/2023            *
//      *                                                                *
//      ******************************************************************

//
// This sketch shows how to use the "TouchUserInterfaceForArduino" to create screens 
// of your own, typically to display or request information from the user. 
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
// forward declarations for images
//
extern const unsigned short DPEALogo[];


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
// for each menu, create a forward declaration with "extern"
//
extern MENU_ITEM mainMenu[];


//
// the main menu
//
MENU_ITEM mainMenu[] = {
  {MENU_ITEM_TYPE_MAIN_MENU_HEADER,  "Example Five - Display Information",   MENU_COLUMNS_2,            mainMenu},
  {MENU_ITEM_TYPE_COMMAND,           "Back button",                          commandBackButtonExample,  NULL},
  {MENU_ITEM_TYPE_COMMAND,           "OK button",                            commandOKButtonExample,    NULL},
  {MENU_ITEM_TYPE_COMMAND,           "OK/Cancel buttons",                    commandOkCancelExample,    NULL},
  {MENU_ITEM_TYPE_COMMAND,           "Printing in columns",                  commandPrintingColumns,    NULL},
  {MENU_ITEM_TYPE_COMMAND,           "Fonts and colors",                     commandFontsAndColors,     NULL},
  {MENU_ITEM_TYPE_COMMAND,           "Graphics",                             commandGraphics,           NULL},
  {MENU_ITEM_TYPE_COMMAND,           "Hold to say hello",                    commandHoldToSayHello,     NULL},
  {MENU_ITEM_TYPE_COMMAND,           "Show an image",                        commandShowImage,          NULL},
  {MENU_ITEM_TYPE_COMMAND,           "Live updates",                         commandLiveUpdates,        NULL},
  {MENU_ITEM_TYPE_END_OF_MENU,       "",                                     NULL,                      NULL}
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
// menu command that demonstrates the use of the "Back" button
//
void commandBackButtonExample(void)
{
  //
  // clear the screen and draw title bar showing with the "Back" button
  //
  ui.drawTitleBarWithBackButton("Back Button Example");
  ui.clearDisplaySpace();
  
  //
  // show some info in the display space
  //
  ui.lcdSetCursorXY(ui.displaySpaceCenterX, ui.displaySpaceCenterY - 10);
  ui.lcdPrintCentered("We exit this screen with the Back button.");


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
// menu command that demonstrates the use of an "OK" button
//
void commandOKButtonExample(void)
{
  //
  // clear the screen and draw title bar showing without the "Back" button
  //
  ui.drawTitleBar("OK Button Example");
  ui.clearDisplaySpace();
  
  //
  // show some info in the display space
  //
  ui.lcdSetCursorXY(ui.displaySpaceCenterX, ui.displaySpaceCenterY - 20);
  ui.lcdPrintCentered("We exit this screen with an OK button.");

  //
  // define and display an "OK" button 
  //
  int buttonX = ui.displaySpaceCenterX;
  int buttonY = ui.displaySpaceBottomY-30;
  int buttonWidth = 120;
  int buttonHeight = 35;
  BUTTON okButton  = {"OK", buttonX, buttonY, buttonWidth, buttonHeight};
  ui.drawButton(okButton);


  //
  // wait for the user to press the "OK" button, then return to the main menu
  //
  while(true)
  {
    //
    // get touch events on the LCD
    //
    ui.getTouchEvents();

    //
    // check for a touch event on the OK button, if so return to the main menu
    //
    if (ui.checkForButtonClicked(okButton))
      return;
  }
}



//
// menu command that demonstrates the use of "OK" & "Cancel" buttons
//
void commandOkCancelExample(void)
{
  //
  // clear the screen and draw title bar showing without the "Back" button
  //
  ui.drawTitleBar("OK / Cancel Button Example");
  ui.clearDisplaySpace();
  
  //
  // show some info in the display space
  //
  ui.lcdSetCursorXY(ui.displaySpaceCenterX, ui.displaySpaceCenterY - 20);
  ui.lcdPrintCentered("The user can exit with OK or Cancel.");

  //
  // define and display "OK" and "Cancel" buttons
  //
  BUTTON okButton        = {"OK",      ui.displaySpaceCenterX-70,   ui.displaySpaceBottomY-30,  120 , 35};
  ui.drawButton(okButton);

  BUTTON cancelButton    = {"Cancel",  ui.displaySpaceCenterX+70,   ui.displaySpaceBottomY-30,  120 , 35};
  ui.drawButton(cancelButton);


  //
  // wait for the user to press the "OK" button, then return to the main menu
  //
  while(true)
  {
    //
    // get touch events on the LCD
    //
    ui.getTouchEvents();


    //
    // check for a touch event on the OK button, if so do stuff then return to the main menu
    //
    if (ui.checkForButtonClicked(okButton))
    {
      //
      // do some stuff, or save some stuff because the user pressed OK
      //
      ui.clearDisplaySpace();
      ui.lcdSetCursorXY(ui.displaySpaceCenterX, ui.displaySpaceCenterY - 20);
      ui.lcdPrintCentered("Saving...");
      delay(1500);

      //
      // return to the main menu
      //
      return;
    }

      
    //
    // check for a touch event on the Cancel button, if so return to the main menu
    //
    if (ui.checkForButtonClicked(cancelButton))
      return;
  }
}



//
// menu command that demonstrates printing in columns
//
void commandPrintingColumns(void)
{
  //
  // clear the screen and draw title bar showing with the "Back" button
  //
  ui.drawTitleBarWithBackButton("Show Info in Columns");
  ui.clearDisplaySpace();


  //
  // display some data in columns
  //
  int titleX = 96;
  int valueX = 181;  
  int y = 65;
  ui.lcdSetCursorXY(titleX, y);  ui.lcdPrint("X Offset");
  ui.lcdSetCursorXY(valueX, y);  ui.lcdPrint(17);
 
  y += 30;
  ui.lcdSetCursorXY(titleX, y);  ui.lcdPrint("X Scaler");
  ui.lcdSetCursorXY(valueX, y);  ui.lcdPrint(123.456);
  
  y += 30;
  ui.lcdSetCursorXY(titleX, y);  ui.lcdPrint("Y Offset");
  ui.lcdSetCursorXY(valueX, y);  ui.lcdPrint(-350);
 
  y += 30;
  ui.lcdSetCursorXY(titleX, y);  ui.lcdPrint("Y Scaler");
  ui.lcdSetCursorXY(valueX, y);  ui.lcdPrint(3.14159);


  //
  // print using left, right and center justifying
  //
  y = ui.displaySpaceBottomY - 30;
  ui.lcdSetCursorXY(ui.displaySpaceLeftX + 10, y);    ui.lcdPrint("Left");
  ui.lcdSetCursorXY(ui.displaySpaceRightX - 10, y);   ui.lcdPrintRightJustified("Right");
  ui.lcdSetCursorXY(ui.displaySpaceCenterX, y);       ui.lcdPrintCentered("Center");


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
// menu command that demonstrates the use of fonts and color
//
void commandFontsAndColors(void)
{
  //
  // draw title bar showing with the "Back" button
  //
  ui.drawTitleBarWithBackButton("Show Colors and Fonts");

  //
  // clear the display space with a color instead of the default black
  //
  ui.clearDisplaySpace(LCD_NAVY);


  //
  // display titles in white bold
  //
  int titleX = 90;
  int y = 60;
  ui.lcdSetFont(UI_Font_11_Bold);
  ui.lcdSetFontColor(LCD_WHITE);
  ui.lcdSetCursorXY(titleX, y);  ui.lcdPrint("Sensor 1:");
  
  y += 30;
  ui.lcdSetCursorXY(titleX, y);  ui.lcdPrint("Sensor 2:");
  
  y += 30;
  ui.lcdSetCursorXY(titleX, y);  ui.lcdPrint("Sensor 3:");
 
  y += 30;
  ui.lcdSetCursorXY(titleX, y);  ui.lcdPrint("Sensor 4:");


  //
  // values without bold, colored green for positive, red for negative
  //
  int valueX = 175;  
  y = 60;
  ui.lcdSetFont(UI_Font_13);
  ui.lcdSetFontColor(LCD_GREEN);
  ui.lcdSetCursorXY(valueX, y);  ui.lcdPrint(17);

  y += 30;
  ui.lcdSetFontColor(LCD_GREEN);
  ui.lcdSetCursorXY(valueX, y);  ui.lcdPrint(123.456);

  y += 30;
  ui.lcdSetFontColor(LCD_RED);
  ui.lcdSetCursorXY(valueX, y);  ui.lcdPrint(-350);

  y += 30;
  ui.lcdSetFontColor(LCD_GREEN);
  ui.lcdSetCursorXY(valueX, y);  ui.lcdPrint(3.14159);


  //
  // draw a color bar like thing
  //
  int red = 0;
  int green = 0;
  int blue = 0;
  int i = 0;
  
  for (red = 0; red <= 31; red++)
  {
    ui.lcdDrawVerticalLine(65 + i, 190, 30, ui.lcdMakeColor(red, green*2, blue));
    i++;
    ui.lcdDrawVerticalLine(65 + i, 190, 30, ui.lcdMakeColor(red, green*2, blue));
    i++;
  }
  
  for (green = 0; green <= 31; green++)
  {
    red--;
    ui.lcdDrawVerticalLine(65 + i, 190, 30, ui.lcdMakeColor(red, green*2, blue));
    i++;
    ui.lcdDrawVerticalLine(65 + i, 190, 30, ui.lcdMakeColor(red, green*2, blue));
    i++;
  }
  red = 0;
 
  for (blue = 0; blue <= 31; blue++)
  {
    green--;
    ui.lcdDrawVerticalLine(65 + i, 190, 30, ui.lcdMakeColor(red, green*2, blue));
    i++;
    ui.lcdDrawVerticalLine(65 + i, 190, 30, ui.lcdMakeColor(red, green*2, blue));
    i++;
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



//
// menu command that demonstrates drawing with graphics
//
void commandGraphics(void)
{
  //
  // draw title bar showing with the "Back" button
  //
  ui.drawTitleBarWithBackButton("Draw a graph");
  ui.clearDisplaySpace();

  //
  // draw the axes
  //
  ui.lcdDrawHorizontalLine(10, 230, 300, LCD_WHITE);
  ui.lcdDrawVerticalLine(10, 50, 230-50, LCD_WHITE);
  for (int x = 10+30; x <= 300; x+=30)
    ui.lcdDrawVerticalLine(x, 230-4, 8, LCD_WHITE);
  for (int y = 230-30; y > 50; y-=30)
    ui.lcdDrawHorizontalLine(6, y, 8, LCD_WHITE);


  //
  // draw the graph with endpoints
  //
  int dataA[] = {30, 160,   60, 210,   90, 190,   120, 150,   150, 150,   180, 220,   210, 190,   240, 220,   270, 100,   300, 90};
  int arrayLength = sizeof(dataA) / sizeof(dataA[0]);
  int i = 2;
  while(i < arrayLength)
  {
    ui.lcdDrawLine(dataA[i-2], dataA[i-1], dataA[i], dataA[i+1], LCD_YELLOW);
    ui.lcdDrawFilledCircle(dataA[i], dataA[i+1], 3, LCD_LIGHTBLUE);
    i += 2;
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



//
// menu command to print an image on the screen
//
void commandShowImage(void)
{
  //
  // draw title bar showing with the "Back" button
  //
  ui.drawTitleBarWithBackButton("Image");
  ui.clearDisplaySpace();


  //
  // To draw an image, start with an image file (.PNG recommended).  Create it with Photoshop or 
  // your favorite image editor.  Next the image file must be converted into .C compilable code.  
  // This data is stored as an array of 2 bytes/pixel, with each word in the RGB565 format.  
  // The array must be stored in PROGMEM.  
  //
  // The file conversation from .PNG  to  .C  is most easily done using this webpage:
  //      www.rinkydinkelectronics.com/_t_doimageconverter565.php
  // It reads a .PNG file, then saves it as a .C file.  The .C files must then be added to your 
  // project and compiled along with all your code.
  //
  // For each image in your project, you also need to add a "Forward Declaration".  You will see 
  // one in this example near the top of the sketch. It looks like this:
  //      extern const unsigned short DPEALogo[];
  //
  // It's very important that the width and height values used in the call to .lcdDrawImage()
  // exactly match with the size of the original image file.  Here the image from the .PNG file is 
  // 100x100 pixels and the call to .lcdDrawImage() use these dimensions too.
  //


  //
  // draw an image
  //
  int x = 107;
  int y = 80;
  int width = 100;      // Note: width and height must exactly match size of original image
  int height = 100;
  ui.lcdDrawImage(x, y, width, height, (const uint16_t *) DPEALogo);


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
// menu command that demonstrates display live numeric values
//
void commandLiveUpdates(void)
{
  //
  // clear the screen and draw title bar showing with the "Back" button
  //
  ui.drawTitleBar("Showing Live Data");
  ui.clearDisplaySpace();

  
  //
  // define and display an "OK" button 
  //
  BUTTON okButton  = {"OK", ui.displaySpaceCenterX, ui.displaySpaceBottomY-30, 120, 35};
  ui.drawButton(okButton);


  //
  // set the location and update rate for the sensor text
  //
  unsigned long refreshTimer = millis();
  const unsigned long updateRate = 200;
  int sensorLabelTextX = 100;
  int sensorValueTextX = sensorLabelTextX + 70;
  int sensorValueTextY = 100;
  ui.lcdSetFont(UI_Font_13);
  int sensorValueTextWidth = ui.lcdStringWidthInPixels("1234.56789");
  int sensorValueTextHeight = ui.lcdGetFontHeightWithoutDecenders();

  //
  // draw a label for the sensor value
  //
  ui.lcdSetCursorXY(sensorLabelTextX, sensorValueTextY);  ui.lcdPrint("Azimuth:");

  //
  // continuously update the display until the user presses "OK"
  //
  float sensorValue = 0.0;
  while(true)
  {
    //
    // update the display every 0.2 seconds
    //
    if (millis() - refreshTimer >= updateRate)
    {
      //
      // read the sensor value
      //
      sensorValue += 0.123;

      //
      // blank the display where the sensor value is shown
      //
      ui.lcdDrawFilledRectangle(sensorValueTextX, sensorValueTextY, sensorValueTextWidth, sensorValueTextHeight, LCD_BLACK);

      //
      // print the sensor value
      //
      ui.lcdSetFont(UI_Font_13);
      ui.lcdSetCursorXY(sensorValueTextX, sensorValueTextY);
      ui.lcdPrint(sensorValue);

      //
      // reset the update timer
      //
      refreshTimer = millis();
    }
    
    
    //
    // get touch events, return to the main menu when the user presses OK
    //
    ui.getTouchEvents();
    if (ui.checkForButtonClicked(okButton))
      return;
  }
}



//
// menu command that demonstrates doing something while pressing a button
//
void commandHoldToSayHello(void)
{
  //
  // clear the screen and draw title bar showing with the "Back" button
  //
  ui.drawTitleBarWithBackButton("Touch The Button To Say Hello");
  ui.clearDisplaySpace();

  int helloX = 220;
  int helloY = ui.displaySpaceCenterY - 6;

  //
  // create and draw a button
  //
  BUTTON sayHelloButton  = {"Hold to say hello",  90, ui.displaySpaceCenterY,   140, 120};
  ui.drawButton(sayHelloButton);


  //
  // continuously check if any buttons are pressed by the user
  //
  while(true)
  {
    //
    // get events from the touch screen
    //
    ui.getTouchEvents();

    //
    // check if the user pressed and released the Back button, if so return to the main menu
    //
    if (ui.checkForBackButtonClicked())
      return;

    //
    // check if the user is currently pressing the Hello button
    //
    if (ui.checkForButtonFirstTouched(sayHelloButton))
    {
      //
      // they are holding down the button, print "Hello"
      //
      ui.lcdSetCursorXY(helloX, helloY);
      ui.lcdPrint("Hello");
    }

    //
    // check if the user has released the Hello button
    //
    if (ui.checkForButtonClicked(sayHelloButton))
    {
      //
      // blank the area of the screen where "Hello" was printed
      //
      int widthOfMessage = ui.lcdStringWidthInPixels("Hello");
      int heightOfMessage = ui.lcdGetFontHeightWithDecentersAndLineSpacing();
      ui.lcdDrawFilledRectangle(helloX, helloY, widthOfMessage, heightOfMessage, LCD_BLACK);
    }
  }
}
