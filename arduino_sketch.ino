#include <piece.h>
#include <maison.h>

Piece piece = Piece(A1, 0, 12, 11, 2);

Piece pieces[] = {piece};

Maison maison = Maison(1, pieces);

void setup() {
  pinMode(piece.getPinLampe(),OUTPUT);
  pinMode(piece.getPinPresenceSensor(),INPUT);
  Serial.begin(9600);
}

void allumerLampe(Piece piece) {
   if(piece.getIsInterrupteurOn()){
    digitalWrite(piece.getPinLampe(), LOW);
  }
  else{
    digitalWrite(piece.getPinLampe(), HIGH); 
  }
}

void eteindreLampe(Piece piece) {
   if(piece.getIsInterrupteurOn()){
    digitalWrite(piece.getPinLampe(), HIGH);
  }
  else{
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

void updatePiece(Piece piece)
{
  piece.updateFromData(voltageInterrupteurValue(piece), presenceSensorState(piece));
}

float voltageInterrupteurValue(Piece piece) { return analogRead(piece.getPinInterrupteur()) * 5 / 1024; }

int presenceSensorState(Piece piece) { return digitalRead(piece.getPinPresenceSensor()); }

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
  for(int i = 1; i <= maison.getNombrePieces(); i++)
  {
    updatePiece(maison.getPiece(i));
  }
}

void sendCommandeToPiece(Piece piece)
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

void sendCommandeToMaison()
{
  for(int i = 1; i <= maison.getNombrePieces(); i++)
  {
    sendCommandeToPiece(maison.getPiece(i));
  }
}

void updateMaison()
{
  updateFromCommande();
  updateFromSensor();
  sendCommandeToMaison();
  delay(200);  
}

void loop() {
  updateMaison();
}


