// file      : cult/containers/graph.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_CONTAINERS_GRAPH_HXX
#define CULT_CONTAINERS_GRAPH_HXX

#include <cult/types.hxx>
#include <cult/eh/exception.hxx>
#include <cult/containers/map.hxx>

namespace Cult
{
  namespace Containers
  {
    template <typename N, typename E>
    class Graph
    {
    public:
      typedef N Node;
      typedef E Edge;

      struct NoEdge: virtual EH::Exception {};
      struct NoNode: virtual EH::Exception {};

    public:
      template <typename T>
      T&
      new_node ();

      template <typename T, typename A0>
      T&
      new_node (A0 const&);

      template <typename T, typename A0, typename A1>
      T&
      new_node (A0 const&, A1 const&);

      template <typename T, typename A0, typename A1, typename A2>
      T&
      new_node (A0 const&, A1 const&, A2 const&);

      template <typename T, typename A0, typename A1, typename A2,
                typename A3>
      T&
      new_node (A0 const&, A1 const&, A2 const&, A3 const&);

      template <typename T, typename A0, typename A1, typename A2,
                typename A3, typename A4>
      T&
      new_node (A0 const&, A1 const&, A2 const&, A3 const&, A4 const&);

      template <typename T, typename A0, typename A1, typename A2,
                typename A3, typename A4, typename A5>
      T&
      new_node (A0 const&, A1 const&, A2 const&, A3 const&, A4 const&,
                A5 const&);

      template <typename T, typename A0, typename A1, typename A2,
                typename A3, typename A4, typename A5, typename A6>
      T&
      new_node (A0 const&, A1 const&, A2 const&, A3 const&, A4 const&,
                A5 const&, A6 const&);

      template <typename T, typename A0, typename A1, typename A2,
                typename A3, typename A4, typename A5, typename A6,
                typename A7>
      T&
      new_node (A0 const&, A1 const&, A2 const&, A3 const&, A4 const&,
                A5 const&, A6 const&, A7 const&);

      template <typename T, typename A0, typename A1, typename A2,
                typename A3, typename A4, typename A5, typename A6,
                typename A7, typename A8>
      T&
      new_node (A0 const&, A1 const&, A2 const&, A3 const&, A4 const&,
                A5 const&, A6 const&, A7 const&, A8 const&);

      template <typename T, typename A0, typename A1, typename A2,
                typename A3, typename A4, typename A5, typename A6,
                typename A7, typename A8, typename A9>
      T&
      new_node (A0 const&, A1 const&, A2 const&, A3 const&, A4 const&,
                A5 const&, A6 const&, A7 const&, A8 const&, A9 const&);

    public:
      template <typename T, typename Left, typename Right>
      T&
      new_edge (Left&, Right&);

      template <typename T, typename Left, typename Right,
                typename A0>
      T&
      new_edge (Left&, Right&, A0 const&);

      template <typename T, typename Left, typename Right,
                typename A0, typename A1>
      T&
      new_edge (Left&, Right&, A0 const&, A1 const&);

      template <typename T, typename Left, typename Right,
                typename A0, typename A1, typename A2>
      T&
      new_edge (Left&, Right&, A0 const&, A1 const&, A2 const&);

      template <typename T, typename Left, typename Right,
                typename A0, typename A1, typename A2, typename A3>
      T&
      new_edge (Left&, Right&, A0 const&, A1 const&, A2 const&, A3 const&);

      template <typename T, typename Left, typename Right,
                typename A0, typename A1, typename A2, typename A3,
                typename A4>
      T&
      new_edge (Left&, Right&, A0 const&, A1 const&, A2 const&, A3 const&,
                A4 const&);

      template <typename T, typename Left, typename Right,
                typename A0, typename A1, typename A2, typename A3,
                typename A4, typename A5>
      T&
      new_edge (Left&, Right&, A0 const&, A1 const&, A2 const&, A3 const&,
                A4 const&, A5 const&);

      // Functions to reset edge's nodes.
      //
    public:
      template <typename TE, typename TN>
      Void
      reset_left_node (TE& edge, TN& node)
      {
        edge.set_left_node (node);
      }

      template <typename TE, typename TN>
      Void
      reset_right_node (TE& edge, TN& node)
      {
        edge.set_right_node (node);
      }

      // Functions to add edges to a node.
      //
    public:
      template <typename TN, typename TE>
      Void
      add_edge_left (TN& node, TE& edge)
      {
        node.add_edge_left (edge);
      }

      template <typename TN, typename TE>
      Void
      add_edge_right (TN& node, TE& edge)
      {
        node.add_edge_right (edge);
      }

      // Functions to delete edges and nodes. In order to delete a
      // a node without leaving any dangling edges you need to make
      // sure that each edge pointing to it is either deleted or reset
      // to some other node.
      //
    public:
      template <typename T, typename Left, typename Right>
      Void
      delete_edge (Left& left_node, Right& right_node, T& edge);

      Void
      delete_node (Node& node)
      {
        if (nodes_.erase (&node) == 0)
          throw NoNode ();
      }

    protected:
      typedef Shptr<Node> NodePtr;
      typedef Shptr<Edge> EdgePtr;

      typedef Map<Node*, NodePtr> Nodes;
      typedef Map<Edge*, EdgePtr> Edges;

      Nodes nodes_;
      Edges edges_;
    };
  }
}


#include <cult/containers/graph.txx>

#endif  // CULT_CONTAINERS_GRAPH_HXX
