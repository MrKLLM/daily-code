using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

#pragma warning disable CA1814 // Prefer jagged arrays over multidimensional

namespace ConstrainAndRelation.Migrations
{
    /// <inheritdoc />
    public partial class adddata : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.InsertData(
                table: "Instructors",
                columns: new[] { "InstructorId", "HireDate", "Name" },
                values: new object[,]
                {
                    { 1, new DateTime(2023, 5, 17, 0, 0, 0, 0, DateTimeKind.Unspecified), "散华" },
                    { 2, new DateTime(2023, 5, 17, 0, 0, 0, 0, DateTimeKind.Unspecified), "今汐" },
                    { 3, new DateTime(2024, 2, 1, 0, 0, 0, 0, DateTimeKind.Unspecified), "吟霖" }
                });

            migrationBuilder.InsertData(
                table: "Resonators",
                columns: new[] { "ResonatorId", "Efficiency", "EnrollmentDate", "Frequency", "ResonatorName", "Type" },
                values: new object[,]
                {
                    { 1, 95, new DateTime(2025, 1, 1, 0, 0, 0, 0, DateTimeKind.Unspecified), 100, "椿", "堙灭" },
                    { 2, 88, new DateTime(2025, 3, 15, 0, 0, 0, 0, DateTimeKind.Unspecified), 50, "守岸人", "衍射" },
                    { 3, 92, new DateTime(2025, 6, 1, 0, 0, 0, 0, DateTimeKind.Unspecified), 75, "秧秧", "气动" },
                    { 4, 90, new DateTime(2025, 9, 10, 0, 0, 0, 0, DateTimeKind.Unspecified), 200, "炽霞", "热熔" },
                    { 5, 87, new DateTime(2025, 11, 5, 0, 0, 0, 0, DateTimeKind.Unspecified), 150, "渊武", "导电" },
                    { 6, 93, new DateTime(2026, 1, 20, 0, 0, 0, 0, DateTimeKind.Unspecified), 80, "茉莉", "冷凝" }
                });

            migrationBuilder.InsertData(
                table: "Departments",
                columns: new[] { "DepartmentId", "Budget", "InstructorId", "Name", "StartDate" },
                values: new object[,]
                {
                    { 1, 500000m, 1, "月影谷", new DateTime(2020, 1, 1, 0, 0, 0, 0, DateTimeKind.Unspecified) },
                    { 2, 300000m, 2, "白缇教", new DateTime(2018, 6, 1, 0, 0, 0, 0, DateTimeKind.Unspecified) }
                });

            migrationBuilder.InsertData(
                table: "OfficeAssignments",
                columns: new[] { "InstructorId", "OfficeLocation" },
                values: new object[,]
                {
                    { 1, "月影谷据点" },
                    { 2, "白缇教总部" }
                });

            migrationBuilder.InsertData(
                table: "Courses",
                columns: new[] { "CourseId", "DepartmentId", "Title" },
                values: new object[,]
                {
                    { 1, 1, "共鸣理论基础" },
                    { 2, 1, "散华剑舞修行" },
                    { 3, 2, "深渊区域探索委托" },
                    { 4, 2, "执法实务训练" }
                });

            migrationBuilder.InsertData(
                table: "CourseInstructor",
                columns: new[] { "CoursesCourseId", "InstructorsInstructorId" },
                values: new object[,]
                {
                    { 1, 1 },
                    { 1, 2 },
                    { 2, 1 },
                    { 3, 2 },
                    { 4, 3 }
                });

            migrationBuilder.InsertData(
                table: "Enrollments",
                columns: new[] { "EnrollmentId", "CourseId", "Grade", "ResonatorId" },
                values: new object[,]
                {
                    { 1, 1, 0, 1 },
                    { 2, 2, 0, 1 },
                    { 3, 1, 1, 2 },
                    { 4, 2, 0, 3 },
                    { 5, 3, 2, 4 },
                    { 6, 4, 1, 5 },
                    { 7, 1, null, 6 }
                });
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DeleteData(
                table: "CourseInstructor",
                keyColumns: new[] { "CoursesCourseId", "InstructorsInstructorId" },
                keyValues: new object[] { 1, 1 });

