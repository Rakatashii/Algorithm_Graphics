/*
 Exercise P11.14. Give a graphical animation of selection sort as follows: Fill a vector with a set of random numbers between 1 and 100. Set the window coordinate sys- tem to a.size() by 100. Draw each element as a stick, as in Figure 6. Whenever you change the vector, clear the screen and redraw.
 Exercise P11.15. Write a graphical animation of merge sort.
 Exercise P11.16. Write a graphical animation of binary search. Highlight the cur- rently inspected element.
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "ccc_x11.h"
#include "ccc_shap.h"
#include "util.hpp"
#include <sstream>
#include <unistd.h>
#include <time.h>

using namespace std;
using namespace HELPERS;

Point topleft(-999, 990);
static string current_process = "BINARY_SEARCH1";

int partitionx(vector<Point> &v, int from, int to);
void quicksortx(vector<Point> &v, int from, int to);
int min_position(vector<Point>& v, int from, int to);
void selection_sortx(vector<Point> &v);
void merge(vector<Point>& v, int from, int mid, int to);
void merge_sort(vector<Point> &v, int from, int to);
bool binary_search(vector<Point> v, int from, int to, double val, int& pos, double sleeptime = 500.0);
void print_binary_search_results(vector<Point> v, double val, int& pos, string result_name = "FOUND ", double sleeptime = 2000.0);

int ccc_win_main() {
    //HELPERS::test_coords();
    
    vector<Point> vp;
    std::string x_str = "", y_str = "";
    
    string data = "/Users/christianmeyer/Cpp/ch11/P11_14_15_16/data1000.txt";
    fstream fs(data.c_str(), ios::in | ios::out);
    
    string first_line;
    getline(fs, first_line);
    int sz = HELPERS::stringtoint(first_line);
    
    double xd = 0, yd = -1000;
    double y_incr = 2000.0/sz;
    
    vector<vector<string> > coord_strings;
    vector<string > coord_string;

    while (vp.size() < sz){
        getline(fs, x_str, '|');
        getline(fs, y_str, '\n');
        
        xd = HELPERS::stringtoint(x_str);
        yd += y_incr;
        
        vp.push_back(Point(xd, yd));
    }
    fs.close();
    
    //HELPERS::print_vector_coords(vp);
    //HELPERS::print_vector_points(vp);
    //HELPERS::display_total_time_sleeping();
    
    vector<Point> copy1 = vp;
    vector<Point> copy2 = vp;

    quicksortx(vp, 0, vp.size()-1);
    HELPERS::sleep(1000);
    cwin.clear();
    
    selection_sortx(copy1);
    HELPERS::sleep(1000);
    cwin.clear();
    
    merge_sort(copy2, 0, copy2.size()-1);
    HELPERS::sleep(1000);
    cwin.clear();
    
    double val1 = 500, val2 = 0, val3 = -500;
    int pos1 = 0, pos2 = 0, pos3 = 0;
    Message m1, m2, m3;
    
    double sleeptime = 2000.0;
    current_process = "BINARY_SEARCH1";
    print_binary_search_results(vp, val1, pos1, "FOUND1", sleeptime);
    HELPERS::sleep(500);
    cwin.clear();
    
    current_process = "BINARY_SEARCH2";
    print_binary_search_results(vp, val2, pos2, "FOUND2", sleeptime);
    HELPERS::sleep(500);
    cwin.clear();
    
    current_process = "BINARY_SEARCH3";
    print_binary_search_results(vp, val3, pos3, "FOUND3", sleeptime);
    HELPERS::sleep(500);
    cwin.clear();
    
    return 0;
}

int partitionx(vector<Point> &v, int from, int to){
    int pivot = v[from].get_x();
    int i = from-1;
    int j = to+1;
    while (i < j){
        i++; while (v[i].get_x() < pivot) i++;
        j--; while (v[j].get_x() > pivot) j--;
        if (i < j) {
            int temp = v[i].get_x();
            v[i] = Point(v[j].get_x(), v[i].get_y());
            v[j] = Point(temp, v[j].get_y());
        }
    } return j;
}
void quicksortx(vector<Point> &v, int from, int to){
    cwin.clear();
    Message m(topleft, "QUICKSORT");
    cwin << m;
    print_vector_points(v);
    if (from >= to) return;
    int p = partitionx(v, from, to);
    quicksortx(v, from, p);
    quicksortx(v, p+1, to);
}
int min_position(vector<Point>& v, int from, int to){
    int min_pos = from;
    int i;
    for (i = from + 1; i <= to; i++)
        if (v[i].get_x() < v[min_pos].get_x()) min_pos = i;
    return min_pos;
}
void selection_sortx(vector<Point> &v){
    int next;
    for (next = 0; next < v.size()-1; next++){
        int min_pos = min_position(v, next, v.size()-1);
        if (min_pos != next){
            cwin.clear();
            Message m(topleft, "SELECTION SORT");
            cwin << m;
            vector<Point> v_copy = v;
            //print_vector_points(v_copy);
            v_copy.clear();
            int temp = v[next].get_x();
            v[next] = Point(v[min_pos].get_x(), v[next].get_y());
            v[min_pos] = Point(temp, v[min_pos].get_y());
            print_vector_points(v);
        }
    }
}
void merge(vector<Point>& v, int from, int mid, int to){
    vector<Point> z = HELPERS::get_subvector(v, from, to);

    int i1 = from;
    int i2 = mid+1;
    int j = 0;
    while (i1 <= mid && i2 <= to){
        if (v[i1].get_x() < v[i2].get_x()){
            z[j] = Point(v[i1].get_x(), z[j].get_y());
            i1++;
        } else{
            z[j] = Point(v[i2].get_x(), z[j].get_y());
            i2++;
        }
        j++;
    }
    while (i1 <= mid){
        z[j] = Point(v[i1].get_x(), z[j].get_y());
        i1++;
        j++;
    }
    while (i2 <= to){
        z[j] = Point(v[i2].get_x(), z[j].get_y());
        i2++;
        j++;
    }
    for (j = 0; j < z.size(); j++){
        v[from + j] = z[j];
        cwin.clear();
        Message m(topleft, "MERGE_SORT");
        cwin << m;
        HELPERS::print_vector_points(v);
    }
}
void merge_sort(vector<Point> &v, int from, int to){
    if (from == to) return;
    int mid = (from + to) / 2;
    merge_sort(v, from, mid);
    merge_sort(v, mid+1, to);
    merge(v, from, mid, to);
}
void print_binary_search_results(vector<Point> v, double val, int& pos, string result_name, double sleeptime){
    double bs_sleeptime = sleeptime/4.0;
    bool found = binary_search(v, 0, v.size()-1, val, pos, bs_sleeptime);
    
    Message bs(topleft, current_process);
    cwin << bs;
    
    Point msg_point = v[pos];
    
    string printstring1 = result_name + " == true";
    Message m;
    bool move_left = false, move_right = false;
    if (found){
        string printstring2 = "vp[";
        ostringstream oss;
        oss << pos;
        oss << "] = (";
        oss << v[pos].get_x();
        oss << ", ";
        oss << v[pos].get_y();
        oss << ")";
        printstring2 += oss.str();
        if (v[pos].get_x() >= 800){
            move_left = true;
            msg_point.move(-200, 0);
        } else if (v[pos].get_x() <= -800){
            move_right = true;
            msg_point.move(200, 0);
        }
        m = Message(msg_point, printstring1);
        cwin << m;
        msg_point.move(0, -35);
        m = Message(msg_point, printstring2);
        cwin << m;
        msg_point.move(35, 0);
        if (move_right) msg_point.move(-200.0, 0.0);
        else if (move_left) msg_point.move(200.0, 0.0);
    }
    else {
        printstring1 = "Closest value to (x == ";
        ostringstream oss;
        oss << val;
        oss << ")";
        printstring1 += oss.str();
        oss.str("");
        string printstring2;
        oss << "is v[";
        oss << pos;
        oss << "]: (";
        oss << v[pos].get_x();
        oss << ", ";
        oss << v[pos].get_y();
        oss << ")";
        printstring2 = oss.str();
        if (v[pos].get_x() >= 800.0){
            move_left = true;
            msg_point.move(-200.0, 0.0);
        } else if (v[pos].get_x() <= -800.0){
            move_right = true;
            msg_point.move(200.0, 0.0);
        }
        m = Message(msg_point, printstring1);
        cwin << m;
        msg_point.move(0, -35);
        m = Message(msg_point, printstring2);
        cwin << m;
        msg_point.move(0, 35);
        if (move_right) msg_point.move(-200.0, 0.0);
        else if (move_left) msg_point.move(200.0, 0.0);
    }
    HELPERS::sleep(sleeptime);
}
bool binary_search(vector<Point> v, int from, int to, double val, int& pos, double sleeptime){
    if (from > to){
        pos = from;
        return false;
    }
    int mid = (from + to) / 2;
    
    cwin.clear();
    Message bs(topleft, current_process);
    cwin << bs;
    HELPERS::print_vector_points(v, from, to);
    HELPERS::sleep(sleeptime);
    
    if (static_cast<int>(v[mid].get_x()) == static_cast<int>(val)){
        pos = mid;
        return true;
    }
    else if (static_cast<int>(v[mid].get_x()) < static_cast<int>(val)) return binary_search(v, mid+1, to, val, pos, sleeptime);
    else return binary_search(v, from, mid-1, val, pos, sleeptime);
}










