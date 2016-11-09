using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VarnamCLR;

namespace VarnamCLRTest
{
    class Program
    {
        static void Main(string[] args)
        {
            Varnam varnam = new Varnam("ml");
            List<String> words = varnam.Transliterate("riyas");
            System.IO.File.WriteAllLines(@"C:\Users\Yash\Desktop\New folder\varnam.txt", words);            
            Console.ReadLine();
        }
    }
}
