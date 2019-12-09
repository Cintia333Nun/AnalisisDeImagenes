/*
	Materia: Analisis De Imagen
	Prof:	 Meza Maria Elena
	Escuela: Escom
	Alumna:  Disque Nuñez Valdovinos Cintia :'v
*/

#include "procesamientoimagenes.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <string.h>
FILE *f;

using namespace std;

//Pratica 1
void Imagen::LeerImagen(char *Nombre){
	FILE 	* f;
	char	* s;
	bool    TerminarLectura = false;
	char    c;

	this->NombreImagen = Nombre;
	f = fopen (Nombre, "rb");
	if(f == NULL){
		cout<<"El archivo que especifico no existe"<<endl;
		exit;
	}

	s = (char*)calloc(256,1);
	if(s == NULL)
		cout<<"Error al reservar memoria"<<endl;
	while(!TerminarLectura && ( c = (char)fgetc(f) ) != '\0')
		switch(c){
			case 'P':
				c = (char)fgetc(f);
				switch(c){
					/*
					Portable Graymap
						El formato graymap portátil es un archivo de escala de grises 
						de denominador común más bajo formato.  
						*/
					case '2':
						this->NumeroMagico = 2;
						this->NumCanales = 1;
						break;
					case '5':
						this->NumeroMagico = 5;
						this->NumCanales = 1;
						break;
					/*
					Portable pixmap
						El formato de mapa de píxeles portátil es una imagen de color de 
						denominador común más bajo formato de archivo.
					*/
					case '3':
						this->NumeroMagico = 3;
						this->NumCanales = 3;
						break;
					case '6':
						this->NumeroMagico = 6;
						this->NumCanales = 3;
						break;
				}
				c = (char)fgetc(f);
				if (c != 0x0A)
					ungetc(c,f);
				else{
					ungetc(c,f);
					fgets(s,256,f);
				}
				break;

			case '#':
				fgets(s,256,f);
				break;

			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				ungetc(c,f);
				fscanf(f,"%d %d %d",&(this->Columnas),&(this->Filas),&(this->MaximoColor));
				TerminarLectura = true;
				fgetc(f);
				break;
		}
		this->TotalPixeles = this->Columnas*this->Filas*this->NumCanales;
		this->Image = (unsigned char*) malloc(this->TotalPixeles);
		fread(this->Image,1,this->TotalPixeles,f);
		cout<<"\nImegen leida correctamente\n"<<endl;
		cout<<"Nombre de la Imagen: "<<this->NombreImagen<<endl;
		cout<<"Numero de canales: "<<this->NumCanales<<endl;
		cout<<"Numero de columnas: "<<this->Columnas<<endl;
		cout<<"Numero de Filas: "<<this->Filas<<endl;
		cout<<"Total de pixeles: "<<this->TotalPixeles<<endl;
		cout<<"Color maximo: "<<this->MaximoColor<<endl;
		fclose(f);
}

void Imagen::GetNombre(){
	cout<<this->NombreImagen<<endl;
}

void Imagen::MostrarImagen(){
	char Comando[20] = "fim -a ";
	strcat(Comando, this->NombreImagen);
	system(Comando);
}

void Imagen::BorrarImagen(){
	char Comando[20] = "rm ";
	strcat(Comando, this->NombreImagen);
	system(Comando);
}

unsigned char* Imagen::ObtenerImagen(){
	return this->Image;
}

unsigned int Imagen::ObtenerPix(){
	return this->TotalPixeles;
}

unsigned int Imagen::ObtenerFila(){
	return this->Filas;
}

unsigned int Imagen::ObtenerColumna(){
	return this->Columnas;
}

unsigned int Imagen::ObtenerNumeroMagico(){
	return this->NumeroMagico;
}

