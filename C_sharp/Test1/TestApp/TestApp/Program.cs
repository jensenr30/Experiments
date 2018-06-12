// Program.cs
// Ryan Jensen
// 2018-06-11
//
// Test program just to get my fingers back into the groove of writing C#.

using System;

namespace TestApp
{
    class Program
    {
        static void Main(string[] args)
        {
            // Hello World test.
            //Console.writeline("what is your name?");
            //string name = console.readline();
            //console.writeLine("Hello " + name);

            //bool canVote = true;

            //char grade = 'A';

            //long.MaxValue
            //Console.WriteLine(decimal.MaxValue);

            //Console.WriteLine("5 + 3 = " + (5 + 3));
            //Console.WriteLine("5 - 3 = " + (5 - 3));
            //Console.WriteLine("5 * 3 = " + (5 * 3));
            //Console.WriteLine("5 / 3 = " + (5 / 3));
            //Console.WriteLine("5.2 % 3 = " + (5.2 % 3));

            //int i = 0;

            //Console.WriteLine("i++ = " + (i++));
            //Console.WriteLine("++i = " + (++i));
            //Console.WriteLine("i-- = " + (i--));
            //Console.WriteLine("--i = " + (--i));

            //Console.WriteLine("i += 3 = " + (i+=3));
            //Console.WriteLine("i -= 2 = " + (i -= 2));
            //Console.WriteLine("i *= 2 = " + (i *= 2));
            //Console.WriteLine("i /= 2 = " + (i /= 2));
            //Console.WriteLine("i %= 2 = " + (i %= 2));

            //double pi10 = 31.4;
            //int intPi10 = (int)pi10;

            //Console.WriteLine("pi10 = " + pi10 + ". intPi10 = " + intPi10);

            //double number1 = 10.5;
            //double number2 = 15;

            //Console.WriteLine("Math.Abs(number1) = " + Math.Abs(number1));
            //Console.WriteLine("Math.Ceiling(nubmer1) = " + Math.Ceiling(number1));
            //Console.WriteLine("Math.Floor(number1) = " + Math.Floor(number1));
            //Console.WriteLine("Math.Max(number1, number2) = " + Math.Max(number1, number2));
            //Console.WriteLine("Math.Min(number2, number2) = " + Math.Min(number2, number2));
            //Console.WriteLine("Math.Pow(number1, 2) = " + Math.Pow(number1, 2));
            //Console.WriteLine("Math.Round(number1) = " + Math.Round(number1));
            //Console.WriteLine("Math.Sqrt(number1) = " + Math.Sqrt(number1));

            //Random rand = new Random();

            //for (int i = 0; i < 100; i++)
            //    Console.WriteLine("Random Number between 1 and 10 = " + (rand.Next(1,11)));

            //double age = 5;

            //if ((age >= 5) && (age <= 7))
            //{
            //    Console.WriteLine("Go to elementary school");
            //}
            //else if((age > 7) && (age < 13))
            //{
            //    Console.WriteLine("Go to middle schoole");
            //}
            //else
            //{
            //    Console.WriteLine("Go to highschool!");
            //}

            //int age = 15;

            //bool canDrive = age >= 16 ? true : false;
            //Console.WriteLine("CanDrive = " + canDrive);

            //int age = 0;
            //switch (age)
            //{
            //    case 0:
            //        Console.WriteLine("Infant");
            //        break;
            //    case 1:
            //    case 2:
            //        Console.WriteLine("Toddler");
            //        break;
            //    default:
            //        Console.WriteLine("Other than 0,1,2");
            //        break;

            //}

            //string guess;

            //do
            //{
            //    Console.WriteLine("Guess a number");
            //    guess = Console.ReadLine();
            //}
            //while (!guess.Equals("12"));

            //string randStr = "Here are some random characters";

            //foreach(char c in randStr)
            //{
            //    Console.WriteLine(c);
            //}

            //string myStr = "And then I made the program say,\n\"Hello world!\"\nand it worked out pretty good.";
            //Console.WriteLine(myStr);

            string sampString  = "more words1";
            string sampString2 = "more words";

            Console.WriteLine("Is empty = " + String.IsNullOrEmpty(sampString));
            Console.WriteLine("Is null or white space = " + String.IsNullOrWhiteSpace(sampString));
            Console.WriteLine("length = " + sampString.Length);

            Console.WriteLine("Are String sampString and sampString2 equal? " + sampString.Equals(sampString2));

        }
    }
}
