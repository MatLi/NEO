/*
 * Fil: Position.cc
 * Programmerare: Emil Karlsson <emika583@student.liu.se>
 * Datum: 2012-11-21
 *
 * En klass f�r representation av koordinater och vektorer i planet som anv�nds av Node.
 */

#include <cmath>
#include "Position.h"

/*
 * Position::xpos()
 * Returnerar Positions x-koordinat.
 */
double Position::xpos() const
{
  return xpos_;
}

/*
 * Position::ypos()
 * Returnerar Positions y-koordinat.
 */
double Position::ypos() const
{
  return ypos_;
}

/*
 * Position::difference(Position pos)
 * Returnerar vektorn fr�n *this till pos.
 */
Position Position::difference(Position pos) const
{
  double xpos_new = pos.xpos_ - xpos_;
  double ypos_new = pos.ypos_ - ypos_;

  return Position(xpos_new, ypos_new);
}

/*
 * Position::rotate(Position center, double angle)
 * Roterar Position angle grader runt punkten center
 */
void Position::rotate(Position center, double angle)
{
  // Translaterar s� att vi st�r i "(0,0)"
  this->translate(Position(- center.xpos_, - center.ypos_));
    
  // Konverterar vinkeln till radianer
  angle = angle * (PI/180); 

  // Utr�kning
  xpos_ = xpos_help*cos(angle) - ypos_help*sin(angle);
  ypos_ = xpos_help*sin(angle) + ypos_help*cos(angle);
  // ---
  // �r hj�lpvariablerna bara bortgl�mda h�r?
  // Fixa eller f�rklara
  // ---

  // Translaterar tillbaka till ursprungskoordinatsystemet
  this->translate(center);
}

/*
 * Position::move_to(Position pos_new)
 * Flyttar Position till en ny position
 */
void Position::move_to(Position pos_new)
{
  xpos_ = pos_new.xpos_;
  ypos_ = pos_new.ypos_;
}

/*
 * Position::mirror(Position point, Position vect)
 * Speglar position genom linjen vect som g�r igenom punkten point
 */
void Position::mirror(Position point, Position vect)
{
  //Translaterar vect och this s� att vi g�r point till (0,0) i v�rt koordinatsystem
  this->translate(Position(- point.xpos_, - point.ypos_));
  vect.translate(Position(- point.xpos_, - point.ypos_));
  // ---
  // Ska vect.translate verkligen g�ras? /Jonas
  // ---

  // Utr�kning av det gemensamma projektionen f�r x- och y-koordinaten i speglingen
  Projection = (vect.xpos_*xpos_+vect.xpos*xpos_)/(vect.xpos_*vect.xpos_+vect.ypos_*vect.ypos_);
  // ---
  // vad �r Projection f�r typ?
  // ---

  // Utr�kningen f�r x- och y-koordinaten
  xpos_ = 2*Projection*vect.xpos_ - xpos_;
  ypos_ = 2*Projection*vect.ypos_ - ypos_;

  // Translaterar tillbaka till ursprungskoordinatsystemet
  this->translate(point);
}
  
/*
 * Position::translate(Position vect)
 * Translaterar Position med vektorn vect
 */
void Position::translate(Position vect)
{
  xpos_ += vect.xpos_;
  ypos_ += vect.ypos_;
}
