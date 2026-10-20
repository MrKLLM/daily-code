using System;
using System.Collections.Generic;
using System.Text;

namespace EFCore_First
{
    public class Book
    {
        public int BookId { get; set; }
        public string Title { get; set; }
        public string Description { get; set; }
        public DateTime PublishedOn { get; set; }
        public decimal Price { get; set; }
        public string ImageUrl { get; set; }
    }
}
