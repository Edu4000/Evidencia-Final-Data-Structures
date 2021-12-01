#include <iostream>
#include <fstream>	// Leer el archivo
#include <sstream>	// tokenizar el string de cada registro
#include <random>
#include "tablahash.h"
#include "registro.h"

using namespace std;

// O(1)
bool sort_frq_str(const pair<string,int> &a,
			  const pair<string,int> &b)
{
	return (a.second > b.second);
}

// O(1)
bool sort_frq_int(const pair<int,int> &a,
			  const pair<int,int> &b)
{
	return (a.second > b.second);
}

int main(int nargs, char * args[]){

	// Limiting arguments for main / O(1)
	if(nargs == 0){
		cerr << "Error por numero de argumentos: Ningun argumento recibido" << endl;
		exit(1);
	} else if (nargs > 2){
		cerr << "Error por numero de argumentos: Demasiados argumentos recibido" << endl;
		exit(2);
	}

	// Get file name from arguments / O(1)
	string fileName = string(args[1]);
	
	// Create a text string, which is used to output the text file / O(1)
	string mes, hora, ip, errorLog, myText, aux;
	int dia;
	Registro dummy;

	// Data Structures Initialization
	hash<string> hashF;
	vector<pair<string,int>>* ips = new vector<pair<string,int>>();
	vector<pair<string,int>>* ports = new vector<pair<string,int>>();
	vector<pair<int,int>>* weeks = new vector<pair<int,int>>();

	HashTable<string, Registro> bitacoraIP(113379);
	HashTable<string, Registro> bitacoraPorts(113379);
	HashTable<int, Registro> bitacoraSemanas(53);
	
	// HashTable para dias acumulados por mes
	HashTable <string, int> dias_acum (32);
	dias_acum.put("Jan",1);
	dias_acum.put("Feb",32);
	dias_acum.put("Mar",60);
	dias_acum.put("Apr",91);
	dias_acum.put("May",121);
	dias_acum.put("Jun",152);
	dias_acum.put("Jul",182);
	dias_acum.put("Aug",213);
	dias_acum.put("Oct",244);
	dias_acum.put("Sep",274);
	dias_acum.put("Nov",305);
	dias_acum.put("Dec",335);

	// Read from the text file / O(1)
	ifstream MyReadFile(fileName);

	// Use a while loop together with the getline() function to read the file line by line / O(n)
	cout << "\nLEYENDO ARCHIVO" << endl;
	int ctr = 0;
	while (getline (MyReadFile, myText)){
		if(ctr < 1000){
			ctr++;
		}else{
			ctr = 0;
			cout << "#";
		}

		istringstream tokens(myText);
		tokens >> mes;		// O(1)
		tokens >> dia;		// O(1)
		tokens >> hora;		// O(1)
		tokens >> ip;		// O(1)
		errorLog = "";		// O(1)
		// O(1) 
		while(getline (tokens, aux)){
			errorLog = aux;
			errorLog.erase(0,1);
		}

		dummy = Registro(mes, dia, hora, ip, errorLog);	// O(1)

		// Adding Registros
		int week = 1 + (dummy.get_dia() + dias_acum.get(dummy.get_mes()))/7;

		// Agregando a Tabla Hash / O(1)
		bitacoraIP.put_add(dummy.get_ip(),dummy);
		bitacoraPorts.put_add(dummy.get_port(),dummy);
		bitacoraSemanas.put_add(week,dummy);
	}
	cout << "\nLECTURA DE ARCHIVO FINALIZADA" << endl;

	// Close the file / O(1)
	MyReadFile.close();

	// ################################################################
	// ###              RESPUESTAS EVIDENCIA FINAL                  ###
	// ################################################################

	// ¿Cuáles son las cinco direcciones IP (sin importar el número de puerto) que tuvieron más accesos ilegales?
	cout << "\n--> Direcciones IP con mas accesos ilegales" << endl;
	vector<pair<string,int>> answer1 = bitacoraIP.keys_freq(); // O(n)
	sort(answer1.begin(), answer1.end(), sort_frq_str);
	for(int i = 0; i < 5; i++){
		cout << i+1 << ": " << answer1.at(i).first << " (" << answer1.at(i).second << " accesos ilegales)" << endl;
	}

	// ¿Con qué frecuencia aparecen cada uno de los distintos mensajes de error (razón de la falla)?
	

	// ¿Cuántos números de puertos distintos fueron atacados en total?
	cout << "\n--> Cuantos numeros de puertos distintos fueron atacados en total?" << endl;
	int answer3 = bitacoraPorts.keys().size();
	cout << "Numero de Puertos atacados: " << answer3 << endl;

	// ¿En qué semana se detectaron una mayor cantidad de accesos ilegales? Se puede suponer que: 1) una semana inicia el día lunes y termina el domingo, y 2) las fechas de los archivos de bitácoras corresponden al año 2020.
	cout << "\n--> En que semana se detectaron una mayor cantidad de accesos ilegales?" << endl;
	vector<pair<int,int>> answer4 = bitacoraSemanas.keys_freq(); // O(n)
	sort(answer4.begin(), answer4.end(), sort_frq_int);
	cout << "Semana: " << answer4.size() << endl;

	return 0;
}