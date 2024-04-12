
find_package(GTest REQUIRED MODULE)
# Use this variable for tests which provide their own main().
SET(2GEOM_TESTS_SRC
#bezier-utils-test
#lin_alg_test
sbasis-text-test
root-find-test
implicitization-test
#timing-test
#rtree-performance-test
)

# Use this variable for GTest tests which should have a default main().
SET(2GEOM_GTESTS_SRC
affine-test
angle-test
bezier-test
choose-test
circle-test
convex-hull-test
coord-test
ellipse-test
elliptical-arc-test
intersection-graph-test
interval-test
line-test
min-bbox-test
nl-vector-test
parallelogram-test
path-test
planar-graph-test
point-test
polynomial-test
rect-test
sbasis-test
self-intersections-test
)

foreach(source ${2GEOM_GTESTS_SRC})

    if(APPLE)
       link_directories("/opt/homebrew/opt/gsl/lib")
       link_directories("/opt/homebrew/opt/gtk4/lib")
       link_directories("/opt/homebrew/opt/pango/lib")
       link_directories("/opt/homebrew/opt/harfbuzz/lib")
       link_directories("/opt/homebrew/opt/gdk-pixbuf/lib")
       link_directories("/opt/homebrew/opt/cairo/lib")
       link_directories("/opt/homebrew/opt/graphene/lib")
       link_directories("/opt/homebrew/opt/glib/lib")
       link_directories("/opt/homebrew/opt/gettext/lib")
    endif()

	add_executable(${source} ${source}.cpp)
	target_include_directories(${source} PRIVATE ${GSL_INCLUDE_DIRS} ${GTK4_INCLUDE_DIRS})
	target_link_libraries(${source} 2geom GTest::Main ${GSL_LIBRARIES} ${GTK4_LIBRARIES})
	add_test(NAME ${source} COMMAND ${source})
endforeach()

foreach(source ${2GEOM_TESTS_SRC})
    if(APPLE)
        link_directories("/opt/homebrew/opt/gsl/lib")
        link_directories("/opt/homebrew/opt/gtk4/lib")
        link_directories("/opt/homebrew/opt/pango/lib")
        link_directories("/opt/homebrew/opt/harfbuzz/lib")
        link_directories("/opt/homebrew/opt/gdk-pixbuf/lib")
        link_directories("/opt/homebrew/opt/cairo/lib")
        link_directories("/opt/homebrew/opt/graphene/lib")
        link_directories("/opt/homebrew/opt/glib/lib")
        link_directories("/opt/homebrew/opt/gettext/lib")
    endif()
    add_executable(${source} ${source}.cpp)
    target_include_directories(${source} PRIVATE ${GSL_INCLUDE_DIRS} ${GTK4_INCLUDE_DIRS})
    target_link_libraries(${source} 2geom GTest::GTest ${GSL_LIBRARIES} ${GTK4_LIBRARIES})
    add_test(NAME ${source} COMMAND ${source})
endforeach(source)

if(WIN32 AND 2GEOM_BUILD_SHARED)
    add_custom_target(copy ALL COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/src/2geom/lib2geom.dll ${CMAKE_BINARY_DIR}/tests/lib2geom.dll)
    add_dependencies(copy 2geom)
endif()
