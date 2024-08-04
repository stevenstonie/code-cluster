using asp.net_mvc_starter.entities;
using efcore_starter.entities;
using Microsoft.EntityFrameworkCore;

namespace asp.net_mvc_starter
{
    public static class Program
    {
        public static void Main(string[] args)
        {
            var builder = WebApplication.CreateBuilder(args);

            builder.Services.AddControllersWithViews();
            builder.Services.AddDbContext<BloggingContext>(options =>
                options.UseSqlite("Data Source=blogging.db"));

            var app = builder.Build();

            if (!app.Environment.IsDevelopment())
            {
                app.UseExceptionHandler("/Home/Error");
                app.UseHsts();
            }

            app.UseHttpsRedirection();
            app.UseStaticFiles();
            app.UseRouting();
            app.UseAuthorization();

            app.MapControllerRoute(
                name: "default",
                pattern: "{controller=Home}/{action=Index}/{id?}");

            using (var scope = app.Services.CreateScope())
            {
                var db = scope.ServiceProvider.GetRequiredService<BloggingContext>();

                Console.WriteLine($"Database path: {db.DbPath}.");

                Console.WriteLine("Inserting a new blog");
                db.Add(new Blog { Url = "http://blogs.msdn.com/adonet" });
                db.SaveChanges();

                Console.WriteLine("Querying for a blog");
                var blog = db.Blogs
                    .OrderBy(b => b.BlogId)
                    .First();

                Console.WriteLine("Updating the blog and adding a post");
                blog.Url = "https://devblogs.microsoft.com/dotnet";
                blog.Posts.Add(
                    new Post { Title = "Hello World", Content = "I wrote an app using EF Core!" });
                db.SaveChanges();

                Console.WriteLine("Delete the blog");
                db.Remove(blog);
                db.SaveChanges();
            }

            app.Run();
        }
    }
}
