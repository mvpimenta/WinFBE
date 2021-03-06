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

#include once "modVDApplyProperties.bi"
#include once "modVDDesignForm.bi"


' ========================================================================================
' Apply properties to the form 
' ========================================================================================
private function Form_ApplyProperties( byval pDoc as clsDocument ptr, _
                                       byval pCtrl as clsControl ptr, _
                                       byval pProp as clsProperty ptr _ 
                                       ) as Long
      
   Dim pWindow As CWindow Ptr = AfxCWindowPtr(pDoc->hWndForm)

   dim as long nPropValue
   dim as CWSTR wszPropName, wszPropValue
   
   wszPropName  = pProp->wszPropName
   wszPropValue = pProp->wszPropValue
   nPropValue   = Val(pProp->wszPropValue)
   
   select CASE ucase(wszPropName)

   case "BACKCOLOR"
      pWindow->Brush = CreateSolidBrush( GetRGBColorFromProperty(pProp) )
      AfxRedrawWindow(pCtrl->hWindow)
   
   case "CONTROLBOX"
      if wszPropValue = "True" then
         AfxAddWindowStyle(pCtrl->hWindow, WS_SYSMENU)
      else
         AfxRemoveWindowStyle(pCtrl->hWindow, WS_SYSMENU)
      end if
      AfxRedrawNonClientArea(pCtrl->hWindow) 
      
   case "ICON"
      dim pImageType as IMAGES_TYPE ptr = GetImagesTypePtr(wszPropValue)
      dim hIcon as HICON
      if pImageType then hIcon = AfxGdipIconFromFile(pImageType->wszFilename)
      SendMessage( pCtrl->hWindow, WM_SETICON, CAST(WPARAM, ICON_BIG), CAST(LPARAM, hIcon))
      SendMessage( pCtrl->hWindow, WM_SETICON, CAST(WPARAM, ICON_SMALL), CAST(LPARAM, hIcon))
      AfxRedrawNonClientArea(pCtrl->hWindow) 
      
   case "MAXIMIZEBOX"
      if wszPropValue = "True" then
         AfxAddWindowStyle(pCtrl->hWindow, WS_MAXIMIZEBOX)
      else
         AfxRemoveWindowStyle(pCtrl->hWindow, WS_MAXIMIZEBOX)
      end if
      AfxRedrawNonClientArea(pCtrl->hWindow) 

   case "MINIMIZEBOX"
      if wszPropValue = "True" then
         AfxAddWindowStyle(pCtrl->hWindow, WS_MINIMIZEBOX)
      else
         AfxRemoveWindowStyle(pCtrl->hWindow, WS_MINIMIZEBOX)
      end if
      AfxRedrawNonClientArea(pCtrl->hWindow) 
      
   case "BORDERSTYLE"
      ' Remove all existing styles before adding the new style
      AfxRemoveWindowStyle(pCtrl->hWindow, WS_BORDER)
      AfxRemoveWindowStyle(pCtrl->hWindow, WS_THICKFRAME)
      AfxRemoveWindowExStyle(pCtrl->hWindow, WS_EX_TOOLWINDOW)
      AfxRemoveWindowExStyle(pCtrl->hWindow, WS_EX_CLIENTEDGE)
      AfxRemoveWindowExStyle(pCtrl->hWindow, WS_EX_WINDOWEDGE)
      AfxRemoveWindowExStyle(pCtrl->hWindow, WS_EX_DLGMODALFRAME)
      
      select case **wszPropValue
         case "FormBorderStyle.None"
            AfxRemoveWindowStyle(pCtrl->hWindow, WS_CAPTION)
         case "FormBorderStyle.SizableToolWindow"
            AfxAddWindowStyle(pCtrl->hWindow, WS_BORDER)
            AfxAddWindowStyle(pCtrl->hWindow, WS_THICKFRAME)
            AfxAddWindowExStyle(pCtrl->hWindow, WS_EX_TOOLWINDOW)
         case "FormBorderStyle.FixedToolWindow"
            AfxAddWindowStyle(pCtrl->hWindow, WS_BORDER)
            AfxAddWindowStyle(pCtrl->hWindow, WS_DLGFRAME)
            AfxAddWindowExStyle(pCtrl->hWindow, WS_EX_TOOLWINDOW)
         case "FormBorderStyle.Sizable"
            AfxAddWindowStyle(pCtrl->hWindow, WS_THICKFRAME)
            AfxAddWindowStyle(pCtrl->hWindow, WS_DLGFRAME)
            AfxAddWindowStyle(pCtrl->hWindow, WS_BORDER)
            AfxAddWindowExStyle(pCtrl->hWindow, WS_EX_WINDOWEDGE)
         case "FormBorderStyle.Fixed3D"
            AfxAddWindowStyle(pCtrl->hWindow, WS_DLGFRAME)
            AfxAddWindowStyle(pCtrl->hWindow, WS_BORDER)
            AfxAddWindowExStyle(pCtrl->hWindow, WS_EX_WINDOWEDGE)
            AfxAddWindowExStyle(pCtrl->hWindow, WS_EX_CLIENTEDGE)
         case "FormBorderStyle.FixedSingle"
            AfxAddWindowStyle(pCtrl->hWindow, WS_DLGFRAME)
            AfxAddWindowStyle(pCtrl->hWindow, WS_BORDER)
            AfxAddWindowExStyle(pCtrl->hWindow, WS_EX_WINDOWEDGE)
         case "FormBorderStyle.FixedDialog"
            AfxAddWindowStyle(pCtrl->hWindow, WS_DLGFRAME)
            AfxAddWindowStyle(pCtrl->hWindow, WS_BORDER)
            AfxAddWindowExStyle(pCtrl->hWindow, WS_EX_DLGMODALFRAME)
      end select     
      AfxRedrawNonClientArea(pCtrl->hWindow) 

   end select
   
   function = 0
