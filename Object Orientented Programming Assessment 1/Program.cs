using System;
using System.Collections.Generic;

namespace Object_Orientented_Programming_Assessment_1
{
    class Program
    {
        static void Main(string[] args)
        {
            Deck deck1 = new Deck();

            deck1.deck = deck1.Shuffle(deck1.deck);

            Console.WriteLine(deck1.IsEmpty(deck1.deck));
            Console.WriteLine("");

            Console.WriteLine("");
            Console.WriteLine("The deck now has {0}", deck1.deck.Count);

            Card card1 = deck1.Deal(deck1.deck);

            Console.WriteLine(card1.value + " " + card1.suit);
        }
    }
    class Deck
    {
        public List<Card> deck;

        public Deck()
        {
            string[] suits = new string[] { "Diamonds", "Hearts", "Spade", "Clubs" };
            int[] values = new int[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
            deck = new List<Card>();
            foreach (string suit in suits)
            {
                foreach (int value in values)
                {
                    deck.Add(new Card(suit, value));
                }
            }



        }
        public bool IsEmpty(List<Card> cards)
        {
            if (cards.Count == 0)
            {
                return true;
            }
            else
            {
                return false;
            }



        }
        public List<Card> Shuffle(List<Card> cards)
        {
            for (int i = 0; i < cards.Count; i++)
            {

                Random rng = new Random();
                int SwapCardIndex = rng.Next(0, 52);


                Card tmp = cards[i];


                cards[i] = cards[SwapCardIndex];


                cards[SwapCardIndex] = tmp;
            }
            return cards;
        }

        ///name="cards"
        public Card Deal(List<Card> cards)
        {
            Card card = cards[0];
            cards.Remove(cards[0]);
            return card;
        }

    }
    class Card
    {
        // attributesj/fields 
        public string suit;
        public string value;

        public Card(string suits, int values)
        {
            suit = suits;
            if (values == 0)
            {
                value = "A";
            }
            else if (values >= 1 && values <= 9)
            {
                values++;
                value = values.ToString();
            }
            else if (values == 10)
            {
                value = "J";
            }
            else if (values == 11)
            {
                value = "Q";
            }
            else
            {
                value = "K";
            }
            // any other methods should be defined as below
            /* public data type/void nameOfMethod()
             * {
             *      Process of method
             * }
             * data type if you need/ want to return that type
             * void if you don't want to return anything
             */
        }
    }
}
