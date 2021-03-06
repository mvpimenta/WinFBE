'    WinFBE - Programmer's Code Editor for the FreeBASIC Compiler
'    Copyright (C) 2016-2019 Paul Squires, PlanetSquires Software
'
'    This program is free software: you can redistribute it and/or modify
'    it under the terms of the GNU General Public License as published by
'    the Free Software Foundation, either version 3 of the License, or
'    (at your option) any later version.
'
'    This program is distributed in the hope that it will be useful,
'    but WITHOUT any WARRANTY; without even the implied warranty of
'    MERCHANTABILITY or FITNESS for A PARTICULAR PURPOSE.  See the
'    GNU General Public License for more details.

#include once "modVDProperties.bi"
#include once "clsApp.bi"
#include once "clsDocument.bi"
#include once "modVDColors.bi"



' ========================================================================================
' Display the Name and Description of the current selected Property.
' ========================================================================================
public function DisplayPropertyDetails() as Long
   
   Dim As HWnd hList = GetDlgItem(HWND_FRMVDTOOLBOX, IDC_FRMVDTOOLBOX_LSTPROPERTIES)
   Dim As HWnd hPropName = GetDlgItem(HWND_FRMVDTOOLBOX, IDC_FRMVDTOOLBOX_LBLPROPNAME)
   Dim As HWnd hPropDescribe = GetDlgItem(HWND_FRMVDTOOLBOX, IDC_FRMVDTOOLBOX_LBLPROPDESCRIBE )

   dim pProp as clsProperty ptr = GetActivePropertyPtr
    
   ' If the listbox is not visible then do not set the labels. It could be that a different
   ' listbox (Events) is active and is using the labels to display other information.
   if IsWindowVisible(hList) = false then exit function
   
   dim as CWSTR wszPropName, wszPropDescribe
   if pProp then 
      wszPropName = pProp->wszPropName
      gApp.PreviousPropName = pProp->wszPropName
   END IF
   
   select case ucase(wszPropName)
      CASE "NAME"
         wszPropDescribe = "Indicates the name used in code to identify the object."
      case "ACCEPTSRETURN"   
         wszPropDescribe = "Indicates if return characters are accepted as input for multiline edit controls."
      case "ACCEPTSTAB"   
         wszPropDescribe = "Indicates if tab characters are accepted as input for multiline edit controls."
      case "ACCEPTBUTTON"   
         wszPropDescribe = "If this is set, the button is 'clicked' whenever the user presses the 'ENTER' key."
      case "ALLOWDROP"   
         wszPropDescribe = "Indicates whether the control can accept data that the user drags onto it."
      case "BACKCOLOR"   
         wszPropDescribe = "The background color of the control. For Button controls the ThemeSupport property must be set to False."
      case "BACKCOLORDOWN"   
         wszPropDescribe = "The background color of the control when pressed. For Button controls the ThemeSupport property must be set to False."
      case "BACKCOLORHOT"   
         wszPropDescribe = "The background color of the control when the mouse is over the control. For Button controls the ThemeSupport property must be set to False."
      case "BACKCOLORSELECTED"   
         wszPropDescribe = "The background color of the selected item in a control."
      case "BACKGROUNDIMAGE"   
         wszPropDescribe = "The background image used for the control."
      case "BACKGROUNDIMAGELAYOUT"   
         wszPropDescribe = "The background image layout used for the control."
      case "BORDERSTYLE"   
         wszPropDescribe = "Indicates the appearance and behaviour of the border of the control."
      case "CANCELBUTTON"   
         wszPropDescribe = "If this is set, the button is 'clicked' whenever the user presses the 'ESC' key."
      case "CHARACTERCASING"   
         wszPropDescribe = "Indicates if all characters should be left alone or converted to uppercase or lowercase."
      case "CHECKALIGN"   
         wszPropDescribe = "Determines the location of the check box inside the control."
      case "CHECKED"   
         wszPropDescribe = "Indicates whether the control is checked."
      case "CHECKSTATE"   
         wszPropDescribe = "Indicates the state of the control."
      case "COLUMNWIDTH"   
         wszPropDescribe = "Indicates how wide each column should be in a multicolumn listbox."
      case "CONTROLBOX"   
         wszPropDescribe = "Determines whether a form has a Control/System menu box."
      CASE "DEFAULTCHARACTER"
         wszPropDescribe = "A default character that the control substitutes for each invalid character in the user input."
      CASE "DROPDOWNSTYLE"
         wszPropDescribe = "Specifies whether the list is always displayed or whether the list is displayed in a drop-down. Also specifies whether the text portion can be edited."
      case "ENABLED"   
         wszPropDescribe = "Indicates whether the control is enabled."
      case "FONT"   
         wszPropDescribe = "The font used to display text in the control."
      case "FORECOLOR"   
         wszPropDescribe = "The foreground color of the control which is used to display text."
      case "FORECOLORHOT"   
         wszPropDescribe = "The foreground color of the control when the mouse is over the control."
      case "FORECOLORSELECTED"   
         wszPropDescribe = "The foreground color of the selected item in a control."
      case "GROUPNAME"
         wszPropDescribe = "Controls with the same GroupName form part of the same OptionButton group."
      case "HIDESELECTION"   
         wszPropDescribe = "Indicates that the selection should be hidden when the edit control loses focus."
      case "HORIZONTALEXTENT"   
         wszPropDescribe = "The width in pixels by which a listbox can be scrolled horizontally. Only valid if HorizontalScrollBars is true."
      case "ICON"   
         wszPropDescribe = "The icon is displayed in the form's system menu box and when the form is minimized (use RC_DATA in Image Manager)."
      case "IMAGE"   
         wszPropDescribe = "The image that will be displayed on the control (use RC_DATA in Image Manager)."
      case "IMAGEHIGHDPI"   
         wszPropDescribe = "Determines whether high DPI scaling will be applied to the Image."
      case "IMAGESCALING"   
         wszPropDescribe = "Determines the scaling (if any) to apply to the Image."
      case "IMAGEWIDTH", "IMAGEHEIGHT"   
         wszPropDescribe = "The size of the image in pixels."
      case "IMAGEALIGN"   
         wszPropDescribe = "The alignment of the image that will be displayed on the control."
      case "IMAGEMARGIN"   
         wszPropDescribe = "The margin in pixels to apply to the image of a Button control."
      CASE "INPUTSTRING"
         wszPropDescribe = "A mask template string that specifies the literal characters that can appear at each position in the user input. Use the underscore character as a character placeholder."
