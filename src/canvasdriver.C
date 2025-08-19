/**
 * @file canvasdriver.C 
 **/


#include <cstdio> 
#include <wx/dcclient.h>
#include <GL/glut.h> 

#include "canvasdriver.H"
#include "renderer.H"  

CanvasDriver::CanvasDriver(wxWindow  * mainframe_parent) : 
  wxGLCanvas(mainframe_parent) 
{

  /*! @todo :  detect which c++ std version is used  */ 
  
   _ctx =  mkptr(unique ,  wxGLContext, this) ; 
   
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_SMOOTH); 

   Bind(wxEVT_PAINT , &CanvasDriver::on_painting , this) ; 
   Bind(wxEVT_SIZE , &CanvasDriver::on_resizing ,  this) ; 

};  


CanvasDriver::~CanvasDriver() 
{
#if   __cpp_11
  delete _ctx ; 
  _ctx = nullptr ; 
#endif 

}


void CanvasDriver::renderer(void) 
{

  SetCurrent(*_ctx) ;
  
  /*! For testing purpose  render  simple triangle 


  //* Make flags  */
   bool m_showTriangle=1 ;
    bool m_showSquare =1;
    bool m_showCircle =1;

        glClearColor(0.15f, 0.15f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Triangle
        if (m_showTriangle) 
        {
           OPENGL_OBJECT(TRIANGLES) 
        }

        // Carré
        if (m_showSquare) {
            OPENGL_OBJECT(QUADS,glColor3f(1.0f, 1.0f, 0.0f)) ;
        }

        // Cercle
        if (m_showCircle) {
            OPENGL_OBJECT(POLYGON ,glColor3f(0.2f, 0.8f, 1.0f)) ; 
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

