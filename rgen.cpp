#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;
namespace patch
{
    template < typename T > std::string to_string( const T& a )
    {
        std::ostringstream s ;
        s << a ;
        return s.str() ;
    }
}


unsigned int StreetNumber ( unsigned int p)
{

    std::ifstream urandom("/dev/urandom");

    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int ran = 3;
    urandom.read((char*)&ran, sizeof(unsigned int));
    ran = ran % (p-2+1) +2;
    urandom.close();
    return (unsigned int) ran;

}

unsigned int LineSegmentNumber(unsigned int q)
{

    std::ifstream urandom("/dev/urandom");


    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int ran = 3;
    urandom.read((char*)&ran, sizeof(unsigned int));
    ran = ran % (q-1+1) + 1;
    urandom.close();
    return (unsigned int) ran;


}

unsigned int WaitingTime (unsigned int r)
{

    std::ifstream urandom("/dev/urandom");


    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int t = 3;
    urandom.read((char*)&t, sizeof(unsigned int));
    t = t % (r-5+1) + 5;
    urandom.close();
    return (unsigned int) t;


}

int value_of_coordinate (unsigned int s)
{

    std::ifstream urandom("/dev/urandom");


    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int ran = 3;
    urandom.read((char*)&ran, sizeof(int));
    ran = ran % (s+s);
    int o = ran - s ;
    urandom.close();
    return o;


}

void Name_of_street( vector<string> &street , unsigned int StreetNumber)
{
    string nm = "a";
    for (unsigned int i=0; i < StreetNumber; i++)
    {
        street.push_back(nm);
        nm = nm +'a';
    }

}

int Maximum_of_XY( int x1, int x2)
{

    int m1;
    if ( x1 > x2)
    {
        m1 = x1;
        return m1;
    }
    m1 = x2;
    return m1;

}

int Minimum_of_XY( int x1, int x2)
{

    int m1;
    if ( x1 > x2)
    {
        m1 = x2;
        return m1;
    }

    m1 = x1;
    return m1;

}



bool Checking_Intersection( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    double xnum, xden, xcoor, ynum, yden, ycoor;

    xnum = ((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4));
    xden = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4));
    xcoor =  xnum / xden;

    ynum = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4);
    yden = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
    ycoor = ynum / yden;

    int min_x1, min_x2, max_x1, max_x2, min_y1, min_y2, max_y1, max_y2;

    min_x1 = Minimum_of_XY(x1,x2);
    max_x1 = Maximum_of_XY(x1,x2);
    min_x2 = Minimum_of_XY(x3,x4);
    max_x2 = Maximum_of_XY(x3,x4);
    min_y1 = Minimum_of_XY(y1,y2);
    max_y1 = Maximum_of_XY(y1,y2);
    min_y2 = Minimum_of_XY(y3,y4);
    max_y2 = Maximum_of_XY(y3,y4);

    if ( min_x1<= xcoor &&  xcoor <= max_x1)
        if ( min_x2 <= xcoor && xcoor <= max_x2)
            if ( min_y1 <= ycoor && ycoor <= max_y1)
                if ( min_y2 <= ycoor && ycoor <= max_y2)
                    return true;
    return false;

}



bool CheckPoint ( vector<int> coordinate, int x, int y)
{
    int s = coordinate.size();
    if ( coordinate.empty())
    {

        return true;
    }if ( s == 2)
    {
        if (( x == coordinate[0]) && (y == coordinate[1]) )
        {

            return false;
        }

        return true;
    }
    else
    {

        for (unsigned int i = 0; i < coordinate.size(); i = i + 2){
            if (x == coordinate[i] && y == coordinate[i+1]){
                return false;
            }
        }

        double k1, k2;

        if ( x == coordinate[s-2] && x == coordinate[s-4])
            return false;


        if ( (x == coordinate[s-2]) && (x != coordinate[s-4]))
        {
            if ( s == 4)
                return true;
            else
            {
                for ( int i = s-3; i >=2; i = i-2 )
                {
                    if ( Checking_Intersection(x,y,coordinate[s-2],coordinate[s-1],coordinate[i-1],coordinate[i],coordinate[i-3],coordinate[i-2]))
                        return false;

                }

                return true;
            }
        }

        if ( (coordinate[s-4] == coordinate[s-2]) && (x != coordinate[s-2]))
        {
            if ( s == 4)
                return true;
            else
            {
                for ( int i = s-3; i >=0; i = i-2 )
                {
                    if ( Checking_Intersection(x,y,coordinate[s-2],coordinate[s-1],coordinate[i-1],coordinate[i],coordinate[i-3],coordinate[i-2]))
                        return false;

                }

                return true;
            }
        }

        k1 = ((y - coordinate[s-1]) / (x-coordinate[s-2]));
        k2 = ((coordinate[s-1]) - coordinate[s-3]) / (coordinate[s-2]-coordinate[s-4]);

        if (k1 == k2)
            return false;

        else
        {

            if ( s == 4)
                return true;
            else
            {
                for ( int i = s-3; i >=0; i = i-2 )
                {
                    if ( Checking_Intersection(x,y,coordinate[s-2],coordinate[s-1],coordinate[i-1],coordinate[i],coordinate[i-3],coordinate[i-2]))
                        return false;

                }

                return true;
            }

        }


    }

}





