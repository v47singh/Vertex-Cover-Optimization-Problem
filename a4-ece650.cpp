#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>
#include "minisat/core/Solver.h"
#include <vector>
#include <set>
#include <list>
using namespace std;

unsigned int n;

struct EdgeS
{
    unsigned v1,v2;
};

typedef std::vector<unsigned> VertexVec;
typedef std::list<unsigned > ListofVertex;
typedef std::vector<ListofVertex> AdjacencyList;
vector<unsigned int> FinalVertices;
vector<unsigned int> FinalEdges;

string input;

struct GraphS
{
    std::size_t number_of_edges;
    AdjacencyList adjacency;

    void initialize(unsigned num_of_vertices);
    void add(EdgeS e);
    void clear(unsigned v);
};

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


void Source_Destination(GraphS &GP)
{
    GP.initialize(n);
    unsigned int s,d;
    for(unsigned int a=1; a<FinalEdges.size(); a=a+2)
       {
           s=FinalEdges[a-1];
           d=FinalEdges[a];
           GP.add({s,d});
       }
}



void Min_Vertex_Cover(GraphS &Graph)
{
    GraphS &graph_input = Graph;
    VertexVec &C = *new VertexVec();


    unsigned int k = 0;
    bool res;
    unsigned int high=graph_input.adjacency.size();
    unsigned int low=0;
    k=(low+high)/2;
    while (low<=high)
    {

        std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
        std::vector<std::vector<Minisat::Lit>> nk_matrix(graph_input.adjacency.size());
        for (unsigned int i = 0; i < graph_input.adjacency.size(); i++)
            for (unsigned int j = 0; j < k; j++) {
                Minisat::Lit l = Minisat::mkLit(solver->newVar());
                nk_matrix[i].push_back(l);
            }

        for (unsigned int i = 0; i < k; i++) {
            Minisat::vec<Minisat::Lit> save_literal;
            for (unsigned int j = 0; j < graph_input.adjacency.size(); j++) {
                save_literal.push(nk_matrix[j][i]);
            }
            solver->addClause(save_literal);
        }

        for (unsigned int m = 0; m < graph_input.adjacency.size(); m++)
            for (unsigned int p = 0; p < k; p++)
                for (unsigned int q = p + 1; q < k; q++) {
                    solver->addClause(~nk_matrix[m][p], ~nk_matrix[m][q]);
                }

        for (unsigned int m = 0; m < k; m++)
            for (unsigned int p = 0; p < graph_input.adjacency.size(); p++)
                for (unsigned int q = p + 1; q < graph_input.adjacency.size(); q++) {
                    solver->addClause(~nk_matrix[p][m], ~nk_matrix[q][m]);
                }

        for(unsigned v1 = 0 ; v1 < graph_input.adjacency.size(); ++v1) {
            for (auto v2 : graph_input.adjacency[v1]) {
                if(v2 < v1) continue;
                Minisat::vec<Minisat::Lit> edge_lit;
                for (unsigned int w = 0; w < k; w++) {
                    edge_lit.push(nk_matrix[v1][w]);
                    edge_lit.push(nk_matrix[v2][w]);
                }

                solver->addClause(edge_lit);
            }
        }
        res = solver->solve();
        if (res )
        {
            C.clear();
            for ( unsigned int i = 0; i < graph_input.adjacency.size(); i++)
                for ( unsigned int j =0; j < k; j++)
                    if ( Minisat::toInt(solver->modelValue(nk_matrix[i][j])) == 0)
                    {
                        C.push_back(i);
                    }
            high=k-1;
        }
        else
        {
            solver.reset(new Minisat::Solver());
            low=k+1;
        }
        k=(low+high)/2;
    }
    std::sort( C.begin(), C.end(), std::less<int>());
    for (unsigned j=0; j < C.size(); j++)
        {
            std::cout<<C[j];
            if(j + 1 != C.size())
                {
                   std::cout<<' ';
                }
        }
        std::cout<<std::endl;

}

void Edges()
{

    GraphS &graph_input = *new GraphS();
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
 Source_Destination(graph_input);

 Min_Vertex_Cover(graph_input);

}

using std::toupper;
void GraphS::initialize(unsigned n)
{
    adjacency.clear();
    adjacency.resize(n,{});
}

void GraphS::add(EdgeS e)
{
    auto &l1 = adjacency[e.v1];
    auto &l2 = adjacency[e.v2];
    l1.push_back(e.v2);
    l2.push_back(e.v1);

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
    }
    return 0;
}
