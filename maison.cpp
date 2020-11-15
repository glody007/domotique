#include "maison.h"
#include "piece.h"

using namespace std;

Maison::Maison(int nombrePieces, Piece *pieces)
{
  this->pieces = pieces;
  this->nombrePieces = nombrePieces;
}

Piece * Maison::getPieces() { return pieces; }

Piece Maison::getPiece(int numero) { return pieces[numero - 1]; }

int Maison::getNombrePieces() { return nombrePieces; }

void Maison::updateFromCommande(char *commande)
{
  if(commande[1] == 'L' or commande[1] == 'l')
  {
    updateLampe(getPiecePosition(commande[2]), commande[0]);
  }
  else
  {
    updatePrise(getPiecePosition(commande[2]), commande[0]);
  }
}

void Maison::updateLampe(int piecePosition, char commandeLampe)
{
  if(commandeLampe == 'A' or commandeLampe == 'a')
  {
    pieces[piecePosition].allumerLampe();
  }
  else
  {
    pieces[piecePosition].eteindreLampe();
  }
}

void Maison::updatePrise(int piecePosition, char commandePrise)
{
  if(commandePrise == 'A' or commandePrise == 'a')
  {
    pieces[piecePosition].alimenterPrise();
  }
  else
  {
    pieces[piecePosition].deconnecterPrise();
  }
}

int Maison::getPiecePosition(char numero)
{
  return getNumeroPiece(numero) - 1;
}

int Maison::getNumeroPiece(char numero)
{
  return numero - 48;
}