            migrationBuilder.DeleteData(
                table: "CourseInstructor",
                keyColumns: new[] { "CoursesCourseId", "InstructorsInstructorId" },
                keyValues: new object[] { 1, 2 });

            migrationBuilder.DeleteData(
                table: "CourseInstructor",
                keyColumns: new[] { "CoursesCourseId", "InstructorsInstructorId" },
                keyValues: new object[] { 2, 1 });

            migrationBuilder.DeleteData(
                table: "CourseInstructor",
                keyColumns: new[] { "CoursesCourseId", "InstructorsInstructorId" },
                keyValues: new object[] { 3, 2 });

            migrationBuilder.DeleteData(
                table: "CourseInstructor",
                keyColumns: new[] { "CoursesCourseId", "InstructorsInstructorId" },
                keyValues: new object[] { 4, 3 });

            migrationBuilder.DeleteData(
                table: "Enrollments",
                keyColumn: "EnrollmentId",
                keyValue: 1);

            migrationBuilder.DeleteData(
                table: "Enrollments",
                keyColumn: "EnrollmentId",
                keyValue: 2);

            migrationBuilder.DeleteData(
                table: "Enrollments",
                keyColumn: "EnrollmentId",
                keyValue: 3);

            migrationBuilder.DeleteData(
                table: "Enrollments",
                keyColumn: "EnrollmentId",
                keyValue: 4);

            migrationBuilder.DeleteData(
                table: "Enrollments",
                keyColumn: "EnrollmentId",
                keyValue: 5);

            migrationBuilder.DeleteData(
                table: "Enrollments",
                keyColumn: "EnrollmentId",
                keyValue: 6);

            migrationBuilder.DeleteData(
                table: "Enrollments",
                keyColumn: "EnrollmentId",
                keyValue: 7);

            migrationBuilder.DeleteData(
                table: "OfficeAssignments",
                keyColumn: "InstructorId",
                keyValue: 1);

            migrationBuilder.DeleteData(
                table: "OfficeAssignments",
                keyColumn: "InstructorId",
                keyValue: 2);

            migrationBuilder.DeleteData(
                table: "Courses",
                keyColumn: "CourseId",
                keyValue: 1);

            migrationBuilder.DeleteData(
                table: "Courses",
                keyColumn: "CourseId",
                keyValue: 2);

            migrationBuilder.DeleteData(
                table: "Courses",
                keyColumn: "CourseId",
                keyValue: 3);

            migrationBuilder.DeleteData(
                table: "Courses",
                keyColumn: "CourseId",
                keyValue: 4);

            migrationBuilder.DeleteData(
                table: "Instructors",
                keyColumn: "InstructorId",
                keyValue: 3);

            migrationBuilder.DeleteData(
                table: "Resonators",
                keyColumn: "ResonatorId",
                keyValue: 1);

            migrationBuilder.DeleteData(
                table: "Resonators",
                keyColumn: "ResonatorId",
                keyValue: 2);

            migrationBuilder.DeleteData(
                table: "Resonators",
                keyColumn: "ResonatorId",
                keyValue: 3);

            migrationBuilder.DeleteData(
                table: "Resonators",
                keyColumn: "ResonatorId",
                keyValue: 4);

            migrationBuilder.DeleteData(
                table: "Resonators",
                keyColumn: "ResonatorId",
                keyValue: 5);

            migrationBuilder.DeleteData(
                table: "Resonators",
                keyColumn: "ResonatorId",
                keyValue: 6);

            migrationBuilder.DeleteData(
                table: "Departments",
                keyColumn: "DepartmentId",
                keyValue: 1);

            migrationBuilder.DeleteData(
                table: "Departments",
                keyColumn: "DepartmentId",
                keyValue: 2);

            migrationBuilder.DeleteData(
                table: "Instructors",
                keyColumn: "InstructorId",
                keyValue: 1);

            migrationBuilder.DeleteData(
                table: "Instructors",
                keyColumn: "InstructorId",
                keyValue: 2);
        }
    }
}
