using efcore_starter.entities;
using Microsoft.EntityFrameworkCore;

namespace asp.net_mvc_starter.entities
{
    public class BloggingContext : DbContext
    {
        public string DbPath { get; }

        public BloggingContext(DbContextOptions<BloggingContext> options)
            : base(options)
        {
            DbPath = "blogging.db";
        }

        public BloggingContext()
        {
            var folder = Environment.SpecialFolder.LocalApplicationData;
            var path = Environment.GetFolderPath(folder);
            DbPath = Path.Join(path, "blogging.db");
        }

        public DbSet<Blog> Blogs
        {
            get; set;
        }
        public DbSet<Post> Posts
        {
            get; set;
        }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
            => optionsBuilder.UseSqlite($"Data Source={DbPath}");
    }
}