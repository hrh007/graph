#ifndef GRAPH_ALGORITHM_OPERATIONS_HPP
#define GRAPH_ALGORITHM_OPERATIONS_HPP
#include "predicates.hpp"
#include "../graph.hpp"
#include<string>
namespace graph
{
    template<typename Graph>
    Graph Union(Graph g1,Graph g2)
    {
        Graph result;
        for(auto i=g1.begin();i!=g1.end();++i)
            result.insertVertex(i->first);
        for(auto i=g2.begin();i!=g2.end();++i)
            result.insertVertex(i->first);
        for(auto i=g1.begin();i!=g1.end();++i)
            for(auto j=g1.nbegin(i->first);j!=g1.nend(i->first);++j)
                result.insertEdge(i->first,j->first,j->second);
        for(auto i=g2.begin();i!=g2.end();++i)
            for(auto j=g2.nbegin(i->first);j!=g2.nend(i->first);++j)
                if(!isAdjacent(result,i->first,j->first))
                    result.insertEdge(i->first,j->first,j->second);
                        
        return result;
    }
    
    template<typename Graph>
    Graph intersection(Graph g1,Graph g2)
    {
        Graph result;
        for(auto i=g1.begin();i!=g1.end();++i)
            if(isVertex(g2,i->first))
                result.insertVertex(i->first);
        for(auto i=result.begin();i!=result.end();++i)
            for(auto j=g1.nbegin(i->first);j!=g1.nend(i->first);++j)
                if(isAdjacent(g2,i->first,j->first))
                    if(!isAdjacent(result,i->first,j->first))
                        result.insertEdge(i->first,j->first,1);
                        
        return result;
    }
    
    template<typename Graph>
    Graph join(Graph g1,Graph g2)
    {
        Graph result=Union(g1,g2);
        for(auto i=g1.begin();i!=g1.end();++i)
            for(auto j=g2.begin();j!=g2.end();++j)
                result.insertEdge(i->first,j->first,1);
         
        return result;
    }
    
    template<typename Graph>
    Graph symmetric_difference(Graph g1,Graph g2)
    {
        Graph result;
        for(auto i=g1.begin();i!=g1.end();++i)
            if(!isVertex(g2,i->first))
                result.insertVertex(i->first);
        for(auto i=g2.begin();i!=g2.end();++i)
            if(!isVertex(g1,i->first))
                result.insertVertex(i->first);
        
        for(auto i=g1.begin();i!=g1.end();++i)
            for(auto j=g1.nbegin(i->first);j!=g1.nend(i->first);++j)
                if(isVertex(result,i->first) && isVertex(result,j->first))
                    if(!isAdjacent(g2,i->first,j->first))
                        result.insertEdge(i->first,j->first,j->second);
        for(auto i=g2.begin();i!=g2.end();++i)
            for(auto j=g2.nbegin(i->first);j!=g2.nend(i->first);++j)
                if(isVertex(result,i->first) && isVertex(result,j->first))
                    if(!isAdjacent(g1,i->first,j->first))
                        result.insertEdge(i->first,j->first,j->second);
                    
        return result;
    }
    
    std::string first(std::string s) { return s.substr(0,s.find('-')); }
    std::string second(std::string s) { return s.substr(s.find('-')+1); }
    template<typename Graph>
    Graph cartesian_product(Graph g1,Graph g2)
    {
        Graph result;
        for(auto i=g1.begin();i!=g1.end();++i)
            for(auto j=g2.begin();j!=g2.end();++j)
                result.insertVertex(i->first+"-"+j->first);
        for(auto i=result.begin();i!=result.end();++i)
            for(auto j=result.begin();j!=result.end();++j)
                if(i->first!=j->first)
                    if( (first(i->first)==first(j->first)&&isAdjacent(g2,second(i->first),second(j->first))) || (second(i->first)==second(j->first)&&isAdjacent(g1,first(i->first),first(j->first))) )
                        if(!isAdjacent(result,i->first,j->first))
                            result.insertEdge(i->first,j->first,1);
        
        return result;
    }
    
    template<typename Graph>
    Graph complement(Graph g1)
    {
        Graph result;
        for(auto i=g1.begin();i!=g1.end();++i)
            result.insertVertex(i->first);
        for(auto i=g1.begin();i!=g1.end();++i)
            for (auto j=g1.begin();j!=g1.end();++j)
                if(i->first!=j->first && !(isAdjacent(g1,i->first,j->first)))
                    result.insertEdge(i->first,j->first,1);
                
        return result;
    }
    template<typename Graph>
    Graph EdgeDeletionSubgraph(Graph g1, typename Graph::VertexType x, typename Graph::VertexType  y)
    {
        g1.removeEdge(x,y);
                
        return g1;
    }
    template<typename Graph>
    Graph VertexDeletionSubgraph(Graph g1, typename Graph::VertexType x)
    {
        g1.removeVertex(x);
                
        return g1;
    }
}
#endif
