#include <2geom/sweep.h>

#include <2geom/toys/path-cairo.h>
#include <2geom/toys/toy-framework.h>

using namespace Geom;

class Sweep: public Toy {
    unsigned count_a, count_b;
    virtual void draw(cairo_t *cr, std::ostringstream *notify, int width, int height, bool save) {
        std::vector<Rect> rects_a, rects_b;

        for(unsigned i = 0; i < count_a; i++)
            rects_a.push_back(Rect(handles[i*2], handles[i*2+1]));

        for(unsigned i = 0; i < count_b; i++)
            rects_b.push_back(Rect(handles[i*2 + count_a*2], handles[i*2+1 + count_a*2]));
                
        std::vector<std::vector<unsigned> > res = sweep_bounds(rects_a, rects_b);
        cairo_set_line_width(cr,0.5);
        for(unsigned i = 0; i < res.size(); i++) {
            for(unsigned j = 0; j < res[i].size(); j++) {
                draw_line_seg(cr, rects_a[i].midpoint(), rects_b[res[i][j]].midpoint());
                cairo_stroke(cr);
            }
        }
        
        cairo_set_line_width(cr,3);
        cairo_set_source_rgba(cr,1,0,0,1);
        for(unsigned i = 0; i < count_a; i++)
            cairo_rectangle(cr, rects_a[i].left(), rects_a[i].top(), rects_a[i].width(), rects_a[i].height());
        cairo_stroke(cr);
        
        cairo_set_source_rgba(cr,0,0,1,1);
        for(unsigned i = 0; i < count_b; i++)
            cairo_rectangle(cr, rects_b[i].left(), rects_b[i].top(), rects_b[i].width(), rects_b[i].height());
        cairo_stroke(cr);
        
        Toy::draw(cr, notify, width, height, save);
    }
    bool should_draw_numbers() { return false; }
    public:
    Sweep () {
        count_a = 20;
        count_b = 10;
        for(unsigned i = 0; i < (count_a + count_b); i++) {
            Point dim(uniform() * 90 + 10, uniform() * 90 + 10),
                  pos(uniform() * 500 + 50, uniform() * 500 + 50);
            handles.push_back(pos - dim/2);
            handles.push_back(pos + dim/2);
        }
    }
};

int main(int argc, char **argv) {
    init(argc, argv, new Sweep());
    return 0;
}

/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=4:softtabstop=4:encoding=utf-8:textwidth=99 :
