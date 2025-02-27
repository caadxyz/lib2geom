SET(2GEOM_TOY-FRAMEWORK-2_SRC
toy-framework-2.cpp
${2GEOM_INCLUDE_DIR}/toys/toy-framework-2.h
path-cairo.cpp
${2GEOM_INCLUDE_DIR}/toys/path-cairo.h
)
SET(2GEOM_LPE_TOY_FRAMEWORK_SRC
${2GEOM_TOY-FRAMEWORK-2_SRC}
lpe-framework.cpp
${2GEOM_INCLUDE_DIR}/toys/lpe-framework.h
)

SET(2GEOM_TOYS-2_SRC
2dsb2d
#aa
arc-bez
arc-length-param
auto-cross
boolops-toy
bound-path
bounds-test
box3d
center-warp
circle-fitting
circle-intersect
circle-line-intersect
circle-tangent-fitting
collinear-normal
conic-3
conic-4
conic-5
conic-6
conic-section-toy
convole
curvature-curve
curvature-test
curve-curve-distance
curve-curve-nearest-time
curve-intersection-by-bezier-clipping
curve-intersection-by-implicitization
cylinder3d
d2sbasis-fitting
d2sbasis-fitting-with-np
draw-toy
ellipse-area-minimizer
ellipse-bezier-intersect-toy
ellipse-fitting
ellipse-intersect-toy
ellipse-line-intersect-toy
elliptiarc-3point-center-fitting
elliptiarc-curve-fitting
elliptical-arc-toy
evolute
filet-minion
find-derivative
gear
#hatches
#implicit-toy
#ineaa
inner-product-clip
intersect-data
inverse-test
kinematic_templates
levelsets-test
line-toy
load-svgd
match-curve
mesh-grad
metro
minsb2d-solver
#normal-bundle
offset-toy
pair-intersect
paptest
parametrics
parser
path-along-path
path-effects
pencil
pencil-2
plane3d
point-curve-nearest-time
portion-test
precise-flat
pw-compose-test
pw-funcs
pw-toy
rdm-area
rect_01
rect_02
rect_03
rect-toy
root-finder-comparer
#rtree-toy
sanitize
# sb1d
sb2d
sb2d-solver
sbasisdim
sbasis-fitting
sb-math-test
sb-of-interval
sb-of-sb
sb-to-bez
sb-zeros
scribble
self-intersect
sketch-fitter
smash-intersector
squiggles
sweep
sweeper-toy
# these ones have only had a trivial rewrite to toy-2
#uncross
winding-test
worms
toy-template
)

SET(2GEOM_LPE_TOYS_SRC
lpe-test
)

OPTION(2GEOM_TOYS_LPE
  "Build Inkscape Live Path Effect (LPE) Toy files"
  ON)

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

IF(2GEOM_TOYS_LPE)
    # make lib for lpetoy
    add_library(lpetoy ${LIB_TYPE} ${2GEOM_LPE_TOY_FRAMEWORK_SRC})
    target_include_directories(lpetoy PUBLIC ${GTK4_INCLUDE_DIRS})
    target_link_libraries(lpetoy
        ${GTK4_LIBRARIES}
        2Geom::2geom
        )
    if(NOT WIN32 AND NOT APPLE)
    	target_link_libraries(lpetoy -lrt)
    endif()

    FOREACH(source ${2GEOM_LPE_TOYS_SRC})
        add_executable(${source} ${source}.cpp)
        target_link_libraries(${source} lpetoy 2Geom::2geom)
    ENDFOREACH(source)

ENDIF(2GEOM_TOYS_LPE)

OPTION(2GEOM_TOYS
  "Build the projects Toy files"
  ON)
IF(2GEOM_TOYS)
 
    # make lib for toy
    ADD_LIBRARY(toy-2 ${LIB_TYPE} ${2GEOM_TOY-FRAMEWORK-2_SRC})
    target_include_directories(toy-2 PUBLIC ${GTK4_INCLUDE_DIRS})
    TARGET_LINK_LIBRARIES(toy-2 2Geom::2geom ${GTK4_LIBRARIES})
    if(NOT WIN32 AND NOT APPLE)
    	target_link_libraries(toy-2 -lrt)
    endif()

    FOREACH(source ${2GEOM_TOYS-2_SRC})
           IF(${source} STREQUAL aa)
            ADD_EXECUTABLE(${source} EXCLUDE_FROM_ALL ${source}.cpp)
            TARGET_LINK_LIBRARIES(${source} affa)
        ELSEIF(${source} STREQUAL ineaa)
            ADD_EXECUTABLE(${source} EXCLUDE_FROM_ALL ${source}.cpp)
            TARGET_LINK_LIBRARIES(${source} affa)
        ELSEIF(${source} STREQUAL implicit-toy)
            ADD_EXECUTABLE(${source} EXCLUDE_FROM_ALL ${source}.cpp)
            TARGET_LINK_LIBRARIES(${source} affa)
		ELSEIF(${source} STREQUAL boolops-cgal)
			
        ELSE(${source} STREQUAL aa)
            ADD_EXECUTABLE(${source} ${source}.cpp)
        ENDIF(${source} STREQUAL aa)
        TARGET_LINK_LIBRARIES(${source} toy-2  2Geom::2geom ${GTK4_LIBRARIES})
    ENDFOREACH(source)
ENDIF(2GEOM_TOYS)

