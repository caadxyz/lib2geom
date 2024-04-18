SET(GTK101_SRC
    main.cpp
)

if(APPLE AND LIB_TYPE STREQUAL "SHARED")
    link_directories("/opt/homebrew/opt/cairo/lib")
    link_directories("/opt/homebrew/opt/gsl/lib")
    link_directories("/opt/homebrew/opt/gtk4/lib")
    link_directories("/opt/homebrew/opt/pango/lib")
    link_directories("/opt/homebrew/opt/harfbuzz/lib")
    link_directories("/opt/homebrew/opt/gdk-pixbuf/lib")
    link_directories("/opt/homebrew/opt/graphene/lib")
    link_directories("/opt/homebrew/opt/glib/lib")
    link_directories("/opt/homebrew/opt/gettext/lib")
endif()

include_directories( ${GTK4_INCLUDE_DIRS})
ADD_EXECUTABLE(gtk101 ${GTK101_SRC})
TARGET_LINK_LIBRARIES(gtk101 ${GTK4_LIBRARIES})

