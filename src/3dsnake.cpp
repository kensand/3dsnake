//////////////////////////////////////////////////////////////////////////////
//
//  Triangles.cpp
//
//////////////////////////////////////////////////////////////////////////////

#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.hpp"
#include "ObjectLoader.hpp"
#include <string>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include <math.h>
#include <cstdio>
#include <cstdlib>
#include <X11/Xlib.h>
#include "Object.hpp"



vmath::vec3 getDirectionVec(double xrot, double yrot){
  //return vmath::vec3( sin(yrot * M_PI / 180.f) * cos(xrot * M_PI / 180.f), sin(yrot * M_PI / 180.f) * sin(xrot * M_PI / 180.f), cos(xrot * M_PI / 180.f));
  //return vmath::vec3( cos(yrot) * cos(xrot), sin(xrot), cos(xrot)*sin(yrot));
  yrot+=90.f;
  return vmath::vec3( cos(yrot* M_PI / 180.f) * cos(xrot* M_PI / 180.f), sin(xrot* M_PI / 180.f), cos(xrot* M_PI / 180.f)*sin(yrot* M_PI / 180.f));
  /*
  vmath::vec4 fowardVec = vmath::vec4(0.f,0.f, 1.f, 0.f);

  vmath::mat4 yRotMat = vmath::rotate(0.f, ((GLfloat) yrot), 0.f) ;
  vmath::vec3 Xaxis = vmath::vec3(1.f, 0.f, 0.f);//yRotMat * vmath::vec4(1.0f, 0.f, 0.f, 0.f);
  vmath::mat4 xRotMat = vmath::rotate((GLfloat) xrot, Xaxis);

  vmath::mat4 ViewR = xRotMat * yRotMat;


  vmath::mat4 direction = ViewR * fowardVec;
  return vmath::vec3(direction[0][0], direction[1][1], direction[2][2]);
  */
}
vmath::vec3 cameraLocation;
double mouseXPosition, mouseYPosition;
double xRotation, yRotation;
double mouseXSensitivity, mouseYSensitivity;
bool mouseCaptured;


GLFWwindow* window;




void closeProgram(){
  glfwDestroyWindow(window);

  glfwTerminate();
  exit(0);
}











static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
  if(mouseCaptured){
    double xdiff = xpos - mouseXPosition;
    double ydiff = ypos - mouseYPosition;
    mouseXPosition = xpos;
    mouseYPosition = ypos;
    yRotation += (xdiff * mouseXSensitivity);//swapped because mouse y axis controls rendered x axis rotation.
    xRotation += (ydiff * mouseYSensitivity);//and vice versa.
    if(xRotation >= 90.0f){
      xRotation = 89.9999f;
    }
    else if(xRotation <= -90.0f){
      xRotation = -89.9999f;
    }
  
    yRotation = fmod(yRotation, 360);
  }
  //vmath::vec3 center = getDirectionVec(xRotation, yRotation) + cameraLocation;
  //printf("Mouse input, Camera location: %lf, %lf, %lf. Looking at: %lf, %lf, %lf\n", cameraLocation[0], cameraLocation[1], cameraLocation[2], center[0], center[1], center[2]);
  //fflush(stdout);
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

  
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
    if(mouseCaptured){
      mouseCaptured = false;
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else{
      mouseCaptured = true;
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    //closeProgram();

  }

  else if (key == GLFW_KEY_W && action == GLFW_PRESS){
    //cameraLocation += vmath::vec3(0.f, 0.f, 1.f);
    //vmath::vec3 norm = cross(getDirectionVec(xRotation, yRotation), vmath::vec3(0.f, 1.f, 0.f));
    //cameraLocation -= norm;
    cameraLocation += getDirectionVec(xRotation, yRotation);

  }
  else if (key == GLFW_KEY_S && action == GLFW_PRESS){
    //vmath::vec3 norm = cross(getDirectionVec(xRotation, yRotation), vmath::vec3(0.f, 1.f, 0.f));
    //cameraLocation += norm;
    cameraLocation -= getDirectionVec(xRotation, yRotation);
  }
      
  else if (key == GLFW_KEY_A && action == GLFW_PRESS){
    vmath::vec3 norm = cross(getDirectionVec(xRotation, yRotation), vmath::vec3(0.f, 1.f, 0.f));
    cameraLocation -= norm;
    //cameraLocation -= vmath::vec3(1.f, 0.f, 0.f);//getDirectionVec(xRotation, yRotation);
  }
  else if (key == GLFW_KEY_D && action == GLFW_PRESS){
    vmath::vec3 norm = cross(getDirectionVec(xRotation, yRotation), vmath::vec3(0.f, 1.f, 0.f));
    cameraLocation += norm;
    //cameraLocation += vmath::vec3(1.f, 0.f, 0.f);//getDirectionVec(xRotation, yRotation);
  }


  vmath::vec3 vec = getDirectionVec(xRotation, yRotation);// + cameraLocation;
  printf("Keystroke, Camera location: %lf, %lf, %lf, direction: %lf, %lf, %lf, xRotation: %lf, Yrotation: %lf \n", cameraLocation[0], cameraLocation[1], cameraLocation[2], vec[0], vec[1], vec[2], xRotation, yRotation);
  fflush(stdout);
}


