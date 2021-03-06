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

void Shape::draw() 
{
  // Set color
  GLint location = glGetUniformLocation(Renderer::gProgramID, "in_Color");
  glUniform4f(location, color.r, color.g, color.b, color.a); // rgba

  int nPoints = getNPoints();

  //Create VBO
  glGenBuffers( 1, &Renderer::gVBO );
  glBindBuffer( GL_ARRAY_BUFFER, Renderer::gVBO );
  glBufferData( GL_ARRAY_BUFFER, 2 * nPoints * sizeof(GLfloat), getGlCoords(), GL_DYNAMIC_DRAW );

  //Create IBO
  GLuint indexData[nPoints];
  for (int i=0; i<nPoints; i++)
    indexData[i] = i;

  glGenBuffers( 1, &Renderer::gIBO );
  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, Renderer::gIBO );
  glBufferData( GL_ELEMENT_ARRAY_BUFFER, nPoints * sizeof(GLuint), indexData, GL_DYNAMIC_DRAW );

  //Enable vertex position
  glEnableVertexAttribArray( Renderer::gVertexPos2DLocation );
  //Set vertex data 
  glBindBuffer( GL_ARRAY_BUFFER, Renderer::gVBO );
  glVertexAttribPointer( Renderer::gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL ); 
  //Set index data and render 
  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, Renderer::gIBO ); 

  //Draw
  glDrawElements( shapeComponent, getNPoints(), GL_UNSIGNED_INT, NULL ); 
  
  //Disable vertex position 
  glDisableVertexAttribArray( Renderer::gVertexPos2DLocation ); 
}

Rectangle::Rectangle(float x, float y, float w, float h) : Shape(x, y)
{
  this->w = w;
  this->h = h;

  shapeComponent = GL_TRIANGLE_FAN;
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


Line::Line(float x1, float y1, float x2, float y2) : Shape(x1, y1)
{
  this->x2 = x2;
  this->y2 = y2;

  shapeComponent = GL_LINES;
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

Circle::Circle(float x, float y, float r) : Shape(x + r, y + r)
{
  this->r = r;
  shapeComponent = GL_LINE_LOOP;
}

Circle::Circle()
{
  shapeComponent = GL_LINE_LOOP;
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
  Shape::draw();
  glLineWidth(1);
}

Color::Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
  this->r = r; 
  this->g = g; 
  this->b = b; 
  this->a = a;
}

Color::Color() 
{
  r=1;
  g=1;
  b=1;
  a=1;
}