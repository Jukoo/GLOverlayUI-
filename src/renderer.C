/** 
 * @file renderer.C 
 * @brief Rendering OpenGl   stuff 
 * @author Umar Ba <jUmarB@protonmail.com> 
 **/

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
