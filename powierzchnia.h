#define MENUX		1
#define MENUY		1
#define SIZEINPUTX	1
#define SIZEINPUTY	20
#define NAMEINPUTX	1
#define NAMEINPUTY	24
#define FILENAMEX	1
#define FILENAMEY	28
#define MAXNAME		15
#define ENTER		0x0d
#define ESC			27
#define STALAPLIK	0 
#define PICX		40  //wspó³rzêdne lewego górnego rogu obrazka
#define PICY		2
#define LINIEX		1
#define LINIEY		28


struct Colorxpm {
	char* ch;
	int* color;
};
struct znak {
	char fg,bg,ch;
};
struct Powierzchnia{
	int w, h;
	znak*tab;
	char*name;
};
struct Parameters {
	int zn , x , y , attr , back , zero ;
};

Powierzchnia create(int x, int y);
void draw(Powierzchnia p,int x, int y);
Powierzchnia change_bg(Powierzchnia p, Parameters par); 
void save_my_file(Powierzchnia p,char*fn);
Powierzchnia create_new();
char* get_fn();
void write_fn(Powierzchnia obrazek);
void write_cursor_coord(int x, int y);
Parameters color_and_cursor(Parameters par);
Powierzchnia draw_rectangle(Powierzchnia p, Parameters par);
Powierzchnia draw_line(Powierzchnia p, Parameters par);
Powierzchnia load_my_file(char*fn);
Powierzchnia load_XPM2(char*fn, Colorxpm xpm);
void save_XPM2(Powierzchnia p, Colorxpm xpm, char* fn);
char file_format(char*fn);
Powierzchnia kubelek(Powierzchnia p, Parameters par);