end function


' ========================================================================================
' Apply properties to the button
' ========================================================================================
private function Button_ApplyProperties( byval pDoc as clsDocument ptr, _
                                         byval pCtrl as clsControl ptr, _
                                         byval pProp as clsProperty ptr _ 
                                         ) as Long
   
   Dim pWindow As CWindow Ptr = AfxCWindowPtr(pDoc->hWndForm)

   dim as long nPropValue
   dim as CWSTR wszPropName, wszPropValue
   
   wszPropName  = pProp->wszPropName
   wszPropValue = pProp->wszPropValue
   nPropValue   = Val(pProp->wszPropValue)
   
   select CASE ucase(wszPropName)
   
   case "THEMESUPPORT"
      if wszPropValue = "True" then
         pCtrl->AfxButtonPtr->EnableTheming
      else
         pCtrl->AfxButtonPtr->DisableTheming
      end if
      
   case "IMAGE"
      dim pImageType as IMAGES_TYPE ptr = GetImagesTypePtr(wszPropValue)
      if pImageType then 
         pCtrl->AfxButtonPtr->SetImageFromFile( pImageType->wszFilename )
      end if

   case "IMAGEWIDTH"
      pCtrl->AfxButtonPtr->SetImageWidth( nPropValue )
      
   case "IMAGEHEIGHT"
      pCtrl->AfxButtonPtr->SetImageHeight( nPropValue )
         
   case "IMAGEHIGHDPI"
      ' The default width/height is 16x16 so adjust that size accordingly.
      dim as long nWidth = val( GetControlProperty(pCtrl, "IMAGEWIDTH") )
      dim as long nHeight = val( GetControlProperty(pCtrl, "IMAGEHEIGHT") )
      if wszPropValue = "True" then
         pCtrl->AfxButtonPtr->SetImageSize( pWindow->ScaleX(nWidth), pWindow->ScaleY(nHeight), true )
      end if
      
   case "BACKCOLOR"
      pCtrl->AfxButtonPtr->SetButtonBkColor( GetRGBColorFromProperty(pProp), true )

   case "TEXTFORECOLOR"
      pCtrl->AfxButtonPtr->SetTextForeColor( GetRGBColorFromProperty(pProp), true )

   case "TEXTBACKCOLOR"
      pCtrl->AfxButtonPtr->SetTextBkColor( GetRGBColorFromProperty(pProp), true )

   case "TEXTMARGIN"
      pCtrl->AfxButtonPtr->SetTextMargin( nPropValue, true )

   case "TEXTALIGN"
      dim as long wsStyle
      select case **wszPropValue
         CASE "ButtonAlignment.BottomCenter": wsStyle = DT_CENTER OR DT_BOTTOM
         CASE "ButtonAlignment.BottomLeft":   wsStyle = DT_LEFT   OR DT_BOTTOM
         CASE "ButtonAlignment.BottomRight":  wsStyle = DT_RIGHT  OR DT_BOTTOM
         CASE "ButtonAlignment.MiddleCenter": wsStyle = DT_CENTER OR DT_VCENTER
         CASE "ButtonAlignment.MiddleLeft":   wsStyle = DT_LEFT   OR DT_VCENTER
         CASE "ButtonAlignment.MiddleRight":  wsStyle = DT_RIGHT  OR DT_VCENTER
         CASE "ButtonAlignment.TopCenter":    wsStyle = DT_CENTER OR DT_TOP
         CASE "ButtonAlignment.TopLeft":      wsStyle = DT_LEFT   OR DT_TOP
         CASE "ButtonAlignment.TopRight":     wsStyle = DT_RIGHT  OR DT_TOP
      END SELECT
      pCtrl->AfxButtonPtr->SetTextFormat(wsStyle OR DT_SINGLELINE, true)

   end select
   
   function = 0
end function


