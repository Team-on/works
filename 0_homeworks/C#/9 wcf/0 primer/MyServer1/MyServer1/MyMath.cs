using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;

namespace MyServer1
{
   
    public class MyMath : IMyMath
    {
        public int Add(int a, int b)
        {
            return a + b;
        }
    }
}
