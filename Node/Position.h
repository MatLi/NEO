/*
 * Fil: Position.h
 * Programmerare: Emil Karlsson <emika583@student.liu.se>
 * Datum: 2012-11-20
 *
 * En klass för representation av koordinater och vektorer i planet som används av Node.
 */

#ifndef POSITION_HH
#define POSITION_HH

#include <cmath>

class Position
{
 public:
  //Konstruktorer och destruktor
  Position(double xpos_new=0, double ypos_new=0)
    : xpos_(xpos_new), ypos_(ypos_new) {}

  Position(const Position& pos_new)
    : xpos_(pos_new.xpos_), ypos_(pos_new.ypos_) {}

  ~Position() = default;

  // Medlemsfunktioner
  double xpos() const;
  double ypos() const;
  Position difference(Position pos) const;
  void rotate(Position center, double angle);
  void move_to(Position pos_new);
  void mirror(Position point, Position vect);
  void translate(Position vect);

 private:
  const double PI = 3.1415926535;
  double xpos_;
  double ypos_;
};

#endif
