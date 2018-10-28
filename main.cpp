// ----------------------------------------------------------------------------
//
// ---------------------- [Untitled Program.  Name Me!] -----------------------
//
// ----------------------------------------------------------------------------
//
//  Program Name:			[Untitled Program.  Name Me!]
//
//  Program Description:	[Describe this program!]
//
//  Author:					[Your Name Here!]
//  Course:					[Course Name]
//  Date:					YYYY-MM-DD
//
// ----------------------------------------------------------------------------

#include <iostream>
//--------------------Add The Rest of Your Includes Here!--------------------//
#include "ccc_x11.h"
#include "ccc_shap.h"

using namespace std ;

// ----------------------------------------------------------------------------
//
// -------------------------------- Prototypes --------------------------------
//
// ----------------------------------------------------------------------------



// ----------------------------------------------------------------------------
//
// ------------------------------- Main Program -------------------------------
//
// ----------------------------------------------------------------------------

int ccc_win_main()
{
    Point ignore0 = cwin.get_mouse("Click to get started");
    cwin << ignore0;
    cwin.clear();
    Point top_left1 = cwin.get_mouse("Click top left point for R1");
    cwin << top_left1;
    Point bot_right1 = cwin.get_mouse("Click bot right point for R1");
    cwin << bot_right1;
    //Point top_left1(-20, 60);
    //Point bot_right1(30, -10);
    Rectangle rect1(top_left1, bot_right1);
    rect1.display();
    Point ignore1 = cwin.get_mouse("Click for next Rectangle");
    cwin << ignore1;
    cwin.clear();
    Point top_left2 = cwin.get_mouse("Click top left point for R2");
    cwin << top_left2;
    Point bot_right2 = cwin.get_mouse("Click bot right point for R2");
    cwin << bot_right2;
    //Point top_left2(-40, 75);
    //Point bot_right2(82, -30);
    Rectangle rect2(top_left2, bot_right2);
    rect2.display();
    Point ignore2 = cwin.get_mouse("Click to generate Prism1");
    cwin << ignore2;
    cwin.clear();
    Prism p1(rect1, rect2);
    p1.display();
    
    /*
    Line lr1(top_left1, rect1.get_topright());
    Point top1(lr1.midpoint().get_x(), lr1.midpoint().get_y()+40);
    Line lr2(top_left2, rect2.get_topright());
    Point top2(lr2.midpoint().get_x(), lr2.midpoint().get_y()+40);
    */
    /*
    Triangle t1(top_left1, rect1.get_topright(), top1);
    Triangle t2(top_left2, rect2.get_topright(), top2);
    t1.display();
    t2.display();
    */
    
    Line surface_diagonal(rect1.get_topleft(), rect2.get_topright());
    //Point peak(surface_diagonal.midpoint().get_x(), surface_diagonal.midpoint().get_y()+30);
    Point peak = cwin.get_mouse("Click peak location");
    cwin << peak;
    Point ignore3 = cwin.get_mouse("Click to generate Prism2");
    cwin << ignore3;
    cwin.clear();
    Triangle t1(rect1.get_topleft(), rect1.get_topright(), peak);
    Triangle t2(rect2.get_topleft(), rect2.get_topright(), peak);
    p1.display();
    t1.display();
    t2.display();
    
    //Prism p2(t1, t2);
    //p2.display();
    
    // Working
    return 0;
}

// ----------------------------------------------------------------------------
//
// ------------------------------- Sub Programs -------------------------------
//
// ----------------------------------------------------------------------------


