#pragma warning (disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
#include"powierzchnia.h"
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include"conio2.h"

char* xpmcolor[]{
	"#000000",
	"#0C0CC7",
	"#126601",
	"#02F1F5",
	"#D60D21",
	"#DE07DE",
	"#8B4513",
	"#D3D3D3",
	"#A9A9A9",
	"#87CEFA",
	"#0AF20E",
	"#e0ffff",
	"#ff6666",
	"#FF99FF",
	"#ECEC09",
	"#FFFFFF"
};

Powierzchnia create(int x, int y) {
	Powierzchnia p;
	p.w = x;
	p.h = y;
	p.tab = new znak[x*y];
	return p;
};

Powierzchnia load_my_file(char*fn) {
	FILE*plik = fopen(fn, "r");
	int x, y;
	fscanf(plik, "%d%d", &x, &y);
	Powierzchnia p = create(x, y);
	p.name = new char[strlen(fn)+1];
	strcpy(p.name, fn);
	char* buff = new char[x+2];
	fgetc(plik);

	for (int i = 0; i < p.h; i++) {
		fgets(buff, x + 2, plik);
		for(int j=0; j<p.w; ++j) 
		p.tab[i*p.w + j].ch = buff[j];
	}

	for (int i = 0; i < x*y; i++) {
		fscanf(plik, "%hhd %hhd", &(p.tab[i].fg), &(p.tab[i].bg));
	}

	fclose(plik);
	return p;
};

void draw(Powierzchnia p,int x, int y) {
	int startx = x;
	for (int i = 0; i < p.w*p.h; i++,((++x)-startx)<p.w?0:(y++,x=startx)) {
		gotoxy(x, y);
		textbackground(p.tab[i].bg+STALAPLIK);
		textcolor(p.tab[i].fg+STALAPLIK);
		putch(p.tab[i].ch);
	}
};	

Powierzchnia change_bg(Powierzchnia p,Parameters par) {
	int x, y;
	x = wherex();
	y = wherey();
	y = y - PICY+1;
	x = x - PICX;
	p.tab[(y-1)*(p.w)+x-1].fg = par.back;
	p.tab[(y - 1)*(p.w) + x - 1].bg = par.back;
	return p;
};

char* get_fn() {
	int x;
	Powierzchnia nameinput = load_my_file("nameinput.mff");
	draw(nameinput, NAMEINPUTX, NAMEINPUTY);
	gotoxy(NAMEINPUTX + 14, NAMEINPUTY + 1);
	textattr(15+STALAPLIK);
	textbackground(0+STALAPLIK);
	char*wsk= new char[MAXNAME];
	for (int o = 0; o<MAXNAME; o++)
		wsk[o] = '\0';
	for (int l = 0; l < MAXNAME; l++) {
		x = getche();
		if (x == ENTER) {
			l = MAXNAME;
		}
		else
			wsk[l] = (char)x;
	}
	return wsk;
}

void save_my_file(Powierzchnia p, char* fn) {
	
	
	FILE* plik = fopen(fn, "w");
	fprintf(plik, "%d %d", p.w, p.h);
	fputc('\n', plik);
	for (int i = 0; i < p.h; i++) {
		for (int j = 0; j < p.w; j++) {
			fputc('x', plik);
		}
		fputc('\n', plik);
	}
	for (int k=0; k < p.h; k++) {
		for (int l=0; l < p.w; l++) {
			fprintf(plik, "%d %d ", p.tab[p.w*k + l].fg, p.tab[p.w*k + l].bg);
		}
		fputc('\n', plik);
	};
	fclose(plik);
	return;
};

Powierzchnia create_new() {
	int x, y;
	Powierzchnia sizeinput = load_my_file("sizeinput.mff");
	draw(sizeinput, SIZEINPUTX, SIZEINPUTY);
	textattr(15+STALAPLIK);
	textbackground(0+STALAPLIK);
	gotoxy(SIZEINPUTX + 16, SIZEINPUTY+1);
	x = getche() - 48;
	x= 10 * x + getche() - 48;
	gotoxy(SIZEINPUTX + 19, SIZEINPUTY+1);
	putch('x');
	gotoxy(SIZEINPUTX + 21, SIZEINPUTY+1);
	y = getche() - 48;
	y = 10 * y + getche() - 48;
	Powierzchnia p=create(x, y);
	for (int i = 0; i < x*y; i++) {
		p.tab[i].bg = 15;
		p.tab[i].fg = 15;
		p.tab[i].ch = 'x';
	};
	char*fn=get_fn();
	p.name = fn;
	return p;
}

