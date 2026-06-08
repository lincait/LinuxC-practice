#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159

enum Grade  //成绩等级
{
    F,
    D,
    C,
    B,
    A
};
struct Student  
{
    char stu_id[20];
    char stu_name[20];
    int stu_score[3];
    float stu_ave;
    enum Grade grade; 
};


enum ShapeType
{
    CIRCLE, 
    RECTANGLE,
    TRIANGLE
};
struct Shape
{
    enum ShapeType type;
    union
    {
        double radius;       //圆形半径
        struct //此处只能再定义一个结构体，不能把长宽都放在共用体（不能同时使用）
        {
            double Length,Width; //矩形长宽
        }rec;
        struct 
        {
            double Base,Height;  //三角形底高
        }tri;
    }Data;
};

void input_students(struct Student *stu, int n);    //从键盘输入 n 个学生的信息（学号、姓名、三门成绩)
void calc_average_and_grade(struct Student *stu);   //calc_average_and_grade：计算该学生的平均分，并根据平均分设置等级
void print_students(const struct Student *stu, int n);  //按格式打印所有学生信息

void set_circle(struct Shape *s, double radius);    //三个函数分别设置图形类型和对应的数据
void set_rectangle(struct Shape *s, double width, double length);
void set_triangle(struct Shape *s, double base, double height);
double get_area(const struct Shape *s);             //计算面积
const char* get_shape_name(const struct Shape *s);  //获取形状名称


int main(void)
{
    // struct Student stu[3];  //三个学生
    // input_students(stu,3);  //传入首地址
    // calc_average_and_grade(&stu[0]);
    // calc_average_and_grade(&stu[1]);
    // calc_average_and_grade(&stu[2]);
    // print_students(stu,3);

    struct Shape s[3];
    double r,l,w,b,h;
    printf("Enter r l w b h:\n");
    scanf("%lf%lf%lf%lf%lf",&r,&l,&w,&b,&h);
    set_circle(&s[0],r);
    set_rectangle(&s[1],w,l);
    set_triangle(&s[2],b,h);
    for (int i = 0; i < 3; i++)
    {
        printf("Shape:%10s\tArea:%7.3lf\n",get_shape_name(&s[i]),get_area(&s[i]));
    }

    return 0;
}

/*学生成绩管理系统
描述：
定义一个枚举类型 Grade 表示成绩等级（A=4, B=3, C=2, D=1, F=0）。
定义结构体 Student，包含：
学号（字符串，长度不超过 20）,姓名（字符串，长度不超过 20）,三门课的成绩（整型数组，长度 3）,平均分（浮点数）,等级（枚举 Grade）

编写以下函数：
void input_students(struct Student *stu, int n);    //从键盘输入 n 个学生的信息（学号、姓名、三门成绩)
void calc_average_and_grade(struct Student *stu);   //计算该学生的平均分，并根据平均分设置等级
void print_students(const struct Student *stu, int n);  //按格式打印所有学生信息
*/
void input_students(struct Student *stu, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Please Enter Student %d Information(ID Name Score):\n",i);
        scanf("%s%s%d%d%d",(stu+i)->stu_id,(stu+i)->stu_name,&(stu+i)->stu_score[0],&(stu+i)->stu_score[1],&(stu+i)->stu_score[2]);
    }    
}
void calc_average_and_grade(struct Student *stu)
{
    stu->stu_ave = (stu->stu_score[0] + stu->stu_score[1] + stu->stu_score[2]) / 3;
    if(stu->stu_ave >= 0 && stu->stu_ave < 40)
    {
        stu->grade = F;
    }
    else if(stu->stu_ave >= 40 && stu->stu_ave < 60)
    {
        stu->grade = D;
    }
    else if(stu->stu_ave >= 60 && stu->stu_ave < 80)
    {
        stu->grade = C;
    }
    else if(stu->stu_ave >= 80 && stu->stu_ave < 90)
    {
        stu->grade = B;
    }
    else if(stu->stu_ave >= 90 && stu->stu_ave <= 100)
    {
        stu->grade = A;
    }
    else
    {
        printf("score error\n");
    }
    
}
void print_students(const struct Student *stu, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("ID:%s\tName:%s\n",(stu+i)->stu_id,(stu+i)->stu_name);
        printf("Math:%d\nSignal:%d\nEnglish:%d\n",(stu+i)->stu_score[0],(stu+i)->stu_score[1],(stu+i)->stu_score[2]);
        printf("average:%.1f\t",(stu+i)->stu_ave);
        switch ((stu+i)->grade)
        {
            case F: printf("Grade:F\n"); break;
            case D: printf("Grade:D\n"); break;
            case C: printf("Grade:C\n"); break;
            case B: printf("Grade:B\n"); break;
            case A: printf("Grade:A\n"); break;
            default: printf("error\n"); break;
        }
    }

    
}

/*形状联合体与结构体嵌套
描述：
实现一个简单的“图形信息存储”，支持三种图形：圆形、矩形、三角形。
定义一个枚举 ShapeType，包含 CIRCLE, RECTANGLE, TRIANGLE。
定义一个结构体 Shape，包含：
一个 ShapeType 类型的成员，表示图形种类。
一个共用体 Data，根据种类存储不同的信息：圆形：半径（浮点数）矩形：长和宽（两个浮点数）三角形：底和高（两个浮点数）
编写以下函数：
void set_circle(struct Shape *s, double radius);
void set_rectangle(struct Shape *s, double width, double length);
void set_triangle(struct Shape *s, double base, double height);
double get_area(const struct Shape *s);
const char* get_shape_name(const struct Shape *s);
三个函数分别设置图形类型和对应的数据。
get_area：计算面积
get_shape_name：返回图形的字符串名称（如 "Circle"、"Rectangle"、"Triangle"），不能使用任何标准库字符串转换函数，需要利用枚举手动映射。
编写一段测试代码，用结构体数组存储多个不同图形并打印面积。
*/
void set_circle(struct Shape *s, double radius)
{
    s->type = CIRCLE;
    s->Data.radius = radius;
}
void set_rectangle(struct Shape *s, double width, double length)
{
    s->type = RECTANGLE;
    s->Data.rec.Width = width;
    s->Data.rec.Length = length;
}
void set_triangle(struct Shape *s, double base, double height)
{
    s->type = TRIANGLE;
    s->Data.tri.Base = base;
    s->Data.tri.Height = height;
}
double get_area(const struct Shape *s)
{
    switch (s->type)
    {
        case CIRCLE:
            return PI * s->Data.radius * s->Data.radius;
        case RECTANGLE:
            return s->Data.rec.Length * s->Data.rec.Width;
        case TRIANGLE:
            return (s->Data.tri.Base * s->Data.tri.Height) * 0.5;
        
        default:
        printf("没有图形\n");
        return 0;
    }
}
const char* get_shape_name(const struct Shape *s)
{
    switch (s->type)
    {
        case CIRCLE: return "Circle";
        case RECTANGLE: return "Rectangle";
        case TRIANGLE: return "Triangle";
        
        default: return "Unknown";
    }
}
