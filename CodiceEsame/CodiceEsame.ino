// includo le librerie 
#include <SoftwareSerial.h>

SoftwareSerial esp8266(3, 2); //RX pin = 3, TX pin = 2

//definisco le variabile 
#define DEBUG true //variabile booleana necessaria per vedere sulla porta seriale i messaggi fra il modulo esp8266 e l'Arduino
int state = 5; //definisco il numero di stati possibili (5 = stai fermo)
//assegno a ogni pin utillizato un nome
const int motor1Pin1 = 5;
const int motor1Pin2 = 6;
const int motor2Pin1 = 9;
const int motor2Pin2 = 10;

int motorSpeed = 150; //imposto la  velocità dei due mototi DC

//*****
//SETUP
//*****
void setup()
{
  //setto i pin che fungeranno da output
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  
  //inizio la comunicazione sulla porta seriale
  Serial.begin(115200);
  esp8266.begin(115200);
  
  sendData("AT+RST\r\n", 2000, DEBUG); //resetto il modulo
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG); // faccio collegare l'ESP8266 (se avviene in maiera coretta restiturà ok)
  sendData("AT+CWJAP=\"MotoG(5)Plus6843\",\"00000000\"\r\n", 2000, DEBUG); //collegati alla rete Wi-Fi con nome xxxxxxxx e password yyyyyyyyyy(variabili in base alla rete)
  delay(5000); //aspetta per la connessione
  sendData("AT+CIFSR\r\n", 1000, DEBUG); // mostra l'indirizzo IP
  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG); //abilita una conesione multipla (massimo 4)
  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG); //  avvia il web server sulla porta 80
}

//*********
//MAIN LOOP
//*********
void loop()
{

  if (esp8266.available())  // se è disponibile il modulo 
  {
    if (esp8266.find("+IPD,")) // se c'è un messaggio
    {
      String msg;
      esp8266.find("?"); //cerca il messaggio
      msg = esp8266.readStringUntil(' '); //leggi il messaggio
      String command = msg.substring(0, 3); //prendi i primi  3 caratteri
      Serial.println(command);// stampa sulla porta seriale
           
      //vai indietro
      if(command == "cm1") {
          state = 1;
      } 

      //vai avanti
     if(command == "cm2") {
          state = 2;
      } 

      //andare a sinistra
      if(command == "cm3") {
          state = 3;
       }
       
       //andare a destra
       if(command == "cm4") {
          state = 4;
       }

       //stai fermo   
       if(command == "cm5") {
          state = 5;
       }

    }
  }
  
  //STATO 1: vai indietro
  if (state == 4) {  
    digitalWrite(motor1Pin1, LOW);
    analogWrite(motor1Pin2, motorSpeed);
    digitalWrite(motor2Pin1, LOW);
    analogWrite(motor2Pin2, motorSpeed);
    }
  // STATO 1: vai a destra
  if (state == 1) {
    analogWrite(motor1Pin1, motorSpeed);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    analogWrite(motor2Pin2, motorSpeed);
  }
  //STATO 2: vai a sinistra
  if (state == 2) {
     digitalWrite(motor1Pin1, LOW);
    analogWrite(motor1Pin2, motorSpeed);
    analogWrite(motor2Pin1, motorSpeed);
    digitalWrite(motor2Pin2, LOW);
  }
 //STATO 3: vai avanti
  if (state == 3) {
    analogWrite(motor1Pin1, motorSpeed);
    digitalWrite(motor1Pin2, LOW);
    analogWrite(motor2Pin1, motorSpeed);
    digitalWrite(motor2Pin2, LOW);
  }

 //STATO 5: stai fermo
  if (state == 5) {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
  }
  
}

//*******************
// Funzione ausiliarie
//*******************
String sendData(String command, const int timeout, boolean debug)
{
  String response = "";
  esp8266.print(command);// invia il carattere letto all'esp8266
  long int time = millis();
  while ( (time + timeout) > millis())// aspetto qualche momento
  {
    while (esp8266.available())// se il modulo è disponibile
    {
      char c = esp8266.read();// legge un solo carattere.
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}
