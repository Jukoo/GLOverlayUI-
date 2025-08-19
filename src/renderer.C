#include  "renderer.H" 


Renderer::Renderer(){} 


void Renderer::setforms(int form_flags) 
{
  _form_options|=form_flags ; 
}


int Renderer::getforms(void) 
{
  return _form_options ; 
}
