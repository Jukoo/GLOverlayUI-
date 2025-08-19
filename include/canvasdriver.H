/**
 * @file  canvasdriver.H
 * @brief  Kind of bridge for layout interaction and OpenGL  render 
 * @author Umar Ba <jUmaB@protonmail.com> 
 * */

#if !defined(GLOverlayUI_canvasdriver_h)
#define  GLOverlayUI_canvasdriver_h 

#include <wx/glcanvas.h>
#include <GL/gl.h> 
#include <GL/glu.h>
#include <GL/glut.h>
#include <wx/wx.h> 


/** 
 * @class CanvasDriver
 * @brief Responsable to render OpenGL stuff  on Canvas Frame layout  
 */

class CanvasDriver : public  wxGLCanvas  
{

  wxGLContext *_ctx ;  
  void on_painting(wxPaintEvent & evt ) ; 
  void on_resizing(wxSizeEvent& evt) ; 
  
  public: 
    /** 
     * @brief  CanvasDriver  ctor
     * */
    CanvasDriver(wxWindow  * mainframe_parent)  ;
    /**
     * @brief CanvasDriver dtor
     * */
    virtual  ~CanvasDriver() ; 

    /** 
     * @brief  Initialize Gl stuff 
     * */
    static void  CanvasDriver_init(void) ; 
   
    /** 
     * @brief Renderer OpenGL frame
     **/
    void renderer(void) ; 

}; 

#endif  /*! GLOverlayUI_canvasdriver_h */
