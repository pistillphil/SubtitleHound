SubtitleHound
=========

SubtitleHound is a tool for finding and downloading subtitles for video files.

  - Add various video Files from various directories
  - Find and download subtitles for selected video files automatically
  - Works on Linux and Windows


Version
----

0.1 - Can download subtitles automatically, but is still pretty bare-bones.

Tech
-----------

SubtitleHound depends on various following projects:

* [SubDB] - a free subtitle database -> _Protocol_ _Version_ _1.0_
* [wxWidgets] - Cross-Platform GUI Library -> _Version_ _3.x.x_
* [libcurl] - the multiprotocol file transfer library -> _Version_ _7.37.x_

Installation
--------------

The installation can be performed using [CMake].  
As a small help the commands using a Unix Shell are shown below:
```sh
git clone https://github.com/pistillphil/SubtitleHound.git
mkdir SubtitleHound/build && cd SubtitleHound/build
cmake ..
make
```
After executing these commands the executable can be found in the `SubtitleHound/build` directory. It is also possible to prepare the build using the `cmake-gui`.

Author
------
pistillphil


License
----

**This application is licensed under the [GNU GPLv3](https://www.gnu.org/licenses/gpl-3.0.txt).**

[SubDB]:http://thesubdb.com/
[wxWidgets]:http://www.wxwidgets.org/
[libcurl]:http://curl.haxx.se/
[CMake]:http://www.cmake.org/
[git-repo-url]:https://github.com/pistillhil/SubtitleHound.git