'      case "INDEX"   
'         wszPropDescribe = "The position of the control within the OptionButton group."
      case "ITEMHEIGHT"   
         wszPropDescribe = "Determines the height of an individual item in a control."
      case "INTEGRALHEIGHT"   
         wszPropDescribe = "Indicates whether the list can contain only complete items."
      case "KEYPREVIEW"
         wszPropDescribe = "Determines whether the form will receive key events before the event is passed to the control that has focus."
      case "LOCKED"   
         wszPropDescribe = "Determines if the control can be moved or resized."
      CASE "MASKSTRING"
         wszPropDescribe = "A mask string that specifies the type of character that can appear at each position in the user input.."
      case "MAXLENGTH"   
         wszPropDescribe = "Indicates the maximum number of characters that can be entered into the edit control."
      case "MAXIMIZEBOX"   
         wszPropDescribe = "Determines whether a form has a maximize box in the upper-right corner of its caption bar."
      case "MINIMIZEBOX"   
         wszPropDescribe = "Determines whether a form has a minimize box in the upper-right corner of its caption bar."
      case "MAXIMUMWIDTH"   
         wszPropDescribe = "The maximun width size the form can be resized to."
      case "MAXIMUMHEIGHT"   
         wszPropDescribe = "The maximun height size the form can be resized to."
      case "MINIMUMWIDTH"   
         wszPropDescribe = "The minimum width size the form can be resized to."
      case "MINIMUMHEIGHT"   
         wszPropDescribe = "The minimum height size the form can be resized to."
      case "MULTICOLUMN"   
         wszPropDescribe = "Indicates if values should be displayed in columns horizontally."
      case "MULTILINE"   
         wszPropDescribe = "Controls whether the text of the edit control can span more than one line."
      case "PASSWORDCHAR"   
         wszPropDescribe = "Indicates the character to display for password input for single-line edit control."
      case "READONLY"   
         wszPropDescribe = "Controls whether the text in the edit control can be changed or not."
      case "SCROLLALWAYSVISIBLE"   
         wszPropDescribe = "Indicates if the listbox should always have a scrollbar present regardless of how many items are in it."
      case "TEXTSCROLLBARS"   
         wszPropDescribe = "Indicates for multiline edit controls which scroll bars will be shown for the control."
      case "SELECTIONMODE"   
         wszPropDescribe = "Indicates if the listbox is to be simple-select, multiselect, or not selectable."
      case "SHOWINTASKBAR"   
         wszPropDescribe = "Determines whether the form appears in the Windows Taskbar."
      case "SORTED"   
         wszPropDescribe = "Controls whether the list is sorted."
      case "LEFT", "TOP"   
         wszPropDescribe = "The coordinates of the upper-left corner of the control relative to the upper-left corner of its container."
      case "WIDTH", "HEIGHT"   
         wszPropDescribe = "The size of the control in pixels."
      case "STARTPOSITION"   
         wszPropDescribe = "Determines the position of a form when it first appears."
      case "TABINDEX"   
         wszPropDescribe = "Determines the index in the TAB order that this control will occupy."
      case "TABSTOP"   
         wszPropDescribe = "Indicates whether the user can use the TAB key to give focus to the control."
      case "TAG"   
         wszPropDescribe = "User-defined text data associated with the control."
      case "TEXT"   
         wszPropDescribe = "The text associated with the control."
      case "TEXTALIGN"   
         wszPropDescribe = "The alignment of the text that will be displayed on the control."
      case "TEXTFORECOLOR"   
         wszPropDescribe = "The foreground color of the displayed control text. For Button controls the ThemeSupport property must be set to False."
      case "TEXTBACKCOLOR"   
         wszPropDescribe = "The background color of the displayed control text. For Button controls the ThemeSupport property must be set to False."
      case "TEXTFORECOLORDOWN"   
         wszPropDescribe = "The foreground color of the displayed control text when pressed. For Button controls the ThemeSupport property must be set to False."
      case "TEXTBACKCOLORDOWN"   
         wszPropDescribe = "The background color of the displayed control text when pressed. For Button controls the ThemeSupport property must be set to False."
      case "TEXTMARGIN"   
         wszPropDescribe = "The margin in pixels to apply to the text of a Button control."
      case "THEMESUPPORT"   
         wszPropDescribe = "If True, the Windows Theme is applied to the control. Set to False to specify a BackColor and/or ForeColor for the control."
      case "THREESTATE"
         wszPropDescribe = "Indicates whether the checkbox will allow three check states rather than two."
      case "TOGGLEMODE"
         wszPropDescribe = "Determines if the button allows dual states to toggle from ON (pressed) to OFF (unpressed)."
      case "USEMNEMONIC"   
         wszPropDescribe = "If True, the first character preceded by an ampersand will be used as the button's mnemonic key."
      case "USETABSTOPS"   
         wszPropDescribe = "Indicates if TAB character should be expanded into full spacing."
      CASE "WINDOWSTATE"
         wszPropDescribe = "Determines the initial visual state of the form."
      CASE "WORDWRAP"
         wszPropDescribe = "Indicates if lines are automatically word wrapped for multiline edit controls."
      CASE "VALIDCHARACTERS"
         wszPropDescribe = "Specifies a string of valid characters that the user can enter. Empty string means all characters are valid."
      CASE "VISIBLE"
         wszPropDescribe = "Determines whether the control is visible or hidden."
      case else
         wszPropDescribe = ""
   END SELECT
   
   AfxSetWindowText(hPropName, wszPropName)
   AfxSetWindowText(hPropDescribe, wszPropDescribe)
   
   function = 0