void write_fn(Powierzchnia obrazek) {
	textattr(15+STALAPLIK);
	textbackground(0+STALAPLIK);
	gotoxy(FILENAMEX+14, FILENAMEY+1);
	cputs(obrazek.name);
	return;
};

void write_cursor_coord(int x,int y) {
	char buffer[sizeof(int) * 3 + 1];
	textattr(15+STALAPLIK);
	textbackground(0+STALAPLIK);
	gotoxy(MENUX+23, MENUY+4);
	itoa(x, &buffer[0], 10);
	itoa(y, &buffer[3], 10);
	if (buffer[1] == '\0')
		buffer[1] = ' ';
	if (buffer[2] == '\0')
		buffer[2] = ' ';
	cputs(buffer);
	return;
};

Parameters color_and_cursor(Parameters par) {
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
	else if (par.zn == 'q') par.back = 11;
	else if (par.zn == 'w') par.back = 12;
	else if (par.zn == 'e') par.back = 13;
	else if (par.zn == 'r') par.back = 14;
	else if (par.zn == 't') par.back = 15;
	else if (par.zn == 'y') par.back = 16;
	return par;
};

Powierzchnia draw_rectangle(Powierzchnia p,Parameters par) {
	Powierzchnia prostokat = load_my_file("prostokat.mff");
	Powierzchnia start = create(p.w, p.h);
	for (int i = 0; i < p.h*p.w; i++) {
		start.tab[i] = p.tab[i];
	};
	start.name = p.name;
	int xp, yp, xk, yk;
	xp = par.x -PICX+1;
	yp = par.y-PICY+1;
	do {
	textbackground(0 + STALAPLIK);
	clrscr();
	draw(prostokat, LINIEX, LINIEY);
	draw(p, PICX, PICY);
	gotoxy(par.x, par.y);
	textbackground(par.back+STALAPLIK);
	putch('*');
	par.zero = 0;
	par.zn = getch();
	par=color_and_cursor(par);
	xk = par.x - PICX + 1;
	yk = par.y - PICY + 1;
	if (par.zn != 'k'&&par.zn != ESC) {                 
		for (int i = 0; i < p.h*p.w; i++) {
			p.tab[i] = start.tab[i];
		};
	}
	if (yk > yp) {
		for (int j = 0; j <= yk - yp; j++) {  // lewy bok,gdy yp<yk
			p.tab[xp - 1 + p.w*(yp + j - 1)].bg = par.back;
			p.tab[xp - 1 + p.w*(yp + j - 1)].fg = par.back;
			p.tab[xk - 1 + p.w*(yk - j - 1)].bg = par.back;//prawy bok
			p.tab[xk - 1 + p.w*(yk - j - 1)].fg = par.back;
		}
	}
	if (yp > yk) {
		for (int k = 0; k >= yk - yp; k--) {
			p.tab[xp - 1 + p.w*(yp + k - 1)].bg = par.back;
			p.tab[xp - 1 + p.w*(yp + k - 1)].fg = par.back;
			p.tab[xk - 1 + p.w*(yk - k - 1)].bg = par.back;
			p.tab[xk - 1 + p.w*(yk - k - 1)].fg = par.back;
		}
	}
	if (xp > xk) {
		for (int i = 0; i >= xk - xp; i--) {//pionowe
			p.tab[xp - 1 + i + p.w*(yp - 1)].bg = par.back;
			p.tab[xp - 1 + i + p.w*(yp - 1)].fg = par.back;
			p.tab[xk - 1 - i + p.w*(yk - 1)].bg = par.back;
			p.tab[xk - 1 - i + p.w*(yk - 1)].fg = par.back;
		}
	}
	if (xk > xp) {
		for (int i = 0; i < xk - xp; i++) {
			p.tab[xp - 1 + i + p.w*(yp - 1)].bg = par.back;
			p.tab[xp - 1 + i + p.w*(yp - 1)].fg = par.back;
			p.tab[xk - 1 - i + p.w*(yk - 1)].bg = par.back;
			p.tab[xk - 1 - i + p.w*(yk - 1)].fg = par.back;
		}
	}
	} while (par.zn!=ESC&& par.zn != 'k');
	if (par.zn == ESC) {
		return start;
	}
	else if (par.zn == 'k') {

			return p;
	
	}
};