//Practica 2
void Imagen::BinarizarUmbral(char *NuevoNombre){
	f = fopen(NuevoNombre, "w+");
	if (f == NULL)
		exit;
	fprintf(f, "P%d\n%d %d\n%d\n",this->NumeroMagico,this->Columnas,this->Filas,this->MaximoColor);

	for(int i = 0; i<this->Filas; i++)
		if(this->NumCanales == 3)
			for(int j = 0; j<(this->Columnas*this->NumCanales);)
				if(this->Image[j+(this->Columnas*i*this->NumCanales)+1]<0x63)
					for(int k = 0; k<3; k++){
						fputc(0x00,f);
						j++;
					}		
				else
					for(int k = 0; k<3; k++){
						fputc(0xFF,f);
						j++;
					}
		else
			for(int j = 0; j<(this->Columnas*this->NumCanales); j++)
				if(this->Image[j+(this->Columnas*i*this->NumCanales)]<0x63)
						fputc(0x00,f);
				else
						fputc(0xFF,f);
		

	fclose(f);
}

void Imagen::MultiUmbral(char *NuevoNombre){
	f = fopen(NuevoNombre, "w+");
	unsigned char u1 = 0x32,u2 = 0x96,u3 = 0xc8;
	if (f == NULL)
		exit;
	fprintf(f, "P%d\n%d %d\n%d\n",this->NumeroMagico,this->Columnas,this->Filas,this->MaximoColor);

	for(int i = 0; i<this->Filas; i++)
		if(this->NumCanales == 3)
			for(int j = 0; j<(this->Columnas*this->NumCanales);)
				if(this->Image[j+(this->Columnas*i*this->NumCanales)+1]<u1)
					for(int k = 0; k<3; k++){
						fputc(0xFF,f);
						j++;
					}	
				else if(this->Image[j+(this->Columnas*i*this->NumCanales)+1]>u1 && this->Image[j+(this->Columnas*i*this->NumCanales)+1]<u2)
					for(int k = 0; k<3; k++){
						fputc(this->Image[j+(this->Columnas*i*this->NumCanales)+1],f);
						j++;
					}
				else if(this->Image[j+(this->Columnas*i*this->NumCanales)+1]>u2 && this->Image[j+(this->Columnas*i*this->NumCanales)+1]>u3)
					for(int k = 0; k<3; k++){
						fputc(0x00,f);
						j++;
					}	
				else
					for(int k = 0; k<3; k++){
						fputc(0x64,f);
						j++;
					}
		else
			for(int j = 0; j<(this->Columnas*this->NumCanales);j++)
				if(this->Image[j+(this->Columnas*i*this->NumCanales)+1]<u1)
					fputc(0xFF,f);	
				else if(this->Image[j+(this->Columnas*i*this->NumCanales)+1]>u1 && this->Image[j+(this->Columnas*i*this->NumCanales)+1]<u2)
					fputc(this->Image[j+(this->Columnas*i*this->NumCanales)+1],f);
				else if(this->Image[j+(this->Columnas*i*this->NumCanales)+1]>u2 && this->Image[j+(this->Columnas*i*this->NumCanales)+1]>u3)
					fputc(0x00,f);
				else
					fputc(0x64,f);
	fclose(f);
}

//Practica 3
void Imagen::EscalaGrises(char *NuevoNombre){
	unsigned char c;

	if(this->NumeroMagico == 2 || this->NumeroMagico == 5)//Solo se aplica a imagenes de 3 canales
		return;

	f = fopen(NuevoNombre, "w+");
	if (f == NULL)
		exit;
	fprintf(f,"P%d\n%d %d\n%d\n",this->NumeroMagico,this->Columnas,this->Filas,this->MaximoColor);	
	for(int i = 0; i<this->Filas; i++)
		for(int j = 0; j<this->Columnas*3; j++){
			c = this->Image[j+(this->Columnas*3*i)]*0.3;
			j++;
			c += this->Image[j+(this->Columnas*3*i)]*0.59;
			j++;
			c += this->Image[j+(this->Columnas*3*i)]*0.11;				
		for(int k=0; k<3; k++)
			fputc(c,f);
		}
	fclose(f);
}

