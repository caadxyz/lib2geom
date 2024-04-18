# 2Geom: easy 2D graphics library

## gtk tutorial

* https://github.com/raspberry-cpp-tutorials/gtk-opencv-simple/wiki
* https://docs.gtk.org/gtk4/getting_started.html

## What is this?

2Geom is a C++ 2D geometry library geared towards robust processing of
computational geometry data associated with vector graphics. The primary
design consideration is ease of use and clarity. It is dual-licensed
under LGPL 2.1 and MPL 1.1.

The library is descended from a set of geometric routines present in
Inkscape, a vector graphics editor based around the Scalable Vector
Graphics format, the most widespread vector graphics interchange format
on the Web and a W3C Recommendation. Due to this legacy, not all parts
of the API form a coherent whole (yet).

Rendering is outside the scope of this library, and it is assumed
something like libcairo or similar is employed for this.  2geom
concentrates on higher level algorithms and geometric computations.


## Features List

* C++ 17
* Functional programming style.
* Points
* Efficient affine transformations
* Rectangles
* Convex Hulls
* Bounded error
* General purpose paths:
  + Exact elliptical arcs
  + Area
  + Centroid and bending moments
* Path Locations:
  + Determination of special spots (e.g. maximum curvature)
  + Splitting
  + Point, tangent, curvature at location
  + Efficient arc length and inverse arc length
* Path algebra:
  + Computations such as offset curves can be written with their mathematical definition
    and still get a bounded error, efficient curve. (preliminary trials indicate offset
    done this way out performs the method used in Inkscape)
* Arbitrary distortion (with bounded error):
  + Mesh distorts
  + Computational distorts such as the GIMP's 'vortex' plugin
  + 3d mapping (perspective, flag, sphere)
* Exact boolean ops (elliptic arcs remain elliptic arcs)
* Efficient 2d database
* Implicit function plotting
* NURBs input and output
* Tunable path simplification
* PDoF constraint system for CAD/CAGD


## Dependencies

To build 2Geom, you will need:

