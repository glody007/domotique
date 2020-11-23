#include <piece.h>
#include <maison.h>

//Piece(int pinInterrupteur, int pinPrise, int pinPresenceSensor, int pinLampe, int tresholdVoltage);
Piece piece1 = Piece(A1, A6, 2, 30, 2);
Piece piece2 = Piece(A2, A6, 3, 31, 2);
Piece piece3 = Piece(A3, A6, 53, 32, 2);
Piece piece4 = Piece(A4, A6, 4, 33, 2);
Piece piece5 = Piece(A5, A6, 5, 34, 2);

Piece pieces[] = {piece1, piece2, piece3, piece4, piece5};

Maison maison = Maison(5, pieces);

void setup() 
{
  for(int i = 0; i < maison.getNombrePieces(); i++)
  {
    pinMode(maison.getPieces()[i].getPinLampe(),OUTPUT);
    pinMode(maison.getPieces()[i].getPinPresenceSensor(),INPUT);
  }
  Serial.begin(9600);
}

void loop() 
{
  updateMaison();
}

void updateMaison()
{
  updateFromCommande();
  updateFromSensor();
  sendCommandeToMaison();
  delay(200);  
}

void updateFromCommande()
{
  if(Serial.available())
  {
    char commande[4];
    String commandeString = Serial.readStringUntil('\n'); 
    commandeString.toCharArray(commande, 4);
    maison.updateFromCommande(commande);
  }
}

void updateFromSensor()
{
  for(int i = 0; i < maison.getNombrePieces(); i++)
  {
    updatePiece(maison.getPieces()[i]);
  }
}

void sendCommandeToMaison()
{
  for(int i = 0; i < maison.getNombrePieces(); i++)
  {
    sendCommandeToPiece(maison.getPieces()[i]);
  }
}

void updatePiece(Piece &piece)
{
  piece.updateFromData(voltageInterrupteurValue(piece), presenceSensorState(piece));
}

void sendCommandeToPiece(Piece &piece)
{
  if(piece.getIsLampeOn())
  {
    allumerLampe(piece);
  }
  else
  {
    eteindreLampe(piece);
  }
  printStates(piece);
}

float voltageInterrupteurValue(Piece piece) { return analogRead(piece.getPinInterrupteur()) * 5 / 1024; }

int presenceSensorState(Piece piece) { return digitalRead(piece.getPinPresenceSensor()); }

void allumerLampe(Piece &piece) 
{
  if(piece.getIsInterrupteurOn())
  {
    digitalWrite(piece.getPinLampe(), LOW);
  }
  else
  {
    digitalWrite(piece.getPinLampe(), HIGH); 
  }
}

void eteindreLampe(Piece &piece) 
{
  if(piece.getIsInterrupteurOn())
  {
    digitalWrite(piece.getPinLampe(), HIGH);
  }
  else
  {
    digitalWrite(piece.getPinLampe(), LOW); 
  }
}

void printStates(Piece piece)
{
  Serial.print("interrupteur : ");
  Serial.println(piece.getIsInterrupteurOn());
  Serial.print("presence : ");
  Serial.println(piece.getPresence());
  Serial.print("lampe : ");
  Serial.println(piece.getIsLampeOn());
}