//Practica 4
void Imagen::CanalesRGB(char* NombreR, char* NombreG, char* NombreB){
	FILE *R,*G,*B;

	if(this->NumeroMagico == 2 || this->NumeroMagico == 5)//Solo se aplica en imagenes con 3 caneles
		return ;

	R = fopen(NombreR, "w+");
	G = fopen(NombreG, "w+");
	B = fopen(NombreB, "w+");

	if (R == NULL)
		exit;
	if (G == NULL)
		exit;
	if (B == NULL)
		exit;

	fprintf(R, "P%d\n%d %d\n%d\n",this->NumeroMagico,this->Columnas,this->Filas,this->MaximoColor);
	fprintf(G, "P%d\n%d %d\n%d\n",this->NumeroMagico,this->Columnas,this->Filas,this->MaximoColor);
	fprintf(B, "P%d\n%d %d\n%d\n",this->NumeroMagico,this->Columnas,this->Filas,this->MaximoColor);

	for(int i = 0; i<this->Filas; i++)
		for(int j = 0; j<this->Columnas*3;){
			fputc(this->Image[j+(this->Columnas*3*i)],R);
			fputc(0x00,G);
			fputc(0x00,B);
			j++;
			fputc(0x00,R);
			fputc(this->Image[j+(this->Columnas*3*i)],G);
			fputc(0x00,B);
			j++;
			fputc(0x00,R);
			fputc(0x00,G);
			fputc(this->Image[j+(this->Columnas*3*i)],B);
			j++;
		}

	fclose(R);
	fclose(G);
	fclose(B);
}

//Operaciones Aritmeticas
void Imagen::SumaArit(char* NuevoNombre, Imagen a){
	unsigned int tp,numMagic,Fil,Col;
	unsigned char* Image2, c;

	tp = a.ObtenerPix();
	Fil = a.ObtenerFila();
	Col = a.ObtenerColumna();
	numMagic = a.ObtenerNumeroMagico();
	cout<<tp<<endl<<Fil<<endl<<Col<<endl<<numMagic<<endl;

	if((tp != this->TotalPixeles)||(this->NumeroMagico != numMagic)||(this->Filas != Fil)||(this->Columnas != Col))
		return ;

	Image2 = (unsigned char*) malloc(this->TotalPixeles);
	Image2 = a.ObtenerImagen();

	f = fopen(NuevoNombre, "w+");
	if (f == NULL)
		exit;
	fprintf(f,"P%d\n%d %d\n%d\n",this->NumeroMagico,this->Columnas,this->Filas,this->MaximoColor);

	for(int i=0; i<this->Filas; i++)
		for(int j = 0; j<this->Columnas*this->NumCanales; j++){
			c = this->Image[j+(this->Columnas*i*this->NumCanales)]+Image2[j+(this->Columnas*i*this->NumCanales)];
			if(c >= 0xff)
				fputc(0xff,f);
			else
				fputc(c,f);
		}

	fclose(f);
}

void Imagen::RestaArit(char* NuevoNombre, Imagen a){
	unsigned int tp,numMagic,Fil,Col;
	unsigned char* Image2, c;

	tp = a.ObtenerPix();
	Fil = a.ObtenerFila();
	Col = a.ObtenerColumna();
	numMagic = a.ObtenerNumeroMagico();
	cout<<tp<<endl<<Fil<<endl<<Col<<endl<<numMagic<<endl;

	if((tp != this->TotalPixeles)||(this->NumeroMagico != numMagic)||(this->Filas != Fil)||(this->Columnas != Col))
		return ;

	Image2 = (unsigned char*) malloc(this->TotalPixeles);
	Image2 = a.ObtenerImagen();

	f = fopen(NuevoNombre, "w+");
	if (f == NULL)
		exit;
	fprintf(f,"P%d\n%d %d\n%d\n",this->NumeroMagico,this->Columnas,this->Filas,this->MaximoColor);

	for(int i=0; i<this->Filas; i++)
		for(int j=0; j<this->Columnas*this->NumCanales; j++){
			c = this->Image[j+(this->Columnas*i*this->NumCanales)]-Image2[j+(this->Columnas*i*this->NumCanales)];
			if(c<0x00)
				fputc(0x00,f);
			else
				fputc(c,f);
		}

	fclose(f);
}

