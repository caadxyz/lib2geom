#include <iostream>
//#include <chrono>
#include <ctime>

#include "2geom/svg-path-parser.h"
#include "2geom/pathvector.h"
using namespace Geom;

static char const *banana = "M 265.71429,158.07648 C 190.6809,177.20365 122.07669,234.71591 "
                            "104.63056,312.25563 C 77.156999,399.83651 70.794763,500.27985 "
                            "114.77866,583.69036 C 144.53063,634.44937 199.36676,669.20393 "
                            "257.74302,675.53709 C 270.81001,702.04856 314.06907,671.3079 "
                            "286.33697,654.18295 C 255.1688,600.99542 216.46623,548.3017 "
                            "211.13947,484.83476 C 202.31209,421.03768 205.02251,351.85571 "
                            "239.06833,295.30186 C 257.00587,263.44474 279.73092,234.67917 "
                            "301.98406,205.79097 C 300.02661,180.33683 358.06043,134.08979 "
                            "326.58199,129.37189 C 312.92978,127.95692 277.30454,151.73686 "
                            "265.71429,158.07648 z";

static char const *many_subpaths =
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 "
    "M 240,495.21933 648.57143,400.93361 C 190.6809,177.20365 122.07669,234.71591 104.6,312.5 ";

int main()
{
    //    auto start = std::chrono::high_resolution_clock::now();
    const int num_repeats = 1000;
    std::vector<Path> path = parse_svg_path(many_subpaths);
    path += Point(1, 0);
    std::clock_t start = std::clock();
    for (int i = 0; i < num_repeats; i++) {
        std::vector<Path> path2 = reverse_paths_and_order(path);
        std::vector<Path> path3 = reverse_paths_and_order(reverse_paths_and_order(path2));
    }
    // auto stop = std::chrono::high_resolution_clock::now();
    std::clock_t stop = std::clock();
    std::cout << "Runtime (" << num_repeats << "x): "
        //<< std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms "
              << (stop - start) * (1000. / CLOCKS_PER_SEC) << " ms " << std::endl;
}



//