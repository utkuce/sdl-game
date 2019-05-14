#include "Renderer.h"
#include <iostream>

SDL_Window *Renderer::window;
int windowWidth, windowHeight;
float rendererWidth, rendererHeight;

ImVec4 Renderer::background = ImColor(114, 144, 154);

int numberOfFrames;
int startTime;

float Renderer::frameRate = -1;
bool Renderer::vsync = true;
bool Renderer::fullscreen = false;

//Graphics program
GLuint Renderer::gProgramID = 0;
GLint Renderer::gVertexPos2DLocation = -1;
GLuint Renderer::gVBO = 0;
GLuint Renderer::gIBO = 0;

//Fragment source
const GLchar* fragmentShaderSource[] = 
{
    "#version 300 es\n"
    "out lowp vec4 LFragment;"
    "void main() {"
    "   LFragment = vec4( 1.0, 1.0, 1.0, 1.0 );"
    "}"
};

//Vertex source
const GLchar* vertexShaderSource[] =
{
    "#version 300 es\n"
    "in vec2 LVertexPos2D;"
    "void main() {"
    "    gl_Position = vec4( LVertexPos2D.xy, 0, 1 );"
    "}" 
};

//Shader loading utility programs 
bool initGL();
void printProgramLog( GLuint program ); 
void printShaderLog( GLuint shader );

void Renderer::translateCoords(float coords[2])
{
	// translate game coordinates to opengl and scales according to resolution
	// coordinates are hardcoded for renderer size and scaled before translation

    coords[0] *= windowWidth / rendererWidth;
    coords[1] *= windowHeight / rendererHeight;

    coords[0] = (float)(coords[0] - windowWidth / 2) / (windowWidth / 2);
    coords[1] = (float)(coords[1] - windowHeight / 2) / (windowHeight / 2);
}

void Renderer::init(SDL_Window *window, float width, float height)
{
    Renderer::window = window;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    rendererWidth = width;
    rendererHeight = height;

    numberOfFrames = 0;
    startTime = SDL_GetTicks();

    SDL_WarpMouseInWindow(window, windowWidth / 2, windowHeight / 2);
    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR));

    initGL();
}

void vertexShader(GLuint gProgramID) 
{
    //Create vertex shader
    GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );
    //Set vertex source
    glShaderSource( vertexShader, 1, vertexShaderSource, NULL );
    //Compile vertex source
    glCompileShader( vertexShader );
    //Check vertex shader for errors
    GLint vShaderCompiled = GL_FALSE;
    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &vShaderCompiled );
    if( vShaderCompiled != GL_TRUE )
    {
        printf( "Unable to compile vertex shader %d!\n", vertexShader );
        printShaderLog( vertexShader );
    }
    else 
    {
        //Attach vertex shader to program
        glAttachShader( gProgramID, vertexShader );
    }
}

void fragmentShader(GLuint gProgramID)
{
    //Create fragment shader
    GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
        
    //Set fragment source
    glShaderSource( fragmentShader, 1, fragmentShaderSource, NULL );
    //Compile fragment source
    glCompileShader( fragmentShader );
    //Check fragment shader for errors
    GLint fShaderCompiled = GL_FALSE;
    glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled );
    if( fShaderCompiled != GL_TRUE )
    {
        printf( "Unable to compile fragment shader %d!\n", fragmentShader );
        printShaderLog( fragmentShader );
    }
    else
    {
        //Attach fragment shader to program
        glAttachShader( gProgramID, fragmentShader );
    }
    
}

void Renderer::initGL() {

    //Generate program
    gProgramID = glCreateProgram();

    vertexShader(gProgramID);
    fragmentShader(gProgramID);
            
    //Link program
    glLinkProgram( gProgramID );
            
    //Check for errors
    GLint programSuccess = GL_TRUE;
    glGetProgramiv( gProgramID, GL_LINK_STATUS, &programSuccess );
    if( programSuccess != GL_TRUE )
    {
        printf( "Error linking program %d!\n", gProgramID );
        printProgramLog( gProgramID );
    }
    else
    {
        //Get vertex attribute location
        Renderer::gVertexPos2DLocation = glGetAttribLocation( gProgramID, "LVertexPos2D" );
        if( Renderer::gVertexPos2DLocation == -1 )
        {
            printf( "LVertexPos2D is not a valid glsl program variable!\n" );
        }
    }

    //Bind program
    glUseProgram(gProgramID);
}

void update_framerate()
{
    numberOfFrames++;
    int elapsedMS = SDL_GetTicks() - startTime;

    if (elapsedMS != 0)
    {
		double elapsedSeconds = elapsedMS / 1000.0; // Convert to seconds
		double fps = numberOfFrames / elapsedSeconds;
		if (fps != 0)
			Renderer::frameRate = fps;

		// reset frame count every second
		if (elapsedMS > 1000)
		{
			startTime = SDL_GetTicks();
			numberOfFrames = 0;
			Interface::fps_display = Renderer::frameRate;
		}
    }

    Renderer::vsync = SDL_GL_GetSwapInterval();
}

void update_interface(SDL_Window *window)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();
    Interface::update();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Renderer::render()
{
    glViewport(0, 0, windowWidth, windowHeight);
    glClearColor(0.44, 0.56, 0.6, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    for (Shape *item : Shape::render_list)
    {
		item->update();
		item->draw();
    }

    update_framerate();
    update_interface(window);

    SDL_GL_SwapWindow(window);
}

void Renderer::toggleFullscreen()
{
    SDL_SetWindowFullscreen(Renderer::window,
			    Renderer::fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
}

void printProgramLog( GLuint program ) { 
    //Make sure name is shader 
    if( glIsProgram( program ) ) 
    { 
        //Program log length 
        int infoLogLength = 0; 
        int maxLength = infoLogLength; 
        //Get info string length 
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength ); 
        //Allocate string 
        char* infoLog = new char[ maxLength ]; 
        //Get info log 
        glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog ); 
        if( infoLogLength > 0 ) 
        { 
            //Print Log 
            printf( "%s\n", infoLog ); 
        } 
        //Deallocate string 
        delete[] infoLog; 
        
    } 
    else 
    { 
        printf( "Name %d is not a program\n", program ); 
    } 
} 

void printShaderLog( GLuint shader ) { 
    //Make sure name is shader 
    if( glIsShader( shader ) ) 
    { 
        //Shader log length 
        int infoLogLength = 0; 
        int maxLength = infoLogLength; 
        //Get info string length 
        glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength ); 
        //Allocate string 
        char* infoLog = new char[ maxLength ]; 
        //Get info log 
        glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog ); 
        if( infoLogLength > 0 ) 
        { 
            //Print Log 
            printf( "%s\n", infoLog ); 
        } 
        //Deallocate string 
        delete[] infoLog; 
    } 
    else 
    { 
        printf( "Name %d is not a shader\n", shader ); 
    } 
}
