/**
 * @file mainframe.C 
 * @brief Mainframe layou logic implementation
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


#include "mainframe.H" 
#include <cstdio> 
#include <wx/bannerwindow.h>


MainFrame::MainFrame(std::basic_string<char> app_title) : 
  wxFrame(nullptr , wxID_ANY ,  app_title , 
      wxPoint(0,0), wxSize(MF_SIZE),DEF_FRAME_STYLE(0) ), _app_title(app_title), 
  _app_icon(GLOverlayUI_ICO)    
{

  SetIcon(_app_icon);    
  setup_menubar();
  define_layout() ;
  
  
  CreateStatusBar() ;
  SetStatusText("GLOverlayUI version  0.1.0-a1") ; 
  
  Bind(wxEVT_MENU , &MainFrame::on_about , this ,wxID_ABOUT) ; 
  Bind(wxEVT_MENU , &MainFrame::on_exit , this ,wxID_EXIT) ;
  Bind(wxEVT_MENU , &MainFrame::on_sidepanel_toggle ,  this , wxID_JUMP_TO) ;  
  Bind(wxEVT_MENU , &MainFrame::on_refresh , this , wxID_REFRESH) ; 
  Bind(wxEVT_MENU , &MainFrame::on_zoom_in , this , wxID_ZOOM_IN) ; 
  Bind(wxEVT_MENU , &MainFrame::on_zoom_out , this , wxID_ZOOM_OUT) ; 
}

MainFrame::~MainFrame(){}  


void MainFrame::setup_menubar(void ) 
{
  wxMenu *helper = new wxMenu ; 
  helper->Append(wxID_EXIT) ; 
  helper->AppendSeparator() ; 
  helper->Append(wxID_ABOUT,"&About \tCtrl+a");  

  wxMenu *view  = new wxMenu ; 
  view->Append(wxID_JUMP_TO ,"&Toggle SidePanel \tCtrl+t") ; 
  helper->AppendSeparator() ; 
  view->Append(wxID_REFRESH ,"&Refresh \tCtrl+r") ; 
  helper->AppendSeparator() ; 
  view->Append(wxID_ZOOM_IN ,"&Zoom In \tCtrl++") ;  
  helper->AppendSeparator() ; 
  view->Append(wxID_ZOOM_OUT ,"&Zoom Out \tCtrl+-") ;  
  
 
  wxMenuBar *  menu_bar = new wxMenuBar ; 
  menu_bar->Append(view ,  "&View"); 
  menu_bar->Append(helper , "&Help");
  SetMenuBar(menu_bar) ;

}

void MainFrame::define_layout(void) 
{

  int panel_sizes = dispatch_layout() ; 

  _main_boxsizer = new wxBoxSizer(wxHORIZONTAL) ;
  
  _panels["ctrl"]=  new wxPanel(this, wxID_ANY ,wxDefaultPosition , wxSize((panel_sizes & 0xffff), ~0)) ;
  _panels["ctrl"]->SetBackgroundColour(*wxLIGHT_GREY);
  _panels["canvas"] = new wxPanel(this,wxID_ANY ,wxDefaultPosition , wxSize((panel_sizes >> 0x10) , ~0)) ; 

  //!Append  items into ctlr panel ; 
  wxBoxSizer * ctrl_panel_vbox = new wxBoxSizer(wxVERTICAL) ;  
  wxStaticText *slider_label = new wxStaticText(_panels["ctrl"] , wxID_ANY , "(-) Scale (+)"); 
  ctrl_panel_vbox->Add(slider_label , 0 ,  wxALIGN_CENTER , 5) ; 
  _slider  = new wxSlider(_panels["ctrl"] , wxID_ANY ,10 , 0 , 100, wxDefaultPosition , wxDefaultSize ,  wxSL_HORIZONTAL); 
  _slider->Bind(wxEVT_SLIDER ,  &MainFrame::on_sliding , this ) ;
  ctrl_panel_vbox->Add(_slider  , 0  , wxEXPAND| wxALL , 5 ) ;

  _checkbox  = new wxCheckBox(_panels["ctrl"]  , wxID_ANY , "Show Objects");  
  _checkbox->SetValue(true) ; 
  _checkbox->Bind(wxEVT_CHECKBOX , &MainFrame::on_checking , this ) ; 
  ctrl_panel_vbox->Add(_checkbox , 0 , wxEXPAND| wxALL,10) ;  

  wxBannerWindow *tips = new wxBannerWindow(_panels["ctrl"] ,wxID_ANY )  ; //, wxDOWN) ; // wxSOUTH) ; 
  tips->SetText(GLOverlayUI_TIPS) ; 
  //tips->SetGradient(*wxLIGHT_GREY, *wxWHITE) ; 
  ctrl_panel_vbox->Add(tips , 5 , wxEXPAND | wxBOTTOM | wxRIGHT,0 ) ; 
  
  _panels["ctrl"]->SetSizer(ctrl_panel_vbox) ; 

  wxBoxSizer *canvas_panel_vbox = new wxBoxSizer(wxHORIZONTAL) ; 
  _canvas_driver=  new CanvasDriver(this) ; 
  _canvas_driver->set_renderer_state(_checkbox->GetValue())  ;  
  canvas_panel_vbox->Add(_canvas_driver , 1 , wxEXPAND| wxALL ,1)  ; 
  _panels["canvas"]->SetSizer(canvas_panel_vbox) ; 

  int i = 0 ; 
  for (auto  const & panel :  _panels )  
    _main_boxsizer->Add(panel.second, (i=-~i), wxEXPAND|wxALL , 0) ; 

  SetSizer(_main_boxsizer) ;  
  Center() ; 
  
}



int  MainFrame::dispatch_layout(void)
{
  struct  { 
    int  ctlr ; 
    int  canvas; 
  } panels = {  
      DEF_BASE_SIZE / 3 
  }; 
  
  panels.canvas = DEF_BASE_SIZE - panels.ctlr ; 
  
  return   (panels.canvas<< 0x10 | panels.ctlr) ; 

}


/*====================Event Handling ============================== */
void MainFrame::on_exit(wxCommandEvent & evt) 
{
   Close(true) ; 
}

