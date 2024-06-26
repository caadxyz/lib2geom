# (re-)generate parser file with ragel if it's available
SET(SVG_PARSER_CPP "svg-path-parser.cpp")
SET(SVG_PARSER_RL  "svg-path-parser.rl")

find_program(RAGEL_PROGRAM
   NAMES ragel
   HINTS /usr/bin
         /usr/local/bin
)
if(RAGEL_PROGRAM)
    message(STATUS "Found Ragel in ${RAGEL_PROGRAM}. ${SVG_PARSER_CPP} will be recreated from ${SVG_PARSER_RL}.")
    add_custom_command(OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/${SVG_PARSER_CPP}"
                       COMMAND ${RAGEL_PROGRAM} -o "${SVG_PARSER_CPP}" "${SVG_PARSER_RL}"
                       DEPENDS "${SVG_PARSER_RL}"
                       WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                       COMMENT "Generating ${SVG_PARSER_CPP} with ragel")
else()
    message(STATUS "Ragel NOT found. Using stale ${SVG_PARSER_CPP}.")
endif()

add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${SVG_PARSER_CPP}"
                   COMMAND "${CMAKE_COMMAND}"
                       "-DSOURCE=${CMAKE_CURRENT_SOURCE_DIR}/${SVG_PARSER_CPP}"
                       "-DTARGET=${CMAKE_CURRENT_BINARY_DIR}/${SVG_PARSER_CPP}"
                       "-DSOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
                       -P "${CMAKE_MODULE_PATH}/RewriteLineMarkers.cmake"
                   DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${SVG_PARSER_CPP}"
                   COMMENT "Rewriting #line markers in ${SVG_PARSER_CPP}")

if(APPLE AND LIB_TYPE STREQUAL "SHARED" )
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

