/*
 *
 * Copyright (C) 2011 Christian Brandt
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#include "graph/graph.hpp"
#include "graph/edge.hpp"
#include "graph/node.hpp"

namespace Gamera { namespace GraphApi {



// -----------------------------------------------------------------------------
Graph::Graph(bool directed, bool check_on_insert) {
   _flags = FLAG_FREE; //flag free as default flags
   if(directed)
      GRAPH_SET_FLAG(this, FLAG_DIRECTED);
   else
      GRAPH_UNSET_FLAG(this, FLAG_DIRECTED);

   if(check_on_insert)
      GRAPH_SET_FLAG(this, FLAG_CHECK_ON_INSERT);
   else
      GRAPH_UNSET_FLAG(this, FLAG_CHECK_ON_INSERT);
   _colorhistogram = nullptr;
   _colors = nullptr;

}



// -----------------------------------------------------------------------------
Graph::Graph(flag_t flags) {
   if(flags == FLAG_TREE) {
      UNSET_FLAG(flags, FLAG_DIRECTED);
      UNSET_FLAG(flags, FLAG_CYCLIC);
   }
   else if(flags == FLAG_BLOB) {
      SET_FLAG(flags, FLAG_CYCLIC);
   }
   if(!HAS_FLAG(flags, FLAG_CYCLIC)) {
      UNSET_FLAG(flags, FLAG_MULTI_CONNECTED);
      UNSET_FLAG(flags, FLAG_SELF_CONNECTED);
   }
   _flags = flags;

   _colorhistogram = nullptr;
   _colors = nullptr;
}




// -----------------------------------------------------------------------------
/** 
  * deletes all edges and nodes when deleting the whole graph
  */
Graph::~Graph() {
	size_t edgecount = 0, nodecount = 0;
	for (Edge* _edge : _edges) {
		delete _edge;
		edgecount++;
	}
	
	for (Node* _node : _nodes) {
		delete _node;
		nodecount++;
	}
	
	assert(nodecount == _nodes.size());
	assert(edgecount == _edges.size());
	
	_edges.clear();
	_nodes.clear();
	_valuemap.clear();
	
	delete _colors;
	
	delete _colorhistogram;
}



// -----------------------------------------------------------------------------
/**
  * copies the whole graph as a deep copy
  */
Graph::Graph(Graph &g) {
   _colors = nullptr;
   _colorhistogram = nullptr;
   _flags = g._flags;
   NodePtrIterator *nit = g.get_nodes();
   Node *n;
   while((n=nit->next()) != nullptr)
      add_node(n->_value);

   delete nit;
   EdgePtrIterator *eit = g.get_edges();
   Edge *e;
   while((e=eit->next()) != nullptr) {
      add_edge(e->from_node->_value, e->to_node->_value, e->weight,
            e->is_directed, e->label);
   }
   delete eit;
}



// -----------------------------------------------------------------------------
Graph::Graph(Graph* g, flag_t flags) {
   _colors = nullptr;
   _colorhistogram = nullptr;
   _flags = flags;
   bool directed = GRAPH_HAS_FLAG(g, FLAG_DIRECTED);
   NodePtrIterator *nit = g->get_nodes();
   Node *n;
   while((n=nit->next()) != nullptr)
      add_node(n->_value->copy());

   delete nit;
   EdgePtrIterator *eit = g->get_edges();
   Edge *e;
   if(!directed) {
      while((e=eit->next()) != nullptr) {
         add_edge(e->from_node->_value, e->to_node->_value, e->weight,
            e->is_directed, e->label);
      }
   }
   else {
      while((e=eit->next()) != nullptr) {
         add_edge(e->from_node->_value, e->to_node->_value, e->weight,
            false, e->label);
      }
   }
   delete eit;
}



// -----------------------------------------------------------------------------
// methods for nodes
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/**
 * returns true when graph has a node with same value as the given Node.
 */

bool Graph::has_node(Node* node) {
    return has_node(node->_value);
}

// -----------------------------------------------------------------------------
bool Graph::has_node(GraphData * value) {
   return _valuemap.find(value) != _valuemap.end();
}


// -----------------------------------------------------------------------------
/**
  * a new node is created and added using add_node
  */
bool Graph::add_node(GraphData * value) {
   Node* toadd = new Node(value);
   if(!add_node(toadd)) {
      delete toadd;
      return false;
   }
   else {
       return true;
   }
}



// -----------------------------------------------------------------------------
/**
   a Node is added in following steps
   - assign value to node
   - check if value is already present in graph
   - set node's graph
   - add node to graph's nodelist
   - add node's value to graph's valuemap
   */
bool Graph::add_node(Node* node) {
   if(!has_node(node)) {
      node->add_to_graph(this);
      _nodes.push_back(node);
      _valuemap[node->_value] = node;
      return true;
   }
   else { //already in list
      return false;
   }
}



// -----------------------------------------------------------------------------
Node* Graph::add_node_ptr(GraphData * value) {
   Node* n = get_node(value);
   if(n == nullptr) {
      n = new Node(value);
      if(!add_node(n)) {
         delete n;
         n = nullptr;
      }
   }
   return n;
}



// -----------------------------------------------------------------------------
/**
   Parameter: NodeVector of nodes which should be added 
   returns count of added nodes
 */
int Graph::add_nodes(const NodeVector& nodes) {
   int count = 0;
   for(Node* node : nodes) {
      if(add_node(node))
         count++;
   }
   return count;
}



// -----------------------------------------------------------------------------
/** Parameter: ValueVector of values which should be added
  returns count of added nodes
  */
