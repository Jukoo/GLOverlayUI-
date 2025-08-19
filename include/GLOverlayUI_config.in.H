/** 
 * @file  GLOverlayUI_config.H  
 * @brief Basic Configuration 
 * @author Umar Ba <jUmarB@protonmail.com> 
 */

#if !defined(GLOverlayUI_) 
#define GLOverlayUI_ 

#define  _STRINGIFY(_X)  #_X  
#define  _CONCATENATE(_X , _Y) _X ## _Y 

#define  GLOverlayUI_VERSION   "0.1.0"
#define  GLOverlayUI_APP_NAME  "GLOverlayUI"

#define  GLOverlayUI_ICON_APP  "/home/umar/Desktop/workstation/CGui/WxWidget/assets/logo/gloverui-ico.bmp" 

#define  _PREFIX(__prefix)\
         GLOverlayUI_ ## __prefix 

#endif /*! GLOverlayUI_ */ 