add_library(2geom ${LIB_TYPE}
    # sources
    affine.cpp

    basic-intersection.cpp
    bezier.cpp
    bezier-clipping.cpp
    bezier-curve.cpp
    bezier-utils.cpp

    cairo-path-sink.cpp
    circle.cpp
    concepts.cpp
    conicsec.cpp
    conic_section_clipper_impl.cpp
    convex-hull.cpp
    coord.cpp
    crossing.cpp
    curve.cpp

    d2-sbasis.cpp

    ellipse.cpp
    elliptical-arc.cpp
    elliptical-arc-from-sbasis.cpp

    geom.cpp

    intersection-graph.cpp

    line.cpp

    nearest-time.cpp

    numeric/matrix.cpp

    parallelogram.cpp
    parting-point.cpp
    path-extrema.cpp
    path-intersection.cpp
    path-sink.cpp
    path.cpp
    pathvector.cpp
    piecewise.cpp
    point.cpp
    polynomial.cpp

    rect.cpp
    recursive-bezier-intersection.cpp

    sbasis-2d.cpp
    sbasis-geometric.cpp
    sbasis-math.cpp
    sbasis-poly.cpp
    sbasis-roots.cpp
    sbasis-to-bezier.cpp
    sbasis.cpp
    self-intersect.cpp
    solve-bezier.cpp
    solve-bezier-one-d.cpp
    solve-bezier-parametric.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/${SVG_PARSER_CPP}
    svg-path-writer.cpp
    sweep-bounds.cpp

    transforms.cpp

    utils.cpp

    # headers (for IDE support only)
    # private:
    planar-graph.h

    # public:
    ${2GEOM_INCLUDE_DIR}/2geom/affine.h
    ${2GEOM_INCLUDE_DIR}/2geom/angle.h

    ${2GEOM_INCLUDE_DIR}/2geom/basic-intersection.h
    ${2GEOM_INCLUDE_DIR}/2geom/bezier.h
    ${2GEOM_INCLUDE_DIR}/2geom/bezier-curve.h
    ${2GEOM_INCLUDE_DIR}/2geom/bezier-to-sbasis.h
    ${2GEOM_INCLUDE_DIR}/2geom/bezier-utils.h

    ${2GEOM_INCLUDE_DIR}/2geom/cairo-path-sink.h
    ${2GEOM_INCLUDE_DIR}/2geom/choose.h
    ${2GEOM_INCLUDE_DIR}/2geom/circle.h
    ${2GEOM_INCLUDE_DIR}/2geom/concepts.h
    ${2GEOM_INCLUDE_DIR}/2geom/conicsec.h
    ${2GEOM_INCLUDE_DIR}/2geom/conic_section_clipper.h
    ${2GEOM_INCLUDE_DIR}/2geom/conic_section_clipper_cr.h
    ${2GEOM_INCLUDE_DIR}/2geom/conic_section_clipper_impl.h
    ${2GEOM_INCLUDE_DIR}/2geom/convex-hull.h
    ${2GEOM_INCLUDE_DIR}/2geom/coord.h
    ${2GEOM_INCLUDE_DIR}/2geom/crossing.h
    ${2GEOM_INCLUDE_DIR}/2geom/curve.h
    ${2GEOM_INCLUDE_DIR}/2geom/curves.h

    ${2GEOM_INCLUDE_DIR}/2geom/d2.h

    ${2GEOM_INCLUDE_DIR}/2geom/ellipse.h
    ${2GEOM_INCLUDE_DIR}/2geom/elliptical-arc.h
    ${2GEOM_INCLUDE_DIR}/2geom/exception.h

    ${2GEOM_INCLUDE_DIR}/2geom/forward.h

    ${2GEOM_INCLUDE_DIR}/2geom/geom.h

    ${2GEOM_INCLUDE_DIR}/2geom/intersection.h
    ${2GEOM_INCLUDE_DIR}/2geom/intersection-graph.h

    ${2GEOM_INCLUDE_DIR}/2geom/line.h
    ${2GEOM_INCLUDE_DIR}/2geom/linear.h

    ${2GEOM_INCLUDE_DIR}/2geom/math-utils.h

    ${2GEOM_INCLUDE_DIR}/2geom/nearest-time.h

    ${2GEOM_INCLUDE_DIR}/2geom/ord.h

    ${2GEOM_INCLUDE_DIR}/2geom/parallelogram.h
    ${2GEOM_INCLUDE_DIR}/2geom/path-intersection.h
    ${2GEOM_INCLUDE_DIR}/2geom/path-sink.h
    ${2GEOM_INCLUDE_DIR}/2geom/path.h
    ${2GEOM_INCLUDE_DIR}/2geom/pathvector.h
    ${2GEOM_INCLUDE_DIR}/2geom/piecewise.h
    ${2GEOM_INCLUDE_DIR}/2geom/point.h
    ${2GEOM_INCLUDE_DIR}/2geom/polynomial.h

    ${2GEOM_INCLUDE_DIR}/2geom/ray.h
    ${2GEOM_INCLUDE_DIR}/2geom/rect.h

    ${2GEOM_INCLUDE_DIR}/2geom/sbasis-2d.h
    ${2GEOM_INCLUDE_DIR}/2geom/sbasis-curve.h
    ${2GEOM_INCLUDE_DIR}/2geom/sbasis-geometric.h
    ${2GEOM_INCLUDE_DIR}/2geom/sbasis-math.h
    ${2GEOM_INCLUDE_DIR}/2geom/sbasis-poly.h
    ${2GEOM_INCLUDE_DIR}/2geom/sbasis-to-bezier.h
    ${2GEOM_INCLUDE_DIR}/2geom/sbasis.h
    ${2GEOM_INCLUDE_DIR}/2geom/solver.h
    ${2GEOM_INCLUDE_DIR}/2geom/svg-path-parser.h
    ${2GEOM_INCLUDE_DIR}/2geom/svg-path-writer.h
    ${2GEOM_INCLUDE_DIR}/2geom/sweeper.h
    ${2GEOM_INCLUDE_DIR}/2geom/sweep-bounds.h

    ${2GEOM_INCLUDE_DIR}/2geom/transforms.h

    ${2GEOM_INCLUDE_DIR}/2geom/utils.h
)

# make lib for 2geom
target_include_directories(2geom
    PUBLIC
        ${GLIB_INCLUDE_DIRS}
        ${GSL_INCLUDE_DIRS}
        ${CAIRO_INCLUDE_DIRS}
        ${DoubleConversion_INCLUDE_DIRS}
        $<BUILD_INTERFACE:${2GEOM_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${2GEOM_INCLUDE_DIR}/2geom>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/2geom-${2GEOM_VERSION}>
    )

target_link_libraries(2geom
    PUBLIC
        ${GLIB_LIBRARIES}
        ${GSL_LIBRARIES}
        ${CAIRO_LIBRARIES}
        ${DoubleConversion_LIBRARIES}
    )

set_target_properties(2geom PROPERTIES SOVERSION "${2GEOM_ABI_VERSION}")

install(TARGETS 2geom
    EXPORT 2geom_targets
    RUNTIME
      DESTINATION ${CMAKE_INSTALL_BINDIR}
      COMPONENT "lib2geom${2GEOM_VERSION}"
    LIBRARY
      DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT "lib2geom${2GEOM_VERSION}"
      NAMELINK_COMPONENT "lib2geom_dev"
    ARCHIVE
      DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT "lib2geom${2GEOM_VERSION}"
)

add_library(2Geom::2geom ALIAS 2geom)
