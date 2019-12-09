#ifndef _PROCESAMIENTOIMAGENES_H_
#define _PROCESAMIENTOIMAGENES_H_


class Imagen{
	unsigned int Columnas, Filas, TotalPixeles, NumCanales, MaximoColor,NumeroMagico;
	unsigned char *Image;
	char *NombreImagen;

public:
	unsigned char* ObtenerImagen();
	unsigned int ObtenerPix();
	unsigned int ObtenerNumeroMagico();
	unsigned int ObtenerFila();
	unsigned int ObtenerColumna();
	void LeerImagen(char*);
	void GetNombre();
	void EscribirImagen(char*);
	void MostrarImagen();
	void BorrarImagen();
	//Funciones de transformacion
	void BinarizarUmbral(char*);
	void EscalaGrises(char*);
	void CanalesRGB(char*, char*, char*);
	void SumaArit(char*, Imagen);
	void RestaArit(char*, Imagen);
	void AND(char*, Imagen);
	void OR(char*, Imagen);
	void NOT(char*);
	void Histograma(char*);
	void FiltroMedia(char*);
	void FiltroMediaP(char*);
	void FiltroSobel_Prewitt(char*,int);
	void FiltroRoberts(char*);
	void FiltroMinMed(char*,int);
	void FiltroModa(char*);
	void MultiUmbral(char*);
};
	unsigned char* Orden(unsigned char*,int);
	unsigned char moda_(unsigned char*, int,unsigned char);
#endif