end function

            
' ========================================================================================
' Display the Name and Description of the current selected Event.
' ========================================================================================
public function DisplayEventDetails() as Long
   
   Dim As HWnd hList = GetDlgItem(HWND_FRMVDTOOLBOX, IDC_FRMVDTOOLBOX_LSTEVENTS)
   Dim As HWnd hEventName = GetDlgItem(HWND_FRMVDTOOLBOX, IDC_FRMVDTOOLBOX_LBLPROPNAME)
   Dim As HWnd hEventDescribe = GetDlgItem(HWND_FRMVDTOOLBOX, IDC_FRMVDTOOLBOX_LBLPROPDESCRIBE )

   dim pEvent as clsEvent ptr = GetActiveEventPtr()

   ' If the listbox is not visible then do not set the labels. It could be that a different
   ' listbox (Properties) is active and is using the labels to display other information.
   if IsWindowVisible(hList) = false then exit function

   dim as CWSTR wszEventName, wszEventDescribe
   if pEvent then 
      wszEventName = pEvent->wszEventName
      gApp.PreviousEventName = pEvent->wszEventName
   END IF
   
   select case ucase(wszEventName)
      case "ALLEVENTS"
         wszEventDescribe = "Allows the user to respond to all Windows messages for the control."
      case "LOAD"
         wszEventDescribe = "Occurs whenever the user loads the form. Form and control window handles are valid at this point."
      CASE "SHOWN"
         wszEventDescribe = "Occurs whenever the form is first shown."
      CASE "ACTIVATED"
         wszEventDescribe = "Occurs whenever the form is activated."
      CASE "DEACTIVATE"
         wszEventDescribe = "Occurs whenever the form is deactivated."
      CASE "DESTROY"
         wszEventDescribe = "Occurs immediately before the control is about to be destroyed and all resources associated with it released."
      CASE "DROPDOWN"
         wszEventDescribe = "Occurs when the drop-down portion of the combobox is shown."
      CASE "DROPDOWNCLOSED"
         wszEventDescribe = "Indicates that the drop-down portion of the combobox has closed."
      CASE "GOTFOCUS"
         wszEventDescribe = "Occurs when the control receives focus."
      case "INITIALIZE"   
         wszEventDescribe = "Occurs before a form loads. Form and control window handles are invalid at this point."
      CASE "LOSTFOCUS"
         wszEventDescribe = "Occurs when the control loses focus."
      CASE "RESIZE"
         wszEventDescribe = "Occurs when a form is resized."
      CASE "FORMCLOSING"
         wszEventDescribe = "Occurs whenever the user closes the form, before the form has been closed."
      CASE "FORMCLOSED"
         wszEventDescribe = "Occurs whenever the user closes the form, after the form has been closed."
      CASE "MOVE"
         wszEventDescribe = "Occurs when a control is moved."
      CASE "CLICK"
         wszEventDescribe = "Occurs when a control is clicked."
      CASE "DROPFILES"
         wszEventDescribe = "Occurs whenever files are dropped on a control with the AllowDrop property enabled."
      CASE "MOUSEMOVE"
         wszEventDescribe = "Occurs when the mouse pointer is moved over the control."
      CASE "MOUSEDOWN"
         wszEventDescribe = "Occurs when the mouse pointer is over a control and a mouse button is pressed."
      CASE "MOUSEUP"
         wszEventDescribe = "Occurs when the mouse pointer is over a control and a mouse button is released."
      CASE "MOUSEDOUBLECLICK"
         wszEventDescribe = "Occurs when the control is double clicked by the mouse."
      CASE "MOUSEENTER"
         wszEventDescribe = "Occurs when the mouse pointer enters the control."
      CASE "MOUSEHOVER"
         wszEventDescribe = "Occurs when the mouse pointer rests on the control."
      CASE "MOUSELEAVE"
         wszEventDescribe = "Occurs when the mouse pointer leaves the control."
      case "TEXTCHANGED"   
         wszEventDescribe = "Occurs when the Text property is changed by either a programmatic modification or user interaction."
      CASE "KEYDOWN"
         wszEventDescribe = "Occurs when a key is first pressed."
      CASE "KEYPRESS"
         wszEventDescribe = "Occurs when a control has focus and the user presses and releases a key."
      CASE "KEYUP"
         wszEventDescribe = "Occurs when a key is released."
      case else
         wszEventDescribe = ""
   END SELECT
   
   AfxSetWindowText(hEventName, wszEventName)
   AfxSetWindowText(hEventDescribe, wszEventDescribe)
   
   function = 0
