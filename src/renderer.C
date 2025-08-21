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

void Renderer::setforms(int form_flags) 
{
  _form_options= form_flags  ; 
}


int Renderer::getforms(void) const 
{
  return _form_options ; 
}


void Renderer::display(void) 
{
  int forms =  getforms()  ; 

  glClearColor(0.15f, 0.15f, 0.2f, 1.0f);
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
