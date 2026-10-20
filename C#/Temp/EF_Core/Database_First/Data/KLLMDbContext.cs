using System;
using System.Collections.Generic;
using Database_First.Models;
using Microsoft.EntityFrameworkCore;

namespace Database_First.Data;

public partial class KLLMDbContext : DbContext
{
    public KLLMDbContext()
    {
    }

    public KLLMDbContext(DbContextOptions<KLLMDbContext> options)
        : base(options)
    {
    }

    public virtual DbSet<Address> Addresses { get; set; }

    public virtual DbSet<Product> Products { get; set; }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
#warning To protect potentially sensitive information in your connection string, you should move it out of source code. You can avoid scaffolding the connection string by using the Name= syntax to read it from configuration - see https://go.microsoft.com/fwlink/?linkid=2131148. For more guidance on storing connection strings, see https://go.microsoft.com/fwlink/?LinkId=723263.
        => optionsBuilder.UseSqlServer("Server=(localdb)\\MSSQLLocalDB;Database=AdventureWorksLT2025;trusted_connection=True;MultipleActiveResultSets=True;");

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<Address>(entity =>
        {
            entity.HasKey(e => e.AddressId).HasName("PK_Address_AddressID");

            entity.ToTable("Address", "SalesLT", tb => tb.HasComment("Street address information for customers."));

            entity.Property(e => e.AddressId).HasComment("Primary key for Address records.");
            entity.Property(e => e.AddressLine1).HasComment("First street address line.");
            entity.Property(e => e.AddressLine2).HasComment("Second street address line.");
            entity.Property(e => e.City).HasComment("Name of the city.");
            entity.Property(e => e.ModifiedDate)
                .HasComment("Date and time the record was last updated.")
                .HasDefaultValueSql("(getdate())", "DF_Address_ModifiedDate");
            entity.Property(e => e.PostalCode).HasComment("Postal code for the street address.");
            entity.Property(e => e.Rowguid)
                .HasComment("ROWGUIDCOL number uniquely identifying the record. Used to support a merge replication sample.")
                .HasDefaultValueSql("(newid())", "DF_Address_rowguid");
            entity.Property(e => e.StateProvince).HasComment("Name of state or province.");
        });

        modelBuilder.Entity<Product>(entity =>
        {
            entity.HasKey(e => e.ProductId).HasName("PK_Product_ProductID");

            entity.ToTable("Product", "SalesLT", tb => tb.HasComment("Products sold or used in the manfacturing of sold products."));

            entity.Property(e => e.ProductId).HasComment("Primary key for Product records.");
            entity.Property(e => e.Color).HasComment("Product color.");
            entity.Property(e => e.DiscontinuedDate).HasComment("Date the product was discontinued.");
            entity.Property(e => e.ListPrice).HasComment("Selling price.");
            entity.Property(e => e.ModifiedDate)
                .HasComment("Date and time the record was last updated.")
                .HasDefaultValueSql("(getdate())", "DF_Product_ModifiedDate");
            entity.Property(e => e.Name).HasComment("Name of the product.");
            entity.Property(e => e.ProductCategoryId).HasComment("Product is a member of this product category. Foreign key to ProductCategory.ProductCategoryID. ");
            entity.Property(e => e.ProductModelId).HasComment("Product is a member of this product model. Foreign key to ProductModel.ProductModelID.");
            entity.Property(e => e.ProductNumber).HasComment("Unique product identification number.");
            entity.Property(e => e.Rowguid)
                .HasComment("ROWGUIDCOL number uniquely identifying the record. Used to support a merge replication sample.")
                .HasDefaultValueSql("(newid())", "DF_Product_rowguid");
            entity.Property(e => e.SellEndDate).HasComment("Date the product was no longer available for sale.");
            entity.Property(e => e.SellStartDate).HasComment("Date the product was available for sale.");
            entity.Property(e => e.Size).HasComment("Product size.");
            entity.Property(e => e.StandardCost).HasComment("Standard cost of the product.");
            entity.Property(e => e.ThumbNailPhoto).HasComment("Small image of the product.");
            entity.Property(e => e.ThumbnailPhotoFileName).HasComment("Small image file name.");
            entity.Property(e => e.Weight).HasComment("Product weight.");
        });

        OnModelCreatingPartial(modelBuilder);
    }

    partial void OnModelCreatingPartial(ModelBuilder modelBuilder);
}
