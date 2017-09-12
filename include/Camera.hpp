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

class Camera{

  static const vmath::vec3 Xaxis = vmath::vec3(1.f, 0.f, 0.f);
  static const vmath::vec3 Yaxis = vmath::vec3(0.f, 1.f, 0.f);
  static const vmath::vec3 Zaxis = vmath::vec3(0.f, 0.f, 1.f);
  vmath::vec3 up;
  vmath::vec3 forward;
  vmath::vec3 CameraLocation;
  vmath::vec3 CameraRotation;
  vmath::vec3 Rotation;
  vmath::mat4 View;


  vmath::mat4 Perspective;

  vmath::mat4 ViewPerspective;

  vmath::mat4 getViewPerspective(){
    return ViewPerspective;
  }

  vmath::mat4 getPerspective(){
    return Perspective;
  }
  vmath::mat4 getView(){
    return View;
  }
  vmath::vec3 getUp(){
    return ViewPerspective;
  }
  vmath::vec3 getForward(){
    return ViewPerspective;
  }



  template <typename T>
  void setRotation(T rotation){
    this->CameraRotation = (vmath::vec3) rotation
  }
  template <typename T>
  void setPosition(T Position){
    this->CameraLocation = Position
  }
  template <typename T>
  void setView(){
    return View;
  }
  template <typename T>
  void setUp(){
    return ViewPerspective;
  }
  template <typename T>
  void setForward(){
    return ViewPerspective;
  }

  void update(){
    vmath::mat4 yRotMat = vmath::rotate(Roation[1], Yaxis);//(0.f, ((GLfloat) Rotation[1]), 0.f) ;
    //yRotMat * vmath::vec4(1.0f, 0.f, 0.f, 0.f);
    vmath::mat4 xRotMat = vmath::rotate((GLfloat) Rotation[0], Xaxis);

    vmath::mat4 ViewR = xRotMat * yRotMat;//vmath::rotate(0.f, ((GLfloat) yRotation), 0.f) ;//vmath::rotate(((GLfloat) xRotation), cross(forward, up)) * vmath::rotate(0.f, ((GLfloat) yRotation), 0.f) ;
    vmath::mat4 ViewT = vmath::translate(CameraLocation);
    vmath::mat4 View = ViewR * ViewT;

    vmath::mat4 Perspective = vmath::perspective(90.0f, (1.0f), 0.1f, 1000.0f);
    vmath::mat4 ViewPerspective = Perspective * View;

  }
}