* C++ 17
* [Boost](http://www.boost.org/) (headers only)
* [glib](https://wiki.gnome.org/Projects/GLib)
* [GNU Scientific Library](http://www.gnu.org/software/gsl/)
* [double-conversion](https://github.com/google/double-conversion)
* [cairo](https://www.cairographics.org/)
* [Ragel](http://www.colm.net/open-source/ragel/) (if you want to modify the SVG path parser)
* [GTK+ 2](http://www.gtk.org/) (for demo programs)


## Building

2Geom uses CMake as the build and configuration system. To build, type:

    mkdir build && cd build
    cmake ..
    make

To run tests and performance tests:

    make test
    make perf
    
**Note**: Tests are disabled by default. To enable tests pass `-D2GEOM_TESTING=ON` to `cmake` command.  

Also check out some of the interactive programs in src/toys.

Documentation is generated from source comments using Doxygen.
Run `doxygen` in the project root to generate documentation in
`doc/html`.


## API / ABI Stability

Version 1.0 of 2Geom marks its first official release.  With this
release the library's API/ABI is considered stable:

 * All public APIs will not be renamed or have their parameters changed
   without providing backwards-compatible aliases.

 * New functionality added to these APIs will not change their meaning
   or fundamental behaviors.

 * If an API needs to be removed or replaced, it will be declared
   deprecated but will remain in the API until the next major version.
   Warnings will be issued when the deprecated method is called.

 * We'll only break backwards compatibility of these APIs if a bug or
   security hole makes it completely unavoidable.

Improvements that would break the API/ABI will be noted in our bug
tracker, for a future release.

2Geom does not follow Semantic Versioning. Instead, version numbers
match major Inkscape release versions.


## Further information

Communications related to 2Geom development happen on a
[SourceForge mailing list](https://lists.sourceforge.net/lists/listinfo/lib2geom-devel).

The primary user of 2Geom is [Inkscape](https://inkscape.org/en/).
API-breaking changes to 2Geom will require corresponding changes to
Inkscape.


================

http://devlib.symbian.slions.net/s3/GUID-7FD05006-09C1-4EF4-A2EB-AD98C2FA8866.html

## GLib Event Loop

The GLib event loop manages all the sources of an event available for GLib. These events can come from different kinds of sources like file descriptors (plain file descriptors, sockets, or pipes), time-outs, or any kind of source that can be added.

To allow multiple independent sets of events to be handled in different threads, each source is associated with a GMainContext.

Each event source is given a priority. The default priority is G_PRIORITY_DEFAULT and its value is 0. Values less than 0 denote higher priority and values greater than zero denote lower priority. The events from higher priority sources are processed earlier than events from lower priority sources.

The GMainLoop data type represents an event loop. GMainContext is a parameter to GMainLoop. If GMainContext is passed as NULL, then a main loop with the default context is created. After the sources are added to GMainContext and a GMainLoop variable is created, g_main_loop_run() is called. This checks continuously for events from its sources and dispatches them. Finally when all the events have been processed, g_main_loop_quit() must be called to return from g_main_loop_run().

**Note**: Sources are associated with

GMainContext and not with GMainLoop. Events from sources will be checked and dispatched from all the GMainLoop the GMainContext is associated with.

## Creating an event loop

GLib provides ready-made functions for adding the following sources either to the default context or to a custom context:

* time-outs
* I/O
* child watch

idle source (events from idle sources are ready if none of the other sources with priority > G_PRIORITY_DEFAULT are ready)

The following example code demonstrates the way to add a time-out source to the default context. The program makes 10 calls to timeout_callback(), which at the 10th call, calls g_main_loop_quit to make the main loop return.

```c++
#include <glib.h>
gboolean timeout_callback(gpointer data)
{
    static int i = 0;
    
    i++;
    g_print("timeout_callback called %d times\n", i);
    if (10 == i)
    {
        g_main_loop_quit( (GMainLoop*)data );
        return FALSE;
    }

    return TRUE;
}

int main()
{
    GMainLoop *loop;

    loop = g_main_loop_new ( NULL , FALSE );

    // add source to default context
    g_timeout_add (100 , timeout_callback , loop); 
    g_main_loop_run (loop);
    g_main_loop_unref(loop);

    return 0;
}
The following code demonstrates the method to add the time-out source to a different context than the default context:

#include <glib.h>
gboolean timeout_callback(gpointer data)
{
    static int i = 0;
    
    i++;
    g_print("timeout_callback called %d times\n",i);
    
    if(10 == i)
    {
        g_main_loop_quit((GMainLoop*)data);
        return FALSE;
    }
	
    return TRUE;
}

int main()
{
    GMainLoop *loop = NULL;
    GMainContext *context;
    GSource *source;
    int id;
		
    //create a new time-out source
    source = g_timeout_source_new(10);

    //create a context
    context = g_main_context_new();

    //attach source to context
    id = g_source_attach(source,context);
 
    //create a main loop with context
    loop = g_main_loop_new(context,FALSE);
	
    //set the callback for this source
    g_source_set_callback (source,timeout_callback,loop,NULL);
	
    g_main_loop_run (loop);
    
    g_main_loop_unref (loop);
     
    return 0;
}
```

The same process can be used for other default sources like child watch, I/O, and idle source since they are GLib APIs that allow the creation of a source directly.

## Creating a new source

The previous section applies only to four types of sources ( time-outs, I/O, child watch, and idle source ), for which GLib provides ready-made functions. The program below demonstrates the creation of a new source.

```c++
#include <glib.h>
gboolean callback(gpointer data)
{
    static int i = 0;
    i++;
    g_print ("timeout_callback called %d times\n",i);
    if (10 == i)
    {
        g_main_loop_quit((GMainLoop*)data);
        return FALSE;
    }

    return TRUE;
}

gboolean prepare(GSource *source,gint *timeout_)
{
    *timeout_ = -1;
    return TRUE;
}

gboolean check(GSource *source)
{
    return TRUE;
}

gboolean dispatch(GSource *source,GSourceFunc callback,gpointer user_data)
{
    if (callback(user_data))
        return TRUE;
    else
        return FALSE;
}

int main()
{
    GMainLoop *loop = NULL;
    GMainContext *context;
    GSource *source;
    int id;
	
    //create a variable of type GSourceFuncs
    GSourceFuncs SourceFuncs =
    {
        prepare,
        check,
        dispatch,
        NULL
    };
	
    //create a new source
    source = g_source_new (&SourceFuncs, sizeof(GSource));
	
    //create a context
    context = g_main_context_new ();
	
    //attach source to context
    id = g_source_attach (source,context);
	
    //create a main loop with context
    loop = g_main_loop_new (context,FALSE);
 
    //set the callback for this source
    g_source_set_callback (source,callback,loop,NULL);
	
    g_main_loop_run (loop);
    g_main_loop_unref (loop);
	
    return 0;
}
```

The creation of a new source requires us to define at least 3 functions:

* `prepare()`: Called before all the file descriptors are polled. If the source can determine that it is ready here (without waiting for the results of the poll() call), it should return TRUE. It can also return a time-out value which should be the maximum time-out (in milliseconds) which should be passed to the poll() call. The actual time-out used will be -1 if all sources returned -1, or it will be the minimum of all the timeout_values returned which were >= 0
* `check()`: Called after all the file descriptors are polled. The source should return TRUE if it is ready to be dispatched.
**Note**: Time may have passed since the previous prepare function was called, so the source should be checked again.
* `dispatch()` Called to dispatch the event source after it has returned TRUE in either its prepare or check function. The dispatch function is passed in a callback function and data. The callback function may be NULL if the source was never connected to a callback using g_source_set_callback(). The dispatch function should call the callback function with user_data and the additional parameters that are needed for this type of event source.

## Customizing the main loop iteration

Single iteration of GMainContext can be run in g_main_context_iteration (). When a more detailed control of how the main loop runs is desired call the component function of g_main_context iteration() directly.

The component functions of g_main_context iteration() are listed below:

* `g_main_context_prepare()`
* `g_main_context_query()`
* `g_main_context_check()`

Last updated December 31st, 2009

© Nokia 2011.