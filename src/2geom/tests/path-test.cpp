#include "testing.h"
#include <iostream>

#include <2geom/bezier.h>
#include <2geom/path.h>
#include <2geom/pathvector.h>
#include <2geom/path-intersection.h>
#include <2geom/svg-path-parser.h>
#include <2geom/svg-path-writer.h>
#include <vector>
#include <iterator>

using namespace std;
using namespace Geom;

Path string_to_path(const char* s) {
    PathVector pv = parse_svg_path(s);
    assert(pv.size() == 1);
    return pv[0];
}

// Path fixture
class PathTest : public ::testing::Test {
protected:
    PathTest() {
        line.append(LineSegment(Point(0,0), Point(1,0)));
        square = string_to_path("M 0,0 1,0 1,1 0,1 z");
        circle = string_to_path("M 0,0 a 4.5,4.5 0 1 1 -9,0 4.5,4.5 0 1 1 9,0 z");
        diederik = string_to_path("m 262.6037,35.824151 c 0,0 -92.64892,-187.405851 30,-149.999981 104.06976,31.739531 170,109.9999815 170,109.9999815 l -10,-59.9999905 c 0,0 40,79.99999 -40,79.99999 -80,0 -70,-129.999981 -70,-129.999981 l 50,0 C 435.13571,-131.5667 652.76275,126.44872 505.74322,108.05672 358.73876,89.666591 292.6037,-14.175849 292.6037,15.824151 c 0,30 -30,20 -30,20 z");
        cmds = string_to_path("M 0,0 V 100 H 100 Q 100,0 0,0 L 200,0 C 200,100 300,100 300,0 S 200,-100 200,0");
    }

    // Objects declared here can be used by all tests in the test case for Foo.
    Path line, square, circle, diederik, cmds;
};

TEST_F(PathTest, Continuity) {
    line.checkContinuity();
    square.checkContinuity();
    circle.checkContinuity();
    diederik.checkContinuity();
    cmds.checkContinuity();
}

TEST_F(PathTest, ValueAt) {
    EXPECT_EQ(Point(0,0), line.initialPoint());
    EXPECT_EQ(Point(1,0), line.finalPoint());

    EXPECT_EQ(Point(0.5, 0.0), line.pointAt(0.5));

    EXPECT_EQ(Point(0,0), square.initialPoint());
    EXPECT_EQ(Point(0,0), square.finalPoint());
    EXPECT_EQ(Point(1,0), square.pointAt(1));
    EXPECT_EQ(Point(0.5,1), square.pointAt(2.5));
    EXPECT_EQ(Point(0,0.5), square.pointAt(3.5));
    EXPECT_EQ(Point(0,0), square.pointAt(4));
}

TEST_F(PathTest, NearestPoint) {
    EXPECT_EQ(0, line.nearestTime(Point(0,0)));
    EXPECT_EQ(0.5, line.nearestTime(Point(0.5,0)));
    EXPECT_EQ(0.5, line.nearestTime(Point(0.5,1)));
    EXPECT_EQ(1, line.nearestTime(Point(100,0)));
    EXPECT_EQ(0, line.nearestTime(Point(-100,1000)));

    EXPECT_EQ(0, square.nearestTime(Point(0,0)));
    EXPECT_EQ(1, square.nearestTime(Point(1,0)));
    EXPECT_EQ(3, square.nearestTime(Point(0,1)));
    
    //cout << diederik.nearestTime(Point(247.32293,-43.339507)) << endl;

    EXPECT_FLOAT_EQ(6.5814033, diederik.nearestTime(Point(511.75,40.85)));
    //cout << diederik.pointAt(diederik.nearestTime(Point(511.75,40.85))) << endl;

}

TEST_F(PathTest, Winding) {
    // test points in special positions
    EXPECT_EQ(winding(line, Point(-1, 0)), 0);
    EXPECT_EQ(winding(line, Point(2, 0)), 0);
    EXPECT_EQ(winding(line, Point(0, 1)), 0);
    EXPECT_EQ(winding(line, Point(0, -1)), 0);
    EXPECT_EQ(winding(line, Point(1, 1)), 0);
    EXPECT_EQ(winding(line, Point(1, -1)), 0);

    EXPECT_EQ(winding(square, Point(0, -1)), 0);
    EXPECT_EQ(winding(square, Point(1, -1)), 0);
    EXPECT_EQ(winding(square, Point(0, 2)), 0);
    EXPECT_EQ(winding(square, Point(1, 2)), 0);
    EXPECT_EQ(winding(square, Point(-1, 0)), 0);
    EXPECT_EQ(winding(square, Point(-1, 1)), 0);
    EXPECT_EQ(winding(square, Point(2, 0)), 0);
    EXPECT_EQ(winding(square, Point(2, 1)), 0);
    EXPECT_EQ(winding(square, Point(0.5, 0.5)), 1);

    EXPECT_EQ(winding(circle, Point(-4.5,0)), 1);
    EXPECT_EQ(winding(circle, Point(-3.5,0)), 1);
    EXPECT_EQ(winding(circle, Point(-4.5,1)), 1);
    EXPECT_EQ(winding(circle, Point(-10,0)), 0);
    EXPECT_EQ(winding(circle, Point(1,0)), 0);
}

