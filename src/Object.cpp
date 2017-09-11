

vmath::vec3 getDirectionVec(double xrot, double yrot){
  //return vmath::vec3( sin(yrot * M_PI / 180.f) * cos(xrot * M_PI / 180.f), sin(yrot * M_PI / 180.f) * sin(xrot * M_PI / 180.f), cos(xrot * M_PI / 180.f));
  return vmath::vec3( cos(yrot) * cos(xrot), sin(xrot), cos(xrot)*sin(yrot));
}



struct VertexData{
  GLfloat color[4];
  GLfloat position[4];
};
double mouseXPosition, mouseYPosition;
double xRotation, yRotation;
double mouseXSensitivity, mouseYSensitivity;

double viewx, viewy, viewz;
vmath::vec3 cameraLocation;
void closeProgram(){
  glfwDestroyWindow(window);

  glfwTerminate();
  exit(0);
}

class Object{
public:

  enum VAO_IDs { Triangles, NumVAOs };
  enum Buffer_IDs { ArrayBuffer, NumBuffers };
  enum Attrib_IDs { vPosition = 0, vColor = 1};
  //char * VarNames[] = {"vPosition", "vColor"};
  GLuint VarIndicies[2] = {vPosition, vColor};
  int NumVars = 2;
  GLuint VAOs[NumVAOs];
  GLuint Buffers[NumBuffers];
  GLuint dims = 3;
  GLuint color_dims = 4;
  GLuint NumVertices;
  GLuint modelViewLoc;
  GLuint ambientLoc;
  GLfloat drawDistance;

  vmath::vec3 ModelLocation;

  void
  init(vmath::vec3 location )
  {
    ModelLocation = location;
    drawDistance = 1000;
    cameraLocation = vmath::vec3(0.0f, 0.0f, 0.f);
    mouseXSensitivity = mouseYSensitivity = 0.1f;
    xRotation = yRotation = 0.0f;
    viewx = viewy = viewz = 0.0d;
    std::vector<GLfloat *> lvertices;
    std::vector<GLfloat *> luvs;
    std::vector<GLfloat *> lnorms;

    if(!loadOBJ("../media/objects/suzanne.obj", lvertices, luvs, lnorms)){
      printf("Error loading suzanne");
      closeProgram();
    }
    else{
      printf("Loaded Model");
    }
    glEnable(GL_DEPTH_TEST);
    glGenVertexArrays( NumVAOs, VAOs );
    glBindVertexArray( VAOs[Triangles] );
    NumVertices = lvertices.size();
    VertexData vertices[NumVertices];

    for(int i = 0; i < lvertices.size(); i++){
      printf("%d, %d, %d\n", lvertices[i][0], lvertices[i][1], lvertices[i][2]);
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
      //delete vertices[i];
    }




    /*GLfloat  vertices[NumVertices][2] = {
      { -0.90f, -0.90f }, {  0.85f, -0.90f }, { -0.90f,  0.85f },  // Triangle 1
      {  0.90f, -0.85f }, {  0.90f,  0.90f }, { -0.85f,  0.90f }   // Triangle 2
      };*/

    glCreateBuffers( NumBuffers, Buffers );
    glBindBuffer( GL_ARRAY_BUFFER, Buffers[ArrayBuffer] );
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                 vertices, GL_STATIC_DRAW);
    //glBufferStorage( GL_ARRAY_BUFFER, sizeof(vertices), vertices, 0);
    ///*
    ShaderInfo  shaders[] =
      {
        { GL_VERTEX_SHADER, "/home/kenny/Projects/3dsnake/media/shaders/triangles/triangles.vert" },
        { GL_FRAGMENT_SHADER, "/home/kenny/Projects/3dsnake/media/shaders/triangles/triangles.frag" },
        { GL_NONE, NULL }
      };
    //*/
    /*
      ShaderInfo  shaders[] =
      {
      { GL_VERTEX_SHADER, "/home/kenny/Projects/3dsnake/media/shaders/compat/shader.vert" },
      { GL_FRAGMENT_SHADER, "/home/kenny/Projects/3dsnake/media/shaders/compat/shader.frag" },
      { GL_NONE, NULL }
      };
    */