//Operaciones logicas 
void Imagen::AND(char* NuevoNombre, Imagen a){
	unsigned int tp,numMagic,Fil,Col;
	unsigned char* Image2, c;

	tp = a.ObtenerPix();
	Fil = a.ObtenerFila();
	Col = a.ObtenerColumna();
	numMagic = a.ObtenerNumeroMagico();

	if((tp != this->TotalPixeles)||(this->NumeroMagico != numMagic)||(this->Filas != Fil)||(this->Columnas != Col))
		return ;

	Image2 = (unsigned char*) malloc(this->TotalPixeles);
	Image2 = a.ObtenerImagen();

	f = fopen(NuevoNombre, "w+");
	if (f == NULL)
		exit;
	fprintf(f,"P%d\n%d %d\n%d\n",this->NumeroMagico,this->Columnas,this->Filas,this->MaximoColor);

	for(int i=0; i<this->Filas; i++)
		for(int j=0; j<this->Columnas*this->NumCanales; j++){
			c = this->Image[j+(this->Columnas*i*this->NumCanales)]&Image2[j+(this->Columnas*i*this->NumCanales)];
			if(c<0x00)
				fputc(0x00,f);
			else if(c>0xff)
				fputc(0xff,f);
			else
				fputc(c,f);
		}
		
	fclose(f);
}

void Imagen::OR(char* NuevoNombre, Imagen a){
	unsigned int tp,numMagic,Fil,Col;
	unsigned char* Image2, c;

	tp = a.ObtenerPix();
	Fil = a.ObtenerFila();
	Col = a.ObtenerColumna();
	numMagic = a.ObtenerNumeroMagico();

	if((tp != this->TotalPixeles)||(this->NumeroMagico != numMagic)||(this->Filas != Fil)||(this->Columnas != Col))
		return ;

	Image2 = (unsigned char*) malloc(this->TotalPixeles);
	Image2 = a.ObtenerImagen();

	f = fopen(NuevoNombre, "w+");
	if (f == NULL)
		exit;
	fprintf(f,"P%d\n%d %d\n%d\n",this->NumeroMagico,this->Columnas,this->Filas,this->MaximoColor);

	for(int i=0; i<this->Filas; i++)
		for(int j=0; j<this->Columnas*this->NumCanales; j++){
			c = this->Image[j+(this->Columnas*i*this->NumCanales)]|Image2[j+(this->Columnas*i*this->NumCanales)];
			if(c<0x00)
				fputc(0x00,f);
			else if(c>0xff)
				fputc(0xff,f);
			else
				fputc(c,f);
		}
		
	fclose(f);
}

void Imagen::NOT(char* NuevoNombre){
	unsigned char c;

	f = fopen(NuevoNombre, "w+");
	if (f == NULL)
		exit;
	fprintf(f,"P%d\n%d %d\n%d\n",this->NumeroMagico,this->Columnas,this->Filas,this->MaximoColor);

	for(int i=0; i<this->Filas; i++)
		for(int j=0; j<this->Columnas*this->NumCanales; j++){
			//c = ~this->Image[j+(this->Columnas*i*this->NumCanales)];
			c = 255-this->Image[j+(this->Columnas*i*this->NumCanales)];
			fputc(c,f);
		}
		
	fclose(f);
}

