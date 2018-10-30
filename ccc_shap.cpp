#include <cstdio>

#include "ccc_shap.h"
#include <cmath>

Point::Point()
{  
   x = 0.0;
   y = 0.0;
}

Point::Point(double x1, double y1)
{  
   x = x1;
   y = y1;
}

double Point::get_x() const
{  
   return x;
}

double Point::get_y() const
{  
   return y;
}

void Point::move(double dx, double dy)
{  
   x += dx;
   y += dy;
}

/*-------------------------------------------------------------------------*/

Circle::Circle()
{  
   radius = 0.0;
}

Circle::Circle(Point p, double r)
{  
   center = p;
   radius = r;
}

Point Circle::get_center() const
{  
   return center;
}

double Circle::get_radius() const
{  
   return radius;
}

void Circle::move(double dx, double dy)
{  
   center.move(dx, dy);
}

/*-------------------------------------------------------------------------*/

Line::Line()
{
}

Line::Line(Point p1, Point p2)
{  
   from = p1;
   to = p2;
   distance = sqrt( pow((to.get_x()-from.get_x()), 2) + pow((to.get_y()-from.get_y()),2) );
}

Point Line::get_start() const
{  
   return from;
}

Point Line::get_end() const
{  
   return to;
}

void Line::move(double dx, double dy)
{  
   from.move(dx, dy);
   to.move(dx, dy);
}
Point Line::midpoint() const{
    double x, y;
    if (from.get_x() > to.get_x()){
        x = (from.get_x() + to.get_x()) / 2;
    } else {
        x = (to.get_x() + from.get_x()) / 2;
    }
    if (from.get_y() >= to.get_x()){
        y = (from.get_y() + to.get_y()) / 2;
    } else {
        y = (to.get_y() + from.get_y()) / 2;
    }
    Point mp(x, y);
    return mp;
}
double Line::get_distance() const{
    return distance;
}

/*-------------------------------------------------------------------------*/

Message::Message()
{}

Message::Message(Point s, const string& m)
{  
   start = s;
   text = m;
}

Message::Message(Point s, double x)
{  
   start = s;
   char buf[20];
   sprintf(buf, "%g", x);
   text = buf;
}


Point Message::get_start() const
{  
   return start;
}

string Message::get_text() const
{  
   return text;
}

void Message::move(double dx, double dy)
{  
   start.move(dx, dy);
}

/*-------------------------------------------------------------------------*/
/* RECTANGLE CLASS */
Rectangle::Rectangle(){
    topleft = Point(0,0);
    botright = Point(0,0);
    topright = Point(0,0);
    botleft = Point(0,0);
    length = 0;
    width = 0;
}
Rectangle::Rectangle(Point tl, Point br){
    topleft = tl;
    botright = br;
    topright = Point(br.get_x(), tl.get_y());
    botleft = Point(tl.get_x(), br.get_y());
    if (topleft.get_x() >= botright.get_x()){
        width = topleft.get_x() - botright.get_x();
    } else if (botright.get_x() > topleft.get_x()){
        width = botright.get_x() - topleft.get_x();
    }
    if (topleft.get_y() >= botright.get_y()){
        length = topleft.get_y() - botright.get_y();
    } else if (botright.get_y() > topleft.get_y()){
        length = botright.get_y() - topleft.get_y();
    }
    // Line left_vertical, right_vertical, top_horizontal, bot_horizontal;
    left_vertical = Line(botleft, topleft);
    right_vertical = Line(botright, topright);
    top_horizontal = Line(topleft, topright);
    bot_horizontal = Line(botleft, botright);
}
//Rectangle::Rectangle(Point tl, Point tr, Point bl, Point br){
Point Rectangle::get_topleft() const{
    return topleft;
}
Point Rectangle::get_botright() const{
    return botright;
}
Point Rectangle::get_topright() const{
    return topright;
}
Point Rectangle::get_botleft() const{
    return botleft;
}
double Rectangle::calc_r_area(){
    double a = length * width;
    return a;
}
double Rectangle::calc_r_perimeter(){
    double p = (2*length)+(2*width);
    return p;
}
void Rectangle::display() const{
    cwin << topleft << topright << botleft << botright;
    cwin << top_horizontal << bot_horizontal << left_vertical << right_vertical;
}

