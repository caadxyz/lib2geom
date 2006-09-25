SET(2GEOM_DEPENDS gtk+-2.0 cairo gsl blas)
include(UsePkgConfig)

# Dependencies Packages
IF(UNIX)
    IF(APPLE)
    message(STATUS "Apple depends not added yet PLEASE HELP.")
    ELSE(APPLE)
        FOREACH(dep ${2GEOM_DEPENDS})
            PKGCONFIG_FOUND(${dep} "${dep}_FOUND")
            PKGCONFIG(${dep} "${dep}_INCLUDE_DIR" "${dep}_LINK_DIR" "${dep}_LINK_FLAGS" "${dep}_CFLAGS")
        ENDFOREACH(dep)
        # This is a hack due to the Cmake vars system,temp fix until I figure it out //verbalshadow
        PKGCONFIG(gtk+-2.0 GTK2_INCLUDE_DIR GTK2_LINK_DIR GTK2_LINK_FLAGS GTK2_CFLAGS)
    ENDIF(APPLE)
ELSE(UNIX)
    IF(WIN32)
        SET(GTK2_INCLUDE_DIR c:/gtk28/include)
        SET(GTK2_LINK_FLAGS "-lgtk-win32-2.0 -lgdk-win32-2.0 -latk-1.0 -lgdk_pixbuf-2.0 -lpangowin32-1.0 -lgdi32 -lpangocairo-1.0 -lfontconfig -lfreetype -lpango-1.0 -lm -lcairo -lgobject-2.0 -lgmodule-2.0 -lglib-2.0 -lintl -liconv -lgsl -lgslcblas")
        SET(GTK2_CFLAGS "-Ic:/gtk28/include/gtk-2.0 -Ic:/gtk28/lib/gtk-2.0/include -Ic:/gtk28/include/atk-1.0 -Ic:/gtk28/include/cairo -Ic:/gtk28/include/pango-1.0 -Ic:/gtk28/include/glib-2.0 -Ic:/gtk28/lib/glib-2.0/include -Ic:/gtk28/include -Lc:/gtk28/lib")
        SET(GTK2_LINK_DIR c:/gtk28/lib)
        SET(gtk+-2.0_FOUND "TRUE")
        SET(cairo_FOUND "TRUE")
    ENDIF(WIN32)
ENDIF(UNIX)
# end Dependencies

FOREACH(need ${2GEOM_DEPENDS})
    IF("${need}_FOUND")
        #IF(WIN32)
        #    message(STATUS "${need} Includes, Compile, and Link Flags: HARDCODED")
        #ELSEIF(UNIX)
            message(STATUS "${need} Includes, Compile, and Link Flags: FOUND")
        ENDIF(WIN32)
    ELSE("${need}_FOUND")
        message(STATUS "${need} Includes, Compile, and Link Flags: NOT FOUND")
ENDIF("${need}_FOUND")
ENDFOREACH(need)

INCLUDE (CheckIncludeFiles)
# usage: CHECK_INCLUDE_FILES (<header> <RESULT_VARIABLE> )

#CHECK_INCLUDE_FILES (malloc.h HAVE_MALLOC_H)
#CHECK_INCLUDE_FILES ("sys/param.h;sys/mount.h" HAVE_SYS_MOUNT_H)
#CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h)
