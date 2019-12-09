#include "procesamientoimagenes.h"
#include <iostream>
#include <string.h>

using namespace std;

int main(int argc, char const *argv[]){
	int e, o, contador = 0, ig, a;
	
	char Nombre[30][20], Temp[20];
	Imagen n[30];

	while(true){
		system("clear");
		cout<<"ANALISIS DE IMAGENES"<<endl;
		cout<<"1. Imagenes"<<endl;
		cout<<"2. Binarizar imagen con x umbral."<<endl;
		cout<<"3. Convertir Imagen de color a escala de grises."<<endl;
		cout<<"4. Imagen por canales RGB."<<endl;
		cout<<"5. Operaciones aritmeticas(+,-)."<<endl;
		cout<<"6. Operaciones logicas(AND,OR,NOT)."<<endl;
		cout<<"7. Histograma."<<endl;
		cout<<"8. Seccion de filtrado."<<endl;
		cout<<"9. Multi-Umbral."<<endl;
		cout<<"10. Salir."<<endl;
		cout<<"\nQue accion desea realizar: "<<endl;
		cin>>e;

		switch (e){	
			case 1://Opciones con imagen
				system("clear");
				cout<<"Opciones"<<endl;
				cout<<"1. Abrir imagen"<<endl;
				cout<<"2. Guardar imagen"<<endl;
				cout<<"3. Deshacer tecnica a imagen"<<endl;
				cout<<"\nQue accion desea realizar: "<<endl;
				cin>>o;
				switch (o){
					case 1://Mostrar Imagen
						if(contador > 0){
							cout<<"Imagenes Guardadas:"<<endl;
							for(int i = 0; i < contador; i++){
								cout<<"Numero:"<<i<<"   Nombre: ";
								n[i].GetNombre();
							}
							cout<<"Que imagen desea ver (Numero):"<<endl;
							cin>>ig;
							n[ig].MostrarImagen();
						}
						break;

					case 2://Guardar una imagen
						if(contador < 30){
							cout<<"Ingresar nombre de la imagen (nombre.pgm/ppm):"<<endl;
							cin>>Nombre[contador];
							n[contador].LeerImagen(Nombre[contador]);
							contador++;
						}
						break;

					case 3://Deshacer
						if(contador > 0){
							n[contador-1].BorrarImagen();
							contador--;
						}
						break;

					default:
						break;
					}
				system("clear");
				break;

			case 2://Binarizar
				system("clear");
				if(contador > 0 && contador < 30){
					cout<<"Imagenes Guardadas:"<<endl;
					for(int i = 0; i < contador; i++){
						cout<<"Numero:"<<i<<"   Nombre: ";
						n[i].GetNombre();
					}
					cout<<"Que imagen desea BINARIZAR (Numero):"<<endl;
					cin>>ig;
					cout<<"Umbral=99\nNombre de la imagen (NuevoNombre.pgm/ppm) si existe se modificara:"<<endl;
					cin>>Nombre[contador];
					n[ig].BinarizarUmbral(Nombre[contador]);
					n[contador].LeerImagen(Nombre[contador]);
					contador++;
				}
				system("clear");
				break;

			case 9://MultiUmbral
				system("clear");
				if(contador > 0 && contador < 30){
					cout<<"Imagenes Guardadas:"<<endl;
					for(int i = 0; i < contador; i++){
						cout<<"Numero:"<<i<<"   Nombre: ";
						n[i].GetNombre();
					}
					cout<<"Que imagen desea aplicarle Muli-Umbral (Numero):"<<endl;
					cin>>ig;
					cout<<"Umbral=99\nNombre de la imagen (NuevoNombre.pgm/ppm) si existe se modificara:"<<endl;
					cin>>Nombre[contador];
					n[ig].MultiUmbral(Nombre[contador]);
					n[contador].LeerImagen(Nombre[contador]);
					contador++;
				}
				system("clear");
				break;

			case 3://Escala de grises
				system("clear");
				if(contador > 0 && contador < 30){
					cout<<"Imagenes Guardadas:"<<endl;
					for(int i = 0; i < contador; i++){
						cout<<"Numero:"<<i<<"   Nombre: ";
						n[i].GetNombre();
					}
					cout<<"Que imagen desea transformar a ESCALA DE GRISES (Numero):"<<endl;
					cin>>ig;
					cout<<"Nombre de la imagen (Nombre.ppm) si existe se modificara:"<<endl;
					cin>>Nombre[contador];
					n[ig].EscalaGrises(Nombre[contador]);
					n[contador].LeerImagen(Nombre[contador]);
					contador++;
				}
				break;

			case 4://Canales RGB
				system("clear");
				if(contador > 0){
					cout<<"Imagenes Guardadas:"<<endl;
					for(int i = 0; i < contador; i++){
						cout<<"Numero:"<<i<<"   Nombre: ";
						n[i].GetNombre();
					}
					cout<<"Que imagen desea sacar sus CANALES RGB (Numero):"<<endl;
					cin>>ig;
					n[ig].CanalesRGB((char*)"0R.ppm", (char*)"0G.ppm", (char*)"0B.ppm");
				}
				system("clear");
				break;

			case 5://Operaciones aritmeticas
				system("clear");
				cout<<"OPERACIONES ARITMETICAS"<<endl;
				cout<<"1. Suma"<<endl;
				cout<<"2. Resta"<<endl;
				cout<<"\nQue accion desea realizar: "<<endl;
				cin>>o;
				switch (o){
					case 1://Suma aritmetica
						system("clear");
						if(contador > 1){
							cout<<"Imagenes Guardadas:"<<endl;
							for(int i = 0; i < contador; i++){
								cout<<"Numero:"<<i<<"   Nombre: ";
								n[i].GetNombre();
							}
							cout<<"Que imagen desea sumar (Numero):"<<endl;
							cin>>ig;
							cout<<"Con cual (Numero):"<<endl;
							cin>>a;
							cout<<"Nombre de la imagen (Nombre.pgm/ppm) si existe se modificara:"<<endl;
							cin>>Nombre[contador];
							n[ig].SumaArit(Nombre[contador], n[a]);
							n[contador].LeerImagen(Nombre[contador]);
							contador++;
						}
						break;

					case 2://Resta Aritmetica
						system("clear");
						if(contador > 1){
							cout<<"Imagenes Guardadas:"<<endl;
							for(int i = 0; i < contador; i++){
								cout<<"Numero:"<<i<<"   Nombre: ";
								n[i].GetNombre();
							}
							cout<<"Que imagen desea restar (Numero):"<<endl;
							cin>>ig;
							cout<<"Con cual (Numero):"<<endl;
							cin>>a;
							cout<<"Nombre de la imagen (Nombre.pgm/ppm) si existe se modificara:"<<endl;
							cin>>Nombre[contador];
							n[ig].RestaArit(Nombre[contador], n[a]);
							n[contador].LeerImagen(Nombre[contador]);
							contador++;
						}	
						break;

					default :
						break;
				}
				system("clear");
				break;

			case 6://Operaciones logicas
				system("clear");
				cout<<"OPERACIONES LOGICAS"<<endl;
				cout<<"1. AND"<<endl;
				cout<<"2. OR"<<endl;
				cout<<"3. NOT"<<endl;
				cout<<"\nQue accion desea realizar: "<<endl;
				cin>>o;
				switch (o){
					case 1://AND
						system("clear");
						if(contador > 0){
							cout<<"Imagenes Guardadas:"<<endl;
							for(int i = 0; i < contador; i++){
								cout<<"Numero:"<<i<<"   Nombre: ";
								n[i].GetNombre();
							}
							cout<<"Que imagen desea aplicar compuerta AND (Numero):"<<endl;
							cin>>ig;
							cout<<"Con cual (Numero):"<<endl;
							cin>>a;
							cout<<"Nombre de la imagen (Nombre.pgm/ppm) si existe se modificara:"<<endl;
							cin>>Nombre[contador];
							n[ig].AND(Nombre[contador], n[a]);
							n[contador].LeerImagen(Nombre[contador]);
							contador++;
						}
						break;

					case 2://OR
						system("clear");
						if(contador > 0){
							cout<<"Imagenes Guardadas:"<<endl;
							for(int i = 0; i < contador; i++){
								cout<<"Numero:"<<i<<"   Nombre: ";
								n[i].GetNombre();
							}
							cout<<"Que imagen desea aplicar compuerta OR (Numero):"<<endl;
							cin>>ig;
							cout<<"Con cual (Numero):"<<endl;
							cin>>a;
							cout<<"Nombre de la imagen (Nombre.pgm/ppm) si existe se modificara:"<<endl;
							cin>>Nombre[contador];
							n[ig].OR(Nombre[contador], n[a]);
							n[contador].LeerImagen(Nombre[contador]);
							contador++;
						}
						break;

					case 3://NOT
						system("clear");
						if(contador > 0){
							cout<<"Imagenes Guardadas:"<<endl;
							for(int i = 0; i < contador; i++){
								cout<<"Numero:"<<i<<"   Nombre: ";
								n[i].GetNombre();
							}
							cout<<"Que imagen desea aplicarle una operacion NOT (Numero):"<<endl;
							cin>>ig;
							cout<<"Nombre de la imagen (Nombre.pgm/ppm) si existe se modificara:"<<endl;
							cin>>Nombre[contador];
							n[ig].NOT(Nombre[contador]);
							n[contador].LeerImagen(Nombre[contador]);
							contador++;
						}
						break;

					default:
					break;
				}
				system("clear");
				break;

			case 7://Histograma
				system("clear");
				if(contador > 0){
					cout<<"Imagenes Guardadas:"<<endl;
					for(int i = 0; i < contador; i++){
						cout<<"Numero:"<<i<<"   Nombre: ";
						n[i].GetNombre();
					}
					cout<<"De cual imagen desea obtener su histograma:"<<endl;
					cin>>ig;
					cout<<"Formato de imagen: "<<endl;
					cout<<"1. PPM "<<endl;
					cout<<"2. PGM "<<endl;
					cin>>o;
					if(o == 1){
						n[ig].Histograma((char*)"h.ppm");
						system((char*)"fim -a h.ppm");
						system((char*)"rm h.ppm");

						}
					if(o == 2){
						n[ig].Histograma((char*)"h.pgm");
						system((char*)"fim -a h.pgm");
						system((char*)"rm h.pgm");
					}
				}
					system("clear");
					break;

			case 8://Filtros pasa bajas, pasa altas, pasa banda
				system("clear");
				cout<<"FILTROS"<<endl;
				cout<<"1. Filtro Media"<<endl;
				cout<<"2. Filtro Media Ponderada"<<endl;
				cout<<"3. Filtro Sobel"<<endl;
				cout<<"4. Filtro Prewitt"<<endl;
				cout<<"5. Filtro Roberts"<<endl;
				cout<<"6. Filtro Mediana"<<endl;
				cout<<"7. Filtro Moda"<<endl;
				cout<<"8. Filtro Minimo"<<endl;
				cout<<"\nQue accion desea realizar: "<<endl;
				cin>>o;
				switch (o){
					case 1://Filtro Media
						system("clear");
						if(contador > 0){
							cout<<"Imagenes Guardadas:"<<endl;
							for(int i = 0; i < contador; i++){
								cout<<"Numero:"<<i<<"   Nombre: ";
								n[i].GetNombre();
							}
							cout<<"Que imagen desea aplicarle el filtro pasa bajas MEDIA (Numero):"<<endl;
							cin>>ig;
							cout<<"Nombre de la imagen (Nombre.pgm/ppm) si existe se modificara:"<<endl;
							cin>>Nombre[contador];
							n[ig].FiltroMedia(Nombre[contador]);
							n[contador].LeerImagen(Nombre[contador]);
							contador++;
						}
						break;

					case 2://Filtro Media Pnderada
						system("clear");
						if(contador > 0){
							cout<<"Imagenes Guardadas:"<<endl;
							for(int i = 0; i < contador; i++){
								cout<<"Numero:"<<i<<"   Nombre: ";
								n[i].GetNombre();
							}
							cout<<"Que imagen desea aplicarle el filtro pasa bajas MEDIA PONDERADA (Numero):"<<endl;
							cin>>ig;
							cout<<"Nombre de la imagen (Nombre.pgm/ppm) si existe se modificara:"<<endl;
							cin>>Nombre[contador];
							n[ig].FiltroMediaP(Nombre[contador]);
							n[contador].LeerImagen(Nombre[contador]);
							contador++;
						}
						break;

					case 3://Filtro Sobel
						system("clear");
						if(contador > 0){
							cout<<"Imagenes Guardadas:"<<endl;
							for(int i = 0; i < contador; i++){
								cout<<"Numero:"<<i<<"   Nombre: ";
								n[i].GetNombre();
							}
							cout<<"Que imagen desea aplicarle el filtro pasa altas Sobel (Numero):"<<endl;
							cin>>ig;
							cout<<"Nombre de la imagen (Nombre.pgm/ppm) si existe se modificara:"<<endl;
							cin>>Nombre[contador];
							n[ig].FiltroSobel_Prewitt(Nombre[contador],2);
							n[contador].LeerImagen(Nombre[contador]);
							n[contador].BinarizarUmbral(Nombre[contador]);
							n[contador].LeerImagen(Nombre[contador]);
							contador++;
						}
						break;

					case 4://Filtro Prewitt
						system("clear");
						if(contador > 0){
							cout<<"Imagenes Guardadas:"<<endl;
							for(int i = 0; i < contador; i++){
								cout<<"Numero:"<<i<<"   Nombre: ";
								n[i].GetNombre();
							}
							cout<<"Que imagen desea aplicarle el filtro pasa altas Prewitt (Numero):"<<endl;
							cin>>ig;
							cout<<"Nombre de la imagen (Nombre.pgm/ppm) si existe se modificara:"<<endl;
							cin>>Nombre[contador];
							n[ig].FiltroSobel_Prewitt(Nombre[contador],1);
							n[contador].LeerImagen(Nombre[contador]);
							n[contador].BinarizarUmbral(Nombre[contador]);
							n[contador].LeerImagen(Nombre[contador]);
							contador++;
						}
						break;

					case 5://Filtro Roberts
						system("clear");
						if(contador > 0){
							cout<<"Imagenes Guardadas:"<<endl;
							for(int i = 0; i < contador; i++){
								cout<<"Numero:"<<i<<"   Nombre: ";
								n[i].GetNombre();
							}
							cout<<"Que imagen desea aplicarle el filtro pasa altas Roberts(Numero):"<<endl;
							cin>>ig;
							cout<<"Nombre de la imagen (Nombre.pgm/ppm) si existe se modificara:"<<endl;
							cin>>Nombre[contador];
							n[ig].FiltroRoberts(Nombre[contador]);
							n[contador].LeerImagen(Nombre[contador]);
							contador++;
						}
						break;

					case 6://Filtro Mediana
						system("clear");
						if(contador > 0){
							cout<<"Imagenes Guardadas:"<<endl;
							for(int i = 0; i < contador; i++){
								cout<<"Numero:"<<i<<"   Nombre: ";
								n[i].GetNombre();
							}
							cout<<"Que imagen desea aplicarle el filtro pasa bajas MEDIANA (Numero):"<<endl;
							cin>>ig;
							cout<<"Nombre de la imagen (Nombre.pgm/ppm) si existe se modificara:"<<endl;
							cin>>Nombre[contador];
							n[ig].FiltroMinMed(Nombre[contador],4);
							n[contador].LeerImagen(Nombre[contador]);
							contador++;
						}
						break;

					case 7://Filtro Mediana
						system("clear");
						if(contador > 0){
							cout<<"Imagenes Guardadas:"<<endl;
							for(int i = 0; i < contador; i++){
								cout<<"Numero:"<<i<<"   Nombre: ";
								n[i].GetNombre();
							}
							cout<<"Que imagen desea aplicarle el filtro pasa bajas MODA (Numero):"<<endl;
							cin>>ig;
							cout<<"Nombre de la imagen (Nombre.pgm/ppm) si existe se modificara:"<<endl;
							cin>>Nombre[contador];
							n[ig].FiltroModa(Nombre[contador]);
							n[contador].LeerImagen(Nombre[contador]);
							contador++;
						}
						break;

					case 8://Filtro Minimo
						system("clear");
						if(contador > 0){
							cout<<"Imagenes Guardadas:"<<endl;
							for(int i = 0; i < contador; i++){
								cout<<"Numero:"<<i<<"   Nombre: ";
								n[i].GetNombre();
							}
							cout<<"Que imagen desea aplicarle el filtro pasa bajas MININO (Numero):"<<endl;
							cin>>ig;
							cout<<"Nombre de la imagen (Nombre.pgm/ppm) si existe se modificara:"<<endl;
							cin>>Nombre[contador];
							n[ig].FiltroMinMed(Nombre[contador],0);
							n[contador].LeerImagen(Nombre[contador]);
							contador++;
						}
						break;

					default:
						break;
				}
				system("clear");
				break;

			case 10://Salir
				return 0;
				break;

			default :
				return 1;
				break;				
		}
	}
	return 0;
}