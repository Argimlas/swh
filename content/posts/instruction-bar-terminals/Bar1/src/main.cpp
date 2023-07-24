#include <Arduino.h>
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include <SoftwareSerial.h>

//BAR 1 !!!

// Header: to whom?, from who, message, forward-bit

#define I2C_ADDRESS 0x3C

// Rotary Encoder Inputs
#define CLK 2
#define DT 3
#define SW 4

//LED
#define LED 7

//HC12
SoftwareSerial hc12(10,11);

//OLED
SSD1306AsciiWire oled;

//Encoder
int counter = 0;
int counterTemp = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir ="";

//Button
unsigned long lastButtonPress = 0;
int isPressed = false;

//Bools for screens
bool startScreenBool;
bool messageScreenBool;
bool barScreenBool;

//Bools for Cursor
bool cursorBackBool;
bool cursor4Bool;
bool cursor5Bool;
bool cursor6Bool;

//Variables for send message (header)
String toBar;
String fromBar = "1";
String barName = "Caipibar (Bar 1)";
String toMessage;
String forwardBit = "0";

//Variables for recieved Message
String recievedPayload;
String recievedForwardBit = "1";
bool recievedMessage;

//functions (because of platform.io)
void startScreen();
void messageScreen();
void barScreen();

void menueMessageScreen();
void menueBarScreen();

void setCursorBack();
void setCursor4();
void setCursor5();
void setCursor6();

void clearCursors();

void readRecievedPayload(String recievedPayload);

void printRecievedMessage(int fromBar, int message);

void sendMessage();

//SetupFunction
void setup() {
  //Start radio-module
  hc12.begin(9600);

  //Set LED pin as output
  pinMode(LED, OUTPUT);

	// Set encoder pins as inputs
	pinMode(CLK,INPUT);
	pinMode(DT,INPUT);
	pinMode(SW, INPUT_PULLUP);

	// Setup Serial Monitor
	Serial.begin(9600);

	// Read the initial state of CLK
	lastStateCLK = digitalRead(CLK);

  //Setup oled-screen
  Wire.begin();
  Wire.setClock(400000L);
  oled.begin(&SH1106_128x64, I2C_ADDRESS);
  oled.setFont(System5x7);
  startScreen();
}

