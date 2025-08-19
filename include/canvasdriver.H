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
#include <memory> 

/** 
 * @brief  memory allocation compatibility over  c++_std=11  
 * */


#if defined(__cplusplus) && (__cplusplus >= 201402L ) 
# define   uniq_allocator(__object)  std::unique_ptr<__object>   
# define   shrd_allocator(__object)  std::shared_ptr<__object>  

# define   mkptr(__type , __object , ... )  std::make_##__type<__object> (__VA_ARGS__)  

#else 
# define   uniq_allocator(__object)   __object *  
# define   shrd_allocator(__object)   __object *  

# define   mkptr(__type /* ignored */ , __object ,... )   new __object (__VA_ARGS__)

# define   __cpp_11
#endif 


/** 
 * @class CanvasDriver
 * @brief Responsable to render OpenGL stuff  on Canvas Frame layout  
 */

class CanvasDriver : public  wxGLCanvas  
{

  uniq_allocator(wxGLContext) _ctx  ;  
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
