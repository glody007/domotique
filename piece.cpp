#include "piece.h"

using namespace std;

Piece::Piece() : Piece::Piece(2, 3, 4, 5, Piece::LOW_VOLTAGE) {}

Piece::Piece(int pinInterrupteur, int pinPrise, int pinPresenceSensor, int pinLampe) :
            Piece::Piece(pinInterrupteur, pinPrise, pinPresenceSensor, pinLampe, Piece::LOW_VOLTAGE) {}

Piece::Piece(int pinInterrupteur, int pinPrise, int pinPresenceSensor, int pinLampe, int tresholdVoltage)
{
  isInterrupteurOn = false;
  isInterrupteurPriseOn = false;
  isPriseAlimenter = false;
  isLampeOn = false;
  presence = false;
  isNight = true;
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

const char * Piece::getEtatLampe()
{
    if(isLampeOn) return "Lampe allumer";
    return "Lampe eteinte";
}

const char * Piece::getEtatPrise()
{
    if(isPriseAlimenter) return "Prise alimenter";
    return "Prise deconnecter";
}

bool Piece::getIsInterrupteurOn()
{
  return isInterrupteurOn;
}

bool Piece::getIsInterrupteurPriseOn()
{
  return isInterrupteurPriseOn;
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

void Piece::updateFromDataAndHour(float interrupteurState, int presenceState, bool isNight) {
  this->isNight = isNight;
  updateFromData(interrupteurState, presenceState);
}

void Piece::updatePriseFromData(float interrupteurPriseState) {
  bool isInterrupteurPriseOn = boolFromState(interrupteurPriseState);
  if(this->isInterrupteurPriseOn != isInterrupteurPriseOn){
    isPriseAlimenter = !isPriseAlimenter;
    this->isInterrupteurPriseOn = isInterrupteurPriseOn;
  }
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
  this->presence = presence;
  if(isNight && presence)
  {
    isLampeOn = true;
  }
  else
  {
    isLampeOn = false;
  }
}

void Piece::updateFromInterrupteur(bool isInterrupteurOn) {
  isLampeOn = !isLampeOn;
  this->isInterrupteurOn = isInterrupteurOn;
}
