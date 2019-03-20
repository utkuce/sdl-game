#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <array>
#include <math.h>
#include "Renderer.h"

class Shape
{
public:
  Shape(float, float);
  Shape();
  virtual ~Shape();
  virtual void draw() = 0;
  virtual void update() = 0;

  static std::vector<Shape *> render_list;

protected:
  float x, y;
};

class Rectangle : public Shape
{
public:
  Rectangle(float, float, float, float);
  void update() override;
  void draw() override;

protected:
  float glCoords[4][2]; // 4 corners
  float w, h;
};

class Line : public Shape
{
public:
  Line(float = 0, float = 0, float = 0, float = 0);
  void update() override;
  void draw() override;

protected:
  float glCoords[2][2]; // 2 points
  float x2, y2;
};

class Circle : public Shape
{
public:
  Circle(float, float, float);
  Circle();
  void update() override;
  void draw() override;

protected:
  std::vector<std::array<float, 2>> glCoords;
  float r;
};

#endif