end function


' ========================================================================================
' Get the RGB (BGR) color value from the specified property value
' ========================================================================================
public function GetRGBColorFromProperty( byval pProp as clsProperty ptr ) as COLORREF
   if pProp = 0 then exit function
   
   dim as CWSTR wszPropValue, wszList, wszValue
   wszPropValue = pProp->wszPropValue
   wszList = AfxStrParse(wszPropValue, 1, "|")
   wszValue = AfxStrParse(wszPropValue, 2, "|")

   dim as long nLookFor
   select case **wszList
      CASE "CUSTOM"
         return val(wszValue) 
      case "COLORS": nLookFor = COLOR_COLORS
      case "SYSTEM": nLookFor = COLOR_SYSTEM
   end select
   for i as long = lbound(gColors) to ubound(gColors)
      if gColors(i).ColorType = nLookFor then
         if gColors(i).wszColorName = wszValue then
            return gColors(i).ColorValue
         end if
      end if   
   NEXT
   function = 0
end function


' ========================================================================================
' Set values of a LOGFONT based on property value string
' ========================================================================================
public function SetLogFontFromPropValue( byref wszPropValue as wstring ) as LOGFONT
   dim lf as LOGFONT
   lf.lfFaceName  = AfxStrParse(wszPropValue, 1, ",") 
   lf.lfHeight    = AfxGetFontHeight(val(AfxStrParse(wszPropValue, 2, ",")))
   lf.lfWeight    = val(AfxStrParse(wszPropValue, 3, ","))
   lf.lfItalic    = val(AfxStrParse(wszPropValue, 4, ","))
   lf.lfUnderline = val(AfxStrParse(wszPropValue, 5, ","))
   lf.lfStrikeOut = val(AfxStrParse(wszPropValue, 6, ","))
   lf.lfCharSet   = val(AfxStrParse(wszPropValue, 7, ","))
   function = lf
