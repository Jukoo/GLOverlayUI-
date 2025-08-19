/**
 * @file  mainframe.H 
 * @brief Handle the main frame  application layout 
 * @author Umar Ba <jUmarB@protonmail.com> 
 * */

#if !defined(GLOverlayUI_mainframe_h) 
#define      GLOverlayUI_mainframe_h 

#include <string>
#include <wx/wx.h>
#include <wx/aboutdlg.h>
#include <wx/splitter.h>
#include <map>  

#include "GLOverlayUI_config.in.H" 
#include "canvasdriver.H"

#define  APP_TITLE   _PREFIX(APP_NAME)  
#define  APP_VERSION _PREFIX(VERSION)  
#define  APP_ICO     _PREFIX(ICON_APP) 
/*!  Define  the default base size of the frame  */
#if !defined(DEF_BASE_SIZE)
#define  DEF_BASE_SIZE     650 
#endif

#if !defined(MF_SIZE) 
/*! Will have a square main frame window  */
# define  MF_SIZE  DEF_BASE_SIZE,DEF_BASE_SIZE 
#endif

/*! Desable  Option or Exclude option about frame style and behavior */
#define  DEF_FRAME_STYLE(_EXCLUDE_OPTION) \
  wxDEFAULT_FRAME_STYLE & ~(_EXCLUDE_OPTION) 



/**
 * @class  GLOverlayUI_APP 
 * 
 * @brief Handle Global Application state
 * */

class  GLOverlayUI_APP: public wxApp
{
  public : 
    virtual  bool OnInit(void) ; 
}; 

 
/**
 * @class MainFrame 
 *
 * @brief Responsible  about main frame layout GLOverlayUI application 
 * */
class  MainFrame : public wxFrame 
{
   std::basic_string<char> _app_title; 
   std::basic_string<char> _app_status_text;

   wxBoxSizer * _main_boxsizer ;  
   wxCheckBox * _checkbox ;
   wxSlider   * _slider ; 
   std::map<std::basic_string<char>  , wxPanel*> _panels;  
   CanvasDriver * _canvas_driver ; 

   /**
    * @brief handle on exit event  
    * @param evt - the event 
    * */
   void  on_exit(wxCommandEvent & evt) ; 
   /**
    * @brief handle on exit event  
    * @param evt - the event 
    * */
   void  on_about(wxCommandEvent & evt); 

   /** 
    * @brief Handle checkbox event  
    **/

   void on_checking(wxCommandEvent  & evt) ; 

   /**
    * @brief Handle slider event 
    * */

   void on_sliding (wxCommandEvent & evt) ;
    
   /** 
    * @brief  Toggle sidepanel control
    */

   void on_sidepanel_toggle(wxCommandEvent & evt) ; 

   public:
   /**
    *  @fn MainFrame(std::basic_string<char>) 
    *  @brief  MainFrame class Constructor 
    *  @param  application_title  - The Application title 
    * */
     MainFrame(std::basic_string<char> application_title) ;  

     /**
      * @brief MainFrame class Destructor 
      **/
     virtual ~MainFrame() ;  

     /**
      * @brief setup the menu bar
      * */
     void setup_menubar(void) ; 

     /**
      * @brief  define the layout UI 
      * */
     void define_layout(void) ; 


     /**
      * @brief setting  rule on how panels should be arranged  
      * @return  int - (canvaspanel size | control panel size) 
      **/
     virtual int panel_sizing_layout_rule(void)  ;  


  
}; 


#endif  /*! GLOverlayUI_mainframe_h*/ 