int Graph::add_nodes(const ValueVector& values) {
   int count = 0;
   for(GraphData* value : values) {
      if(add_node(value))
         count++;
   }
   return count;
}



// -----------------------------------------------------------------------------
Node* Graph::get_node(GraphData * value) {
	ValueNodeMap::iterator it = _valuemap.find(value);
   if(it == _valuemap.end())
      return nullptr;
   else
      return it->second;
}



// -----------------------------------------------------------------------------
NodePtrIterator* Graph::get_nodes() {
   NodePtrIterator* it= new NodePtrIterator(this, _nodes.begin(), _nodes.end());
   return it;
}



// -----------------------------------------------------------------------------
/** removes a node glueing all edges together */
void Graph::remove_node(Node* node) {
   if(node != nullptr) {
      node->remove_self(true);
      _nodes.remove(node);
      _valuemap.erase(node->_value);
      delete node;
   }
   else {
      throw std::runtime_error("some error occurred: Null pointer to node");
   }
}



// -----------------------------------------------------------------------------
void Graph::remove_node(GraphData * value) {
   Node* node = get_node(value);
   if (node != nullptr)
      remove_node(node);
   else
      throw std::runtime_error("node not present");
}



// -----------------------------------------------------------------------------
/**
  * removes a node not glueing all edges together
  */
void Graph::remove_node_and_edges(Node* node) {
   if(node != nullptr) {
      node->remove_self(false);
      _nodes.remove(node);
      _valuemap.erase(node->_value);
      delete node;
   }
}



// -----------------------------------------------------------------------------
void Graph::remove_node_and_edges(GraphData * value) {
   Node* node = get_node(value);
   if (node != nullptr)
     remove_node_and_edges(node);
}



// -----------------------------------------------------------------------------
int Graph::add_edge(GraphData * from_value, GraphData * to_value, cost_t cost,
      bool directed, void* label) {
   Node *from_node, *to_node;

   from_node = add_node_ptr(from_value);
   to_node = add_node_ptr(to_value);

   return add_edge(from_node, to_node, cost, directed, label);
}



// -----------------------------------------------------------------------------
int Graph::add_edge(Node* from_node, Node* to_node, cost_t cost,
      bool directed, void* label) {
   Edge *e = nullptr, *f = nullptr;
   unsigned long count = 0;
   if (from_node == nullptr || to_node == nullptr)
      return 0;

   if(!GRAPH_HAS_FLAG(this, FLAG_DIRECTED) && directed)
      throw std::invalid_argument("Cannot insert directed edge into "
                                    "undirected graph.");

   if(GRAPH_HAS_FLAG(this, FLAG_DIRECTED) && !directed) {
      directed = true;
      f = new Edge(to_node, from_node, cost, true, label);
      _edges.push_back(f);
      if(GRAPH_HAS_FLAG(this, FLAG_CHECK_ON_INSERT) &&
            !conforms_restrictions()) {
         remove_edge(f);
         f = nullptr;
      }
      else
         count++;
   }

   e = new Edge(from_node, to_node, cost, directed, label);
   _edges.push_back(e);

   if(GRAPH_HAS_FLAG(this, FLAG_CHECK_ON_INSERT) &&
         !conforms_restrictions()) {
        remove_edge(e);
        e = nullptr;
   }
   else
      count++;

   return count;
}



// -----------------------------------------------------------------------------
EdgePtrIterator *Graph::get_edges() {
   EdgePtrIterator* it= new EdgePtrIterator(this, _edges.begin(), _edges.end());
   return it;
}



// -----------------------------------------------------------------------------
bool Graph::has_edge(GraphData * from_value, GraphData * to_value) {
   Node* from_node = get_node(from_value);
   Node* to_node = get_node(to_value);
   return has_edge(from_node, to_node);
}



// -----------------------------------------------------------------------------
bool Graph::has_edge(Node* from_node, Node* to_node) {
   if(from_node == nullptr || to_node == nullptr)
      return false;
   if(!is_directed())
      return from_node->has_edge_to(to_node) || to_node->has_edge_to(from_node);
   else
      return from_node->has_edge_to(to_node);
}



// -----------------------------------------------------------------------------
void Graph::remove_edge(GraphData * from_value, GraphData * to_value) {
   Node* from_node = get_node(from_value);
   Node* to_node = get_node(to_value);
   remove_edge(from_node, to_node);
}



// -----------------------------------------------------------------------------
void Graph::remove_edge(Node* from_node, Node* to_node) {
   unsigned long count = 0;
   EdgeVector to_remove;
   for(Edge* e : _edges) {
      if(e->to_node == to_node && e->from_node == from_node) {
         to_remove.push_back(e);
      }
      else if(is_undirected() && e->from_node == to_node &&
            e->to_node == from_node) {

         to_remove.push_back(e);
      }
   }

   for(Edge* it : to_remove) {
      remove_edge(it);
      count++;
   }

   if(count == 0)
      throw std::runtime_error("There is no edge with given nodes in this graph.");
}



// -----------------------------------------------------------------------------
void Graph::remove_edge(Edge* edge) {
   edge->remove_self();
//   int count = _edges.size();
   _edges.remove(edge);
//   assert(_edges.size() < count);
   delete edge;
}



// -----------------------------------------------------------------------------
void Graph::remove_all_edges() {
   //not calling remove_edge because this would take O ( e*ln(e)*ln(e) )
   //doing it this way takes only O(e * ln(e))
   for(Edge* _edge : _edges) {
      _edge->remove_self();
      delete _edge;
   }
   _edges.clear();
}



}} // end Gamera::GraphApi