void Imagen::Histograma(char* NuevoNombre){
	unsigned int MaxHistogram;
	unsigned char *Histogram, *imgHistogram,*Image2;
	bool bandera = false;
	int hr, hg, hb, hgr, hrgb;

	f = fopen(NuevoNombre, "w+");
	if (f == NULL)
		exit;

	Histogram = (unsigned char *)malloc(this->MaximoColor*this->NumCanales);
	Image2 = (unsigned char *)malloc(this->TotalPixeles*sizeof(unsigned char));
	Image2 = this->Image;

	if(this->NumCanales == 3)
		bandera = true;

	if(bandera){
		hr = this->Image[0];
		hg = this->Image[1];
		hb = this->Image[2];
		for(int i = 0; i<this->TotalPixeles/this->NumCanales; i++)
			for(int j = 0; j<this->NumCanales; j++)
				Histogram[this->Image[i*this->NumCanales+j]] += 1;
	}else{
		hgr = this->Image[0];
		for(int i = 0; i<this->TotalPixeles; i++)
			Histogram[this->Image[i]] += 1;
	}

	if (bandera){
		for (int i = 0; i < this->MaximoColor; i++){
			if(Histogram[i*this->NumCanales] > hr)
				hr = Histogram[i*this->NumCanales];
			if(Histogram[i*this->NumCanales+1] > hg)
				hg = Histogram[i*this->NumCanales+1];
			if(Histogram[i*this->NumCanales+2] > hb)
				hb = Histogram[i*this->NumCanales+2];
		}

		hrgb = hr;
		if(hrgb < hg){
			if(hg < hb)
				hrgb = hb;
			else
				hrgb = hg;
		}
		if(hrgb < hg){
			if(hr < hb)
				hrgb = hb;
		}
		imgHistogram = (unsigned char*)malloc((hrgb+10)*this->MaximoColor*this->NumCanales);//TotalPixels
	}else{
		for (int i = 0; i < this->MaximoColor; i++)
			if(Histogram[i] > hgr)
				hgr = Histogram[i];
		imgHistogram = (unsigned char*)malloc((hgr+10)*this->MaximoColor*this->NumCanales);	
	}

	if (bandera)
		MaxHistogram = hrgb; 
	else
		MaxHistogram = hgr;

	fprintf(f,"P%d\n%d %d\n%d\n",this->NumeroMagico,this->MaximoColor,MaxHistogram,255);
	for(int i=0; i<this->MaximoColor; i++)
		for(int j=0; j<this->MaximoColor; j++)
			for (int k = 0; k < this->NumCanales; k++){
				if(MaxHistogram - i < Histogram[j+k])
					imgHistogram[j+k+i*this->MaximoColor*this->NumCanales] = 255;
				else
					imgHistogram[j+k+i*this->MaximoColor*this->NumCanales] = 0;
			}
	
	for(int i=0; i<(MaxHistogram*this->MaximoColor*this->NumCanales); i++)
		fputc(imgHistogram[i],f);

	fclose(f);
}

//Filtros pasa bajas
void Imagen::FiltroMedia(char* NuevoNombre){
	unsigned char r,g,b;
	int limitemx = this->NumCanales*2;

	f = fopen(NuevoNombre, "w+");
	if (f == NULL)
		exit;

	fprintf(f,"P%d\n%d %d\n%d\n",this->NumeroMagico,this->Columnas,this->Filas,this->MaximoColor);

	for(int i = 0; i<this->Filas; i++)
		for(int j = 0; j<this->Columnas*this->NumCanales; j++){
			r = 0x00;
			g = 0x00;
			b = 0x00;		
			for(int my = -1; my<2; my++)
				for(int mx = -1*this->NumCanales; mx<limitemx; mx++)
					if(i+my<0 || i+my>this->Filas || j+mx<0 || j+mx>this->Columnas*this->NumCanales)
						if(this->NumCanales == 1)
							r += 0;
						else{
							r += 0;mx++;
							g += 0;mx++;
							b += 0;
						}
					else
						if(this->NumCanales == 1)
							r += (int)this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]/9;
						else{
							r += (int)this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]/9;mx++;
							g += (int)this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]/9;mx++;
							b += (int)this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]/9;
						}

					if(this->NumCanales == 1)
						fputc(r,f);
					else{
						j++;j++;
						fputc(r,f);
						fputc(g,f);
						fputc(b,f);
					}
		}	
	fclose(f);
}

void Imagen::FiltroMediaP(char* NuevoNombre){
	unsigned char r,g,b;
	int limitemx = this->NumCanales*2, n = 5;

	f = fopen(NuevoNombre, "w+");
	if (f == NULL)
		exit;
	fprintf(f,"P%d\n%d %d\n%d\n",this->NumeroMagico,this->Columnas,this->Filas,this->MaximoColor);

	for(int i = 0; i<this->Filas; i++)
		for(int j = 0; j<this->Columnas*this->NumCanales; j++){
			r = 0x00;
			g = 0x00;
			b = 0x00;
			for(int my = -1; my<2; my++)
				for(int mx = -1*this->NumCanales; mx<limitemx; mx++)
					if(i+my<0 || i+my>this->Filas || j+mx<0 || j+mx>this->Columnas*this->NumCanales)
						if(this->NumCanales == 1)
							r += 0;
						else{
							r += 0;mx++;
							g += 0;mx++;
							b += 0;
						}
					else
						if(this->NumCanales == 1)
							if(j+mx == j && i+my == i)
								r += (int)(this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]*n)/(n+8);
							else
								r += (int)this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]/(n+8);
						else
							if(j+mx == j && i+my == i){
								r += (int)(this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]*n)/(n+8);
								mx++;
								g += (int)(this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]*n)/(n+8);
								mx++;
								b += (int)(this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]*n)/(n+8);
							}else{
								r += (int)this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]/(n+8);
								mx++;
								g += (int)this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]/(n+8);
								mx++;
								b += (int)this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]/(n+8);
							}
				if(this->NumCanales == 1)
					fputc(r,f);	
				else{
					j++;j++;
					fputc(r,f);
					fputc(g,f);
					fputc(b,f);
				}	
		}
	fclose(f);
}