Powierzchnia draw_line(Powierzchnia p, Parameters par) {
	Powierzchnia start = create(p.w, p.h);
	Powierzchnia linie = load_my_file("linie.mff");
	for (int i = 0; i < p.h*p.w; i++) {
		start.tab[i] = p.tab[i];
	};
	start.name = p.name;
	int xp, yp, xk, yk;
	xp = par.x - PICX + 1;
	yp = par.y - PICY + 1;
	do {
		textbackground(0 + STALAPLIK);
		clrscr();
		draw(linie, LINIEX, LINIEY);
		draw(p, PICX, PICY);
		gotoxy(par.x, par.y);
		textbackground(par.back + STALAPLIK);
		putch('*');
		par.zero = 0;
		par.zn = getch();
		par = color_and_cursor(par);
		xk = par.x - PICX + 1;
		yk = par.y - PICY + 1;
		if (par.zn != 'k'&&par.zn != ESC) {
			for (int i = 0; i < p.h*p.w; i++) {
				p.tab[i] = start.tab[i];
			}
		}

		if (xp == xk || yp == yk) {
			if (yk > yp) {
				for (int j = 0; j <= yk - yp; j++) {
					p.tab[xp - 1 + p.w*(yp + j - 1)].bg = par.back;
					p.tab[xp - 1 + p.w*(yp + j - 1)].fg = par.back;

				}
			}
			if (yp > yk) {
				for (int k = 0; k >= yk - yp; k--) {
					p.tab[xp - 1 + p.w*(yp + k - 1)].bg = par.back ;
					p.tab[xp - 1 + p.w*(yp + k - 1)].fg = par.back ;
				}
			}
			if (xp > xk) {
				for (int i = 0; i >= xk - xp; i--) {
					p.tab[xp - 1 + i + p.w*(yp - 1)].bg = par.back ;
					p.tab[xp - 1 + i + p.w*(yp - 1)].fg = par.back ;
				}
			}
			if (xk > xp) {
				for (int i = 0; i <= xk - xp; i++) {
					p.tab[xp - 1 + i + p.w*(yp - 1)].bg = par.back ;
					p.tab[xp - 1 + i + p.w*(yp - 1)].fg = par.back ;
				}
			}
		}
		else if (xp - xk == yp - yk) {
			if (xp > xk&&yp > yk) {
				for (int i = 0; i < xp - xk+1; i++) {
					p.tab[xp - i - 1 + p.w*(yp - i - 1)].bg = par.back ;
					p.tab[xp - i - 1 + p.w*(yp - i - 1)].fg = par.back ;
				}

			}
			if (xk > xp && yk > yp) {
				for (int i = 0; i < xk - xp+1; i++) {
					p.tab[xp + i - 1 + p.w*(yp + i - 1)].bg = par.back;
					p.tab[xp + i - 1 + p.w*(yp + i - 1)].fg = par.back;
				}
			}}
			else if (xk - xp == yp - yk) {
				if (xk > xp&&yp > yk) {
					for (int i = 0; i < xk - xp+1; i++) {
						p.tab[xp +i - 1 + p.w*(yp - i - 1)].bg = par.back;
						p.tab[xp + i - 1 + p.w*(yp - i - 1)].fg = par.back;
					}

				}
				if (xp > xk&&yk > yp) {
					for (int i = 0; i < xp - xk+1; i++) {
						p.tab[xp - i - 1 + p.w*(yp + i - 1)].bg = par.back;
						p.tab[xp - i - 1 + p.w*(yp + i - 1)].fg = par.back;
					}

				}
			}
		
			} while (par.zn != ESC&& par.zn != 'l');
			if (par.zn == ESC) {
				return start;
			}
			else if (par.zn == 'l') {

				return p;
			}
		
};

