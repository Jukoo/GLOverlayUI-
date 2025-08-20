/**
 * @file canvasdriver.C 
 **/


#include <cstdio> 
#include <iostream> 

#include "renderer.H"  
#include "canvasdriver.H"

CanvasDriver::CanvasDriver(wxWindow  * mainframe_parent) : 
  wxGLCanvas(mainframe_parent) 
{

  /*! @todo :  detect which c++ std version is used  */ 
  
   _ctx =  mkptr(unique ,  wxGLContext, this) ; 
   
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_SMOOTH); 

   Bind(wxEVT_PAINT , &CanvasDriver::on_painting , this) ; 
   Bind(wxEVT_SIZE , &CanvasDriver::on_resizing ,  this) ; 
   Bind(wxEVT_MOTION, &CanvasDriver::on_mouse , this) ;
   Bind(wxEVT_LEFT_DOWN, &CanvasDriver::on_mouse_grab , this ) ; 
   Bind(wxEVT_LEFT_UP  , &CanvasDriver::on_mouse_release,this) ; 
};  


CanvasDriver::~CanvasDriver() 
{
#if   __cpp_11
  delete _ctx ; 
  _ctx = nullptr ; 
#endif 

}


void CanvasDriver::renderer(int forms) 
{

  SetCurrent(*_ctx) ;

  
  _renderer.setforms(forms) ;  
  _renderer.display()  ;

  SwapBuffers() ;  
   
}

bool CanvasDriver::get_renderer_state(void) 
{
  return _show ;
}

void CanvasDriver::set_renderer_state(bool  state) 
{
   _show  = state ;  
}

void CanvasDriver::toggle_renderer(void) 
{
  static int   current_forms =  _renderer.getforms() ;  
  _show^=1;    
 
  if(!_show) 
    _renderer.setforms(current_forms &~current_forms);  
  else
    _renderer.setforms(current_forms); 

  Refresh(true) ; 
}


void CanvasDriver::apply_rotation(float  _angle) 
{
  _renderer.rotate_forms(_angle) ; 
  Refresh(true) ; 
}

void CanvasDriver::apply_scaling(float  scale )  
{
  _renderer.scale_forms(scale) ;
  Refresh(true) ; 
}
void CanvasDriver::on_painting(wxPaintEvent& evt) 
{ 
  int  forms = _renderer.getforms() ; 
  renderer(forms) ;   
}

void CanvasDriver::on_resizing(wxSizeEvent  & evt) 
{

  wxSize size =  GetClientSize() ; 
  
  glViewport(0, 0, size.x, size.y);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(size.x/2, size.x/2, size.y/2, size.y/2, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  evt.Skip() ; 
  Refresh(false) ; 
}


void CanvasDriver::on_mouse(wxMouseEvent& evt) 
{
  if(_mouse_grab_state) 
  {
    wxPoint position=  evt.GetPosition() ;
    float angle =  (position.x * position.y)  /  360.f ; 
    apply_rotation(static_cast<float>(angle)) ;

  }
}

void CanvasDriver::on_mouse_grab(wxMouseEvent& evt ) 
{
   _mouse_grab_state^=1 ; 
   (_mouse_grab_state) ?  CaptureMouse() : ReleaseMouse() ; 
}

void CanvasDriver::on_mouse_release(wxMouseEvent & evt) 
{
  on_mouse_grab(evt) ; 
}
