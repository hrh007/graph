//expected output 112347891011113
#include "../graph.hpp"
#include "../util/generate.hpp"
#include "../algorithm/sssp.hpp"
#include <iostream>
using namespace graph;
int main()
{
   auto g = graph::gen::cycle({10});
   auto s = graph::Djikstra(g,1);
   auto p = s.getParentArray();
   for(auto i=g.begin();i!=g.end();++i)
   {
     std::cout<<p[i->first];
   }
   Graph <int, int> g5(true);
    g5.insertVertex(1);
    g5.insertVertex(2);
    g5.insertVertex(3);
    g5.insertVertex(4);
    g5.insertEdge(1,2,7);
    g5.insertEdge(2,3,3);
    g5.insertEdge(3,4,6);
    g5.insertEdge(4,1,2);
    g5.insertEdge(1,3,1);
    g5.insertEdge(2,4,1);
   auto s1 = graph::BellmanFord(g5,1);
   auto p1 = s1.getParentArray();
   for(auto i=g5.begin();i!=g5.end();++i)
   {
     std::cout<<p1[i->first];
   }
}