//loop function
void loop() {

//----------------handle recieved messages-----------------------|

  if (startScreenBool) { //if on startscreen
    if(hc12.available()) {
      recievedPayload = hc12.readString(); //read the recieved message

      // split the message
      int msgToBar = recievedPayload.substring(0, 1).toInt();
      int msgFromBar = recievedPayload.substring(1, 2).toInt();
      int msg = recievedPayload.substring(2, 3).toInt();
      int msgForwardBit = recievedPayload.substring(3).toInt();

      if (msgToBar == fromBar.toInt()) { //checks if message is for this terminal
        digitalWrite(LED, HIGH);
        recievedMessage = true;
        readRecievedPayload(recievedPayload);
      } else if(msgToBar == toBar.toInt() && msgFromBar == fromBar.toInt() && msg == toMessage.toInt()) { //checks if its the own message
        Serial.println("Meine eigene nachricht");
      } else if(msgForwardBit == recievedForwardBit.toInt()) { //checks if message already forwarded
        recievedForwardBit = "1";
        Serial.println("Nachricht schon mal forwarded");  
      } else {                                    //forward message
        recievedForwardBit = msgForwardBit;
        hc12.print(recievedPayload);
        Serial.println("Message forwarded");
      }
    }
  }

  //---------------------------------encoder---------------------------|
	// Read the current state of CLK
	currentStateCLK = digitalRead(CLK);

	// If last and current state of CLK are different, then pulse occurred
	// React to only 1 state change to avoid double count
	if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

		// If the DT state is different than the CLK state then
		// the encoder is rotating CCW so decrement
		if (digitalRead(DT) != currentStateCLK) {
			counter --;
			currentDir ="CCW";

      if (messageScreenBool || barScreenBool) { //if either on message-selection-screen or on bar-selection-screen
        if (!cursorBackBool && !cursor4Bool && !cursor5Bool && !cursor6Bool) setCursorBack(); //checks if no cursor is set
        else if (cursorBackBool) setCursor4();
        else if (cursor4Bool) setCursor5();
        else if (cursor5Bool) setCursor6();
        else if (cursor6Bool) setCursorBack();
      }


		} else {
			// Encoder is rotating CW so increment
			counter ++;
			currentDir ="CW";

      if (messageScreenBool || barScreenBool) { //if either on message-selection-screen or on bar-selection-screen
        if (!cursorBackBool && !cursor4Bool && !cursor5Bool && !cursor6Bool) setCursorBack(); //checks if no cursor is set
        else if (cursorBackBool) setCursor6();
        else if (cursor6Bool) setCursor5();
        else if (cursor5Bool) setCursor4();
        else if (cursor4Bool) setCursorBack();
      }


		}

		Serial.print("Direction: ");
		Serial.print(currentDir);
		Serial.print(" | Counter: ");
		Serial.println(counter);
	}

	// Remember last CLK state
	lastStateCLK = currentStateCLK;


  //-------------------Button--------------------|
	// Read the button state
	int btnState = digitalRead(SW);

	//If we detect LOW signal, button is pressed
	if (btnState == LOW) {
		//if 50ms have passed since last LOW pulse, it means that the
		//button has been pressed, released and pressed again
		if (millis() - lastButtonPress > 50) {
			Serial.println("Button pressed!");

      if (recievedMessage == true) { //turns of LED if message was read after recieved and removes message from startscreen
        startScreen();
      } else if (!messageScreenBool && !barScreenBool && recievedMessage == false) messageScreen(); //switches to message-selection-screen if messageScreen AND barScreen not active AND no message recieved

      //message-selection-screen, decides when to switch to bar screen
      if (cursorBackBool && !barScreenBool) { //switches from message-selection-screen to startscreen
        startScreen();
      } else if (cursor4Bool && !barScreenBool) { //switches to barScreen if cursor on msg1 and NOT in barScreen
        barScreen();
        toMessage = "1";
      } else if (cursor5Bool && !barScreenBool) {
        barScreen();
        toMessage = "2";
      } else if (cursor6Bool && !barScreenBool) {
        barScreen();
        toMessage = "3";
      }

      //bar-seleciton screen, decides when to switch back to startscreen over the sendMessage function
      if (cursorBackBool && !messageScreenBool) { //switches from bar-seleciton screen to message-selection-screen
        messageScreen();
      } else if (cursor4Bool && !messageScreenBool) {
        toBar = "1";
        sendMessage();
      } else if (cursor5Bool && !messageScreenBool) {
        toBar = "2";
        sendMessage();
      } else if (cursor6Bool && !messageScreenBool) {
        toBar = "3";
        sendMessage();
      }
		}

		// Remember last button press event
		lastButtonPress = millis();
	}

	// Put in a slight delay to help debounce the reading
	delay(1);
}

//<---------Screen functions---------------->
void startScreen() {
  startScreenBool = true;
  messageScreenBool = false;
  barScreenBool = false;
  digitalWrite(LED, LOW);
  recievedMessage = false;
  clearCursors();
  oled.clear();
  oled.setRow(0);
  oled.println(barName);
  oled.setRow(2);
  oled.println("Press button to send");
  oled.setRow(3);
  oled.println("a message!");
  oled.setRow(4);
  oled.println("                             ");
  oled.setRow(5);
  oled.println("                             ");
  oled.setRow(6);
  oled.println("                             ");
  oled.setRow(7);
  oled.println("                             ");
}

void messageScreen() {
  startScreenBool = false;
  messageScreenBool = true;
  barScreenBool = false;
  digitalWrite(LED, LOW);
  recievedMessage = false;
  clearCursors();
  oled.clear();
  menueMessageScreen();
}

void barScreen() {
  startScreenBool = false;
  messageScreenBool = false;
  barScreenBool = true;
  digitalWrite(LED, LOW);
  recievedMessage = false;
  clearCursors();
  oled.clear();
  menueBarScreen();
}

//<---------Menue functions-------------->

