/** 
 * @file  GLOverlayUI_config.H  
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

#if !defined(GLOverlayUI_) 
#define GLOverlayUI_ 

#define  _STRINGIFY(_X)  #_X  
#define  _CONCATENATE(_X , _Y) _X ## _Y 

#define  GLOverlayUI_VERSION   "0.1.0"
#define  GLOverlayUI_APP_NAME  "GLOverlayUI"

#define  GLOverlayUI_ICON_APP  "/home/umar/Desktop/workstation/CGui/WxWidget/assets/logo/gloverui-ico.bmp" 

#define  GLOverlayUI_ICO "/home/umar/Desktop/workstation/CGui/WxWidget/assets/logo/gloverui.ico"
#define  _PREFIX(__prefix)\
         GLOverlayUI_ ## __prefix 


/*!  Define  the default base size of the frame  */
#if !defined(DEF_BASE_SIZE)
#define  DEF_BASE_SIZE     800 
#endif  

#if !defined(MF_SIZE) 
/*! Will have a square main frame window  */
# define  MF_SIZE  DEF_BASE_SIZE,DEF_BASE_SIZE 
#endif

/*! Desable  Option or Exclude option about frame style and behavior */
#define  DEF_FRAME_STYLE(_EXCLUDE_OPTION) \
  wxDEFAULT_FRAME_STYLE & ~(_EXCLUDE_OPTION) 




#define GLOverlayUI_TIPS "GLOverlayUI:Tips",\
  "Grab the Canvas Area with Your Mouse\n"\
  "And move it to  rotate objects"



#endif /*! GLOverlayUI_ */ 
