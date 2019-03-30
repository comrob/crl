/*
 * File name: mouseclick.cc
 * Date:      2019/03/29 23:13
 * Author:    Jan Faigl
 */

#include <crl/gui/wait_gui_event.h>

using namespace crl::gui;

/// ----------------------------------------------------------------------------
/// Class CWaitForClick
/// ----------------------------------------------------------------------------
CWaitGuiEvent::CWaitGuiEvent(CGui &iGui) : CGuiListener(), gui(iGui)
{
   enabled = false;
   gui.getHandler()->registerListener(this);
}

/// ----------------------------------------------------------------------------
CWaitGuiEvent::~CWaitGuiEvent() { gui.getHandler()->unregisterListener(this); }

/// ----------------------------------------------------------------------------
bool CWaitGuiEvent::handle(Event &event)
{
   bool ret = false;
   if (enabled) {
      if (event.getType() == Event::MOUSE_PRESS) {
         gui.getRenderer()->canvas2Real(event.mouseX, event.mouseY, &x, &y);
	 mouse = true;
         ret = true;
         enabled = false;
         waitObject.notify();
      }
      if (event.getType() == Event::KEY_PRESS) {
	 key = true;
	 code = event.keyCode;
	 ret = true;
	 enabled = false;
	 waitObject.notify();
      }
   }
   return ret;
}

/// ----------------------------------------------------------------------------
void CWaitGuiEvent::nextEvent(double &oX, double &oY, int &oCode, bool &oKey, bool &oMouse)
{
   {
      ScopedLock lk(enableMtx);
      enabled = true;
      key = mouse = false;
   }
   waitObject.wait(); // wait for handler finished
   oX = x;
   oY = y;
   oCode = code;
   oKey = key;
   oMouse = mouse;
}

/* end of wait_gui_event.cc */