//Filtros pasa altas
void Imagen::FiltroSobel_Prewitt(char* NuevoNombre, int n){// Prewitt n=1, sobel=2 
	unsigned char r,g,b, GradienteX_r, GradienteX_g, GradienteX_b, GradienteY_r, GradienteY_g, GradienteY_b;
	int limitemx = this->NumCanales*2;
	int GradienteX[3][3]{ {1,0,-1}, {n,0,-n}, {1,0,-1} };
	int GradienteY[3][3]{ {-1,-n,-1}, {n,1,-n}, {1,n,1} };

	f = fopen(NuevoNombre, "w+");
	if (f == NULL)
		exit;
	fprintf(f,"P%d\n%d %d\n%d\n",this->NumeroMagico,this->Columnas,this->Filas,this->MaximoColor);

	for(int i = 0; i<this->Filas; i++)
		for(int j = 0; j<this->Columnas*this->NumCanales; j++){
			GradienteX_r = 0x00; GradienteY_r = 0x00;
			GradienteX_g = 0x00; GradienteY_g = 0x00;
			GradienteX_b = 0x00; GradienteY_b = 0x00;
			for(int my = -1; my<2; my++)
				for(int mx = -1*this->NumCanales; mx<limitemx; mx++)
					if(i+my<0 || i+my>this->Filas || j+mx<0 || j+mx>this->Columnas*this->NumCanales)
						if(this->NumCanales == 1){
							GradienteX_r += 0; 
							GradienteY_r += 0;
						}
						else{
							GradienteX_r += 0; GradienteY_r += 0; mx++;
							GradienteX_g += 0; GradienteY_g += 0; mx++;
							GradienteX_b += 0; GradienteY_b += 0;
						}
					else
						if(this->NumCanales == 1){
							GradienteX_r += (int)(this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]*GradienteX[my+1][mx+1])/(n+2);
							GradienteY_r += (int)(this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]*GradienteY[my+1][mx+1])/(n+2);
						}

						else{
							GradienteX_r += (int)(this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]*GradienteX[my+1][mx-(3*my)])/(n+2);
							GradienteY_r += (int)(this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]*GradienteY[my+1][mx-(3*my)])/(n+2);
							mx++;
							GradienteX_g += (int)(this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]*GradienteX[my+1][mx-(3*my)-1])/(n+2);
							GradienteY_g += (int)(this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]*GradienteY[my+1][mx-(3*my)-1])/(n+2);
							mx++;
							GradienteX_b += (int)(this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]*GradienteX[my+1][mx-(3*my)-2])/(n+2);
							GradienteY_b += (int)(this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]*GradienteY[my+1][mx-(3*my)-2])/(n+2);
						}
				if(this->NumCanales == 1){
					r = (int)sqrt(pow(GradienteX_r,2)+pow(GradienteY_r,2));
					fputc(r,f);	
				}
				else{
					j++;j++;
					r = (int)sqrt(pow(GradienteX_r,2)+pow(GradienteY_r,2));
					g = (int)sqrt(pow(GradienteX_g,2)+pow(GradienteY_g,2));
					b = (int)sqrt(pow(GradienteX_b,2)+pow(GradienteY_b,2));
					fputc(r,f);
					fputc(g,f);
					fputc(b,f);
				}	
		}
	fclose(f);
}

