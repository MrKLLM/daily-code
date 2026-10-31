using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace ConstrainAndRelation.Migrations
{
    /// <inheritdoc />
    public partial class Resonator_Update : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_CourseInstructor_Courses_CoursesCourseId",
                table: "CourseInstructor");

            migrationBuilder.DropForeignKey(
                name: "FK_CourseInstructor_Instructors_InstructorsInstructorId",
                table: "CourseInstructor");

            migrationBuilder.AlterColumn<DateTime>(
                name: "EnrollmentDate",
                table: "Resonators",
                type: "datetime2",
                nullable: false,
                defaultValueSql: "GETDATE()",
                oldClrType: typeof(DateTime),
                oldType: "datetime2");

            migrationBuilder.AddColumn<int>(
                name: "Efficiency",
                table: "Resonators",
                type: "int",
                nullable: false,
                defaultValue: 0);

            migrationBuilder.AddColumn<int>(
                name: "Frequency",
                table: "Resonators",
                type: "int",
                nullable: false,
                defaultValue: 0);

            migrationBuilder.AddColumn<string>(
                name: "Type",
                table: "Resonators",
                type: "nvarchar(30)",
                maxLength: 30,
                nullable: false,
                defaultValue: "");

            migrationBuilder.AddForeignKey(
                name: "FK_CourseInstructor_Courses_CoursesCourseId",
                table: "CourseInstructor",
                column: "CoursesCourseId",
                principalTable: "Courses",
                principalColumn: "CourseId",
                onDelete: ReferentialAction.Restrict);

            migrationBuilder.AddForeignKey(
                name: "FK_CourseInstructor_Instructors_InstructorsInstructorId",
                table: "CourseInstructor",
                column: "InstructorsInstructorId",
                principalTable: "Instructors",
                principalColumn: "InstructorId",
                onDelete: ReferentialAction.Restrict);
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_CourseInstructor_Courses_CoursesCourseId",
                table: "CourseInstructor");

            migrationBuilder.DropForeignKey(
                name: "FK_CourseInstructor_Instructors_InstructorsInstructorId",
                table: "CourseInstructor");

            migrationBuilder.DropColumn(
                name: "Efficiency",
                table: "Resonators");

            migrationBuilder.DropColumn(
                name: "Frequency",
                table: "Resonators");

            migrationBuilder.DropColumn(
                name: "Type",
                table: "Resonators");

            migrationBuilder.AlterColumn<DateTime>(
                name: "EnrollmentDate",
                table: "Resonators",
                type: "datetime2",
                nullable: false,
                oldClrType: typeof(DateTime),
                oldType: "datetime2",
                oldDefaultValueSql: "GETDATE()");

            migrationBuilder.AddForeignKey(
                name: "FK_CourseInstructor_Courses_CoursesCourseId",
                table: "CourseInstructor",
                column: "CoursesCourseId",
                principalTable: "Courses",
                principalColumn: "CourseId",
                onDelete: ReferentialAction.Cascade);

            migrationBuilder.AddForeignKey(
                name: "FK_CourseInstructor_Instructors_InstructorsInstructorId",
                table: "CourseInstructor",
                column: "InstructorsInstructorId",
                principalTable: "Instructors",
                principalColumn: "InstructorId",
                onDelete: ReferentialAction.Cascade);
        }
    }
}
