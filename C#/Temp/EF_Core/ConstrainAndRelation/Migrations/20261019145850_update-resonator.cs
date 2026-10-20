using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace ConstrainAndRelation.Migrations
{
    /// <inheritdoc />
    public partial class updateresonator : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "Power",
                table: "Resonators");

            migrationBuilder.RenameColumn(
                name: "Name",
                table: "Resonators",
                newName: "ResonatorName");

            migrationBuilder.AlterColumn<string>(
                name: "ResonatorName",
                table: "Resonators",
                type: "nvarchar(50)",
                maxLength: 50,
                nullable: false,
                oldClrType: typeof(string),
                oldType: "nvarchar(max)");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.RenameColumn(
                name: "ResonatorName",
                table: "Resonators",
                newName: "Name");

            migrationBuilder.AlterColumn<string>(
                name: "Name",
                table: "Resonators",
                type: "nvarchar(max)",
                nullable: false,
                oldClrType: typeof(string),
                oldType: "nvarchar(50)",
                oldMaxLength: 50);

            migrationBuilder.AddColumn<int>(
                name: "Power",
                table: "Resonators",
                type: "int",
                nullable: false,
                defaultValue: 0);
        }
    }
}
