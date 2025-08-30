/** 
 * @file renderer.C 
 * @brief Rendering 2D Using OpenGL logic 
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

#include  "renderer.H"
#include <iostream> 

Renderer::Renderer(int form) : _form_options {form} {}   

void Renderer::init(void) 
{
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_TEXTURE_2D) ; 
   glShadeModel(GL_SMOOTH);   

}
 

void Renderer::setforms(int form_flags) 
{
  _form_options= form_flags  ; 
}


int Renderer::getforms(void) const 
{
  return _form_options ; 
}

void Renderer::projection(int x , int y) 
{
  glViewport(0, 0,x, y);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(x/2, x/2, y/2, y/2, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Renderer::display(void) 
{
  int forms =  getforms()  ; 

  glClearColor(RENDERER_BG_COLOR, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  if(!forms)
  {
    glFlush(); 
    return ; 
  }
    
  glPushMatrix() ;
  glScalef(_scl, _scl, 1.0f); 
  glRotatef(_rot, 0.0f, 0.0f, 1.0f);

  if (forms &  TRIANGLES) 
    OPENGL_OBJECT(TRIANGLES);

  if (forms &  QUADS ) 
    OPENGL_OBJECT(QUADS,glColor3f(1.0f, 1.0f, 0.0f)); 

  if (forms  & POLYGON) 
    OPENGL_OBJECT(POLYGON ,glColor3f(0.2f, 0.8f, 1.0f)) ; 


  glPopMatrix() ; 
  glFlush();
}


void Renderer::rotate_forms(float angle) 
{
    _rot = angle ; 
}

void Renderer::scale_forms(float scale) 
{
   _scl = scale ; 
} 

void Renderer::upscale(void)  
{
  unsigned int scl_factor = (unsigned int )  _scl ;  
  if(!(scl_factor ^ 0x64))
  { 
     _scl = 100.f  ; 
     return ; 
  }

   scl_factor=-~scl_factor ; 
   _scl =  (float) scl_factor ;

}

void Renderer::downscale(void) 
{
   if(!_scl) 
   {
      _scl=1.f; 
      return ; 
   }
  
  _scl-- ;  
}


//!FIXME  
void  Renderer::draw(std::vector<float> points, GLuint &texture)  
{
   //!For this moment this routine is just static  
   //!@todo : need to be improve in near future 

   if (!texture) 
     return ; 

   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texture);
   glColor3f(RENDERER_BG_COLOR);
 
   glBegin(GL_QUADS); 
   glVertex2f(points[0] ,  points[3]) ; 
   glVertex2f(points[0] ,  points[2]) ; 
   glVertex2f(points[1] ,  points[2]) ; 
   glVertex2f(points[1] ,  points[3]) ; 
   glEnd() ;
   
   glDisable(GL_TEXTURE_2D) ; 

}

//!FIXME  
void Renderer::create_texture(GLuint &  texture , int width , int height , GLvoid * data)  
{
   
  glGenTextures(1 , &texture) ; 
  glBindTexture(GL_TEXTURE_2D , texture) ; 

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 
       0, GL_RGB, GL_UNSIGNED_BYTE, data) ; 

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}