Powierzchnia load_XPM2(char*fn, Colorxpm xpm) {
	FILE*plik = fopen(fn, "r");
	int x, y, c;
	char*ptr;
	fscanf(plik, "%*[^\n]\n", NULL); // pomijamy 1 wiersz
	fscanf(plik, "%d%d%d", &x, &y,&c);
	Powierzchnia p = create(x, y);
	xpm.ch = new char[c];
	xpm.color = new int[c];
	char buffer[9];
	p.name = new char[strlen(fn) + 1];
	strcpy(p.name, fn);
	fgetc(plik);
	fgetc(plik);
	fgetc(plik);
	for (int i = 0; i < c; i++) {
		xpm.ch[i]=fgetc(plik); 
		fgetc(plik);
		fgetc(plik);
		fgetc(plik);
		fgets(buffer, 9, plik);
		for (int j = 0; j < c; j++) {
			ptr=strstr(buffer, xpmcolor[j]);
			if (ptr != NULL) {
				xpm.color[i] = j;
			}
		}
		
	}
	char* buff = new char[x + 2];
	for (int i = 0; i < p.h; i++) {
		fgets(buff, x + 2, plik);
		for (int j = 0; j < p.w; ++j) {
			p.tab[i*p.w + j].ch = buff[j];
		}
	}
	for (int k = 0; k < p.h*p.w; k++) {
		for (int l = 0; l < c; l++) {
			if (p.tab[k].ch == xpm.ch[l]) {
				p.tab[k].bg = xpm.color[l];
				p.tab[k].fg = xpm.color[l];
			}
		}
	}
	fclose(plik);
	return p;
}

void save_XPM2(Powierzchnia p, Colorxpm xpm, char* fn){

	FILE* plik = fopen(fn, "w");
	fprintf(plik, "! XPM2");
	fputc('\n', plik);
	fprintf(plik, "%d %d 16 1",p.w,p.h);
	fputc('\n', plik);
	if (xpm.ch == NULL) {
		for (int i = 0; i < 16; i++) {
			fputc(97 + i,plik);
			fprintf(plik," c ");
			fputs(xpmcolor[i], plik);
			fputc('\n', plik);
		}
			for (int k = 0; k < p.h*p.w; k++) {
				p.tab[k].ch = 97 + p.tab[k].bg;
			}
			for (int j = 0; j < p.h; j++) {
				for (int l = 0; l < p.w; l++) {
					fputc(p.tab[p.w*j+l].ch, plik);
				}
				fputc('\n', plik);
			}
	}
	else {
		for (int i = 0; i < 16; i++) {
			fputc(xpm.ch[i], plik);
			fprintf(plik, " c ");
			fputs(xpmcolor[xpm.color[i]], plik);
			fputc('\n', plik);
		}
		for (int j = 0; j < p.h; j++) {
			for (int l = 0; l < p.w; l++) {
				fputc(p.tab[p.w*j + l].ch, plik);
			}
			fputc('\n', plik);
		}
	}


	fclose(plik);
}

char file_format(char*fn) {
	char xpm[] = ".xpm";
	char mff[] = ".mff";
	char txt[] = ".txt";
	if (strstr(fn, mff) != NULL)
		return 'm';
	if (strstr(fn, txt) != NULL)
		return 'm';
	else if (strstr(fn, xpm) != NULL)
		return 'x';
	else
		return 'e'; //error
}

