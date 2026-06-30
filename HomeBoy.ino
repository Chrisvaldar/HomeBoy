/*
	MCD1160 
    Name: G02
    ID: 35054387
    Teacher: Mehran Vahid
    
    Description:
    
      G02 Circuit Design and Code for Assignment 1
      Last edited: 8/11/2024 (Chris)
      Version: 1.0 (Complete)
*/

#include <LiquidCrystal.h>
#define TEMP_SENSOR A0
#define BUTTON_PIN 8
#define RED_PIN 11
#define BLUE_PIN 10
#define GREEN_PIN 9
#define BUZZER_PIN 13

//Initialize global variable
int counter = 0;
float totalC = 0;
float totalF = 0;
float totalK = 0;
bool buttonState = false;

LiquidCrystal lcd(7, 6, 5, 4,3, 2);

void setup()
{
  Serial.begin(9600); //Start Serial monitor
  lcd.begin(16,2);
  pinMode(BUTTON_PIN, INPUT); //Set Button to Input
  pinMode(BUZZER_PIN, OUTPUT); //Set Buzzer to Output
}

void loop()
{
  int rawTemp = analogRead(TEMP_SENSOR); //Read temperature sensor

  //Calculate raw voltage
  float rawVoltage = rawTemp * 5;
  rawVoltage = rawVoltage / 1024;
  
  //Calculate temperature in celsius
  float celsius = rawVoltage - 0.5;
  celsius = celsius * 100;
  
  float fahrenheit = (9.0 / 5.0 * celsius) + 32.0; //Calculate Farenheit
  float kelvin = celsius + 273.15; //Calculate kelvin
  
  //Scale blue LED if lower than 20 degrees Celsius (0 is the floor)
  if(celsius < 20)
  {
    int blueBrightness = 255 - (255 * celsius / 20);
    if(blueBrightness > 255)
    {
      blueBrightness = 255;
    }
    analogWrite(RED_PIN, 0);
    analogWrite(GREEN_PIN, 0);
    analogWrite(BLUE_PIN, blueBrightness);
    
    /* Buzzer usage referenced from 
    https://www.ardumotive.com/how-to-use-a-buzzer-en.html */
    if(celsius < 10)
    {
    	digitalWrite(BUZZER_PIN, HIGH);
    }
    else
    {
      digitalWrite(BUZZER_PIN, LOW);
    }
  }
  //If 20-30 degrees Celsius, just display green
  else if(celsius >= 20 && celsius <= 30) 
  {
    analogWrite(RED_PIN, 0);
    analogWrite(GREEN_PIN, 255);
    
    /* Buzzer usage referenced from 
    https://www.ardumotive.com/how-to-use-a-buzzer-en.html */
    analogWrite(BLUE_PIN, 0);
    digitalWrite(BUZZER_PIN, LOW);
  }
  //Scale red LED if higher than 30 degrees Celsius (40 is the cap)
  else if(celsius > 30)
  {
    int redBrightness = (celsius - 30) * 255 / 10;
    if(redBrightness > 255)
    {
      redBrightness = 255;
    }
    analogWrite(RED_PIN, redBrightness);
    analogWrite(GREEN_PIN, 0);
    analogWrite(BLUE_PIN, 0);
    
    /* Buzzer usage referenced from 
    https://www.ardumotive.com/how-to-use-a-buzzer-en.html */
	if(celsius > 35)
    {
    	digitalWrite(BUZZER_PIN, HIGH);
    }
    else
    {
      digitalWrite(BUZZER_PIN, LOW);
    }
  }
  //Prints Celsius and Farenheit in each line
  lcd.print("Celsius: ");
  lcd.print(celsius);
  lcd.setCursor(0,1);
  lcd.print("Farenheit: ");
  lcd.print(fahrenheit);
  
  delay(1000); //Wait 1 seconds
  lcd.clear(); //Clears lcd
  
  //Prints Kelvin
  lcd.print("Kelvin: ");
  lcd.print(kelvin);
  
  //Calculates sum of all temperatures recorded so far
  totalC += celsius;
  totalF += fahrenheit;
  totalK += kelvin;
  
  counter++; //Increment counter to calculate average
  
  if(digitalRead(BUTTON_PIN) == HIGH)//If the button is pressed
  {
    buttonState = true;
    //Calculate current average temperature
    float avgC = totalC / counter;
    float avgF = totalF / counter;
    float avgK = totalK / counter;

    //Prints all temperature averages
    lcd.clear();
    lcd.print("Avg C: ");
    lcd.print(avgC);
    lcd.setCursor(0,1);
    lcd.print("Avg F: ");
    lcd.print(avgF);
    
    delay(1000);
    lcd.clear();
    lcd.print("Avg K: ");
    lcd.print(avgK);
    
    //Display menu
    Serial.println("Menu:");
    Serial.println("A. Display temperature in Fahrenheit");
    Serial.println("B. Display temperature in Celsius");
    Serial.println("C. Display temperature in Kelvin");
    Serial.println("D. Display average temperature in all units");
    Serial.println("Enter choice: ");
    Serial.println(""); //Print new line
    
    while(Serial.available() == 0); //Waits for user input
    char choice = Serial.read(); //Put users choice in a variable
    
    //Do things based on choice
    if(choice == 'A')
    {
      lcd.clear();
      lcd.print("Fahrenheit: ");
      lcd.setCursor(0,1);
      lcd.print(fahrenheit);
      Serial.print("Fahrenheit: ");
      Serial.println(fahrenheit);
    }
    else if(choice == 'B')
    {
      lcd.clear();
      lcd.print("Celsius: ");
      lcd.setCursor(0,1);
      lcd.print(celsius);
      Serial.print("Celsius: ");
      Serial.println(celsius);
    }
    else if(choice == 'C')
    {
      lcd.clear();
      lcd.print("Kelvin: ");
      lcd.setCursor(0,1);
      lcd.print(kelvin);
      Serial.print("Kelvin: ");
      Serial.println(kelvin);
    }
    else if(choice == 'D')
    {
      Serial.print("Avg C: ");
      Serial.println(avgC);
      Serial.print("Avg F: ");
      Serial.println(avgF);
      Serial.print("Avg K: ");
      Serial.println(avgK);
      
      lcd.clear();
      lcd.print("Avg C: ");
      lcd.print(avgC);
      lcd.setCursor(0,1);
      lcd.print("Avg F: ");
      lcd.print(avgF);
      
	  delay(1000);
      lcd.clear();
      lcd.print("Avg K: ");
      lcd.print(avgK);
    }
    else
    {
      //If user doesn't comply, tell them it's wrong
      Serial.print("Invalid Choice."); 
    }
    
    Serial.println("Action completed.");
    Serial.println("Menu closed.");
    Serial.println(""); //Print new line for clarity
    
    //On second button press, return to initial temperature display
    while (buttonState == true) 
    {
      if (digitalRead(BUTTON_PIN) == HIGH)
      {
        buttonState = false;
      }
    }
    delay(200); //Add small delay to prevent multiple readings from button
  }
  delay(1000); //Wait 1 seconds
  lcd.clear();
}
