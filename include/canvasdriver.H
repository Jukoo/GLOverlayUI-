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
#include <wx/window.h>
#include <wx/gdicmn.h>
#include <wx/glcanvas.h>
#include <GL/gl.h> 
#include <GL/glu.h>
#include <memory>
#include <map>

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

enum __button_overlay_position_t{ 
  TOP_LEFT , 
#define TOP_LEFT       (1 << TOP_LEFT) 
  BOTTOM_LEFT,
#define  BOTTOM_LEFT   (1 << BOTTOM_LEFT) 
  TOP_RIGHT, 
#define  TOP_RIGHT     (1 << TOP_RIGHT) 
  BOTTOM_RIGHT, 
#define  BOTTOM_RIGHT  (1 << BOTTOM_RIGHT) 
};

#define  X  0.9f, 0.7f
#define  Y  0.8f, 0.9f 

#define  POS    0x2b   
#define  NEG    0x2d 

/** 
 *   This bunch of macro bellow  represente the  xy  coords : 
 *                ^
 *                |(y) + 
 *    TOP_LEFT    |   TOP_RIGHT 
 *       - _______.________> (x) +
 *                |
 *   BOTTOM_LEFT  |   BOTTOM_RIGHT   
 *             -  | 
 *                v 
 */

#define  SIGN_TOP_LEFT     ('-'<<8|'+')          /** x negative & y positive   */
#define  DRAW_BUTTON_TOP_LEFT  (SIGN_TOP_LEFT <<4 | TOP_LEFT)

#define  SIGN_TOP_RIGHT    ('+'<<8|'+')          /** x positive & y positive */  
#define  DRAW_BUTTON_TOP_RIGHT  (SIGN_TOP_RIGHT << 4 | TOP_RIGHT) 

#define  SIGN_BOTTOM_LEFT  ('-'<<8|'-')           /** x negative & y  negative */ 
#define  DRAW_BUTTON_BOTTOM_LEFT  (SIGN_BOTTOM_LEFT << 4 | BOTTOM_LEFT)

#define  SIGN_BOTTOM_RIGHT ('+'<<8|'-')          /** x positive & y negative */
#define  DRAW_BUTTON_BOTTOM_RIGHT  (SIGN_BOTTOM_RIGHT << 4 | BOTTOM_RIGHT) 


#define SIGN(_position) SIGN_##_position 
#define DRAW(_position) DRAW_##_position   


/** \endcond  */

struct motion_metadata { 
  wxSize _size;                             /**  Hold the area size of   the canvas  */
  std::vector<float> _reference_coords ;    /**  coords reference you want to lookup */
  void  * status ;                          /**  status it can be anything. You can use it pass data in or out */  
}; 

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
  void on_mouse_release(wxMouseEvent&); 
  /** \endcond  */
  
  bool _mouse_grab_state = false ;   /**  Detecte the mouse grab to trigger  rotation on mouse motion  */
  Renderer _renderer ;               /**  Renderer instance  */ 
  bool _show ;                       /**  The rendere state  */
  std::vector<float> button_area ;   /**  Hold the coords of "Button"*/ 
  wxSize canvas_surface  ; 

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
   

   /*
    * @brief  specialized function to trac mouse motion on canvas 
    * @param  custom function that define the behavior   
    * @param  cursor_position - cursor position
    */

   void *mouse_motion_action_on(void (*what)(wxMouseEvent*, void * extradata) , wxMouseEvent*  ) ; 
  
   /** 
     * @brief make kind of sketch mappin point 
     *        to place the coordinate of each point  
     *        depending where the form should be appear  
     * @param  where  - the location   ( TOP_LEFT , TOP_RIGHT ,BOTTOM_LEFT ,BOTTOM_RIGHT )
     */
    void sketch_map(int where = TOP_LEFT /* TOP_LEFT as default value */)  ; 

    /**
     * @brief  a specialized  function to detecte  mouse action on "button"
     * @param  mouse coords  as reference  
     */

    static void overlay_button(  wxMouseEvent * , void * ) ;  

  void on_mouse_grab(wxMouseEvent&) ; 

}; 

#endif  /*! GLOverlayUI_canvasdriver_h */
