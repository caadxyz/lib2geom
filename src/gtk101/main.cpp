#include <cairo.h>
#include <gtk/gtk.h>
#include <glib/gtypes.h>

static int centerX = 200;
static int centerY = 200;
static int radius = 50;
static gboolean dragging = FALSE;
static GtkWidget *the_canvas=nullptr;

static void draw_callback(GtkDrawingArea *drawing_area, cairo_t *cr, int width, int height, gpointer user_data)
{
    cairo_set_source_rgb(cr, 0.0, 0.0, 1.0);  // Blue color for the circle
    cairo_arc(cr, centerX, centerY, radius, 0, 2 * G_PI);  // Draw the circle
    cairo_fill(cr);  // Fill the circle with the current color
}

static void mouse_press_event(GtkGestureClick *gesture, int n_press, double x, double y, gpointer user_data)
{
    double dx = x - centerX;
    double dy = y - centerY;
    if (dx * dx + dy * dy <= radius * radius) {
        dragging = TRUE;
    }
}

static void mouse_release_event(GtkGestureClick *gesture, gint n_press, gdouble x, gdouble y, gpointer user_data)
{
    dragging = FALSE; 
}

static void mouse_motion_event(GtkEventControllerMotion *controller, double x, double y, gpointer user_data)
{
    if (dragging) {
        centerX = x;  
        centerY = y; 
        gtk_widget_queue_draw(GTK_WIDGET(the_canvas)); 
    }
}


static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Gtk_Window");

    the_canvas = gtk_drawing_area_new();
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(the_canvas), draw_callback, NULL, NULL);

    auto click = gtk_gesture_click_new();
    gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(click), 0);
    g_signal_connect(click, "pressed", G_CALLBACK(mouse_press_event), nullptr);
    g_signal_connect(click, "released", G_CALLBACK(mouse_release_event), nullptr);
    gtk_widget_add_controller(the_canvas, GTK_EVENT_CONTROLLER(click));

    auto motion = gtk_event_controller_motion_new();
    g_signal_connect(motion, "motion", G_CALLBACK(mouse_motion_event), nullptr);
    gtk_widget_add_controller(the_canvas, motion);

    gtk_window_set_child(GTK_WINDOW(window), the_canvas);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv)
{

    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}