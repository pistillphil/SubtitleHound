/*****************************************************************
SubtitleHound
Copyright (C) 2014  pistillphil

This file is part of SubtitleHound.

SubtitleHound is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

SubtitleHound is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with SubtitleHound.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************/

#include "wx_pch.h"
#include "SubtitleHoundApp.h"

//(*AppHeaders
#include "SubtitleHoundMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(SubtitleHoundApp);

bool SubtitleHoundApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	SubtitleHoundFrame* Frame = new SubtitleHoundFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
