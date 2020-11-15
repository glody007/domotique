#ifndef PIECE_HPP_
#define PIECE_HPP_

class Piece
{
  private:
    bool isInterrupteurOn, isPriseAlimenter, isLampeOn, presence;
    int pinInterrupteur, pinPrise, pinPresenceSensor, pinLampe, tresholdVoltage;

    void updateIfPossible(bool isInterrupteurOn, bool presence);

    bool etatIsDifferent(bool isInterrupteurOn, bool presence);

    void update(bool isInterrupteurOn, bool presence);

    void updateFromPresence(bool presence);

    void updateFromInterrupteur(bool isInterrupteurOn);

  public:

    static const int HIGH_VOLTAGE = 5, LOW_VOLTAGE = 0;

    Piece();

    Piece(int pinInterrupteur, int pinPrise, int pinPresenceSensor, int pinLampe);

    Piece(int pinInterrupteur, int pinPrise, int pinPresenceSensor, int pinLampe, int tresholdVoltage);

    bool getIsLampeOn();

    bool getIsInterrupteurOn();

    bool getPresence();

    int getPinInterrupteur();

    int getPinPrise();

    int getPinLampe();

    int getPinPresenceSensor();

    void allumerLampe();

    void eteindreLampe();

    bool getIsPriseAlimenter();

    void alimenterPrise();

    void deconnecterPrise();

    void update();

    void updateFromData(float interrupteurState, int presenceState);

    bool boolFromState(float state);
};

#endif