void Imagen::FiltroRoberts(char* NuevoNombre){
	unsigned char r,g,b, GradienteX_r, GradienteX_g, GradienteX_b, GradienteY_r, GradienteY_g, GradienteY_b;
	int limitemx = this->NumCanales*2;
	int GradienteX[3][3]{ {0,0,0}, {0,0,1}, {0,-1,0} };
	int GradienteY[3][3]{ {-1,0,0}, {0,1,0}, {0,0,0} };

	f = fopen(NuevoNombre, "w+");
	if (f == NULL)
		exit;
	fprintf(f,"P%d\n%d %d\n%d\n",this->NumeroMagico,this->Columnas,this->Filas,this->MaximoColor);

	for(int i = 0; i<this->Filas; i++)
		for(int j = 0; j<this->Columnas*this->NumCanales; j++){
			GradienteX_r = 0x00; GradienteY_r = 0x00;
			GradienteX_g = 0x00; GradienteY_g = 0x00;
			GradienteX_b = 0x00; GradienteY_b = 0x00;
			for(int my = -1; my<2; my++)
				for(int mx = -1*this->NumCanales; mx<limitemx; mx++)
					if(i+my<0 || i+my>this->Filas || j+mx<0 || j+mx>this->Columnas*this->NumCanales)
						if(this->NumCanales == 1){
							GradienteX_r += 0; 
							GradienteY_r += 0;
						}
						else{
							GradienteX_r += 0; GradienteY_r += 0; mx++;
							GradienteX_g += 0; GradienteY_g += 0; mx++;
							GradienteX_b += 0; GradienteY_b += 0;
						}
					else
						if(this->NumCanales == 1){
							GradienteX_r += (int)(this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]*GradienteX[my+1][mx+1]);
							GradienteY_r += (int)(this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]*GradienteY[my+1][mx+1]);
						}
						else{
							GradienteX_r += (int)(this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]*GradienteX[my+1][mx-(3*my)]);
							GradienteY_r += (int)(this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]*GradienteY[my+1][mx-(3*my)]);
							mx++;
							GradienteX_g += (int)(this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]*GradienteX[my+1][mx-(3*my)-1]);
							GradienteY_g += (int)(this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]*GradienteY[my+1][mx-(3*my)-1]);
							mx++;
							GradienteX_b += (int)(this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]*GradienteX[my+1][mx-(3*my)-2]);
							GradienteY_b += (int)(this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]*GradienteY[my+1][mx-(3*my)-2]);
						}	
				if(this->NumCanales == 1){
					r = (int)sqrt(pow(GradienteX_r,2)+pow(GradienteY_r,2));
					fputc(r,f);	
				}
				else{
					j++;j++;
					r = (int)sqrt(pow(GradienteX_r,2)+pow(GradienteY_r,2));
					g = (int)sqrt(pow(GradienteX_g,2)+pow(GradienteY_g,2));
					b = (int)sqrt(pow(GradienteX_b,2)+pow(GradienteY_b,2));
					fputc(r,f);
					fputc(g,f);
					fputc(b,f);
				}	
		}
	fclose(f);
}

//Filtros pasa bandas y no lineales
void Imagen::FiltroMinMed(char* NuevoNombre,int l){
	unsigned char r,g,b,*Filtro_r,*Filtro_g,*Filtro_b;
	int limitemx = this->NumCanales*2;

	Filtro_r = (unsigned char*) malloc (9*sizeof(char));
	Filtro_g = (unsigned char*) malloc (9*sizeof(char));
	Filtro_b = (unsigned char*) malloc (9*sizeof(char));

	f = fopen(NuevoNombre, "w+");
	if (f == NULL)
		exit;
	fprintf(f,"P%d\n%d %d\n%d\n",this->NumeroMagico,this->Columnas,this->Filas,this->MaximoColor);

	for(int i = 0; i<this->Filas; i++)
		for(int j = 0; j<this->Columnas*this->NumCanales; j++){
			for(int my = -1; my<2; my++)
				for(int mx = -1*this->NumCanales; mx<limitemx; mx++)
					if(i+my<0 || i+my>this->Filas || j+mx<0 || j+mx>this->Columnas*this->NumCanales)
						if(this->NumCanales == 1)
							Filtro_r[my+mx+2] = 0; 
						else{
							Filtro_r[my+mx+2] = 0; mx++;
							Filtro_g[my+mx+2] = 0; mx++;
							Filtro_b[my+mx+2] = 0;
						}
					else
						if(this->NumCanales == 1)
							Filtro_r[my+mx+2] = this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]; 
						else{
							Filtro_r[my+mx+2] = this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]; 
							mx++;
							Filtro_g[my+mx+2] = this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]; 
							mx++;
							Filtro_b[my+mx+2] = this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)];
						}
					
				if(this->NumCanales == 1){
					Filtro_r = Orden(Filtro_r,9);
					r = (int) Filtro_r[l];
					fputc(r,f);	
				}
				else{
					j++;j++;
					Filtro_r = Orden(Filtro_r,9);
					Filtro_g = Orden(Filtro_g,9);
					Filtro_b = Orden(Filtro_b,9);
					fputc((int)Filtro_r[l],f);
					fputc((int)Filtro_g[l],f);
					fputc((int)Filtro_b[l],f);
				}
		}
	fclose(f);
}

