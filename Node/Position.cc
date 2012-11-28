/*
 * Fil: Position.cc
 * Programmerare: Emil Karlsson <emika583@student.liu.se>,
 *                David Larsson <davla210@student.liu.se> (endast funktionen 
 * mirror och mindre fix i rotate)
 * Datum: 2012-11-21
 *
 * En klass för representation av koordinater och vektorer i planet som används
 * av Node.
 */

#include <cmath>
#include "Position.h"

/*
 * Position::xpos()
 * Returnerar Positions x-koordinat.
 */
double
Position::xpos() const
{
  return xpos_;
}

/*
 * Position::ypos()
 * Returnerar Positions y-koordinat.
 */
double
Position::ypos() const
{
  return ypos_;
}

/*
 * Position::difference(Position pos)
 * Returnerar vektorn från *this till pos.
 */
Position
Position::difference(Position pos) const
{
  double xpos_new = pos.xpos_ - xpos_;
  double ypos_new = pos.ypos_ - ypos_;

  return Position(xpos_new, ypos_new);
}

/*
 * Position::rotate(Position center, double angle)
 * Roterar Position angle grader runt punkten center
 */
void
Position::rotate(Position center, double angle)
{
  // Translaterar så att centrum är "(0,0)"
  this->translate(Position(- center.xpos_, - center.ypos_));
    
  // Konverterar vinkeln till radianer
  angle = angle * (PI/180); 

  // Uträkning
  double new_xpos_ = xpos_*cos(angle) - ypos_*sin(angle);
  double new_ypos_ = xpos_*sin(angle) + ypos_*cos(angle);
  xpos_ = new_xpos_;
  ypos_ = new_ypos_;
  
  // Translaterar tillbaka till ursprungskoordinatsystemet
  this->translate(center);
}

/*
 * Position::move_to(Position pos_new)
 * Flyttar Position till en ny position
 */
void
Position::move_to(Position pos_new)
{
  xpos_ = pos_new.xpos_;
  ypos_ = pos_new.ypos_;
}

/*
 * Position::mirror(Position point, Position vect)
 * Speglar position genom linjen med riktningsvektor vect som går genom
 * punkten point
 */
void
Position::mirror(Position point, Position vect)
{
  /* Normen i kvadrat av vect. */
  double vect_norm_2 = vect.xpos()*vect.xpos() + vect.ypos()*vect.ypos();
  /* Skalärfaktorn för projektionen på vektorn vect. */
  double scale = (vect.xpos()*xpos_ + vect.ypos()*ypos_)/vect_norm_2;
  /* Projektionen på vektorn vect. */
  Position projection(scale*vect.xpos(),scale*vect.ypos());

  /* Projektionen på normalen till vect. */
  Position normal_projection(xpos_ - projection.xpos(),
			     ypos_ - projection.ypos());

  /* Se till att vi är på rätt linje och spegla med hjälp av projektionen på
   * normalen. Flytta sedan tillbaka till ursprungligt koordinatsystem.
   */
  this->translate(Position(-point.xpos(),-point.ypos()));
  xpos_ = xpos_ - 2*normal_projection.xpos();
  ypos_ = ypos_ - 2*normal_projection.ypos();
  this->translate(point);
  return;
}

  
/*
 * Position::translate(Position vect)
 * Translaterar Position med vektorn vect
 */
void
Position::translate(Position vect)
{
  xpos_ += vect.xpos_;
  ypos_ += vect.ypos_;
}
