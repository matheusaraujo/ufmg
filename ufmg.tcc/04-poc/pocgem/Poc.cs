using System;
using System.Collections.Generic;

namespace pocgem
{
    public class Poc
    {
        private readonly PGraph _g;

        public Poc()
        {
            _g = new PGraph();
        }

        public void ReadInput()
        {
            int v = int.Parse(Console.ReadLine());

            for (int i = 0; i < v; i++)
            {
                string s1 = Console.ReadLine();
                _g.AddVertex(s1);
            }

            int e = int.Parse(Console.ReadLine());

            for (int i = 0; i < e; i++)
            {
                string[] s = Console.ReadLine().Split(' ');
                _g.AddEdge(s[0], s[1]);
            }
        }

        public void PrintOutput()
        {
            _g.GetInfo((string s) =>
            {
                Console.WriteLine(s);
            });
        }
    }
}