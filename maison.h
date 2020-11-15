#ifndef MAISON_HPP_
#define MAISON_HPP_

#include "piece.h"

class Maison
{
  private:
    Piece *pieces;
    int nombrePieces;

  public:

    Maison(int nombrePieces, Piece *pieces);

    Piece * getPieces();

    Piece getPiece(int numero);

    int getNombrePieces();

    void updateFromCommande(char *commande);

    void updateLampe(int piecePosition, char commandeLampe);

    void updatePrise(int piecePosition, char commandePrise);

    int getNumeroPiece(char numero);

    int getPiecePosition(char numero);
};

#endif
