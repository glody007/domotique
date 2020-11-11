#include <string>
#include "piece.h"

using namespace std;

Piece::Piece()
{
  isInterrupteurOn = false;
  isPriseAlimenter = false;
  isLampeOn = false;
  presence = false;
}

Piece::Piece(int pinInterrupteur, int pinPrise, int pinPresenceSensor, int pinLampe)
{
  isInterrupteurOn = false;
  isPriseAlimenter = false;
  isLampeOn = false;
  presence = false;
  this->pinInterrupteur = pinInterrupteur;
  this->pinPrise = pinPrise;
  this->pinPresenceSensor = pinPresenceSensor;
  this->pinLampe = pinLampe;
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

string Piece::etatLampe()
{
  if(isLampeOn){
    return "La lampe est allume";
  }
  return "La lampe est eteinte";
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

string Piece::etatPrise()
{
  if(isPriseAlimenter){
    return "La prise est alimente";
  }
  return "La prise n'est pas alimente";
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

void Piece::updateFromData(int interrupteurState, int presenceState) {
  update(boolFromState(interrupteurState), boolFromState(presenceState));
}

bool Piece::boolFromState(int state) {
  int delta = state - LOW_VOLTAGE;
  if(delta < 1) {
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
  isLampeOn = isInterrupteurOn;
  this->isInterrupteurOn = isInterrupteurOn;
}
