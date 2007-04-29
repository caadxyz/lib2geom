#include "s-basis.h"
#include "bezier-to-sbasis.h"
#include "sbasis-to-bezier.h"
#include "d2.h"
#include "s-basis-2d.h"

#include "path-cairo.h"

#include <iterator>

#include "toy-framework.h"

#include "basic-intersection.h"

using std::vector;
const unsigned bez_ord = 10;
using namespace Geom;

class SelfIntersect: public Toy {
virtual void draw(cairo_t *cr, std::ostringstream *notify, int width, int height, bool save) {
    cairo_set_line_width (cr, 0.5);
    cairo_set_source_rgba (cr, 0., 0., 0, 1);
    
    D2<SBasis> A = handles_to_sbasis<bez_ord-1>(handles.begin());
    Rect Ar = A.boundsLocal(0, 1);
    cairo_md_sb(cr, A);
    cairo_stroke(cr);

    std::vector<std::pair<double, double> >  all_si = 
        find_self_intersections(A);
    
    cairo_stroke(cr);
    cairo_set_source_rgba (cr, 1., 0., 1, 1);
    for(int i = 0; i < all_si.size(); i++) {
        draw_handle(cr, A(all_si[i].first));
    }
    cairo_stroke(cr);
    
    *notify << "total intersections: " << all_si.size();

    Toy::draw(cr, notify, width, height, save);
}
public:
SelfIntersect () {
    for(unsigned i = 0; i < bez_ord; i++)
        handles.push_back(Geom::Point(uniform()*400, uniform()*400));
}
};

int main(int argc, char **argv) {   
    init(argc, argv, "Self Intersect", new SelfIntersect());

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
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:encoding=utf-8:textwidth=99 :
