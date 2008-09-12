/*
 * Line Toy
 *
 * Copyright 2008  Marco Cecchetti <mrcekets at gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it either under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation
 * (the "LGPL") or, at your option, under the terms of the Mozilla
 * Public License Version 1.1 (the "MPL"). If you do not alter this
 * notice, a recipient may use your version of this file under either
 * the MPL or the LGPL.
 *
 * You should have received a copy of the LGPL along with this library
 * in the file COPYING-LGPL-2.1; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * You should have received a copy of the MPL along with this library
 * in the file COPYING-MPL-1.1
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY
 * OF ANY KIND, either express or implied. See the LGPL or the MPL for
 * the specific language governing rights and limitations.
 */


#include <2geom/line.h>
#include <2geom/toys/path-cairo.h>
#include <2geom/toys/toy-framework-2.h>

#include <2geom/angle.h>

#include <vector>
#include <string>

using namespace Geom;



std::string angle_formatter(double angle)
{
    return default_formatter(decimal_round(rad_to_deg(angle),2));
}



class LineToy : public Toy
{
    enum menu_item_t
    {
        SHOW_MENU = 0,
        TEST_CREATE,
        TEST_PROJECTION,
        TEST_ORTHO,
        TEST_DISTANCE,
        TEST_POSITION,
        TEST_SEG_BISEC,
        TEST_ANGLE_BISEC,
        TEST_COLLINEAR,
        TEST_INTERSECTIONS,
        TOTAL_ITEMS // this one must be the last item
    };

    enum handle_label_t
    {
    };

    enum toggle_label_t
    {
    };

    enum slider_label_t
    {
        ANGLE_SLIDER = 0,
    };

    static const char* menu_items[TOTAL_ITEMS];
    static const char keys[TOTAL_ITEMS];

    virtual void first_time(int /*argc*/, char** /*argv*/)
    {
        draw_f = &LineToy::draw_menu;
    }

    void init_common()
    {
        set_common_control_geometry = true;
        set_control_geometry = true;

        sliders.clear();
        toggles.clear();
        handles.clear();
    }


    virtual void draw_common( cairo_t *cr, std::ostringstream *notify,
                              int width, int height, bool /*save*/ )
    {
        init_common_ctrl_geom(cr, width, height, notify);
    }


    void init_create()
    {
        init_common();

        p1.pos = Point(400, 50);
        p2.pos = Point(450, 450);
        O.pos = Point(50, 400);

        sliders.push_back(Slider(0, 2*M_PI, 0, 0, "angle"));
        sliders[ANGLE_SLIDER].formatter(&angle_formatter);

        handles.push_back(&p1);
        handles.push_back(&p2);
        handles.push_back(&O);
        handles.push_back(&(sliders[ANGLE_SLIDER]));
    }

    void draw_create(cairo_t *cr, std::ostringstream *notify,
                      int width, int height, bool save)
    {
        draw_common(cr, notify, width, height, save);
        init_create_ctrl_geom(cr, notify, width, height);

        Line l1(p1.pos, p2.pos);
        Line l2(O.pos, sliders[ANGLE_SLIDER].value());

        cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 1.0);
        cairo_set_line_width(cr, 0.3);
        draw_line(cr, l1);
        draw_line(cr, l2);
        cairo_stroke(cr);