Powierzchnia kubelek(Powierzchnia p, Parameters par) {
	Powierzchnia start = create(p.w, p.h);
	for (int i = 0; i < p.h*p.w; i++) {
		start.tab[i] = p.tab[i];
	};
	int xp, yp;
	xp = par.x - PICX + 1;
	yp = par.y - PICY + 1;
	char zmieniany= p.tab[xp - 1 + p.w*(yp - 1)].bg;
	p.tab[xp - 1 + p.w*(yp - 1)].bg = par.back;
	p.tab[xp - 1 + p.w*(yp - 1)].fg = par.back;
	
	for (int i = 0; i < yp; i++) {
		if (zmieniany == start.tab[xp - 1 + p.w*(yp-i - 1)].bg) {//w gore
			p.tab[xp - 1  + p.w*(yp- i - 1)].bg = par.back;
			p.tab[xp - 1  + p.w*(yp- i - 1)].fg = par.back;
		for (int j = 1; j <  p.w - xp+1; j++) {
			if (zmieniany == start.tab[xp - 1 + j + p.w*(yp-i - 1)].bg) {//w prawo
			p.tab[xp - 1 + j + p.w*(yp -i - 1)].bg = par.back;
			p.tab[xp - 1 + j + p.w*(yp -i - 1)].fg = par.back;

			for (int l = 1; l < p.h - yp + i; l++) {////proba dol
				if (zmieniany == start.tab[xp +j- 1 + p.w*(yp-i + l - 1)].bg) {
					p.tab[xp - 1 + j + p.w*(yp + l-i - 1)].bg = par.back;
					p.tab[xp - 1 + j + p.w*(yp + l-i - 1)].fg = par.back;
				}
				else
					break;

			}

			for (int m = 1; m < yp - i; m++) {////proba gora
				if (zmieniany == start.tab[xp + j - 1 + p.w*(yp - i - m - 1)].bg) {
					p.tab[xp + j - 1 + p.w*(yp - m -i - 1)].bg = par.back;
					p.tab[xp + j - 1 + p.w*(yp - m - i - 1)].fg = par.back;
				}
				else
					break;

			}
			}
		else
			break;
		}
		for (int k = 1; k < xp; k++) {
			if (zmieniany == start.tab[xp - 1 - k + p.w*(yp-i - 1)].bg) {//w lewo
			p.tab[xp - 1 - k + p.w*(yp - i- 1)].bg = par.back;
			p.tab[xp - 1 - k + p.w*(yp -i - 1)].fg = par.back;

			for (int l = 1; l < p.h - yp + i; l++) {////proba dol
				if (zmieniany == start.tab[xp -k- 1 + p.w*(yp -i+ l - 1)].bg) {
					p.tab[xp - 1 -k + p.w*(yp + l - i - 1)].bg = par.back;
					p.tab[xp - 1 -k + p.w*(yp + l - i - 1)].fg = par.back;
				}
				else
					break;

			}

			for (int m = 1; m < yp - i; m++) {////proba gora
				if (zmieniany == start.tab[xp -k - 1 + p.w*(yp - i - m - 1)].bg) {
					p.tab[xp -k - 1 + p.w*(yp - m - i - 1)].bg = par.back;
					p.tab[xp -k - 1 + p.w*(yp - m - i - 1)].fg = par.back;
				}
				else
					break;

			}
			}
		else
			break;
	}
		}
		else
			break;
	}

	for (int i = 0; i < p.h - yp+1; i++) {
		if (zmieniany == start.tab[xp - 1 + p.w*(yp + i - 1)].bg) {//w dol
			p.tab[xp - 1 + p.w*(yp + i - 1)].bg = par.back;
			p.tab[xp - 1 + p.w*(yp + i - 1)].fg = par.back;
			for (int j = 1; j < p.w - xp + 1; j++) {
				if (zmieniany == start.tab[xp - 1 + j + p.w*(yp + i - 1)].bg) {//w prawo
					p.tab[xp - 1 + j + p.w*(yp + i - 1)].bg = par.back;
					p.tab[xp - 1 + j + p.w*(yp + i - 1)].fg = par.back;

					for (int l = 1; l < p.h - yp - i; l++) {////proba dol
						if (zmieniany == start.tab[xp +j- 1 + p.w*(yp + l+i - 1)].bg) {
							p.tab[xp - 1+j + p.w*(yp + l +i - 1)].bg = par.back;
							p.tab[xp - 1+j + p.w*(yp + l +i - 1)].fg = par.back;
						}
						else
							break;

					}

					for (int m = 1; m < yp + i; m++) {////proba gora
						if (zmieniany == start.tab[xp+j - 1 + p.w*(yp+i - m - 1)].bg) {
							p.tab[xp+j - 1 + p.w*(yp - m+i - 1)].bg = par.back;
							p.tab[xp+j - 1 + p.w*(yp - m+i - 1)].fg = par.back;
						}
						else
							break;

					}
				}
				else
					break;
}
				for (int k = 1; k < xp; k++) {
					if (zmieniany == start.tab[xp - 1 - k + p.w*(yp + i - 1)].bg) {//w lewo
						p.tab[xp - 1 - k + p.w*(yp + i - 1)].bg = par.back;
						p.tab[xp - 1 - k + p.w*(yp + i - 1)].fg = par.back;

						for (int l = 1; l < p.h - yp - i; l++) {////proba dol
							if (zmieniany == start.tab[xp -k- 1 + p.w*(yp + l +i - 1)].bg) {
								p.tab[xp - 1 -k  + p.w*(yp + l+i - 1)].bg = par.back;
								p.tab[xp - 1 -k + p.w*(yp + l+i - 1)].fg = par.back;
							}
							else
								break;

						}

						for (int m = 1; m < yp + i; m++) {////proba gora
							if (zmieniany == start.tab[xp -k - 1 + p.w*(yp + i - m - 1)].bg) {
								p.tab[xp -k - 1 + p.w*(yp - m + i - 1)].bg = par.back;
								p.tab[xp -k - 1 + p.w*(yp - m + i - 1)].fg = par.back;
							}
							else
								break;

						}
					}
					else
						break;
				}

		}
		else
			break;
		
	}
	return p;
}