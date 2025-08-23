/**
 * @file renderer.H
 * @brief Redering 2D using OpenGL logic 
 *
 * @copyright (C) 2025  Umar Ba  <jUmarB@protonmail.com>
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

#if !defined(GLOverlayUI_renderer_h)
#define GLOverlayUI_renderer_h 

#include <GL/gl.h> 
#include <GL/glu.h> 
#include <cmath> 

enum { 
  TRIANGLES,  
#define TRIANGLES (1 << TRIANGLES) 
  QUADS ,
#define  QUADS    (1 << QUADS)  
  POLYGON
#define POLYGON   (1 << POLYGON)  
};

#define  RENDERER_ALL_FORM ( TRIANGLES| QUADS |  POLYGON ) 

/*!  BASIC GEOMETRICS  FORM OBJECT */ 
#define  OBJECT_TRIANGLES\
  glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.8f, -0.5f);\
  glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(-0.2f, -0.5f);\
  glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(-0.5f,  0.2f);

#define  OBJECT_QUADS \
  glVertex2f(0.2f, -0.5f);\
  glVertex2f(0.7f, -0.5f);\
  glVertex2f(0.7f,  0.0f);\
  glVertex2f(0.2f,  0.0f);

#define  OBJECT_POLYGON ({\
    int segments = 60; \
    float r = 0.3f;\
    float cx = 0.0f, cy = 0.5f;\
    for (int i = 0; i < segments; ++i) {\
          float t = 2.0f * M_PI * float(i) / float(segments);\
          float x = r * std::cos(t);\
          float y = r * std::sin(t);\
          glVertex2f(cx + x, cy + y);\
    }\
    });

#define  OPENGL_OBJECT(__figure , ...) \
  __VA_ARGS__;\
  glBegin(GL_##__figure);\
  OBJECT_##__figure\
  glEnd();



/** 
 * @class  Renderer  
 * @brief  Dedicated for Rendering 2D Object using OpenGL logic 
 */
class  Renderer
{  
  
  int _form_options =  RENDERER_ALL_FORM ; 
  float _rot = 0.0 , 
        _scl = 1.0f; 
  public :
  /*
   * @brief  default ctor 
   * */
  Renderer() = default  ;
 
  /**
   * @brief  alternative ctor 
   */
  Renderer(int) ; 

  /** 
   * @brief  Default dtor 
   **/
  virtual  ~Renderer()= default ; 
 
  /** 
   * @brief  init openGL stuff 
   */
  
  void  init(void) ;   
  /** 
   * @brief  enable forms  by  specifying the  apropriate flags 
   *         Multiple Forms can be enable or  disable by ORing
   */
  void setforms(int __form_flag_options) ;
    
  /** 
   * @brief retrieve bit mask for current  enabling forms  
   * @return int  - forms flags bit mask  
   **/
  int getforms(void) const ; 

  /*
   * @brief apply othogonal  projection when  the canvas layou expand  
   * @param  coord  - the coordinate  x - y
   **/
  
  void apply_orthogonal_projection(int xcoords , int ycoords)  ; 
  
  /**
   * @brief rotate by updating the _rot attribute that is responsible for the rotation
   */
    
  void rotate_forms(float angle) ; 

  /*
   * @brief scale  by updating the _scl attribute that is responsible for scaling forms 
   **/

  void scale_forms(float scale) ;  

  /*
   * @brief  increase the  scale  produce zoom in  effect 
   * @todo   improve the scale precision 
   **/
  void upscale(void) ; 

  /**
   * @brief  decrease the scale  produce zoom out  effect
   * @todo   improve the scale precision 
   */
  void downscale(void) ;  


  /**
   * @brief  display OpenGL  forms  in Canvas Area   
   */
  void display(void) ; 
  
}; 

#endif  /* GLOverlayUI_renderer_h */
