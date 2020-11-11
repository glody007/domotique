#ifndef PIECE_HPP_
#define PIECE_HPP_

#include <string>

class Piece
{
  private:
    bool isInterrupteurOn, isPriseAlimenter, isLampeOn, presence;
    int pinInterrupteur, pinPrise, pinPresenceSensor; int pinLampe;

    void updateIfPossible(bool isInterrupteurOn, bool presence);

    bool etatIsDifferent(bool isInterrupteurOn, bool presence);

    void update(bool isInterrupteurOn, bool presence);

    void updateFromPresence(bool presence);

    void updateFromInterrupteur(bool isInterrupteurOn);

  public:

    static const int HIGH_VOLTAGE = 5, LOW_VOLTAGE = 0;

    Piece();

    Piece(int pinInterrupteur, int pinPrise, int pinPresenceSensor, int pinLampe);

    bool getIsLampeOn();

    bool getIsInterrupteurOn();

    bool getPresence();

    int getPinInterrupteur();

    int getPinPrise();

    int getPinLampe();

    int getPinPresenceSensor();

    std::string etatLampe();

    void allumerLampe();

    void eteindreLampe();

    bool getIsPriseAlimenter();

    std::string etatPrise();

    void alimenterPrise();

    void deconnecterPrise();

    void update();

    void updateFromData(int interrupteurState, int presenceState);

    bool boolFromState(int state);
};

#endif