' ========================================================================================
' Apply properties to the label
' ========================================================================================
private function Label_ApplyProperties( byval pDoc as clsDocument ptr, _
                                        byval pCtrl as clsControl ptr, _
                                        byval pProp as clsProperty ptr _ 
                                        ) as Long
    
   Dim pWindow As CWindow Ptr = AfxCWindowPtr(pDoc->hWndForm)

   dim as long nPropValue
   dim as CWSTR wszPropName, wszPropValue
   
   wszPropName  = pProp->wszPropName
   wszPropValue = pProp->wszPropValue
   nPropValue   = Val(pProp->wszPropValue)
   
   select CASE ucase(wszPropName)
      
   case "BACKCOLOR"
      dim as COLORREF clrBack = GetRGBColorFromProperty(pProp)
      if pCtrl->hBackBrush then DeleteBrush(pCtrl->hBackBrush)
      pCtrl->hBackBrush = CreateSolidBrush(clrBack)
      AfxRedrawWindow(pCtrl->hWindow)

   case "BORDERSTYLE"
      AfxRemoveWindowExStyle(pCtrl->hWindow, WS_EX_CLIENTEDGE)
      AfxRemoveWindowStyle(pCtrl->hWindow, WS_BORDER)
      dim as long wsStyle
      select case **wszPropValue
         case "ControlBorderStyle.None"
         case "ControlBorderStyle.Fixed3D"
            AfxAddWindowExStyle(pCtrl->hWindow, WS_EX_CLIENTEDGE)
         case "ControlBorderStyle.FixedSingle"
            AfxAddWindowStyle(pCtrl->hWindow, WS_BORDER)
      end select
      AfxRedrawNonClientArea(pCtrl->hWindow) 

   end select
   
   function = 0
end function


' ========================================================================================
' Apply properties to the checkbox
' ========================================================================================
private function CheckBox_ApplyProperties( byval pDoc as clsDocument ptr, _
                                           byval pCtrl as clsControl ptr, _
                                           byval pProp as clsProperty ptr _ 
                                           ) as Long
   
   Dim pWindow As CWindow Ptr = AfxCWindowPtr(pDoc->hWndForm)

   dim as long nPropValue
   dim as CWSTR wszPropName, wszPropValue
   
   wszPropName  = pProp->wszPropName
   wszPropValue = pProp->wszPropValue
   nPropValue   = Val(pProp->wszPropValue)
   
   select CASE ucase(wszPropName)
      
   case "BACKCOLOR"
      dim as COLORREF clrBack = GetRGBColorFromProperty(pProp)
      if pCtrl->hBackBrush then DeleteBrush(pCtrl->hBackBrush)
      pCtrl->hBackBrush = CreateSolidBrush(clrBack)
      AfxRedrawWindow(pCtrl->hWindow)

   case "CHECKSTATE"
      dim as long wsState
      select case **wszPropValue
         Case "CheckBoxState.Checked": wsState = BST_CHECKED
         Case "CheckBoxState.UnChecked": wsState = BST_UNCHECKED
         Case "CheckBoxState.Indeterminate": wsState = BST_INDETERMINATE
      End Select   
      SendMessage( pCtrl->hWindow, BM_SETCHECK, wsState, 0)
      AfxRedrawWindow(pCtrl->hWindow)
      
   case "THREESTATE"
      AfxRemoveWindowStyle(pCtrl->hWindow, BS_AUTOCHECKBOX)
      AfxRemoveWindowStyle(pCtrl->hWindow, BS_AUTO3STATE)
      if wszPropValue = "True" then
         AfxAddWindowStyle(pCtrl->hWindow, BS_AUTO3STATE)
      else
         AfxAddWindowStyle(pCtrl->hWindow, BS_AUTOCHECKBOX)
      end if
         
   case "TEXTALIGN"
      AfxRemoveWindowStyle(pCtrl->hWindow, BS_CENTER)
      AfxRemoveWindowStyle(pCtrl->hWindow, BS_LEFT)
      AfxRemoveWindowStyle(pCtrl->hWindow, BS_RIGHT)
      AfxRemoveWindowStyle(pCtrl->hWindow, BS_TOP)
      AfxRemoveWindowStyle(pCtrl->hWindow, BS_BOTTOM)
      AfxRemoveWindowStyle(pCtrl->hWindow, BS_VCENTER)
      dim as long wsStyle
      select case **wszPropValue
         CASE "ButtonAlignment.BottomCenter": wsStyle = BS_CENTER OR BS_BOTTOM
         CASE "ButtonAlignment.BottomLeft":   wsStyle = BS_LEFT   OR BS_BOTTOM
         CASE "ButtonAlignment.BottomRight":  wsStyle = BS_RIGHT  OR BS_BOTTOM
         CASE "ButtonAlignment.MiddleCenter": wsStyle = BS_CENTER OR BS_VCENTER
         CASE "ButtonAlignment.MiddleLeft":   wsStyle = BS_LEFT   OR BS_VCENTER
         CASE "ButtonAlignment.MiddleRight":  wsStyle = BS_RIGHT  OR BS_VCENTER
         CASE "ButtonAlignment.TopCenter":    wsStyle = BS_CENTER OR BS_TOP
         CASE "ButtonAlignment.TopLeft":      wsStyle = BS_LEFT   OR BS_TOP
         CASE "ButtonAlignment.TopRight":     wsStyle = BS_RIGHT  OR BS_TOP
      END SELECT
      AfxAddWindowStyle(pCtrl->hWindow, wsStyle)
      AfxRedrawNonClientArea(pCtrl->hWindow) 

   end select
   
   function = 0
end function


