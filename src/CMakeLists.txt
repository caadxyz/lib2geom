add_subdirectory(2geom)
if(GTK4_FOUND)
  add_subdirectory(toys EXCLUDE_FROM_ALL)
else()
  message("Not building toys as they require GTK4.")
endif()

add_subdirectory(gtk101)
