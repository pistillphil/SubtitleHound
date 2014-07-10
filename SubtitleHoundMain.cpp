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
#include "SubtitleHoundMain.h"
#include <wx/msgdlg.h>
#include <wx/wfstream.h>
#include <wx/log.h>
#include "MD5.h"
#include <fstream>
#include "curl/curl.h"
#include <cstdio>


// The first and last 64KB of the file are read and digested
#define DATASIZE (64 * 1024)

//(*InternalHeaders(SubtitleHoundFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(SubtitleHoundFrame)
const long SubtitleHoundFrame::ID_BUTTON1 = wxNewId();
const long SubtitleHoundFrame::ID_CHECKLISTBOX1 = wxNewId();
const long SubtitleHoundFrame::ID_BUTTON2 = wxNewId();
const long SubtitleHoundFrame::idMenuGithub = wxNewId();
const long SubtitleHoundFrame::idMenuQuit = wxNewId();
const long SubtitleHoundFrame::idMenuAbout = wxNewId();
const long SubtitleHoundFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SubtitleHoundFrame,wxFrame)
    //(*EventTable(SubtitleHoundFrame)
    //*)
END_EVENT_TABLE()

SubtitleHoundFrame::SubtitleHoundFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(SubtitleHoundFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxFlexGridSizer* FlexGridSizer1;
    wxMenu* Menu2;

    Create(parent, id, _("Subtitle Hound"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX|wxMINIMIZE_BOX|wxCLIP_CHILDREN, _T("id"));
    FlexGridSizer1 = new wxFlexGridSizer(3, 1, 0, 0);
    btn_addVideoFiles = new wxButton(this, ID_BUTTON1, _("Add Video Files"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    btn_addVideoFiles->SetToolTip(_("Add video files which subtitles should be downloaded for."));
    btn_addVideoFiles->SetHelpText(_("Add video files which subtitles should be downloaded for."));
    FlexGridSizer1->Add(btn_addVideoFiles, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lst_movieFiles = new wxCheckListBox(this, ID_CHECKLISTBOX1, wxDefaultPosition, wxSize(350,250), 0, 0, wxLB_HSCROLL, wxDefaultValidator, _T("ID_CHECKLISTBOX1"));
    FlexGridSizer1->Add(lst_movieFiles, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btn_downloadSubtitles = new wxButton(this, ID_BUTTON2, _("Download Subtitles"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    FlexGridSizer1->Add(btn_downloadSubtitles, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, idMenuGithub, _("View on Github\tAlt-G"), _("View Subtitle Hound on Github"), wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    fd_openFiles = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, _("Video Files|*.avi;*.mp4;*.mkv|All Files|*.*"), wxFD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    fd_openFiles = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, _("Video Files|*.avi;*.mp4;*.mkv|All Files|*.*"), wxFD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);
    Center();

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SubtitleHoundFrame::Onbtn_addVideoFiles);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SubtitleHoundFrame::Onbtn_downloadSubtitles);
    Connect(idMenuGithub,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SubtitleHoundFrame::OnGithub);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SubtitleHoundFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SubtitleHoundFrame::OnAbout);
    //*)
}

SubtitleHoundFrame::~SubtitleHoundFrame()
{
    //(*Destroy(SubtitleHoundFrame)
    //*)
}

void SubtitleHoundFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void SubtitleHoundFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(wxT("Version 0.1\nby pistillphil"),wxT("About Subtitle Hound"));
}

void SubtitleHoundFrame::Onbtn_addVideoFiles(wxCommandEvent& event)
{
    if (fd_openFiles->ShowModal() == wxID_CANCEL)
        return;

    wxFileInputStream input(fd_openFiles->GetPath());
    if (!input.IsOk())
    {
        wxLogError("The file '%s' could not be opened", fd_openFiles->GetPath());
        return;
    }
    else
    {
        lst_movieFiles->AppendAndEnsureVisible(fd_openFiles->GetPath());
        lst_movieFiles->Check(lst_movieFiles->GetCount() - 1);
    }
}

static size_t writeDownload(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void SubtitleHoundFrame::Onbtn_downloadSubtitles(wxCommandEvent& event)
{
    btn_downloadSubtitles->Disable();

    // For calculating the hash
    MD5 md5;
    char* data;

    // For accessing SubDB
    CURL* curl;
    CURLcode res;
    CURLcode statusCodeStatus;
    FILE* outputFile;

    // Counting all checked files
    unsigned counter = 0;

    for(unsigned i=0; i < lst_movieFiles->GetCount(); i++)
    {
        if(lst_movieFiles->IsChecked(i))
        {
            data = new char[DATASIZE * 2];
            wxString inputPath = lst_movieFiles->GetString(i);
            std::ifstream input;
            input.open(inputPath.c_str(), std::ios::binary);
            input.read((char*) data, DATASIZE);
            input.seekg(-DATASIZE ,std::ios::end);
            input.read((char*) (data + DATASIZE), DATASIZE);
            std::string result = md5.digestMemory(reinterpret_cast<BYTE*>(data) , DATASIZE * 2);
            //wxMessageBox(result); // For checking the hash

            delete[] data;
            data = 0;

            curl = curl_easy_init();
            if(curl)
            {
                outputFile = fopen((lst_movieFiles->GetString(i) + ".srt").c_str(),"wb");
                curl_easy_setopt(curl, CURLOPT_USERAGENT, "SubDB/1.0 (SubtitleHound/0.1; https://github.com/pistillphil/SubtitleHound)");
                //curl_easy_setopt(curl, CURLOPT_URL, "http://sandbox.thesubdb.com/?action=download&hash=edc1981d6459c6111fe36205b4aff6c2&language=en");    // Use this for testing purposes
                std::string subtitleRequest = "http://api.thesubdb.com/?action=download&hash=" + result + "&language=en,de";
                curl_easy_setopt(curl, CURLOPT_URL, subtitleRequest.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeDownload);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, outputFile);
                res = curl_easy_perform(curl);
                if(res != CURLE_OK)
                {
                    wxMessageBox(curl_easy_strerror(res), wxT("Download Error"));
                }
                else
                {
                    long statusCode = 0;
                    statusCodeStatus = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &statusCode);
                    if(statusCode == 404 && statusCodeStatus == CURLE_OK)
                    {
                        wxMessageBox(wxT("The Subtitle for " + lst_movieFiles->GetString(i) + " could not be found."), wxT("Subtitle Not Available"));
                    }
                    else
                    {
                        counter++;
                    }
                }
                fclose(outputFile);
                curl_easy_cleanup(curl);
            }
            else
            {
                wxMessageBox(wxT("Something went wrong with curl."), wxT("Error"));
                break;
            }

        }
    }
    wxString successMessage;
    if(counter == 0)
    {
        successMessage.Printf(wxT("No Subtitles have been downloaded."));
        wxMessageBox(successMessage, wxT("Warning"));
    }
    else
    {
        successMessage.Printf(wxT("The subtitle(s) for %u file(s) have been downloaded."), counter);
        wxMessageBox(successMessage, wxT("Download Successful"));
    }
    btn_downloadSubtitles->Enable();
}

void SubtitleHoundFrame::OnGithub(wxCommandEvent& event)
{
    wxMessageBox(wxT("Easy there, buddy. I'm merely a placeholder."), wxT("I can't do that, yet!"));
}
