#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <array>
#include <math.h>
#include "Renderer.h"

class Color
{
public:
  Color(GLfloat, GLfloat, GLfloat, GLfloat);
  Color();
  GLfloat r,g,b,a;
};

class Shape
{
public:
  Shape(float, float);
  Shape();
  virtual ~Shape();
  virtual void draw();
  virtual void update() = 0;

  static std::vector<Shape *> render_list;

protected:
  virtual void* getGlCoords() = 0;
  virtual int getNPoints() = 0;
  float x, y;

  GLenum shapeComponent;  
  Color color;
};

class Rectangle : public Shape
{
public:
  Rectangle(float, float, float, float);
  void update() override;

protected:
  void* getGlCoords() override { return glCoords;}; 
  int getNPoints() override { return 4;};
  float glCoords[4][2]; // 4 corners
  float w, h;
};

class Line : public Shape
{
public:
  Line(float = 0, float = 0, float = 0, float = 0);
  void update() override;

protected:
  void* getGlCoords() override { return glCoords;};  
  int getNPoints() override { return 2;};
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
  void* getGlCoords() override { return &glCoords[0];}; 
  int getNPoints() override { return glCoords.size();};
  std::vector<std::array<float, 2>> glCoords;
  float r;
};

#endif