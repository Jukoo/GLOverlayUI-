/**
 * @file  canvasdriver.H
 * @brief  Kind of bridge for layout interaction and OpenGL  render 
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

#if !defined(GLOverlayUI_canvasdriver_h)
#define  GLOverlayUI_canvasdriver_h 

#include <wx/wx.h> 
#include <wx/glcanvas.h>
#include <GL/gl.h> 
#include <GL/glu.h>
#include <memory> 

#include "renderer.H"

/** \cond 
 *   @NOTE : Adapts the memory allocation to the standard C++ (11 -> 17)
 */

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

/** \endcond  */

/** 
 * @class CanvasDriver
 * @brief Responsable to render OpenGL stuff  on Canvas Frame layout  
 */
class CanvasDriver : public  wxGLCanvas  
{


  /** \cond  */
  uniq_allocator(wxGLContext) _ctx  ; 

  /* --  Canvas  Event --  */
  void on_painting(wxPaintEvent&) ; 
  void on_resizing(wxSizeEvent&) ; 
  void on_mouse(wxMouseEvent&) ; 
  void on_mouse_grab(wxMouseEvent&) ; 
  void on_mouse_release(wxMouseEvent&); 
  /** \endcond  */
  
  bool _mouse_grab_state = false ;   /**  Detecte the mouse grab to trigger  rotation on mouse motion  */
  Renderer _renderer ;               /** Renderer instance  */ 
  bool _show ;                       /** The rendere state  */
  public: 
    /** 
     * @brief  CanvasDriver  constructor
     */
    CanvasDriver(wxWindow  * mainframe_parent);

    /**
     * @brief CanvasDriver destructor
     */
    virtual  ~CanvasDriver() ; 

    /** 
     * @brief  Initialize OpenGL stuff 
     */
    void  CanvasDriver_init(void); 

    /**
     * @brief apply  rotation angle  on all form 
     * @param  rotation_angle -  float 
     */
    void apply_rotation(float rotation_angle) ; 
   
    /**
     * @brief apply scaling form
     * @param  scale - float 
     */
    void apply_scaling(float   scale) ;  
  
    /** 
     * @brief increase or decrease scaling
     * @param symbole  -  unsigned char should be "+" or "-" 
     */
    void increase_or_decrease_scaling(unsigned char ) ;   

    /** 
     * @brief Renderer OpenGL frame 
     * @param  forms_bit_mask - Each form can be represented by a mask. 
     *         please see  the  renderer.H  file for more information  
     */
    void renderer(int forms_bit_mask) ; 

    /** 
     * @brief  enable/disable the canvas renderering forms  
     */
    void toggle_renderer(void) ; 
    
    /**
     * @brief   get the renderer state 
     */
    bool get_renderer_state(void)  ; 

    /**
     * @brief  set the renderer  state  
     * @param  state - (true or false)
     */
    void set_renderer_state(bool state) ; 
}; 

#endif  /*! GLOverlayUI_canvasdriver_h */
