cmake_minimum_required (VERSION 3.0)
project (SubtitleHound CXX)

# For libcurl
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

# For wxWidgets
set(wxWidgets_ROOT_DIR C:/Libs/wxWidgets)
#set(wxWidgets_USE_MONOLITHIC TRUE)
if(WIN32)
	find_package(wxWidgets COMPONENTS mono REQUIRED)
else()
	find_package(wxWidgets COMPONENTS core base REQUIRED)
endif()
include(${wxWidgets_USE_FILE})

# Build
add_executable(SubtitleHound WIN32 SubtitleHoundMain.cpp SubtitleHoundApp.cpp)
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARY})