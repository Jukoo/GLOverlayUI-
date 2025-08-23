/**
 * @file  mainframe.H 
 * @brief Mainframe  application layout Controler 
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

#if !defined(GLOverlayUI_mainframe_h) 
#define      GLOverlayUI_mainframe_h 

#include <string>
#include <wx/wx.h>
#include <wx/aboutdlg.h>
#include <wx/splitter.h>
#include <wx/icon.h> 
#include <map>  

#include "GLOverlayUI_config.in.H" 
#include "canvasdriver.H"

#define  APP_TITLE   _PREFIX(APP_NAME)  
#define  APP_VERSION _PREFIX(VERSION)  
#define  APP_ICO     _PREFIX(ICON_APP) 

/**
 * @class  GLOverlayUI_APP 
 * @brief Handle Global Application state
 * */

class  GLOverlayUI_APP: public wxApp
{
  public : 
    virtual  bool OnInit(void) ; 
}; 

 
/**
 * @class MainFrame 
 * @brief Responsible  about main frame layout GLOverlayUI application 
 * */
class  MainFrame : public wxFrame  
{
   std::basic_string<char> _app_title;      /* ! Application  Title */
   std::basic_string<char> _app_status_text;/* ! Application status  text */

   std::map<std::basic_string<char>  , wxPanel*> _panels;  /* ! hold the panels  */ 
   
   wxIcon       _app_icon;                  /* ! Application  icon in .ico format */
   wxBoxSizer   * _main_boxsizer ;          /* ! Main box sizer split the layout in half*/
   wxCheckBox   * _checkbox ;               /* ! Checkbox  component  */
   wxSlider     * _slider ;                 /* ! Slider    component  */
   CanvasDriver * _canvas_driver ;          /* ! CanvasDriver  instance */

   /* -- UI Event -- */
   void on_exit(wxCommandEvent & evt) ; 
   void on_about(wxCommandEvent & evt); 
   void on_checking(wxCommandEvent  & evt) ; 
   void on_sliding (wxCommandEvent & evt) ;
   void on_sidepanel_toggle(wxCommandEvent & evt) ; 
   void on_refresh(wxCommandEvent &) ; 
   void on_zoom_in(wxCommandEvent &) ;  
   void on_zoom_out(wxCommandEvent &) ;  

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
      * @brief Calculate how the layout rendering  must be shared between panels
      * @return  int - (canvaspanel size | control panel size) 
      **/
     virtual int dispatch_layout (void)  ;  


  
}; 


#endif  /*! GLOverlayUI_mainframe_h*/ 