void MainFrame::on_about(wxCommandEvent  & evt ) {
  wxAboutDialogInfo  about ;
  SetIcon(_app_icon); 
  about.SetName(APP_TITLE); 
  about.SetVersion("GLOverlayUI version 0.1.0-a1") ; 
  about.SetCopyright("(C) CopyRight 2025") ; 
  about.AddDeveloper("Umar Ba <jUmarB@protonmail.com> ") ; 
  about.AddArtist("Umar Ba <github.com/Jukoo>") ; 
  about.SetWebSite("https://gloverlayui.readthedocs.io/en/latest") ; 
  about.SetIcon(_app_icon) ;  
  wxAboutBox(about) ;    
}


void MainFrame::on_checking(wxCommandEvent  & evt)  
{  
  _canvas_driver->toggle_renderer(); 
}


void  MainFrame::on_sliding(wxCommandEvent  & evt) 
{
  float scale= static_cast<float>(evt.GetInt()) ; 
  scale /= 100.0f; 
  _canvas_driver->apply_scaling(scale) ; 
}


void MainFrame::on_sidepanel_toggle(wxCommandEvent &evt) 
{
  static bool toggle_state =false ; 
  toggle_state^=1 ;  
  if (toggle_state)
    _main_boxsizer->Hide(&*_panels["ctrl"]) ;  
  else 
    _main_boxsizer->Show(&*_panels["ctrl"]) ;  
   
  Layout() ;
}

void MainFrame::on_refresh(wxCommandEvent &evt)  
{
    Layout() ; 
}
void MainFrame::on_zoom_in(wxCommandEvent& evt ) 
{
  puts("zoom in") ; 
  _canvas_driver->increase_or_decrease_scaling('+')  ;  
  
}

void MainFrame::on_zoom_out(wxCommandEvent & evt) 
{
  _canvas_driver->increase_or_decrease_scaling('-')  ;  
}
