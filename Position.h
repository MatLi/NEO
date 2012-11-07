#ifndef POSITION_HH
#define POSITION_HH

class Position
{
  Position() = default;
  ~Position() = default;

  int xpos() const;
  int ypos() const;

  void rotate(Position, double);
  void mirror(Position, Position);
  void translate(Position);

 private:
  int xpos_;
  int ypos_;
}

#endif
