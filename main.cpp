#include <iostream>
#include "ccc_x11.h"
#include "ccc_shap.h"

using namespace std ;

/*
 Exercise P6.19. A polygon is a closed sequence of lines. To describe a polygon, store the sequence of its corner points. Because the number of points is variable, use a vector.
 class Polygon
 {
 public:
 Polygon();
 void add_point(Point p);
 void plot() const;
 private:
 vector<Point> corners;
 };
 Implement this class and supply a test harness that plots a polygon such as the following:
*/

int ccc_win_main()
{
    Point origin(0, 0);
    Point topleft((cwin.get_xmin()-(cwin.get_xmin()/10)), (cwin.get_ymax() - (cwin.get_ymax()/10)));
    Point topright((cwin.get_xmax()-(cwin.get_xmax()/10)), (cwin.get_ymax() - (cwin.get_ymax()/10)));
    Point bottomleft((cwin.get_xmin()-(cwin.get_xmin()/10)), (cwin.get_ymin() - (cwin.get_ymin()/10)));
    Point bottomright((cwin.get_xmax()-(cwin.get_xmax()/10)), (cwin.get_ymin() - (cwin.get_ymin()/10)));
    //cwin << topleft << topright << bottomleft << bottomright;
    //Message set_corners_message(topleft, "How many corners for polygon?");
    //cwin << set_corners_message;
    /*
    int corners = cwin.get_int("How many corners for polygon? ");
    Message get_corners_message(topleft, corners);
    cwin << get_corners_message;
     */
    
    int corners = 0;
    while (corners < 3){
        corners = cwin.get_int("How many corners for polygon? ");
        Message get_corners_message(topleft, corners);
        cwin << get_corners_message;
        cwin.clear();
    }
    
    topleft.move(0, -5);
    Polygon poly;
    
    int i;
    for (i = 0; i < corners; i++){
        Point p = cwin.get_mouse("Input points");
        cwin << p;
        poly.add_point(p);
    }
    topleft.move(0, 5);
    
    poly.display();
    
    return 0;
}

// ----------------------------------------------------------------------------
//
// ------------------------------- Sub Programs -------------------------------
//
// ----------------------------------------------------------------------------