int main (int argc, char **argv) {

    std::string svalue, nvalue, lvalue, cvalue;
    unsigned int S_intVal = 10, N_intVal = 5, L_intVal = 5, C_intVal = 20;
    int c;
    int s_num, l_num, x_cord, y_cord;
    unsigned int w_sed;

    vector<string> NameofStreet;
    vector<int> street_line_num;
    vector<int> coordinate;

    opterr = 0;

    while ((c = getopt(argc, argv, "s:n:l:c:")) != -1) {
        switch (c) {
            case 's':
                svalue = optarg;
                S_intVal = std::atoi(svalue.c_str());
                if (S_intVal < 2)
                {
                    cerr << "Error: the number is too small (after s)"<<endl;
                    exit(1);
                }

                break;
            case 'n':
                nvalue = optarg;
                N_intVal = std::atoi(nvalue.c_str());
                if (N_intVal < 1)
                {
                    cerr << "Error: the number is too small (after n)"<<endl;
                    exit(1);
                }

                break;
            case 'l':
                lvalue = optarg;
                L_intVal = std::atoi(lvalue.c_str());
                if (L_intVal < 5)
                {
                    cerr << "Error: the number is too small (after l)"<<endl;
                    exit(1);
                }

                break;
            case 'c':
                cvalue = optarg;
                C_intVal = std::atoi(cvalue.c_str());
                if (C_intVal < 1)
                {
                    cerr << "Error: the number is too small (after c)"<<endl;
                    exit(1);
                }

                break;

            case '?':
                if (optopt == 's') {
                    std::cerr << "Error: option -" << optopt
                              << " requires an argument." << std::endl;
                    break;
                }
                else if (optopt == 'n') {
                    std::cerr << "Error: option -" << optopt
                              << " requires an argument." << std::endl;
                    break;
                }
                else if (optopt == 'l') {
                    std::cerr << "Error: option -" << optopt
                              << " requires an argument." << std::endl;
                    break;
                }
                else if (optopt == 'c') {
                    std::cerr << "Error: option -" << optopt
                              << " requires an argument." << std::endl;
                    break;
                }

                else
                    std::cerr << "Error: unknown option: " << optopt << std::endl;
                    break;

        }


    }

    while (true)
    {

        if ( !NameofStreet.empty())
        {
            for(std::vector<string>::iterator it = NameofStreet.begin(); it != NameofStreet.end(); it++)
            {
                cout<<"r "<<'"'<<*it<<'"'<<endl;

            }

            NameofStreet.clear();
            street_line_num.clear();

        }

        s_num = StreetNumber(S_intVal);

        Name_of_street(NameofStreet, s_num);


        for (int j = 0; j < s_num; j++)
        {
            l_num = LineSegmentNumber(N_intVal);
            street_line_num.push_back(l_num);

        }

        int index = 0;

        for (unsigned int mk = 0; mk < street_line_num.size(); mk++)
        {
            coordinate.clear();
            int times = 0;
            int error = 0;
            while ( times < street_line_num[mk]+1 )
            {
                x_cord = value_of_coordinate(C_intVal);
                y_cord = value_of_coordinate(C_intVal);
                if (CheckPoint(coordinate, x_cord, y_cord))
                {
                    coordinate.push_back(x_cord);
                    coordinate.push_back(y_cord);
                    times++;
                    error = 0;
                }

                else
                {

                    if ( error == 25)
                    {
                        cerr<<"Error: failed to generate valid input for 25 simultaneous attempts"<<endl;
                        exit(1);
                    }

                    error++;
                }


            }

            string a_output;
            a_output = string("a \"") + NameofStreet[index] + "\" ";


            for (unsigned int mk = 0; mk < coordinate.size(); mk = mk+2)
            {
                string a,b;
                if (coordinate[mk]<0){
                  a = "-"+patch::to_string(coordinate[mk]*(-1));
                } else {
                  a = patch::to_string(coordinate[mk]);
                }
                if (coordinate[mk+1]<0){
                  b = "-"+patch::to_string(coordinate[mk+1]*(-1));
                } else {
                  b = patch::to_string(coordinate[mk+1]);
                }
                a_output = a_output + '('+ a + ','+ b +')';
            }

            cout<<a_output<<endl;

            index++;
        }


            cout<<'g'<<endl;
            w_sed = WaitingTime(L_intVal);
            usleep(w_sed*1000000);

        }

return 0;
}