' ========================================================================================
' Apply properties to the optionbutton
' ========================================================================================
private function OptionButton_ApplyProperties( byval pDoc as clsDocument ptr, _
                                               byval pCtrl as clsControl ptr, _
                                               byval pProp as clsProperty ptr _ 
                                               ) as Long
   
   Dim pWindow As CWindow Ptr = AfxCWindowPtr(pDoc->hWndForm)

   dim as long nPropValue
   dim as CWSTR wszPropName, wszPropValue
   
   wszPropName  = pProp->wszPropName
   wszPropValue = pProp->wszPropValue
   nPropValue   = Val(pProp->wszPropValue)
   
   select CASE ucase(wszPropName)
      
   case "BACKCOLOR"
      dim as COLORREF clrBack = GetRGBColorFromProperty(pProp)
      if pCtrl->hBackBrush then DeleteBrush(pCtrl->hBackBrush)
      pCtrl->hBackBrush = CreateSolidBrush(clrBack)
      AfxRedrawWindow(pCtrl->hWindow)

   case "CHECKED"
      ' If Checked is True then cycle through all of the other OptionButtons in
      ' the same group and toggle their Checked property to False.
      if wszPropValue = "True" then
         dim pCtrl2 as clsControl ptr
         dim as CWSTR wszOptionGroup = ucase(GetControlProperty(pCtrl, "GROUPNAME")) 
         for i as long = pDoc->Controls.ItemFirst to pDoc->Controls.ItemLast
            pCtrl2 = pDoc->Controls.ItemAt(i)
            if pCtrl2->ControlType <> CTRL_OPTION then continue for
            if pCtrl2 = pCtrl then continue for
            if ucase(GetControlProperty(pCtrl2, "GROUPNAME")) = wszOptionGroup THEN
               SetControlProperty(pCtrl2, "CHECKED", "False") 
               SendMessage( pCtrl2->hWindow, BM_SETCHECK, BST_UNCHECKED, 0)
               AfxRedrawWindow(pCtrl2->hWindow)
            end if
         NEXT
         SendMessage( pCtrl->hWindow, BM_SETCHECK, BST_CHECKED, 0)
         AfxRedrawWindow(pCtrl->hWindow)
      end if
      
   case "TEXTALIGN"
      AfxRemoveWindowStyle(pCtrl->hWindow, BS_CENTER)
      AfxRemoveWindowStyle(pCtrl->hWindow, BS_LEFT)
      AfxRemoveWindowStyle(pCtrl->hWindow, BS_RIGHT)
      AfxRemoveWindowStyle(pCtrl->hWindow, BS_TOP)
      AfxRemoveWindowStyle(pCtrl->hWindow, BS_BOTTOM)
      AfxRemoveWindowStyle(pCtrl->hWindow, BS_VCENTER)
      dim as long wsStyle
      select case **wszPropValue
         CASE "ButtonAlignment.BottomCenter": wsStyle = BS_CENTER OR BS_BOTTOM
         CASE "ButtonAlignment.BottomLeft":   wsStyle = BS_LEFT   OR BS_BOTTOM
         CASE "ButtonAlignment.BottomRight":  wsStyle = BS_RIGHT  OR BS_BOTTOM
         CASE "ButtonAlignment.MiddleCenter": wsStyle = BS_CENTER OR BS_VCENTER
         CASE "ButtonAlignment.MiddleLeft":   wsStyle = BS_LEFT   OR BS_VCENTER
         CASE "ButtonAlignment.MiddleRight":  wsStyle = BS_RIGHT  OR BS_VCENTER
         CASE "ButtonAlignment.TopCenter":    wsStyle = BS_CENTER OR BS_TOP
         CASE "ButtonAlignment.TopLeft":      wsStyle = BS_LEFT   OR BS_TOP
         CASE "ButtonAlignment.TopRight":     wsStyle = BS_RIGHT  OR BS_TOP
      END SELECT
      AfxAddWindowStyle(pCtrl->hWindow, wsStyle)
      AfxRedrawNonClientArea(pCtrl->hWindow) 

   end select
   
   function = 0
end function


' ========================================================================================
' Apply properties to the listbox
' ========================================================================================
private function ListBox_ApplyProperties( byval pDoc as clsDocument ptr, _
                                          byval pCtrl as clsControl ptr, _
                                          byval pProp as clsProperty ptr _ 
                                          ) as Long
   
   Dim pWindow As CWindow Ptr = AfxCWindowPtr(pDoc->hWndForm)
   if pWindow = 0 then exit function
   
   dim as long nPropValue
   dim as CWSTR wszPropName, wszPropValue
   
   wszPropName  = pProp->wszPropName
   wszPropValue = pProp->wszPropValue
   nPropValue   = Val(pProp->wszPropValue)
   
   select CASE ucase(wszPropName)
      
   case "BACKCOLOR"
      dim as COLORREF clrBack = GetRGBColorFromProperty(pProp)
      if pCtrl->hBackBrush then DeleteBrush(pCtrl->hBackBrush)
      pCtrl->hBackBrush = CreateSolidBrush(clrBack)
      AfxRedrawWindow(pCtrl->hWindow)

   case "BORDERSTYLE"
      AfxRemoveWindowExStyle(pCtrl->hWindow, WS_EX_CLIENTEDGE)
      AfxRemoveWindowStyle(pCtrl->hWindow, WS_BORDER)
      dim as long wsStyle                                     
      select case **wszPropValue
         case "ControlBorderStyle.None"
         case "ControlBorderStyle.Fixed3D"
            AfxAddWindowExStyle(pCtrl->hWindow, WS_EX_CLIENTEDGE)
         case "ControlBorderStyle.FixedSingle"
            AfxAddWindowStyle(pCtrl->hWindow, WS_BORDER)
      end select
      AfxRedrawNonClientArea(pCtrl->hWindow) 

   case "INTEGRALHEIGHT"
      ' Do not do anything with the IntegralHeight property. Let the user size at whatever
      ' size he wishes during runtime. If property is set to True then it will resize
      ' appropriately at runtime. It appears that even though you can dynamically set the
      ' NOINTEGRALHEIGHT flag, the control itself doesn't seem to respond to it correctly
      ' once the original listview has been cfreated.

   end select
   
   function = 0
