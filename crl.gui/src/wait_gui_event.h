/*
 * File name: wait_gui_event.h
 * Date:      2019/03/29 23:13
 * Author:    Jan Faigl
 */

#ifndef __WAIT_GUI_EVENT_H__
#define __WAIT_GUI_EVENT_H__

#include <crl/waitobject.h>

#include <crl/gui/gui.h>
#include <crl/gui/guievent.h>
#include <crl/gui/guilistener.h>

namespace crl { namespace gui {

   class CWaitGuiEvent : CGuiListener {
    public:
      typedef SGuiEvent Event;

      CWaitGuiEvent(CGui &iGui);
      ~CWaitGuiEvent();

      bool handle(Event &event);

      void nextEvent(double &oX, double &oY, int &oCode, bool &oKey, bool &oMouse);

    private:
      typedef crl::concurrent::CWaitObject::Mutex Mutex;
      typedef crl::concurrent::CWaitObject::ScopedLock ScopedLock;

    private:
      CGui &gui;
      crl::concurrent::CWaitObject waitObject;
      bool enabled;
      Mutex enableMtx;
      double x;
      double y;
      int code;
      bool key;
      bool mouse;

   };

}} // namespace crl::gui

#endif

/* end of wait_gui_event.h */
