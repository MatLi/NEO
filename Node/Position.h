/*
 * Fil: Position.h
 * Programmerare: Emil Karlsson <emika583@student.liu.se>
 * Datum: 2012-11-20
 *
 * En klass för representation av koordinater och vektorer i planet som används av Node.
 */

#ifndef POSITION_HH
#define POSITION_HH

#define _PI_ = 3.14159265359;

#include <math.h>

class Position
{ 
 private:
  double xpos_;
  double ypos_;

 public:
  //Konstruktorer och destruktorer
  Position(xpos_new=0, ypos_new=0)
  {
    xpos_ = xpos_new;
    ypos_ = ypos_new;
  }

  Position(Position pos_new)
  {
    xpos_ = pos_new.xpos_;
    ypos_ = pos_new.ypos_;
  }

  ~Position() = default;

/*
 * Position::xpos()
 * Returnerar Positions x-koordinat.
 */
  int xpos() const
  {
    return xpos_;
  }

/*
 * Position::ypos()
 * Returnerar Positions y-koordinat.
 */
  int ypos() const;
  {
    return ypos_;
  }

/*
 * Position::difference(Position pos)
 * Returnerar vektorn mellan två position.
 */
  Position difference(Position pos) const
  {
    xpos_new = abs(pos.xpos_ - xpos_);
    ypos_new = abs(pos.ypos_ - ypos_);

    return Position(xpos_new, ypos_new);
  }

/*
 * Position::rotate(Position center, double angle)
 * Roterar Position angle grader runt punkten center
 */
  void rotate(Position center, double angle)
  {
    // Hjälpvariabler
    xpos_help = xpos_ - center.xpos_;
    ypos_help = ypos_ - center.ypos_;
    
    angle = angle * (_PI_/180);

    //Uträkning
    xpos_ = xpos_help*cos(angle) - ypos_help*sin(angle);
    ypos_ = xpos_help*sin(angle) + ypos_help*cos(angle);
  }

/*
 * Position::move_to(Position pos_new)
 * Flyttar Position till en ny position
 */
  void move_to(Position pos_new)
  {
    xpos_ = pos_new.xpos_;
    ypos_ = pos_new.ypos_;
  }

/*
 * Position::mirror(Position point, Position vect)
 * Speglar position genom linjen vect som går igenom punkten point
 */
  void mirror(Position point, Position vect)
  {
    // Hjälpvariabler
    vect_xpos_help = vect.xpos_ - point.xpos_;
    vect_ypos_help = vect.ypos_ - point.ypos_;

    xpos_help = xpos_ - point.xpos_;
    ypos_help = ypos_ - point.ypos_;

    // Uträkning
    xpos_ = 2*(vect_xpos_help*xpos_help+vect_xpos_help*xpos_help)
      /(vect_xpos_help*vect_xpos_help+vect_ypos_help*vect_ypos_help)
      *vect_xpos_help
      -xpos_help + point.xpos_;

    ypos_ = 2*(vect_xpos_help*xpos_help+vect_xpos_help*xpos_help)
      /(vect_xpos_help*vect_xpos_help+vect_ypos_help*vect_ypos_help)
      *vect_ypos_help
      -ypos_help + point.ypos_;
  }
  
/*
 * Position::translate(Position vect)
 * Translaterar Position med vektorn vect
 */
  void translate(Position vect)
  {
    xpos_ += vect.xpos_;
    ypos_ += vect.ypos_;
  }
}

#endif
