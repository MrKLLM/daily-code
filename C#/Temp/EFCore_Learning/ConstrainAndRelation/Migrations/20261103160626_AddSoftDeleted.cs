using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace ConstrainAndRelation.Migrations
{
    /// <inheritdoc />
    public partial class AddSoftDeleted : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<bool>(
                name: "SoftDeleted",
                table: "Resonators",
                type: "bit",
                nullable: false,
                defaultValue: false);

            migrationBuilder.UpdateData(
                table: "Resonators",
                keyColumn: "ResonatorId",
                keyValue: 1,
                column: "SoftDeleted",
                value: false);

            migrationBuilder.UpdateData(
                table: "Resonators",
                keyColumn: "ResonatorId",
                keyValue: 2,
                column: "SoftDeleted",
                value: false);

            migrationBuilder.UpdateData(
                table: "Resonators",
                keyColumn: "ResonatorId",
                keyValue: 3,
                column: "SoftDeleted",
                value: false);

            migrationBuilder.UpdateData(
                table: "Resonators",
                keyColumn: "ResonatorId",
                keyValue: 4,
                column: "SoftDeleted",
                value: false);

            migrationBuilder.UpdateData(
                table: "Resonators",
                keyColumn: "ResonatorId",
                keyValue: 5,
                column: "SoftDeleted",
                value: false);

            migrationBuilder.UpdateData(
                table: "Resonators",
                keyColumn: "ResonatorId",
                keyValue: 6,
                column: "SoftDeleted",
                value: false);
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "SoftDeleted",
                table: "Resonators");
        }
    }
}
