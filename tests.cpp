#include <gtest/gtest.h>
#include <iostream>
#include "piece.h"
#include "maison.h"

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
  Piece piece1 = Piece();
  ASSERT_EQ(true, piece1.boolFromState(Piece::HIGH_VOLTAGE));
  ASSERT_EQ(false, piece1.boolFromState(Piece::LOW_VOLTAGE));
  int interrupteur = 2, prise = 3, presenceSensor = 4, lampe = 5, tresholdVoltage = 2;
  Piece piece2 = Piece(interrupteur, prise, presenceSensor, lampe, tresholdVoltage);
  ASSERT_EQ(true, piece2.boolFromState(Piece::HIGH_VOLTAGE));
  ASSERT_EQ(false, piece2.boolFromState(tresholdVoltage));
  ASSERT_EQ(false, piece2.boolFromState(tresholdVoltage - 1));
  ASSERT_EQ(true, piece2.boolFromState(tresholdVoltage + 1));
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

  //Eteindre avec le telephone
  piece.eteindreLampe();
  ASSERT_EQ(false, piece.getIsLampeOn());
  //Allumer en mettant l'interrupteur a OFF
  piece.updateFromData(Piece::LOW_VOLTAGE, Piece::HIGH_VOLTAGE);
  ASSERT_EQ(true, piece.getIsLampeOn());
  //Eteindre en mettant l'interrupteur a ON
  piece.updateFromData(Piece::HIGH_VOLTAGE, Piece::HIGH_VOLTAGE);
  ASSERT_EQ(false, piece.getIsLampeOn());
}

TEST(MaisonTest, constructor) {
  Piece piece1 = Piece();
  Piece piece2 = Piece();
  Piece pieces[] = {piece1, piece2};
  Maison maison = Maison(2, pieces);
  ASSERT_EQ(2, maison.getNombrePieces());
  ASSERT_EQ(&(pieces[0]), &(maison.getPieces()[0]));
}

TEST(MaisonTest, commande) {
  Piece piece1 = Piece();
  Piece piece2 = Piece();
  Piece pieces[] = {piece1, piece2};
  Maison maison = Maison(2, pieces);
  ASSERT_EQ(false, piece1.getIsLampeOn());
  char allumerLampe1[] = "AL1";
  char allumerLampe2[] = "AL2";
  char eteindreLampe1[] = "EL1";
  char eteindreLampe2[] = "EL2";
  maison.updateFromCommande(allumerLampe1);
  ASSERT_EQ(true, maison.getPiece(1).getIsLampeOn());
  maison.updateFromCommande(eteindreLampe1);
  ASSERT_EQ(false, maison.getPiece(1).getIsLampeOn());
  ASSERT_EQ(false, maison.getPiece(2).getIsLampeOn());
  maison.updateFromCommande(allumerLampe2);
  ASSERT_EQ(true, maison.getPiece(2).getIsLampeOn());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