        draw_label(cr, p1, "P1");
        draw_label(cr, p2, "P2");
        draw_label(cr, O, "O");
        draw_label(cr, l1, "L(P1,P2)");
        draw_label(cr, l2, "L(O,angle)");
    }


    void init_projection()
    {
        init_common();
        p1.pos = Point(400, 50);
        p2.pos = Point(450, 450);
        p3.pos = Point(100, 250);
        p4.pos = Point(200, 450);
        O.pos = Point(50, 150);

        handles.push_back(&p1);
        handles.push_back(&p2);
        handles.push_back(&p3);
        handles.push_back(&p4);
        handles.push_back(&O);
    }

    void draw_projection(cairo_t *cr, std::ostringstream *notify,
                      int width, int height, bool save)
    {
        draw_common(cr, notify, width, height, save);

        Line l1(p1.pos, p2.pos);
        LineSegment ls(p3.pos, p4.pos);

        Point np = projection(O.pos, l1);
        LineSegment lsp = projection(ls, l1);

        cairo_set_source_rgba(cr, 0.3, 0.3, 0.3, 1.0);
        cairo_set_line_width(cr, 0.2);
        draw_line(cr, l1);
        draw_segment(cr, ls);
        cairo_stroke(cr);

        cairo_set_line_width(cr, 0.3);
        cairo_set_source_rgba(cr, 0.0, 0.0, 1.0, 1.0);
        draw_segment(cr, lsp);
        draw_handle(cr, lsp[0]);
        draw_handle(cr, lsp[1]);
        cairo_stroke(cr);

        cairo_set_source_rgba(cr, 0.8, 0.0, 0.0, 1.0);
        draw_circ(cr, np);
        cairo_stroke(cr);

        cairo_set_source_rgba(cr, 0.5, 0.5, 0.5, 1.0);
        draw_label(cr, p1, "P1");
        draw_label(cr, p2, "P2");
        draw_label(cr, ls, "S");
        draw_label(cr, lsp, "prj(S)");
        draw_label(cr, O, "P");
        draw_text(cr, np, "prj(P)");

        cairo_stroke(cr);
    }


    void init_ortho()
    {
        init_common();
        p1.pos = Point(400, 50);
        p2.pos = Point(450, 450);
        p3.pos = Point(100, 50);
        p4.pos = Point(150, 450);

        handles.push_back(&p1);
        handles.push_back(&p2);
        handles.push_back(&p3);
        handles.push_back(&p4);
    }

    void draw_ortho(cairo_t *cr, std::ostringstream *notify,
                      int width, int height, bool save)
    {
        draw_common(cr, notify, width, height, save);

        Line l1(p1.pos, p2.pos);
        Line l2 = make_orthogonal_line(p3.pos, l1);
        Line l3 = make_parallel_line(p4.pos, l1);

        cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 1.0);
        cairo_set_line_width(cr, 0.3);
        draw_line(cr, l1);
        draw_line(cr, l2);
        draw_line(cr, l3);
        cairo_stroke(cr);

        draw_label(cr, p1, "P1");
        draw_label(cr, p2, "P2");
        draw_label(cr, p3, "O1");
        draw_label(cr, p4, "O2");

        draw_label(cr, l1, "L");
        draw_label(cr, l2, "L1 _|_ L");
        draw_label(cr, l3, "L2 // L");

    }


    void init_distance()
    {
        init_common();
        p1.pos = Point(400, 50);
        p2.pos = Point(450, 450);
        p3.pos = Point(100, 250);
        p4.pos = Point(200, 450);
        p5.pos = Point(50, 150);
        p6.pos = Point(480, 60);
        O.pos = Point(300, 300);

        handles.push_back(&p1);
        handles.push_back(&p2);
        handles.push_back(&p3);
        handles.push_back(&p4);
        handles.push_back(&p5);
        handles.push_back(&p6);
        handles.push_back(&O);
    }

    void draw_distance(cairo_t *cr, std::ostringstream *notify,
                      int width, int height, bool save)
    {
        draw_common(cr, notify, width, height, save);

        Line l1(p1.pos, p2.pos);
        LineSegment ls(p3.pos, p4.pos);
        Ray r1(p5.pos, p6.pos);

        Point q1 = l1.pointAt(l1.nearestPoint(O.pos));
        Point q2 = ls.pointAt(ls.nearestPoint(O.pos));
        Point q3 = r1.pointAt(r1.nearestPoint(O.pos));

        double d1 = distance(O.pos, l1);
        double d2 = distance(O.pos, ls);
        double d3 = distance(O.pos, r1);

        cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 1.0);
        cairo_set_line_width(cr, 0.3);
        draw_line(cr, l1);
        draw_segment(cr, ls);
        draw_ray(cr, r1);
        cairo_stroke(cr);


        draw_label(cr, l1, "L");
        draw_label(cr, ls, "S");
        draw_label(cr, r1, "R");
        draw_label(cr, O, "P");
        cairo_stroke(cr);

        cairo_set_source_rgba(cr, 0.5, 0.5, 0.8, 1.0);
        cairo_set_line_width(cr, 0.2);
        draw_segment(cr, O.pos, q1);
        draw_segment(cr, O.pos, q2);
        draw_segment(cr, O.pos, q3);
        cairo_stroke(cr);

        cairo_set_source_rgba(cr, 0.8, 0.0, 0.0, 1.0);
        cairo_set_line_width(cr, 0.3);
        draw_handle(cr, q1);
        draw_handle(cr, q2);
        draw_handle(cr, q3);
        cairo_stroke(cr);

        *notify << "  distance(P,L) = " << d1 << std::endl;
        *notify << "  distance(P,S) = " << d2 << std::endl;
        *notify << "  distance(P,R) = " << d3 << std::endl;
    }


    void init_position()
    {
        init_common();
        p1.pos = Point(400, 50);
        p2.pos = Point(450, 450);
        p3.pos = Point(100, 50);
        p4.pos = Point(150, 450);

        handles.push_back(&p1);
        handles.push_back(&p2);
        handles.push_back(&p3);
        handles.push_back(&p4);
    }

    void draw_position(cairo_t *cr, std::ostringstream *notify,
                      int width, int height, bool save)
    {
        draw_common(cr, notify, width, height, save);

        Line l1(p1.pos, p2.pos);
        Line l2(p3.pos, p4.pos);

        bool b1 = are_same(l1, l2, 0.01);
        bool b2 = are_parallel(l1, l2, 0.01);
        bool b3 = are_orthogonal(l1, l2, 0.01);

        double a = angle_between(l1,l2);

        cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 1.0);
        cairo_set_line_width(cr, 0.3);
        draw_line(cr, l1);
        draw_line(cr, l2);
        cairo_stroke(cr);

        draw_label(cr, l1, "A");
        draw_label(cr, l2, "B");
        cairo_stroke(cr);

        if (b1)
        {
            *notify << "  A is coincident with B" << std::endl;
        }
        else if (b2)
        {
            *notify << "  A is parallel to B" << std::endl;
        }
        else if (b3)
        {
            *notify << "  A is orthogonal to B" << std::endl;
        }
        else
        {
            *notify << "  A is incident with B:  angle(A,B) = " << angle_formatter(a) << std::endl;
        }
    }


    void init_seg_bisec()
    {
        init_common();
        p1.pos = Point(100, 50);
        p2.pos = Point(150, 450);

        handles.push_back(&p1);
        handles.push_back(&p2);
    }

    void draw_seg_bisec(cairo_t *cr, std::ostringstream *notify,
                      int width, int height, bool save)
    {
        draw_common(cr, notify, width, height, save);

        LineSegment ls(p1.pos, p2.pos);
        Line l = make_bisector_line(ls);
        Point M = middle_point(p1.pos, p2.pos);

        cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 1.0);
        cairo_set_line_width(cr, 0.3);
        draw_label(cr, p1, "P");
        draw_label(cr, p2, "Q");
        draw_label(cr, M, "M");
        draw_segment(cr, ls);
        draw_line(cr, l);
        cairo_stroke(cr);

        draw_label(cr, l, "axis");
        cairo_stroke(cr);
    }


    void init_angle_bisec()
    {
        init_common();
        p1.pos = Point(100, 50);
        p2.pos = Point(150, 450);
        O.pos = Point(50, 200);

        handles.push_back(&p1);
        handles.push_back(&p2);
        handles.push_back(&O);
    }

    void draw_angle_bisec(cairo_t *cr, std::ostringstream *notify,
                      int width, int height, bool save)
    {
        draw_common(cr, notify, width, height, save);

        Ray r1(O.pos, p1.pos);
        Ray r2(O.pos, p2.pos);
        Ray rb = make_angle_bisector_ray(r1, r2);

        double a1 = angle_between(r1,rb);
        double a2 = angle_between(rb,r2);

        cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 1.0);
        cairo_set_line_width(cr, 0.3);
        draw_label(cr, O, "O");
        draw_ray(cr, r1);
        draw_ray(cr, r2);
        draw_ray(cr, rb);
        cairo_stroke(cr);

        draw_label(cr, r1, "R1");
        draw_label(cr, r2, "R2");
        draw_label(cr, rb, "bisector ray");

        *notify << "  angle(R1, bisector ray) = " << angle_formatter(a1)
                << "    angle(bisector ray, R2) = " << angle_formatter(a2)
                << std::endl;
    }


    void init_collinear()
    {
        init_common();
        p1.pos = Point(100, 50);
        p2.pos = Point(450, 450);
        p3.pos = Point(400, 50);

        handles.push_back(&p1);
        handles.push_back(&p2);
        handles.push_back(&p3);
    }

    void draw_collinear(cairo_t *cr, std::ostringstream *notify,
                      int width, int height, bool save)
    {
        draw_common(cr, notify, width, height, save);

        Point A = p1.pos;
        Point B = p2.pos;
        Point C = p3.pos;

        LineSegment AB(A, B);
        LineSegment BC(B, C);
        Line l(A, C);

        cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 1.0);
        cairo_set_line_width(cr, 0.3);
        draw_label(cr, p1, "A");
        draw_label(cr, p2, "B");
        draw_label(cr, p3, "C");
        cairo_stroke(cr);


        double turn = cross(C, B) - cross(C, A) + cross(B, A);
        //*notify << "  turn: " << turn << std::endl;

        bool collinear = are_collinear(A, B, C, 200);
        if (collinear)
        {
            cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 1.0);
            cairo_set_line_width(cr, 0.3);
            draw_line(cr, l);
            cairo_stroke(cr);
            *notify << "  A,B,C are collinear!" << std::endl;
        }
        else
        {
            cairo_set_source_rgba(cr, 0.5, 0.5, 0.8, 1.0);
            cairo_set_line_width(cr, 0.2);
            draw_segment(cr, AB);
            draw_segment(cr, BC);
            cairo_stroke(cr);
            if (turn < 0)
                *notify << "  A,B,C is a left turn:  " << turn << std::endl;
            else
                *notify << "  A,B,C is a right turn: " << turn << std::endl;
        }

    }


    void init_intersections()
    {
        init_common();
        p1.pos = Point(400, 50);
        p2.pos = Point(450, 450);
        p3.pos = Point(100, 250);
        p4.pos = Point(200, 450);
        p5.pos = Point(50, 150);
        p6.pos = Point(480, 60);

        handles.push_back(&p1);
        handles.push_back(&p2);
        handles.push_back(&p3);
        handles.push_back(&p4);
        handles.push_back(&p5);
        handles.push_back(&p6);
    }

    void draw_intersections(cairo_t *cr, std::ostringstream *notify,
                            int width, int height, bool save)
    {
        draw_common(cr, notify, width, height, save);

        Line l1(p1.pos, p2.pos);
        Ray r1(p3.pos, p4.pos);
        LineSegment s1(p5.pos, p6.pos);

        Crossings cl1r1 = intersection(l1, r1);
        Crossings cl1s1 = intersection(l1, s1);
        Crossings cr1s1 = intersection(r1, s1);

        std::vector<Point> ip;

        for (unsigned int i = 0; i < cl1r1.size(); ++i)
        {
            ip.push_back(l1.pointAt(cl1r1[i].ta));
        }
        for (unsigned int i = 0; i < cl1s1.size(); ++i)
        {
            ip.push_back(l1.pointAt(cl1s1[i].ta));
        }
        for (unsigned int i = 0; i < cr1s1.size(); ++i)
        {
            ip.push_back(r1.pointAt(cr1s1[i].ta));
        }


        cairo_set_source_rgba(cr, 0.2, 0.2, 0.2, 1.0);
        cairo_set_line_width(cr, 0.3);
        draw_line(cr, l1);
        draw_ray(cr, r1);
        draw_segment(cr, s1);
        cairo_stroke(cr);


        draw_label(cr, l1, "L");
        draw_label(cr, r1, "R");
        draw_label(cr, s1, "S");
        cairo_stroke(cr);

        std::string label("A");
        cairo_set_source_rgba(cr, 1.0, 0.0, 0.0, 1.0);
        cairo_set_line_width(cr, 0.5);
        for (unsigned int i = 0; i < ip.size(); ++i)
        {
            draw_handle(cr, ip[i]);
            draw_text(cr, ip[i]+op, label.c_str());
            label[0] += 1;
        }
        cairo_stroke(cr);

    }

    void init_common_ctrl_geom(cairo_t* /*cr*/, int /*width*/, int /*height*/, std::ostringstream* /*notify*/)
    {
        if ( set_common_control_geometry )
        {
            set_common_control_geometry = false;
        }
    }

    void init_create_ctrl_geom(cairo_t* /*cr*/, std::ostringstream* /*notify*/, int /*width*/, int height)
    {
        if ( set_control_geometry )
        {
            set_control_geometry = false;

            sliders[ANGLE_SLIDER].geometry(Point(50, height - 50), 180);
        }
    }



    void draw_segment(cairo_t* cr, Point const& p1, Point const&  p2)
    {
        cairo_move_to(cr, p1);
        cairo_line_to(cr, p2);
    }

    void draw_segment(cairo_t* cr, Point const& p1, double angle, double length)
    {
        Point p2;
        p2[X] = length * std::cos(angle);
        p2[Y] = length * std::sin(angle);
        p2 += p1;
        draw_segment(cr, p1, p2);
    }

    void draw_segment(cairo_t* cr, LineSegment const& ls)
    {
        draw_segment(cr, ls[0], ls[1]);
    }

    void draw_ray(cairo_t* cr, Ray const& r)
    {
        double angle = r.angle();
        draw_segment(cr, r.origin(), angle, m_length);
    }

    void draw_line(cairo_t* cr, Line const& l)
    {
        double angle = l.angle();
        draw_segment(cr, l.origin(), angle, m_length);
        draw_segment(cr, l.origin(), angle, -m_length);
    }

    void draw_label(cairo_t* cr, PointHandle const& ph, const char* label)
    {
        draw_text(cr, ph.pos+op, label);
    }

    void draw_label(cairo_t* cr, Line const& l, const char* label)
    {
        draw_text(cr, projection(Point(m_width/2-30, m_height/2-30), l)+op, label);
    }

    void draw_label(cairo_t* cr, LineSegment const& ls, const char* label)
    {
        draw_text(cr, middle_point(ls[0], ls[1])+op, label);
    }

    void draw_label(cairo_t* cr, Ray const& r, const char* label)
    {
        Point prj = r.pointAt(r.nearestPoint(Point(m_width/2-30, m_height/2-30)));
        if (L2(r.origin() - prj) < 100)
        {
            prj = r.origin() + 100*r.versor();
        }
        draw_text(cr, prj+op, label);
    }

    void init_menu()
    {
        handles.clear();
        sliders.clear();
        toggles.clear();
    }

    void draw_menu( cairo_t * /*cr*/, std::ostringstream *notify,
                    int /*width*/, int /*height*/, bool /*save*/ )
    {
        *notify << std::endl;
        for (int i = SHOW_MENU; i < TOTAL_ITEMS; ++i)
        {
            *notify << "   " << keys[i] << " -  " <<  menu_items[i] << std::endl;
        }
    }

    void key_hit(GdkEventKey *e)
    {
        char choice = std::toupper(e->keyval);
        switch ( choice )
        {
            case 'A':
                init_menu();
                draw_f = &LineToy::draw_menu;
                break;
            case 'B':
                init_create();
                draw_f = &LineToy::draw_create;
                break;
            case 'C':
                init_projection();
                draw_f = &LineToy::draw_projection;
                break;
            case 'D':
                init_ortho();
                draw_f = &LineToy::draw_ortho;
                break;
            case 'E':
                init_distance();
                draw_f = &LineToy::draw_distance;
                break;
            case 'F':
                init_position();
                draw_f = &LineToy::draw_position;
                break;
            case 'G':
                init_seg_bisec();
                draw_f = &LineToy::draw_seg_bisec;
                break;
            case 'H':
                init_angle_bisec();
                draw_f = &LineToy::draw_angle_bisec;
                break;
            case 'I':
                init_collinear();
                draw_f = &LineToy::draw_collinear;
                break;
            case 'J':
                init_intersections();
                draw_f = &LineToy::draw_intersections;
                break;
        }
        redraw();
    }

    virtual void draw( cairo_t *cr, std::ostringstream *notify,
                       int width, int height, bool save )
    {
        m_width = width;
        m_height = height;
        m_length = (m_width > m_height) ? m_width : m_height;
        m_length *= 2;
        (this->*draw_f)(cr, notify, width, height, save);
        Toy::draw(cr, notify, width, height, save);
    }

  public:
    LineToy()
    {
        op = Point(5,5);
    }

  private:
    typedef void (LineToy::* draw_func_t) (cairo_t*, std::ostringstream*, int, int, bool);
    draw_func_t draw_f;
    bool set_common_control_geometry;
    bool set_control_geometry;
    PointHandle p1, p2, p3, p4, p5, p6, O;
    std::vector<Toggle> toggles;
    std::vector<Slider> sliders;
    Point op;
    double m_width, m_height, m_length;

}; // end class LineToy


const char* LineToy::menu_items[] =
{
    "show this menu",
    "line generation",
    "projection on  a line",
    "make orthogonal/parallel",
    "distance",
    "position",
    "segment bisector",
    "angle bisector",
    "collinear",
    "intersection"
};

const char LineToy::keys[] =
{
     'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'
};



int main(int argc, char **argv)
{
    init( argc, argv, new LineToy());
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