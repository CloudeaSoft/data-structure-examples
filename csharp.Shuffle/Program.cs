namespace csharp.Shuffle
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello, World!");
        }

        private static void Shuffle<T>(List<T> list)
        {
            byte[] buffer = Guid.NewGuid().ToByteArray();
            int root = BitConverter.ToInt32(buffer, 0);
            Random rand = new(root);

            for (int i = 0; i < list.Count; i++)
            {
                var index = rand.Next(list.Count);

                var temp = list[index];
                list[index] = list[i];
                list[i] = temp;
            }
        }
    }
}