end function


' ========================================================================================
' Apply properties to the combobox
' ========================================================================================
private function ComboBox_ApplyProperties( byval pDoc as clsDocument ptr, _
                                           byval pCtrl as clsControl ptr, _
                                           byval pProp as clsProperty ptr _ 
                                           ) as Long
   
   Dim pWindow As CWindow Ptr = AfxCWindowPtr(pDoc->hWndForm)
   if pWindow = 0 then exit function
   
   dim as long nPropValue
   dim as CWSTR wszPropName, wszPropValue
   
   wszPropName  = pProp->wszPropName
   wszPropValue = pProp->wszPropValue
   nPropValue   = Val(pProp->wszPropValue)
   
   select CASE ucase(wszPropName)
      
   case "BACKCOLOR"
      dim as COLORREF clrBack = GetRGBColorFromProperty(pProp)
      if pCtrl->hBackBrush then DeleteBrush(pCtrl->hBackBrush)
      pCtrl->hBackBrush = CreateSolidBrush(clrBack)
      AfxRedrawWindow(pCtrl->hWindow)

   case "BORDERSTYLE"
      AfxRemoveWindowExStyle(pCtrl->hWindow, WS_EX_CLIENTEDGE)
      AfxRemoveWindowStyle(pCtrl->hWindow, WS_BORDER)
      dim as long wsStyle                                     
      select case **wszPropValue
         case "ControlBorderStyle.None"
         case "ControlBorderStyle.Fixed3D"
            AfxAddWindowExStyle(pCtrl->hWindow, WS_EX_CLIENTEDGE)
         case "ControlBorderStyle.FixedSingle"
            AfxAddWindowStyle(pCtrl->hWindow, WS_BORDER)
      end select
      AfxRedrawNonClientArea(pCtrl->hWindow) 

   case "DROPDOWNSTYLE"
      dim as long nCtrlId, dwStyle, dwExStyle = -1
      dwStyle = WS_CHILD or WS_VISIBLE OR WS_HSCROLL OR WS_VSCROLL OR WS_BORDER OR _
                CBS_HASSTRINGS or CBS_NOINTEGRALHEIGHT 
      Select Case **wszPropValue
         Case "ComboBoxStyle.Simple":       dwStyle = dwStyle OR CBS_SIMPLE 
         Case "ComboBoxStyle.DropDown":     dwStyle = dwStyle OR CBS_DROPDOWN 
         Case "ComboBoxStyle.DropDownList": dwStyle = dwStyle OR CBS_DROPDOWNLIST 
      End Select
      dim as CWSTR wszControlName = GetControlProperty(pCtrl, "NAME")
      dim rcDraw as RECT = GetControlRect(pCtrl)
      nCtrlId = GetDlgCtrlID(pCtrl->hWindow)
      DestroyWindow(pCtrl->hWindow)
      pCtrl->hWindow = pWindow->AddControl( "ComboBox", , nCtrlId, wszControlName, _
                       rcDraw.left, rcDraw.top, rcDraw.right-rcDraw.left, rcDraw.bottom-rcDraw.top, _
                       dwStyle, dwExStyle, , _
                       CAST(SUBCLASSPROC, @Control_SubclassProc), CTRL_COMBOBOX, CAST(DWORD_PTR, pDoc))
      ' Also subclass the combobox edit control
      dim as HWND hWndEditCtrl = ComboBox_GetEditBoxHandle(pCtrl->hWindow)
      if IsWindow(hWndEditCtrl) then
         SetWindowSubclass(hWndEditCtrl, CAST(SUBCLASSPROC, @Control_SubclassProc), CTRL_COMBOBOX, CAST(DWORD_PTR, pDoc))
      end if
      dim as HWND hWndListCtrl = ComboBox_GetListBoxHandle(pCtrl->hWindow)
      if IsWindow(hWndListCtrl) then
         SetWindowSubclass(hWndListCtrl, CAST(SUBCLASSPROC, @Control_SubclassProc), CTRL_COMBOBOX, CAST(DWORD_PTR, pDoc))
      end if
      AfxRedrawNonClientArea(pCtrl->hWindow) 
      
   end select
   
   function = 0
end function