//GLfloat ambient[4] = {0.0f, 1.0f, 0.0f, 1.0f};




//----------------------------------------------------------------------------
//
// init
//




void error_callback(int error, const char* description)
{
  puts(description);
}

//----------------------------------------------------------------------------
//
// main
//


#ifdef _WIN32
int CALLBACK WinMain(
                     _In_ HINSTANCE hInstance,
                     _In_ HINSTANCE hPrevInstance,
                     _In_ LPSTR     lpCmdLine,
                     _In_ int       nCmdShow
                     )
#else
  int
  main( int argc, char** argv )
#endif
{
  if(!glfwInit()){
    printf("Error initializing glfw, exiting");
    exit(1);
  }
  glfwSetErrorCallback(error_callback);
  window = glfwCreateWindow(1920, 1080, "Triangles", NULL, NULL);

  
  glfwMakeContextCurrent(window);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(window, cursor_position_callback);
  glfwSetKeyCallback(window, key_callback);
  gl3wInit();

  mouseCaptured = true;
  //init();
  cameraLocation = vmath::vec3(0.0f, 0.0f, 0.f);
  mouseXSensitivity = mouseYSensitivity = 0.1f;
  xRotation = yRotation = 0.0f;
  static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
  static const float white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  std::string objFile("../media/objects/suzanne.obj");
  Object o, p;
  try{
    o.init(objFile, vmath::vec3(1.f, 1.f, 1.f));
    p.init(objFile, vmath::vec3(-1.f, -1.f, -1.f));
  }
  catch(int e){
    switch(e){
    case 1:
      printf("Exiting due to failure to load model.");
      closeProgram();
      break;
    }
  }

  //Framecounter setup
  double lastTime = glfwGetTime();
  int nbFrames = 0;

  //Main Loop
  while (!glfwWindowShouldClose(window)){
    /*
      //Framecounter
      double currentTime = glfwGetTime();
      nbFrames++;
      if ( currentTime - lastTime >= 1.0 ){
        printf("%f ms/frame\n", 1000.0/double(nbFrames));
        nbFrames = 0;
        lastTime += 1.0;
      }
    */

      vmath::vec3 up = cameraLocation + vmath::vec3(0.f, 1.f, 0.f);
      vmath::vec3 forward = cameraLocation + vmath::vec3(cos(yRotation), 0.f, sin(yRotation));


      vmath::mat4 yRotMat = vmath::rotate(0.f, ((GLfloat) yRotation), 0.f) ;
      vmath::vec3 Xaxis = vmath::vec3(1.f, 0.f, 0.f);//yRotMat * vmath::vec4(1.0f, 0.f, 0.f, 0.f);
      vmath::mat4 xRotMat = vmath::rotate((GLfloat) xRotation, Xaxis);

      vmath::mat4 ViewR = xRotMat * yRotMat;//vmath::rotate(0.f, ((GLfloat) yRotation), 0.f) ;//vmath::rotate(((GLfloat) xRotation), cross(forward, up)) * vmath::rotate(0.f, ((GLfloat) yRotation), 0.f) ;
      vmath::mat4 ViewT = vmath::translate(cameraLocation);
      vmath::mat4 View = ViewR * ViewT;

      vmath::mat4 Perspective = vmath::perspective(90.0f, (1.0f), 0.1f, 1000.0f);
      vmath::mat4 ViewPerspective = Perspective * View;


      glClearBufferfv(GL_COLOR, 0, black);
      glClear(GL_DEPTH_BUFFER_BIT);
      o.display(ViewPerspective);
      p.display(ViewPerspective);
      glfwSwapBuffers(window);
      glfwPollEvents();
    }

  closeProgram();
}


