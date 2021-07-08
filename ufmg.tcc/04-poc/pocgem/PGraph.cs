using System;
using System.Collections.Generic;
using System.Linq;

namespace pocgem
{
,.
    public class Graph
    {
        private int[] v;
        private int[,] g;

        public Graph(List<string> _v, List<Tuple<string, string>> _e)
        {
            v = new int[_v.Count];
            g = new int[_v.Count, _v.Count];

            foreach (var e in _e)
            {
                int i1 = _v.IndexOf(e.Item1);
                int i2 = _v.IndexOf(e.Item2);
                g[i1, i2] = 1;
            }
        }

        private void dfs(int i, int d, bool f)
        {
            v[i] = d;

            for (int k = 0; k < v.Length; k++)
            {
                if (d > 1 && v[k] == 0 && ((f && g[i, k] == 1) || (!f && g[k, i] == 1)))
                    dfs(k, d - 1, f);
            }
        }

        public int f_dfs(int i)
        {
            v = new int[v.Length];
            dfs(i, 3, true);
            return v.ToList().Sum() - 1;
        }

        public int b_dfs(int i)
        {
            v = new int[v.Length];
            dfs(i, 3, false);
            return v.ToList().Sum() - 1;
        }

    }


    public class PGraph
    {
        private readonly List<string> _vertexs;
        private readonly List<Tuple<string, string>> _edges;

        public PGraph()
        {
            _vertexs = new List<string>();
            _edges = new List<Tuple<string, string>>();
        }

        public void AddVertex(string v)
        {
            if (!_vertexs.Contains(v))
                _vertexs.Add(v);
        }

        public void AddEdge(string v1, string v2)
        {
            var i1 = _vertexs.IndexOf(v1);
            var i2 = _vertexs.IndexOf(v2);

            if (i1 == i2 || i1 == -1 || i2 == -1)
                throw new Exception("invalid vertex," + v1 + "," + v2);

            _edges.Add(new Tuple<string, string>(v1, v2));
        }

        public void GetInfo(Action<string> callback)
        {
            var g = new Graph(_vertexs, _edges);
            for (int i = 0; i < _vertexs.Count; i++)
            {
                var s = _vertexs[i].ToString() + "," +
                    g.b_dfs(i).ToString() + "," + g.f_dfs(i).ToString();
                callback(s);
            }
        }
    }
}