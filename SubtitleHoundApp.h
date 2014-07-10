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

#ifndef SUBTITLEHOUNDAPP_H
#define SUBTITLEHOUNDAPP_H

#include <wx/app.h>

class SubtitleHoundApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // SUBTITLEHOUNDAPP_H
