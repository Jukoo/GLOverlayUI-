/**  
 **/

#if !defined(GLOverlayUI_renderer_h)
#define GLOverlayUI_renderer_h 


enum { 
  TRIANGLES,  
#define TRIANGLES (1 << TRIANGLES) 
  QUADS ,
#define  QUADS   (1 << QUADS)  
  POLYGON
#define POLYGON  (1 << POLYGON)  
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
    int segments = 50; \
    float r = 0.3f;\
    float cx = 0.0f, cy = 0.5f;\
    for (int i = 0; i < segments; ++i) {\
          float theta = 2.0f * M_PI * float(i) / float(segments);\
          float x = r * cos(theta);\
          float y = r * sin(theta);\
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
 * @brief  Dedicated for Rendering  Object using OpenGL  
 * 
 */

class  Renderer
{  
  
  int _form_options =  RENDERER_ALL_FORM ; 
  public : 
    Renderer() ; 
    virtual  ~Renderer()= default ; 
  

    /** 
     * @brief  forms by setting form flags  mask by oring 
     */
    void   setforms(int __form_flag_options) ;
    
    /** 
     *  @brief retrieve bit mask for current enabling forms  
     *  @return int  - forms flags bit mask  
     */
    int    getforms(void) ;   
  
}; 

#endif  /* GLOverlayUI_renderer_h */
