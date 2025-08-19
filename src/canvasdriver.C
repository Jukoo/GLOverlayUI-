/**
 * @file canvasdriver.C 
 **/


#include <GL/glut.h>
#include "canvasdriver.H"
#include <cstdio> 
#include <wx/dcclient.h>

CanvasDriver::CanvasDriver(wxWindow  * mainframe_parent) : 
  wxGLCanvas(mainframe_parent) 
{
   _ctx = new wxGLContext(this) ;

   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_SMOOTH); 

   Bind(wxEVT_PAINT , &CanvasDriver::on_painting , this) ; 
   Bind(wxEVT_SIZE , &CanvasDriver::on_resizing ,  this) ; 

};  



CanvasDriver::~CanvasDriver() 
{
  delete _ctx ; 
  _ctx =  nullptr ; 
}


void CanvasDriver::renderer(void) 
{

  SetCurrent(*_ctx) ;
  
  /*! For testing purpose  render  simple triangle 
  glClearColor(0.6,0.5,0.5,0) ; 
  glClear(GL_COLOR_BUFFER_BIT) ;  

  glBegin(GL_TRIANGLES);
  glVertex3f( 0, 0.5 , 0 ) ; 
  glVertex3f( -0.5, -0.5 , 0 ) ; 
  glVertex3f( 0.5,-0.5 , 0 ) ; 
  glEnd() ; 
  */ 

  //* Make flags  */
   bool m_showTriangle=1 ;
    bool m_showSquare =1;
    bool m_showCircle =1;

        glClearColor(0.15f, 0.15f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Triangle
        if (m_showTriangle) {
            glBegin(GL_TRIANGLES);
                glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.8f, -0.5f);
                glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(-0.2f, -0.5f);
                glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(-0.5f,  0.2f);
            glEnd();
        }

        // Carré
        if (m_showSquare) {
            glColor3f(1.0f, 1.0f, 0.0f);
            glBegin(GL_QUADS);
                glVertex2f(0.2f, -0.5f);
                glVertex2f(0.7f, -0.5f);
                glVertex2f(0.7f,  0.0f);
                glVertex2f(0.2f,  0.0f);
            glEnd();
        }

        // Cercle
        if (m_showCircle) {
            glColor3f(0.2f, 0.8f, 1.0f);
            glBegin(GL_POLYGON);
                int segments = 50;
                float r = 0.3f;
                float cx = 0.0f, cy = 0.5f;
                for (int i = 0; i < segments; ++i) {
                    float theta = 2.0f * M_PI * float(i) / float(segments);
                    float x = r * cos(theta);
                    float y = r * sin(theta);
                    glVertex2f(cx + x, cy + y);
                }
            glEnd();
        }


  glFlush();
  SwapBuffers() ; 



}

void CanvasDriver::on_painting(wxPaintEvent& evt) 
{
    renderer() ; 

}

void CanvasDriver::on_resizing(wxSizeEvent  & evt) 
{
  Refresh() ; 
  evt.Skip() ; 
}

