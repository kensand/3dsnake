
#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.hpp"
#include "ObjectLoader.hpp"
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <cmath>
#include <math.h>
#include <cstdio>
#include <cstdlib>
#include <X11/Xlib.h>
#include "Object.hpp"







void Object::init(std::string objFile, vmath::vec3 location, vmath::vec3 rotation, GLfloat scale){
  ModelLocation = location;
  ModelRotation = rotation;
  ModelScale = scale;
  drawDistance = 1000;

  std::vector<GLfloat *> lvertices;
  std::vector<GLfloat *> luvs;
  std::vector<GLfloat *> lnorms;

  if(!loadOBJ(objFile.c_str(), lvertices, luvs, lnorms)){
    printf("Error loading suzanne\n");
    throw(1);
  }
  else{
    printf("Loaded Model\n");
  }

  glEnable(GL_DEPTH_TEST);
  glGenVertexArrays( NumVAOs, VAOs );
  glBindVertexArray( VAOs[Triangles] );
  NumVertices = lvertices.size();
  VertexData vertices[NumVertices];

  for(int i = 0; i < lvertices.size(); i++){
    for(int j = 0; j < dims; j++){
      vertices[i].position[j] = lvertices[i][j];
      if(lvertices[i][j] >= -1. && lvertices[i][j] <= 1.){
        vertices[i].color[j] = abs(lvertices[i][j] / 1.0);
      }
      else{
        vertices[i].color[j] = 1.0;
      }
      vertices[i].color[3] = 1.0;
    }
  }

  glCreateBuffers( NumBuffers, Buffers );
  glBindBuffer( GL_ARRAY_BUFFER, Buffers[ArrayBuffer] );
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
               vertices, GL_STATIC_DRAW);

  ShaderInfo  shaders[] = {
    { GL_VERTEX_SHADER, "../media/shaders/triangles/triangles.vert" },
    { GL_FRAGMENT_SHADER, "../media/shaders/triangles/triangles.frag" },
    { GL_NONE, NULL }
  };

  GLuint program = LoadShaders( shaders);
  glUseProgram( program );
  modelViewLoc = glGetUniformLocation(program, "ModelViewProjectionMatrix");

  glVertexAttribPointer( vColor, color_dims, GL_FLOAT,
                         GL_FALSE, sizeof(VertexData), BUFFER_OFFSET(0) );
  glVertexAttribPointer(vPosition, dims, GL_FLOAT,
                        GL_FALSE, sizeof(VertexData),
                        BUFFER_OFFSET(sizeof(GLfloat) * color_dims));
  glEnableVertexAttribArray( vPosition );
  glEnableVertexAttribArray(vColor);
  fflush(stdout);
  this->update();
}

void Object::display( vmath::mat4 ViewPerspective ){
  static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
  static const float white[] = { 1.0f, 1.0f, 1.0f, 1.0f };


  vmath::mat4 ModelViewProject = ViewPerspective * modelMatrix;

  glUniformMatrix4fv(modelViewLoc, 1 , GL_FALSE, ModelViewProject);

  glBindVertexArray( VAOs[Triangles] );
  glDrawArrays( GL_TRIANGLES, 0, NumVertices );

}

template <typename T>
void Object::setPosition(T x, T y, T z){
  this->ModelLocation[0] = (GLfloat) x;
  this->ModelLocation[1] = (GLfloat) y;
  this->ModelLocation[2] = (GLfloat) z;
  this->update();
}

template <typename T>
void Object::setPosition(T coords){
  this->ModelLocation[0] = (GLfloat) coords[0];
  this->ModelLocation[1] = (GLfloat) coords[1];
  this->ModelLocation[2] = (GLfloat) coords[2];
  this->update();
}

template <typename T>
void Object::setRotation(T x, T y, T z){
  this->ModelRotation[0] = (GLfloat) x;
  this->ModelRotation[1] = (GLfloat) y;
  this->ModelRotation[2] = (GLfloat) z;
  this->update();
}

template <typename T>
void Object::setRotation(T axisRot){
  this->ModelRotation[0] = (GLfloat) axisRot[0];
  this->ModelRotation[1] = (GLfloat) axisRot[1];
  this->ModelRotation[2] = (GLfloat) axisRot[2];
  this->update();
}
void Object::setScale(GLfloat scale){
  this->ModelScale = scale;
}


vmath::vec3 Object::getRotation(){
  return vmath::vec3(ModelRotation[0], ModelRotation[1], ModelRotation[2]);
}

vmath::vec3 Object::getPosition(){
  return vmath::vec3(ModelLocation[0], ModelLocation[1], ModelLocation[2]);
}

GLfloat Object::getScale(){
  return this->ModelScale;
}


vmath::mat4 Object::getModelMatrix(){
  return modelMatrix;
}

void Object::update(){
  vmath::mat4 ModelS = vmath::scale(this->ModelScale);
  vmath::mat4 ModelR = vmath::rotate(this->ModelRotation[0], this->ModelRotation[1], this->ModelRotation[2]);
  vmath::mat4 ModelT = vmath::translate(this->ModelLocation[0], this->ModelLocation[1], this->ModelLocation[2]);
  this->modelMatrix = ModelT * ModelR * ModelS;
}