' ========================================================================================
' Apply properties to the textbox
' ========================================================================================
private function TextBox_ApplyProperties( byval pDoc as clsDocument ptr, _
                                          byval pCtrl as clsControl ptr, _
                                          byval pProp as clsProperty ptr _ 
                                          ) as Long
   
   Dim pWindow As CWindow Ptr = AfxCWindowPtr(pDoc->hWndForm)

   dim as long nPropValue
   dim as CWSTR wszPropName, wszPropValue
   
   wszPropName  = pProp->wszPropName
   wszPropValue = pProp->wszPropValue
   nPropValue   = Val(pProp->wszPropValue)
   
   select CASE ucase(wszPropName)
      
   case "BACKCOLOR"
      dim as COLORREF clrBack = GetRGBColorFromProperty(pProp)
      if pCtrl->hBackBrush then DeleteBrush(pCtrl->hBackBrush)
      pCtrl->hBackBrush = CreateSolidBrush(clrBack)

   case "BORDERSTYLE"
      AfxRemoveWindowExStyle(pCtrl->hWindow, WS_EX_CLIENTEDGE)
      AfxRemoveWindowStyle(pCtrl->hWindow, WS_BORDER)
      select case **wszPropValue
         case "ControlBorderStyle.None"
         case "ControlBorderStyle.Fixed3D"
            AfxAddWindowExStyle(pCtrl->hWindow, WS_EX_CLIENTEDGE)
         case "ControlBorderStyle.FixedSingle"
            AfxAddWindowStyle(pCtrl->hWindow, WS_BORDER)
      end select
      AfxRedrawNonClientArea(pCtrl->hWindow) 

   case "CHARACTERCASING"
      AfxRemoveWindowStyle(pCtrl->hWindow, ES_LOWERCASE)
      AfxRemoveWindowStyle(pCtrl->hWindow, ES_UPPERCASE)
      select case **wszPropValue
         Case "CharacterCase.Normal"
         Case "CharacterCase.Upper"
            AfxAddWindowStyle(pCtrl->hWindow, ES_UPPERCASE)
         Case "CharacterCase.Lower"
            AfxAddWindowStyle(pCtrl->hWindow, ES_LOWERCASE)
      End Select
      AfxRedrawWindow(pCtrl->hWindow)

   CASE "MULTILINE"
      if wszPropValue = "True" then
         AfxAddWindowStyle(pCtrl->hWindow, ES_MULTILINE)
      else   
         AfxRemoveWindowStyle(pCtrl->hWindow, ES_MULTILINE)
      END IF
      AfxRedrawWindow(pCtrl->hWindow)

   case "PASSWORDCHAR"
      Dim As Long iChr = 0
      If Len(wszPropValue) Then iChr = wszPropValue[0]
      SendMessage(pCtrl->hWindow, EM_SETPASSWORDCHAR, iChr, 0)
      AfxRedrawWindow(pCtrl->hWindow)
      
   case "TEXTSCROLLBARS"
      AfxRemoveWindowStyle(pCtrl->hWindow, WS_HSCROLL)
      AfxRemoveWindowStyle(pCtrl->hWindow, WS_VSCROLL)
      dim as long wsStyle
      select case **wszPropValue
         case "ScrollBars.None"
         case "ScrollBars.Horizontal"
            wsStyle = WS_HSCROLL
         case "ScrollBars.Vertical"
            wsStyle = WS_VSCROLL
         case "ScrollBars.Both"
            wsStyle = (WS_HSCROLL or WS_VSCROLL)
      end select
      AfxAddWindowStyle(pCtrl->hWindow, wsStyle)
      AfxRedrawNonClientArea(pCtrl->hWindow) 

   case "TEXTALIGN"
      AfxRemoveWindowStyle(pCtrl->hWindow, ES_CENTER)
      AfxRemoveWindowStyle(pCtrl->hWindow, ES_LEFT)
      AfxRemoveWindowStyle(pCtrl->hWindow, ES_RIGHT)
      dim as long wsStyle
      select case **wszPropValue
         CASE "TextAlignment.Left":   wsStyle = ES_LEFT
         CASE "TextAlignment.Center": wsStyle = ES_CENTER 
         CASE "TextAlignment.Right":  wsStyle = ES_RIGHT  
      END SELECT
      AfxAddWindowStyle(pCtrl->hWindow, wsStyle)
      AfxRedrawNonClientArea(pCtrl->hWindow) 

   end select
   
   function = 0
end function


' ========================================================================================
' Apply properties to the MaskedEdit textbox
' ========================================================================================
private function MaskedEdit_ApplyProperties( byval pDoc as clsDocument ptr, _
                                             byval pCtrl as clsControl ptr, _
                                             byval pProp as clsProperty ptr _ 
                                             ) as Long
   
   Dim pWindow As CWindow Ptr = AfxCWindowPtr(pDoc->hWndForm)

   dim as long nPropValue
   dim as CWSTR wszPropName, wszPropValue
   
   wszPropName  = pProp->wszPropName
   wszPropValue = pProp->wszPropValue
   nPropValue   = Val(pProp->wszPropValue)
   
   select CASE ucase(wszPropName)
      
   case "BACKCOLOR"
      dim as COLORREF clrBack = GetRGBColorFromProperty(pProp)
      if pCtrl->hBackBrush then DeleteBrush(pCtrl->hBackBrush)
      pCtrl->hBackBrush = CreateSolidBrush(clrBack)

   case "BORDERSTYLE"
      AfxRemoveWindowExStyle(pCtrl->hWindow, WS_EX_CLIENTEDGE)
      AfxRemoveWindowStyle(pCtrl->hWindow, WS_BORDER)
      select case **wszPropValue
         case "ControlBorderStyle.None"
         case "ControlBorderStyle.Fixed3D"
            AfxAddWindowExStyle(pCtrl->hWindow, WS_EX_CLIENTEDGE)
         case "ControlBorderStyle.FixedSingle"
            AfxAddWindowStyle(pCtrl->hWindow, WS_BORDER)
      end select
      AfxRedrawNonClientArea(pCtrl->hWindow) 

   case "TEXT", "MASKSTRING", "INPUTSTRING", "DEFAULTCHARACTER"
      dim as CWSTR wszMaskString = GetControlProperty(pCtrl, "MASKSTRING")
      dim as CWSTR wszInputString = GetControlProperty(pCtrl, "INPUTSTRING")
      dim as CWSTR wszDefaultCharacter = GetControlProperty(pCtrl, "DEFAULTCHARACTER")
      dim as CWSTR wszValidCharacters = GetControlProperty(pCtrl, "VALIDCHARACTERS")
      dim as CWSTR wszText = GetControlProperty(pCtrl, "TEXT")
      pCtrl->AfxMaskedPtr->EnableMask(wszMaskString, wszInputString, wszDefaultCharacter, wszValidCharacters)
      pCtrl->AfxMaskedPtr->SetText(wszText, false)
      
   end select
   
   function = 0
