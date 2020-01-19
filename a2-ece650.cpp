#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#define MAX   (~(0x1<<31))

using namespace std;

string input;

vector<vector<unsigned int> > adj;
vector<unsigned int> FinalVertices;
vector<unsigned int> FinalEdges;
vector<unsigned int> FinalSD;
vector<unsigned int> shortest_path;

unsigned int Source, Destination, n;


void Vertex()
{
    FinalVertices.clear();
    FinalEdges.clear();

    std::vector<std::string> b;
     std::size_t prev_pos = 0, pos;
         while ((pos = input.find_first_of(" ", prev_pos)) != std::string::npos)
         {
            if (pos > prev_pos)
              b.push_back(input.substr(prev_pos, pos-prev_pos));
            prev_pos= pos+1;
         }
        if (prev_pos< input.length())
            b.push_back(input.substr(prev_pos, std::string::npos));

    for (auto &s : b)
    {
        std::stringstream parser(s);
        unsigned int v = 0;

        parser >> v;

        FinalVertices.push_back(v);
    }

    n=FinalVertices[1];

}

void initialize_adj()
{
    unsigned int a = FinalVertices[1];
    adj.resize(a);
    for (auto &i:adj)
    {
        i.resize(a,MAX);
    }
}

void calc_adjacency_matrix(unsigned int a,unsigned int b)
{
    adj[a][b]=1;
    adj[b][a]=1;
}

void Source_Destination()
{
    initialize_adj();

    unsigned int s,d;
    for(unsigned int a=1; a<FinalEdges.size(); a=a+2)
       {
           s=FinalEdges[a-1];
           d=FinalEdges[a];
           calc_adjacency_matrix(s,d);

       }
}

void Edges()
{
    adj.clear();
    vector<string> b;
     std::size_t prev_pos = 0, pos;
         while ((pos = input.find_first_of("{<,>}", prev_pos)) != std::string::npos)
         {
            if (pos > prev_pos)
              b.push_back(input.substr(prev_pos, pos-prev_pos));
            prev_pos= pos+1;
         }
        if (prev_pos< input.length())
            b.push_back(input.substr(prev_pos, std::string::npos));
    vector<unsigned int> outEdges;

    for (auto &s : b)
    {
        std::stringstream parser(s);
        unsigned int e = 0;

        parser >> e;
        outEdges.push_back(e);
    }

    unsigned int chk=0;
    for (unsigned int i=1; i<outEdges.size(); i++)
    {
        if(outEdges[i]>=0 && outEdges[i]<n)
        {
            FinalEdges.push_back(outEdges[i]);
        }
       else{
        chk=1;
       }
    }

    if(chk==1)
    {
        cout<<"Error: Edges out of range"<<endl;
    }

    Source_Destination();
}

void Source_and_Destination()
{

    FinalSD.clear();

    vector<string> sd;
    std::size_t prev_pos = 0, pos;

        while ((pos = input.find_first_of(" ", prev_pos)) != std::string::npos)
        {
            if (pos > prev_pos)
              sd.push_back(input.substr(prev_pos, pos-prev_pos));
            prev_pos= pos+1;
        }
        if (prev_pos< input.length())
            sd.push_back(input.substr(prev_pos, std::string::npos));


    for (auto &s : sd)
    {
        std::stringstream parser(s);
        unsigned int t = 0;

        parser >> t;

        FinalSD.push_back(t);
    }

    Source = FinalSD[1];
    Destination = FinalSD[2];

}

void print_shortest_path(unsigned int S,unsigned int D)
{

    if (S >= n|| D >=n)
    {
        cout<<"Error: Vertex out of range"<<endl;
    }
    else
    {
        unsigned int new_distance;
        unsigned int check[n];

        unsigned int distance[n];
        shortest_path.clear();


        for (unsigned int q = 0; q < n; q++)
        {
            check[q] = 0;
            distance[q] = adj[S][q];

        }

        check[S] = 1;
        distance[S] = 0;

        for (unsigned int i = 1; i < n; i++)
        {

            unsigned int min = MAX;
            unsigned int c = 0;
            for (unsigned int p = 0; p < n; p++) {
                if (check[p] == 0 && distance[p] < min)
                {
                    min = distance[p];
                    c = p;
                }
            }

            check[c] = 1;

            for (unsigned int b = 0; b < n; b++)
            {
                new_distance = (adj[c][b] == MAX ? MAX : (min + adj[c][b]));
                if (check[b] == 0 && (new_distance < distance[b]))
                {
                    distance[b] = new_distance;
                }
            }
        }

        if (distance[D] == MAX)
        {
            cout<<"Error: No path exists between these vertices."<<endl;
        }
        else
        {
        unsigned int node = D;
        while (distance[node] > 0)
        {
            shortest_path.push_back(node);

            for(size_t a = 0; a<n; ++a)
            {
                if(adj[node][a] < MAX &&
                   distance[a] + adj[node][a] == distance[node])
                {
                    node = a;
                    break;
                }
            }
        }

        shortest_path.push_back(node);

        for (auto m = shortest_path.rbegin(); m != shortest_path.rend(); m++)
        {
            cout << *m;
            if (m != shortest_path.rend() - 1)
            {
                cout << "-";
            }
            else
            {
                cout << "\n";
            }
        }
      }
   }
}


int main()
{
    while(getline(cin,input))
    {

        if(input[0]=='v' || input[0]=='V')
        {
            Vertex();

        }
        else if(input[0]=='e' || input[0]=='E')
        {

            Edges();

        }
        else if(input[0]=='s' || input[0]=='S')
        {

            Source_and_Destination();
            print_shortest_path(Source, Destination);

        }
    }
    return 0;
}