void Imagen::FiltroModa(char* NuevoNombre){
	unsigned char r,g,b,*Filtro_r,*Filtro_g,*Filtro_b;
	int limitemx = this->NumCanales*2;

	Filtro_r = (unsigned char*) malloc (9*sizeof(char));
	Filtro_g = (unsigned char*) malloc (9*sizeof(char));
	Filtro_b = (unsigned char*) malloc (9*sizeof(char));

	f = fopen(NuevoNombre, "w+");
	if (f == NULL)
		exit;
	fprintf(f,"P%d\n%d %d\n%d\n",this->NumeroMagico,this->Columnas,this->Filas,this->MaximoColor);

	for(int i = 0; i<this->Filas; i++)
		for(int j = 0; j<this->Columnas*this->NumCanales; j++){
			for(int my = -1; my<2; my++)
				for(int mx = -1*this->NumCanales; mx<limitemx; mx++)
					if(i+my<0 || i+my>this->Filas || j+mx<0 || j+mx>this->Columnas*this->NumCanales)
						if(this->NumCanales == 1)
							Filtro_r[my+mx+2] = 0; 
						else{
							Filtro_r[my+mx+2] = 0; mx++;
							Filtro_g[my+mx+2] = 0; mx++;
							Filtro_b[my+mx+2] = 0;
						}
					else
						if(this->NumCanales == 1)
							Filtro_r[my+mx+2] = this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]; 
						else{
							Filtro_r[my+mx+2] = this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]; 
							mx++;
							Filtro_g[my+mx+2] = this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)]; 
							mx++;
							Filtro_b[my+mx+2] = this->Image[j+mx+(this->Columnas*(i+my)*this->NumCanales)];
						}
					
				if(this->NumCanales == 1){
					r = (int)moda_(Filtro_r,9,this->Image[j+(this->Columnas*i*this->NumCanales)]);
					fputc(r,f);	
				}
				else{
					r = (int)moda_(Filtro_r,9,this->Image[j+(this->Columnas*i*this->NumCanales)]);
					g = (int)moda_(Filtro_g,9,this->Image[j+1+(this->Columnas*i*this->NumCanales)]);
					b = (int)moda_(Filtro_b,9,this->Image[j+2+(this->Columnas*i*this->NumCanales)]);
					j++;j++;
					fputc(r,f);
					fputc(g,f);
					fputc(b,f);
				}
		}
	fclose(f);
}

unsigned char* Orden(unsigned char* n, int cn){//Metodo de ordenamiento: Burbuja
	unsigned char aux;

 	for(int i=1; i<cn; i++)
		for(int j=0; j<cn-i; j++)
			if(n[j]>n[j+1]){
			    aux    = n[j+1];
				n[j+1] = n[j];
				n[j]   = aux;
			}

	return n;
}

unsigned char moda_(unsigned char* n, int cn,unsigned char valor){
	unsigned char temp,max = 0,moda,*frec; 
	frec = (unsigned char*) malloc (255*sizeof(unsigned char));
	for(int i = 0 ; i < 255; i++)
		frec[i] = 0;

	for(int i = 0 ; i < cn; i++)
		frec[n[i]] += 1;

	for(int i = 0 ; i < 255; i++)
		if(max>frec[i]){
			max = frec[i];
			moda = i;
		}

	if(max <= 1)
		return valor;
	else 
		return moda;
}