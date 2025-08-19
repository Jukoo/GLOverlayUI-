/** 
 * @file GLOverlayUI_APP.C 
 * @brief GLOverlayUI_APP entry point of the application 
 * @author Umar Ba <jUmarB@protonmail.com> 
 * 
 */
#include <cstdlib> 

#include "mainframe.H" 
#include "canvasdriver.H"


bool GLOverlayUI_APP::OnInit(void) 
{
   MainFrame * gframe = new MainFrame(APP_TITLE)  ; 
   
   //CanvasDriver  * canvasdriver = new CanvasDriver(gframe) ; 

    

   bool initial_status = true ;  
   initial_status ^=gframe->Show(initial_status) ;

   return !initial_status ; 
}

wxIMPLEMENT_APP(GLOverlayUI_APP);
