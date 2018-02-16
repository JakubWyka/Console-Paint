#pragma warning (disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include"conio2.h"
#include <stdio.h>
#include"powierzchnia.h" 
int main(int argc, char ** argv) {
	Parameters par;
	par.zn = 0, par.x = 40, par.y = 12, par.attr = WHITE, par.back = BLACK, par.zero = 0;
	settitle("Jakub Wyka 165734");
	Colorxpm xpm;
	xpm.ch = NULL;
	Powierzchnia p;
	p.w = 0, p.h = 0;
	Powierzchnia obrazek = load_my_file("domyslny.mff");
	Powierzchnia menu = load_my_file("menu.mff");
	Powierzchnia aktualnanazwa = load_my_file("filename.mff");
	if (argc == 2)
		obrazek = load_my_file(argv[1]);
		do {
			textbackground(BLACK + STALAPLIK);
			clrscr();
			draw(menu, MENUX, MENUY);
			write_cursor_coord(par.x, par.y);
			draw(obrazek, PICX, PICY);
			draw(aktualnanazwa, FILENAMEX, FILENAMEY);
			write_fn(obrazek);
			gotoxy(par.x, par.y);
			textcolor(par.attr + STALAPLIK);
			textbackground(par.back + STALAPLIK);
			putch('*');
			par.zero = 0;
			par.zn = getch();
			if (par.zn == 0) {
				par.zero = 1;
				par.zn = getch();
				if (par.zn == 0x48) par.y--;
				else if (par.zn == 0x50) par.y++;
				else if (par.zn == 0x4b) par.x--;
				else if (par.zn == 0x4d) par.x++;
			}
			else if (par.zn == ' ') par.attr = (par.attr + 1) % 16;
			else if (par.zn == ENTER) par.back = (par.back + 1) % 16;
			else if (par.zn == '1') par.back = 1;
			else if (par.zn == '2') par.back = 2;
			else if (par.zn == '3') par.back = 3;
			else if (par.zn == '4') par.back = 4;
			else if (par.zn == '5') par.back = 5;
			else if (par.zn == '6') par.back = 6;
			else if (par.zn == '7') par.back = 7;
			else if (par.zn == '8') par.back = 8;
			else if (par.zn == '9') par.back = 9;
			else if (par.zn == '0') par.back = 10;
			else if ((par.zn == 'q') || (par.zn == 'Q')) par.back = 11;
			else if ((par.zn == 'w') || (par.zn == 'W')) par.back = 12;
			else if ((par.zn == 'e') || (par.zn == 'E')) par.back = 13;
			else if ((par.zn == 'r') || (par.zn == 'R')) par.back = 14;
			else if ((par.zn == 't') || (par.zn == 'T')) par.back = 15;
			else if ((par.zn == 'y') || (par.zn == 'Y')) par.back = 16;
				else if ((par.zn == 'p') || (par.zn == 'P')) {
					obrazek = change_bg(obrazek, par);
				}
				else if ((par.zn == 'i') || (par.zn == 'I')) {
					obrazek = load_my_file("domyslny.mff");
				}
				else if ((par.zn == 's') || (par.zn == 'S')) {
					char format;
					char* fn = get_fn();
					if (fn[0] == '\0') {
						fn = obrazek.name;
					}
					format = file_format(fn);
					switch (format) {
					case 'm':
						 save_my_file(obrazek,fn);
						 obrazek = load_my_file(fn);
						break;

					case 'x':
						 save_XPM2(obrazek, xpm,fn);
						 obrazek = load_XPM2(fn,xpm);
						break;
					case 'e':
						break;
					}
				}
				else if ((par.zn == 'n') || (par.zn == 'N')) {
					obrazek = create_new();
				}
				else if ((par.zn == 'o') || (par.zn == 'O')) {
					char format;
					char* fn = get_fn();
					format = file_format(fn);
					switch (format) {
					case 'm':
						obrazek = load_my_file(fn);
						break;

					case 'x':
						obrazek = load_XPM2(fn, xpm);
						break;
					case 'e':
						break;
					}

				}
				else if ((par.zn == 'k') || (par.zn == 'K')) {
					obrazek = draw_rectangle(obrazek, par);
				}
				else if ((par.zn == 'l') || (par.zn == 'K')) {
					obrazek = draw_line(obrazek, par);
				}
				else if ((par.zn == 'f') || (par.zn == 'F')) {
					obrazek = kubelek(obrazek, par);
				}
		} while (par.zn != 27);
		return 0;
	}
 

