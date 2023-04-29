
//      ******************************************************************
//      *                                                                *
//      *  Example demonstrates Buttons with images on their face. It's  *
//      *  also an application that starts with the app's main screen    *
//      *  rather than a menu.                                           *
//      *                                                                *
//      *            S. Reifel & Co.                4/22/2023            *
//      *                                                                *
//      ******************************************************************

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
extern const unsigned short HomeButton_48x48[];
extern const unsigned short HomeButton_48x48_Pushed[];
extern const unsigned short EditButton_48x48[];
extern const unsigned short EditButton_48x48_Pushed[];
extern const unsigned short SettingsButton_48x48[];
extern const unsigned short SettingsButton_48x48_Pushed[];
extern const unsigned short ExitButton_48x48[];
extern const unsigned short ExitButton_48x48_Pushed[];
extern const unsigned short OKButton_48x48[];
extern const unsigned short OKButton_48x48_Pushed[];
extern const unsigned short CancelButton_48x48[];
extern const unsigned short CancelButton_48x48_Pushed[];

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
//                                Application's Main Screen
// ---------------------------------------------------------------------------------

//
// example of an application that's displayed first upon power up, then
// menus can be called from it
//
void loop()
{
  //
  // build the image buttons
  //
  int x = 55;
  int y = 130;
  
  IMAGE_BUTTON homeButton  = {HomeButton_48x48, HomeButton_48x48_Pushed, x, y, 48 , 48};
  x += 70;
  
  IMAGE_BUTTON editButton  = {EditButton_48x48, EditButton_48x48_Pushed, x, y, 48 , 48};
  x += 70;
  
  IMAGE_BUTTON settingsButton  = {SettingsButton_48x48, SettingsButton_48x48_Pushed, x, y, 48 , 48};
  x += 70;
  
  IMAGE_BUTTON exitButton  = {ExitButton_48x48, ExitButton_48x48_Pushed, x, y, 48 , 48};
  x += 70;
  

  //
  // draw the screen, then check for events
  //
  while(true)
  {
    //
    // draw the Title Bar and clear the display space
    //
    ui.drawTitleBar("An App With Image Buttons");
    ui.clearDisplaySpace(LCD_WHITE);
  
    //
    // draw the buttons
    //
    ui.drawImageButton(homeButton);
    ui.drawImageButton(editButton);
    ui.drawImageButton(settingsButton);
    ui.drawImageButton(exitButton);


    //
    // check for touch events from the user, and update the stopwatch display if it's running
    //
    while(true)
    {
      //
      // get any new touch events on the LCD
      //
      ui.getTouchEvents();
  
      //
      // check if the Home button pressed
      //
      if (ui.checkForImageButtonClicked(homeButton))
      {
        showMessageScreen("Home button pressed.");
        break;    // go redraw the main screen
      }
  
      //
      // check if the Edit button pressed
      //
      if (ui.checkForImageButtonClicked(editButton))
      {
        showMessageScreen("Edit button pressed.");
        break;    // go redraw the main screen
      }
  
      //
      // check if the Settings button pressed
      //
      if (ui.checkForImageButtonClicked(settingsButton))
      {
        showMessageScreen("Settings button pressed.");
        break;    // go redraw the main screen
      }
        
      //
      // check if the Exit button pressed
      //
      if (ui.checkForImageButtonClicked(exitButton))
      {
        showMessageScreen("Exit button pressed.");
        break;    // go redraw the main screen
      }
    }
  }
}



//
// screen to show a message
//
void showMessageScreen(const char *message)
{
  //
  // draw the Title bar and blank the Display Space
  //
  ui.drawTitleBar("Message:");
  ui.clearDisplaySpace(LCD_WHITE);

  //
  // draw the message
  //
  ui.lcdSetCursorXY(ui.displaySpaceCenterX, ui.displaySpaceCenterY - 35);
  ui.lcdSetFont(UI_Font_15_Bold);
  ui.lcdSetFontColor(LCD_RED);
  ui.lcdPrintCentered(message);

  //
  // create and display OK and Cancel buttons using images
  //
  IMAGE_BUTTON okButton  = {OKButton_48x48, OKButton_48x48_Pushed, ui.displaySpaceCenterX - 42, 190, 48 , 48};
  ui.drawImageButton(okButton);

  IMAGE_BUTTON cancelButton  = {CancelButton_48x48, CancelButton_48x48_Pushed, ui.displaySpaceCenterX + 42, 190, 48 , 48};
  ui.drawImageButton(cancelButton);

  //
  // wait for the user to press a button, then return from this screen
  //
  while(true)
  {
    ui.getTouchEvents();

    if (ui.checkForImageButtonClicked(okButton))
      return;

    if (ui.checkForImageButtonClicked(cancelButton))
      return;
  }
}
