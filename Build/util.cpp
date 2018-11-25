#include "util.hpp"

int HELPERS::stringtoint(const std::string &s){
    int i = s.length()-1;
    int n = 0;
    int digit = 0;
    bool negative = (s[0] == '-') ? true : false;

    while(i >= 0)
    {
        if (s[i] == '-') return n * -1;
        if (digit != 0)
            n += pow(10.0, digit) * (s[i] - '0');
        else n += (s[i] - '0');
        --i;
        ++digit;
    }
    return n;
}
void HELPERS::print_vector_points(std::vector<Point> vp){
    for (int i = 0; i < vp.size(); i++){
        //HELPERS::sleep(10); // if vect size is 1000, sleep time will be 10 * 1000 = 10000 ms
        cwin << vp[i];
    }
}
void HELPERS::print_vector_points(std::vector<Point> vp, int from, int to){
    vector<Point> vp_copy = HELPERS::get_subvector(vp, from, to);
    HELPERS::print_vector_points(vp_copy);
}
void HELPERS::test_coords(){
    Point topleft = Point(-999, 999);
    Point topright = Point(999, 999);
    Point botleft = Point(-999, -999);
    Point botright = Point(999, -999);
    cwin << topleft << topright << botleft << botright;
}
void HELPERS::print_vector_coords(std::vector<Point> vp, int line_space, int width){
    Point topleft(-999, 999);
    
    for (int i = 0; i < vp.size(); i++){
        Message d1(topleft, vp[i].get_x());
        cwin << d1;
        
        topleft.move(width, 0);
        Message d2(topleft, vp[i].get_y());
        cwin << d2;
        
        topleft.move(-width, line_space);
        if (topleft.get_y() < -1000){
            topleft.move(width*2, 2000);
        }
    }
}
std::vector<Point> HELPERS::get_subvector(std::vector<Point>& vp, int from, int to){
    vector<Point> z;
    for (int i = from; i <= to; i++){
        z.push_back(vp[i]);
    }
    return z;
}
long double total_time_sleeping = 0;
bool HELPERS::sleep(double milliseconds){
    total_time_sleeping += milliseconds;
    milliseconds /= 10.0;
    clock_t time_end;
    time_end = clock() + milliseconds * (CLOCKS_PER_SEC/1000.0);
    while (clock() < time_end) { cwin.repaint(); }
    return true;
}
void HELPERS::display_total_time_sleeping(){
    // Heads up, these times are relative - not precise at all and don't truly denote ms or sec. This func still gives a good idea of actual times since usually working w powers of 10.
    double seconds = total_time_sleeping / 1000.0;
    ostringstream oss;
    oss << total_time_sleeping;
    string msg = "Total Time Sleeping: ";
    msg += oss.str();
    msg += " milliseconds or ";
    oss.str("");
    oss << seconds;
    msg += oss.str();
    msg += " seconds";
    Point p = Point(-990, 990);
    Message m(p, msg);
    cwin << m;
}