    //GLuint program = LoadShaders( shaders, VarIndicies, VarNames, NumVars );
    GLuint program = LoadShaders( shaders);
    glUseProgram( program );
    modelViewLoc = glGetUniformLocation(program, "ModelViewProjectionMatrix");
    //ambientLoc = glGetUniformLocation(program, "Ambient");



    glVertexAttribPointer( vColor, color_dims, GL_FLOAT,
                           GL_FALSE, sizeof(VertexData), BUFFER_OFFSET(0) );
    glVertexAttribPointer(vPosition, dims, GL_FLOAT,
                          GL_FALSE, sizeof(VertexData),
                          BUFFER_OFFSET(sizeof(GLfloat) * color_dims));
    glEnableVertexAttribArray( vPosition );
    glEnableVertexAttribArray(vColor);
    vmath::vec3 center = getDirectionVec(xRotation, yRotation) + cameraLocation;
    printf("Mouse input, Camera location: %lf, %lf, %lf. Looking at: %lf, %lf, %lf\n", cameraLocation[0], cameraLocation[1], cameraLocation[2], center[0], center[1], center[2]);
    fflush(stdout);

  }

  //----------------------------------------------------------------------------
  //
  // display
  //

  void
  display( void )
  {
    static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    static const float white[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    vmath::mat4 ModelS = vmath::scale(.5f);
    vmath::mat4 ModelR = vmath::rotate(0.f, 0.f, 0.0f);
    vmath::mat4 ModelT = vmath::translate(ModelLocation);
    vmath::mat4 Model = ModelT * ModelR * ModelS;

    vmath::vec3 up = cameraLocation + vmath::vec3(0.f, 1.f, 0.f);
    vmath::vec3 forward = cameraLocation + vmath::vec3(cos(yRotation), 0.f, sin(yRotation));


    vmath::mat4 yRotMat = vmath::rotate(0.f, ((GLfloat) yRotation), 0.f) ;
    vmath::vec3 Xaxis = vmath::vec3(1.f, 0.f, 0.f);//yRotMat * vmath::vec4(1.0f, 0.f, 0.f, 0.f);
    vmath::mat4 xRotMat = vmath::rotate((GLfloat) xRotation, Xaxis);

    vmath::mat4 ViewR = xRotMat * yRotMat;//vmath::rotate(0.f, ((GLfloat) yRotation), 0.f) ;//vmath::rotate(((GLfloat) xRotation), cross(forward, up)) * vmath::rotate(0.f, ((GLfloat) yRotation), 0.f) ;
    vmath::mat4 ViewT = vmath::translate(cameraLocation);
    vmath::mat4 View = ViewR * ViewT;

    vmath::mat4 Perspective = vmath::perspective(90.0f, (9.0f/16.0f), 0.1f, 1000.0f);
    //vmath::mat4 ModelViewProject = vmath::perspective(90.0f, (9.0f/16.0f), 0.1f, 1000.0f) * vmath::rotate(((GLfloat) xRotation, ((GLfloat) yRotation), 0.0f) * vmath::translate(cameraLocation) * Model;

    vmath::mat4 ModelViewProject = Perspective * View * Model;

    glUniformMatrix4fv(modelViewLoc, 1 , GL_FALSE, ModelViewProject);
    //glUniformMatrix4fv(ambientLoc, 1 , GL_FALSE, ambient);
    //glClearBufferfv(GL_COLOR, 0, white);
    //glClear(GL_DEPTH_BUFFER_BIT);
    glBindVertexArray( VAOs[Triangles] );
    glDrawArrays( GL_TRIANGLES, 0, NumVertices );
  }

};