end function


' ========================================================================================
' Apply properties to the frame
' ========================================================================================
private function Frame_ApplyProperties( byval pDoc as clsDocument ptr, _
                                        byval pCtrl as clsControl ptr, _
                                        byval pProp as clsProperty ptr _ 
                                        ) as Long
    
   Dim pWindow As CWindow Ptr = AfxCWindowPtr(pDoc->hWndForm)

   dim as long nPropValue
   dim as CWSTR wszPropName, wszPropValue
   
   wszPropName  = pProp->wszPropName
   wszPropValue = pProp->wszPropValue
   nPropValue   = Val(pProp->wszPropValue)
   
   select CASE ucase(wszPropName)
      
   case "BACKCOLOR"
      dim as COLORREF clrBack = GetRGBColorFromProperty(pProp)
      if pCtrl->hBackBrush then DeleteBrush(pCtrl->hBackBrush)
      pCtrl->hBackBrush = CreateSolidBrush(clrBack)
      AfxRedrawWindow(pCtrl->hWindow)

   end select
   
   function = 0
end function


' ========================================================================================
' Apply properties to the PictureBox
' ========================================================================================
private function PictureBox_ApplyProperties( byval pDoc as clsDocument ptr, _
                                             byval pCtrl as clsControl ptr, _
                                             byval pProp as clsProperty ptr _ 
                                             ) as Long
    
   Dim pWindow As CWindow Ptr = AfxCWindowPtr(pDoc->hWndForm)

   dim as long nPropValue
   dim as CWSTR wszPropName, wszPropValue

   wszPropName  = pProp->wszPropName
   wszPropValue = pProp->wszPropValue
   nPropValue   = Val(pProp->wszPropValue)
   
   select CASE ucase(wszPropName)
      
   case "IMAGE"
      dim pImageType as IMAGES_TYPE ptr = GetImagesTypePtr(wszPropValue)
      if pImageType then 
         pCtrl->AfxPicturePtr->LoadImageFromFile( pImageType->wszFilename )
      else
         pCtrl->AfxPicturePtr->Clear
      end if

   case "IMAGEWIDTH"
      if nPropValue > 0 then
         pCtrl->AfxPicturePtr->SetImageWidth( nPropValue )
      end if
      
   case "IMAGEHEIGHT"
      if nPropValue > 0 then
         pCtrl->AfxPicturePtr->SetImageHeight( nPropValue )
      end if
         
   case "IMAGESCALING"
      select case **wszPropValue
         case "ImageScale.None"
            pCtrl->AfxPicturePtr->SetImageAdjustment( GDIP_IMAGECTX_ACTUALSIZE, true )
         case "ImageScale.AutoSize"
            pCtrl->AfxPicturePtr->SetImageAdjustment( GDIP_IMAGECTX_AUTOSIZE, true )
         case "ImageScale.FitWidth"   
            pCtrl->AfxPicturePtr->SetImageAdjustment( GDIP_IMAGECTX_FITTOWIDTH, true )
         case "ImageScale.FitHeight"   
            pCtrl->AfxPicturePtr->SetImageAdjustment( GDIP_IMAGECTX_FITTOHEIGHT, true )
         case "ImageScale.Stretch"
            pCtrl->AfxPicturePtr->SetImageAdjustment( GDIP_IMAGECTX_STRETCH, true )
      end select        

   case "BACKCOLOR"
      pCtrl->AfxPicturePtr->SetBkColor( GetRGBColorFromProperty(pProp), true )

   case "BACKCOLOR"
      pCtrl->AfxPicturePtr->SetBkColorHot( GetRGBColorFromProperty(pProp), true )

   end select
   
   function = 0
end function


