#include "Shape.h"

std::vector<Shape *> Shape::render_list;

Shape::Shape(float x, float y)
{
  this->x = x;
  this->y = y;
  render_list.push_back(this);
}

Shape::Shape()
{
  render_list.push_back(this);
}

Shape::~Shape()
{
  std::vector<Shape *>::iterator it = render_list.begin();
  while (*it != this) it++;
  if (it != render_list.end())
    render_list.erase(it);
}

Rectangle::Rectangle(float x, float y, float w, float h) : Shape(x, y)
{
  this->w = w;
  this->h = h;
}

void Rectangle::update()
{
  float coords[4][2] = {{x, y}, {x + w, y}, {x + w, y + h}, {x, y + h}};

  for (int i = 0; i < 4; i++)
    Renderer::translateCoords(coords[i]);

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 2; j++)
      glCoords[i][j] = coords[i][j];
}

void Rectangle::draw()
{
  glColor3f(1, 1, 1);
  glBegin(GL_QUADS);
  for (int i = 0; i < 4; i++)
    glVertex2f(glCoords[i][0], glCoords[i][1]);
  glEnd();
}

Line::Line(float x1, float y1, float x2, float y2) : Shape(x1, y1)
{
  this->x2 = x2;
  this->y2 = y2;
}

void Line::update()
{
  float coords[2][2] = {{x, y}, {x2, y2}};

  for (int i = 0; i < 2; i++)
    Renderer::translateCoords(coords[i]);

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
      glCoords[i][j] = coords[i][j];
}

void Line::draw()
{
  glLineWidth(2);
  glColor3f(1, 0, 0);

  glBegin(GL_LINES);
  for (int i = 0; i < 2; i++)
    glVertex2f(glCoords[i][0], glCoords[i][1]);
  glEnd();
}

Circle::Circle(float x, float y, float r) : Shape(x + r, y + r)
{
  this->r = r;
}

Circle::Circle()
{

}

void Circle::update()
{
  glCoords.clear();

  int dx = -r - 1;

  while (dx++ <= r)
  {
    float corner[2] = {x + dx, y + static_cast<float>(sqrt(r * r - dx * dx))}; //top half
    float cornerMirror[2] = {corner[0], y - (corner[1] - y)};                  //bottom half

    Renderer::translateCoords(corner);
    std::array<float, 2> cc1 = {corner[0], corner[1]};
    glCoords.insert(glCoords.begin() + glCoords.size() / 2, cc1);

    Renderer::translateCoords(cornerMirror);
    std::array<float, 2> cc2 = {cornerMirror[0], cornerMirror[1]};
    glCoords.insert(glCoords.begin() + glCoords.size() / 2 + 1, cc2);
  }
}

void Circle::draw()
{
  glLineWidth(2);
  glColor3f(1, 0, 0);

  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < glCoords.size(); i++)
    glVertex2f(glCoords[i][0], glCoords[i][1]);
  glEnd();
}