end function


' ========================================================================================
' Set values of a property value string based on LOGFONT 
' ========================================================================================
public function SetPropValueFromLogFont( byref lf as LOGFONT ) as CWSTR
   dim as CWSTR wszPropValue = _
   lf.lfFaceName  & "," & _
   AfxGetFontPointSize(lf.lfHeight) & "," & _
   lf.lfWeight    & "," & _
   lf.lfItalic    & "," & _
   lf.lfUnderline & "," & _
   lf.lfStrikeOut & "," & _
   lf.lfCharSet   
   function = wszPropValue
end function


' ========================================================================================
' Create a default value for a FONT property of a control
' ========================================================================================
private function CreateDefaultFontPropValue() as CWSTR
   
   Dim pWindow As CWindow Ptr = AfxCWindowPtr(HWnd_FRMMAIN)
   if pWindow = 0 THEN exit function
   
   dim lf as LOGFONT
   GetObject(pWindow->Font, sizeof(lf), @lf)
   
   function = SetPropValueFromLogFont(lf)
end function


' ========================================================================================
' Determine if an Property exists for a Form
' ========================================================================================
public function IsPropertyExists( byval pCtrl as clsControl ptr, _
                                  byval wszPropName as CWSTR _
                                  ) as boolean
   if pCtrl = 0 THEN return false
   dim as long lb = lbound(pCtrl->Properties)
   dim as long ub = ubound(pCtrl->Properties)
   dim as CWSTR wszPropName_ucase = ucase(wszPropName)
   
   for i as long = lb to ub
      if ucase(pCtrl->Properties(i).wszPropName) = wszPropName_ucase THEN
         return true
      END IF
   NEXT
   return false
