/*
 * Fil: Position.cc
 * Programmerare: Emil Karlsson <emika583@student.liu.se>
 * Datum: 2012-11-20
 *
 * En klass för representation av koordinater och vektorer i planet som används av Node.
 */

#include <cmath>
#include "Position.h"

/*
 * Position::xpos()
 * Returnerar Positions x-koordinat.
 */
int Position::xpos() const
{
  return xpos_;
}

/*
 * Position::ypos()
 * Returnerar Positions y-koordinat.
 */
int Position::ypos() const
{
  return ypos_;
}

/*
 * Position::difference(Position pos)
 * Returnerar vektorn från *this till pos.
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
  // Hjälpvariabler
  double xpos_help = xpos_ - center.xpos_;
  double ypos_help = ypos_ - center.ypos_;
    
  angle = angle * (PI/180); // konverterar vinkeln till radianer

  //Uträkning
  xpos_ = xpos_help*cos(angle) - ypos_help*sin(angle);
  ypos_ = xpos_help*sin(angle) + ypos_help*cos(angle);
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
 * Speglar position genom linjen vect som går igenom punkten point
 */
void Position::mirror(Position point, Position vect)
{
  // Hjälpvariabler
  double vect_xpos_help = vect.xpos_ - point.xpos_;
  double vect_ypos_help = vect.ypos_ - point.ypos_;

  double xpos_help = xpos_ - point.xpos_;
  double ypos_help = ypos_ - point.ypos_;

  // Uträkning
  xpos_ = 2*(vect_xpos_help*xpos_help+vect_xpos_help*xpos_help)
    /(vect_xpos_help*vect_xpos_help+vect_ypos_help*vect_ypos_help)
    *vect_xpos_help
    -xpos_help + point.xpos_;

  ypos_ = 2*(vect_xpos_help*xpos_help+vect_xpos_help*xpos_help)
    /(vect_xpos_help*vect_xpos_help+vect_ypos_help*vect_ypos_help)
    *vect_ypos_help
    -ypos_help + point.ypos_;

  // Skulle kunna skrivas snyggare med delresultat (t.ex. normer) i 
  // hjälpvariabler och/eller funktioner
  // /Jonas
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
