// file      : cult/containers/graph.txx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace Cult
{
  namespace Containers
  {

    // Nodes.
    //

    template <typename N, typename E>
    template <typename T>
    T& Graph<N, E>::
    new_node ()
    {
      Shptr<T> node (new T);
      nodes_[node.get ()] = node;

      return *node;
    }


    template <typename N, typename E>
    template <typename T, typename A0>
    T& Graph<N, E>::
    new_node (A0 const& a0)
    {
      Shptr<T> node (new T (a0));
      nodes_[node.get ()] = node;

      return *node;
    }


    template <typename N, typename E>
    template <typename T, typename A0, typename A1>
    T& Graph<N, E>::
    new_node (A0 const& a0, A1 const& a1)
    {
      Shptr<T> node (new T (a0, a1));
      nodes_[node.get ()] = node;

      return *node;
    }

    template <typename N, typename E>
    template <typename T, typename A0, typename A1, typename A2>
    T& Graph<N, E>::
    new_node (A0 const& a0, A1 const& a1, A2 const& a2)
    {
      Shptr<T> node (new T (a0, a1, a2));
      nodes_[node.get ()] = node;

      return *node;
    }

    template <typename N, typename E>
    template <typename T, typename A0, typename A1, typename A2,
              typename A3>
    T& Graph<N, E>::
    new_node (A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3)
    {
      Shptr<T> node (new T (a0, a1, a2, a3));
      nodes_[node.get ()] = node;

      return *node;
    }

    template <typename N, typename E>
    template <typename T, typename A0, typename A1, typename A2,
              typename A3, typename A4>
    T& Graph<N, E>::
    new_node (A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3,
              A4 const& a4)
    {
      Shptr<T> node (new T (a0, a1, a2, a3, a4));
      nodes_[node.get ()] = node;

      return *node;
    }

    template <typename N, typename E>
    template <typename T, typename A0, typename A1, typename A2,
              typename A3, typename A4, typename A5>
    T& Graph<N, E>::
    new_node (A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3,
              A4 const& a4, A5 const& a5)
    {
      Shptr<T> node (new T (a0, a1, a2, a3, a4, a5));
      nodes_[node.get ()] = node;

      return *node;
    }

    template <typename N, typename E>
    template <typename T, typename A0, typename A1, typename A2,
              typename A3, typename A4, typename A5, typename A6>
    T& Graph<N, E>::
    new_node (A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3,
              A4 const& a4, A5 const& a5, A6 const& a6)
    {
      Shptr<T> node (new T (a0, a1, a2, a3, a4, a5, a6));
      nodes_[node.get ()] = node;

      return *node;
    }

    template <typename N, typename E>
    template <typename T, typename A0, typename A1, typename A2,
              typename A3, typename A4, typename A5, typename A6,
              typename A7>
    T& Graph<N, E>::
    new_node (A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3,
              A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7)
    {
      Shptr<T> node (new T (a0, a1, a2, a3, a4, a5, a6, a7));
      nodes_[node.get ()] = node;

      return *node;
    }


    template <typename N, typename E>
    template <typename T, typename A0, typename A1, typename A2,
              typename A3, typename A4, typename A5, typename A6,
              typename A7, typename A8>
    T& Graph<N, E>::
    new_node (A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3,
              A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7,
              A8 const& a8)
    {
      Shptr<T> node (new T (a0, a1, a2, a3, a4, a5, a6, a7, a8));
      nodes_[node.get ()] = node;

      return *node;
    }


    template <typename N, typename E>
    template <typename T, typename A0, typename A1, typename A2,
              typename A3, typename A4, typename A5, typename A6,
              typename A7, typename A8, typename A9>
    T& Graph<N, E>::
    new_node (A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3,
              A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7,
              A8 const& a8, A9 const& a9)
    {
      Shptr<T> node (new T (a0, a1, a2, a3, a4, a5, a6, a7, a8, a9));
      nodes_[node.get ()] = node;

      return *node;
    }


    // Edges.
    //

    template <typename N, typename E>
    template <typename T, typename Left, typename Right>
    T& Graph<N, E>::
    new_edge (Left& l, Right& r)
    {
      Shptr<T> edge (new T);
      edges_[edge.get ()] = edge;

      edge->set_left_node (l);
      edge->set_right_node (r);

      l.add_edge_left (*edge);
      r.add_edge_right (*edge);

      return *edge;
    }

    template <typename N, typename E>
    template <typename T, typename Left, typename Right,
              typename A0>
    T& Graph<N, E>::
    new_edge (Left& l, Right& r, A0 const& a0)
    {
      Shptr<T> edge (new T (a0));
      edges_[edge.get ()] = edge;

      edge->set_left_node (l);
      edge->set_right_node (r);

      l.add_edge_left (*edge);
      r.add_edge_right (*edge);

      return *edge;
    }

    template <typename N, typename E>
    template <typename T, typename Left, typename Right,
              typename A0, typename A1>
    T& Graph<N, E>::
    new_edge (Left& l, Right& r, A0 const& a0, A1 const& a1)
    {
      Shptr<T> edge (new T (a0, a1));
      edges_[edge.get ()] = edge;

      edge->set_left_node (l);
      edge->set_right_node (r);

      l.add_edge_left (*edge);
      r.add_edge_right (*edge);

      return *edge;
    }

    template <typename N, typename E>
    template <typename T, typename Left, typename Right,
              typename A0, typename A1, typename A2>
    T& Graph<N, E>::
    new_edge (Left& l, Right& r, A0 const& a0, A1 const& a1, A2 const& a2)
    {
      Shptr<T> edge (new T (a0, a1, a2));
      edges_[edge.get ()] = edge;

      edge->set_left_node (l);
      edge->set_right_node (r);

      l.add_edge_left (*edge);
      r.add_edge_right (*edge);

      return *edge;
    }

    template <typename N, typename E>
    template <typename T, typename Left, typename Right,
              typename A0, typename A1, typename A2, typename A3>
    T& Graph<N, E>::
    new_edge (Left& l, Right& r, A0 const& a0, A1 const& a1, A2 const& a2,
              A3 const& a3)
    {
      Shptr<T> edge (new T (a0, a1, a2, a3));
      edges_[edge.get ()] = edge;

      edge->set_left_node (l);
      edge->set_right_node (r);

      l.add_edge_left (*edge);
      r.add_edge_right (*edge);

      return *edge;
    }

    template <typename N, typename E>
    template <typename T, typename Left, typename Right,
              typename A0, typename A1, typename A2, typename A3,
              typename A4>
    T& Graph<N, E>::
    new_edge (Left& l, Right& r, A0 const& a0, A1 const& a1, A2 const& a2,
              A3 const& a3, A4 const& a4)
    {
      Shptr<T> edge (new T (a0, a1, a2, a3, a4));
      edges_[edge.get ()] = edge;

      edge->set_left_node (l);
      edge->set_right_node (r);

      l.add_edge_left (*edge);
      r.add_edge_right (*edge);

      return *edge;
    }

    template <typename N, typename E>
    template <typename T, typename Left, typename Right,
              typename A0, typename A1, typename A2, typename A3,
              typename A4, typename A5>
    T& Graph<N, E>::
    new_edge (Left& l, Right& r, A0 const& a0, A1 const& a1, A2 const& a2,
              A3 const& a3, A4 const& a4, A5 const& a5)
    {
      Shptr<T> edge (new T (a0, a1, a2, a3, a4, a5));
      edges_[edge.get ()] = edge;

      edge->set_left_node (l);
      edge->set_right_node (r);

      l.add_edge_left (*edge);
      r.add_edge_right (*edge);

      return *edge;
    }


    template <typename N, typename E>
    template <typename T, typename Left, typename Right>
    Void Graph<N, E>::
    delete_edge (Left& l, Right& r, T& edge)
    {
      typename Edges::Iterator i (edges_.find (&edge));

      if (i == edges_.end () ||
          nodes_.find (&l) == nodes_.end () ||
          nodes_.find (&r) == nodes_.end ())
        throw NoEdge ();

      r.remove_edge_right (edge);
      l.remove_edge_left (edge);

      edge.clear_right_node (r);
      edge.clear_left_node (l);

      edges_.erase (i);
    }
  }
}