end function


' ========================================================================================
' Determine if an Event exists for a Form
' ========================================================================================
public function IsEventExists( byval pCtrl as clsControl ptr, _
                               byval wszEventName as CWSTR _
                               ) as boolean
   if pCtrl = 0 THEN return false
   dim as long lb = lbound(pCtrl->Events)
   dim as long ub = ubound(pCtrl->Events)
   dim as CWSTR wszEventName_ucase = ucase(wszEventName)
   
   for i as long = lb to ub
      if ucase(pCtrl->Events(i).wszEventName) = wszEventName_ucase THEN
         return true
      END IF
   NEXT
   return false
end function


' ========================================================================================
' Retrieve the Property pointer for the specified control property
' ========================================================================================
public function GetControlPropertyPtr( byval pCtrl as clsControl ptr, _
                                       byval wszPropName as CWSTR _
                                       ) as clsProperty Ptr
   if pCtrl = 0 THEN return 0
   dim as long lb = lbound(pCtrl->Properties)
   dim as long ub = ubound(pCtrl->Properties)
   dim as CWSTR wszPropName_ucase = ucase(wszPropName)
   
   ' All property values are returned as strings. 
   for i as long = lb to ub
      if ucase(pCtrl->Properties(i).wszPropName) = wszPropName_ucase THEN
         return @pCtrl->Properties(i)
      END IF
   NEXT

   return 0
end function


' ========================================================================================
' Retrieve the value for the specified control property
' ========================================================================================
public function GetControlProperty( byval pCtrl as clsControl ptr, _
                                    byval wszPropName as CWSTR _
                                    ) as CWSTR
   dim pProp as clsProperty ptr = GetControlPropertyPtr(pCtrl, wszPropName)
   if pProp then return pProp->wszPropValue 
   return 0
end function


' ========================================================================================
' Set the value for the specified control property
' ========================================================================================
public function SetControlProperty( byval pCtrl as clsControl ptr, _
                                    byval wszPropName as CWSTR, _
                                    byval wszPropValue as CWSTR _
                                    ) as long
   if pCtrl = 0 then exit function
   dim as long lb = lbound(pCtrl->Properties)
   dim as long ub = ubound(pCtrl->Properties)
   dim as CWSTR wszPropName_ucase = ucase(wszPropName)
   
   for i as long = lb to ub
      if ucase(pCtrl->Properties(i).wszPropName) = wszPropName_ucase THEN
         ' Save the previous property value so that ApplyProperties will only
         ' act on any properties that have actually changed.
         pCtrl->Properties(i).wszPropValuePrev = pCtrl->Properties(i).wszPropValue
         pCtrl->Properties(i).wszPropValue = wszPropValue
         exit for
      END IF
   NEXT
   function = 0
end function


' ========================================================================================
' Add an event to the incoming control and optionally a value
' ========================================================================================
private function AddControlEvent( byval pCtrl as clsControl ptr, _
                                  byref wszEventName as CWSTR, _
                                  byval bIsSelected as boolean = false _
                                  ) as Long
   dim as long ub = ubound(pCtrl->Events) + 1
   redim preserve pCtrl->Events(ub) as clsEvent
   pCtrl->Events(ub).wszEventName = wszEventName
   pCtrl->Events(ub).bIsSelected = bIsSelected
   function = 0
end function


' ========================================================================================
' Set the value for the specified control event
' ========================================================================================
public function SetControlEvent( byval pCtrl as clsControl ptr, _
                                 byval wszEventName as CWSTR, _
                                 byval bIsSelected as boolean _
                                 ) as long
   if pCtrl = 0 then exit function
   dim as long lb = lbound(pCtrl->Events)
   dim as long ub = ubound(pCtrl->Events)
   dim as CWSTR wszEventName_ucase = ucase(wszEventName)
   
   for i as long = lb to ub
      if ucase(pCtrl->Events(i).wszEventName) = wszEventName_ucase THEN
         pCtrl->Events(i).bIsSelected = bIsSelected
         exit for
      END IF
   NEXT
   function = 0
end function



