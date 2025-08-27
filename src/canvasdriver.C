/**
 * @file canvasdriver.C 
 * @brief Kind of middleware  between  mainframe layout and  rendering interaction 
 *
 * @copyright (C) 2025   Umar Ba  <jUmarB@protonmail.com> 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#include <cstdio> 
#include <iostream> 

#include "renderer.H"  
#include "canvasdriver.H"

CanvasDriver::CanvasDriver(wxWindow  * mainframe_parent) : 
  wxGLCanvas(mainframe_parent) 
{

  
   _ctx =  mkptr(unique ,  wxGLContext, this) ; 
   CanvasDriver_init() ;  

   Bind(wxEVT_PAINT , &CanvasDriver::on_painting , this) ; 
   Bind(wxEVT_SIZE , &CanvasDriver::on_resizing ,  this) ; 
   Bind(wxEVT_MOTION, &CanvasDriver::on_mouse , this) ;
   Bind(wxEVT_LEFT_DOWN, &CanvasDriver::on_mouse_grab , this ) ; 
   Bind(wxEVT_LEFT_UP  , &CanvasDriver::on_mouse_release,this) ; 
};  


void CanvasDriver::CanvasDriver_init(void) 
{
   _renderer.init() ;  
}
 

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
  
  sketch_map() ; 
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
  _renderer.projection(size.x , size.y) ; 
  evt.Skip() ; 
  Refresh(false) ; 
}


void CanvasDriver::on_mouse(wxMouseEvent& evt) 
{ 
  wxPoint cursor_position=  evt.GetPosition() ;
  //mouse_motion_action_on(CANVAS_OVERLAY_BUTTON ,cursor_position,  /*propagation=false */) ; 
  if(_mouse_grab_state) 
  {
    float angle =  (cursor_position.x * cursor_position.y)  /  360.f ; 
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


void CanvasDriver::increase_or_decrease_scaling(unsigned char  symbole) 
{ 
  if (!((symbole & 0xff)  ^ 0x2b)) 
    _renderer.upscale() ;  
  
  if (!((symbole & 0xff) ^ 0x2d))  
    _renderer.downscale() ; 
}


void CanvasDriver::sketch_map(int where) 
{
  unsigned int sign_mask   =0; 
  
  switch(where  & 0xf )
  {
    case   TOP_RIGHT : sign_mask  = SIGN(TOP_RIGHT) ; break; 
    case   TOP_LEFT : sign_mask  = SIGN(TOP_LEFT) ; break; 
    case   BOTTOM_RIGHT : sign_mask  = SIGN(BOTTOM_RIGHT) ; break; 
    case   BOTTOM_LEFT : sign_mask  = SIGN(BOTTOM_LEFT) ; break; 
  } 
  
  int x_sign = (sign_mask>>8)  ,
      y_sign = (sign_mask & 0xff) ; 
  
  std::vector<float> points {X,Y};  

  int y_coord_strating  = 0 ,
      j=0 ; 

  for (float i : points ) 
  {
     if(!(y_coord_strating&~(1) )) 
       button_area.push_back(!(x_sign ^ NEG) ? -i: i) ;  
     else
       button_area.push_back(!(y_sign ^ POS) ?  i:-i) ; 

     y_coord_strating-=~0 ; 
  }
  
  _renderer.draw(button_area) ; 
}

