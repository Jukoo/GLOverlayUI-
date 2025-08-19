/**
 * @file mainframe.C 
 * @brief main frame application implementation
 * @author  Umar Ba <jUmarB@protonmail.com> 
 * */


#include "mainframe.H" 
#include <cstdio> 
#include <iostream> 

MainFrame::MainFrame(std::basic_string<char> app_title) : 
  wxFrame(nullptr , wxID_ANY ,  app_title , 
      wxPoint(0,0), wxSize(MF_SIZE),DEF_FRAME_STYLE(0) ), _app_title(app_title) 
{

  setup_menubar();
  define_layout() ; 
  
  CreateStatusBar() ;
  SetStatusText("GLOverlayUI version  0.1.0-a1") ; 
  Bind(wxEVT_MENU , &MainFrame::on_about , this ,wxID_ABOUT) ; 
  Bind(wxEVT_MENU , &MainFrame::on_exit , this ,wxID_EXIT) ;

}

MainFrame::~MainFrame(){}  


void MainFrame::setup_menubar(void ) 
{
  wxMenu *helper = new wxMenu ; 
  helper->Append(wxID_EXIT) ; 
  helper->AppendSeparator() ; 
  helper->Append(wxID_ABOUT,"&About \tCtrl+a");  

  wxMenu *panel_settings  = new wxMenu ; 

  wxMenuBar *  menu_bar = new wxMenuBar ; 
  menu_bar->Append(helper , "&Help"); 

  SetMenuBar(menu_bar) ;

   wxToolBar* tb = new  wxToolBar(this , wxID_ANY) ; //CreateToolBar();
        //tb->Bind(wxEVT_TOOL, &MainFrame::OnTogglePanel, this);
        tb->Realize();

}







void MainFrame::define_layout(void) 
{

  int panel_sizes =   panel_sizing_layout_rule() ; 

  _main_boxsizer = new wxBoxSizer(wxHORIZONTAL) ;
  
  //std::vector<wxPanel *> panels  = createpanels(this, 2 , panel_sizing_layout_rule); 
  _panels["ctrl"]=  new wxPanel(this, wxID_ANY ,wxDefaultPosition , wxSize((panel_sizes & 0xffff), ~0)) ;
  _panels["ctrl"]->SetBackgroundColour(*wxLIGHT_GREY);
  _panels["canvas"] = new wxPanel(this,wxID_ANY ,wxDefaultPosition , wxSize((panel_sizes >> 0x10) , ~0)) ; 

  //!Append  items into ctlr panel ; 
  wxBoxSizer * ctrl_panel_vbox = new wxBoxSizer(wxVERTICAL) ;  
  wxStaticText *slider_label = new wxStaticText(_panels["ctrl"] , wxID_ANY , "Rotation /Scale"); 
  ctrl_panel_vbox->Add(slider_label , 0 ,  wxALIGN_CENTER , 5) ; 
  _slider  = new wxSlider(_panels["ctrl"] , wxID_ANY ,10 , 0 , 100, wxDefaultPosition , wxDefaultSize ,  wxSL_HORIZONTAL); 
  _slider->Bind(wxEVT_SLIDER ,  &MainFrame::on_sliding , this ) ;
  ctrl_panel_vbox->Add(_slider  , 0  , wxEXPAND| wxALL , 5 ) ;

  _checkbox  = new wxCheckBox(_panels["ctrl"]  , wxID_ANY , "Show Object") ; 
  _checkbox->Bind(wxEVT_CHECKBOX , &MainFrame::on_checking , this ) ; 
  ctrl_panel_vbox->Add(_checkbox , 0 , wxEXPAND| wxALL,10) ;  

  _panels["ctrl"]->SetSizer(ctrl_panel_vbox) ; 

  wxBoxSizer *canvas_panel_vbox = new wxBoxSizer(wxHORIZONTAL) ; 
  _canvas_driver=  new CanvasDriver(this) ; 
  canvas_panel_vbox->Add(_canvas_driver , 1 , wxEXPAND| wxALL ,1)  ; 
  _panels["canvas"]->SetSizer(canvas_panel_vbox) ; 

  int i = 0 ; 
  for (auto  const & panel :  _panels )  
    _main_boxsizer->Add(panel.second, (i=-~i), wxEXPAND|wxALL , 5) ; 

  SetSizer(_main_boxsizer) ;  
  Center() ; 
  
}



int  MainFrame::panel_sizing_layout_rule(void)
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
  about.SetName(APP_TITLE); 
  about.SetVersion("GLOverlayUI version 0.1.0-a1") ; 
  about.SetCopyright("(C) CopyRight 2025") ; 
  about.AddDeveloper("Umar Ba <jUmarB@protonmail.com> ") ; 
  
  wxIcon  ico(APP_ICO, wxBITMAP_TYPE_BMP , 0x64 , 0x64) ; 
  about.SetIcon(ico) ; 
  wxAboutBox(about) ;  
}


void MainFrame::on_checking(wxCommandEvent  & evt)  
{
  _main_boxsizer->Hide(&*_panels["ctrl"]) ;  
  Layout() ; 
}


void  MainFrame::on_sliding(wxCommandEvent  & evt) 
{
  puts("slid") ; 
}
