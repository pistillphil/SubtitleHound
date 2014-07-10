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

#ifndef SUBTITLEHOUNDMAIN_H
#define SUBTITLEHOUNDMAIN_H

//(*Headers(SubtitleHoundFrame)
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/checklst.h>
#include <wx/filedlg.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

class SubtitleHoundFrame: public wxFrame
{
    public:

        SubtitleHoundFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~SubtitleHoundFrame();

    private:

        //(*Handlers(SubtitleHoundFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void Onbtn_addVideoFiles(wxCommandEvent& event);
        void Onbtn_downloadSubtitles(wxCommandEvent& event);
        void OnGithub(wxCommandEvent& event);
        //*)

        //(*Identifiers(SubtitleHoundFrame)
        static const long ID_BUTTON1;
        static const long ID_CHECKLISTBOX1;
        static const long ID_BUTTON2;
        static const long idMenuGithub;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(SubtitleHoundFrame)
        wxCheckListBox* lst_movieFiles;
        wxButton* btn_downloadSubtitles;
        wxFileDialog* fd_openFiles;
        wxMenuItem* MenuItem3;
        wxButton* btn_addVideoFiles;
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // SUBTITLEHOUNDMAIN_H