' ========================================================================================
' Apply properties to the incoming control
' ========================================================================================
public function ApplyControlProperties( byval pDoc as clsDocument ptr, _
                                        byval pCtrl as clsControl ptr _
                                        ) as long

   if pDoc = 0 then exit function
   if pCtrl = 0 then exit function
   
   Dim pWindow As CWindow Ptr = AfxCWindowPtr(pDoc->hWndForm)
   dim pProp as clsProperty ptr
   
   dim as long lb = lbound(pCtrl->Properties)
   dim as long ub = ubound(pCtrl->Properties)
   
   dim as long nPropValue, nTemp, nLeft, nTop, nWidth, nHeight
   dim as CWSTR wszPropName, wszPropValue
   
   ' Loop through all properties and apply them
   for i as long = lb to ub
      pProp = @pCtrl->Properties(i)
      if pProp = 0 then continue for
      
      wszPropName  = pProp->wszPropName
      wszPropValue = pProp->wszPropValue
      nPropValue   = Val(pProp->wszPropValue)
      
      select CASE ucase(wszPropName)
         case "NAME"
            if pCtrl->ControlType = CTRL_LISTBOX then
               ListBox_ResetContent(pCtrl->hWindow)
               ListBox_AddString(pCtrl->hWindow, wszPropValue)
            END IF
         CASE "LEFT"
            nLeft = nPropValue
            if pCtrl->SuspendLayout = false THEN
               nTemp = val(GetControlProperty(pCtrl, "TOP"))
               if pCtrl->ControlType = CTRL_FORM then
                  nLeft = 10: nTemp = 10
               end if
               pWindow->SetWindowPos(pCtrl->hWindow, 0, nLeft, nTemp, 0, 0, SWP_NOZORDER or SWP_NOSIZE)
            end if   
         CASE "TOP"
            nTop = nPropValue
            if pCtrl->SuspendLayout = false THEN
               nTemp = val(GetControlProperty(pCtrl, "LEFT"))
               if pCtrl->ControlType = CTRL_FORM then
                  nTop = 10: nTemp = 10
               end if
               pWindow->SetWindowPos(pCtrl->hWindow, 0, nTemp, nTop, 0, 0, SWP_NOZORDER or SWP_NOSIZE)
            end if   
         CASE "WIDTH"
            nWidth = nPropValue
            if pCtrl->SuspendLayout = false THEN
               nTemp = val(GetControlProperty(pCtrl, "HEIGHT"))
               pWindow->SetWindowPos(pCtrl->hWindow, 0, 0, 0, nWidth, nTemp, SWP_NOZORDER or SWP_NOMOVE)
            end if   
         CASE "HEIGHT"      
            nHeight = nPropValue
            if pCtrl->SuspendLayout = false THEN
               nTemp = val(GetControlProperty(pCtrl, "WIDTH"))
               pWindow->SetWindowPos(pCtrl->hWindow, 0, 0, 0, nTemp, nHeight, SWP_NOZORDER or SWP_NOMOVE)
            end if 
         case "TEXT"
            if pCtrl->ControlType <> CTRL_MASKEDEDIT then
               AfxSetWindowText(pCtrl->hWindow, wszPropValue)     
            end if   
         case "FONT"
            dim as HFONT hFontOld = AfxGetWindowFont(pCtrl->hWindow)
            dim as LOGFONT lf
            lf = SetLogFontFromPropValue(wszPropValue)
            dim as HFONT hFont = CreateFontIndirect(@lf)
            AfxSetWindowFont(pCtrl->hWindow, hFont, true)
            DeleteFont(hFontOld)
      END SELECT
      
   
      ' Handle control specific properties
      ' Only act on properties where the value has changed.
      if pProp->wszPropValue = pProp->wszPropValuePrev then continue for
      select CASE pCtrl->ControlType
         case CTRL_FORM:       Form_ApplyProperties(pDoc, pCtrl, pProp)
         case CTRL_BUTTON:     Button_ApplyProperties(pDoc, pCtrl, pProp)
         case CTRL_LABEL:      Label_ApplyProperties(pDoc, pCtrl, pProp)
         case CTRL_CHECKBOX:   CheckBox_ApplyProperties(pDoc, pCtrl, pProp)      
         case CTRL_OPTION:     OptionButton_ApplyProperties(pDoc, pCtrl, pProp)      
         case CTRL_TEXTBOX:    TextBox_ApplyProperties(pDoc, pCtrl, pProp)      
         case CTRL_MASKEDEDIT: MaskedEdit_ApplyProperties(pDoc, pCtrl, pProp)      
         case CTRL_LISTBOX:    ListBox_ApplyProperties(pDoc, pCtrl, pProp)      
         case CTRL_COMBOBOX:   ComboBox_ApplyProperties(pDoc, pCtrl, pProp)      
         case CTRL_FRAME:      Frame_ApplyProperties(pDoc, pCtrl, pProp)
         case CTRL_PICTUREBOX: PictureBox_ApplyProperties(pDoc, pCtrl, pProp)
         CASE ELSE
      END SELECT

   next

   ' If layout has been suspended then only move/resize the control after
   ' all of the relevant properties have now been set.
   if pCtrl->SuspendLayout THEN
      pWindow->SetWindowPos( pCtrl->hWindow, 0, nLeft, nTop, nWidth, nHeight, SWP_NOZORDER)
   END IF
   
   ' Repaint to ensure that the grab handles draw
   AfxRedrawWindow(pDoc->hWndFrame)
   AfxRedrawWindow(pDoc->hWndForm)
   AfxRedrawNonClientArea(pDoc->hWndForm) 
   
   function = 0

end function