/*-------------------------------------------------------------------------*/
/* TRIANGLE CLASS */
// Triangle(); No need for default constructor atm...
Triangle::Triangle(Point p1, Point p2, Point p3){
    equilateral = false;
    isosceles = false;
    a = p1;
    b = p2;
    c = p3;
    ab = Line(a, b);
    ac = Line(a, c);
    bc = Line(b, c);
    if  ( (ab.get_distance() == bc.get_distance()) ||
         (ab.get_distance() == ac.get_distance()) ||
         (bc.get_distance() == ac.get_distance()) ){
        isosceles = true;
    }
    
    if ((a.get_x() >= b.get_x()) && (a.get_x() >= c.get_x()) ){
        max_x = a.get_x();
    } else if ((b.get_x() >= a.get_x()) && (b.get_x() >= c.get_x()) ){
        max_x = b.get_x();
    } else if ((c.get_x() >= a.get_x()) && (c.get_x() >= b.get_x()) ){
        max_x = c.get_x();
    }
    if ((a.get_x() <= b.get_x()) && (a.get_x() <= c.get_x()) ){
        min_x = a.get_x();
    } else if ((b.get_x() <= a.get_x()) && (b.get_x() <= c.get_x()) ){
        min_x = b.get_x();
    } else if ((c.get_x() <= a.get_x()) && (c.get_x() <= b.get_x()) ){
        min_x = c.get_x();
    }
    if ((a.get_y() >= b.get_y()) && (a.get_y() >= c.get_y()) ){
        max_y = a.get_y();
    } else if ((b.get_y() >= a.get_y()) && (b.get_y() >= c.get_y()) ){
        max_y = b.get_y();
    } else if ((c.get_y() >= a.get_y()) && (c.get_y() >= b.get_y()) ){
        max_y = c.get_y();
    }
    if ((a.get_y() <= b.get_y()) && (a.get_y() <= c.get_y()) ){
        min_y = a.get_y();
    } else if ((b.get_y() <= a.get_y()) && (b.get_y() <= c.get_y()) ){
        min_y = b.get_y();
    } else if ((c.get_y() <= a.get_y()) && (c.get_y() <= b.get_y()) ){
        min_y = c.get_y();
    }
    
    if ((ab.get_distance() > ac.get_distance()) && (ab.get_distance() > bc.get_distance())){
        hypotenuse = ab;
        if (isosceles) {opposite = Point(hypotenuse.midpoint().get_x(), c.get_y());}
    } else if ((ac.get_distance() > ab.get_distance()) && (ac.get_distance() > bc.get_distance())){
        hypotenuse = ac;
        if (isosceles) {opposite = Point(hypotenuse.midpoint().get_x(), b.get_y());}
    } else if ((bc.get_distance() > ab.get_distance()) && (bc.get_distance() > ac.get_distance())){
        hypotenuse = bc;
        if (isosceles) {opposite = Point(hypotenuse.midpoint().get_x(), a.get_y());}
    } else {
        equilateral = true;
    }
    
    if (equilateral){
        height = abs(b.get_y() + ac.midpoint().get_y());
    } else if (isosceles){
        height = abs(hypotenuse.midpoint().get_y() - opposite.get_y());
    } else {
        height = abs(max_y - min_y);
    }
}
bool Triangle::is_equilateral() const{
    if (equilateral){
        return true;
    } else {
        return false;
    }
}
double Triangle::calc_t_area(){
    double a = (1.0/2.0) * hypotenuse.get_distance() * height;
    return a;
}
double Triangle::calc_t_perimeter(){
    double p = ab.get_distance() + bc.get_distance() + ac.get_distance();
    return p;
}
void Triangle::display() const{
    cwin << a << b << c << ab << bc << ac;
}
/*
 private:
 Point a, b, c;
 Line ab, ac, bc;
 Line hypotenuse;
 double height;
 */

/*-------------------------------------------------------------------------*/
/* PRISM CLASS */

// don't see the point of a default constructor here...

Prism::Prism(Rectangle a, Rectangle b){
    r1 = a;
    r2 = b;
    top_right = Line(a.get_topright(), b.get_topright());
    top_left = Line(a.get_topleft(), b.get_topleft());
    bot_right = Line(a.get_botright(), b.get_botright());
    bot_left = Line(a.get_botleft(), b.get_botleft());
}

void Prism::display(){
    r1.display();
    r2.display();
    cwin << top_right << top_left << bot_right << bot_left;
}

/*-------------------------------------------------------------------------*/
/* Polygon CLASS */

Polygon::Polygon(){}
void Polygon::add_point(Point p1){
    corners.push_back(p1);
}
void Polygon::plot_corners(){
    vector<Point> temp_corners = corners;
    int i;
    for (i = 0; i < (corners.size()-1); i++){
        Line l(corners[i], corners[i+1]);
        lines.push_back(l);
    }
    Line l(corners[0], corners[corners.size()-1]);
    lines.push_back(l);
}
void Polygon::display_corners() const{
    int i;
    for (i = 0; i < corners.size(); i++){
        cwin << corners[i];
    }
}
void Polygon::display_lines() const{
    int i;
    for (i = 0; i < lines.size(); i++){
        cwin << lines[i];
    }
}
void Polygon::display(){
    if (lines.size() == 0){
        plot_corners();
    }
    display_corners();
    display_lines();
}
double Polygon::get_distance(Point p1, Point p2) const{
    double distance = sqrt( pow((p1.get_x()-p2.get_x()), 2) + pow((p1.get_y()-p2.get_y()),2) );
    return distance;
}
double Polygon::get_num_corners(){
    return corners.size();
}

/*
private:
    vector<Point> corners;
    vector<Line> connections;
*/

//HELPERS
void remove_corner(vector<Point>& vp, int index){
    int i;
    for (i = index; i < (vp.size() - 1); i++){
        vp[i] = vp[i+1];
    }
    vp.pop_back();
}
