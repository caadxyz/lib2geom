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

ADD_EXECUTABLE(gtk101 ${GTK101_SRC})
TARGET_INCLUDE_DIRECTORIES(
    gtk101
    PRIVATE
    ${GIO_INCLUDE_DIRS}
    ${GLIB_INCLUDE_DIRS}
    ${GTK4_INCLUDE_DIRS}
)
TARGET_LINK_LIBRARIES(
    gtk101 
    PRIVATE
    ${GLIB_LIBRARIES}
    ${GTK4_LIBRARIES})

