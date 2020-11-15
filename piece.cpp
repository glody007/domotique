#include "piece.h"

using namespace std;

Piece::Piece() : Piece::Piece(2, 3, 4, 5, Piece::LOW_VOLTAGE) {}

Piece::Piece(int pinInterrupteur, int pinPrise, int pinPresenceSensor, int pinLampe) :
            Piece::Piece(pinInterrupteur, pinPrise, pinPresenceSensor, pinLampe, Piece::LOW_VOLTAGE) {}

Piece::Piece(int pinInterrupteur, int pinPrise, int pinPresenceSensor, int pinLampe, int tresholdVoltage)
{
  isInterrupteurOn = false;
  isPriseAlimenter = false;
  isLampeOn = false;
  presence = false;
  this->pinInterrupteur = pinInterrupteur;
  this->pinPrise = pinPrise;
  this->pinPresenceSensor = pinPresenceSensor;
  this->pinLampe = pinLampe;
  this->tresholdVoltage = tresholdVoltage;
}

int Piece::getPinInterrupteur()
{
  return pinInterrupteur;
}

int Piece::getPinPrise()
{
  return pinPrise;
}

int Piece::getPinLampe()
{
  return pinLampe;
}

int Piece::getPinPresenceSensor()
{
  return pinPresenceSensor;
}

bool Piece::getIsLampeOn()
{
  return isLampeOn;
}

bool Piece::getIsInterrupteurOn()
{
  return isInterrupteurOn;
}

bool Piece::getPresence()
{
  return presence;
}

void Piece::allumerLampe()
{
  isLampeOn = true;
}

void Piece::eteindreLampe()
{
  isLampeOn = false;
}

bool Piece::getIsPriseAlimenter()
{
  return isPriseAlimenter;
}

void Piece::alimenterPrise()
{
  isPriseAlimenter = true;
}

void Piece::deconnecterPrise()
{
  isPriseAlimenter = false;
}

void Piece::update() {

}

void Piece::updateFromData(float interrupteurState, int presenceState) {
  updateIfPossible(boolFromState(interrupteurState), presenceState);
}

bool Piece::boolFromState(float state) {
  if(state <= tresholdVoltage) {
    return false;
  }
  return true;
}

void Piece::updateIfPossible(bool isInterrupteurOn, bool presence)
{
  if(etatIsDifferent(isInterrupteurOn, presence))
  {
    update(isInterrupteurOn, presence);
  }
}

bool Piece::etatIsDifferent(bool isInterrupteurOn, bool presence) {
  if(this->isInterrupteurOn != isInterrupteurOn ||
     this->presence != presence)
  {
    return true;
  }
  return false;
}

void Piece::update(bool isInterrupteurOn, bool presence) {
  if(this->presence != presence){
    updateFromPresence(presence);
  }
  else
  {
    updateFromInterrupteur(isInterrupteurOn);
  }
}

void Piece::updateFromPresence(bool presence)
{
  isLampeOn = presence;
  this->presence = presence;
}

void Piece::updateFromInterrupteur(bool isInterrupteurOn) {
  isLampeOn = !isLampeOn;
  this->isInterrupteurOn = isInterrupteurOn;
}