void menueMessageScreen() {
  //Heading
  oled.println("Choose a message!");
  //Back Button
  oled.setRow(2);
  oled.println("  Back to start");
  //Messages
  oled.setRow(4);
  oled.println("  need helpers");
  oled.setRow(5);
  oled.println("  need glasses");
  oled.setRow(6);
  oled.println("  need change");
  //Cursor
}

void menueBarScreen() {
  //Heading
  oled.println("Choose a bar!");
  //Back Button
  oled.setRow(2);
  oled.println("  Back to messages");
  //Messages
  oled.setRow(4);
  oled.println("  Caipibar");
  oled.setRow(5);
  oled.println("  Shotbar");
  oled.setRow(6);
  oled.println("  Bierbar");
  //Cursor
}

//<---------------other functions------------------->
void readRecievedPayload(String recievedPayload) { //splits the recieved message
  int fromBar = recievedPayload.substring(1,2).toInt();
  int message = recievedPayload.substring(2,3).toInt();
  printRecievedMessage(fromBar, message);
}

void printRecievedMessage(int fromBar, int message) { //prints the recieved message
  String FromBar;
  String Message;

  if (fromBar == 1) FromBar = "Caipibar ";
  else if (fromBar == 2) FromBar = "Shotbar ";
  else if (fromBar == 3) FromBar = "Bierbar ";

  if (message == 1) Message = "needs helpers!";
  else if (message == 2) Message = "needs glasses!";
  else if (message == 3) Message = "needs change.";

  String printMessage = FromBar + Message;
  oled.setRow(5);
  oled.println("Recieved a message:");
  oled.setRow(6);
  oled.println("                             ");
  oled.setRow(7);
  oled.println(printMessage);
}

void sendMessage() { //sends the Message, switches to startscreen and shows succesfull send
  String msg = toBar + fromBar + toMessage + forwardBit;
  hc12.print(msg);
  startScreen();
  oled.setRow(5);
  oled.println("Message send");
  oled.setRow(6);
  oled.println("succesfully!");
  oled.setRow(7);
  oled.println("                             ");
}

//<------------------Set Cursor Functions---------------->
void setCursorBack() {
  cursorBackBool = true;
  oled.setRow(2);
  oled.setCol(0);
  oled.print("<");
  cursor4Bool = false;
  oled.setRow(4);
  oled.setCol(0);
  oled.print(" ");
  cursor5Bool = false;
  oled.setRow(5);
  oled.setCol(0);
  oled.println(" ");
  cursor6Bool = false;
  oled.setRow(6);
  oled.setCol(0);
  oled.println(" ");
}

void setCursor4() {
  cursorBackBool = false;
  oled.setRow(2);
  oled.setCol(0);
  oled.print(" ");
  cursor4Bool = true;
  oled.setRow(4);
  oled.setCol(0);
  oled.print(">");
  cursor5Bool = false;
  oled.setRow(5);
  oled.setCol(0);
  oled.println(" ");
  cursor6Bool = false;
  oled.setRow(6);
  oled.setCol(0);
  oled.println(" ");
}

void setCursor5() {
  cursorBackBool = false;
  oled.setRow(2);
  oled.setCol(0);
  oled.print(" ");
  cursor4Bool = false;
  oled.setRow(4);
  oled.setCol(0);
  oled.print(" ");
  cursor5Bool = true;
  oled.setRow(5);
  oled.setCol(0);
  oled.println(">");
  cursor6Bool = false;
  oled.setRow(6);
  oled.setCol(0);
  oled.println(" ");
}

void setCursor6() {
  cursorBackBool = false;
  oled.setRow(2);
  oled.setCol(0);
  oled.print(" ");
  cursor4Bool = false;
  oled.setRow(4);
  oled.setCol(0);
  oled.print(" ");
  cursor5Bool = false;
  oled.setRow(5);
  oled.setCol(0);
  oled.println(" ");
  cursor6Bool = true;
  oled.setRow(6);
  oled.setCol(0);
  oled.println(">");
}

void clearCursors() {
  cursorBackBool = false;
  cursor4Bool = false;
  cursor5Bool = false;
  cursor6Bool = false;
}