TEST_F(PathTest, SVGRoundtrip) {
    SVGPathWriter sw;

    Path transformed = diederik * (Rotate(1.23456789) * Scale(1e-8) * Translate(1e-9, 1e-9));

    for (unsigned i = 0; i < 4; ++i) {
        sw.setOptimize(i & 1);
        sw.setUseShorthands(i & 2);

        sw.feed(line);
        //cout << sw.str() << endl;
        Path line_svg = string_to_path(sw.str().c_str());
        EXPECT_TRUE(line_svg == line);
        sw.clear();

        sw.feed(square);
        //cout << sw.str() << endl;
        Path square_svg = string_to_path(sw.str().c_str());
        EXPECT_TRUE(square_svg == square);
        sw.clear();

        sw.feed(circle);
        //cout << sw.str() << endl;
        Path circle_svg = string_to_path(sw.str().c_str());
        EXPECT_TRUE(circle_svg == circle);
        sw.clear();

        sw.feed(diederik);
        //cout << sw.str() << endl;
        Path diederik_svg = string_to_path(sw.str().c_str());
        EXPECT_TRUE(diederik_svg == diederik);
        sw.clear();

        sw.feed(transformed);
        //cout << sw.str() << endl;
        Path transformed_svg = string_to_path(sw.str().c_str());
        EXPECT_TRUE(transformed_svg == transformed);
        sw.clear();

        sw.feed(cmds);
        //cout << sw.str() << endl;
        Path cmds_svg = string_to_path(sw.str().c_str());
        EXPECT_TRUE(cmds_svg == cmds);
        sw.clear();
    }
}

    /*TEST_F(PathTest,Operators) {
    cout << "scalar operators\n";
    cout << hump + 3 << endl;
    cout << hump - 3 << endl;
    cout << hump*3 << endl;
    cout << hump/3 << endl;

    Bezier reverse_wiggle = reverse(wiggle);
    EXPECT_EQ(reverse_wiggle[0], wiggle[wiggle.size()-1]);
    EXPECT_TRUE(are_equal(reverse(reverse_wiggle), wiggle));

    cout << "Bezier portion(const Bezier & a, double from, double to);\n";
    cout << portion(Bezier(0.0,2.0), 0.5, 1) << endl;

// std::vector<Point> bezier_points(const D2<Bezier > & a) {

    cout << "Bezier derivative(const Bezier & a);\n";
    std::cout << derivative(hump) <<std::endl;
    std::cout << integral(hump) <<std::endl;

    EXPECT_TRUE(are_equal(derivative(integral(wiggle)), wiggle));
    std::cout << derivative(integral(hump)) <<std::endl;
    expect_array((const double []){0.5}, derivative(hump).roots());

    EXPECT_TRUE(bounds_fast(hump)->contains(Interval(0,hump.valueAt(0.5))));

    EXPECT_EQ(Interval(0,hump.valueAt(0.5)), *bounds_exact(hump));

    Interval tight_local_bounds(min(hump.valueAt(0.3),hump.valueAt(0.6)),
             hump.valueAt(0.5));
    EXPECT_TRUE(bounds_local(hump, Interval(0.3, 0.6))->contains(tight_local_bounds));

    Bezier Bs[] = {unit, hump, wiggle};
    for(unsigned i = 0; i < sizeof(Bs)/sizeof(Bezier); i++) {
        Bezier B = Bs[i];
        Bezier product = multiply(B, B);
        for(int i = 0; i <= 16; i++) {
            double t = i/16.0;
            double b = B.valueAt(t);
            EXPECT_FLOAT_EQ(b*b, product.valueAt(t));
        }
    }
    }*/

/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:fileencoding=utf-8:textwidth=99 :
