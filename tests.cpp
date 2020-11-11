#include <gtest/gtest.h>
#include <iostream>
#include "piece.h"

TEST(PieceTest, defaultConstructor) {
  Piece piece = Piece();
  ASSERT_EQ(false, piece.getIsLampeOn());
}

TEST(PieceTest, customizeConstructor) {
  int interrupteur = 2, prise = 3, presenceSensor = 4, lampe = 5;
  Piece piece = Piece(interrupteur, prise, presenceSensor, lampe);
  ASSERT_EQ(interrupteur, piece.getPinInterrupteur());
  ASSERT_EQ(prise, piece.getPinPrise());
  ASSERT_EQ(presenceSensor, piece.getPinPresenceSensor());
  ASSERT_EQ(lampe, piece.getPinLampe());
}

TEST(PieceTest, allumerEtEteindreLampe) {
  Piece piece = Piece();
  ASSERT_EQ(false, piece.getIsLampeOn());
  piece.allumerLampe();
  ASSERT_EQ(true, piece.getIsLampeOn());
  piece.eteindreLampe();
  ASSERT_EQ(false, piece.getIsLampeOn());
}

TEST(PieceTest, alimenterEtDeconnecterPrise) {
  Piece piece = Piece();
  ASSERT_EQ(false, piece.getIsPriseAlimenter());
  piece.alimenterPrise();
  ASSERT_EQ(true, piece.getIsPriseAlimenter());
  piece.deconnecterPrise();
  ASSERT_EQ(false, piece.getIsPriseAlimenter());
}

TEST(PieceTest, boolFromState) {
  Piece piece = Piece();
  ASSERT_EQ(true, piece.boolFromState(Piece::HIGH_VOLTAGE));
  ASSERT_EQ(false, piece.boolFromState(Piece::LOW_VOLTAGE));
}

TEST(PieceTest, updateFromData) {
  Piece piece = Piece();
  ASSERT_EQ(false, piece.getIsLampeOn());
  ASSERT_EQ(false, piece.getPresence());

  //Allumer avec l'interrupteur
  piece.updateFromData(Piece::HIGH_VOLTAGE, Piece::LOW_VOLTAGE);
  ASSERT_EQ(true, piece.getIsLampeOn());
  ASSERT_EQ(false, piece.getPresence());
  ASSERT_EQ(true, piece.getIsInterrupteurOn());

  //Toujours present dans la piece
  piece.updateFromData(Piece::HIGH_VOLTAGE, Piece::HIGH_VOLTAGE);
  ASSERT_EQ(true, piece.getIsLampeOn());
  ASSERT_EQ(true, piece.getPresence());
  ASSERT_EQ(true, piece.getIsInterrupteurOn());

  //Eteindre avec l'interrupteur
  piece.updateFromData(Piece::LOW_VOLTAGE, Piece::HIGH_VOLTAGE);
  ASSERT_EQ(false, piece.getIsLampeOn());
  ASSERT_EQ(true, piece.getPresence());
  ASSERT_EQ(false, piece.getIsInterrupteurOn());

  //Allumer avec l'interrupteur
  piece.updateFromData(Piece::HIGH_VOLTAGE, Piece::HIGH_VOLTAGE);
  ASSERT_EQ(true, piece.getIsLampeOn());
  ASSERT_EQ(true, piece.getPresence());
  ASSERT_EQ(true, piece.getIsInterrupteurOn());

  //Quitter la piece
  piece.updateFromData(Piece::HIGH_VOLTAGE, Piece::LOW_VOLTAGE);
  ASSERT_EQ(false, piece.getIsLampeOn());
  ASSERT_EQ(false, piece.getPresence());
  ASSERT_EQ(true, piece.getIsInterrupteurOn());

  //Revenir dans la piece
  piece.updateFromData(Piece::HIGH_VOLTAGE, Piece::HIGH_VOLTAGE);
  ASSERT_EQ(true, piece.getIsLampeOn());
  ASSERT_EQ(true, piece.getPresence());
  ASSERT_EQ(true, piece.getIsInterrupteurOn());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
